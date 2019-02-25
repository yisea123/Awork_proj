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
 * \brief LED例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能AW_DEV_GPIO_LED
 *   2. 具体LED硬件配置需查看awbl_hwconf_gpio_led.h
 *
 * - 实验现象：
 *   1. LED以1Hz的频率闪烁。
 *
 * \par 源代码
 * \snippet demo_led.c src_led
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_led
 * \copydoc demo_led.c
 */

/** [src_led] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "aw_led.h"

#define  LED  0

/**
 * \brief LED demo
 * \return 无
 */
void demo_led_entry (void)
{
    aw_kprintf("\nled demo testing...\n");

    while(1) {
        aw_led_on(LED);            /* 点亮LED灯   */
        aw_mdelay(500);             /* 延时0.5s */
        aw_led_off(LED);
        aw_mdelay(500);

        aw_led_set(LED, TRUE);     /* 点亮LED灯   */
        aw_mdelay(500);
        aw_led_set(LED, FALSE);    /* 熄灭LED灯    */
        aw_mdelay(500);

        aw_led_toggle(LED);        /* LED状态翻转  */
        aw_mdelay(500);
        aw_led_toggle(LED);        /* LED状态翻转  */
        aw_mdelay(500);
    }
}

/** [src_led] */

/* end of file */
