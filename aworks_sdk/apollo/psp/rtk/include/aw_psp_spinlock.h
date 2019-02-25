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
 * \brief aworks1.0, ������(spin lock)ƽ̨�����ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 12-08-27  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_SPINLOCK_H
#define __AW_PSP_SPINLOCK_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_int.h"

/** \brief isr-takeable spin lock's unlock value */
#define AW_PSP_SPINLOCK_ISR_UNLOCK \
    { {-1, 0}, 0}

/** \brief declare a initialized isr-takeable spin lock */
#define AW_PSP_SPINLOCK_ISR_DECL(x,flag) \
    aw_spinlock_isr_t x = AW_PSP_SPIN_LOCK_ISR_UNLOCK

#define __SPIN_LOCK_EMPTY           0
#define __SPIN_LOCK_BUSY            1
#define __SPIN_LOCK_INTERESTED      2
#define __SPIN_LOCK_ACKNOWLEDGED    3
#define __SPIN_LOCK_NOBODY         -1

/**
 * \brief ��������������
 */
typedef struct {
    int owner;
    AW_INT_CPU_LOCK_DECL(key);      /**< \brief The int key for this lock */
} __aw_psp_spinlock_t;

/**
 * \brief ISR�ɵ�����������������
 */
typedef struct aw_psp_spinlock_isr {
    __aw_psp_spinlock_t lock;
    int                  flags;   /**< \brief Reserved for system use */
} aw_psp_spinlock_isr_t;

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_PSP_SPINLOCK_H */

/* end of file */
