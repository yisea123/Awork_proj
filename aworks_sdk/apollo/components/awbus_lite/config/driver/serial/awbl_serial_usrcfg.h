/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 外部使用的配置文件
 *
 * 用户在此文件中对串口模块的相关参数进行配置
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-31  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_SERIAL_USRCFG_H
#define __AWBL_SERIAL_USRCFG_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \brief 系统串行端口个数
 *
 * 当前支持的最大端口个数为10个，应该根据实际的硬件配置修改。
 * 配置的端口个数不应该超过10个。
 */
#define AW_NUM_COM      		2

/**
 * \name 串行端口的收发缓冲大小配置
 * \brief 不用的串行端口（编号超过AW_NUM_COM）的配置不起作用。
 * @{
 */

#define AW_COM0_TX_BUF_SIZE     128 /**< \brief COM0 发送缓冲大小 */
#define AW_COM0_RX_BUF_SIZE     128 /**< \brief COM0 接收缓冲大小 */

#define AW_COM1_TX_BUF_SIZE     128 /**< \brief COM1 发送缓冲大小 */
#define AW_COM1_RX_BUF_SIZE     128 /**< \brief COM1 接收缓冲大小 */

#define AW_COM2_TX_BUF_SIZE     128 /**< \brief COM2 发送缓冲大小 */
#define AW_COM2_RX_BUF_SIZE     128 /**< \brief COM2 接收缓冲大小 */

#define AW_COM3_TX_BUF_SIZE     128 /**< \brief COM3 发送缓冲大小 */
#define AW_COM3_RX_BUF_SIZE     128 /**< \brief COM3 接收缓冲大小 */

#define AW_COM4_TX_BUF_SIZE     128 /**< \brief COM4 发送缓冲大小 */
#define AW_COM4_RX_BUF_SIZE     128 /**< \brief COM4 接收缓冲大小 */

#define AW_COM5_TX_BUF_SIZE     128 /**< \brief COM5 发送缓冲大小 */
#define AW_COM5_RX_BUF_SIZE     128 /**< \brief COM5 接收缓冲大小 */

#define AW_COM6_TX_BUF_SIZE     128 /**< \brief COM6 发送缓冲大小 */
#define AW_COM6_RX_BUF_SIZE     128 /**< \brief COM6 接收缓冲大小 */

#define AW_COM7_TX_BUF_SIZE     128 /**< \brief COM7 发送缓冲大小 */
#define AW_COM7_RX_BUF_SIZE     128 /**< \brief COM7 接收缓冲大小 */

#define AW_COM8_TX_BUF_SIZE     128 /**< \brief COM8 发送缓冲大小 */
#define AW_COM8_RX_BUF_SIZE     128 /**< \brief COM8 接收缓冲大小 */

#define AW_COM9_TX_BUF_SIZE     128 /**< \brief COM9 发送缓冲大小 */
#define AW_COM9_RX_BUF_SIZE     128 /**< \brief COM9 接收缓冲大小 */

/** @} */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_SERIAL_USRCFG_H */

/* end of file */
