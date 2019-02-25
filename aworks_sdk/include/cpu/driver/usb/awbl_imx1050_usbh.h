/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief imx1050 USB host controller driver head file
 *
 * \internal
 * \par modification history:
 * - 1.00 17-12-20  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX1050_USBH_H
#define __AWBL_IMX1050_USBH_H


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "host/awbl_usbh.h"
#include "host/controller/awbl_usbh_ehci.h"


#define AWBL_IMX1050_USBH_DRV_NAME    "awbl_imx1050_usbh"


/** \brief imx1050 USB host controller struct */
struct awbl_imx1050_usbh {
    struct awbl_usbh      hc;
    struct awbl_usbh_ehci ehci;
};

/** \brief imx1050 USB host controller information */
struct awbl_imx1050_usbh_info {
    struct awbl_usbh_info   info;
    uint32_t                prio;

    uint32_t                usb_reg;
    uint32_t                phy_reg;

    int                     inum;

    int                     nqhs;
    int                     nqtds;
    int                     nitds;
    int                     nsitds;

    void (*pfn_pwr_ctrl) (bool_t on);
    void (*pfu_plfm_init)(void);
};


void awbl_imx1050_usbh_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX1050_USBH_H */
