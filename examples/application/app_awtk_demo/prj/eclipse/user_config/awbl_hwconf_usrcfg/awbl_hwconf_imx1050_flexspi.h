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

#ifndef __AWBL_HWCONF_IMX1050_FLEXSPI_H
#define __AWBL_HWCONF_IMX1050_FLEXSPI_H


#ifdef AW_DEV_IMX1050_FLEXSPI

#include "aw_gpio.h"
#include "aw_clk.h"
#include "driver/flexspi/awbl_imx1050_flexspi.h"
#include "driver/flexspi/awbl_imx1050_flexspi_mtd.h"
#include "imx1050_pin.h"


typedef struct __imx1050_felxspi_gpio_cfg {
    int         gpio;
    uint32_t    func;

} __imx1050_felxspi_gpio_cfg_t;


/* NVRAM 接口缓存，一个扇区，4K字节 */
aw_local uint8_t __g_nvram_buf[1024 * 4] = {0};

aw_local aw_const struct awbl_nvram_segment __g_flexspi_flash_seglst[] = {
    {"calc_data", 0,          0x600000,   1024 },
    /*
     * 存储段名称, 单元号, 起始地址，长度
     * 这里预留前4MB的空间用作Flexspi启动模式下存储固件数据,
     * 1MB作为系统配置存储s
     */
    {"IS25LP064_Flash", 0,    0x700000,   1 * 1024 * 1024},
};

#ifdef AW_CFG_FLEXSPI_FLASH_MTD
aw_local struct awbl_flexspi_flash_mtd __g_flexspi_flash_mtd;
aw_local aw_const struct awbl_flexspi_flash_mtd_info  __g_flexspi_flash_mtd_info = {
    "/sflash0",      /**< \brief flash 注册成块设备的名字 */
    1025,             /**< \brief MTD操作的起始块 (每个块为4KB)*/
    511,             /**< \brief MTD操作的块数量 */
};
#endif

aw_local aw_const  __imx1050_felxspi_gpio_cfg_t __g_flexspi_gpios_list[] = {

    {GPIO3_6,  GPIO3_6_FLEXSPIA_SS0_B},     /* FlexSPI_SS0  GPIO_SD_B1_06 */
    {GPIO3_7,  GPIO3_7_FLEXSPIA_SCLK},      /* FlexSPI_CLK  GPIO_SD_B1_07 */
    {GPIO3_8,  GPIO3_8_FLEXSPIA_DATA00},    /* FlexSPI_D0_A GPIO_SD_B1_08 */
    {GPIO3_9,  GPIO3_9_FLEXSPIA_DATA01},    /* FlexSPI_D1_A GPIO_SD_B1_09 */
    {GPIO3_10, GPIO3_10_FLEXSPIA_DATA02},   /* FlexSPI_D2_A GPIO_SD_B1_10 */
    {GPIO3_11, GPIO3_11_FLEXSPIA_DATA03},   /* FlexSPI_D3_A GPIO_SD_B1_11 */
};

/* 平台相关初始化 */
aw_local void __imx1050_flexspi_plfm_init (void)
{
    int i = 0;
    int flexspi_gpios[AW_NELEMENTS(__g_flexspi_gpios_list)];

    for (i = 0; i < AW_NELEMENTS(__g_flexspi_gpios_list); i++) {

        flexspi_gpios[i] = __g_flexspi_gpios_list[i].gpio;
    }

    if (aw_gpio_pin_request("flexspi_gpios",
                             flexspi_gpios,
                             AW_NELEMENTS(flexspi_gpios)) == AW_OK) {

        for (i = 0; i < AW_NELEMENTS(__g_flexspi_gpios_list); i++) {

            /* 配置功能引脚 */
            aw_gpio_pin_cfg(__g_flexspi_gpios_list[i].gpio,
                            __g_flexspi_gpios_list[i].func);
        }
    }

    /* 时钟配置 */
    aw_clk_parent_set(IMX1050_CLK_FLEXSPI_CLK_SEL, IMX1050_CLK_PLL_USB1);
    aw_clk_rate_set(IMX1050_CLK_FLEXSPI_PODF, 60000000);
    aw_clk_enable(IMX1050_CLK_CG_FLEXSPI);
}


/* 设备信息 */
aw_local aw_const struct awbl_imx1050_flexspi_devinfo __g_imx1050_flexspi_devinfo = {

    IMX1050_FLEXSPI_BASE,            /**< \brief LPSPI1寄存器基地址 */
    INUM_FLEXSPI,                    /**< \brief 中断编号 */
    FLEXSPI_PORT_A1,                 /**< \brief Flash芯片连接在A1端口 */
    {
        8 * 1024 * 1024,             /**< \brief Flash的大小，单位(Byte) */
        4 * 1024,                    /**< \brief Flash扇区大小 单位(Byte) */
        256,                         /**< \brief Flash页大小 单位(Byte) */
        4 * 1024,                    /**< \brief Flash块大小 单位(Byte) */
        2,                           /**< \brief CS选中到释放的间隔时间,时间为该值乘以串行时钟周期 */
        0,                           /**< \brief CS的保持时间 */
        3,                           /**< \brief CS的建立时间 */
        0,                           /**< \brief 列地址位宽 */
        1,                           /**< \brief 数据的有效时间 */
        AhbWriteWaitUnit2AhbCycle,     /**< \brief AHB写等待间隔时间单元 */
        20,                          /**< \brief AHB写等待间隔时间 */
    },

    3,                               /**< \brief 3字节地址模式 */

#if 1 /* Quad模式 (使用四个数据线，读写较快，推荐此模式) */
    AWBL_FLEXSPI_NOR_SDR_QUAD,          /**< \brief 读模式 */
    AWBL_FLEXSPI_NOR_OP_READ_1_1_4,   /**< \brief 读操作数 */
    AWBL_FLEXSPI_NOR_OP_PP_4,         /**< \brief 编程操作数 */

#else  /* Single模式 (相当于SPI，读写较慢)*/
    AWBL_FLEXSPI_NOR_FAST,           /**< \brief 读模式 */
    AWBL_FLEXSPI_NOR_OP_READ_FAST,   /**< \brief 读操作数 */
    AWBL_FLEXSPI_NOR_OP_PP_1,        /**< \brief 编程操作数 */
#endif

    AWBL_FLEXSPI_NOR_OP_BE_4K,       /**< \brief 擦除操作数 */
    8,                               /**< \brief Dummy cycle */

    {
        &__g_flexspi_flash_seglst[0],            /* 非易失性存储段配置列表 */
        AW_NELEMENTS(__g_flexspi_flash_seglst),  /* 非易失性存储段配置列表条目数 */
        __g_nvram_buf,
    },

#ifdef AW_CFG_FLEXSPI_FLASH_MTD
    &__g_flexspi_flash_mtd,
    &__g_flexspi_flash_mtd_info,
#else
    NULL,
    NULL,
#endif
    IMX1050_CLK_CG_FLEXSPI,            /**< \brief时钟号 */
    __imx1050_flexspi_plfm_init      /**< \brief平台相关初始化 */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_imx1050_flexspi_dev __g_imx1050_flexspi_dev;

#define AWBL_HWCONF_IMX1050_FLEXSPI                   \
    {                                                 \
        AWBL_IMX1050_FLEXSPI_NAME,                    \
        0,                                            \
        AWBL_BUSID_PLB,                               \
        0,                                            \
        (struct awbl_dev *)&__g_imx1050_flexspi_dev,  \
        &__g_imx1050_flexspi_devinfo                  \
    },

#else
#define AWBL_HWCONF_IMX1050_FLEXSPI

#endif /* AWBL_HWCONF_IMX1050_FLEXSPI */

#endif /* __AWBL_HWCONF_IMX1050_FLEXSPI_H */

/* end of file */
