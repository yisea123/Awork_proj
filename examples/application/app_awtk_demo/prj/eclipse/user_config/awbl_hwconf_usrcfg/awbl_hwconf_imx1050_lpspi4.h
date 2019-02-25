/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_HWCONF_IMX1050_LPSPI4_H
#define __AWBL_HWCONF_IMX1050_LPSPI4_H

#ifdef AW_DEV_IMX1050_LPSPI4

#include "aw_gpio.h"
#include "aw_clk.h"
#include "driver/lpspi/awbl_imx1050_lpspi.h"

/* ƽ̨��س�ʼ�� */
aw_local void __imx1050_lpspi4_plfm_init (void)
{
    int lpspi4_gpios[] = {
                          GPIO2_23,    //CLK
                          GPIO2_22,    //MOSI
                          GPIO2_21,    //MISO
                          //GPIO2_20,  //CS
                          };

    if (aw_gpio_pin_request("lpspi4_gpios",
                             lpspi4_gpios,
                             AW_NELEMENTS(lpspi4_gpios)) == AW_OK) {

        /* ���ù������� */
       // aw_gpio_pin_cfg(GPIO2_20, GPIO2_20_LPSPI4_PCS0);
        aw_gpio_pin_cfg(GPIO2_22, GPIO2_22_LPSPI4_SDO);
        aw_gpio_pin_cfg(GPIO2_21, GPIO2_21_LPSPI4_SDI);
        aw_gpio_pin_cfg(GPIO2_23, GPIO2_23_LPSPI4_SCK);
    }

    aw_clk_enable(IMX1050_CLK_CG_LPSPI4);
}


/* �豸��Ϣ */
aw_local aw_const struct awbl_imx1050_lpspi_devinfo __g_imx1050_lpspi4_devinfo = {
    {
        IMX1050_LPSPI4_BUSID,       /* ���߱�� */
    },
    IMX1050_LPSPI4_BASE,            /* LPSPI1�Ĵ�������ַ */
    INUM_LPSPI4,                    /* �жϱ�� */

    0,                              /**< \brief channel0 ~ channel3 */
    6,                              /**< \brief �����������ȼ� */
    DISABLE_DMA_TRANS,              /**< \brief ����DMA���� */
    50,                             /**< \brief ���һ��SCK�ź��ص�CSȡ��ѡ�е���ʱ */
    50,                             /**< \brief CSѡ�е���һ��SCK�źű��ص���ʱ */
    50,                             /**< \brief �������ʱ */

    IMX1050_CLK_CG_LPSPI4,            /**< \briefʱ�Ӻ� */
    __imx1050_lpspi4_plfm_init      /**< \briefƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_imx1050_lpspi_dev __g_imx1050_lpspi4_dev;

#define AWBL_HWCONF_IMX1050_LPSPI4                   \
    {                                                \
        AWBL_IMX1050_LPSPI_NAME,                     \
        0,                                           \
        AWBL_BUSID_PLB,                              \
        0,                                           \
        (struct awbl_dev *)&__g_imx1050_lpspi4_dev,  \
        &__g_imx1050_lpspi4_devinfo                  \
    },

#else
#define AWBL_HWCONF_IMX1050_LPSPI4

#endif /* AW_DEV_IMX1050_LPSPI4 */

#endif /* __AWBL_HWCONF_IMX1050_LPSPI4_H */

/* end of file */
