/*******************************************************************************
*                                  AWorks
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
 * \brief (浮点计算 + 任务调用 ) 性能测试
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能 对应平台UART宏。
 *
 * - 实验现象：
 *   1. 串口打印计算信息。
 *
 * \par 源代码
 * \snippet demo_vfp_swith_context_task_terminate.c src_vfp_swith_context_task_terminate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  mex, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_vfp_swith_context_task_terminate
 * \copydoc demo_vfp_swith_context_task_terminate.c
 */

/** [src_vfp_swith_context_task_terminate] */


#include "aworks.h"
#include "aw_task.h"
#include "aw_system.h"
#include "aw_vdebug.h"
#include "aw_sem.h"


#define CAL_LN2_INTER(x) \
    t = c/N; \
    if(i %2 ) { \
        r##x += t; \
    } \
    else { \
        r##x -=t; \
    } \
    N +=  cal_step; \

static double cal_ln2()
{
    register double      t,r,c,N;
    int                 i;
    int                 cal_count = 100000000;
    int                 cal_step = cal_count/16;

    register double  r0 = 0,r1 = 0,r2 = 0,r3 = 0,r4 = 0;
    register double  r5 = 0,r6 = 0,r7 = 0,r8 = 0,r9 = 0;
    register double  r10 = 0,r11 = 0,r12 = 0,r13 = 0,r14 = 0,r15 = 0;

    if (cal_step %2 != 0) {
        cal_step --;
    }
    cal_count = cal_step * 16;

    r = 0;
    c = 1;

    for (i=1;i<cal_step;i++) {
        N = (double )i;
        CAL_LN2_INTER(0);
        CAL_LN2_INTER(1);
        CAL_LN2_INTER(2);
        CAL_LN2_INTER(3);
        CAL_LN2_INTER(4);
        CAL_LN2_INTER(5);
        CAL_LN2_INTER(6);
        CAL_LN2_INTER(7);
        CAL_LN2_INTER(8);
        CAL_LN2_INTER(9);
        CAL_LN2_INTER(10);
        CAL_LN2_INTER(11);
        CAL_LN2_INTER(12);
        CAL_LN2_INTER(13);
        CAL_LN2_INTER(14);
        CAL_LN2_INTER(15);
    }

    r = r0 + r1 + r2 + r3;
    r+= r4 + r5 + r6 + r7;
    r+= r8 + r9 +r10 + r11;
    r+= r12 + r13 + r14 + r15;
    return r;
}

#define CAL_PI_INTER(x) \
    t = c/(double)N; \
    if(i %2 ) { \
        r##x -= t; \
    } \
    else { \
        r##x +=t; \
    } \
    N +=  cal_step; \

static double cal_pi(int cal_count)
{
    register double  t,r,N,c;
    int             i;
    int             cal_step = cal_count/16;

    register double  r0 = 0,r1 = 0,r2 = 0,r3 = 0,r4 = 0;
    register double  r5 = 0,r6 = 0,r7 = 0,r8 = 0,r9 = 0;
    register double  r10 = 0,r11 = 0,r12 = 0,r13 = 0,r14 = 0,r15 = 0;

    if (cal_step %2 != 0) {
        cal_step --;
    }
    cal_count = cal_step * 16;

    r = 0;
    c = 4;
    N = 1;


    for (i=0;i<cal_step;i++) {
        N = 2*i+1;
        CAL_PI_INTER(0);
        CAL_PI_INTER(1);
        CAL_PI_INTER(2);
        CAL_PI_INTER(3);
        CAL_PI_INTER(4);
        CAL_PI_INTER(5);
        CAL_PI_INTER(6);
        CAL_PI_INTER(7);
        CAL_PI_INTER(8);
        CAL_PI_INTER(9);
        CAL_PI_INTER(10);
        CAL_PI_INTER(11);
        CAL_PI_INTER(12);
        CAL_PI_INTER(13);
        CAL_PI_INTER(14);
        CAL_PI_INTER(15);
    }

    r = r0 + r1 + r2 + r3;
    r+= r4 + r5 + r6 + r7;
    r+= r8 + r9 +r10 + r11;
    r+= r12 + r13 + r14 + r15;
    return r;
}

AW_SEMB_DECL_STATIC(__g_pi_finish);
AW_SEMB_DECL_STATIC(__g_ln2_finish);

AW_TASK_DECL_STATIC(task_test_pi, 1024);
AW_TASK_DECL_STATIC(task_test_ln2, 1024);


static void task_test_pi_fn(void *param)
{
    double         *p = (double *)param;
    double          t;

    t = cal_pi(100000000);
    if(p != NULL) {
        *p = t;
    }
    else {
        aw_kprintf("%s@%d::%f\n",__func__,__LINE__,t);
    }
    AW_SEMB_GIVE(__g_pi_finish);
}

static void task_test_ln2_fn(void *param)
{
    double         *p = (double *)param;

    *p = cal_ln2();
    AW_SEMB_GIVE(__g_ln2_finish);
}


AW_SEMB_DECL_STATIC(task_test_vfp_task_terminate_finish);
AW_TASK_DECL_STATIC(task_test_vfp_task_terminate,1024);

static void task_test_vfp_task_terminate_fn(void *param)
{
    AW_SEMB_INIT(__g_pi_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);
    AW_SEMB_INIT(__g_ln2_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    AW_TASK_INIT(task_test_pi,
                   "task_test_pi",
                    9,
                    1024,
                    task_test_pi_fn,
                    0);
    AW_TASK_INIT(task_test_ln2,
                   "task_test_ln2",
                    10,
                    1024,
                    task_test_ln2_fn,
                    param);

    AW_TASK_STARTUP(task_test_ln2);

    aw_task_delay(1000);

    AW_TASK_STARTUP(task_test_pi);

    aw_task_delay(1000);

    AW_TASK_TERMINATE(task_test_pi);

    aw_kprintf("task_test_pi terminate.\r\n");

    memset(&task_test_pi.stack,0,sizeof(task_test_pi.stack));

    AW_SEMB_TAKE(__g_ln2_finish,AW_SEM_WAIT_FOREVER);

    while(AW_TASK_VALID(task_test_ln2) )
    {
        aw_task_delay(1);
    }

    aw_kprintf("task_test_ln2 invalid.\r\n");

    AW_SEMB_GIVE(task_test_vfp_task_terminate_finish);
}

/*
 * /brief 任务入口
 */
void demo_vfp_swith_context_task_terminate()
{
    double              ln1,ln2;
    volatile aw_tick_t  tick;
    int                 r = 0;
    int                 len = sizeof(task_test_pi.stack),i;
    char               *p = (char *)task_test_pi.stack;

    //首先计算ln2的值
    tick = aw_sys_tick_get();
    ln1 = cal_ln2();
    tick = aw_sys_tick_get() - tick;
    aw_kprintf("ln2 = %.9f,time = %dms \n",ln1,tick);


    AW_SEMB_INIT(task_test_vfp_task_terminate_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    AW_TASK_INIT(task_test_vfp_task_terminate,
                   "task_test_vfp_task_exit",
                    8,
                    1024,
                    task_test_vfp_task_terminate_fn,
                    &ln2);

    AW_TASK_STARTUP(task_test_vfp_task_terminate);

    AW_SEMB_TAKE(task_test_vfp_task_terminate_finish,AW_SEM_WAIT_FOREVER);

    while(AW_TASK_VALID(task_test_vfp_task_terminate) )
    {
        aw_task_delay(1);
    }

    aw_kprintf("task_test_vfp_task_terminate is invalid.\r\n");

    //执行一次浮点运算
    aw_kprintf("pi = %.9f\n",3.1415926);

    for(i=0;i<len;i++) {
        if(p[i] ) {
            r = 1;
            break;
        }
    }
    if(0 == r){
        aw_kprintf("stack is 0.\r\n");
    }

    if(ln1 == ln2){
        aw_kprintf("ln1 and ln2 equal.\r\n");
    }

    return ;
}


/** [src_vfp_swith_context_task_terminate] */

/* end of file */
