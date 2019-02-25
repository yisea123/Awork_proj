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


#ifndef __AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08_H
#define __AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08_H

//#define AW_DEV_NAND_FLASH

#ifdef AW_DEV_NAND_FLASH

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus   */

#include "driver/nand/awbl_imx1050_nand.h"
#include "awbl_nand.h"

#include "driver/busctlr/awbl_imx1050_semc.h"

/** \brief partition table */
aw_local aw_const struct awbl_nand_partition __g_imx1050_nand_mx30lf1g08_ptab[] = {
    {"/dev/mtd0",            101,      300    , 0},        /* 101 ~ 300   */
    {"/dev/mtd1",            301,      500    , 0},        /* 301 ~ 500   */
    {"/dev/rootfs",          501,     1023    , 0},        /* 501 ~ 2048  */
};

/** \brief ECC存储位置描述  */
aw_local aw_const struct aw_mtd_oob_space __g_imx1050_nand_mx30lf1g08_ecc_pos[] = {
    {2,   34},
};

/** \brief 空闲空间位置描述，注意：使用硬件BCH时，free oob区的布局应该为从ECC的结束地址开始到OOB区的结束地址 */
aw_local aw_const struct aw_mtd_oob_space __g_imx1050_nand_mx30lf1g08_free_pos[] = {
    {36,  28},
};

/** \brief OOB布局描述数据 */
aw_local aw_const struct awbl_nand_ooblayout __g_imx1050_nand_mx30lf1g08_oob_layout = {
    __g_imx1050_nand_mx30lf1g08_ecc_pos,
    AW_NELEMENTS(__g_imx1050_nand_mx30lf1g08_ecc_pos),
    __g_imx1050_nand_mx30lf1g08_free_pos,
    AW_NELEMENTS(__g_imx1050_nand_mx30lf1g08_free_pos)
};

/** \brief NandFlash device information */
aw_const struct awbl_imx1050_nand_info __g_imx1050_nand_mx30lf1g08_devinfo = {
    {NANDFLASH_MX30LF1G08_TIMING},
    (void *)AWBL_IMX1050_SEMC_CE0,
    NANDFLASH_MX30LF1G08,
    NANDFLASH_MX30LF1G08_ECC_STRENGTH,
    5,
    __g_imx1050_nand_mx30lf1g08_ptab,
    AW_NELEMENTS(__g_imx1050_nand_mx30lf1g08_ptab),
    AWBL_NAND_ECC_MODE_SW_BCH,
    &__g_imx1050_nand_mx30lf1g08_oob_layout,
};

/** \brief static memory of NandFlash device */
struct awbl_imx1050_nand_dev __g_imx1050_nand_mx30lf1g08_dev;

#define AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08               \
    {                                             \
        AWBL_IMX1050_NANDFLASH_DRV_NAME,            \
        0,                                  \
        AWBL_BUSID_NAND,                    \
        IMX1050_NAND0_BUSID,                  \
        &(__g_imx1050_nand_mx30lf1g08_dev.nand.awdev),    \
        &(__g_imx1050_nand_mx30lf1g08_devinfo)            \
    },

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#else
#define AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08

#endif  /* AW_DEV_NAND_FLASH */

#endif /* __AWBL_HWCONF_IMX1050_NANDFLASH_MX30LF1G08_H */

/* end of file */

