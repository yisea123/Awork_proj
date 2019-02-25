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

/**
 * \file
 * \brief AWBus-lite 硬件配置文件
 */

/*******************************************************************************
  headers
*******************************************************************************/

#undef  AW_IMG_PRJ_BUILD
#define AW_IMG_PRJ_BUILD


#include "aworks.h"
#include "awbus_lite.h"
#include "aw_gpio.h"
#include "aw_delay.h"
#include "aw_prj_params.h"
#include "aw_clk.h"
#include "aw_bitops.h"
#include "imx1050_inum.h"
#include "imx1050_reg_base.h"

#include "awbl_hwconf_imx1050_nvic.h"
#include "awbl_hwconf_imx1050_lpuart1.h"
#include "awbl_hwconf_imx1050_lpuart2.h"
#include "awbl_hwconf_imx1050_lpuart3.h"
#include "awbl_hwconf_imx1050_lpuart4.h"
#include "awbl_hwconf_imx1050_lpuart5.h"
#include "awbl_hwconf_imx1050_lpuart6.h"
#include "awbl_hwconf_imx1050_lpuart7.h"
#include "awbl_hwconf_imx1050_lpuart8.h"
#include "awbl_hwconf_imx1050_flexio2_uart0.h"
#include "awbl_hwconf_imx1050_gpio.h"
#include "awbl_hwconf_gpio_led.h"
#include "awbl_hwconf_gpio_key.h"
#include "awbl_hwconf_imx1050_flexspi.h"
#include "awbl_hwconf_imx1050_lpspi1.h"
#include "awbl_hwconf_imx1050_lpspi2.h"
#include "awbl_hwconf_imx1050_lpspi3.h"
#include "awbl_hwconf_imx1050_lpspi4.h"
#include "awbl_hwconf_imx1050_rtwdt.h"
#include "awbl_hwconf_imx1050_wdt1.h"
#include "awbl_hwconf_imx1050_gpt1.h"
#include "awbl_hwconf_imx1050_gpt2.h"
#include "awbl_hwconf_imx1050_pit.h"
#include "awbl_hwconf_imx1050_adc1.h"
#include "awbl_hwconf_imx1050_sdio_sd0.h"
#include "awbl_hwconf_imx1050_edma.h"
#include "awbl_hwconf_imx1050_sai1.h"
#include "awbl_hwconf_imx1050_sai3.h"
#include "awbl_hwconf_imx1050_mqs.h"
#include "awbl_hwconf_imx1050_lpi2c1.h"
#include "awbl_hwconf_imx1050_lpi2c2.h"
#include "awbl_hwconf_imx1050_ocotp.h"
#include "awbl_hwconf_imx1050_flexcan1.h"
#include "awbl_hwconf_imx1050_flexcan2.h"
#include "awbl_hwconf_imx1050_enet.h"
#include "awbl_hwconf_generic_phy.h"
#include "awbl_hwconf_imx1050_adc2.h"
#include "awbl_hwconf_hw480272f.h"
#include "awbl_hwconf_hwcap480272f.h"
#include "awbl_hwconf_emwin_fb.h"
#include "awbl_hwconf_imx1050_ts.h"
#include "awbl_hwconf_bu21029muv.h"
#include "awbl_hwconf_ft5x06.h"
#include "awbl_hwconf_imx1050_eflex_pwm4.h"
#include "awbl_hwconf_imx1050_qtimer3_pwm.h"
#include "awbl_hwconf_imx1050_qtimer3_cap.h"
#include "awbl_hwconf_buzzer_pwm.h"
#include "awbl_hwconf_gpio_i2c0.h"
#include "awbl_hwconf_pcf85063.h"
#include "awbl_hwconf_hw800480f.h"
#include "awbl_hwconf_spi_flash0.h"
#include "awbl_hwconf_imx1050_semc.h"
#include "awbl_hwconf_imx1050_nandflash_s34ml01g2.h"
#include "awbl_hwconf_imx1050_nandflash_s34ml02g2.h"
#include "awbl_hwconf_imx1050_nandflash_mx30lf1g08.h"
#include "awbl_hwconf_imx1050_usbh1.h"
#include "awbl_hwconf_fm175xx_spi.h"
#include "awbl_hwconf_imx1050_usbd.h"
#include "awbl_hwconf_imx1050_usbh2.h"
#include "awbl_hwconf_gpio_wdt.h"
#include "awbl_hwconf_imx1050_rtc.h"

#include "awbl_hwconf_imx1050_enc1.h"
#include "awbl_hwconf_imx1050_tempmon.h"
#include "awbl_hwconf_imx1050_acmp1.h"
#include "awbl_hwconf_cyw43362_wifi_spi.h"

#include "awbl_hwconf_sx127x.h"

#include "awbl_hwconf_imx1050_csi.h"
#include "awbl_hwconf_ov7725.h"

#include "awbl_hwconf_gprs_me909s.h"
#include "awbl_hwconf_gprs_sim800.h"
#include "awbl_hwconf_gprs_u9300c.h"
#include "awbl_hwconf_hw1280720f.h"
#include "awbl_hwconf_pcf85263.h"

/*******************************************************************************
  globals
*******************************************************************************/

/* 硬件设备列表 */
aw_const struct awbl_devhcf g_awbl_devhcf_list[] = {
    /* nvic */
    AWBL_HWCONF_IMX1050_NVIC

    /* GPIO */
    AWBL_HWCONF_IMX1050_GPIO

    /* LED */
    AWBL_HWCONF_GPIO_LED

    /* KEY */
    AWBL_HWCONF_GPIO_KEY

    /* FlexSPI */
    AWBL_HWCONF_IMX1050_FLEXSPI

    /* LPSPI1 */
    AWBL_HWCONF_IMX1050_LPSPI1

    /* LPSPI2 */
    AWBL_HWCONF_IMX1050_LPSPI2

    /* LPSPI3 */
    AWBL_HWCONF_IMX1050_LPSPI3

    /* LPSPI4 */
    AWBL_HWCONF_IMX1050_LPSPI4

    /* RTWDOG */
    AWBL_HWCONF_IMX1050_RTWDT

    /* WDOG1 */
    AWBL_HWCONF_IMX1050_WDT1

    /* GPT1 */
    AWBL_HWCONF_IMX1050_GPT1

    /* GPT2 */
    AWBL_HWCONF_IMX1050_GPT2

    /* PIT */
    AWBL_HWCONF_IMX1050_PIT

    /* ADC */
    AWBL_HWCONF_IMX1050_ADC1

    /* SDIO */
    AWBL_HWCONF_IMX1050_SDIO_SSP0

    /* eDMA */
    AWBL_HWCONF_IMX1050_EDMA

    /* lpuart1 */
    AWBL_HWCONF_IMX1050_LPUART1

    /* lpuart2 */
    AWBL_HWCONF_IMX1050_LPUART2

    /* lpuart3 */
    AWBL_HWCONF_IMX1050_LPUART3

    /* lpuart4 */
    AWBL_HWCONF_IMX1050_LPUART4

    /* lpuart5 */
    AWBL_HWCONF_IMX1050_LPUART5

    /* lpuart6 */
    AWBL_HWCONF_IMX1050_LPUART6

    /* lpuart7 */
    AWBL_HWCONF_IMX1050_LPUART7

    /* lpuart8 */
    AWBL_HWCONF_IMX1050_LPUART8

    /* SAI1 */
    AWBL_HWCONF_IMX1050_SAI1

    /* SAI3 */
    AWBL_HWCONF_IMX1050_SAI3

    /* MQS */
    AWBL_HWCONF_IMX1050_MQS

    /* LPI2C1 */
    AWBL_HWCONF_IMX1050_LPI2C1

    /* LPI2C2 */
    AWBL_HWCONF_IMX1050_LPI2C2

    /* OCOTP */
    AWBL_HWCONF_IMX1050_OCOTP
    /* CAN1 */
    AWBL_HWCONF_IMX1050_CAN1

    /* CAN2 */
    AWBL_HWCONF_IMX1050_CAN2

    /* ENET */
    AWBL_HWCONF_IMX1050_ENET

    /* PHY */
    AWBL_HWCONF_GENERIC_PHY0

    /* ADC2 */
    AWBL_HWCONF_IMX1050_ADC2

    /* 480 X 272 TFT屏 */
    AWBL_HWCONF_HW480272F
    AWBL_HWCONF_HWCAP480272F

    /* 800 X 400 7寸TFT屏 */
    AWBL_HWCONF_HW800480F

    /* emWin FB */
    AWBL_HWCONF_EMWIN_FB

    /* 触摸屏 */
    AWBL_HWCONF_IMX1050_TS

    /* i2c电阻触摸屏 */
    AWBL_HWCONF_BU21029MUV

    /* i2c电容触摸屏 */
    AWBL_HWCONF_FT5X06

    /* eFlexPWM4　*/
    AWBL_HWCONF_IMX1050_EFLEX_PWM4

    /* QTimer3 PWM */
    AWBL_HWCONF_IMX1050_QTIMER3_PWM

    /* PWM蜂鸣器 */
    AWBL_HWCONF_BUZZER_PWM

    /* GPIO I2C0 */
    AWBL_HWCONF_GPIO_I2C0

    /* PCF85063 */
    AWBL_HWCONF_PCF85063

    /* SPI_FLASH0 */
    AWBL_HWCONF_SPI_FLASH0

    /* SEMC */
    AWBL_HWCONF_IMX1050_SEMC

    /* NAND FLASH*/
    AWBL_HWCONF_IMX1050_NANDFLASH_S34ML01G2
    AWBL_HWCONF_IMX1050_NANDFLASH_S34ML02G2
    AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08

    /* FlexIO2 UART0 */
    AWBL_HWCONF_IMX1050_FLEXIO2_UART0

    /* USB HOST 1 */
    AWBL_HWCONF_IMX1050_USBH1

    /* USB HOST 2 */
    AWBL_HWCONF_IMX1050_USBH2

    /* Mifare卡 */
    AWBL_HWCONF_FM175XX_0

    /* USB device */
    AWBL_HWCONF_IMX1050_USBD

    /* GPIO看门狗 */
    AWBL_HWCONF_GPIO_WDT

    /* ENC */
    AWBL_HWCONF_IMX1050_ENC1

    /* Temperature Monitor */
    AWBL_HWCONF_IMX1050_TEMPMON

    /* Analog Comparator 1 */
    AWBL_HWCONF_IMX1050_ACMP1

    /* SPI WIFI */
    AWBL_HWCONF_CYW43362_WIFI_SPI

    /* LoRa sx127x */
    AWBL_HWCONF_SX127X

    /* CSI */
    AWBL_HWCONF_IMX1050_CSI

    /* OV7725 */
    AWBL_HWCONF_OV7725


    AWBL_HWCONF_GPRS_ME909S
    AWBL_HWCONF_GPRS_SIM800
    AWBL_HWCONF_GPRS_U9300C

    /* 1280 X 720 mipi屏 */
    AWBL_HWCONF_HW1280720F

    /* PCF85263 RTC */
    AWBL_HWCONF_PCF85263

    /* SNVS HP RTC */
    AWBL_HWCONF_IMX1050_RTC

    /* QTimer3 CAP */
    AWBL_HWCONF_IMX1050_QTIMER_CAP

};

/* 硬件设备列表成员个数 */
aw_const size_t g_awbl_devhcf_list_count = AW_NELEMENTS(g_awbl_devhcf_list);

/* end of file */
