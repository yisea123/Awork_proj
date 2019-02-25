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
 * \brief task 平台相关标准定义头文件
 *
 * \internal
 * \par modification history:
 * - 1.12 15-11-02  deo, fixes aw_semb_valid and
 *                       add aw_semc_valid aw_semc_set_invalid aw_semb_set_invalid
 * - 1.11 14-08-29  orz, do fixes to fit new RTK kernel due to API changed
 * - 1.10 13-03-04  zen, refine the description
 * - 1.00 12-09-14  orz, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_SEM_H
#define __AW_PSP_SEM_H

#include "rtk.h"
#include "aw_common.h"

/******************************************************************************/
#define AW_PSP_SEM_WAIT_FOREVER        WAIT_FOREVER
#define AW_PSP_SEM_NO_WAIT             0

/******************************************************************************/
#define AW_PSP_SEM_EMPTY               0
#define AW_PSP_SEM_FULL                1

/******************************************************************************/
#define AW_PSP_SEM_Q_FIFO              0x00
#define AW_PSP_SEM_Q_PRIORITY          0x01
#define AW_PSP_SEM_DELETE_SAFE         0x02
#define AW_PSP_SEM_INVERSION_SAFE      0x04

/******************************************************************************/
typedef struct rtk_semaphore *aw_psp_semb_id_t;
typedef struct rtk_semaphore *aw_psp_semc_id_t;
typedef struct rtk_mutex     *aw_psp_mutex_id_t;

/******************************************************************************/
#define AW_PSP_SEMB_DECL(sem)          SEMB_DECL(sem)
#define AW_PSP_SEMB_DECL_STATIC(sem)   static SEMB_DECL(sem)
#define AW_PSP_SEMB_IMPORT(sem)        extern SEMB_DECL(sem)

aw_static_inline aw_psp_semb_id_t aw_psp_semb_init (struct rtk_semaphore *semid,
                                                    int                   count)
{
    (void)semb_init(semid, count);
    return semid;
}

#define AW_PSP_SEMB_INIT(sem, initial_state, options)  \
            aw_psp_semb_init(&(sem), initial_state)

#define AW_PSP_SEMB_TAKE(sem, timeout)     semb_take(&(sem), timeout)
#define AW_PSP_SEMB_GIVE(sem)              semb_give(&(sem))
#define AW_PSP_SEMB_RESET(sem, reset_value)              semb_reset(&(sem), reset_value)
#define AW_PSP_SEMB_VALID(sem)             ((sem).type != SEM_TYPE_NULL)
#define AW_PSP_SEMB_SET_INVALID(sem)       do{(sem).type=SEM_TYPE_NULL;}while(0)
#define AW_PSP_SEMB_TERMINATE(sem)         semb_terminate(&(sem))

/******************************************************************************/
static aw_inline aw_err_t aw_semb_take(aw_psp_semb_id_t sem_id, int timeout)
{
    return semb_take(sem_id, timeout);
}

/******************************************************************************/
static aw_inline aw_err_t aw_semb_give(aw_psp_semb_id_t sem_id)
{
    return semb_give(sem_id);
}

/******************************************************************************/
static aw_inline aw_err_t aw_semb_reset(aw_psp_semb_id_t sem_id, int reset_value )
{
    return semb_reset(sem_id, reset_value );
}

/******************************************************************************/
static aw_inline bool_t aw_semb_valid(aw_psp_semc_id_t sem_id)
{
    if ((sem_id != NULL) &&
        AW_PSP_SEMB_VALID(*sem_id)) {
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************/
static aw_inline void aw_semb_set_invalid (aw_psp_semc_id_t *sem_id)
{
    if (*sem_id != NULL){
        AW_PSP_SEMB_SET_INVALID(**sem_id);
    }
    *sem_id = NULL;
}

/******************************************************************************/
static aw_inline aw_err_t aw_semb_terminate(aw_psp_semb_id_t sem_id)
{
    return semb_terminate(sem_id);
}

/******************************************************************************/
#define AW_PSP_SEMC_DECL(sem)          SEMC_DECL(sem)
#define AW_PSP_SEMC_DECL_STATIC(sem)   static SEMC_DECL(sem)
#define AW_PSP_SEMC_IMPORT(sem)        extern SEMC_DECL(sem)

aw_static_inline aw_psp_semc_id_t aw_psp_semc_init (struct rtk_semaphore *semid,
                                                    int                   count)
{
    (void)semc_init(semid, count);
    return semid;
}
#define AW_PSP_SEMC_INIT(sem, initial_count, options) \
            aw_psp_semc_init(&(sem), initial_count)

#define AW_PSP_SEMC_TAKE(sem, timeout)     semc_take(&(sem), timeout)
#define AW_PSP_SEMC_GIVE(sem)              semc_give(&(sem))
#define AW_PSP_SEMC_RESET(sem, reset_value)              semc_reset(&(sem), reset_value)
#define AW_PSP_SEMC_VALID(sem)             ((sem).type != SEM_TYPE_NULL)
#define AW_PSP_SEMC_SET_INVALID(sem)       do{(sem).type=SEM_TYPE_NULL;}while(0)
#define AW_PSP_SEMC_TERMINATE(sem)         semc_terminate(&(sem))

/******************************************************************************/
static aw_inline bool_t aw_semc_valid (aw_psp_semc_id_t sem_id)
{
    if ((sem_id != NULL) &&
        AW_PSP_SEMC_VALID(*sem_id)) {
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************/
static aw_inline void aw_semc_set_invalid (aw_psp_semc_id_t *sem_id)
{
    if (*sem_id != NULL){
        AW_PSP_SEMC_SET_INVALID(**sem_id);
    }
    *sem_id = NULL;
}

/******************************************************************************/
static aw_inline aw_err_t aw_semc_take(aw_psp_semc_id_t sem_id, int timeout)
{
    return semc_take(sem_id, timeout);
}

/******************************************************************************/
static aw_inline aw_err_t aw_semc_give(aw_psp_semc_id_t sem_id)
{
    return semc_give(sem_id);
}

/******************************************************************************/
static aw_inline aw_err_t aw_semc_reset(aw_psp_semc_id_t sem_id, int reset_value)
{
    return semc_reset(sem_id, reset_value);
}

/******************************************************************************/
static aw_inline aw_err_t aw_semc_terminate(aw_psp_semc_id_t sem_id)
{
    return semc_terminate(sem_id);
}

/******************************************************************************/
aw_static_inline aw_psp_mutex_id_t aw_psp_mutex_init (struct rtk_mutex *semid)
{
    (void)mutex_init(semid);
    return semid;
}

#define AW_PSP_MUTEX_DECL(sem)             MUTEX_DECL(sem)
#define AW_PSP_MUTEX_DECL_STATIC(sem)      static MUTEX_DECL(sem)
#define AW_PSP_MUTEX_IMPORT(sem)           extern MUTEX_DECL(sem)
#define AW_PSP_MUTEX_INIT(sem, options)    aw_psp_mutex_init(&(sem))
#define AW_PSP_MUTEX_LOCK(sem, timeout)    mutex_lock(&(sem), timeout)
#define AW_PSP_MUTEX_UNLOCK(sem)           mutex_unlock(&(sem))
#define AW_PSP_MUTEX_VALID(sem)            ((sem).s.type != SEM_TYPE_NULL)
#define AW_PSP_MUTEX_SET_INVALID(sem)      do { (sem).s.type = SEM_TYPE_NULL; } while (0)
#define AW_PSP_MUTEX_TERMINATE(sem)        mutex_terminate(&(sem))

/******************************************************************************/
aw_static_inline aw_err_t aw_mutex_lock(aw_psp_mutex_id_t sem_id, int timeout)
{
    return mutex_lock(sem_id, timeout);
}

/******************************************************************************/
aw_static_inline aw_err_t aw_mutex_unlock(aw_psp_mutex_id_t sem_id)
{
    return mutex_unlock(sem_id);
}

/******************************************************************************/
aw_static_inline aw_err_t aw_mutex_terminate(aw_psp_mutex_id_t sem_id)
{
    return mutex_terminate(sem_id);
}

/******************************************************************************/
aw_static_inline bool_t aw_mutex_valid(aw_psp_mutex_id_t sem_id)
{
    if ((sem_id != NULL) &&
        AW_PSP_MUTEX_VALID(*sem_id)) {
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************/
#define AW_PSP_SEL_WRITE               0
#define AW_PSP_SEL_READ                1

#define AW_PSP_SEL_WKUP_LIST_DECL(list)
#define AW_PSP_SEL_WKUP_LIST_INIT(list)
#define AW_PSP_SEL_WAKEUP_All(list, sel_flag)

#endif  /* __AW_PSP_SEM_H */

/* end of file */
