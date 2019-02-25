/*******************************************************************************
*                                 Apollo
*                       ---------------------------
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
 * \brief 输入捕获测试例程
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - AW_DEV_IMX1050_QTIMER3_CAP
 *   2. 将板子上的GPIO1_19与GPIO1_8引脚短接,运行程序，通过串口调试助手观察捕获结果，
 *      串口调试助手设置：波特率为115200，8位数据长度，1个停止位，无流控。
 *
 * \par 源代码
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-05  mex, first implementation.
 * \endinternal
 */
#include "aworks.h"
#include "aw_gpio.h"
#include "aw_cap.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "imx1050_pin.h"
#include "aw_prj_params.h"
#include "aw_timer.h"
#include "aw_sem.h"

/* 定义一个二进制信号量 */
AW_SEMB_DECL_STATIC(cap_semb);

/* 定义输入捕捉使用的输入通道 */
#define __TEST_CAP_ID       QTIMER3_CAP3   /* GPIO1_19 */

/* 定义全局的测量信号周期 */
unsigned int g_period_ns;

/**
 * \brief 捕获PWM的周期
 */
static void __my_callback(void *arg, unsigned int count)
{
    static unsigned int num = 0;

    if (num == 0) {
        num = 1;
    } else {
        num = 0;
        aw_cap_disable(__TEST_CAP_ID);

        /* count 中保存了两次捕获的计数差值 */
        aw_cap_count_to_time(__TEST_CAP_ID, 0, count, &g_period_ns);

        /* 释放信号量 */
        AW_SEMB_GIVE(cap_semb);
    }
}

/**
 * \brief 软件定时器中断入口函数
 */
aw_local void __timer_isr (void *p_arg)
{

    /* GPIO翻转模拟产生PWM */
    aw_gpio_toggle(GPIO1_8);

    /*  再次定时2ms */
    aw_timer_start(p_arg, aw_ms_to_ticks(2));
}


/**
 * \brief 主函数
 */
void demo_qtimer_cap_entry (void)
{
    aw_timer_t timer;
    int cap_test_gpios[] = {
         GPIO1_8,
    };

    /* 初始化信号量 */
    AW_SEMB_INIT(cap_semb,
                 AW_SEM_EMPTY,    /* 初始化为空状态 */
                 AW_SEM_Q_FIFO);  /* 初始化时，选项设置：AW_SEM_Q_FIFO（先后顺序排队）*/
                                  /* AW_SEM_Q_PRIORITY (按优先级排队)   */

    /* 初始化一个软件定时器 */
    aw_timer_init(&timer, __timer_isr, (void *)&timer);

    /* 定时2ms， 启动软件定时器 */
    aw_timer_start(&timer, aw_ms_to_ticks(2));

    /* 申请与配置PWM引脚 */
    if (aw_gpio_pin_request("cap_test_gpios", cap_test_gpios, AW_NELEMENTS(cap_test_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(GPIO1_8, AW_GPIO_OUTPUT_INIT_LOW | AW_GPIO_PULL_UP);
    }

    /* 配置输入捕获为上升沿触发 */
    aw_cap_config(__TEST_CAP_ID, AW_CAP_TRIGGER_RISE, &__my_callback, 0);

    /* 启动捕获 */
    aw_cap_enable(__TEST_CAP_ID);

    while(1) {

        /* 等待信号量 */
        AW_SEMB_TAKE(cap_semb, AW_SEM_WAIT_FOREVER);

        /* 打印输出 */
        aw_kprintf("The period of the signal is:%d ns\n", g_period_ns);

        /* 重新启动捕获 */
        aw_cap_enable(__TEST_CAP_ID);
    }
}


/* end of file */
