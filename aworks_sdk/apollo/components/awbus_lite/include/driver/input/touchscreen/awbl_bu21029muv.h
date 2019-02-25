/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief touch screen controller
 *
 * \internal
 * \par modification history:
 * - 1.01 16-12-13  ucc, first implemetation
 * \endinternal
 */
#ifndef __AWBL_BU210299MUV_
#define __AWBL_BU210299MUV_

#include "awbl_input.h"
#include "awbl_ts.h"
#include "awbus_lite.h"
#include "aw_i2c.h"
#include "aw_sem.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#define AWBL_TOUCHSCREEN_NAME            "bu21029muv"


struct awbl_bu21029muv_cfg
{
    int int_pin;                        /** \brief 中断引脚保留使用   */
    int dev_addr;
    awbl_ts_service_info_t ts_serv_info;
    void (*pfn_plfm_init)(void);
};

struct awbl_bu21029muv
{
	/** \brief 继承自 AWBus 设备 */
	struct awbl_dev super;

	/** \brief 继承自Touch SCreen服务 */
	struct awbl_ts_service ts;

	/** \brief iicbus */
	struct aw_i2c_device iic_bus;
    struct aw_i2c_device iic_bus_nosubaddr;
};

/**
 * \brief ts driver register
 */
void awbl_bu21029muv_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_TS2046_H */
