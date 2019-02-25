/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
#include "app_video.h"
#include "fs/aw_mount.h"
#include "fs/aw_blk_dev.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "mjpeg.h"
#include "avi.h"
#include "aw_mem.h"
#include "aw_emwin_fb.h"
#include "string.h"

#define __DECODE_BUF_SIZE (60 * 1024)
#define __FB_BUF_SIZE     (480 * 252 * 2 + 4)

/*视频任务相关宏定义*/
#define __APP_VIDEO_DECODE_PRIO           34                         /** \brief 任务优先级定义 */
#define __APP_VIDEO_DECODE_STACK_SIZE    (1024 * 16)                 /** \brief stack大小定义 */
AW_TASK_DECL_STATIC(__video_task, __APP_VIDEO_DECODE_STACK_SIZE);    /** \brief 定义视频播放任务 */

GUI_BITMAP  g_video_bmp = {
    480,                    /* xSize */
    252,                    /* ySize */
    480 * 2,                /* BytesPerLine */
    16,                     /* BitsPerPixel */
    (unsigned char *)0,     /* Pointer to picture data */
    NULL,                   /* Pointer to palette */
    GUI_DRAW_BMPM565
};

/******************************************************************************/
aw_err_t __video_run ()
{


    int                 fd = -1;
    static uint8_t      decode[__DECODE_BUF_SIZE]__attribute__ ((aligned(4)));
    uint8_t            *p_buf;
    int                 len;
    uint16_t            sid;
    uint32_t            slen;
    aw_err_t            ret = AW_OK;

    /* 分配内存作为显存使用 */
    p_buf = aw_mem_align(__FB_BUF_SIZE, 4);
    if (p_buf == NULL) {
        aw_kprintf("allocate memory failed.\r\n");
        goto __exit;
    }

__next_file:

    memset(p_buf,0,__FB_BUF_SIZE);/*清除缓存*/

    fd = aw_open(gp_list_state->ready_to_play_filename, O_RDONLY, 0777);/* 打开视频文件 */
    if (fd < 0) {
        aw_kprintf("open %s failed %d.\r\n", gp_list_state->ready_to_play_filename, fd);
        goto __exit;
    }

    aw_kprintf("\r\nstart play.\r\n");
    aw_lseek(fd, 0, SEEK_SET);
    len = aw_read(fd, decode, sizeof(decode));/* 读取文件头信息 */
    if(len < 8) {
        aw_kprintf("no enough data for decode.\r\n");
        goto __exit;
    }

    /* 解析视频文件信息 */
    len = avi_srarch_id(decode, sizeof(decode), "movi");
    avi_get_streaminfo(decode+ len + 4, &sid, &slen);
    mjpegdec_init(&mjpeg_info, 0, 0);

    /* 索引到第一帧视频 */
    aw_lseek(fd, len + 12, SEEK_SET);

    while(1) {
        if(gp_play_state->stop_btn_opt_state == 1){
            continue ;
        }

        switch(gp_play_state->play_file_change_flag){
        case 0:
            if (sid == AVI_VIDS_FLAG) {
                if (slen > (sizeof(decode) - 8)) {
                    aw_kprintf("frame too large(%d->%d), to next frame.\r\n", slen + 8, sizeof(decode));
                    goto __next_frame;
                }

                len = aw_read(fd, decode, slen);
                if (len < 0 ){
                    break;
                }
                if(len < slen) {
                    goto __exit;
                }

                /* 解析一帧视频数据 */
                ret = mjpegdec_decode(&mjpeg_info, decode, p_buf, slen);
                if (ret < 0) {
                    break;
                }

                g_video_bmp.pData = (uint8_t*)p_buf;

                /* 选择主窗口作为视频显示窗口 */
                WM_SelectWindow(g_main_win);

                GUI_MULTIBUF_Begin();
                GUI_DrawBitmap(&g_video_bmp,
                               (LCD_GetXSize() - g_video_bmp.XSize) / 2,
                               (LCD_GetYSize() - g_video_bmp.YSize) / 2);
                GUI_MULTIBUF_End();

            } else {
                off_t offs;
            __next_frame:
                offs = aw_lseek(fd, 0, SEEK_CUR);
                if (aw_lseek(fd, slen, SEEK_CUR) != (offs + slen)) {
                    goto __exit;
                }
            }

            len = aw_read(fd, decode, 8);
            if (len < 0){
                break;
            }
            if(len != 8) {
                aw_close(fd);
                aw_mem_free(p_buf);
                goto __exit;
            }

            /* 获取下一帧信息 */
            avi_get_streaminfo(decode, &sid, &slen);
            break ;

        case 1:
            gp_play_state->play_file_change_flag = 0;
            GUI_Clear();
            aw_close(fd);
            goto __next_file;
        }
    }

__exit:
    GUI_Clear();
    if(fd > 0){
        aw_close(fd);
    }
    if (p_buf) {
        aw_mem_free(p_buf);
    }
    aw_kprintf("end play.\r\n");
    return ret;
}

/******************************************************************************/
aw_local void __video_task_entry (void)
{
    while (1){

        switch(gp_play_state->play_btn_opt_state){

        case PLAY_BUTTON_CLICKED_OPERATION:/*播放状态*/
            gp_play_state->play_file_change_flag = 0;
            __video_run();/*播放视频*/
            gp_play_state->play_btn_opt_state = PLAY_DONE;/*视频播放完成，正常退出*/
            break ;

        case PLAY_DONE:/*一个视频文件播放完成*/
            gp_list_state->list_btn_opt_state = LIST_SHOW;/*隐藏文件列表*/
            WM_ShowWindow(g_list_win);
            WM_HideWindow(hitem_play);
            gp_play_state->play_btn_opt_state = NO_OPERATION;
            break;

        case NO_OPERATION:/*无操作*/
            break;
        }

    }

    return ;
}

void app_vedio_task(void){

    AW_TASK_INIT(__video_task,                      /* 任务实体 */
                 "video_task",                      /* 任务名字 */
                 __APP_VIDEO_DECODE_PRIO,           /* 任务优先级 */
                 __APP_VIDEO_DECODE_STACK_SIZE,     /* 任务堆栈大小 */
                 __video_task_entry,                /* 任务入口函数 */
                 NULL);                             /* 任务入口参数 */

    /* 启动任务 */
    AW_TASK_STARTUP(__video_task);

}
