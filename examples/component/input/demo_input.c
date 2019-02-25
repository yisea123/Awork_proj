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
 * \brief AWorks输入子系统使用例程
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 调试串口对应的宏
 *      - AW_COM_CONSOLE
 *      - AW_COM_INPUT_EV
 *      - AW_COM_INPUT_EV_KEY
 *   2. 将开发板64号GPIO管脚连接到用户按键电路；
 *   3. 将板子中的调试串口USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *
 * - 实验现象：
 *   1. 按键状态变化，串口打印调试信息。
 *
 * \par 源代码
 * \snippet demo_input.c src_input
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-04-05  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_input
 * \copydoc demo_input.c
 */

/** [src_input] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_gpio.h"
#include "aw_input.h"
#include "aw_defer.h"

/******************************************************************************/
#define GPIO_KEY   64      /**< \brief GPIO按键管脚号GPIOn_x（视平台而定） */
#define DELAY_MS   25      /**< \brief 延时时间-ms */
/******************************************************************************/

aw_local struct aw_defer        __g_defer;  /* 定义defer对象 */
aw_local struct aw_defer_djob   __g_djob;   /* 定义工作节点 */

/**
 * \brief GPIO 按键触发回调函数
 * \param[in] p_arg  回调函数参数
 */
aw_local void gpio_key_callback (void *p_arg)
{
    /* 关闭GPIO触发功能 */
    aw_gpio_trigger_off(GPIO_KEY);

    /* 将一个工作节点添加至延迟作业处理 */
    aw_defer_commit(&__g_defer, &__g_djob);
}

/**
 * \brief 延迟工作回调函数
 * \param[in] p_arg  回调参数
 */
aw_local void delayed_work_func (void *p_arg)
{
    uint32_t key      = (uint32_t)p_arg;
    uint32_t cur_stat = aw_gpio_get(key);

    /* 上报按键事件 */
    aw_input_report_key(AW_INPUT_EV_KEY, KEY_0, cur_stat);

    /* 开启触发功能 */
    aw_gpio_trigger_on(key);
}

/**
 * \brief 输入子系统回调函数
 * \param[in] p_input_data  输入事件数据
 * \param[in] p_usr_data    用户数据
 */
aw_local void key_proc_cb (struct aw_input_event *p_input_data, void *p_usr_data)
{
    struct aw_input_key_data *p_key_data = NULL;

    if ((p_input_data != NULL) &&
        (p_input_data->ev_type != AW_INPUT_EV_KEY)) {
        return;
    }

    p_key_data = (struct aw_input_key_data *)p_input_data;
    if (p_key_data->key_code == KEY_0) {
        if (p_key_data->key_state) {
            AW_INFOF(("KEY is up : %d. \n", p_key_data->key_state));
        } else {
            AW_INFOF(("KEY is down : %d. \n", p_key_data->key_state));
        }
    }
}

/**
 * \brief 任务入口函数
 * \param[in] p_arg  任务入口参数
 */
void demo_input_entry (void)
{
    struct aw_input_handler input_handler;

    AW_INFOF(("\ninput system testing...\n"));

    /* 初始化一个延迟作业 */
    aw_defer_init(&__g_defer);

    /* 初始化一个工作节点 */
    aw_defer_job_init(&__g_djob, delayed_work_func, (void *)GPIO_KEY);

    /* 配置GPIO按键管脚为输入功能 */
    int gpio0_gpios[] = {GPIO_KEY};
    if (aw_gpio_pin_request("gpios",
                             gpio0_gpios,
                             AW_NELEMENTS(gpio0_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(GPIO_KEY, AW_GPIO_INPUT | AW_GPIO_PULL_UP);
    }

    /* 连接回调函数到引脚 */
    aw_gpio_trigger_connect(GPIO_KEY, gpio_key_callback, NULL);

    /* 设置引脚触发类型，下降沿触发 */
    aw_gpio_trigger_cfg(GPIO_KEY, AW_GPIO_TRIGGER_FALL);

    /* 注册按键输入事件到输入子系统中 */
    aw_input_handler_register(&input_handler, key_proc_cb, NULL);

    /* 启动延迟作业（创建1个优先级为0，堆栈大小为4096的线程，并启动） */
    AW_DEFER_START(&__g_defer, 1, 0, 4096, "demo_input");

    /* 开启引脚上的触发器  */
    aw_gpio_trigger_on(GPIO_KEY);
}

/** [src_input] */

/* end of file */
