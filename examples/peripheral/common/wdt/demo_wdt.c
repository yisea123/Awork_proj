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
 * \brief 看门狗（WDT）演示例程
 *
 * - 操作步骤:
 *   1. 需要在aw_prj_params.h中使能
 *      - 对应平台的内部看门狗 或 外部看门狗(AW_DEV_GPIO_WDT)；
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *   2. 这里演示的是AWorks软件看门狗用法，实际上只要使能看门狗设备宏，硬件看门狗系统会定时
 *      喂，但如果软件看门狗没有及时喂，那么系统就会停止喂硬件看门狗，从而导致系统被复位。
 *   3. 调试WDT程序时，不能打断点调试，否则会因为系统没有喂狗，导致复位。
 *
 * - 实验现象:
 *   1. 程序启动，串口打印"Add WDT device!"
 *   2. 每喂狗一次，打印"WDT Feed!"
 *   3. 若喂狗超时，程序复位，重新打印出"Add WDT device!".
 *
 * - 备注：
 *   1. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用；
 *   2. 外部看门狗使用后，为避免硬件复位，请屏蔽掉外部看门狗的宏。
 *
 * \par 源代码
 * \snippet demo_wdt.c src_wdt
 *
 * \internal
 * \par History
 * - 1.00 18-06-25  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_wdt
 * \copydoc demo_wdt.c
 */

/** [src_wdt] */
#include "aworks.h"     /* 此头文件必须被首先包含 */

/* 本程序用到了以下服务 */
#include "aw_delay.h"
#include "aw_wdt.h"
#include "aw_vdebug.h"
#include "aw_led.h"

#define WDT_TIMEOUT_MS     1000   /* 看门狗时间  */
#define FEED_TIME_MS       600    /* 喂狗时间  */

#define LED      0
/**
 * \brief WDT 例程
 * \return 无
 */
void demo_wdt_entry (void)
{
    struct awbl_wdt wdt_dev;
    aw_err_t  ret = AW_OK;

    /* 设置看门狗时间 */
    ret = aw_wdt_add(&wdt_dev, WDT_TIMEOUT_MS);
    if (ret != AW_OK) {
        AW_ERRF(("*ERR: WDT add error %d\n", ret));
        return;
    }

    AW_INFOF(("Add WDT device!\r\n"));
    AW_INFOF(("WDT timeout is %d ms!\r\n", WDT_TIMEOUT_MS));

    /* LED0 间隔闪烁 */
    while (1) {
        aw_wdt_feed(&wdt_dev);    /* 喂狗   */
        aw_mdelay(FEED_TIME_MS);
        aw_led_toggle(LED);
        AW_INFOF(("WDT Feed!\r\n"));
    }
}

/** [src_wdt] */

/* end of file */
