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
 * \file  rtk.h
 * \brief rtk is light weigh and powerful real time scheduler since 2012.
 *
 * \internal
 * \par modification history:
 * - 2.02.1110 1017-11-10  imp, add OS_TRACE instrumentation;remove RTK_TRACE().
 * - 2.01.1209 2015-12-09  dcf, add RTK_TRACE(); fix bug: msgq_send() always return 0.
 * - 2.00.1117 2015-11-17  dcf, add semc_broadcast, 
 *                              add members to rtk_task,
 *                              support task event callback on exit.
 *                              support thread local storage.
 * - 1.02.0 2015-08-26     dcf, rewrite msgq, add mbox; fix software timer bug; Support newlib reent.
 * - 1.00.14433 2014-11-19 dcf, support task_errno_set/get.
 * - 0.9    2012-08-01 dcf first version.
 * \endinternal
 */

#ifndef __RTK_H
/* rtk header always define this macro */
#define __RTK_H 1

#define __RTK_VERSION__ ( (2<<24)  | (0<<16) | (1117<<0))
#define __RTK_VERSION_STR__ "2.00.1117"

#ifdef __cplusplus
extern "C" {
#endif                                                                  /* __cplusplus                  */

#include <stdarg.h>
#include <stdint.h>
#include "os/list.h"
#include "rtk_config.h"

/**
 *  @addtogroup kernel
 *  @{
 */

/**
 *  @addtogroup kernel_structure
 *  @{
 */


/**
 *  @brief soft timer structure definition
 *
 *  this is a link list watchdog like soft timer implementation.
 *  The list is sorted at insertion time by 'tick'.
 *  The first element's uiTick is decreased at each tick anounce in the link list.
 */
struct  rtk_tick
{
    struct list_head  node;     /*!< node to the link list     */
    unsigned int      tick;     /*!< tick count                */
    void (*timeout_callback)( void *); /*!< timeout callback function */
    void             *arg;
};


/**
 *  @brief priority queue node structure
 *
 *  This is a priority queue node with key.
 */
struct rtk_private_priority_q_node
{
    struct list_head node;          /*!< the node       */
    int              key;           /*!< the key value  */
};

/**
 *  @brief task control block definition
 *
 *  Task Control Block have many fields.
 *  Task's name is just a pointer.
 *  option and safe_count is not used currently.
 *  @sa TASK_API
 */
struct rtk_task
{
    void                               *sp;                /*!< stack pointer,        */
    const char                         *name;              /*!< task's name           */
    char                               *stack_low;         /*!< stack low pointer     */
    char                               *stack_high;        /*!< stack high pointer    */
    struct rtk_private_priority_q_node  prio_node;         /*!< node in priority Q    */
    struct rtk_tick                     tick_node;         /*!< node in softtimer Q   */
    struct list_head                    sem_node;          /*!< node in pending Q     */
    struct list_head                   *pending_resource;  /*!< pend node if any      */
#if CONFIG_MUTEX_EN
    struct list_head                    mutex_holded_head; /*!< remember all mutex    */
    int                                 priority;          /*!< normal priority       */
#endif
    struct list_head                    task_list_node;    /*!< node in task list     */
    int                                 option;            /*!< for the further       */
    int                                 current_priority;  /*!< running priority      */
    int                                 err;               /*!< errno used internal   */
#if CONFIG_TASK_TERMINATE_EN
    int                                 safe_count;        /*!< prevent task deletion */
#endif
    int                                 status;            /*!< task status           */
    unsigned int                        tid;               /*!< task id               */
    int                                 error_number;      /**<  errno of current task,exit value */
#if CONFIG_NEWLIB_REENT_EN
       /* Allocate a Newlib reent structure that is specific to this task.
        Note Newlib support has been included by popular demand, but is not
        used by the rtk maintainers themselves.  rtk is not
        responsible for resulting newlib operation.  User must be familiar with
        newlib and must provide system-wide implementations of the necessary
        stubs. Be warned that (at the time of writing) the current newlib design
        implements a system-wide malloc() that must be provided with locks. */
        struct _reent                   newlib_reent;
#endif

    void                               *thread_local_storage;
    void                               *env;
#if CONFIG_TASK_JOIN_EN
    struct rtk_task                    *p_who_join_me;
    void                               *p_join_ret;
#endif
    void                               *extended[4]; /*  */
};


/**
 *  @brief semaphore definition
 *
 *  @sa SEMAPHORE_API
 */
struct rtk_semaphore
{
    union {
        unsigned int        count; /*!< counter when it is semB or sem C    */
        struct rtk_task     *owner; /*!< owner when it is mutex              */
    }u;
    struct list_head        pending_tasks;          /*!< the pending tasks link list head    */
    unsigned char           type;                   /*!< Specifies the type of semaphore     */
};

/**
 *  @brief mutex struct
 */
struct rtk_mutex
{
    struct rtk_semaphore s;
    struct list_head     sem_member_node; /*!< only used when it is mutex          */
    int                  mutex_recurse_count; /*!< only used when it is mutex          */
};


/**
 *  @brief struct rtk_msgq struct definition
 *
 *  @sa  MSGQ_API
 */
struct rtk_msgq_node;
struct rtk_msgq_node
{
	struct rtk_msgq_node *next;
};
struct rtk_msgq
{
    struct rtk_semaphore sem_rd;         /*!< read semaphore          */
    struct rtk_semaphore sem_wr;         /*!< write semaphore         */
    int         buff_size;      /*!< buffer size             */
    int         count;          /*!< max unit                */
    int         unit_size;      /*!< element size            */
    struct rtk_msgq_node *full_list_head; /*!< read list head */
    struct rtk_msgq_node *full_list_tail; /*!< read list tail */
    struct rtk_msgq_node *free_list_head; /*!< not used storages */
    char       *buff;        /*!< dynamic allocated       */
    struct rtk_msgq_node nodes[1]; /* pointer to node array */
};

/**
 *  @brief struct rtk_mbox - mailbox struct definition
 *
 *  @sa  MBOX_API
 */
struct rtk_mbox
{
    struct rtk_semaphore sem_rd;         /*!< read semaphore          */
    struct rtk_semaphore sem_wr;         /*!< write semaphore         */
    int         count;          /*!< max unit                */
    int         rd;             /*!< read pointer            */
    int         wr;             /*!< write pointer           */
    void       **buff;        /*!< dynamic allocated       */
};


/**
 *  @}
 */

/**
 *  @defgroup kernel_const_value const definition
 *  @{
 */
/**
 *  @defgroup task_status   task status definition
 *  @{
 */
#ifndef TASK_READY
#define TASK_READY              0x00
#endif
#ifndef TASK_PENDING
#define TASK_PENDING            0x01
#endif
#ifndef TASK_DELAY
#define TASK_DELAY              0x02
#endif
#ifndef TASK_SUSPENDED
#define TASK_SUSPENDED          0x04
#endif
#ifndef TASK_DEAD
#define TASK_DEAD               0xF0
#endif
#ifndef TASK_PREPARED
#define TASK_PREPARED           0x50
#endif
/**
 *  @}
 */
/**
 *  @}
 */

/**
 *  @addtogroup kernel_const_value
 *  @{
 */
/**
 *  @defgroup struct rtk_semaphoreype    semaphore type
 *  @{
 */
#ifndef SEM_TYPE_NULL
#define SEM_TYPE_NULL       0x00    /*!< semaphore type: NULL    */
#endif
#ifndef SEM_TYPE_BINARY
#define SEM_TYPE_BINARY     0x01    /*!< semaphore type: binary  */
#endif
#ifndef SEM_TYPE_COUNTER
#define SEM_TYPE_COUNTER    0x02    /*!< semaphore type: counter */
#endif
#ifndef SEM_TYPE_MUTEX
#define SEM_TYPE_MUTEX      0x03    /*!< semaphore type: mutex   */
#endif
/**
 *  @}
 */
/**
 *  @}
 */


/**
 *  @name waitforever
 *  @{
 */
#ifndef WAIT_FOREVER
#define WAIT_FOREVER    ((unsigned int)0xffffffff)
#endif
/**
 *  @}
 */


/**
 *  @defgroup API
 *  @{
 */

/**
 *  @defgroup TASK_API task API
 *  @{
 */

/**
 *  @brief declare task infomation
 *
 *  @par startup example
 *  @code
 *  void func(char *a, char *b) {
 *
 *      init_systimer();
 *      while (1) {
 *          kprintf("hello %s %s\n", a, b)
 *          task_delay(1);
 *      }
 *  }
 *  int main()
 *  {
 *      int priority1 = 10;
 *      int priority2 = 20;
 *      static TASK_INFO_DECL(info1, 1024);
 *      static TASK_INFO_DECL(info2, 1024);
 *
 *      arch_interrupt_disable();
 *      kernel_init();
 *
 *      TASK_INIT( "ta", info1, priority1, func, "task a p1","task a p2" );
 *      TASK_INIT( "tb", info2, priority2, func, "task b p1","task b p2" );
 *      TASK_STARTUP(info1);
 *      TASK_STARTUP(info2);
 *      os_startup();
 *      return 0;
 *  }
 *  @endcode
 */
/* #define TASK_INFO_DECL(info, stack_size) struct __taskinfo_##info {struct rtk_task tcb; char stack[stack_size]; }info */
#define TASK_INFO_DEF(info, stack_size) struct __taskinfo_##info {struct rtk_task tcb; char stack[stack_size]; }info
#define TASK_INFO_IMPORT(info)  extern struct __taskinfo_##info info  /* added by zen 2013-3-6 */

/**
 *  @brief init task infomation
 *
 *  infomation value 'info' is from TASK_INFO_DECL().
 */
#define TASK_INIT(name, info, priority, func, arg1, arg2)               \
    task_init( &(info).tcb, (name), (priority), 0, (info).stack, (info).stack+sizeof((info).stack)-1, func, (arg1), (arg2) )

/**
 *  @brief task startup macro.
 *
 *  infomation value 'info' is from TASK_INFO_DECL().
 */
#define TASK_STARTUP(info)  task_startup( &(info).tcb )

#define TASK_TERMINATE(info) task_terminate( &(info).tcb );

/**
 * @brief kernel initialize
 *
 * kernel_init() must be called first of all.
 */
void rtk_init( void );

/**
 * @brief task control block init.
 *
 * @param task          pointer of task control block. You provide it.
 * @param name          name of the task. This string is copied to the top of the stack.
 * @param priority      task normal running priority.
 * @param stack_low     low address of the stack.
 * @param stack_high    high address of the stack.
 * @param pfunc         task entry function.
 * @param arg1          argument 1 to the task.
 * @param arg2          argument 2 to the task.
 *
 *  A task is initialized by this function but not be added to running queue.
 *  A task_starup(task) will add a initialized task to running queue.
 *  So you must use function task_startup() to start a initialized task.
 * @sa task_starup();
 */
struct rtk_task *task_init(struct rtk_task *task,
                          const char     *name,
                          int             priority, /* priority of new task */
                          int             option, /* task option word */
                          char *          stack_low,
                          char *          stack_high,
                          void           *pfunc, /* entry point of new task */
                          void           *arg1, /* 1st of 10 req'd args to pass to entryPt */
                          void           *arg2);

/**
 *  @brief task start up.
 *
 *  add a task to running queue.
 */
int task_startup( struct rtk_task *task );

void *task_set_tls(struct rtk_task *task, void *data );
void *task_get_tls(struct rtk_task *task );

/**
 *  @brief starting up operating system.
 *
 *  calling this function will start the scheduler, and switch to
 *  the highest priority task created. So, task must be created and started up
 *  before calling this function.
 */
void rtk_startup( void );

/**
 *  @brief set task priority
 *  @fn task_priority_set
 *  @param[in]  task            task control block pointer. If NULL, current task's
 *                              priority will be change.
 *  @param[in]  new_priority    new priority.
 *  @return     0               successfully.
 *  @return     -EINVAL         Invalid argument.
 *  @return     -EPERM          Permission denied. The task is not startup yet.
 *
 * new_priority:         P0       P1   P3
 *                        |       |     |
 *  0(high) ==============================================>> 256(low priority)
 *                                ^
 *                                |
 *                         current priority
 */
int task_priority_set( struct rtk_task *task, unsigned int priority );


/**
 *  @brief stop a task and deinitialize.
 *
 *  the task may be running or pending.
 */
int task_terminate( struct rtk_task *task );

/**
 *  @brief task delay
 *
 *  delay tick.
 */
void task_delay( int tick );

/**
 *  @brief suspend a task
 *
 *  task must be READY: TASK_READY ==> TASK_SUSPENDED
 */
int task_suspend( struct rtk_task *task );
    
/**
 *  @brief resume a task
 *
 *  task must be SUSPENDED: TASK_SUSPENDED ==> TASK_READY
 */
int task_resume( struct rtk_task *task );
    
/**
 *  \brief system tick get
 */
unsigned int tick_get( void );

int task_safe( void );
int task_unsafe( void );

/**
 *  @brief check if a task is exist in the system
 *
 */
int task_check_exist(struct rtk_task *task);

/**
 *  @brief Wait for a task exit,and get its exit code
 *  @fn task_join
 *  @param[in]  task            task control block pointer.
 *  @param[out] p_status        out the exit code
 *  @return     0               successfully.
 *  @return     0 - errno

 */
int task_join(struct rtk_task *task,void **p_status);

/**
 *  @brief current task name
 */
#define CURRENT_TASK_NAME() (task_self()->name+0)

/**
 *  @brief current task priority
 */
#define CURRENT_TASK_PRIORITY() (task_self()->priority+0)

/**
 *  @brief current task errno
 */
#define CURRENT_TASK_ERR() (task_self()->err+0)

/**
 *  @}
 */

/**
 *  @defgroup SEMAPHORE_API semaphore API
 *  @{
 */

/**
 *  @brief semaphore declaration macro
 *
 *  @par example
 *  @code
 *  struct rtk_semaphore semb;
 *  struct rtk_semaphore semc;
 *  struct rtk_mutex mutex;
 *  void do_init( void ) {
 *      semc_init( &semc, init_count );
 *      semb_init( &semb, init_count ); /@ 0 or 1 @/
 *      mutex_init( &mutex );
 *  }
 *
 *  void use_it( void ) {
 *      semc_take( &semc, tick );
 *      ...
 *      semb_take( &semb, tick );
 *      ...
 *      mutex_lock( &mutex );
 *      ...
 *      mutex_unlock( &mutex );
 *      ...
 *  }
 *  @endcode
 */
#define SEM_DECL(sem) struct rtk_semaphore sem
#define SEM_DEF( sem, t, init)                 \
    struct rtk_semaphore sem; struct rtk_semaphore sem = {  \
        {init},                                 \
        LIST_HEAD_INIT(sem.pending_tasks),      \
        t,                                      \
    }

/**
 *  @brief semaphore binary declaration macro.
 */
#define SEMB_DECL(name)  SEM_DECL(name)
#define SEMB_DEF(name, init_value)  SEM_DECL(name, SEM_TYPE_BINARY, init_value)

/**
 *  @brief semaphore counter declaration macro.
 */
#define SEMC_DECL(name) SEM_DECL(name)
#define SEMC_DEF(name, init_value)   SEM_DECL(name, SEM_TYPE_COUNTER, init_value)

/**
 *  @brief mutex declaration macro.
 */
#define MUTEX_DECL(var) struct rtk_mutex var
#define MUTEX_DEF(var)                                            \
    struct rtk_mutex var={                                        \
        {                                                         \
            {0}, LIST_HEAD_INIT((var).s.pending_tasks),           \
            SEM_TYPE_MUTEX,                                       \
        },                                                        \
        LIST_HEAD_INIT((var).sem_member_node),                    \
        0,                                                        \
    }

/**
 *  \brief Initialize a counter semaphore.
 *
 *  \param[in]  semid       pointer
 *  \param[in]  initcount   Initializer: 0 or 1.
 *  \return     0           always successfully.
 *  \attention  parameter is not checked. You should check it by yourself.
 */
int  semc_init( struct rtk_semaphore *semid, int InitCount );

/**
 *  @brief semaphore counter deinitialize
 */
int  semc_terminate( struct rtk_semaphore *semid );

int  semc_reset( struct rtk_semaphore *semid, int reset_value );
int  semc_clear( struct rtk_semaphore *semid );

/**
 *  \brief Initialize a binary semaphore.
 *
 *  \param[in]  semid       pointer
 *  \param[in]  initcount   Initializer: 0 or 1.
 *  \return     0           always successfully.
 *  \attention  parameter is not checked. You should check it by yourself.
 */
int  semb_init( struct rtk_semaphore *semid, int InitCount );

/**
 *  \brief make a semaphore binary invalidate.
 *
 *  \param[in] semid    pointer
 *  \return 0           successfully.
 *  \return -EPERM      Permission Denied.
 *
 *  make the semaphore invalidate. This function will wake up all
 *  the pending tasks with parameter -ENXIO, and the pending task will
 *  get an error -ENXIO returning from semb_take().
 *
 *  \sa semb_init()
 */
int  semb_terminate( struct rtk_semaphore*semid );

/**
 *  \brief aquire a semaphore counter.
 *  \param[in] semid    semaphore pointer
 *  \param[in] tick     max waiting time in systerm tick.
 *                      if tick == 0, it will return immedately without block.
 *                      if tick == -1, it will wait forever.
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *  \return     -EINVAL Invalid argument
 *  \return     -ETIME  time out.
 *  \return     -ENXIO  semaphore is terminated by other task or interrupt service routine.
 *  \return     -EAGAIN Try again. Only when tick==0 and semaphore is not available.
 */
int  semc_take( struct rtk_semaphore *semid, unsigned int tick );

/**
 *  \brief release a counter semaphore.
 *  \param[in] semid    pointer
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *  \return     -ENOSPC no space to perform give operation.
 *  \return     -EINVAL Invalid argument
 *  \note               can be used in interrupt service.
 */
int  semc_give( struct rtk_semaphore *semid );

int  semb_reset( struct rtk_semaphore*semid, int reset_value );
int  semb_clear( struct rtk_semaphore*semid );

/**
 *  \brief broadcast all pending task
 *
 *  \param[in] semid    pointer
 *  \retval    n        number of pending task.
 *  \note               can be used in interrupt service.
 */
int semc_broadcast( struct rtk_semaphore *semid );

/**
 *  \brief aquire a semaphore binary.
 *  \param[in] semid    semaphore pointer
 *  \param[in] tick     max waiting time in systerm tick.
 *                      if tick == 0, it will return immedately without block.
 *                      if tick == -1, it will wait forever.
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *  \return     -EINVAL Invalid argument
 *  \return     -ETIME  time out.
 *  \return     -ENXIO  semaphore is terminated by other task or interrupt service routine.
 *  \return     -EAGAIN Try again. Only when tick==0 and semaphore is not available.
 *
 */
int  semb_take( struct rtk_semaphore *semid, unsigned int tick );

/**
 *  \brief release a binary semaphore.
 *  \param[in] semid    pointer
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *  \return     -EINVAL Invalid argument
 *  \note               can be used in interrupt service.
 */
int  semb_give( struct rtk_semaphore *semid );

/**
 *  \brief initialize a mutex.
 *
 *  \param[in]  semid       pointer
 *  \return     0           always successfully.
 *  \attention  parameter is not checked. You should check it yourself.
 *  \sa struct rtk_mutexerminate()
 */
int  mutex_init( struct rtk_mutex *semid );

/**
 *  \brief aquire a mutex lock.
 *  \param[in] semid    mutex pointer
 *  \param[in] tick     max waiting time in systerm tick.
 *                      if tick == 0, it will return immedately without block.
 *                      if tick == -1, it will wait forever.
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *  \return     -EINVAL Invalid argument
 *  \return     -ETIME  time out.
 *  \return     -EDEADLK Deadlock condition detected.
 *  \return     -ENXIO  mutex is terminated by other task or interrupt service routine.
 *  \return     -EAGAIN Try again. Only when tick==0 and mutex is not available.
 *
 *  \attention          cannot be used in interrupt service.
 */
int  mutex_lock( struct rtk_mutex *semid, unsigned int tick );

/**
 *  \brief release a mutex lock.
 *  \param[in] semid    mutex pointer
 *  \return     0       successfully.
 *  \return     -EPERM  permission denied.
 *                      The mutex's ownership is not current task. Or
 *                      used in interrupt context.
 *  \return     -EINVAL Invalid argument
 *  \attention          cannot be used in interrupt service.
 */
int  mutex_unlock( struct rtk_mutex *semid );

/**
 *  \brief make a mutex invalidate.
 *
 *  \param[in] semid    mutex pointer
 *  \return 0       successfully.
 *  \return -EPERM  Permission Denied.
 *
 *  make the mutex invalidate. This function will wake up all
 *  the pending tasks with parameter -ENXIO, and the pending task will
 *  get an error -ENXIO returning from mutex_take().
 *
 *  \sa mutex_init()
 */
int mutex_terminate( struct rtk_mutex *mutex );
/**
 *  @}
 */


/**
 *  \defgroup MSGQ_API message queue API
 *  @{
 */

/**
 *  @brief declare & init msgq
 *
 *  declare a msg queue and init.
 *  large code size.
 *  please use MSGQ_DECL_NO_INIT() & MSGQ_DO_INIT()
 *
 *  @par example
 *  @code
 *
 *  MSGQ_DECL_INIT( mymsgq, sizeof(int), 10 );
 *  int func_init( void )
 *  {
 *      /@ do nothing to init @/
 *      return 0;
 *  }
 *  int func_send( int *buff )
 *  {
 *      return msgq_send( (struct rtk_msgq*)&mymsgq, buff, sizeof(int), 1000 );
 *  }
 *  int func_recieve( int *buff )
 *  {
 *      return msgq_recieve( (struct rtk_msgq*)mymsgq, buff, sizeof(int), -1, 0);
 *  }
 *  @endcode
 */

/**
 *  @brief declare & init msgq (wellcome to MICRO world)
 *
 *  this is recommemded way to init msgq ( reducing code's size ):
 *
 *  @par example
 *  @code
 *
 *  MSGQ_DECL_NO_INIT( static, mymsgq, sizeof(int)*10 );
 *  int func_init( void )
 *  {
 *      return MSGQ_DO_INIT( mymsgq, sizeof(int) );
 *  }
 *  int func_send( int *buff )
 *  {
 *      return msgq_send( &mymsgq, buff, sizeof(int), 1000 );
 *  }
 *  int func_recieve( int *buff )
 *  {
 *      return msgq_recieve( (struct rtk_msgq*)mymsgq, buff, sizeof(int), -1, 0);
 *  }
 *  @endcode
 */
#define MSGQ_DECL(name, msg_size, msg_count ) \
		struct rtk_msgq_new_type_##name {\
			struct rtk_msgq super;\
			struct rtk_msgq_node __reserved_storage[msg_count];\
			char storage[msg_count][msg_size];\
		}name

#define MSGQ_INIT(name, msg_size, msg_count)  msgq_init( &(name).super, (name).storage, sizeof((name).storage), msg_size )

/**
 *  \brief Initialize a message queue.
 *
 *  \param[in]  pmsgq       pointer
 *  \param[in]  buff        buffer pointer.
 *  \param[in]  msg_count   msg count.
 *  \param[in]  msg_size    element size.
 *  \return     pmsgq       successfully.
 *  \return     NULL        Invalid argument.
 *  \attention  parameter is not checked. You should check it by yourself.
 *
 *  @par example
 *  @code
 *      #define COUNT 10
 *      #define M sizeof(struct _yourbase_type)*COUNT
 *      struct _yourbase_type {
 *          int a;int b;
 *      };
 *      MSGQ_DECL(msgq_var, sizeof(struct _yourbase_type), COUNT );
 *      void func_init( void ){
 *          MSGQ_INIT(msgq_var);
 *      }
 *  @endcode
 */
struct rtk_msgq *msgq_init( struct rtk_msgq *pmsgq, void *buff, int count, int unit_size );

/**
 *  \brief msgq_is_empty
 *
 *  \return 1   msgq is empty
 *  \return 0   msgq is not empty
 */
int msgq_is_empty( struct rtk_msgq *pmsgq );
    
/**
 *  \brief msgq_is_full
 *
 *  \return 1   msgq is full
 *  \return 0   msgq is not full
 */
int msgq_is_full( struct rtk_msgq *pmsgq );
    
/**
 *  \brief make a msgq invalidate.
 *
 *  \param[in] pmsgq    pointer
 *  \return 0           successfully.
 *  \return -EPERM      Permission Denied.
 *
 *  make the msgq invalidate. This function will wake up all
 *  the pending tasks with parameter -ENXIO, and the pending task will
 *  get an error -ENXIO returning from msgq_receive()/msgq_send().
 *
 *  \sa msgq_init()
 */
int msgq_terminate( struct rtk_msgq *pmsgq );


/**
 *  @brief receive msg from a msgQ
 *  @param pmsgq     a pointer to the msgQ.(the return value of function msgq_create)
 *  @param buff      the memory to store the msg. It can be NULL. if
 *                   it is NULL, it just remove one message from the head.
 *  @param buff_size the buffer size.
 *  @param tick      the max time to wait if there is no message.
 *                   if pass -1 to this, it will wait forever.
 *  @return -1       error, please check errno. if errno == ETIME, it means Timer expired,
 *                   if errno == ENOMEM, it mean buffer_size if not enough.
 *  @return 0        receive successfully.
 */
int msgq_receive( struct rtk_msgq *pmsgq, void *buff, int buff_size, int tick );

/**
 *  @brief send message to a the message Q.
 *  @param pmsgq     a pointer to the msgQ.
 *  @param buff      the message to be sent.
 *  @prarm size      the size of the message to be sent in bytes.
 *  @param tick      if the msgQ is not full, this function will return immedately, else it
 *                   will block some tick. Set it to -1 if you want to wait forever.
 *  @return 0        successfully.
 *  @return -EINVAL  Invalid argument.
 *  @return -ENODATA size is 0.
 *  @return -ETIME   time expired.
 */
int msgq_send( struct rtk_msgq *pmsgq, const void *buff, int size, int tick );

/**
 *  @brief reset a message queue.
 *
 *  make the specified message queue write counter full,
 *  and read counter empty.
 *  This function will wake up the writer.
 */
int msgq_clear( struct rtk_msgq *pmsgq );

/**
 *  @}
 */


/**
 *  \defgroup MBOX_API -mailbox API
 *  @{
 */

/**
 *  @brief declare & init mbox
 *
 *  declare a msg queue and init.
 *  large code size.
 *  please use MSGQ_DECL_NO_INIT() & MSGQ_DO_INIT()
 *
 *  @par example
 *  @code
 *
 *  MSGQ_DECL_INIT( mymsgq, sizeof(int), 10 );
 *  int func_init( void )
 *  {
 *      /@ do nothing to init @/
 *      return 0;
 *  }
 *  int func_send( int *buff )
 *  {
 *      return msgq_send( (struct rtk_msgq*)&mymsgq, buff, sizeof(int), 1000 );
 *  }
 *  int func_recieve( int *buff )
 *  {
 *      return msgq_recieve( (struct rtk_msgq*)mymsgq, buff, sizeof(int), -1, 0);
 *  }
 *  @endcode
 */

#define MBOX_DECL_INIT(zone, name, unitsize, cnt)                             \
    zone char __mboxqbuff##name[(unitsize)*(cnt)];                  \
    zone struct rtk_mbox name; struct rtk_mbox name = {                                           \
        /* .sem_rd = , */                                               \
        {{0,}, LIST_HEAD_INIT((name.sem_rd.pending_tasks)),  SEM_TYPE_COUNTER},    \
        /* .sem_wr = , */                                               \
        {{cnt,},LIST_HEAD_INIT((name.sem_wr.pending_tasks)), SEM_TYPE_COUNTER},  \
        /* .buff_size = sizeof((name).buff),  */                        \
        /* .count = cnt, */                                             \
        /* .unit_size = unitsize, */                                    \
        (unitsize)*(cnt),cnt,unitsize,                                  \
        /* .rd = 0, */                                                  \
        /* .wr = 0, */                                                  \
        0,0,                                                            \
        /* buff*/                                                       \
        __mboxbuff##name,                                               \
    }

/**
 *  @brief declare & init msgq
 *
 *  this is recommemded way to init msgq ( reducing code's size ):
 *
 *  @par example
 *  @code
 *
 *  MSGQ_DECL_NO_INIT( static, mymsgq, sizeof(int)*10 );
 *  int func_init( void )
 *  {
 *      return MSGQ_DO_INIT( mymsgq, sizeof(int) );
 *  }
 *  int func_send( int *buff )
 *  {
 *      return msgq_send( &mymsgq, buff, sizeof(int), 1000 );
 *  }
 *  int func_recieve( int *buff )
 *  {
 *      return msgq_recieve( (struct rtk_msgq*)mymsgq, buff, sizeof(int), -1, 0);
 *  }
 *  @endcode
 */
#define MBOX_DECL(name, buffersize )
#define MBOX_DEF_NO_INIT(name, buffersize )                             \
    struct __mbox_def_##name {                                          \
        char   buffer[buffersize];                                      \
        struct rtk_mbox mbox;                                           \
    } name;
#define MBOX_DO_INIT(name, unitsize)  mbox_init( &name.mbox, mbox.buffer, sizeof(mbox.buffer), unitsize)

/**
 *  \brief Initialize a message queue.
 *
 *  \param[in]  pmsgq       pointer
 *  \param[in]  buff        buffer pointer.
 *  \param[in]  buffer_size buffer size.
 *  \param[in]  unit_size   element size.
 *  \return     pmsgq       successfully.
 *  \return     NULL        Invalid argument.
 *  \attention  parameter is not checked. You should check it by yourself.
 *
 *  @par example
 *  @code
 *      #define COUNT 10
 *      #define M sizeof(struct _yourbase_type)*COUNT
 *      struct _yourbase_type {
 *          int a;int b;
 *      };
 *      char buffer[M];
 *      struct rtk_msgq msgq_var;
 *      void func_init( void ){
 *          msgq_init( &msgq_var, buffer, sizeof(buffer), (struct _yourbase_type));
 *      }
 *  @endcode
 */
struct rtk_mbox *mbox_init( struct rtk_mbox *thiz, void *buff, int element_count );

/**
 *  \brief msgq_is_empty
 *
 *  \return 1   msgq is empty
 *  \return 0   msgq is not empty
 */
int mbox_is_empty( struct rtk_mbox *thiz );

/**
 *  \brief msgq_is_full
 *
 *  \return 1   msgq is full
 *  \return 0   msgq is not full
 */
int mbox_is_full( struct rtk_mbox *thiz );

/**
 *  \brief make a msgq invalidate.
 *
 *  \param[in] pmsgq    pointer
 *  \return 0           successfully.
 *  \return -EPERM      Permission Denied.
 *
 *  make the msgq invalidate. This function will wake up all
 *  the pending tasks with parameter -ENXIO, and the pending task will
 *  get an error -ENXIO returning from msgq_receive()/msgq_send().
 *
 *  \sa msgq_init()
 */
int mbox_terminate( struct rtk_mbox *thiz );


/**
 *  @brief receive msg from a msgQ
 *  @param pmsgq     a pointer to the msgQ.(the return value of function msgq_create)
 *  @param buff      the memory to store the msg. It can be NULL. if
 *                   it is NULL, it just remove one message from the head.
 *  @param buff_size the buffer size.
 *  @param tick      the max time to wait if there is no message.
 *                   if pass -1 to this, it will wait forever.
 *  @return -1       error, please check errno. if errno == ETIME, it means Timer expired,
 *                   if errno == ENOMEM, it mean buffer_size if not enough.
 *  @return 0        receive successfully.
 */
int mbox_receive( struct rtk_mbox *thiz, void *buff, int tick );

/**
 *  @brief send message to a the message Q.
 *  @param pmsgq     a pointer to the msgQ.
 *  @param buff      the message to be sent.
 *  @prarm size      the size of the message to be sent in bytes.
 *  @param tick      if the msgQ is not full, this function will return immedately, else it
 *                   will block some tick. Set it to -1 if you want to wait forever.
 *  @return 0        successfully.
 *  @return -EINVAL  Invalid argument.
 *  @return -ENODATA size is 0.
 *  @return -ETIME   time expired.
 */
int mbox_send( struct rtk_mbox *thiz, const void *buff, int tick );

/**
 *  @brief reset a message queue.
 *
 *  make the specified message queue write counter full,
 *  and read counter empty.
 *  This function will wake up the writer.
 */
int mbox_clear( struct rtk_mbox *thiz );

/**
 *  @}
 */

/**
 *  @defgroup OTHER_API other API
 *  @{
 */

void arch_interrupt_enable( int old );
int  arch_interrupt_disable( void );
void enter_int_context( void );
void exit_int_context( void );

extern int rtk_is_int_context;
extern void schedule(void);
#define IS_INT_CONTEXT()        (rtk_is_int_context>0)
#define ENTER_INT_CONTEXT()     enter_int_context()
#define EXIT_INT_CONTEXT()      exit_int_context()


#if CONFIG_TICK_DOWN_COUNTER_EN>0
void rtk_tick_down_counter_init(struct rtk_tick *_this);
int rtk_tick_down_counter_set_func( struct rtk_tick *_this, void (*func)(void*), void*arg );
void rtk_tick_down_counter_start( struct rtk_tick *_this, unsigned int tick );
void rtk_tick_down_counter_stop ( struct rtk_tick *_this );
void rtk_tick_down_counter_announce( void );
#endif

/**
 * @brief task list head
 *
 * internal used currently
 */
/**
 * @brief pontor of current task control bock.
 *
 * @ATTENTION  you should NEVER modify it.
 */
extern struct rtk_task *task_self(void);

/**
 *  @brief     task_yield
 *
 *
 *  note: idle task cannot call this function
 *  @param  N/A
 *  @return N/A. yield cpu.
 */
void task_yield( void );

/**
 *  @brief task iterate
 *
 *  @param     func    iterating callback function, type: int func( void *arg, struct rtk_task*task );
 *  @param     arg     arg to int func( arg, task );
 *
 *  int func( void *arg, struct rtk_task*task );
 *  function func()'s return value:
 *      - 0             no error
 *      - nonzero       error, return immediately.
 *  
 */
void task_for_each( int ( *func )( void *, struct rtk_task * ), void *arg );
    
/**
 *  @brief get current task_errno addr
 *
 *  @return errno's address
 */
int *task_errno_addr( void );
    
/**
 *  @}
 */

/**
 *  @brief user never use this.
 *
 *  this is private structure.
 */
struct __priority_q_bitmap_head
{
    struct rtk_private_priority_q_node *phighest_node;
    unsigned int                        bitmap_group;
    unsigned int                        max_priority;
    struct list_head                   *tasks;
    uint32_t                            bitmap_tasks[1];
};

/**
 *  @brief rtk max priority def
 *
 *  define rtk max priroty.
 *  _max_priority can be 8~1023
 */
#define RTK_MAX_PRIORITY_DEF(_max_priority)                             \
    struct __priority_q_bitmap_head_def                                 \
    {                                                                   \
        struct rtk_private_priority_q_node *phighest_node;              \
        unsigned int                        bitmap_group;               \
        unsigned int                        max_priority;               \
        struct list_head                   *tasks;                      \
        uint32_t                            bitmap_tasks[((_max_priority+1)&(32-1)) \
                                                         ?((_max_priority+1)/32+1) \
                                                         :((_max_priority+1)/32)]; \
        struct list_head                    _tasks[_max_priority+1];    \
    };                                                                  \
    static struct __priority_q_bitmap_head_def __rtk_readyq;            \
    static struct __priority_q_bitmap_head_def __rtk_readyq = {0,0,_max_priority,__rtk_readyq._tasks,}; \
    struct __priority_q_bitmap_head * aw_const g_rtk_ready_q          = (struct __priority_q_bitmap_head*)&__rtk_readyq

unsigned int rtk_max_priority( void );

/**
 * \brief 最大优先级数目配置
 *
 * 由于CPU资源可能有限，为了避免不必要的RAM消耗，用户可以将此参数设置为实际
 * 需要的优先级数目。取值范围：1 <= MAX_PRIORITY  <= 1024， 可用的优先级是：
 *  0到 MAX_PRIORITY-1。例：如果配置为8，那么可用优先级范围是0-7.
 *
 *
 * \hideinitializer
 */
#define MAX_PRIORITY            rtk_max_priority()/*!< must be <= 256 and >=1 */

/**
 *  @}
 */

/**
 *  @}
 */

typedef struct {

    void (*pfRecordEnterISR)      (void); 
    void (*pfRecordExitISR)       (void); 
    void (*pfRecordExitISRToSched)(void);

    void (*pfRecordTaskInfo)      (struct rtk_task* pTask);
    void (*pfRecordTaskCreate)    (struct rtk_task* pTask);
    void (*pfRecordTaskTerminate) (struct rtk_task* pTask);

    void (*pfRecordTaskStartExec) (struct rtk_task* pTask);
    void (*pfRecordTaskStopExec)  (void);
    void (*pfRecordTaskStartReady)(struct rtk_task* pTask);
    void (*pfRecordTaskStopReady) (struct rtk_task* pTask, unsigned int Reason);
    
    void (*pfRecordStart)         (void);
    void (*pfRecordStop)          (void);

    void (*pfRecordVoid)          (unsigned int EventID);
    void (*pfRecordU32)           (unsigned int EventID, unsigned long para0);
    void (*pfRecordU32x2)         (unsigned int EventID, unsigned long para0, unsigned long para1);
    void (*pfRecordU32x3)         (unsigned int EventID, unsigned long para0, unsigned long para1, unsigned long para2);
    void (*pfRecordU32x4)         (unsigned int EventID, unsigned long para0, unsigned long para1, unsigned long para2, unsigned long para3);
    void (*pfRecordEndCall)       (unsigned int EventID);
    void (*pfRecordEndCallU32)    (unsigned int EventID, unsigned long retval);
    
    unsigned long (*pfShrinkId) (unsigned long ID); 

    void (*pfRecordEnterTimer)    (unsigned long TimerId);           
    void (*pfRecordExitTimer)     (void); 

} OS_TRACE_API;

void OS_SetTraceAPI(const OS_TRACE_API *p_trace);

/**
 *  @}
 */



#ifdef __cplusplus
}
#endif                                                                  /*  __cplusplus                 */


#endif

