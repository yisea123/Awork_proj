/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

#ifndef AWBL_HWCONF_FM175XX_SPI_H
#define AWBL_HWCONF_FM175XX_SPI_H

#include "aw_gpio.h"
#include "aw_delay.h"
#include "driver/card_reader/awbl_fm175xx.h"
#include "imx1050_pin.h"

#ifdef AW_DEV_FM175XX_SPI3_0

/**
 * \addtogroup grp_aw_plfm_ext_fm175xx_usrcfg
 * @{
 */



/* 平台相关初始化 */
aw_local void __fm175xx_plfm_init (void)
{

    int fm175xx_gpios[] = {GPIO3_4};  /* NPD管脚 */

    aw_gpio_pin_request("fm175xx_gpios",
                         fm175xx_gpios,
                         AW_NELEMENTS(fm175xx_gpios));
}

/* FM175XX 设备信息 */
aw_local aw_const awbl_fm175xx_devinfo_t __g_fm175xx_dev0info = {
    0,
    AW_SPI_MODE_0,                     /* 接口时序模式 */
    GPIO1_28,                          /* NSS 管脚(CS) */
    2000000,                           /* SPI总线时钟 */
    GPIO3_4,                           /* NPD管脚 */
    __fm175xx_plfm_init
};

/* FM175XX 设备实例内存静态分配 */
aw_local awbl_fm175xx_dev_t __g_fm175xx_dev0;

#define AWBL_HWCONF_FM175XX_0                 \
    {                                         \
        AWBL_FM175XX_NAME,                    \
        0,                                    \
        AWBL_BUSID_SPI,                       \
        IMX1050_LPSPI3_BUSID,                 \
        &(__g_fm175xx_dev0.spi_dev.super),    \
        &__g_fm175xx_dev0info                 \
    },

/** @} */

#else
#define AWBL_HWCONF_FM175XX_0

#endif

#endif
