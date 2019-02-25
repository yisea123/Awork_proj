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
 *   1. 在使用该例程时必须保证使用的定时器能支持用名称查找，该项在定时器的配置文件中的设备信息中定义。
 *
 * \par 源代码
 * \snippet demo_hwtimer_byname.c src_hwtimer_byname
 *
 * \internal
 * \par modification history:
 * - 1.00 2018-07-03  sdq, first implementation
 * \endinternal
 */
/**
 * \addtogroup demo_if_hwtimer_byname
 * \copydoc demo_hwtimer_byname.c
 */

/** [src_hwtimer_byname] */
#include "aworks.h"
#include "aw_int.h"
#include "aw_hwtimer.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_delay.h"

/**
 *  下列两个宏根据具体平台修改
 *  以imx1050的gpt定时器为例，定时器名字为“imx1050_gpt”，其所在的总线为PLB总线，编号为1
 */
#define  __TEST_HWTIMER_DRV_NAME  "imx1050_gpt"    /* 定时器名字 */
#define  __TEST_HWTIMER_BUSID      1               /* 定时器所在的总线ID */

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
void demo_hwtimer_byname_entry (void)
{
    aw_hwtimer_handle_t mytimer;

    /* 分配名为 __TEST_HWTIMER_DRV_NAME 的定时器 */
    mytimer = aw_hwtimer_alloc_byname(__TEST_HWTIMER_DRV_NAME,  /* 定时器名字 */
                                      __TEST_HWTIMER_BUSID,     /* 定时器所在总线ID */
                                      0,                        /* 定时器编号 */
                                      mytimer_isr,              /* 中断回调函数 */
                                      NULL);                    /* 中断回调函数的参数 */

    if (mytimer) {
        aw_hwtimer_enable(mytimer, 2);                 /* 使能定时中断 2Hz */
    } else {
        aw_kprintf("Timer allocation fail!\n");
    }

    for (;;) {
        aw_mdelay(1000);
    }

}
/** [src_hwtimer_byname] */

/*end of file */
