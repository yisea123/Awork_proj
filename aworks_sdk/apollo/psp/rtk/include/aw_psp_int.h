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
 * \brief aworks1.0 中断标准接口头文件
 *
 * \internal
 * \par modification history:
 * - 1.00 12-08-27  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_INT_H
#define __AW_PSP_INT_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "rtk.h"

/******************************************************************************/
/** \todo seek for the right int libraray by CPU, CPU is from apollo.h  */
#define AW_PSP_INT_CPU_LOCK_DECL(key)         int key
#define AW_PSP_INT_CPU_LOCK_DECL_STATIC(key)  static int key
#define AW_PSP_INT_CPU_LOCK(key)       (key) = arch_interrupt_disable()
#define AW_PSP_INT_CPU_UNLOCK(key)     arch_interrupt_enable(key)

/******************************************************************************/
#define AW_PSP_INT_CONTEXT()    IS_INT_CONTEXT()

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_PSP_INT_H */

/* end of file */
