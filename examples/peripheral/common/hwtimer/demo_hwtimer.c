/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief hwtimer 测试程序
 *
 * hwtimer 通用定时器，提供如下功能:
 *
 * - 操作步骤：
 *   1. 在aw_prj_params.h中使能
 *      - 对应平台的硬件定时器宏
 *      - AW_DEV_GPIO_LED
 *
 * - 实验现象：
 *   1. LED以1Hz的频率闪烁；
 *   2. 串口打印相应信息。
 *
 * - 备注：
 *   1. 在使用该例程时必须保证使用的定时器不能仅支持用名称查找，该项在定时器的配置文件中的设备信息中定义。
 *
 * \par 源代码
 * \snippet demo_hwtimer.c src_hwtimer
 *
 * \internal
 * \par modification history:
 * - 1.00 2018-07-03  sdq, first implementation
 * \endinternal
 */
/**
 * \addtogroup demo_if_hwtimer
 * \copydoc demo_hwtimer.c
 */

/** [src_hwtimer] */
#include "aworks.h"
#include "aw_hwtimer.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_delay.h"

#define  LED  0

/**
 * \brief 硬件定时器中断服务函数。
 * \param[in] p_arg : 任务参数
 */
static void mytimer_isr (void *p_arg)
{
    aw_led_toggle(LED);
}

/**
 * \brief hwtimer 测试函数
 */
void demo_hwtimer_entry (void)
{
    aw_hwtimer_handle_t mytimer;

    /* 通过需求申请定时器 */
    mytimer = aw_hwtimer_alloc(1000,                   /* 申请输入频率1 */
                               1,                      /* 最小频率1Hz */
                               1000000,                /* 最大频率1MHz */
                               AW_HWTIMER_AUTO_RELOAD, /* 自动重装 */
                               mytimer_isr,            /* 中断服务函数 */
                               (void *) NULL);         /* 中断服务函数入口函数 */

    if (mytimer) {
        aw_hwtimer_enable(mytimer, 2);                 /* 使能定时中断 2Hz */
    } else {
        aw_kprintf("Timer allocation fail!\n");
    }

    for (;;) {
        aw_mdelay(1000);
    }

}
/** [src_hwtimer] */

/*end of file */
