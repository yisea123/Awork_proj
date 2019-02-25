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
 * \brief ��������ض���ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-28  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_COMPILER_H /* { */
#define __AW_PSP_COMPILER_H

/**
 * \name inline����
 * @{
 */
#if   defined (__CC_ARM)
#define aw_psp_inline   __inline    /**< ARM������inline�ؼ��� */

#elif defined (__ICCARM__)
#define aw_psp_inline   inline      /**< IAR������inline�ؼ��� */

#elif defined   (__GNUC__)
#define aw_psp_inline   inline      /**< GNU������inline�ؼ��� */

#elif defined   (__TASKING__)
#define aw_psp_inline   inline      /**< TASKING������inline�ؼ��� */

#elif defined   (WIN32)
#define aw_psp_inline   __inline

/** \todo �������������inline�ؼ��ֶ��� */

#endif /* __CC_ARM */
/** @} */

/**
 * \name static inline����
 * @{
 */
#if   defined (__CC_ARM)
#define aw_psp_inline         __inline
#define aw_psp_static_inline  static  __inline 		/**< ARM������inline�ؼ��� */

#elif defined (__ICCARM__)
#define aw_psp_inline         inline
#define aw_psp_tatic_inline   static inline      	/**< IAR������inline�ؼ��� */

#elif defined   (__GNUC__)
#define aw_psp_inline         inline
#define aw_psp_static_inline  static  inline      	/**< GNU������inline�ؼ��� */

#elif defined   (__TASKING__)
#define aw_psp_inline         inline
#define aw_psp_static_inline  static inline      	/**< TASKING������inline�ؼ��� */

#elif defined   (WIN32)
#define aw_psp_inline         __inline
#define aw_psp_static_inline  static __inline

#endif /* __CC_ARM */
/** @} */


/**
 * \name section����
 * @{
 */
#ifdef __CC_ARM             /* RealView Compiler */
#define aw_psp_section(x)    __attribute__((section(x)))

#elif defined (__ICCARM__)  /* IAR Compiler */
#define aw_psp_section(x)    \ x

#elif defined (__GNUC__)    /* GNU GCC Compiler */
#define aw_psp_section(x)    __attribute__((section(x)))

#elif defined   (WIN32)
#define aw_psp_section(x)

#endif
/** @} */

/** \fixme ���ݱ���������ѡ�� static �ؼ���*/
#define aw_psp_local    static

/** \todo ���ݱ���������ѡ�� const �ؼ���*/
#define aw_psp_const    const

/** \todo ���ݱ���������ѡ�� extern �ؼ���*/
#define aw_psp_import   extern

/** \todo ���ݱ���������ѡ�� extern �ؼ���*/
#define aw_psp_export   extern

#ifndef __GNUC__
#define restrict
#endif

#ifdef __GNUC__
# define likely(x)      __builtin_expect(!!(x), 1)
# define unlikely(x)    __builtin_expect(!!(x), 0)
#else
# define likely(x)        x
# define unlikely(x)      x
#endif

#if   defined (__CC_ARM)
aw_psp_static_inline void aw_barrier()
{
    __schedule_barrier();
} 

aw_psp_static_inline void aw_barrier_mb()
{
    __schedule_barrier();
    __dsb(0xF);
    __schedule_barrier();
} 

aw_psp_static_inline void aw_barrier_wmb()
{
    __schedule_barrier();
    __dsb(0xF);
    __schedule_barrier();
}

aw_psp_static_inline void aw_barrier_rmb()
{
    __schedule_barrier();
    __dsb(0xF);
    __schedule_barrier();
}

aw_psp_static_inline void aw_barrier_isb()
{
    __schedule_barrier();
    __isb(0xF);
    __schedule_barrier();
}

#elif defined(__GNUC__)
aw_psp_static_inline void aw_barrier()
{
    asm volatile("" : : : "memory");
} 
#include "aw_psp_barrier_gcc.h"

#endif

#endif /* } __AW_PSP_COMPILER_H */

/* end of file */
