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
  IMX1050 FlexIO ģ�� UART ������Ϣ
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

/** \brief �豸��Ϣ */
aw_local aw_const
awbl_imx1050_flexio_uart_dev_info_t __g_imx1050_flexio2_uart0_devinfo = {
    INUM_FLEXIO2,                    /**< \brief �жϺ� */
    IMX1050_FLEXIO2_BASE,            /**< \brief �Ĵ�������ַ */
    IMX1050_CLK_FLEXIO2_CLK_ROOT,    /**< \brief ����ʱ�� ID */
    FALSE,                           /**< \brief ʧ��doze */
    TRUE,                            /**< \brief ʹ��debug */
    FALSE,                           /**< \brief ʧ��fast access */
    GPIO2_28,                        /**< \brief TX ���ź� */
    GPIO2_29,                        /**< \brief RX ���ź� */
    {0, 1},                          /**< \brief Shifter �� */
    {0, 1},                          /**< \brief Timer �� */
    __imx1050_flexio2_uart0_plat_init  /**< \brief ƽ̨��ʼ������ */
};

/** \brief �豸ʵ���ڴ澲̬���� */
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
