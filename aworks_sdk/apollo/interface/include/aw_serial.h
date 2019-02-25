/*******************************************************************************
*                                 AWorks
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
 * \brief 串口通讯标准接口
 *
 * 本模块提供串口读写，控制等服务
 *
 * 使用本模块需要包含头文件 aw_serial.h
 *
 * \par 简单示例
 * \code
 * aw_serial_write(COM0, "Hello!", 7);  // COM0输出"Hello!"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-29  orz, first implementation.
 * \endinternal
 */

#ifndef __AW_SERIAL_H
#define __AW_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_serial
 * \copydoc aw_serial.h
 * @{
 */

#include "aw_common.h"
#include "aw_sio_common.h"

/**
 * \name 串口索引
 * \brief 目前提供最多10个串口，从0开始编号
 * @{
 */
#define COM0    0
#define COM1    1
#define COM2    2
#define COM3    3
#define COM4    4
#define COM5    5
#define COM6    6
#define COM7    7
#define COM8    8
#define COM9    9
/** @} */

/**
 * \brief 串口设备控制
 *
 * - 这个函数处理所有的串口设备ioctl命令
 * - FIOBAUDRATE映射到了sio_ioct的SIO_BAUD_SET命令，其它所有的ioctl命令都直接
 *   传给了sio_ioctl函数
 *
 * \param[in] com     串口编号
 *
 * \param[in] request iotcl命令请求，参见 aw_ioctl.h 和 aw_sio_common.h ，
 *              可用的请求及参数如下：
 *              @arg AW_FIONREAD，可读数据个数，参数为int型指针
 *              @arg AW_FIONWRITE，已经写入的数据个数，参数为int型指针
 *              @arg AW_FIOFLUSH，清空输入和输出缓冲，无参数
 *              @arg AW_FIOSYNC，同FIOFLUSH
 *              @arg AW_FIODATASYNC，同FIOFLUSH
 *              @arg AW_FIOWFLUSH，清空写缓冲，无参数
 *              @arg AW_FIORFLUSH，清空读缓冲，无参数
 *              @arg AW_TIOCRDTIMEOUT，设置读等待超时时间，单位毫秒，参数为int整数
 *              @arg AW_TIOISATTY，检查设备是否TTY设置，无参数，TTY设备返回true值
 *              @arg SIO_BAUD_SET，设置串行设备的波特率，参数为波特率值，如9600
 *              @arg SIO_BAUD_GET，获取串行设备的波特率，参数为int型指针
 *              @arg SIO_MODE_SET，设置串行设备的模式，参数为：
 *                  - SIO_MODE_POLL，轮询模式
 *                  - SIO_MODE_INT，中断模式
 *              @arg SIO_MODE_GET，获取串行设备的当前模式，参数为int指针，值为
 *                  SIO_MODE_POLL 或 SIO_MODE_INT
 *              @arg SIO_AVAIL_MODES_GET，获取串行设备支持的模式，参数为int指针，
 *                  SIO_MODE_POLL 、 SIO_MODE_INT 或两者相“或”后的值
 *              @arg SIO_HW_OPTS_SET，设置串行设备的通讯参数，
 *                  支持的参数（这些参数可以相互“或”）：
 *                  - CLOCAL， 忽略Modem线状态，使用3线UART时必须使用这个参数
 *                  - CREAD，使能接收数据，默认已经使能
 *                  - 数据位数：
 *                      - CS5： 5位数据位
 *                      - CS6： 6位数据位
 *                      - CS7： 7位数据位
 *                      - CS8： 8位数据位
 *                  - STOPB，设置停止位个数，不设置就默认为1位，设置则为2位
 *                  - PARENB，奇偶校验使能设置，不设置则关闭奇偶校验，如设置则：
 *                      - PARENB：使能偶校验
 *                      - (PARENB | PARODD)：使能奇校验
 *              @arg SIO_HW_OPTS_GET，获取串行设备的通讯参数，参数为int指针，值
 *                  请参考 SIO_HW_OPTS_SET 可设置的值
 *
 * \param[in,out] p_arg   ioctl命令请求参数，参数类型和取值取决于对应的请求命令
 *
 * \return 返回值为错误编码，见 aw_errno.h 。具体取决于请求命令，典型返回值：
 *  - \b AW_OK     请求成功，没有错误
 *  - \b -EINVAL   com参数错误，com值超出系统可用串口数量
 *  - \b -ENODEV   com对应的串口设备没有找到（系统内部错误）
 *  - \b -EIO      设备执行命令失败，可能的原因为传给命令的参数不正确，
 *                 如设置设备波特率超出设备的可设置范围
 *  - \b -ENOSYS   该设备不支持这个命令请求
 *
 * \par 范例
 * \code
 * int baud;
 * aw_serial_ioctl(COM0, SIO_BAUD_SET, (void *)115200); // 设置波特率为115200bps
 * aw_serial_ioctl(COM0, SIO_BAUD_GET, (void *)baud);   // 获取当前波特率值
 * aw_serial_ioctl(COM0, AW_TIOCRDTIMEOUT, (void *)20);    // 设置读超时为20毫秒
 * // 设置串口参数：忽略modem线状态，8个数据位，1个停止位，使能奇校验
 * aw_serial_ioctl(COM0, SIO_HW_OPTS_SET, (void *)(CLOCAL | CS8 | PARENB));
 * \endcode
 */
aw_err_t aw_serial_ioctl (int com, int request, void *p_arg);

/**
 * \brief 向串口设备写入nbytes个字节数据
 *
 * 这个接口向串口设备写入nbytes个字节数据。若设备的内部缓冲不够，将做如下处理：
 * - 在异步模式下，剩余的数据不会被写入，返回值为已经写入的数据个数
 * - 在同步模式下（需在编译时打开该配置），调用会被阻塞直到所有的数据都被写入
 *
 * \param[in] com       串口编号
 * \param[in] p_buffer  要写入设备的数据缓冲区指针
 * \param[in] nbytes    要写入的字节个数
 *
 * \return 成功写入的数据个数，小于0为失败，失败原因可查看 errno
 */
ssize_t aw_serial_write (int com, const char *p_buffer, size_t nbytes);

/**
 * \brief 从串口设备读取maxbytes个字节数据
 *
 * - 这个接口从串口设备读入最多maxbytes个字节数据
 * - 若设备可读数据个数为0，将做如下处理：
 *   - 在异步模式下，立即返回
 *   - 在同步模式下（需在编译时打开该配置），调用会被阻塞直到有数据可读
 *
 * \param[in]  com      串口编号
 * \param[out] p_buffer 存放读取数据的缓冲区指针
 * \param[in]  maxbytes 最多要读取的字节个数
 *
 * \return 成功读取的数据个数，小于0为失败，失败原因可查看errno
 */
ssize_t aw_serial_read (int com, char *p_buffer, size_t maxbytes);

/**
 * \brief 轮询方式向串口设备写入nbytes个字节数据
 *
 * 这个接口以轮询方式向串口设备写入nbytes个字节数据
 *
 * \param[in] com       串口编号
 * \param[in] p_buffer  要写入设备的数据缓冲区指针
 * \param[in] nbytes    要写入的字节个数
 *
 * \return 成功写入的数据个数，小于0为失败，失败原因可查看errno
 */
ssize_t aw_serial_poll_write (int com, const char *p_buffer, size_t nbytes);

/**
 * \brief 以轮询方式从串口设备读取maxbytes个字节数据
 *
 * - 这个接口以轮询方式从串口设备读入最多maxbytes个字节数据
 * - 这个接口会死等直到读完所有数据
 *
 * \param[in]  com      串口编号
 * \param[out] p_buffer 存放读取数据的缓冲区指针
 * \param[in]  maxbytes 最多要读取的字节个数
 *
 * \return 成功读取的数据个数，小于0为失败，失败原因可查看errno
 */
ssize_t aw_serial_poll_read (int com, char *p_buffer, size_t maxbytes);

/** @} grp_aw_if_serial */

#ifdef __cplusplus
}
#endif

#endif /* __AW_SERIAL_H */

/* end of file */
