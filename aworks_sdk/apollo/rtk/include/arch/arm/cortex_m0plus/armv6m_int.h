/*******************************************************************************
*                                 AnyWhere
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ARMv6-M 中断库头文件
 *
 * 本模块为Cortex-M0(ARMv6-M架构)的中断模块实现。
 *
 * \par 特性
 * - 中断号的定义请参考 \ref grp_aw_int_inums
 * - 只能连接一个C函数到一个中断上，连接已经被连接的中断将会返回空间不足错误
 *   (-ENOSPC)。
 *
 * \internal
 * \par modification history:
 * - 1.00 12-09-04  zen, first implementation
 * \endinternal 
 */

#ifndef __ARMV6M_INT_H
#define __ARMV6M_INT_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/** \brief 中断号的最大值 */
#define ARMV6M_INTNUM_MAX       239

/** \brief 中断号的个数 */
#define ARMV6M_INTNUM_COUNT     (ARMV6M_INTNUM_MAX + 1)

/**
 * \brief ARMv6-M 中断库初始化函数
 */
void armv6m_int_init(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __ARMV6M_INT_H */

/* end of file */
