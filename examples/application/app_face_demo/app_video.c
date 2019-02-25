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
#include "aw_vdebug.h"

#include "string.h"

#include "app_video.h"


#define __VIDEO_TSK_STACK  64 * 1024

/* 摄像头名称 */
#define __CAMERA_NAME              "ov7725"

#define __EMWIN_FB                 "imx1050_emwin_fb"  /*根据具体平台修改*/

/**
 * /brief摄像头像分辨率素宽度 和 高度
 * 支持的分辨率有： 640 X 480 、320 X 240
 */
#define __RESOLUTION_WIDTH          320
#define __RESOLUTION_HEIGHT         240

/** \brief 设置VIDEO和PHOTO的分辨率   */
#define __VIDEO_RES                 AW_RESOLUTION_SET(__RESOLUTION_WIDTH, __RESOLUTION_HEIGHT)
#define __PHOTO_RES                 AW_RESOLUTION_SET(__RESOLUTION_WIDTH, __RESOLUTION_HEIGHT)

struct __app_frame_buf {
    uint8_t *p_mem;
    int      xsize;
    int      ysize;
};

struct __app_video {
    AW_TASK_DECL(           tsk, __VIDEO_TSK_STACK);
    struct __app_frame_buf  buf;

    struct app_video_rect   vrect;

    void  *p_arg;
    void (*pfn_img) (void *p_arg, void *img, int width, int height);
};



/******************************************************************************/
aw_err_t app_fbuf_rect_fill (void                  *handle,
                             struct app_video_rect *p_rect,
                             uint8_t               *p_data)
{
    struct __app_video *p_app = (struct __app_video *)handle;
    int                 idx, y;
    int                 nline, nrow;


    if ((p_rect->x1 < p_rect->x0) || (p_rect->y1 < p_rect->y0)) {
        return -AW_EINVAL;
    }

    nrow  = p_rect->x1 - p_rect->x0 + 1;
    nline = p_rect->y1 - p_rect->y0 + 1;

    if ((nrow > p_app->buf.xsize) || (nline >  p_app->buf.ysize)) {
        return -AW_EDOM;
    }

    for (y = 0; y < nline; y++) {
        idx = ((p_rect->y0 + y) * p_app->buf.xsize + p_rect->x0) * 2;
        if (idx >= ((480*272-480) * 2)) {
            aw_kprintf("out of range.\n\r");
            while (1);
        }
        memcpy(&p_app->buf.p_mem[idx], p_data, nrow * 2);
        p_data += (nrow * 2);
    }

    return AW_OK;
}




/******************************************************************************/
aw_err_t app_fbuf_pixel (void                   *handle,
                         int                     x,
                         int                     y,
                         uint16_t                color)
{
    struct __app_video *p_app = (struct __app_video *)handle;
    int                 idx;

    if ((x > p_app->buf.xsize) || (y > p_app->buf.ysize)) {
        return -AW_EINVAL;
    }

    idx = (y * p_app->buf.xsize + x) * 2;
    if (idx >= (480*272*2)) {
        aw_kprintf("out of range.\n\r");
        while (1);
    }

    memcpy(&p_app->buf.p_mem[idx], &color, sizeof(color));

    return AW_OK;
}


/******************************************************************************/
aw_err_t app_fbuf_rect_line (void                  *handle,
                             struct app_video_rect *p_rect,
                             uint16_t               color)
{
    struct __app_video *p_app = (struct __app_video *)handle;
    int                 len, i;

    if ((p_rect->x1 <= p_rect->x0) ||
        (p_rect->y1 <= p_rect->y0) ||
        (p_rect->x1 > p_app->buf.xsize) ||
        (p_rect->y1 > p_app->buf.ysize)) {
        return -AW_EINVAL;
    }

    len = p_rect->x1 - p_rect->x0 + 1;
    for (i = 0; i < len; i++) {
        app_fbuf_pixel(p_app, p_rect->x0 + i, p_rect->y0, color);
        app_fbuf_pixel(p_app, p_rect->x0 + i, p_rect->y0+1, color);
        app_fbuf_pixel(p_app, p_rect->x0 + i, p_rect->y1-1, color);
        app_fbuf_pixel(p_app, p_rect->x0 + i, p_rect->y1, color);
    }

    len = p_rect->y1 - p_rect->y0 + 1;
    for (i = 0; i < len; i++) {
        app_fbuf_pixel(p_app, p_rect->x0, p_rect->y0 + i, color);
        app_fbuf_pixel(p_app, p_rect->x0+1, p_rect->y0 + i, color);
        app_fbuf_pixel(p_app, p_rect->x1-1, p_rect->y0 + i, color);
        app_fbuf_pixel(p_app, p_rect->x1, p_rect->y0 + i, color);
    }

    return AW_OK;
}



/******************************************************************************/
aw_err_t app_video_rect_line (void                  *handle,
                              struct app_video_rect *p_rect,
                              uint16_t               color)
{
    struct __app_video    *p_app = (struct __app_video *)handle;
    struct app_video_rect  rect;

    rect.x0 = p_rect->x0 + p_app->vrect.x0;
    rect.x1 = p_rect->x1 + p_app->vrect.x0;
    rect.y0 = p_rect->y0 + p_app->vrect.y0;
    rect.y1 = p_rect->y1 + p_app->vrect.y0;

    return app_fbuf_rect_line(handle, &rect, color);
}



/******************************************************************************/
aw_local void __video_mirror (uint8_t *p_buf, int width, int height)
{
    uint16_t pixel;
    int      i, j;
    int      tail;

    tail = (width - 1) << 1;

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i += 2) {
            memcpy(&pixel, &p_buf[i], 2);
            memcpy(&p_buf[i], &p_buf[tail - i], 2);
            memcpy(&p_buf[tail - i], &pixel, 2);
        }

        p_buf += (width << 1);
    }
}

/******************************************************************************/
aw_local void __video_mirror1 (uint16_t *p_src, uint16_t *p_dst, int width, int height)
{
    int      i, j;

    uint16_t *ptr;

    for (j = 0; j < height; j++) {
        p_src += width;
        ptr = p_src - 1;
        for (i = 0; i < width; i++) {

            *p_dst = *ptr;

            p_dst++;
            ptr--;
        }
    }
}



/******************************************************************************/
aw_local void __video_tsk_handle (void *p_arg)
{
    struct awbl_camera_service  *p_cam = NULL;
    aw_emwin_fb_info_t          *p_fb  = NULL;
    struct aw_camera_cfg         cfg;
    void                        *vbuf = 0, *p_buf;
    struct __app_video          *p_app;

    p_app = (struct __app_video *)p_arg;

    p_buf = aw_mem_alloc(__RESOLUTION_WIDTH * __RESOLUTION_HEIGHT * 2);
    if (p_buf == NULL) {
        return;
    }

    /* 打开摄像头 */
    p_cam = aw_camera_open(__CAMERA_NAME);
    if (p_cam == NULL) {
        aw_kprintf("camera open failed!\r\n");
        return;
    }

    /* 打开显示器 */
    p_fb = aw_emwin_fb_open(__EMWIN_FB, 0);
    if (p_fb == NULL) {
        aw_kprintf("screen open failed!\r\n");
        goto __failed;
    }

    if (aw_emwin_fb_init(p_fb, NULL, AW_FB_HORIZONTAL_SCREEN) != AW_OK) {
        goto __failed;
    }
    aw_emwin_fb_backlight(p_fb, 100);
    aw_emwin_fb_run(p_fb);

    p_app->buf.p_mem = (uint8_t *)p_fb->v_addr;
    p_app->buf.ysize = p_fb->y_res;
    p_app->buf.xsize = p_fb->x_res;

    memset(p_app->buf.p_mem, 0x00, p_app->buf.ysize * p_app->buf.xsize * 2);

    p_app->vrect.x0 = (p_fb->x_res - __RESOLUTION_WIDTH) / 2;
    p_app->vrect.y0 = (p_fb->y_res - __RESOLUTION_HEIGHT) / 2;

    p_app->vrect.x1 = p_app->vrect.x0 + __RESOLUTION_WIDTH - 1;
    p_app->vrect.y1 = p_app->vrect.y0 + __RESOLUTION_HEIGHT - 1;

    /* 配置摄像头像素 */
    cfg.photo_resolution =  __PHOTO_RES;
    cfg.video_resolution =  __VIDEO_RES;
    aw_camera_cfg(p_cam, &cfg);

    AW_FOREVER {
        /* 获取一帧摄像头数据 */
        aw_camera_get_video_buf(p_cam, &vbuf);

//        __video_mirror((uint8_t *)p_buf, 320, 240);
        __video_mirror1((uint16_t *)vbuf, (uint16_t *)p_buf, __RESOLUTION_WIDTH, __RESOLUTION_HEIGHT);
        /* 拷贝到显存进行显示 */
        app_fbuf_rect_fill(p_app, &p_app->vrect, (uint8_t*)p_buf);
//        app_fbuf_rect_line(p_app, &p_app->vrect, 0x5555);
        /* 进行捕获画面输出 */
        if (p_app->pfn_img) {
            p_app->pfn_img(p_app->p_arg, (void *)p_buf, __RESOLUTION_WIDTH, __RESOLUTION_HEIGHT);
        }
        /* 释放摄像头图像内存 */
        aw_camera_release_video_buf(p_cam, vbuf);
        aw_mdelay(50);
    }

__failed:
    if (p_cam) {
        aw_camera_close(p_cam);
    }

    while(1);
}




/******************************************************************************/
void *app_video_create (void  *p_arg,
                        void (*pfn_img) (void *p_arg, void *img, int width, int height))
{
    struct __app_video *p_app;

    /* 创建对象 */
    p_app = (struct __app_video *)aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }

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
    aw_mem_free(p_app);
}


