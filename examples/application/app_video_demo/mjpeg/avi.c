#include "avi.h"
#include "mjpeg.h"
#include "aw_vdebug.h"


#define    __MAKE_WORD(ptr)    (uint16_t) (((uint16_t) * ((uint8_t *)(ptr)) << 8) | \
                               (uint16_t) * (uint8_t *) ((ptr) + 1))

#define    __MAKE_DWORD(ptr)   (uint32_t) (((uint16_t) * (uint8_t*)(ptr)    | \
                               (((uint16_t) * (uint8_t *) (ptr + 1)) << 8)  | \
                               (((uint16_t) * (uint8_t *) (ptr + 2)) << 16) | \
                               (((uint16_t) * (uint8_t *) (ptr + 3)) << 24)))

avi_info_t avix;                      /* avi文件相关信息 */

const uint8_t * AVI_VIDS_FLAG_TBL[2] = {"00dc", "01dc"};  /* 视频编码标志字符串,00dc/01dc */
const uint8_t * AVI_AUDS_FLAG_TBL[2] = {"00wb", "01wb"};  /* 音频编码标志字符串,00wb/01wb */


/**
 * \brief 查找 ID
 */
uint16_t avi_srarch_id (uint8_t *p_buf, uint16_t size, const char *id)
{
    uint16_t i = 0;
    size -= 4;
    for (i = 0; i < size; i++) {
        if ((p_buf[i] == id[0]) && (p_buf[i + 1] == id[1]) &&
            (p_buf[i + 2] == id[2]) && (p_buf[i + 3] == id[3])) {

            /* 找到"id"所在的位置 */
            return i;
        }
    }
    return 0;
}


/**
 * \brief 得到stream流信息
 */
avi_status_t avi_get_streaminfo (uint8_t *p_buf, uint16_t *stream_id, uint32_t *stream_size)
{
    *stream_id   = __MAKE_WORD(p_buf + 2);    /* 得到流类型 */
    *stream_size = __MAKE_DWORD(p_buf + 4);   /* 得到流大小 */
    if (*stream_size % 2) {
        (*stream_size)++;     /* 奇数加1 (avix.stream_size,必须是偶数) */
    }
    if ((*stream_id == AVI_VIDS_FLAG) || (*stream_id == AVI_AUDS_FLAG)) {
        return AVI_OK;
    }
    return AVI_STREAM_ERR;
}


/**
 * \brief AVI视频解码初始化
 */
avi_status_t avi_init (uint8_t *p_buf, uint16_t size, avi_info_t *p_info)
{
    uint16_t offset;
    uint8_t  *tbuf;
    avi_status_t   res=AVI_OK;
    avi_header_t  *avi_header  = NULL;
    list_header_t *list_header = NULL;
    avih_header_t *avih_header = NULL;
    strh_header_t *strh_header = NULL;

    strf_bmp_header_t *bmp_header = NULL;
    strf_wav_header_t *wav_header = NULL;

    tbuf = p_buf;
    avi_header = (avi_header_t *)p_buf;
    if (avi_header->riff_id != AVI_RIFF_ID) {
        return AVI_RIFF_ERR;               /* RIFF ID错误 */
    }
    if(avi_header->avi_id != AVI_AVI_ID) {
        return AVI_AVI_ERR;                 /* AVI ID错误 */
    }
    p_buf += sizeof(avi_header_t);         /* 偏移 */
    list_header = (list_header_t*)(p_buf);
    if (list_header->list_id != AVI_LIST_ID) {
        return AVI_LIST_ERR;                /* LIST ID错误 */
    }
    if (list_header->list_type != AVI_HDRL_ID) {
        return AVI_HDRL_ERR;                /* HDRL ID错误 */
    }
    p_buf += sizeof(list_header_t);        /* 偏移 */
    avih_header = (avih_header_t *)(p_buf);
    if (avih_header->block_id!=AVI_AVIH_ID) {
        return AVI_AVIH_ERR;                /* AVIH ID错误 */
    }
    p_info->sec_per_frame = avih_header->sec_per_frame;   /* 得到帧间隔时间 */
    p_info->total_frame = avih_header->total_frame;       /* 得到总帧数 */
    p_buf += avih_header->block_size+8;                /* 偏移 */
    list_header = (list_header_t *)(p_buf);
    if (list_header->list_id != AVI_LIST_ID) {
        return AVI_LIST_ERR;        /* LIST ID错误 */
    }
    if (list_header->list_type != AVI_STRL_ID) {
        return AVI_STRL_ERR;        /* STRL ID错误 */
    }
    strh_header = (strh_header_t *)(p_buf + 12);
    if (strh_header->block_id != AVI_STRH_ID) {
        return AVI_STRH_ERR;        /* STRH ID错误 */
    }
    if (strh_header->stream_type == AVI_VIDS_STREAM) {     /* 视频帧在前 */

        if (strh_header->handler != AVI_FORMAT_MJPG) {
            return AVI_FORMAT_ERR;                          /* 非MJPG视频流,不支持 */
        }
        p_info->video_flag = (uint8_t*)AVI_VIDS_FLAG_TBL[0];  /* 视频流标记  "00dc" */
        p_info->audio_flag = (uint8_t*)AVI_AUDS_FLAG_TBL[1];  /* 音频流标记  "01wb" */
        bmp_header = (strf_bmp_header_t*)(p_buf + 12 + strh_header->block_size + 8);
        if (bmp_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;                    /* STRF ID错误 */
        }
        p_info->width  = bmp_header->bmp_header.width;
        p_info->height = bmp_header->bmp_header.height;
        p_buf += list_header->block_size + 8;      /* 得到偏移 */
        list_header = (list_header_t*)(p_buf);
        if (list_header->list_id != AVI_LIST_ID) { /* 是不含有音频帧的视频文件 */

            p_info->sample_rate = 0;                  /* 音频采样率 */
            p_info->channels    = 0;                  /* 音频通道数 */
            p_info->audio_type  = 0;                  /* 音频格式 */
        } else {
            if (list_header->list_type != AVI_STRL_ID) {
                return AVI_STRL_ERR;     /* STRL ID错误 */
            }
            strh_header = (strh_header_t*)(p_buf + 12);
            if (strh_header->block_id!=AVI_STRH_ID) {
                return AVI_STRH_ERR;     /* STRH ID错误 */
            }
            if (strh_header->stream_type!=AVI_AUDS_STREAM) {
                return AVI_FORMAT_ERR;   /* 格式错误 */
            }
            wav_header = (strf_wav_header_t*)(p_buf + 12 + strh_header->block_size + 8);/* strf */
            if (wav_header->block_id != AVI_STRF_ID) {
                return AVI_STRF_ERR;     /* STRF ID错误 */
            }

            p_info->sample_rate = wav_header->sample_rate;        /* 音频采样率 */
            p_info->channels    = wav_header->channels;           /* 音频通道数 */
            p_info->audio_type  = wav_header->format_tag;         /* 音频格式 */
        }
    } else if (strh_header->stream_type == AVI_AUDS_STREAM) {  /* 音频帧在前 */

        p_info->video_flag = (uint8_t*)AVI_VIDS_FLAG_TBL[1];      /* 视频流标记  "01dc" */
        p_info->audio_flag = (uint8_t*)AVI_AUDS_FLAG_TBL[0];      /* 音频流标记  "00wb" */
        wav_header = (strf_wav_header_t*)(p_buf + 12 + strh_header->block_size + 8);
        if (wav_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;                        /* STRF ID错误 */
        }
        p_info->sample_rate = wav_header->sample_rate;    /* 音频采样率 */
        p_info->channels    = wav_header->channels;       /* 音频通道数 */
        p_info->audio_type  = wav_header->format_tag;     /* 音频格式 */
        p_buf += list_header->block_size+8;
        list_header = (list_header_t*)(p_buf);
        if (list_header->list_id!=AVI_LIST_ID) {
            return AVI_LIST_ERR;         /* LIST ID错误 */
        }
        if (list_header->list_type!=AVI_STRL_ID) {
            return AVI_STRL_ERR;         /* STRL ID错误 */
        }
        strh_header = (strh_header_t*)(p_buf + 12);
        if (strh_header->block_id!=AVI_STRH_ID) {
            return AVI_STRH_ERR;         /* STRH ID错误 */
        }
        if (strh_header->stream_type!=AVI_VIDS_STREAM) {
            return AVI_FORMAT_ERR;       /* 格式错误 */
        }
        bmp_header = (strf_bmp_header_t*)(p_buf + 12 + strh_header->block_size + 8);/* strf */
        if (bmp_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;         /* STRF ID错误 */
        }
        if (bmp_header->bmp_header.compression != AVI_FORMAT_MJPG) {
            return AVI_FORMAT_ERR;       /* 格式错误 */
        }
        p_info->width  = bmp_header->bmp_header.width;
        p_info->height = bmp_header->bmp_header.height;
    }
    offset = avi_srarch_id(tbuf, size, (uint8_t *)"movi");  /* 查找movi ID */
    if (offset == 0) {
        return AVI_MOVI_ERR;                      /* MOVI ID错误 */
    }
    if (p_info->sample_rate) {                      /* 有音频流,才查找 */

        tbuf += offset;
        offset = avi_srarch_id(tbuf, size, p_info->audio_flag);  /* 查找音频流标记 */
        if (offset == 0) {
            return AVI_STREAM_ERR;                             /* 流错误 */
        }
        tbuf += offset + 4;
        p_info->audio_buf_size = *((uint16_t*)tbuf);             /* 得到音频流buf大小 */
    }
    AW_INFOF(("avi init ok\r\n"));
    AW_INFOF(("avi sec_per_frame:%d\r\n",p_info->sec_per_frame));
    AW_INFOF(("avi total_frame:%d\r\n",p_info->total_frame));
    AW_INFOF(("avi width:%d\r\n",p_info->width));
    AW_INFOF(("avi height:%d\r\n",p_info->height));
    AW_INFOF(("avi audio_type:%d\r\n",p_info->audio_type));
    AW_INFOF(("avi sample_rate:%d\r\n",p_info->sample_rate));
    AW_INFOF(("avi channels:%d\r\n",p_info->channels));
    AW_INFOF(("avi audio_buf_size:%d\r\n",p_info->audio_buf_size));
    AW_INFOF(("avi video_flag:%s\r\n",p_info->video_flag));
    AW_INFOF(("avi audio_flag:%s\r\n",p_info->audio_flag));
    return res;
}


/* end of file */
