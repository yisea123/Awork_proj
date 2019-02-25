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
 * \brief  rtk �ں������ļ�
 *
 * �û��ڴ��ļ��ж�ģ�����ز�����������
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
 * \name ���ȼ���Ŀ����
 * @{
 */

/**
 * \brief ϵͳ���������ȼ�����
 *
 * ϵͳ������0��ʼ�����ɸ����ȼ�����ϵͳ�����豸����ʹ�á�
 *
 * \hideinitializer
 */
#define RESERVED_PRIORITY       8
/* added by zen 2013-5-6 */

/**
 * \brief �������ʹ��
 *
 * ʹ�ܺ��ܼ���������������-EDEADLK.
 * 1: ʹ��
 * 0: ��ֹ
 * \hideinitializer
 */
#define DEAD_LOCK_DETECT_EN     1

/**
 * \brief ������ʾʹ��
 *
 * ��Ҫkprintf֧�֡�
 * 1: ʹ��
 * 0: ��ֹ
 * \hideinitializer
 */
#define DEAD_LOCK_SHOW_EN       0

/**
 * \brief ��������ջ��С
 *
 * ����CPU��Դ�������ޣ�Ϊ�˱��ⲻ��Ҫ��RAM���ģ��û����Խ��˲�������Ϊʵ��
 * ��Ҫ�Ĵ�С, ���������IDLE_TASK_HOOK,�ر�Ҫע��ջ����̫С��
 *
 * \hideinitializer
 */
//
#ifndef IDLE_TASK_STACK_SIZE
#define IDLE_TASK_STACK_SIZE     1024
#endif

/**
 * \brief ����������
 *
 * IDLE_TASK_HOOK,�ر�Ҫע��ջ����̫С��������������Դ�����ˡ�
 * ���磺
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

// TRACE����
#define OS_CFG_TRACE_EN                 0
#define OS_CFG_TRACE_CONTROL_EN         1

// TICKLESS ����
// �Ƿ�֧��tickless
#define CONFIG_USE_TICKLESS_IDLE                0

// ��Ϊʹ��tickless���ڽ��õ��ȶ�ʱ���Ĺ�������������������������������������������������
#define CONFIG_TICKLESS_MISSED_COUNT_FACTOR     1260

/** @} grp_rtkcfg */


#endif  /* __RTK_CONFIG_H */

/* end of file */

