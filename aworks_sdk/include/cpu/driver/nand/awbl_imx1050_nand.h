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


/** \brief NandFlash驱动名称 */
#define AWBL_IMX1050_NANDFLASH_DRV_NAME        "awbl_imx1050_nandflash_drv_name"

struct awbl_imx1050_nand_dev;

struct awbl_imx1050_nand_info {
    /** \brief 控制器操作Nand芯片的时序 */
    struct awbl_nand_timing     tim;

    /** \brief 控制器在对Nand芯片进行片选操作时所需要的id */
    void                        *id;

    /** \brief 页大小 */
    uint16_t                   page_size;

    /** \brief 每页空闲区域大小 */
    uint8_t                    spare_size;

    /** \brief 每块的页个数 */
    uint16_t                   pages_per_blk;

    /** \brief 块个数 */
    uint32_t                   nblks;

    /** \brief 坏块标记位置相对于空闲块起始位置的偏移 */
    uint8_t                    bad_blk_byte_offs;

    /** \brief 每cell的位个数 */
    uint8_t                    bits_per_cell;

    /** \brief 块大小 */
    uint32_t                   blk_size;

    /** \brief 片大小 */
    uint32_t                   chip_size;

    /** \brief 制造商ID */
    uint8_t                    maker_id;

    /** \brief 设备ID */
    uint8_t                    device_id;

    uint8_t                    ecc_strength;

    /** \brief ID的长度 */
    uint8_t                    id_len;

    const struct awbl_nand_partition *p_partition_tab;

    /** \brief 分区个数 */
    int                         npartition;

    /** \brief ECC模式 */
    enum awbl_nand_ecc_mode           ecc_mode;

    /** \brief ECC配置信息 */
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
