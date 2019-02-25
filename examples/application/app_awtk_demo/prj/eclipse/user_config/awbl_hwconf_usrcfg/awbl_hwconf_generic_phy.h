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

#ifndef __AWBL_HWCONF_GENERIC_PHY0_H
#define __AWBL_HWCONF_GENERIC_PHY0_H

#ifdef AW_DEV_GENERIC_PHY0

#include "aw_gpio.h"
#include "aw_delay.h"

#include "driver/phy/awbl_generic_phy.h"


/* 硬件 PHY 地址 */
#define  PHY0_ADDR            0x01


/* 平台相关初始化 */
aw_local void __generic_phy0_plfm_init (void)
{

}

/* 设备信息 */
aw_local aw_const struct awbl_generic_phy_devinfo __g_gen_phy0_devinfo = {
    PHY0_ADDR,                  /* phy addr */
    AWBL_PHY_LINK_AUTONEG,      /* PHY mode */
    __generic_phy0_plfm_init,   /* 平台相关初始化 */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_generic_phy_dev __g_gen_phy0_dev;

#define AWBL_HWCONF_GENERIC_PHY0                \
    {                                           \
        AWBL_GENERIC_PHY_NAME,                  \
        0,                                      \
        AWBL_BUSID_MII,                         \
        IMX1050_MII_BUSID,                      \
        (struct awbl_dev *)&__g_gen_phy0_dev,   \
        &__g_gen_phy0_devinfo                   \
    },

#else
#define AWBL_HWCONF_GENERIC_PHY0

#endif  /* AW_DEV_GENERIC_PHY0 */

#endif  /* __AWBL_HWCONF_GENERIC_PHY0_H */

/* end of file */
