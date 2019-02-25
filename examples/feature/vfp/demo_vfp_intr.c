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
 * \brief (浮点计算 + 定时器中断) 性能测试
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能 对应平台UART宏。
 *
 * - 实验现象：
 *   1. 串口打印计算信息。
 *
 * \par 源代码
 * \snippet demo_vfp_float_param.c src_vfp_float_param
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  mex, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_vfp_float_param
 * \copydoc demo_vfp_float_param.c
 */

/** [src_vfp_float_param] */

#include "aworks.h"
#include "aw_task.h"
#include "aw_system.h"
#include "aw_vdebug.h"
#include "aw_sem.h"
#include "aw_timer.h"


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

static int __g_timer_count = 0;
static void test_vfp_intr_callback(void *param)
{

    aw_kprintf("pi = %f\n",cal_pi(32));
    if(__g_timer_count< 10) {
        __g_timer_count ++;
        aw_timer_start((aw_timer_t *)param, aw_ms_to_ticks(50));
    }
}

void demo_vfp_intr(void){

    aw_timer_t              timer;
    double                  pi1,pi2,ln1,ln2;
    volatile aw_tick_t      tick;

    //首先计算出pi和ln2正确的值
    tick = aw_sys_tick_get();
    pi1 = cal_pi(100000000);
    tick = aw_sys_tick_get() - tick;
    aw_kprintf("pi = %.9f,time = %dms \n",pi1,tick);

    tick = aw_sys_tick_get();
    ln1 = cal_ln2();
    tick = aw_sys_tick_get() - tick;
    aw_kprintf("ln2 = %.9f,time = %dms \n",ln1,tick);

    AW_SEMB_INIT(__g_pi_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);
    AW_SEMB_INIT(__g_ln2_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    //开启两个任务同时计算pi和ln2
    AW_TASK_INIT(task_test_pi,
                   "task_test_pi",
                    10,
                    1024,
                    task_test_pi_fn,
                    &pi2);

    AW_TASK_INIT(task_test_ln2,
                   "task_test_ln2",
                    10,
                    1024,
                    task_test_ln2_fn,
                    &ln2);

    AW_TASK_STARTUP(task_test_pi);

    AW_TASK_STARTUP(task_test_ln2);

    __g_timer_count = 0;

    /* 初始化定时器  */
    aw_timer_init((aw_timer_t *)&timer, test_vfp_intr_callback, &timer);
    /* 启动定时器，干扰运算 */
    aw_timer_start((aw_timer_t *)&timer, aw_ms_to_ticks(5));

    AW_SEMB_TAKE(__g_ln2_finish,AW_SEM_WAIT_FOREVER);
    AW_SEMB_TAKE(__g_pi_finish,AW_SEM_WAIT_FOREVER);

    if(pi2 == pi1) {
        aw_kprintf("pi1 and pi2 equal.\r\n");
    }
    if(ln2 == ln1) {
        aw_kprintf("ln1 and ln2 equal.\r\n");
    }

    while(AW_TASK_VALID(task_test_pi) )
    {
        aw_task_delay(1);
    }

    aw_kprintf("task_test_pi is invalid.\r\n");

    while(AW_TASK_VALID(task_test_ln2) )
    {
        aw_task_delay(1);
    }

    aw_kprintf("task_test_ln2 is invalid.\r\n");

    return ;
}


/** [src_vfp_float_param] */

/* end of file */
