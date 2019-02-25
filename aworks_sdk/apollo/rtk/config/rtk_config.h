/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file   rtk_config.h
 * \brief  rtk 内核配置文件
 *
 * 用户在此文件中对模块的相关参数进行配置
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-23  or2, first implementation
 * \endinternal
 */

#ifndef __RTK_CONFIG_H
#define __RTK_CONFIG_H

/**
 * \addtogroup grp_aw_task_usrcfg
 * @{
 */

/**
 * \name 优先级数目配置
 * @{
 */

/**
 * \brief 系统保留的优先级个数
 *
 * 系统保留从0开始的若干个优先级，供系统服务、设备驱动使用。
 *
 * \hideinitializer
 */
#define RESERVED_PRIORITY       8
/* added by zen 2013-5-6 */

/**
 * \brief 死锁检查使能
 *
 * 使能后能检查出死锁，并返回-EDEADLK.
 * 1: 使能
 * 0: 禁止
 * \hideinitializer
 */
#define DEAD_LOCK_DETECT_EN     1

/**
 * \brief 死锁显示使能
 *
 * 需要kprintf支持。
 * 1: 使能
 * 0: 禁止
 * \hideinitializer
 */
#define DEAD_LOCK_SHOW_EN       0

/**
 * \brief 空闲任务栈大小
 *
 * 由于CPU资源可能有限，为了避免不必要的RAM消耗，用户可以将此参数设置为实际
 * 需要的大小, 如果定义了IDLE_TASK_HOOK,特别要注意栈不能太小。
 *
 * \hideinitializer
 */
//
#ifndef IDLE_TASK_STACK_SIZE
#define IDLE_TASK_STACK_SIZE     1024
#endif

/**
 * \brief 空闲任务钩子
 *
 * IDLE_TASK_HOOK,特别要注意栈不能太小。就在这里做电源管理了。
 * 例如：
 *     #define IDLE_TASK_HOOK hook_function()
 *
 * \hideinitializer
 */



#define KERNEL_ARG_CHECK_EN            1

#define CONFIG_SEMC_EN                 1
#define CONFIG_SEMB_EN                 1
#define CONFIG_MUTEX_EN                1
#define CONFIG_MSGQ_EN                 1
#define CONFIG_TASK_PRIORITY_SET_EN    1
#define CONFIG_TASK_TERMINATE_EN       1
#define CONFIG_TICK_DOWN_COUNTER_EN    1
#define CONFIG_NEWLIB_REENT_EN         0
#define CONFIG_TASK_JOIN_EN            1

#if CONFIG_NEWLIB_REENT_EN
#include <sys/reent.h>
#endif

#if CONFIG_MSGQ_EN && !CONFIG_SEMC_EN
#error if CONFIG_MSGQ_EN==1 then CONFIG_SEMC_EN must be 1 also.
#endif
/** @} */

// TRACE配置
#define OS_CFG_TRACE_EN                 0
#define OS_CFG_TRACE_CONTROL_EN         1

// TICKLESS 配置
// 是否支持tickless
#define CONFIG_USE_TICKLESS_IDLE                0

// 因为使用tickless，在禁用调度定时器的过程中无论怎样都会引入误差，这个因子是用于修正引入的误差的
#define CONFIG_TICKLESS_MISSED_COUNT_FACTOR     1260

/** @} grp_rtkcfg */


#endif  /* __RTK_CONFIG_H */

/* end of file */

