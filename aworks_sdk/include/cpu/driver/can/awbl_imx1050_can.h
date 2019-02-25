/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
*
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief iMX RT1050 FLEXCAN
 *
 * \internal
 * \par modification history:
 * - 1.00 17-12-14  mex, first implementation
 * \endinternal
 */

#include "awbl_can.h"
#include "imx1050_pin_property.h"

#ifndef __AWBL_IMX1050_CAN_H
#define __AWBL_IMX1050_CAN_H

#define AWBL_IMX1050_CAN_NAME    "imx1050_can"


/** \brief imx1050 can initialization structure for plb based AWBus devices */
typedef struct awbl_imx1050_can_dev_info {

    awbl_can_servinfo_t  servinfo;
    uint32_t             reg_base;
    uint8_t              int_num;

    void   (*pfn_plfm_init)(void);
} awbl_imx1050_can_dev_info_t;

/** \brief imx1050 can device channel structure for awbus lite */
typedef struct awbl_imx1050_can_dev {

    /**< \brief device */
    struct awbl_dev  dev;

     /** \brief driver functions, always goes first */
    struct awbl_can_service can_serv;

    /**< \brief ���ڼ�¼�������� */
    uint8_t sendtype;

} awbl_imx1050_can_dev_t;

/**
 * \brief iMX RT1050 CAN ����ע��
 */
void awbl_imx1050_flexcan_drv_register (void);

#endif /* __AWBL_IMX1050_CAN_H */