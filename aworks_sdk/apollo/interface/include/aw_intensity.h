/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief INTENSITY (强度调节) 标准服务
 *
 * \brief 为LCD、LED、BUZZER等设备提供强度调节服务
 *
 * 使用本服务需要包含以下头文件:
 * \code
 * #include "aw_intensity.h"
 * \endcode
 *
 * \par 使用示例
 * \code
 *
 * 在使用intensity标准接口前, 需调用具体intensity设备驱动的构造函数，
 * 例如，在HW480272面板驱动中，使用基于PWM的intensity设备驱动背光
 *
 * aw_local aw_err_t __panel_pan_backlight (awbl_mxs_panel_t *p_panel, int pwm_num, int percent)
 * {
 *  ......
 *  aw_it_dev_t *p_it = NULL;
 *
 *  p_it = awbl_pwm_it_ctor(&p_this->pwm_it, 100, pwm_num, 10000000);
 *  aw_it_level_set(p_it, 80);
 *  ......
 * }
 *
 * \endcode
 *
 * \par 使用说明
 *
 * \internal
 * \par modification history
 * - 1.01 14-11-01  ops, redefine the intensity device by using new specification.
 * - 1.00 14-07-03  ops, first implementation
 * \endinternal
 */

#ifndef AW_INTENSITY_H_
#define AW_INTENSITY_H_

#include "apollo.h"

/**
 * \brief abstract intensity device
 */
typedef struct aw_it_dev {

	/** \brief 获取强度等级 */
	int (*pfn_it_level_get)(struct aw_it_dev *p_dev);

	/** \brief 设置强度等级 */
	int (*pfn_it_level_set)(struct aw_it_dev *p_dev, int level);

	/** \brief 当前强度 */
	int current_level;

	/** \brief 等级范围 (0, max_level) */
	int max_level;

}aw_it_dev_t;

/**
 * \brief 获取设备最大强度值
 */
aw_static_inline int aw_it_max_level_get(aw_it_dev_t *p_dev)
{
	if (NULL == p_dev) {
		return -EINVAL;
	}

	return p_dev->max_level;
}

/**
 * \brief 设置强度值
 *
 * \param level   强度等级
 *
 * \return error  level大于设备等级范围
 */
aw_err_t aw_it_level_set(aw_it_dev_t *p_dev, int level);

/**
 * \brief 获取当前强度值
 *
 * \return 当前强度值
 */
int aw_it_level_get(aw_it_dev_t *p_dev);

#endif /* AW_INTENSITY_H_ */
