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
 * \brief RTC演示例程，使用aw_rtc_time_set和aw_rtc_time_get接口
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
 * \snippet demo_rtc_std.c src_rtc_std
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rtc_std
 * \copydoc demo_rtc_std.c
 */

/** [src_rtc_std] */
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
void demo_rtc_std_entry (void)
{
    aw_err_t ret = AW_OK;

    /* 定义起始时间 */
    aw_tm_t tm = {
        0,                      /* second */
        30,                     /* minute */
        12,                     /* hour   */
        30,                     /* day of the month      */
        8 - 1,                  /* months since January  */
        2017 - 1900,            /* years since 1900      */
    };

    ret = aw_rtc_time_set(RTC_ID, &tm);    /* 设置起始时间 */
    if (ret != AW_OK) {
        AW_ERRF(("RTC set error: %d\n", ret));
    }

    while (1) {

        ret = aw_rtc_time_get (RTC_ID, &tm);    /* 得到细分时间 */

        if (ret != AW_OK) {
            AW_INFOF(("rtc 操作失败 %d \r\n", ret));
        } else {
            /* 打印细分时间 */
            AW_INFOF(("current time: %s\n",
                      asctime((const struct tm *)&tm)));
        }

        aw_mdelay(1000);
    }
}

/** [src_rtc_std] */

/* end of file */
