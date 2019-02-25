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


/* 平台相关初始化 */
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

        /* 配置功能引脚 */
        aw_gpio_pin_cfg(GPIO1_31, GPIO1_31_LPSPI3_SCK);
        aw_gpio_pin_cfg(GPIO1_30, GPIO1_30_LPSPI3_SDO);
        aw_gpio_pin_cfg(GPIO1_29, GPIO1_29_LPSPI3_SDI);
        //aw_gpio_pin_cfg(GPIO1_28, GPIO1_28_LPSPI3_PCS0);
    }

    aw_clk_enable(IMX1050_CLK_CG_LPSPI3);
}


/* 设备信息 */
aw_local aw_const struct awbl_imx1050_lpspi_devinfo __g_imx1050_lpspi3_devinfo = {
    {
        IMX1050_LPSPI3_BUSID,      /* 总线编号 */
    },
    IMX1050_LPSPI3_BASE,            /* ssp0寄存器基地址 */
    INUM_LPSPI3,                    /* 中断编号 */
    0,                              /**< \brief channel0 ~ channel3 */
    6,                              /**< \brief 传输任务优先级 */
    DISABLE_DMA_TRANS,              /**< \brief 禁能DMA传输 */
    50,                             /**< \brief 最后一个SCK信号沿到CS取消选中的延时 */
    50,                             /**< \brief CS选中到第一个SCK信号边沿的延时 */
    50,                             /**< \brief 传输间延时 */

    IMX1050_CLK_CG_LPSPI3,            /* 时钟号 */
    __imx1050_lpspi3_plfm_init      /* 平台相关初始化 */
};

/* 设备实例内存静态分配 */
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
