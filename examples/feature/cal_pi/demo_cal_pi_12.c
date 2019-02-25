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
 * \brief Calculate ���ܲ���
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ�� ��Ӧƽ̨UART�ꡣ
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ϣ��
 *
 * \par Դ����
 * \snippet demo_cal_pi_12.c src_cal_pi_12
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_cal_pi_12
 * \copydoc demo_cal_pi_12.c
 */

/** [src_cal_pi_12] */

#include "aworks.h"
#include "aw_system.h"
#include "aw_vdebug.h"

#define CAL_PI_INTER(x) \
    t = c/(double)N; \
    if(i %2 ) { \
        r##x -= t; \
    } \
    else { \
        r##x +=t; \
    } \
    N +=  cal_step; \

static double __cal_pi_12(int cal_count)
{
    const int       split = 12;
    register double t,r,N,c;
    register int    i;
    register int    cal_step = cal_count/split;

    register double  r0 = 0,r1 = 0,r2 = 0,r3 = 0;
    register double  r4 = 0,r5 = 0,r6 = 0,r7 = 0;
    register double  r8 = 0,r9 = 0,r10 = 0,r11 = 0;


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
        CAL_PI_INTER(4);
        CAL_PI_INTER(5);
        CAL_PI_INTER(6);
        CAL_PI_INTER(7);
        CAL_PI_INTER(8);
        CAL_PI_INTER(9);
        CAL_PI_INTER(10);
        CAL_PI_INTER(11);
    }

    r = r0 + r1 + r2 + r3;
    r += r4 + r5 + r6 + r7;
    r += r8 + r9 + r10 + r11;
    return r;
}

/**
 * \brief �������
 * \return ��
 */
void demo_cal_pi_12_entry(void){

    int         count = 30000000;
    volatile    aw_tick_t  t1,t2;
    double      pi;

    t1 = aw_sys_tick_get();
    pi = __cal_pi_12(count);
    t2 = aw_sys_tick_get();

    aw_kprintf("loop %d times,pi = %.9f,time = %d ms\n",
            count,pi,t2 - t1);
    return;
}

/** [src_cal_pi_12] */

/* end of file */
