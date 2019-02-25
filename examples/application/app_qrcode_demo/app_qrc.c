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
#include "aw_sem.h"
#include "aw_mem.h"
#include "aw_vdebug.h"
#include "aw_qrcode_decode.h"
#include "string.h"



#define __QRC_TSK_STACK     20 * 1024
#define __QRC_OUT_BUF_SIZE  256

#define __DECODE_TIME_LOG   0


struct __app_qrc {
    bool_t          busy;
    int             width;
    int             height;
    void           *p_buf;
    int             size;
    void           *p_output;
    void           *p_arg;
    void (*pfn_done) (void *p_arg, bool_t found, void *p_dat, int len);
    AW_TASK_DECL(   tsk, __QRC_TSK_STACK);
    AW_SEMB_DECL(   sync);
};



#if 0
/******************************************************************************/
aw_local void  __565_to_8888 (uint8_t *rgb565, uint8_t *rgb8888, int len)
{
#define    RGB565_MASK_RED   0xF800
#define    RGB565_MASK_GREEN 0x07E0
#define    RGB565_MASK_BLUE  0x001F
    uint32_t i = 0;
    uint16_t _565;
    uint8_t r = 0, g = 0, b = 0, max = 0;

    /* rgb565  to rgb888  */
    for (i = 0; i < len; i++) {

        _565 = ((uint16_t)rgb565[1] << 8) | rgb565[0];

        r = (_565 & RGB565_MASK_RED) >> 11;
        g = (_565 & RGB565_MASK_GREEN) >> 5;
        b = (_565 & RGB565_MASK_BLUE);

        r <<= 3;
        g <<= 2;
        b <<= 3;

        if (r > g) {
            if (r > b) {
                max = r;
            } else {
                max = b;
            }
        } else {
            if (g > b) {
                max = g;
            } else {
                max = b;
            }
        }

        rgb8888[0] = b;
        rgb8888[1] = g;
        rgb8888[2] = r;
        rgb8888[3] = max;

        rgb8888 += 4;
        rgb565  += 2;
    }
}
#endif



/******************************************************************************/
aw_local void  __565_to_gray (uint8_t *p_565, uint8_t *p_gray, int len)
{
    int      i;
    uint16_t rgb;

    for (i = 0; i < len; i++, p_gray++, p_565 += 2) {
        memcpy(&rgb, p_565, 2);
        *p_gray = (rgb >> 11) * 0.3 * 8 +
                  ((rgb >> 5) & 0x3F) * 0.59 * 4 +
                  (rgb & 0x1F) * 0.11 * 8;
    }
}




/******************************************************************************/
aw_local void __qrc_tsk_handle (void *p_arg)
{
    struct __app_qrc *p_app = (struct __app_qrc *)p_arg;
    int               ret;
    aw_tick_t         tick;

    AW_FOREVER {
        /* 等待输入图像 */
        AW_SEMB_TAKE(p_app->sync, AW_SEM_WAIT_FOREVER);

#if __DECODE_TIME_LOG
        tick = aw_sys_tick_get();
#endif

        /* 解析并识别二维码 */
        ret = aw_qrcode_decode(p_app->p_buf,
                               p_app->width,
                               p_app->height,
                               p_app->p_output,
                               __QRC_OUT_BUF_SIZE - 1);

#if __DECODE_TIME_LOG
        tick = aw_sys_tick_diff(tick, aw_sys_tick_get());
        aw_kprintf("qrcode time %d ms \r\n", aw_ticks_to_ms(tick));
#endif

        p_app->busy = FALSE;

        if (p_app->pfn_done) {
            /* 输出二维码信息 */
            p_app->pfn_done(p_app->p_arg,
                            ret ? FALSE : TRUE,
                            p_app->p_output,
                            strlen(p_app->p_output));
        }
    }
}




/******************************************************************************/
void *app_qrc_create (int   max_width,
                      int   max_height,
                      void  *p_arg,
                      void (*pfn_done) (void *p_arg, bool_t found, void *p_dat, int len))
{
    struct __app_qrc *p_app;

    /* 创建对象内存 */
    p_app = aw_mem_alloc(sizeof(*p_app) + max_width * max_height + __QRC_OUT_BUF_SIZE);
    if (p_app == NULL) {
        return NULL;
    }

    /* 初始化对象并启动程序 */
    p_app->busy         = FALSE;
    p_app->size         = max_width * max_height;
    p_app->p_buf        = ((uint8_t *)p_app) + sizeof(*p_app);//TODO 此处是否需要进行内存对齐
    p_app->p_output     = ((uint8_t *)p_app->p_buf) + p_app->size * 4;
    p_app->pfn_done     = pfn_done;
    p_app->p_arg        = p_arg;

    AW_SEMB_INIT(p_app->sync, 0, AW_SEM_Q_PRIORITY);
    AW_TASK_INIT(p_app->tsk,
                 "QRC",
                 10,
                 __QRC_TSK_STACK ,
                 __qrc_tsk_handle,
                 (void *)p_app);

    AW_TASK_STARTUP(p_app->tsk);

    return p_app;
}




/******************************************************************************/
void app_qrc_destroy (void *handle)
{
    struct __app_qrc *p_app = (struct __app_qrc *)handle;

    AW_TASK_TERMINATE(p_app->tsk);
    AW_SEMB_TERMINATE(p_app->sync);
    aw_mem_free(p_app);
}





/******************************************************************************/
aw_err_t app_qrc_once (void *handle,
                       void *img,
                       int   width,
                       int   height)
{
    struct __app_qrc *p_app = (struct __app_qrc *)handle;

    if (p_app->busy) {
        return -AW_EBUSY;
    }

    if ((width * height) > p_app->size) {
        return -AW_ERANGE;
    }

    p_app->busy   = TRUE;
    p_app->height = height;
    p_app->width  = width;

    /* 将565图片转成8888 */
//    __565_to_8888(img, p_app->p_buf, width * height);
    __565_to_gray(img, p_app->p_buf, width * height);

//    memcpy(p_app->p_buf, img, width * height * 2);

    AW_SEMB_GIVE(p_app->sync);
    return AW_OK;
}
