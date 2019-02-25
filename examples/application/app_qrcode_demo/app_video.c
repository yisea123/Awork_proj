/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#include "aworks.h"
#include "aw_task.h"
#include "aw_mem.h"
#include "aw_emwin_fb.h"
#include "aw_delay.h"
#include "aw_camera.h"

//#include "driver/camera/awbl_camera.h"
//#include "driver/camera/awbl_ov7725.h"

#include "WM.H"

#include "string.h"



#define __VIDEO_TSK_STACK  10 * 1024

struct __app_video {
    WM_HWIN hwin;
    AW_TASK_DECL(tsk, __VIDEO_TSK_STACK);
    void  *p_arg;
    void (*pfn_img) (void *p_arg, void *img, int width, int height);
};




/******************************************************************************/
aw_local void __video_tsk_handle (void *p_arg)
{
    struct awbl_camera_service  *p_cam = NULL;
    aw_emwin_fb_info_t          *p_fb  = NULL;
    uint8_t                     *p_buf = NULL;
    struct aw_camera_cfg         cfg;
    void                        *vbuf = 0;
    int                          i;
    GUI_RECT                     rect;
    struct __app_video          *p_app;

    p_app = (struct __app_video *)p_arg;

    /* 打开摄像头 */
    p_cam = aw_camera_open("ov7725");
    if (p_cam == NULL) {
        return;
    }

    /* 打开显示器 */
    p_fb = aw_emwin_fb_open("imx1050_emwin_fb", 0);
    if (p_fb == NULL) {
        goto __failed;
    }
    p_buf = (void *)p_fb->v_addr;   //获取显存地址

    /* 配置摄像头像素 */
    cfg.photo_resolution =  AW_RESOLUTION_SET(320, 240);
    cfg.video_resolution =  AW_RESOLUTION_SET(320, 240);
    aw_camera_cfg(p_cam, &cfg);

    /* 计算画面显示位置 */
    WM_GetClientRectEx(p_app->hwin, &rect);
    rect.x0 += ((rect.x1 - rect.x0) - 320) / 2;
    rect.y0 += ((rect.y1 - rect.y0) - 240) / 2;

    AW_FOREVER {
        /* 获取一帧摄像头数据 */
        aw_camera_get_video_buf(p_cam, &vbuf);

        /* 拷贝到显存进行显示 */
        for (i = 0; i < 240; i ++) {
            memcpy((uint8_t*)p_buf + rect.x0 * 2 + 480 * 2 * (i + rect.y0),
                   (uint8_t*)vbuf + 320 * 2 * i,
                   320 * 2);
        }

        /* 进行捕获画面输出 */
        if (p_app->pfn_img) {
            p_app->pfn_img(p_app->p_arg, (void *)vbuf, 320, 240);
        }

        /* 释放摄像头图像内存 */
        aw_camera_release_video_buf(p_cam, vbuf);

        aw_mdelay(1);
    }

__failed:
    if (p_buf) {
        aw_mem_free(p_buf);
    }

    if (p_cam) {
        aw_camera_close(p_cam);
    }

    while(1);
}




/******************************************************************************/
aw_local void __win_video_cb (WM_MESSAGE *pMsg)
{
    switch (pMsg->MsgId) {

    case WM_PAINT:
        /* 设置背景颜色  */
        GUI_SetBkColor(GUI_BLACK);
        GUI_Clear();
        break;

    default:
        WM_DefaultProc(pMsg);
        break;

    }
}




/******************************************************************************/
void *app_video_create (WM_HWIN hwin,
                        int x, int y,
                        int xsize, int ysize,
                        void  *p_arg,
                        void (*pfn_img) (void *p_arg, void *img, int width, int height))
{
    struct __app_video *p_app;

    /* 创建对象 */
    p_app = (struct __app_video *)aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }

    /* 创建对象窗口 */
    p_app->hwin = WM_CreateWindowAsChild(x, y,
                                         xsize, ysize,
                                         hwin,
                                         WM_CF_SHOW,
                                         __win_video_cb,
                                         0);
    p_app->pfn_img = pfn_img;
    p_app->p_arg   = p_arg;

    AW_TASK_INIT(p_app->tsk,
                 "video",
                 10,
                 __VIDEO_TSK_STACK ,
                 __video_tsk_handle,
                 (void *)p_app);

    AW_TASK_STARTUP(p_app->tsk);

    return p_app;
}




/******************************************************************************/
void app_video_destroy (void *handle)
{
    struct __app_video *p_app = (struct __app_video *)handle;

    AW_TASK_TERMINATE(p_app->tsk);
    WM_DeleteWindow(p_app->hwin);
    aw_mem_free(p_app);
}


