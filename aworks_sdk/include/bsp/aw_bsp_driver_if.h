/*******************************************************************************
*                                 AWorks
*                       ----------------------------
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
 * \brief AWBus driver register and initializing interfaces.
 *
 * \internal
 * \par modification history
 * - 1.00 13-03-07  orz, first implementation.
 * \endinternal
 */
 
#ifndef __AW_BSP_DRIVER_IF_H
#define __AW_BSP_DRIVER_IF_H

#include "aw_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup aw_bsp_driver_if
 * @{
 */
 
aw_export void awbl_imx1050_gpio_drv_register (void);
aw_export void awbl_imx1050_gpt_drv_register (void);
aw_export void awbl_imx1050_pit_drv_register (void);
aw_export void awbl_imx1050_lpuart_drv_register (void);
aw_export void awbl_led_gpio_drv_register (void);
aw_export void awbl_imx1050_enet_drv_register (void);
aw_export void awbl_imx1050_flexspi_drv_register (void);
aw_export void awbl_imx1050_lpspi_drv_register (void);
aw_export void awbl_imx1050_wdt_drv_register (void);
aw_export void awbl_imx1050_rtwdt_drv_register (void);
aw_export void awbl_imx1050_adc_drv_register (void);
aw_export void awbl_imx1050_sdio_drv_register (void);
aw_export void awbl_imx1050_edma_drv_register (void);
aw_export void awbl_imx1050_sai_drv_register (void);
aw_export void awbl_imx1050_mqs_drv_register (void);
aw_export void awbl_imx1050_lpi2c_drv_register (void);
aw_export void awbl_imx1050_flexcan_drv_register (void);
aw_export void awbl_imx1050_tft_panel_drv_register (void);
aw_export void awbl_imx1050_emwin_fb_drv_register (void);
aw_export void awbl_bu21029muv_drv_register (void);
aw_export void awbl_imx1050_touch_screen_drv_register (void);
aw_export void awbl_imx1050_eflex_pwm_drv_register (void);
aw_export void awbl_imx1050_qtimer_pwm_drv_register (void);
aw_export void awbl_imx1050_semc_drv_register (void);
aw_export void awbl_imx1050_nand_drv_register (void);
aw_export void awbl_imx1050_usbh_drv_register (void);
aw_export void awbl_imx1050_edma_init (void);
aw_export void awbl_imx1050_rtc_drv_register (void);
aw_export void awbl_imx1050_rtc_drv_register (void);
aw_export void awbl_imx1050_pxp_init(void);
/** @} */

 
 
 
#ifdef __cplusplus
}
#endif

#endif /* __AW_BSP_DRIVER_IF_H */

/* end of file */