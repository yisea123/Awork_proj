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
 * \brief 串口演示例程，rx中断回调演示
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *   2. 使用本例程时，若开启shell (AW_COM_SHELL_SERIAL)，则shell所使用不能为COM0(因为shell会读取串口数据)
 *
 * - 实验现象：
 *   1.启动demo后，串口输入数据，在rx回调函数中检测数据，舍弃收到的'A',保留其他。
 *
 * - 备注：
 *   1. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_serial_rx_callback.c src_serial_rx_callback
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_serial_rx_callback
 * \copydoc demo_serial_rx_callback.c
 */

/** [src_serial_rx_callback] */
#include "aworks.h"

#include "aw_delay.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_led.h"
#include "aw_vdebug.h"

#define  TEST_SERIAL_NUM   COM0

/**
 * \brief 接收中断回调函数
 * \param p_arg 回调参数
 * \param ch    接收到的字符
 *
 * \return      如果协议不需要驱动处理\a ch 则返回1，否则返回0
 */
aw_local int  __rx_callback(void *p_arg, char ch){

    if(ch == 'A'){

        /*返回1， 如果是字符'A'，舍弃*/
        return 1;
    }else{

        /*返回0，如果不是字符'A',保留*/
        return 0;
    }

}
/**
 * \brief 串口 demo(rx中断)
 * \return 无
 */
void demo_serial_rx_callback_entry (void)
{
    char    buf[32];
    int     len = 0;

    /* 串口初始化配置 波特率115200 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_BAUD_SET, (void *)115200);

    /* 串口参数 ：8个数据位 1个停止位，无奇偶校验 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_HW_OPTS_SET, (void *)(CS8 | CLOCAL | CREAD));

    // 清空串口输入输出缓冲区
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_FIOFLUSH, NULL);

    // 设置串口读取超时时间
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOCRDTIMEOUT, (void *)10);

    // 设置为中断模式
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_MODE_SET, (void *)SIO_MODE_INT);

    //设置rx中断回调函数
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOPROTOHOOK,(void *) __rx_callback);

    //设置rx中断回调函数参数
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOPROTOARG, NULL);

    AW_FOREVER{
        len = aw_serial_read(TEST_SERIAL_NUM,buf,sizeof(buf));
        aw_serial_write(TEST_SERIAL_NUM,buf,len);
    }

    return ;
}
/** [src_serial_rx_callback] */

/* end of file */
