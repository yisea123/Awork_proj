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

/* 定义缩放的图像缓存 */
static uint8_t  *__gp_pxp_buf;

/* PXP Output buffer config. */
static pxp_output_buffer_config_t __g_output_buffer_config;

/* 定义屏幕的高度和宽度 */
#define __APP_IMG_HEIGHT  272
#define __APP_IMG_WIDTH   480
#define __APP_BPP         2


#if __APP_IMG_WIDTH > __APP_IMG_HEIGHT
#define __APP_PS_SIZE (__APP_IMG_HEIGHT / 2U)
#else
#define __APP_PS_SIZE (__APP_IMG_WIDTH / 2U)
#endif


#define __APP_PS_ULC_X     0
#define __APP_PS_ULC_Y     0


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


static void __scale_buf_init()
{
    uint32_t i, j;
    uint16_t *pxp_buf = (uint16_t *)__gp_pxp_buf;
    /*
     * The PS input buffer is:
     *
     *  -----------------------------
     *  |             |             |
     *  |             |             |
     *  |   BLUE      |   GREEN     |
     *  |             |             |
     *  |             |             |
     *  |-------------+-------------|
     *  |             |             |
     *  |             |             |
     *  |   WHITE     |    RED      |
     *  |             |             |
     *  |             |             |
     *  -----------------------------
     */
    for (i = 0; i < (__APP_PS_SIZE / 2); i++) {

        for (j = 0; j < (__APP_PS_SIZE / 2); j++) {
            pxp_buf[i * __APP_PS_SIZE  +  j] = 0x1F;
        }

        for (; j < __APP_PS_SIZE; j++) {
            pxp_buf[i * __APP_PS_SIZE  +  j] = 0x7E0;
        }
    }

    for (; i < __APP_PS_SIZE; i++) {

        for (j = 0; j < (__APP_PS_SIZE / 2); j++) {
            pxp_buf[i * __APP_PS_SIZE  +  j] = 0xFFFF;
        }

        for (; j < __APP_PS_SIZE; j++) {
            pxp_buf[i * __APP_PS_SIZE  +  j] = 0xF800;
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


static void __app_scale (void)
{
    uint8_t buf_index = 1U;
    uint8_t (*p_vddr)[__APP_IMG_WIDTH * __APP_IMG_HEIGHT * __APP_BPP] = NULL;

    float scale_start = 0.5f;
    float scale_end   = 4.0f;
    float scale_step  = 1.01f;
    float scale_fact;
    uint16_t width, height;

    /* 显存地址 */
    p_vddr = (void *)__gp_pxp_fb->v_addr;

    while (1) {

        for (scale_fact  = scale_start;
             scale_fact <= scale_end;
             scale_fact *= scale_step) {

            width = (uint16_t)((float)__APP_PS_SIZE / scale_fact);
            height = (uint16_t)((float)__APP_PS_SIZE / scale_fact);

            aw_cache_flush((void *)__gp_pxp_buf, __APP_PS_SIZE *  __APP_PS_SIZE * __APP_BPP);

            /* 缩放的图形配置 */
            pxp_set_process_surface_scaler(__APP_PS_SIZE, __APP_PS_SIZE, width, height);

            pxp_set_process_surface_position(__APP_PS_ULC_X,
                                             __APP_PS_ULC_Y,
                                             __APP_PS_ULC_X + width - 1U,
                                             __APP_PS_ULC_Y + height - 1U);

            __g_output_buffer_config.buffer0_addr = (uint32_t)p_vddr[buf_index];
            pxp_set_output_buffer_config(&__g_output_buffer_config);

            pxp_start();

            /* Wait for process complete. */
            pxp_complete_status_sync();

            aw_cache_invalidate((void *)__gp_pxp_buf, __APP_PS_SIZE *  __APP_PS_SIZE * __APP_BPP);

            aw_cache_flush((void*)p_vddr[buf_index],
                           __gp_pxp_fb->x_res * __gp_pxp_fb->y_res * __APP_BPP);

            /* Now new frame is ready, pass it to LCDIF. */
            aw_emwin_fb_vram_addr_set(__gp_pxp_fb, (uint32_t)p_vddr[buf_index]);

            /* Switch to the other LCD buffer. */
            buf_index ^= 1U;

            aw_mdelay(10);
        }

    }
}


void demo_pxp_scale (void){


    /* 初始化fram buffer */
    __fb_init();

    __gp_pxp_buf = (uint8_t *) aw_mem_align(__APP_PS_SIZE * __APP_PS_SIZE * __APP_BPP,
                                            AW_CACHE_LINE_SIZE);

    if(NULL == __gp_pxp_buf){
        aw_kprintf("__gp_pxp_buf error.\r\n");
        return ;
    }

    /* 初始化buffer */
    __scale_buf_init();

    /* 配置pxp */
    __app_pxp_config();

    /* 缩放测试 */
    __app_scale();

    aw_mem_free(__gp_pxp_buf);
}
/* end of file */
