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

static uint8_t  *__gp_ps_buf;
static uint8_t  *__gp_as_buf;

/* PXP Output buffer config. */
static pxp_output_buffer_config_t __g_output_buffer_config;


/* 定义屏幕的高度和宽度 */
#define __APP_IMG_HEIGHT  272
#define __APP_IMG_WIDTH   480
#define __APP_BPP         2

#define __APP_PS_WIDTH    (__APP_IMG_WIDTH  / 2)
#define __APP_PS_HEIGHT   (__APP_IMG_HEIGHT / 2)

#define __APP_AS_WIDTH    (__APP_IMG_WIDTH  / 2)
#define __APP_AS_HEIGHT   (__APP_IMG_HEIGHT / 2)


#define __APP_PS_ULC_X    ((__APP_IMG_WIDTH  / 2) - (__APP_PS_SIZE / 2))
#define __APP_PS_ULC_Y    ((__APP_IMG_HEIGHT / 2) - (__APP_PS_SIZE / 2))
#define __APP_PS_LRC_X    ((__APP_IMG_WIDTH  / 2) + (__APP_PS_SIZE / 2) - 1)

static void __fb_init (void)
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


static void __as_ps_buf_init (void)
{
    uint32_t i, j;
    uint16_t *ps_buf = (uint16_t *)__gp_ps_buf;
    uint16_t *as_buf = (uint16_t *)__gp_as_buf;

    /* The PS buffer is BLUE rectangle, the AS buffer is YELLOW rectangle. */
    for (i = 0; i < __APP_PS_HEIGHT; i++) {
        for (j = 0; j < __APP_PS_WIDTH; j++) {
            ps_buf[i * __APP_PS_WIDTH +  j] = 0xFF;
        }
    }

    for (i = 0; i < __APP_AS_HEIGHT; i++) {
        for (j = 0; j < __APP_AS_WIDTH; j++) {
            as_buf[i * __APP_AS_WIDTH +  j] = 0xFF00;
        }
    }

}


static void __app_pxp_config(void)
{
    /* PS configure. */
    const pxp_ps_buffer_config_t ps_buffer_config = {
        .pixel_format = kPXP_PsPixelFormatRGB565,
        .swap_byte   = 0,
        .buffer_addr  = (uint32_t)__gp_ps_buf,
        .buffer_addr_u = 0,
        .buffer_addr_v = 0,
        .pitch_bytes = __APP_PS_WIDTH * __APP_BPP,
    };

    /* 复位PXP */
    pxp_hard_reset();

    /* 设置PS背景颜色 */
    pxp_set_process_surface_back_ground_color(0x00);

    /* 配置PS buffer */
    pxp_set_process_surface_buffer_config(&ps_buffer_config);

    /* AS config. */
    const pxp_as_buffer_config_t as_buffer_config = {
        .pixel_format = kPXP_AsPixelFormatRGB565,
        .buffer_addr  = (uint32_t)__gp_as_buf,
        .pitch_bytes  = __APP_AS_WIDTH * __APP_BPP,
    };

    pxp_set_alpha_surface_buffer_config(&as_buffer_config);

    const pxp_as_blend_config_t as_blend_config = {
        .alpha = 0,
        .invert_alpha = 0,
        .alpha_mode = kPXP_AlphaRop,
        .rop_mode = kPXP_RopMergeAs
    };
    pxp_set_alpha_surface_blend_config(&as_blend_config);

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



static void __app_blend (void)
{
    uint8_t buf_index = 1U;
    uint8_t (*p_vddr)[__APP_IMG_WIDTH * __APP_IMG_HEIGHT * __APP_BPP] = NULL;

    int8_t ps_inc_x = 1;
    int8_t ps_inc_y = 1;
    int8_t as_inc_x = -1;
    int8_t as_inc_y = -1;
    uint16_t ps_ulc_x = 0U;
    uint16_t ps_ulc_y = 0U;
    uint16_t as_ulc_x = __APP_IMG_WIDTH - __APP_AS_WIDTH;
    uint16_t as_ulc_y = __APP_IMG_HEIGHT - __APP_AS_HEIGHT;
    uint16_t ps_lrc_x, ps_lrc_y, as_lrc_x, as_lrc_y;

    ps_lrc_x = ps_ulc_x + __APP_PS_WIDTH - 1U;
    ps_lrc_y = ps_ulc_y + __APP_PS_HEIGHT - 1U;
    as_lrc_x = as_ulc_x + __APP_AS_WIDTH - 1U;
    as_lrc_y = as_ulc_y + __APP_AS_HEIGHT - 1U;

    p_vddr = (void *)__gp_pxp_fb->v_addr;

    while (1) {

        aw_cache_flush((void *)__gp_ps_buf, __APP_PS_HEIGHT *  __APP_PS_WIDTH * __APP_BPP);
        aw_cache_flush((void *)__gp_as_buf, __APP_AS_HEIGHT *  __APP_AS_WIDTH * __APP_BPP);

        pxp_set_process_surface_position(ps_ulc_x, ps_ulc_y, ps_lrc_x, ps_lrc_y);

        pxp_set_alpha_surface_position(as_ulc_x, as_ulc_y, as_lrc_x, as_lrc_y);

        __g_output_buffer_config.buffer0_addr = (uint32_t)p_vddr[buf_index];

        pxp_set_output_buffer_config(&__g_output_buffer_config);

        /* Start PXP. */
        pxp_start();

        /* Wait for process complete. */
        pxp_complete_status_sync();

        aw_cache_invalidate((void *)__gp_ps_buf, __APP_PS_HEIGHT *  __APP_PS_WIDTH * __APP_BPP);
        aw_cache_invalidate((void *)__gp_as_buf, __APP_AS_HEIGHT *  __APP_AS_WIDTH * __APP_BPP);

        aw_cache_flush((void*)p_vddr[buf_index],
                       __gp_pxp_fb->x_res * __gp_pxp_fb->y_res * __APP_BPP);

        /* Now new frame is ready, pass it to LCDIF. */
        aw_emwin_fb_vram_addr_set(__gp_pxp_fb, (uint32_t)p_vddr[buf_index]);

        /* Switch to the other LCD buffer. */
        buf_index ^= 1U;

        ps_lrc_x += ps_inc_x;
        ps_lrc_y += ps_inc_y;
        as_lrc_x += as_inc_x;
        as_lrc_y += as_inc_y;

        ps_ulc_x += ps_inc_x;
        ps_ulc_y += ps_inc_y;
        as_ulc_x += as_inc_x;
        as_ulc_y += as_inc_y;

        if (0 == as_ulc_x) {
            as_inc_x = 1;
        } else if (__APP_IMG_WIDTH - 1 == as_lrc_x) {
            as_inc_x = -1;
        }

        if (0 == as_ulc_y) {
            as_inc_y = 1;
        } else if (__APP_IMG_HEIGHT - 1 == as_lrc_y) {
            as_inc_y = -1;
        }

        if (0 == ps_ulc_x) {
            ps_inc_x = 1;
        } else if (__APP_IMG_WIDTH - 1 == ps_lrc_x) {
            ps_inc_x = -1;
        }

        if (0 == ps_ulc_y) {
            ps_inc_y = 1;
        } else if (__APP_IMG_HEIGHT - 1 == ps_lrc_y) {
            ps_inc_y = -1;
        }
        aw_mdelay(50);
    }
}


void demo_pxp_blend (void){

    /* 初始化fram buffer */
    __fb_init();

    __gp_ps_buf = (uint8_t *) aw_mem_align(__APP_PS_WIDTH * __APP_PS_HEIGHT * __APP_BPP,
                                           AW_CACHE_LINE_SIZE);
    __gp_as_buf = (uint8_t *) aw_mem_align(__APP_AS_WIDTH * __APP_AS_HEIGHT * __APP_BPP,
                                           AW_CACHE_LINE_SIZE);
    if(NULL == __gp_ps_buf || __gp_as_buf == NULL){
        aw_kprintf("aw_mem_align error.\r\n");
        return ;
    }

    /* 初始化buffer */
    __as_ps_buf_init();

    /* 配置pxp */
    __app_pxp_config();

    /* blend测试 */
    __app_blend();

    aw_mem_free(__gp_ps_buf);
    aw_mem_free(__gp_as_buf);
}

/* end of file */

