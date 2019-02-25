/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB OS support
 *
 * \internal
 * \par modification history:
 * - 1.00 17-12-11  deo, first implementation
 * \endinternal
 */

/*******************************************************************************
  includes
*******************************************************************************/
#include "aworks.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_usb_os.h"
#include "aw_usb_mem.h"


/* USB SEM */
struct __usb_sem {
    AW_SEMC_DECL(s);
};

/* USB MUTEX */
struct __usb_mutex {
    AW_MUTEX_DECL(m);
};




/******************************************************************************/
aw_usb_task_handle_t aw_usb_task_create (const char  *name,
                                         int          prio,
                                         size_t       stk_s,
                                         void       (*pfnc) (void *p_arg),
                                         void        *p_arg)
{
    return (aw_usb_task_handle_t)aw_task_create(name, prio, stk_s, pfnc, p_arg);
}




/******************************************************************************/
aw_err_t aw_usb_task_delete (aw_usb_task_handle_t tsk)
{
    return aw_task_delete((aw_task_id_t)tsk);
}




/******************************************************************************/
aw_err_t aw_usb_task_startup (aw_usb_task_handle_t tsk)
{
    return aw_task_startup((aw_task_id_t)tsk);
}




/******************************************************************************/
aw_usb_sem_handle_t aw_usb_sem_create (void)
{
    struct __usb_sem *p_sem;

    p_sem = (struct __usb_sem *)aw_usb_mem_alloc(sizeof(struct __usb_sem));
    if (p_sem == NULL) {
        return NULL;
    }

    if (AW_SEMC_INIT(p_sem->s, 0, AW_SEM_Q_PRIORITY) == NULL) {
        aw_usb_mem_free(p_sem);
        return NULL;
    }
    return (aw_usb_sem_handle_t)p_sem;
}




/******************************************************************************/
void aw_usb_sem_delete (aw_usb_sem_handle_t sem)
{
    AW_SEMC_TERMINATE(((struct __usb_sem *)sem)->s);
    aw_usb_mem_free(sem);
}




/******************************************************************************/
aw_err_t aw_usb_sem_take (aw_usb_sem_handle_t sem,
                          int                 timeout)
{
    return AW_SEMC_TAKE(((struct __usb_sem *)sem)->s, timeout);
}




/******************************************************************************/
aw_err_t aw_usb_sem_give (aw_usb_sem_handle_t sem)
{
    return AW_SEMC_GIVE(((struct __usb_sem *)sem)->s);
}




/******************************************************************************/
aw_usb_mutex_handle_t aw_usb_mutex_create (void)
{
    struct __usb_mutex *p_mutex;

    p_mutex = (struct __usb_mutex *)aw_usb_mem_alloc(sizeof(struct __usb_mutex));
    if (p_mutex == NULL) {
        return NULL;
    }

    if (AW_MUTEX_INIT(p_mutex->m, AW_SEM_Q_PRIORITY) == NULL) {
        aw_usb_mem_free(p_mutex);
        return NULL;
    }
    return (aw_usb_mutex_handle_t)p_mutex;
}




/******************************************************************************/
void aw_usb_mutex_delete (aw_usb_mutex_handle_t mutex)
{
    AW_MUTEX_TERMINATE(((struct __usb_mutex *)mutex)->m);
    aw_usb_mem_free(mutex);
}




/******************************************************************************/
aw_err_t aw_usb_mutex_lock (aw_usb_mutex_handle_t mutex,
                            int                   timeout)
{
    return AW_MUTEX_LOCK(((struct __usb_mutex *)mutex)->m, timeout);
}




/******************************************************************************/
aw_err_t aw_usb_mutex_unlock (aw_usb_mutex_handle_t mutex)
{
    return AW_MUTEX_UNLOCK(((struct __usb_mutex *)mutex)->m);
}
