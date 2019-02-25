/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief Freescale iMX RT1050 LCD控制器驱动
 *
 * \internal
 * \par modification history:
 * - 1.00  17-11-21  mex, first implementation.
 * \endinternal
 */

#ifndef __AWBL_IMX1050_LCDIF_H
#define __AWBL_IMX1050_LCDIF_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_spinlock.h"
#include "driver/intensity/awbl_pwm_it.h"
#include "driver/display/awbl_imx1050_lcdif_regs.h"
#include "aw_clk.h"
#include "aw_sem.h"

#define AWBL_MXS_LCDIF_PANEL_SYSTEM      0
#define AWBL_MXS_LCDIF_PANEL_VSYNC       1
#define AWBL_MXS_LCDIF_PANEL_DOTCLK      2
#define AWBL_MXS_LCDIF_PANEL_DVI         3


/** \brief 获取面板设备的名字和单元号 */
typedef aw_err_t (* awbl_imx1050_lcdif_obtain_panel_t) (const char **pp_name, int *p_unit);

/** \brief LCDIF设备信息 */
typedef struct awbl_imx1050_lcdif_devinfo {

    const char          *default_panel_name; /**< \brief 默认面板名 */
    int                  default_panel_unit; /**< \brief 默认面板单元号 */
    int                  default_pwm_num;    /**< \brief 默认背光控制的PWM号 */
    int                  gpio_backlight;     /**< \brief GPIO管脚背光控制 */

    /** \brief 决定使用哪个面板 (为NULL或失败时，使用默认面板) */
    aw_err_t           (*pfunc_decide_panel) (const char **pp_name, int *p_unit);
    uint32_t            regbase;             /**< \brief LCDIF寄存器基地址 */
    int                 inum;                /**< \brief LCD中断号 */
    const aw_clk_id_t  *dev_clks;            /**< \brief the clocks which the timer need */
    int                 dev_clk_count;       /**< \brief count of device clocks */
    aw_clk_id_t         ref_pixel_clk_id;    /**< \brief pixel clocks */

} awbl_imx1050_lcdif_devinfo_t;


struct awbl_imx1050_panel;

/** \brief LCDIF设备 */
typedef struct awbl_imx1050_lcdif {

    awbl_dev_t dev;                          /** \brief 继承自AWBus */
    awbl_imx1050_lcdif_devinfo_t *p_devinfo; /** \brief LCDIF 设备信息 */
    struct awbl_imx1050_panel    *p_panel;   /** \brief 使用的面板 */


    AW_SEMB_DECL(lcd_sem_sync);             /** \brief 用于帧同步的信号量 */

} awbl_imx1050_lcdif_t;

typedef struct awbl_imx1050_dotclk_timing {

    uint16_t               v_pulse_width;
    uint16_t               v_period;
    uint16_t               v_wait_cnt;
    uint16_t               v_active;
    uint16_t               h_pulse_width;
    uint16_t               h_period;
    uint16_t               h_wait_cnt;
    uint16_t               h_active;
    int                    enable_present;

} awbl_imx1050_dotclk_timing_t;

/** \brief panel information */
typedef struct awbl_imx1050_panel_info {

    uint16_t x_res;
    uint16_t y_res;
    uint16_t bpp;
    uint32_t dclk_f;
    int      lcd_type;
    int      bl_percent;

} awbl_imx1050_panel_info_t;


struct awbl_imx1050_panel;

/** \brief panel information */
typedef struct awbl_imx1050_panel_ops {

    aw_err_t (*init_panel)(struct awbl_imx1050_panel *p_panel, uint32_t phys, size_t memsize);
    void     (*release_panel) (struct awbl_imx1050_panel *p_panel);
    aw_err_t (*blank_panel) (struct awbl_imx1050_panel *p_panel, int blank);
    aw_err_t (*run_panel) (struct awbl_imx1050_panel *p_panel);
    aw_err_t (*stop_panel) (struct awbl_imx1050_panel *p_panel);
    aw_err_t (*pan_vram_addr_set) (struct awbl_imx1050_panel *p_panel, uint32_t fb_addr);
    aw_err_t (*update_panel) (struct awbl_imx1050_panel *p_panel, void *);
    aw_err_t (*pan_backlight) (struct awbl_imx1050_panel *p_panel, int pwm_num, int percent);

} awbl_imx1050_panel_ops_t;

typedef struct awbl_imx1050_panel {

    awbl_imx1050_lcdif_t            *p_lcdif;
    awbl_imx1050_panel_info_t       *p_panel_info;
    const awbl_imx1050_panel_ops_t  *p_ops;
    void                            *p_cookie;

} awbl_imx1050_panel_t;


aw_err_t awbl_imx1050_lcdif_init(awbl_imx1050_lcdif_t *p_lcdif, uint8_t bpp);
aw_err_t awbl_imx1050_lcdif_run(awbl_imx1050_lcdif_t *p_lcdif);
aw_err_t awbl_imx1050_lcdif_stop(awbl_imx1050_lcdif_t *p_lcdif);
aw_err_t awbl_imx1050_lcdif_pan_vram_addr_set(awbl_imx1050_lcdif_t *p_lcdif, uint32_t addr);
aw_err_t awbl_imx1050_lcdif_pan_blank(awbl_imx1050_lcdif_t *p_lcdif, int blank);

aw_err_t awbl_imx1050_lcdif_dma_init(awbl_imx1050_lcdif_t *p_lcdif, uint32_t phys, size_t memsize);
aw_err_t awbl_imx1050_lcdif_dma_release(awbl_imx1050_lcdif_t *p_lcdif);

aw_err_t awbl_imx1050_lcdif_setup_dotclk_panel (awbl_imx1050_lcdif_t *p_lcdif, awbl_imx1050_dotclk_timing_t *p_timing);
aw_err_t awbl_imx1050_lcdif_release_dotclk_panel (awbl_imx1050_lcdif_t *p_lcdif);

aw_err_t __imx_lcdif_isr(void *p_dev);
#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_IMX1050_LCDIF_H */

/* end of file */

