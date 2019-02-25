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

#ifndef __AWBL_HWCONF_IMX1050_LPSPI3_H
#define __AWBL_HWCONF_IMX1050_LPSPI3_H


#ifdef AW_DEV_IMX1050_LPSPI3

#include "aw_gpio.h"
#include "aw_clk.h"
#include "driver/lpspi/awbl_imx1050_lpspi.h"


/* ƽ̨��س�ʼ�� */
aw_local void __imx1050_lpspi3_plfm_init (void)
{
    int lpspi3_gpios[] = {GPIO1_31,  //SCK
                          GPIO1_30,  //MOSI
                          GPIO1_29,  //MISO
                         // GPIO1_28   //CS
                          };

    if (aw_gpio_pin_request("lpspi3_gpios",
                             lpspi3_gpios,
                             AW_NELEMENTS(lpspi3_gpios)) == AW_OK) {

        /* ���ù������� */
        aw_gpio_pin_cfg(GPIO1_31, GPIO1_31_LPSPI3_SCK);
        aw_gpio_pin_cfg(GPIO1_30, GPIO1_30_LPSPI3_SDO);
        aw_gpio_pin_cfg(GPIO1_29, GPIO1_29_LPSPI3_SDI);
        //aw_gpio_pin_cfg(GPIO1_28, GPIO1_28_LPSPI3_PCS0);
    }

    aw_clk_enable(IMX1050_CLK_CG_LPSPI3);
}


/* �豸��Ϣ */
aw_local aw_const struct awbl_imx1050_lpspi_devinfo __g_imx1050_lpspi3_devinfo = {
    {
        IMX1050_LPSPI3_BUSID,      /* ���߱�� */
    },
    IMX1050_LPSPI3_BASE,            /* ssp0�Ĵ�������ַ */
    INUM_LPSPI3,                    /* �жϱ�� */
    0,                              /**< \brief channel0 ~ channel3 */
    6,                              /**< \brief �����������ȼ� */
    DISABLE_DMA_TRANS,              /**< \brief ����DMA���� */
    50,                             /**< \brief ���һ��SCK�ź��ص�CSȡ��ѡ�е���ʱ */
    50,                             /**< \brief CSѡ�е���һ��SCK�źű��ص���ʱ */
    50,                             /**< \brief �������ʱ */

    IMX1050_CLK_CG_LPSPI3,            /* ʱ�Ӻ� */
    __imx1050_lpspi3_plfm_init      /* ƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_imx1050_lpspi_dev __g_imx1050_lpspi3_dev;

#define AWBL_HWCONF_IMX1050_LPSPI3                   \
    {                                                \
        AWBL_IMX1050_LPSPI_NAME,                     \
        0,                                           \
        AWBL_BUSID_PLB,                              \
        0,                                           \
        (struct awbl_dev *)&__g_imx1050_lpspi3_dev,  \
        &__g_imx1050_lpspi3_devinfo                  \
    },

#else
#define AWBL_HWCONF_IMX1050_LPSPI3

#endif /* AW_DEV_IMX1050_LPSPI3 */

#endif /* __AWBL_HWCONF_IMX1050_LPSPI3_H */

/* end of file */
