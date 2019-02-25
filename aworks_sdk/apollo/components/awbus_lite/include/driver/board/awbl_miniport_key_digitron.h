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
 * \brief MINIPORT 数码管模块  + 矩阵键盘模块 GPIO 驱动
 *
 *
 * \par 使用示例
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 17-06-19  nwt, first implementation.
 * \endinternal
 */

#ifndef AWBL_MINIPORT_GPIO_KEY_DIGITRON_H_
#define AWBL_MINIPORT_GPIO_KEY_DIGITRON_H_

#include "awbl_scanner.h"
#include "awbl_gpio.h"

#include "driver/digitron/awbl_gpio_digitron.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MINIPORT_KEY_DIGITRON_NAME      "miniport_key_digitron"

struct awbl_miniport_key_digitron_param {

	/**
	 * \brief gpio数码管设备配置参数
	 */
	struct awbl_gpio_digitron_param    gpio_ddpar;

    /**
     * \brief 扫描器设备配置参数
     */
    struct awbl_scanner_param           scpar;
};

struct awbl_miniport_key_digitron_dev {

	/**
	 * \brief 继承自awbl_dev
	 */
	struct awbl_dev                  dev;

	/**
	 * \brief 关联gpio数码管设备
	 */
	struct awbl_gpio_digitron_dev   gpio_digitron;

	/**
	 * \brief 关联扫描器设备
	 */
	struct awbl_scanner_dev          scan_dev;
};

#ifdef __cplusplus
}
#endif


#endif /* AWBL_MINIPORT_GPIO_KEY_DIGITRON_H_ */
