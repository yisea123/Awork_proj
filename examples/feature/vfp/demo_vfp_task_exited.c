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
 * \brief (任务处理 + 浮点计算) 性能测试
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能 对应平台UART宏。
 *
 * - 实验现象：
 *   1. 串口打印计算信息。
 *
 * \par 源代码
 * \snippet demo_vfp_task_exited.c src_vfp_task_exited
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  mex, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_vfp_task_exited
 * \copydoc demo_vfp_task_exited.c
 */

/** [src_vfp_task_exited] */



#include "aworks.h"
#include "aw_task.h"
#include "aw_system.h"
#include "aw_vdebug.h"
#include "aw_sem.h"




AW_SEMB_DECL_STATIC(__g_pi_finish);
AW_SEMB_DECL_STATIC(task_vfp_exit_finish);

AW_TASK_DECL_STATIC(task_vfp_exit,1024);
AW_TASK_DECL_STATIC(task_test_pi, 1024);

#define CAL_LN2_INTER(x) \
    t = c/N; \
    if(i %2 ) { \
        r##x += t; \
    } \
    else { \
        r##x -=t; \
    } \
    N +=  cal_step; \


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



static void __task_pi_fn(void *param)
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




static void __task_vfp_exit_fn(void *param){

    /* 初始化信号量 */
    AW_SEMB_INIT(__g_pi_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    /* 初始化任务 */
    AW_TASK_INIT(task_test_pi,
                   "task_test_pi",
                    10,
                    1024,
                    __task_pi_fn,
                    0);

    /* 启动任务 */
    AW_TASK_STARTUP(task_test_pi);

    /*等待信号量被释放*/
    AW_SEMB_TAKE(__g_pi_finish,AW_SEM_WAIT_FOREVER);

    /* 判断任务是否有效 */
    while(AW_TASK_VALID(task_test_pi))
    {
        aw_task_delay(1);
    }

    aw_kprintf("task_test_pi task invalid.\r\n");

    /* 堆栈清 0 */
    memset(&task_test_pi.stack,0,sizeof(task_test_pi.stack));

    /* 释放信号量 */
    AW_SEMB_GIVE(task_vfp_exit_finish);

    return ;
}



/*
 * /brief 任务入口
 */
void demo_vfp_task_exited_entry(void){

   int          r = 0;
   int          len = sizeof(task_test_pi.stack),i;
   char         *p = (char *)task_test_pi.stack;

   /* 初始化信号量 */
    AW_SEMB_INIT(task_vfp_exit_finish,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    /* 初始化信号量 */
    AW_TASK_INIT(task_vfp_exit,
                   "task_vfp_exit",
                    16,
                    1024,
                    __task_vfp_exit_fn,
                    NULL);

    /* 启动任务 */
    AW_TASK_STARTUP(task_vfp_exit);

    /* 等待信号量被释放  */
    AW_SEMB_TAKE(task_vfp_exit_finish,AW_SEM_WAIT_FOREVER);

    /* 判断任务是否有效 */
    while (AW_TASK_VALID(task_vfp_exit)){
        aw_task_delay(1);
    }

    aw_kprintf("task_vfp_exit task invalid.\r\n");

    //执行一次浮点运算
    aw_kprintf("pi = %.9f\n",cal_pi(32));

    for(i=0;i<len;i++) {
        if(p[i] ) {
            r = 1;
            break;
        }
    }
    if(0 == r){
        aw_kprintf("stack is 0.\r\n");
    }

    return ;
}


/** [src_vfp_task_exited] */

/* end of file */
