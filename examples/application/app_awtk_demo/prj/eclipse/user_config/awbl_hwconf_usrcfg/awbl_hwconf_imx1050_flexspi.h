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


/* NVRAM �ӿڻ��棬һ��������4K�ֽ� */
aw_local uint8_t __g_nvram_buf[1024 * 4] = {0};

aw_local aw_const struct awbl_nvram_segment __g_flexspi_flash_seglst[] = {
    {"calc_data", 0,          0x600000,   1024 },
    /*
     * �洢������, ��Ԫ��, ��ʼ��ַ������
     * ����Ԥ��ǰ4MB�Ŀռ�����Flexspi����ģʽ�´洢�̼�����,
     * 1MB��Ϊϵͳ���ô洢s
     */
    {"IS25LP064_Flash", 0,    0x700000,   1 * 1024 * 1024},
};

#ifdef AW_CFG_FLEXSPI_FLASH_MTD
aw_local struct awbl_flexspi_flash_mtd __g_flexspi_flash_mtd;
aw_local aw_const struct awbl_flexspi_flash_mtd_info  __g_flexspi_flash_mtd_info = {
    "/sflash0",      /**< \brief flash ע��ɿ��豸������ */
    1025,             /**< \brief MTD��������ʼ�� (ÿ����Ϊ4KB)*/
    511,             /**< \brief MTD�����Ŀ����� */
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

/* ƽ̨��س�ʼ�� */
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

            /* ���ù������� */
            aw_gpio_pin_cfg(__g_flexspi_gpios_list[i].gpio,
                            __g_flexspi_gpios_list[i].func);
        }
    }

    /* ʱ������ */
    aw_clk_parent_set(IMX1050_CLK_FLEXSPI_CLK_SEL, IMX1050_CLK_PLL_USB1);
    aw_clk_rate_set(IMX1050_CLK_FLEXSPI_PODF, 60000000);
    aw_clk_enable(IMX1050_CLK_CG_FLEXSPI);
}


/* �豸��Ϣ */
aw_local aw_const struct awbl_imx1050_flexspi_devinfo __g_imx1050_flexspi_devinfo = {

    IMX1050_FLEXSPI_BASE,            /**< \brief LPSPI1�Ĵ�������ַ */
    INUM_FLEXSPI,                    /**< \brief �жϱ�� */
    FLEXSPI_PORT_A1,                 /**< \brief FlashоƬ������A1�˿� */
    {
        8 * 1024 * 1024,             /**< \brief Flash�Ĵ�С����λ(Byte) */
        4 * 1024,                    /**< \brief Flash������С ��λ(Byte) */
        256,                         /**< \brief Flashҳ��С ��λ(Byte) */
        4 * 1024,                    /**< \brief Flash���С ��λ(Byte) */
        2,                           /**< \brief CSѡ�е��ͷŵļ��ʱ��,ʱ��Ϊ��ֵ���Դ���ʱ������ */
        0,                           /**< \brief CS�ı���ʱ�� */
        3,                           /**< \brief CS�Ľ���ʱ�� */
        0,                           /**< \brief �е�ַλ�� */
        1,                           /**< \brief ���ݵ���Чʱ�� */
        AhbWriteWaitUnit2AhbCycle,     /**< \brief AHBд�ȴ����ʱ�䵥Ԫ */
        20,                          /**< \brief AHBд�ȴ����ʱ�� */
    },

    3,                               /**< \brief 3�ֽڵ�ַģʽ */

#if 1 /* Quadģʽ (ʹ���ĸ������ߣ���д�Ͽ죬�Ƽ���ģʽ) */
    AWBL_FLEXSPI_NOR_SDR_QUAD,          /**< \brief ��ģʽ */
    AWBL_FLEXSPI_NOR_OP_READ_1_1_4,   /**< \brief �������� */
    AWBL_FLEXSPI_NOR_OP_PP_4,         /**< \brief ��̲����� */

#else  /* Singleģʽ (�൱��SPI����д����)*/
    AWBL_FLEXSPI_NOR_FAST,           /**< \brief ��ģʽ */
    AWBL_FLEXSPI_NOR_OP_READ_FAST,   /**< \brief �������� */
    AWBL_FLEXSPI_NOR_OP_PP_1,        /**< \brief ��̲����� */
#endif

    AWBL_FLEXSPI_NOR_OP_BE_4K,       /**< \brief ���������� */
    8,                               /**< \brief Dummy cycle */

    {
        &__g_flexspi_flash_seglst[0],            /* ����ʧ�Դ洢�������б� */
        AW_NELEMENTS(__g_flexspi_flash_seglst),  /* ����ʧ�Դ洢�������б���Ŀ�� */
        __g_nvram_buf,
    },

#ifdef AW_CFG_FLEXSPI_FLASH_MTD
    &__g_flexspi_flash_mtd,
    &__g_flexspi_flash_mtd_info,
#else
    NULL,
    NULL,
#endif
    IMX1050_CLK_CG_FLEXSPI,            /**< \briefʱ�Ӻ� */
    __imx1050_flexspi_plfm_init      /**< \briefƽ̨��س�ʼ�� */
};

/* �豸ʵ���ڴ澲̬���� */
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
