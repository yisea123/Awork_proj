#include "avi.h"
#include "mjpeg.h"
#include "aw_vdebug.h"


#define    __MAKE_WORD(ptr)    (uint16_t) (((uint16_t) * ((uint8_t *)(ptr)) << 8) | \
                               (uint16_t) * (uint8_t *) ((ptr) + 1))

#define    __MAKE_DWORD(ptr)   (uint32_t) (((uint16_t) * (uint8_t*)(ptr)    | \
                               (((uint16_t) * (uint8_t *) (ptr + 1)) << 8)  | \
                               (((uint16_t) * (uint8_t *) (ptr + 2)) << 16) | \
                               (((uint16_t) * (uint8_t *) (ptr + 3)) << 24)))

avi_info_t avix;                      /* avi�ļ������Ϣ */

const uint8_t * AVI_VIDS_FLAG_TBL[2] = {"00dc", "01dc"};  /* ��Ƶ�����־�ַ���,00dc/01dc */
const uint8_t * AVI_AUDS_FLAG_TBL[2] = {"00wb", "01wb"};  /* ��Ƶ�����־�ַ���,00wb/01wb */


/**
 * \brief ���� ID
 */
uint16_t avi_srarch_id (uint8_t *p_buf, uint16_t size, const char *id)
{
    uint16_t i = 0;
    size -= 4;
    for (i = 0; i < size; i++) {
        if ((p_buf[i] == id[0]) && (p_buf[i + 1] == id[1]) &&
            (p_buf[i + 2] == id[2]) && (p_buf[i + 3] == id[3])) {

            /* �ҵ�"id"���ڵ�λ�� */
            return i;
        }
    }
    return 0;
}


/**
 * \brief �õ�stream����Ϣ
 */
avi_status_t avi_get_streaminfo (uint8_t *p_buf, uint16_t *stream_id, uint32_t *stream_size)
{
    *stream_id   = __MAKE_WORD(p_buf + 2);    /* �õ������� */
    *stream_size = __MAKE_DWORD(p_buf + 4);   /* �õ�����С */
    if (*stream_size % 2) {
        (*stream_size)++;     /* ������1 (avix.stream_size,������ż��) */
    }
    if ((*stream_id == AVI_VIDS_FLAG) || (*stream_id == AVI_AUDS_FLAG)) {
        return AVI_OK;
    }
    return AVI_STREAM_ERR;
}


/**
 * \brief AVI��Ƶ�����ʼ��
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
        return AVI_RIFF_ERR;               /* RIFF ID���� */
    }
    if(avi_header->avi_id != AVI_AVI_ID) {
        return AVI_AVI_ERR;                 /* AVI ID���� */
    }
    p_buf += sizeof(avi_header_t);         /* ƫ�� */
    list_header = (list_header_t*)(p_buf);
    if (list_header->list_id != AVI_LIST_ID) {
        return AVI_LIST_ERR;                /* LIST ID���� */
    }
    if (list_header->list_type != AVI_HDRL_ID) {
        return AVI_HDRL_ERR;                /* HDRL ID���� */
    }
    p_buf += sizeof(list_header_t);        /* ƫ�� */
    avih_header = (avih_header_t *)(p_buf);
    if (avih_header->block_id!=AVI_AVIH_ID) {
        return AVI_AVIH_ERR;                /* AVIH ID���� */
    }
    p_info->sec_per_frame = avih_header->sec_per_frame;   /* �õ�֡���ʱ�� */
    p_info->total_frame = avih_header->total_frame;       /* �õ���֡�� */
    p_buf += avih_header->block_size+8;                /* ƫ�� */
    list_header = (list_header_t *)(p_buf);
    if (list_header->list_id != AVI_LIST_ID) {
        return AVI_LIST_ERR;        /* LIST ID���� */
    }
    if (list_header->list_type != AVI_STRL_ID) {
        return AVI_STRL_ERR;        /* STRL ID���� */
    }
    strh_header = (strh_header_t *)(p_buf + 12);
    if (strh_header->block_id != AVI_STRH_ID) {
        return AVI_STRH_ERR;        /* STRH ID���� */
    }
    if (strh_header->stream_type == AVI_VIDS_STREAM) {     /* ��Ƶ֡��ǰ */

        if (strh_header->handler != AVI_FORMAT_MJPG) {
            return AVI_FORMAT_ERR;                          /* ��MJPG��Ƶ��,��֧�� */
        }
        p_info->video_flag = (uint8_t*)AVI_VIDS_FLAG_TBL[0];  /* ��Ƶ�����  "00dc" */
        p_info->audio_flag = (uint8_t*)AVI_AUDS_FLAG_TBL[1];  /* ��Ƶ�����  "01wb" */
        bmp_header = (strf_bmp_header_t*)(p_buf + 12 + strh_header->block_size + 8);
        if (bmp_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;                    /* STRF ID���� */
        }
        p_info->width  = bmp_header->bmp_header.width;
        p_info->height = bmp_header->bmp_header.height;
        p_buf += list_header->block_size + 8;      /* �õ�ƫ�� */
        list_header = (list_header_t*)(p_buf);
        if (list_header->list_id != AVI_LIST_ID) { /* �ǲ�������Ƶ֡����Ƶ�ļ� */

            p_info->sample_rate = 0;                  /* ��Ƶ������ */
            p_info->channels    = 0;                  /* ��Ƶͨ���� */
            p_info->audio_type  = 0;                  /* ��Ƶ��ʽ */
        } else {
            if (list_header->list_type != AVI_STRL_ID) {
                return AVI_STRL_ERR;     /* STRL ID���� */
            }
            strh_header = (strh_header_t*)(p_buf + 12);
            if (strh_header->block_id!=AVI_STRH_ID) {
                return AVI_STRH_ERR;     /* STRH ID���� */
            }
            if (strh_header->stream_type!=AVI_AUDS_STREAM) {
                return AVI_FORMAT_ERR;   /* ��ʽ���� */
            }
            wav_header = (strf_wav_header_t*)(p_buf + 12 + strh_header->block_size + 8);/* strf */
            if (wav_header->block_id != AVI_STRF_ID) {
                return AVI_STRF_ERR;     /* STRF ID���� */
            }

            p_info->sample_rate = wav_header->sample_rate;        /* ��Ƶ������ */
            p_info->channels    = wav_header->channels;           /* ��Ƶͨ���� */
            p_info->audio_type  = wav_header->format_tag;         /* ��Ƶ��ʽ */
        }
    } else if (strh_header->stream_type == AVI_AUDS_STREAM) {  /* ��Ƶ֡��ǰ */

        p_info->video_flag = (uint8_t*)AVI_VIDS_FLAG_TBL[1];      /* ��Ƶ�����  "01dc" */
        p_info->audio_flag = (uint8_t*)AVI_AUDS_FLAG_TBL[0];      /* ��Ƶ�����  "00wb" */
        wav_header = (strf_wav_header_t*)(p_buf + 12 + strh_header->block_size + 8);
        if (wav_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;                        /* STRF ID���� */
        }
        p_info->sample_rate = wav_header->sample_rate;    /* ��Ƶ������ */
        p_info->channels    = wav_header->channels;       /* ��Ƶͨ���� */
        p_info->audio_type  = wav_header->format_tag;     /* ��Ƶ��ʽ */
        p_buf += list_header->block_size+8;
        list_header = (list_header_t*)(p_buf);
        if (list_header->list_id!=AVI_LIST_ID) {
            return AVI_LIST_ERR;         /* LIST ID���� */
        }
        if (list_header->list_type!=AVI_STRL_ID) {
            return AVI_STRL_ERR;         /* STRL ID���� */
        }
        strh_header = (strh_header_t*)(p_buf + 12);
        if (strh_header->block_id!=AVI_STRH_ID) {
            return AVI_STRH_ERR;         /* STRH ID���� */
        }
        if (strh_header->stream_type!=AVI_VIDS_STREAM) {
            return AVI_FORMAT_ERR;       /* ��ʽ���� */
        }
        bmp_header = (strf_bmp_header_t*)(p_buf + 12 + strh_header->block_size + 8);/* strf */
        if (bmp_header->block_id != AVI_STRF_ID) {
            return AVI_STRF_ERR;         /* STRF ID���� */
        }
        if (bmp_header->bmp_header.compression != AVI_FORMAT_MJPG) {
            return AVI_FORMAT_ERR;       /* ��ʽ���� */
        }
        p_info->width  = bmp_header->bmp_header.width;
        p_info->height = bmp_header->bmp_header.height;
    }
    offset = avi_srarch_id(tbuf, size, (uint8_t *)"movi");  /* ����movi ID */
    if (offset == 0) {
        return AVI_MOVI_ERR;                      /* MOVI ID���� */
    }
    if (p_info->sample_rate) {                      /* ����Ƶ��,�Ų��� */

        tbuf += offset;
        offset = avi_srarch_id(tbuf, size, p_info->audio_flag);  /* ������Ƶ����� */
        if (offset == 0) {
            return AVI_STREAM_ERR;                             /* ������ */
        }
        tbuf += offset + 4;
        p_info->audio_buf_size = *((uint16_t*)tbuf);             /* �õ���Ƶ��buf��С */
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
