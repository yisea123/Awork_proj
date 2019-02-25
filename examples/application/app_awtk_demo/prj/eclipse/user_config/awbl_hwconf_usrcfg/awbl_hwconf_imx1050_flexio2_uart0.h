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

/*******************************************************************************
  IMX1050 FlexIO 模拟 UART 配置信息
*******************************************************************************/

#ifndef __AWBL_HWCONF_IMX1050_FLEXIO2_UART00_H
#define __AWBL_HWCONF_IMX1050_FLEXIO2_UART00_H

#include "driver/flexio/awbl_imx1050_flexio_uart.h"
#include "imx1050_pin.h"

#ifdef AW_DEV_IMX1050_FLEXIO2_UART0

aw_local void __imx1050_flexio2_uart0_plat_init (void)
{
    aw_clk_enable(IMX1050_CLK_FLEXIO2_CLK_ROOT);

    int flexio2_uart0_gpios[] = {GPIO2_28, GPIO2_29};

    if (aw_gpio_pin_request("flexio2_uart0_gpios",
                             flexio2_uart0_gpios,
                             AW_NELEMENTS(flexio2_uart0_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(GPIO2_28, GPIO2_28_FLEXIO2_FLEXIO28); /* TX */
        aw_gpio_pin_cfg(GPIO2_29, GPIO2_29_FLEXIO2_FLEXIO29); /* RX */
    }
}

/** \brief 设备信息 */
aw_local aw_const
awbl_imx1050_flexio_uart_dev_info_t __g_imx1050_flexio2_uart0_devinfo = {
    INUM_FLEXIO2,                    /**< \brief 中断号 */
    IMX1050_FLEXIO2_BASE,            /**< \brief 寄存器基地址 */
    IMX1050_CLK_FLEXIO2_CLK_ROOT,    /**< \brief 输入时钟 ID */
    FALSE,                           /**< \brief 失能doze */
    TRUE,                            /**< \brief 使能debug */
    FALSE,                           /**< \brief 失能fast access */
    GPIO2_28,                        /**< \brief TX 引脚号 */
    GPIO2_29,                        /**< \brief RX 引脚号 */
    {0, 1},                          /**< \brief Shifter 号 */
    {0, 1},                          /**< \brief Timer 号 */
    __imx1050_flexio2_uart0_plat_init  /**< \brief 平台初始化函数 */
};

/** \brief 设备实例内存静态分配 */
aw_local struct awbl_imx1050_flexio_uart_dev __g_imx1050_flexio2_uart0_dev;

#define AWBL_HWCONF_IMX1050_FLEXIO2_UART0     \
    {                                       \
        AWBL_IMX1050_FLEXIO_UART_DRV_NAME,  \
        IMX1050_FLEXIO2_UART0_COMID,         \
        AWBL_BUSID_PLB,                     \
        0,                                  \
        &__g_imx1050_flexio2_uart0_dev.dev,   \
        &__g_imx1050_flexio2_uart0_devinfo    \
    },
#else
#define AWBL_HWCONF_IMX1050_FLEXIO2_UART0
#endif

#endif /* __AWBL_HWCONF_IMX1050_FLEXIO2_UART00_H */

/* end of file */
