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
 * \brief gpio触发中断例程
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能
 *      - AW_COM_CONSOLE
 *      - AW_DEV_GPIO_LED
 *      - 对应平台的串口宏
 *   2 .测试引脚的触发功能时，需用杜邦线将  TEST_GPIO_0 和 TEST_GPIO_1 对应的引脚连接起来。
 *
 * - 实验现象：
 *  1. 进入中断后，LED灯闪烁；
 *  2. 串口打印调试信息。
 *
 * - 备注：
 *   1. 不同开发平台使用的引脚可能不同，可根据对应平台配置GPIO引脚；
 *   2. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_gpio_trigger.c src_gpio_trigger
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-27  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gpio_trigger
 * \copydoc demo_gpio_trigger.c
 */

/** [src_gpio_trigger] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_led.h"
#include <stdlib.h>
#include "aw_vdebug.h"

/* 平台GPIO，可根据具体平台修改*/
#define TEST_GPIO_0     64      /**< \brief 引脚编号请根据具体平台修改*/
#define TEST_GPIO_1     65      /**< \brief 引脚编号请根据具体平台修改*/

/**\brief 记录中断进入的次数 */
aw_local uint8_t volatile __g_test_count = 0;

/* gpio 测试 回调函数  */
void test_gpio_trig_isr (void* arg) {
    uint8_t trig_mode = (uint32_t)arg;
    aw_led_toggle(0);
    __g_test_count++;
}

void demo_gpio_trigger_entry(void)
{
    uint32_t i = 0;

    // 申请中断引脚并配置引脚输出
    int gpio0_gpios[] = {TEST_GPIO_0, TEST_GPIO_1};
    if (aw_gpio_pin_request("test_gpios",
                             gpio0_gpios,
                             AW_NELEMENTS(gpio0_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(TEST_GPIO_0, AW_GPIO_PUSH_PULL | AW_GPIO_OUTPUT_INIT_HIGH);
        aw_gpio_pin_cfg(TEST_GPIO_1, AW_GPIO_INPUT);
    }

    //连接中断回调函数
    aw_gpio_trigger_connect(TEST_GPIO_1, test_gpio_trig_isr, (void *)AW_GPIO_TRIGGER_FALL);
    //配置为下降沿触发
    aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_FALL);
    //配置为上升沿触发
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_RISE);
    //配置为低电平沿触发
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_LOW);
    //配置为高电平触发
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_HIGH);
    //配置为双边沿触发
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_BOTH_EDGES);
    //启动中断
    aw_gpio_trigger_on(TEST_GPIO_1);

    for (i = 0; i < 19; i++) {
        aw_task_delay(500);
        aw_gpio_toggle(TEST_GPIO_0);
    }

    //打印进入中断次数
    AW_INFOF(("entry gpio int time:%d\r\n",__g_test_count));

    //断开中断回调函数
    aw_gpio_trigger_disconnect(TEST_GPIO_1,
                               test_gpio_trig_isr,
                               (void *)AW_GPIO_TRIGGER_FALL);
    //关闭中断
    aw_gpio_trigger_off(TEST_GPIO_1);
    //释放引脚
    aw_gpio_pin_release(gpio0_gpios, AW_NELEMENTS(gpio0_gpios));
}

/** [src_gpio_trigger] */

/* end of file */
