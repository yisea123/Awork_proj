/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief imx1050 nandflash driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 17-3-22  smc, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX6UL_NAND_H
#define __AWBL_IMX6UL_NAND_H

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus    */

#include "aworks.h"
#include "awbus_lite.h"
#include "mtd/aw_mtd.h"

#include "awbl_nand.h"
#include "awbl_nand_bus.h"


/** \brief NandFlash�������� */
#define AWBL_IMX1050_NANDFLASH_DRV_NAME        "awbl_imx1050_nandflash_drv_name"

struct awbl_imx1050_nand_dev;

struct awbl_imx1050_nand_info {
    /** \brief ����������NandоƬ��ʱ�� */
    struct awbl_nand_timing     tim;

    /** \brief �������ڶ�NandоƬ����Ƭѡ����ʱ����Ҫ��id */
    void                        *id;

    /** \brief ҳ��С */
    uint16_t                   page_size;

    /** \brief ÿҳ���������С */
    uint8_t                    spare_size;

    /** \brief ÿ���ҳ���� */
    uint16_t                   pages_per_blk;

    /** \brief ����� */
    uint32_t                   nblks;

    /** \brief ������λ������ڿ��п���ʼλ�õ�ƫ�� */
    uint8_t                    bad_blk_byte_offs;

    /** \brief ÿcell��λ���� */
    uint8_t                    bits_per_cell;

    /** \brief ���С */
    uint32_t                   blk_size;

    /** \brief Ƭ��С */
    uint32_t                   chip_size;

    /** \brief ������ID */
    uint8_t                    maker_id;

    /** \brief �豸ID */
    uint8_t                    device_id;

    uint8_t                    ecc_strength;

    /** \brief ID�ĳ��� */
    uint8_t                    id_len;

    const struct awbl_nand_partition *p_partition_tab;

    /** \brief �������� */
    int                         npartition;

    /** \brief ECCģʽ */
    enum awbl_nand_ecc_mode           ecc_mode;

    /** \brief ECC������Ϣ */
    const struct awbl_nand_ooblayout *p_nand_ooblayout;
};

struct awbl_imx1050_nand_dev {

    struct awbl_nand_chip nand;

    struct awbl_nandbus  *p_bus;

    struct awbl_imx1050_nand_info *p_info;

    /* General-use Variables */
    int         current_chip;

    /* private */
    void            *priv;
};

void awbl_imx1050_nand_drv_register (void);

#endif    /* __AWBL_IMX1050_NAND_H */

/* end of file */
