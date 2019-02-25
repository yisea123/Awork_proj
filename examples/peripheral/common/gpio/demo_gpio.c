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
 * \brief GPIO例程
 *
 * - 操作：
 *   1. 本例程需在aw_prj_params.h头文件中禁能
 *      - AW_DEV_GPIO_LED
 *
 * - 实验现象：
 *   1. 开发板LED以0.5s的周期闪烁5次，每次打印对应LED的管脚电平值
 *   2. 开发板LED以0.1s的周期闪烁4s。
 *
 * - 备注：
 *   1. 不同开发平台使用的引脚可能不同，可根据对应平台配置GPIO引脚；
 *   2. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_gpio.c src_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 18-02-26  hsg, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gpio
 * \copydoc demo_gpio.c
 */

/** [src_gpio] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_led.h"
#include <stdlib.h>

#define GPIO_LED (19) /* 和LED相连的GPIO 管脚，根据具体平台修改*/

/**
 * \brief GPIO demo 入口
 * \return 无
 */
void demo_gpio_entry(void)
{
    int      i   = 0;
    aw_err_t ret = AW_OK;

    aw_kprintf("\nGPIO demo testing...\n");

    int gpio_led_test[] = {GPIO_LED};
    if (aw_gpio_pin_request("gpio_led_test",
                             gpio_led_test,
                             AW_NELEMENTS(gpio_led_test)) == AW_OK) {

        /* GPIO 引脚配置 */
        aw_gpio_pin_cfg(GPIO_LED, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    }

    /* LED以0.5s的周期闪烁5次 */
    for (i = 0; i < 5; i++) {
        aw_gpio_set(GPIO_LED, 0);
        ret = aw_gpio_get(GPIO_LED);
        if (AW_ENXIO != ret) {
            aw_kprintf("GPIO1_19 is %d\n", ret);
        }
        aw_mdelay(500);

        aw_gpio_set(GPIO_LED, 1);
        ret = aw_gpio_get(GPIO_LED);
        if (AW_ENXIO != ret) {
            aw_kprintf("GPIO1_19 is %d\n", ret);
        }
        aw_mdelay(500);
    }

    /* LED以0.1s的周期持续闪烁 */
    for (i = 0; i < 40; i++) {
        aw_gpio_toggle(GPIO_LED);
        aw_mdelay(100);
    }

    aw_gpio_pin_release(gpio_led_test, AW_NELEMENTS(gpio_led_test));
}

/** [src_gpio] */

/* end of file */
