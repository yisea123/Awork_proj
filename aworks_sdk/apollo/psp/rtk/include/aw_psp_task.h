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
 * - 1.10 13-02-28  zen, refine the description
 * - 1.00 12-09-14  orz, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_TASK_H
#define __AW_PSP_TASK_H

#include "rtk.h"                                /* 目前使用RTK内核 */
#include "aw_compiler.h"
#include "aw_types.h"

/******************************************************************************/
typedef struct rtk_task *aw_psp_task_id_t ;     /* 任务ID类型 */

/******************************************************************************/
#define AW_PSP_TASK_ID_INVALID  NULL            /* 无效任务ID */

/******************************************************************************/
int task_stack_check (struct rtk_task *p_task,
                      unsigned int    *p_total,
                      unsigned int    *p_free);

void rtk_stk_chk_shell_init (void);
void rtk_stk_chk_print_all (void);

/******************************************************************************/
#define AW_PSP_TASK_DECL(task, stack_size) \
            TASK_INFO_DEF(task, stack_size)

/******************************************************************************/
#define AW_PSP_TASK_DECL_STATIC(task, stack_size)  \
            static TASK_INFO_DEF(task, stack_size)

/******************************************************************************/
#define AW_PSP_TASK_IMPORT(task)   TASK_INFO_IMPORT(task)

/******************************************************************************/
#define AW_PSP_TASK_INIT(task, name, priority, stack_size, func, arg1) \
            TASK_INIT(name, task, priority + RESERVED_PRIORITY, func, arg1,(void *)0)

/******************************************************************************/
#define AW_PSP_TASK_STARTUP(task)      TASK_STARTUP(task)

/******************************************************************************/
#define AW_PSP_TASK_TERMINATE(task)    task_terminate( &(task).tcb )

/******************************************************************************/
#define AW_PSP_TASK_DELAY(tick)    TASK_DELAY(tick)

/******************************************************************************/
#define AW_PSP_TASK_SUSPEND(task)    task_suspend(&(task).tcb)//TASK_SUSPEND(task)

/******************************************************************************/
#define AW_PSP_TASK_RESUME(task)    task_resume(&(task).tcb)//TASK_RESUME(task)

/******************************************************************************/
#define AW_PSP_TASK_VALID(task)     (task_check_exist(&(task).tcb))

// 这里注释掉设置任务无效的操作，要想使任务无效，请设计科学的退出机制，然后使用
// join操作
/******************************************************************************/
//#define AW_PSP_TASK_SET_INVALID(task)  do { (task).tcb.status = TASK_DEAD; } while (0)

/******************************************************************************/
#define AW_PSP_TASK_SAFE()             task_safe()

/******************************************************************************/
#define AW_PSP_TASK_UNSAFE()           task_unsafe()

/******************************************************************************/
#define AW_PSP_TASK_STACK_CHECK(task,p_total,p_free)   \
                                aw_task_stack_check(&(task).tcb,p_total,p_free)

/******************************************************************************/
#define AW_PSP_TASK_STACK_CHECK_SELF(p_total,p_free)   \
                           aw_task_stack_check(aw_task_id_self(),p_total,p_free)

/******************************************************************************/
#define AW_PSP_TASK_SYS_PRIORITY(priority)    ((priority) - RESERVED_PRIORITY)

/******************************************************************************/
#define aw_task_startup(task_id)        task_startup(task_id)

/******************************************************************************/
#define aw_task_terminate(task_id)      task_terminate(task_id)

/******************************************************************************/
#define aw_task_delay(ticks)            task_delay(ticks)

#define AW_PSP_TASK_JOIN(task,p_status)  task_join((&(task).tcb),(p_status))

/******************************************************************************/
static aw_inline void kernel_init( void )
{
    rtk_init();
}
static aw_inline void os_startup( void )
{
    rtk_startup();
}


/******************************************************************************/
static aw_inline bool_t aw_task_valid (aw_psp_task_id_t task_id)
{
    return task_check_exist(task_id);
}

/******************************************************************************/
static aw_inline aw_err_t aw_task_priority_set(aw_psp_task_id_t task_id,
                                               unsigned int new_priority)
{
    return task_priority_set(task_id, new_priority + RESERVED_PRIORITY);
}

/******************************************************************************/
static aw_inline unsigned int aw_task_priority_count(void) {
    return MAX_PRIORITY - RESERVED_PRIORITY;
}

/******************************************************************************/
static aw_inline unsigned int aw_task_lowest_priority(void) {
    return MAX_PRIORITY - 1 - RESERVED_PRIORITY;
}

/******************************************************************************/
static aw_inline aw_psp_task_id_t aw_task_id_self(void) {
    return task_self();
}

/******************************************************************************/
static aw_inline void aw_task_yield(void) {
    task_yield();
}

/******************************************************************************/
static aw_inline const char *aw_task_name_get (aw_psp_task_id_t task_id) {
    return task_id->name;
}

/******************************************************************************/
static aw_inline unsigned int aw_task_priority_get (aw_psp_task_id_t task_id) {
    return task_id->current_priority - RESERVED_PRIORITY;
}

/******************************************************************************/
static aw_inline int aw_task_stack_check (aw_psp_task_id_t task_id,
                                          unsigned int     *p_total,
                                          unsigned int     *p_free)
{
    return task_stack_check(task_id, p_total, p_free);
}

static aw_inline void *aw_task_set_tls(aw_psp_task_id_t task_id, void *data )
{
    return task_set_tls( task_id, data );
}

static aw_inline void *aw_task_get_tls(aw_psp_task_id_t task_id )
{
    return task_get_tls( task_id );
}

static aw_inline aw_err_t aw_task_join(aw_psp_task_id_t task_id,void **p_status)
{
    return task_join(task_id,p_status);
}

#endif      /* __AW_PSP_TASK_H */

/* end of file */
