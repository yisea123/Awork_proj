/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  IMX1050 ����UART  ������Ϣ
*******************************************************************************/

#ifndef AWBL_HWCONF_IMX1050_LPUART1_H_
#define AWBL_HWCONF_IMX1050_LPUART1_H_

#include "driver/serial/awbl_imx1050_lpuart.h"
#include "imx1050_pin.h"

#ifdef AW_DEV_IMX1050_LPUART1

aw_local void __imx1050_lpuart1_plat_init (void)
{
    aw_clk_enable(IMX1050_CLK_CG_LPUART1);

    int lpuart1_gpios[] = {GPIO1_12, GPIO1_13};

    if (aw_gpio_pin_request("lpuart1_gpios",
                             lpuart1_gpios,
                             AW_NELEMENTS(lpuart1_gpios)) == AW_OK) {
    }
    aw_gpio_pin_cfg(GPIO1_12, GPIO1_12_LPUART1_TX);
    aw_gpio_pin_cfg(GPIO1_13, GPIO1_13_LPUART1_RX);
}

//aw_local void __imx1050_lpuart1_rs485_dir (uint8_t dir)
//{
//    //aw_gpio_set(GPIO17, dir);
//}

/* imx1050 lpuart1 �豸��Ϣ */
aw_local awbl_imx1050_lpuart_dev_info_t aw_const __g_imx1050_lpuart1_devinfo = {
    INUM_LPUART1,                // irq
    IMX1050_LPUART1_BASE,        // �Ĵ�������ַ
    IMX1050_CLK_CG_LPUART1,        // ����ʱ��id
    115200,
    __imx1050_lpuart1_plat_init, // ƽ̨��ʼ������
    NULL                         // RS485������ƺ���

};

/* imx1050�ڲ�UART�豸ʵ���ڴ澲̬���� */
aw_local struct awbl_imx1050_uart_dev __g_imx1050_lpuart1_dev;

#define AWBL_HWCONF_IMX1050_LPUART1     \
    {                                   \
        AWBL_IMX1050_LPUART_DRV_NAME,   \
        IMX1050_LPUART1_COMID,          \
        AWBL_BUSID_PLB,                 \
        0,                              \
        &__g_imx1050_lpuart1_dev.dev,   \
        &__g_imx1050_lpuart1_devinfo    \
    },
#else
#define AWBL_HWCONF_IMX1050_LPUART1
#endif

#endif /* AWBL_HWCONF_IMX1050_LPUART1_H_ */
