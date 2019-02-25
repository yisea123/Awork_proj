/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#include "aworks.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include <stdio.h>
#include "driver/pxp/awbl_imx1050_pxp.h"
#include "aw_emwin_fb.h"
#include "string.h"
#include "aw_bsp_mem.h"
#include "aw_mem.h"

/* 定义全局的 frame buffer 设备 */
static aw_emwin_fb_info_t  *__gp_pxp_fb;

/* 定义旋转的图像缓存 */
static uint8_t  *__gp_pxp_buf;

/* PXP Output buffer config. */
static pxp_output_buffer_config_t __g_output_buffer_config;

/* 定义屏幕的高度和宽度 */
#define __APP_IMG_HEIGHT  272
#define __APP_IMG_WIDTH   480
#define __APP_BPP         2


#if __APP_IMG_WIDTH > __APP_IMG_HEIGHT
#define __APP_PS_SIZE __APP_IMG_HEIGHT
#else
#define __APP_PS_SIZE __APP_IMG_HEIGHT
#endif

#define __APP_PS_ULC_X ((__APP_IMG_WIDTH / 2) - (__APP_PS_SIZE / 2))
#define __APP_PS_ULC_Y ((__APP_IMG_HEIGHT / 2) - (__APP_PS_SIZE / 2))
#define __APP_PS_LRC_X ((__APP_IMG_WIDTH / 2) + (__APP_PS_SIZE / 2) - 1U)
#define __APP_PS_LRC_Y ((__APP_IMG_HEIGHT / 2) + (__APP_PS_SIZE / 2) - 1U)


static void __fb_init(void)
{
    uint8_t *p_vaddr = NULL;
    __gp_pxp_fb = aw_emwin_fb_open("imx1050_emwin_fb", 0);
    TEST_ASSERT_NOT_EQUAL(NULL, __gp_pxp_fb);

    p_vaddr = (uint8_t *)aw_mem_align(__gp_pxp_fb->x_res * __gp_pxp_fb->y_res * __APP_BPP * 2,
                                      AW_CACHE_LINE_SIZE);
    TEST_ASSERT_NOT_EQUAL(NULL, p_vaddr);

    /* frame buffer 初始化 */
    aw_emwin_fb_init(__gp_pxp_fb, (uint32_t *)p_vaddr, 0);

    /* frame buffer 运行 */
    aw_emwin_fb_run(__gp_pxp_fb);

    /* 设置背光亮度 */
    aw_emwin_fb_backlight(__gp_pxp_fb, 99);

    /* 初始化屏幕背景色(白色) */
    memset(p_vaddr, 0xFF, __gp_pxp_fb->x_res *  __gp_pxp_fb->y_res * __APP_BPP);
    aw_emwin_fb_vram_addr_set(__gp_pxp_fb, (uint32_t)p_vaddr);
}

static void __rotate_buf_init (void)
{
    uint32_t i, j;
    uint16_t *pxp_buf = (uint16_t *)__gp_pxp_buf;

    /*
     * The PS input buffer is:
     *
     *  -----------------------------
     *  |             |             |
     *  |             |             |
     *  |   BLUE      |     RED     |
     *  |             |             |
     *  |             |             |
     *  |-------------+-------------|
     *  |                           |
     *  |                           |
     *  |           GREEN           |
     *  |                           |
     *  |                           |
     *  -----------------------------
     */
    for (i = 0; i < (__APP_PS_SIZE / 2); i++) {

        for (j = 0; j < (__APP_PS_SIZE / 2); j++) {
            pxp_buf[i * __APP_PS_SIZE + j] = 0x1F;
        }

        for (; j < __APP_PS_SIZE; j++) {
            pxp_buf[i * __APP_PS_SIZE + j] = 0xf800;
        }
    }

    for (; i < __APP_PS_SIZE; i++) {

        for (j = 0; j < __APP_PS_SIZE; j++) {
            pxp_buf[i * __APP_PS_SIZE + j] = 0x7e0;
        }
    }
}


static void __app_pxp_config(void)
{
    /* PS configure. */
    const pxp_ps_buffer_config_t ps_buffer_config = {
        .pixel_format = kPXP_PsPixelFormatRGB565,
        .swap_byte    = 0,
        .buffer_addr  = (uint32_t)__gp_pxp_buf,
        .buffer_addr_u = 0,
        .buffer_addr_v = 0,
        .pitch_bytes = __APP_PS_SIZE * __APP_BPP,
    };

    /* 复位PXP */
    pxp_hard_reset();

    /* 设置背景颜色 */
    pxp_set_process_surface_back_ground_color(0x0);

    /* 配置PS buffer */
    pxp_set_process_surface_buffer_config(&ps_buffer_config);

    pxp_set_process_surface_position(__APP_PS_ULC_X,
                                     __APP_PS_ULC_Y,
                                     __APP_PS_LRC_X,
                                     __APP_PS_LRC_Y);

    /* 禁能AS */
    pxp_set_alpha_surface_position(0xFFFF, 0xFFFF, 0, 0);

    /* Output config. */
    __g_output_buffer_config.pixel_format = kPXP_OutputPixelFormatRGB565;
    __g_output_buffer_config.interlaced_mode = kPXP_OutputProgressive;
    __g_output_buffer_config.buffer0_addr = (uint32_t)__gp_pxp_fb->v_addr;
    __g_output_buffer_config.buffer1_addr = 0;
    __g_output_buffer_config.pitch_bytes = __APP_IMG_WIDTH * __APP_BPP;
    __g_output_buffer_config.width  = __APP_IMG_WIDTH;
    __g_output_buffer_config.height = __APP_IMG_HEIGHT;

    pxp_set_output_buffer_config(&__g_output_buffer_config);

    /* Disable CSC1, it is enabled by default. */
    pxp_enable_csc1(0);
}


static void __app_rotate (void)
{
    int i = 0;
    uint8_t buf_index = 1U;
    uint8_t (*p_vddr)[__APP_IMG_WIDTH * __APP_IMG_HEIGHT * __APP_BPP] = NULL;

    const pxp_rotate_degree_t degrees[] = {
        kPXP_Rotate0, kPXP_Rotate90, kPXP_Rotate180, kPXP_Rotate270,
    };

    /* 显存地址 */
    p_vddr = (void *)__gp_pxp_fb->v_addr;

    while (1) {

        for (i = 0; i < AW_NELEMENTS(degrees); i++) {

            aw_cache_flush((void *)__gp_pxp_buf, __APP_PS_SIZE *  __APP_PS_SIZE * __APP_BPP);

            /* 旋转配置 */
            pxp_set_rotate_config(kPXP_RotateProcessSurface, degrees[i], kPXP_FlipDisable);

            /* 输出缓冲区设置 */
            __g_output_buffer_config.buffer0_addr = (uint32_t)p_vddr[buf_index];
            pxp_set_output_buffer_config(&__g_output_buffer_config);

            /* PXP开始处理 */
            pxp_start();

            /* 等待处理完成 */
            pxp_complete_status_sync();

            aw_cache_invalidate((void *)__gp_pxp_buf, __APP_PS_SIZE *  __APP_PS_SIZE * __APP_BPP);

            aw_cache_flush((void*)p_vddr[buf_index],
                           __gp_pxp_fb->x_res * __gp_pxp_fb->y_res * __APP_BPP);

            /* 旋转输出图像显示到LCD */
            aw_emwin_fb_vram_addr_set(__gp_pxp_fb, (uint32_t)p_vddr[buf_index]);

            /* 切换到另外一个显存 */
            buf_index ^= 1U;

            aw_mdelay(1000);
        }
    }
}


void demo_pxp_rotate (void){

    /* 初始化fram buffer */
    __fb_init();

    __gp_pxp_buf = (uint8_t *) aw_mem_align(__APP_PS_SIZE * __APP_PS_SIZE * __APP_BPP,
                                            AW_CACHE_LINE_SIZE);

    if(NULL == __gp_pxp_buf){
        aw_kprintf("__gp_pxp_buf error.\r\n");
        return ;
    }

    /* 初始化buffer */
    __rotate_buf_init();

    /* 配置pxp */
    __app_pxp_config();

    /* 缩放测试 */
    __app_rotate();

    aw_mem_free(__gp_pxp_buf);
}

/* end of file */
