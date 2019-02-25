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

#ifndef __AWBL_HWCONF_HW800480F_H
#define __AWBL_HWCONF_HW800480F_H

#ifdef AW_DEV_HW800480F
/*******************************************************************************
  HW800480 ������Ϣ
*******************************************************************************/
#include "driver/display/awbl_imx1050_tft_panel.h"

#define __AP_TFT7_0_V1_00  0
#define __AP_TFT7_0_V1_01  1

#define __TFT_VERSION   __AP_TFT7_0_V1_01

#define __HW800480_X_RES        800
#define __HW800480_Y_RES        480
#define __HW800480_BPP          16
#if __TFT_VERSION == __AP_TFT7_0_V1_00
#define __HW800480_DCLK_F       30000000
#endif

#if __TFT_VERSION == __AP_TFT7_0_V1_01
#define __HW800480_DCLK_F       24000000
#endif

#define DOTCLK_H_ACTIVE         __HW800480_X_RES
#if __TFT_VERSION == __AP_TFT7_0_V1_00
#define DOTCLK_H_PULSE_WIDTH    48
#define DOTCLK_HF_PORCH         200
#define DOTCLK_HB_PORCH         40
#endif
#if __TFT_VERSION == __AP_TFT7_0_V1_01
#define DOTCLK_H_PULSE_WIDTH    1
#define DOTCLK_HF_PORCH         210
#define DOTCLK_HB_PORCH         46
#endif
#define DOTCLK_H_WAIT_CNT       (DOTCLK_H_PULSE_WIDTH + DOTCLK_HB_PORCH)
#define DOTCLK_H_PERIOD         (DOTCLK_H_WAIT_CNT + DOTCLK_HF_PORCH + DOTCLK_H_ACTIVE)

#define DOTCLK_V_ACTIVE         __HW800480_Y_RES
#if __TFT_VERSION == __AP_TFT7_0_V1_00
#define DOTCLK_V_PULSE_WIDTH    3
#define DOTCLK_VF_PORCH         13
#define DOTCLK_VB_PORCH         29
#endif
#if __TFT_VERSION == __AP_TFT7_0_V1_01
#define DOTCLK_V_PULSE_WIDTH    1
#define DOTCLK_VF_PORCH         22
#define DOTCLK_VB_PORCH         23
#endif
#define DOTCLK_V_WAIT_CNT       (DOTCLK_V_PULSE_WIDTH + DOTCLK_VB_PORCH)
#define DOTCLK_V_PERIOD         (DOTCLK_VF_PORCH + DOTCLK_V_ACTIVE + DOTCLK_V_WAIT_CNT)

typedef struct __hw800400f_gpio_cfg {
    int         gpio;
    uint32_t    func;

} __hw800400f_gpio_cfg_t;


aw_local aw_const  __hw800400f_gpio_cfg_t __g_hw800400f_gpios_list[] = {

    {GPIO1_10, AW_GPIO_OUTPUT_INIT_HIGH_VAL},  /* �������,��ʹ��PWMʱ�����ע�͵� */
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

aw_local void __hw800400_plfm_init (void)
{
    int i = 0;
    int flexspi_gpios[AW_NELEMENTS(__g_hw800400f_gpios_list)];

    for (i = 0; i < AW_NELEMENTS(__g_hw800400f_gpios_list); i++) {
        flexspi_gpios[i] = __g_hw800400f_gpios_list[i].gpio;
    }

    if (aw_gpio_pin_request("flexspi_gpios",
                             flexspi_gpios,
                             AW_NELEMENTS(flexspi_gpios)) == AW_OK) {

        for (i = 0; i < AW_NELEMENTS(__g_hw800400f_gpios_list); i++) {
            /* ���ù������� */
            aw_gpio_pin_cfg(__g_hw800400f_gpios_list[i].gpio,
                            __g_hw800400f_gpios_list[i].func);
        }
    }
}

/* �豸��Ϣ */
aw_local aw_const awbl_imx1050_tft_panel_devinfo_t  __g_hw800400f_param = {
    /* panel_info */
    {
        __HW800480_X_RES,               /* x_res */
        __HW800480_Y_RES,               /* y_res */
        __HW800480_BPP,                 /* bpp */
        __HW800480_DCLK_F,              /* dclk_f */
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
    __hw800400_plfm_init
};

/* �豸ʵ���ڴ澲̬���� */
aw_local awbl_imx1050_tft_panel_t __g_hw800400f;

#define AWBL_HWCONF_HW800480F       \
    {                               \
        AWBL_IMX1050_TFT_PANEL_NAME,\
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        &(__g_hw800400f.dev),       \
        &(__g_hw800400f_param)      \
    },

#else
#define AWBL_HWCONF_HW800480F

#endif  /* AWBL_HWCONF_HW800480F */

#endif  /* __AWBL_HWCONF_HW800480F_H */

/* end of file */
