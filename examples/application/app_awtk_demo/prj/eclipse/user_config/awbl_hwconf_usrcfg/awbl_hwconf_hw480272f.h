/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_HWCONF_HW480272F_H
#define __AWBL_HWCONF_HW480272F_H

#ifdef AW_DEV_HW480272F

/*******************************************************************************
  HW480272 配置信息
*******************************************************************************/
#include "driver/display/awbl_imx1050_tft_panel.h"

#define __HW480272_X_RES        480
#define __HW480272_Y_RES        272
#define __HW480272_BPP          16
#define __HW480272_DCLK_F       12000000

#define DOTCLK_H_ACTIVE         __HW480272_X_RES
#define DOTCLK_H_PULSE_WIDTH    1
#define DOTCLK_HF_PORCH         8
#define DOTCLK_HB_PORCH         15
#define DOTCLK_H_WAIT_CNT       (DOTCLK_H_PULSE_WIDTH + (3 * DOTCLK_HB_PORCH))
#define DOTCLK_H_PERIOD         (DOTCLK_H_WAIT_CNT + DOTCLK_HF_PORCH + DOTCLK_H_ACTIVE)

#define DOTCLK_V_ACTIVE         __HW480272_Y_RES
#define DOTCLK_V_PULSE_WIDTH    1
#define DOTCLK_VF_PORCH         4
#define DOTCLK_VB_PORCH         12
#define DOTCLK_V_WAIT_CNT       (DOTCLK_V_PULSE_WIDTH + DOTCLK_VB_PORCH)
#define DOTCLK_V_PERIOD         (DOTCLK_VF_PORCH + DOTCLK_V_ACTIVE + DOTCLK_V_WAIT_CNT)


typedef struct __hw480272f_gpio_cfg {
    int         gpio;
    uint32_t    func;

} __hw480272f_gpio_cfg_t;


aw_local aw_const  __hw480272f_gpio_cfg_t __g_hw480272f_gpios_list[] = {

    {GPIO1_10, AW_GPIO_OUTPUT_INIT_HIGH_VAL},  /* 背光控制,当使用PWM时将这句注释掉 */
    {GPIO2_0,  GPIO2_0_LCD_CLK},         /* LCD clk */
    {GPIO2_1,  GPIO2_1_LCD_ENABLE},      /* LCD enable */
    {GPIO2_2,  GPIO2_2_LCD_HSYNC},       /* LCD hsync */
    {GPIO2_3,  GPIO2_3_LCD_VSYNC},       /* LCD vsync */

    {GPIO2_4,  GPIO2_4_LCD_DATA00},      /* LCD data0 */
    {GPIO2_5,  GPIO2_5_LCD_DATA01},      /* LCD data1 */
    {GPIO2_6,  GPIO2_6_LCD_DATA02},      /* LCD data2 */
    {GPIO2_7,  GPIO2_7_LCD_DATA03},      /* LCD data3 */
    {GPIO2_8,  GPIO2_8_LCD_DATA04},      /* LCD data4 */
    {GPIO2_9,  GPIO2_9_LCD_DATA05},      /* LCD data5 */
    {GPIO2_10, GPIO2_10_LCD_DATA06},     /* LCD data6 */
    {GPIO2_11, GPIO2_11_LCD_DATA07},     /* LCD data7 */
    {GPIO2_12, GPIO2_12_LCD_DATA08},     /* LCD data8 */
    {GPIO2_13, GPIO2_13_LCD_DATA09},     /* LCD data9 */
    {GPIO2_14, GPIO2_14_LCD_DATA10},     /* LCD data10 */
    {GPIO2_15, GPIO2_15_LCD_DATA11},     /* LCD data11 */
    {GPIO2_16, GPIO2_16_LCD_DATA12},     /* LCD data12 */
    {GPIO2_17, GPIO2_17_LCD_DATA13},     /* LCD data13 */
    {GPIO2_18, GPIO2_18_LCD_DATA14},     /* LCD data14 */
    {GPIO2_19, GPIO2_19_LCD_DATA15},     /* LCD data15 */
};

aw_local void __hw480272_plfm_init (void)
{
    int i = 0;
    int flexspi_gpios[AW_NELEMENTS(__g_hw480272f_gpios_list)];

    for (i = 0; i < AW_NELEMENTS(__g_hw480272f_gpios_list); i++) {
        flexspi_gpios[i] = __g_hw480272f_gpios_list[i].gpio;
    }

    if (aw_gpio_pin_request("flexspi_gpios",
                             flexspi_gpios,
                             AW_NELEMENTS(flexspi_gpios)) == AW_OK) {

        for (i = 0; i < AW_NELEMENTS(__g_hw480272f_gpios_list); i++) {
            /* 配置功能引脚 */
            aw_gpio_pin_cfg(__g_hw480272f_gpios_list[i].gpio,
                            __g_hw480272f_gpios_list[i].func);
        }
    }
}

/* 设备信息 */
aw_local aw_const awbl_imx1050_tft_panel_devinfo_t  __g_hw480272f_param = {
    /* panel_info */
    {
        __HW480272_X_RES,               /* x_res */
        __HW480272_Y_RES,               /* y_res */
        __HW480272_BPP,                 /* bpp */
        __HW480272_DCLK_F,              /* dclk_f */
        AWBL_MXS_LCDIF_PANEL_DOTCLK,    /* type */
        99,                             /* default back light intensity */
    },
    /* timing */
    {
        DOTCLK_V_PULSE_WIDTH,           /* v_pulse_width */
        DOTCLK_V_PERIOD,                /* v_period */
        DOTCLK_V_WAIT_CNT,              /* v_wait_cnt */
        DOTCLK_V_ACTIVE,                /* v_active */
        DOTCLK_H_PULSE_WIDTH,           /* h_pulse_width */
        DOTCLK_H_PERIOD,                /* h_period */
        DOTCLK_H_WAIT_CNT,              /* h_wait_cnt */
        DOTCLK_H_ACTIVE,                /* h_active */
        0,                              /* enable_present */
    },
    /* plfm_init */
    __hw480272_plfm_init
};

/* 设备实例内存静态分配 */
aw_local awbl_imx1050_tft_panel_t __g_hw480272f;

#define AWBL_HWCONF_HW480272F       \
    {                               \
        AWBL_IMX1050_TFT_PANEL_NAME,\
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        &(__g_hw480272f.dev),       \
        &(__g_hw480272f_param)      \
    },

#else
#define AWBL_HWCONF_HW480272F

#endif  /* AW_DEV_HW480272F */

#endif  /* __AWBL_HWCONF_HW480272F_H */

/* end of file */
