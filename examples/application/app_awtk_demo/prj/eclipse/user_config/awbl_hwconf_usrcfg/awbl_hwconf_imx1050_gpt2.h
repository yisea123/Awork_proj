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
 * \brief AWBus-lite iMX1050 GPT 配置文件
 *
 * iMX1050 GPT 为 iMX1050 系列 MCU 的通用定时器，提供如下功能:
 *  - 周期性中断（即定时器）
 *  - 输入捕获
 *  - 输出比较
 *
 * 对应的功能配置见 awbl_imx1050_gpt_devinfo_t 类型，给出了如下示例配置，
 * 通过宏 #__GPT_FOR_TIMER、__GPT_FOR_INPUT 及 __GPT_FOR_OUTPUT 来进行功能选择。
 *
 * - 配置成通用定时器的时候，只需要将 mode 设置为 IMX1050_GPT_MODE_TIMER，
 *   特性、通道以及输出比较值不需要配置，填 0 即可；
 *
 * - 配置成输入捕获的时候，需要将 mode 设置为 IMX1050_GPT_MODE_INPUT，
 *   然后需要填入输出特性，如上升沿触发、下降沿触发或是双边沿触发，
 *   通道选择（输入通道1或2），输出比较值不需要配置，填 0 即可；
 *
 * - 配置成输出比较的时候，需要将 mode 设置为 IMX1050_GPT_MODE_OUTPUT，
 *   然后需要填入输出特性，如输出翻转、输出置位或是输出清零；
 *   通道选择（输出通道1、2或3），以及输出比较值。（特性宏见 imx1050_gpt_regs.h）
 *
 * \internal
 * \par modification history
 * - 1.00 2017-11-10  pea, first implementation
 * \endinternal
 */

#ifndef  __AWBL_HWCONF_IMX1050_GPT2_H
#define  __AWBL_HWCONF_IMX1050_GPT2_H

#ifdef AW_DEV_IMX1050_GPT2

#include "aw_int.h"
#include "driver/timer/awbl_imx1050_gpt.h"

#define __GPT2_FOR_TIMER     /**< \brief 配置 GPT 为定时器模式 */
//#define __GPT2_FOR_INPUT     /**< \brief 配置 GPT 为输入捕获模式 */
//#define __GPT2_FOR_OUTPUT    /**< \brief 配置 GPT 为输出比较模式 */

/**
 * \brief 配置 GPT 使用的通道
 *
 * 定时器模式时，通道配置无效；
 * 输入捕获模式时，通道可配置为 1 或者 2；
 * 输出比较模式时，通道可配置为 1、2 或者 3。
 */
#define __GPT2_CHAN  3

/** \brief GPT2 引脚信息 */
aw_local aw_const uint32_t __gpt2_gpios[5][2] = {
    {GPIO3_27, GPIO3_27_GPT2_CAPTURE1},
    {GPIO3_26, GPIO3_26_GPT2_CAPTURE2},
    {GPIO1_6, GPIO1_6_GPT2_COMPARE1},
    {GPIO1_7, GPIO1_7_GPT2_COMPARE2},
    {GPIO1_8, GPIO1_8_GPT2_COMPARE3}
};

/** \brief GPT2 平台初始化函数 */
aw_local void __imx1050_gpt2_plfm_init (void)
{
#if defined __GPT2_FOR_INPUT
    int gpt2_gpios[] = {__gpt2_gpios[__GPT2_CHAN - 1][0]};

    if (aw_gpio_pin_request("gpt2_gpios",
                             gpt2_gpios,
                             AW_NELEMENTS(gpt2_gpios)) == AW_OK) {

        /* 配置功能引脚 */
        aw_gpio_pin_cfg(__gpt2_gpios[__GPT2_CHAN - 1][0],
                        __gpt2_gpios[__GPT2_CHAN - 1][1]);
    }
#elif defined __GPT2_FOR_OUTPUT
    int gpt2_gpios[] = {__gpt2_gpios[__GPT2_CHAN + 1][0]};

    if (aw_gpio_pin_request("gpt2_gpios",
                             gpt2_gpios,
                             AW_NELEMENTS(gpt2_gpios)) == AW_OK) {

        /* 配置功能引脚 */
        aw_gpio_pin_cfg(__gpt2_gpios[__GPT2_CHAN + 1][0],
                        __gpt2_gpios[__GPT2_CHAN + 1][1]);
    }
#endif
}

#if defined  __GPT2_FOR_TIMER

/** \brief GPT2 设备信息 */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* 通过名称分配定时器 */
    IMX1050_GPT2_BASE,              /* 寄存器基地址 */
    INUM_GPT2,                      /* 中断号 */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* 时钟 ID */
    IMX1050_GPT_MODE_TIMER,         /* 定时器功能 */
    0,                              /* 无特性 */
    0,                              /* 不使用输入输出通道 */
    0,                              /* 无输出比较值 */
    __imx1050_gpt2_plfm_init        /* 平台初始化函数 */
};
/* __GPT_FOR_TIMER */

#elif defined  __GPT2_FOR_INPUT

/** \brief GPT2 设备信息 */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* 通过名称分配定时器 */
    IMX1050_GPT2_BASE,              /* 寄存器基地址 */
    INUM_GPT2,                      /* 中断号 */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* 时钟 ID */
    IMX1050_GPT_MODE_INPUT,         /* 输入捕获模式 */
    IMX1050_GPT_INPUT_FALL,         /* 输入下降沿触发 */
    __GPT2_CHAN,                    /* 通道 */
    0,                              /* 无输出比较值 */
    __imx1050_gpt2_plfm_init        /* 平台初始化函数 */
};
/* __GPT2_FOR_INPUT */

#elif defined  __GPT2_FOR_OUTPUT

/** \brief 设备信息 */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* 通过名称分配定时器 */
    IMX1050_GPT2_BASE,              /* 寄存器基地址 */
    INUM_GPT2,                      /* 中断号 */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* 时钟 ID */
    IMX1050_GPT_MODE_OUTPUT,        /* 输出比较模式 */
    IMX1050_GPT_OUTPUT_TOG,         /* 输出翻转 */
    __GPT2_CHAN,                    /* 通道 */
    0x0000FFFF,                     /* 输出比较值 */
    __imx1050_gpt2_plfm_init,       /* 平台初始化函数 */
};
#endif /* __GPT2_FOR_OUTPUT */

/** \brief 设备实例内存静态分配 */
aw_local struct awbl_imx1050_gpt_dev __g_imx1050_gpt2_dev;

#define AWBL_HWCONF_IMX1050_GPT2    \
    {                               \
        AWBL_IMX1050_GPT_DRV_NAME,  \
        IMX1050_GPT2_BUSID,         \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_imx1050_gpt2_dev.dev,  \
        &__g_imx1050_gpt2_param     \
    },

#else
#define AWBL_HWCONF_IMX1050_GPT2

#endif  /* AW_DEV_IMX1050_GPT2 */

#endif  /* __AWBL_HWCONF_IMX1050_GPT2_H */

/* end of file */
