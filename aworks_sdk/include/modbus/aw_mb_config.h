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
 * \brief Modbus用户配置文件
 *
 * \internal
 * \par modification history
 * - 1.02 2015-05-13  cod, Modify for aworks1.0, fix code style
 * - 1.01 2012-12-04  liuweiyun, Modify for aworks1.0, fix code style
 * - 1.00 2012-05-13  ygy, first implementation
 * \endinternal
 */

#ifndef __AW_MB_CONFIG_H /* { */
#define __AW_MB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_mb_config
 * \copydoc aw_mb_config.h
 * @{
 */

/** \note 本文件所有配置为默认配置，生成库后，直接修改宏定义无效 */

/** \brief 从机通信模式配置 */
#define AW_MB_SERIAL_RTU_ENABLE    1   /**< \brief 串口RTU模式 */
#define AW_MB_SERIAL_ASCII_ENABLE  1   /**< \brief 串口ASCII模式 */
#define AW_MB_TCP_ENABLE           1   /**< \brief TCP/IP模式 */

/** \brief 主站通信模式配置 */
#define AW_MB_MASTER_RTU_ENABLE    1   /**< \brief 串口RTU模式 */
#define AW_MB_MASTER_ASCII_ENABLE  1   /**< \brief 串口ASCII模式 */
#define AW_MB_MASTER_TCP_ENABLE    1   /**< \brief TCP/IP模式 */

/**
 * \brief 串行最大ADU长度
 * - 该长度包括从机地址和检验数据长度
 * - 对于某些应用，可能不需要很长的一帧数据，可以考虑适当剪裁以降低RAM使用
 * - RTU模式长度为4~256， ASCII模式长度为3~255
 */
#define AW_MB_MAX_SER_PDU_LENGTH   256

/**
 * \brief 使能接收双缓冲（RTU和ASCII模式）
 * 如果使能该配置，将使用2*AW_MB_MAX_SER_PDU_LENGTH RAM空间来处理存放PDU数据帧。
 * 使用该功能，可以保证在第一帧处理超时，新一帧数据到来时，保证第二帧数据完整性
 */
#define AW_MB_SER_PDU_RECV_BUF_ENABLE  1

/**
 * \brief TCP模式下最大ADU长度
 * - 对于某些应用，可能不需要很长的一帧数据，可以考虑适当剪裁以降低RAM使用
 */
#define AW_MB_MAX_TCP_ADU_LENGTH   263

/**
 * \brief RTU模式T3.5时间设置（单位：微秒）
 * - 在RTU模式中，隐含着对t3.5（帧间延迟时间）引起的大量中断的处理，
 *   在较高的通信波特率下，这将导致CPU负担加重，
 *   因此当波特率小于或等于19200位/秒的情况下，必须严格遵守这两个定时
 * - 而当波特率大于19200位/秒时，应该使用固定值，建议帧间延迟时间设置为1.750ms
 * - 当使用ASCII模式时，不需要对该宏进行配置
 */
#define AW_MB_SERIAL_RTU_BAUDRATE_OVER_19200_FRAME_DELAY_US    1750ul

/**
 * \brief ASCII模式字符间超时设置
 * 在ASCII模式中，字符间超时时间没有固定，可以根据具体需求来设置
 */
#define AW_MB_ASCII_TIMEOUT_SEC    1

/**
 * \brief 用户可扩展注册的最大功能码个数
 * 配置使用aw_mb_slave_register_handler函数来注册功能码操作函数时可以注册最大个数
 */
#define AW_MB_FUNC_CODE_HANDLER_MAX    4

/**
 * \brief 从站是否使用硬件定时器(默认使用软件定时器)
 */
#define AW_MB_SLAVE_USED_HW_TIMER   1

/**
 * \brief 默认从站允许接收连接数（当超过默认连接数时，关闭最早建立的连接）
 */
#define AW_MB_SLAVE_TCP_CONNECT_NUM   4

/**
 * \brief 主站等待从站应答超时时间（毫秒）
 */
#define AW_MB_MASTER_TIMEOUT_MS_RESPOND  2000
#if ((AW_MB_MASTER_TIMEOUT_MS_RESPOND < 50)  ||\
     (AW_MB_MASTER_TIMEOUT_MS_RESPOND > 100000))
#error "AW_MB_MASTER_TIMEOUT_MS_RESPOND value must be in 50~100000ms"
#endif

/**
 * \brief 主站广播时的转换延迟时间（毫秒）
 */
#define AW_MB_MASTER_DELAY_MS_CONVERT   100

/**
 * \brief 主站用户可扩展注册的最大功能码个数
 * 配置使用aw_mb_master_funcode_register函数来注册功能码操作函数时可以注册最大个数
 */
#define AW_MB_MASTER_FUNCODE_HANDLER_MAX  4

/**
 * \brief TCP模式下单元标示符使用从站地址使能
 * - 对于某些应用，如Modbus服务器连接到串行链路，可使用单元标示符识别从站地址
 * - 若使能，单元标示符当做目标从站地址使用；若不使能，单元标示符值默认为0xFF
 */
#define AW_MB_TCP_UID_AS_SLAVEADDR   0

/**
 * \brief 主站TCP模式下，默认连接超时时间(ms)
 */
#define AW_MB_TCP_CONNECT_TIMEOUT    5000

#ifdef __cplusplus
}
#endif

/** @} grp_aw_if_mb_config */

#endif /* } __AW_MB_CONFIG_H */

/* end of file */
