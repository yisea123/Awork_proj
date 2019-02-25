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
 * \brief RTC演示例程，使用aw_rtc_timespec_set和aw_rtc_timespec_get接口
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台和对应编号的I2C
 *      - AW_DEV_EXTEND_PCF85063
 *      - AW_COM_CONSOLE
 *      注意：如果初始化失败，查看配置文件是否是引脚配置冲突，如果是，在aw_prj_params.h中关闭不使用的宏
 *   2. 将板子中的DURX、DUTX通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *   3. 由于系统中RTC为单实例，因而只能开启一个RTC外设
 *
 * - 实验现象：
 *   1. 设定好初始时间，通过串口可以观察时间和日期相关信息，1秒更新1次数据。
 *
 * \par 源代码
 * \snippet demo_rtc_timespec.c src_rtc_timespec
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rtc_timespec
 * \copydoc demo_rtc_timespec.c
 */

/** [src_rtc_timespec] */
#include "aworks.h"     /* 该头文件必须首先被包含 */

#include "aw_delay.h"
#include "aw_rtc.h"
#include "aw_vdebug.h"
#include "aw_prj_params.h"

//#define RTC_ID    RTC_ID0        /* PCF85063 RTC */
#define RTC_ID    RTC_ID1      /* 核心板内部RTC */

/**
 * \brief RTC演示例程入口
 * \return 无
 */
void demo_rtc_timespec_entry (void)
{
    aw_timespec_t timespec; /* 日历时间 */

    /* 定义细分时间 */
    aw_tm_t tm = {
        0,                  /* seconds after the minute     - [0, 59] */
        0,                  /* minutes after the hour       - [0, 59] */
        15,                 /* hours after midnight         - [0, 23] */
        14,                 /* day of the month      - [1, 31] */
        8 - 1,              /* months since January  - [0, 11] */
        2018 - 1900         /* years since 1900                */
    };

    aw_tm_to_time(&tm, &timespec.tv_sec);     /* 细分转换为日历时间 */
    timespec.tv_nsec = 0;                     /* 纳秒部分置0 */

    aw_rtc_timespec_set(RTC_ID, &timespec);   /* 设置RTC日历时间 */

    while(1) {

        aw_rtc_timespec_get(RTC_ID, &timespec);  /* 获取RTC日历时间 */
        aw_time_to_tm(&timespec.tv_sec, &tm);    /* 将读出来的日历时间转换为细分时间 */

        aw_kprintf("current time is: %d-%d-%d  %02d:%02d:%02d.%d\n",
                    tm.tm_year + 1900,
                    tm.tm_mon + 1,
                    tm.tm_mday,
                    tm.tm_hour,
                    tm.tm_min,
                    tm.tm_sec,
                    timespec.tv_nsec / 1000000);
        aw_mdelay(1);
    }
}
/** [src_rtc_timespec] */

/* end of file */
