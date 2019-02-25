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
 * \brief 串口演示例程，轮询模式
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *   2. 使用本例程时，若开启shell (AW_COM_SHELL_SERIAL)，则shell所使用不能为COM0(因为shell会读取串口数据)
 *
 * - 实验现象：
 *   1. 串口首先打印"Hello,Enter Serial Poll Mode:"；
 *   2. 然后串口进入轮询读模式（阻塞）等待数据输入，上位机通过串口发送10个数据，开发板把接收到的数据返回给上位机 (10次)；
 *
 * - 备注：
 *   1. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_serial.c src_serial
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_serial_poll
 * \copydoc demo_serial_poll.c
 */

/** [src_serial_poll] */
#include "aworks.h"

#include "aw_delay.h"
#include "aw_serial.h"
#include "aw_ioctl.h"

#define  TEST_SERIAL_NUM   COM0

/**
 * \brief 串口 demo（轮询模式）
 * \return 无
 */
void demo_serial_poll_entry (void)
{
    char    buf[32];
    int     len = 0;
    int     i   = 0;

    /* 串口初始化配置 波特率115200 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_BAUD_SET, (void *)115200);

    /* 串口参数 ：8个数据位 1个停止位，无奇偶校验 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_HW_OPTS_SET, (void *)(CS8 | CLOCAL | CREAD));

    /* 串口模式 ：查询模式 发送字符串 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_MODE_SET, (void *)SIO_MODE_POLL);
    aw_serial_poll_write(TEST_SERIAL_NUM, "Hello,Enter Serial Poll Mode:\r\n", 32);

    for(i = 0; i < 10; i++) {
        len = aw_serial_poll_read(TEST_SERIAL_NUM, buf, 10);
        if (len > 0) {
            aw_serial_poll_write(TEST_SERIAL_NUM, buf, len);
        }
        aw_serial_poll_write(TEST_SERIAL_NUM, "\r\n", 2);
    }

    return ;
}
/** [src_serial_poll] */

/* end of file */
