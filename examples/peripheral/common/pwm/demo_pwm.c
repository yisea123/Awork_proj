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
 * \brief PWM演示例程(PWM控制无源蜂鸣器)
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能
 *      - 对应平台的PWM宏。
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *
 * - 实验现象：
 *   1. 蜂鸣器以500ms为周期鸣叫。
 *
 * \par 源代码
 * \snippet demo_pwm.c src_pwm
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-25  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_pwm
 * \copydoc demo_pwm.c
 */

/** [src_pwm] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_pwm.h"
#include "aw_prj_params.h"

#define AW_PWM_ID              10
/**
 * \brief PWM演示例程入口
 * \return 无
 */
void demo_pwm_entry (void)
{
    uint32_t    period1 = 2000000;      // (ns)
    uint32_t    period2 = 1000000;      // (ns)

    while(1) {

        /* 配置 PWM 的有效时间（高电平时间）50% ,周期 period1*/
        aw_pwm_config(AW_PWM_ID, period1 / 2, period1);
        aw_pwm_enable(AW_PWM_ID);      /* 使能通道 */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* 禁能通道  */
        aw_mdelay(250);


        /* 配置 PWM 的有效时间（高电平时间）2% ,周期 period1*/
        aw_pwm_config(AW_PWM_ID, period1 / 50, period1);
        aw_pwm_enable(AW_PWM_ID);      /* 使能通道 */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* 禁能通道  */
        aw_mdelay(250);


        /* 配置 PWM 的有效时间（高电平时间）50% ,周期 period2*/
        aw_pwm_config(AW_PWM_ID, period2 / 2, period2);
        aw_pwm_enable(AW_PWM_ID);      /* 使能通道 */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* 禁能通道  */
        aw_mdelay(250);


        /* 配置 PWM 的有效时间（高电平时间）2% ,周期 period2*/
        aw_pwm_config(AW_PWM_ID, period2 / 50, period2);
        aw_pwm_enable(AW_PWM_ID);      /* 使能通道 */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* 禁能通道  */
        aw_mdelay(250);
    }
}

/** [src_pwm] */

/* end of file */
