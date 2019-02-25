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
 * \brief 编译器相关定义头文件
 *
 * \internal
 * \par modification history:
 * - 1.00 14-09-28  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_COMPILER_H /* { */
#define __AW_PSP_COMPILER_H

/**
 * \name inline定义
 * @{
 */
#if   defined (__CC_ARM)
#define aw_psp_inline   __inline    /**< ARM编译器inline关键字 */

#elif defined (__ICCARM__)
#define aw_psp_inline   inline      /**< IAR编译器inline关键字 */

#elif defined   (__GNUC__)
#define aw_psp_inline   inline      /**< GNU编译器inline关键字 */

#elif defined   (__TASKING__)
#define aw_psp_inline   inline      /**< TASKING编译器inline关键字 */

#elif defined   (WIN32)
#define aw_psp_inline   __inline

/** \todo 添加其它编译器inline关键字定义 */

#endif /* __CC_ARM */
/** @} */

/**
 * \name static inline定义
 * @{
 */
#if   defined (__CC_ARM)
#define aw_psp_inline         __inline
#define aw_psp_static_inline  static  __inline 		/**< ARM编译器inline关键字 */

#elif defined (__ICCARM__)
#define aw_psp_inline         inline
#define aw_psp_tatic_inline   static inline      	/**< IAR编译器inline关键字 */

#elif defined   (__GNUC__)
#define aw_psp_inline         inline
#define aw_psp_static_inline  static  inline      	/**< GNU编译器inline关键字 */

#elif defined   (__TASKING__)
#define aw_psp_inline         inline
#define aw_psp_static_inline  static inline      	/**< TASKING编译器inline关键字 */

#elif defined   (WIN32)
#define aw_psp_inline         __inline
#define aw_psp_static_inline  static __inline

#endif /* __CC_ARM */
/** @} */


/**
 * \name section定义
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

/** \fixme 根据编译器类型选择 static 关键字*/
#define aw_psp_local    static

/** \todo 根据编译器类型选择 const 关键字*/
#define aw_psp_const    const

/** \todo 根据编译器类型选择 extern 关键字*/
#define aw_psp_import   extern

/** \todo 根据编译器类型选择 extern 关键字*/
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
