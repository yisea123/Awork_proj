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
 * \brief 自旋锁演示例程
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能AW_COM_CONSOLE；
 *   2. 将板子中的RX1、TX1通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *
 * - 实验现象：
 *      若定义了__USE_SPINLOCK则串口打印__g_counter的值，每个任务打印5次，中间不会被打断；
 *      否则串口打印的东西比较杂乱，任务1和任务2会嵌套打印。
 *
 * \par 源代码
 * \snippet demo_spinlock.c src_spinlock
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-05  sup, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spinlock
 * \copydoc demo_spinlock.c
 */

/** [src_spinlock] */
#include "aworks.h"
#include "aw_spinlock.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_vdebug.h"
#include "aw_timer.h"
#include "aw_delay.h"

#define __USE_SPINLOCK  /* 使用自旋锁 */

/* 计数器 */
volatile static uint32_t __g_counter = 0;

/* 自旋锁 */
#ifdef __USE_SPINLOCK
static aw_spinlock_isr_t __g_spin_lock;
#endif

/**
 * \brief 线程 task0 入口
 * \return 无
 */
static void __task_entry (void *p_arg)
{
    uint8_t i = 0;

    AW_FOREVER {

        /* 利用自旋锁保护共享的全局变量 */
#ifdef __USE_SPINLOCK
        aw_spinlock_isr_take(&__g_spin_lock);
#endif
        for (i = 0; i < 5; i++) {
            AW_INFOF(("%s counter: %d\n", (char *)p_arg, __g_counter++));
        }
#ifdef __USE_SPINLOCK
        aw_spinlock_isr_give(&__g_spin_lock);
#endif
        AW_INFOF(("\n\n"));

        aw_mdelay(500);
    }
}

/**
 * \brief 自旋锁演示例程入口
 *
 * \return 无
 */
void demo_spinlock_entry (void)
{
    AW_TASK_DECL_STATIC(sl_task1, 1024);
    AW_TASK_DECL_STATIC(sl_task2, 1024);

    AW_INFOF(("Spin lock task start...\n"));

#ifdef __USE_SPINLOCK
    aw_spinlock_isr_init(&__g_spin_lock, 0);
#endif

    AW_TASK_INIT(sl_task1,
                 "demo_spinlock_task",
                 3,
                 1024,
                 __task_entry,
                 "task1");

    AW_TASK_STARTUP(sl_task1);

    AW_TASK_INIT(sl_task2,
                 "demo_spinlock_task",
                 3,
                 1024,
                 __task_entry,
                 "task2");

    AW_TASK_STARTUP(sl_task2);
}

/** [src_spinlock] */

/* end of file */
