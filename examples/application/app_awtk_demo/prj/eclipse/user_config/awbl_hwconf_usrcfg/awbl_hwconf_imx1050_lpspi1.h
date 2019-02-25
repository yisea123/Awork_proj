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

#ifndef __AWBL_HWCONF_IMX1050_LPSPI1_H
#define __AWBL_HWCONF_IMX1050_LPSPI1_H


#ifdef AW_DEV_IMX1050_LPSPI1

#include "aw_gpio.h"
#include "aw_clk.h"
#include "driver/lpspi/awbl_imx1050_lpspi.h"


/* ƽ̨��س�ʼ�� */
aw_local void __imx1050_lpspi1_plfm_init (void)
{
    int lpspi1_gpios[] = {
                          GPIO3_12,  //CLK
                          GPIO3_14,  //MOSI
                          GPIO3_15,  //MISO
                         // GPIO3_13,  //CS
                          };

    if (aw_gpio_pin_request("lpspi1_gpios",
                             lpspi1_gpios,
                             AW_NELEMENTS(lpspi1_gpios)) == AW_OK) {

        /* ���ù������� */
        //aw_gpio_pin_cfg(GPIO3_13, GPIO3_13_LPSPI1_PCS0);
        aw_gpio_pin_cfg(GPIO3_14, GPIO3_14_LPSPI1_SDO);
        aw_gpio_pin_cfg(GPIO3_15, GPIO3_15_LPSPI1_SDI);
        aw_gpio_pin_cfg(GPIO3_12, GPIO3_12_LPSPI1_SCK);
    }
    aw_clk_enable(IMX1050_CLK_CG_LPSPI1);
}


/* �豸��Ϣ */
aw_local aw_const struct awbl_imx1050_lpspi_devinfo __g_imx1050_lpspi1_devinfo = {
    {
        IMX1050_LPSPI1_BUSID,       /* ���߱�� */
    },
    IMX1050_LPSPI1_BASE,            /* LPSPI1�Ĵ�������ַ */
    INUM_LPSPI1,                    /* �жϱ�� */

    0,                              /**< \brief channel0 ~ channel3 */
    6,                              /**< \brief �����������ȼ� */
    DISABLE_DMA_TRANS,              /**< \brief ����DMA���� */
    50,                             /**< \brief ���һ��SCK�ź��ص�CSȡ��ѡ�е���ʱ */
    50,                             /**< \brief CSѡ�е���һ��SCK�źű��ص���ʱ */
    50,                             /**< \brief �������ʱ */

    IMX1050_CLK_CG_LPSPI1,            /**< \briefʱ�Ӻ� */
    __imx1050_lpspi1_plfm_init      /**< \briefƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_imx1050_lpspi_dev __g_imx1050_lpspi1_dev;

#define AWBL_HWCONF_IMX1050_LPSPI1                   \
    {                                                \
        AWBL_IMX1050_LPSPI_NAME,                     \
        0,                                           \
        AWBL_BUSID_PLB,                              \
        0,                                           \
        (struct awbl_dev *)&__g_imx1050_lpspi1_dev,  \
        &__g_imx1050_lpspi1_devinfo                  \
    },

#else
#define AWBL_HWCONF_IMX1050_LPSPI1

#endif /* AW_DEV_IMX1050_LPSPI */

#endif /* __AWBL_HWCONF_IMX1050_LPSPI_H */

/* end of file */
