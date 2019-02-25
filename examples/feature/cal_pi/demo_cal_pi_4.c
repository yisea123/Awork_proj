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
 * \brief Calculate 性能测试
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能 对应平台UART宏。
 *
 * - 实验现象：
 *   1. 串口打印计算信息。
 *
 * \par 源代码
 * \snippet demo_cal_pi_4.c src_cal_pi_4
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_cal_pi_4
 * \copydoc demo_cal_pi_4.c
 */

/** [src_cal_pi_4] */


#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_system.h"

#define CAL_PI_INTER(x) \
    t = c/(double)N; \
    if(i %2 ) { \
        r##x -= t; \
    } \
    else { \
        r##x +=t; \
    } \
    N +=  cal_step; \

static double __cal_pi_4(int cal_count)
{
    const int       split = 4;
    register double t,r,N,c;
    register int    i;
    register int    cal_step = cal_count/split;

    register double  r0 = 0,r1 = 0,r2 = 0,r3 = 0;


    if (cal_step %2 != 0) {
        cal_step --;
    }
    cal_count = cal_step * split;

    r = 0;
    c = 4;
    N = 1;


    for (i=0;i<cal_step;i++) {
        N = 2*i+1;
        CAL_PI_INTER(0);
        CAL_PI_INTER(1);
        CAL_PI_INTER(2);
        CAL_PI_INTER(3);

    }

    r = r0 + r1 + r2 + r3;
    return r;
}

/**
 * \brief 例程入口
 * \return 无
 */
void demo_cal_pi_4_entry(void){

    int         count = 30000000;
    volatile    aw_tick_t  t1,t2;
    double      pi;

    t1 = aw_sys_tick_get();
    pi = __cal_pi_4(count);
    t2 = aw_sys_tick_get();

    aw_kprintf("loop %d times,pi = %.9f,time = %d ms\n",
            count,pi,t2 - t1);
    return;
}

/** [src_cal_pi_4] */

/* end of file */

