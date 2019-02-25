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
 * \brief AWorks 标准I2C接口
 *
 * 使用本服务需要包含头文件 aw_i2c.h
 *
 * \par 简单示例
 * \code
 * #include "aw_i2c.h"
 *
 * aw_i2c_device_t dev;                     // 设备描述
 * uint8_t         read_buf[16];            // 读缓存区
 *
 * // 生成从机设备
 * aw_i2c_mkdev(&dev,
 *              I2C0,
 *              0x50,
 *              AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE);
 *
 * // 写入数据到从器件子地址0开始的16个字节
 * aw_i2c_write(&dev, 0, &write_buf[0], 16);
 *
 * // 从器件子地址0开始读16个字节
 * aw_i2c_read(&dev, 0, &read_buf[0], 16);
 * \endcode
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.01 12-11-16  zen, add aw_i2c_async() and aw_i2c_sync()
 * - 1.00 12-07-27  orz, first implementation
 * \endinternal
 */

#ifndef __AW_I2C_H
#define __AW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \addtogroup grp_aw_if_i2c
 * \copydoc aw_i2c.h
 * @{
 */

/**
 * \name I2C传输控制标志
 * @{
 * 定义I2C传输的地址类型、读写类型、特殊控制等标志
 *
 * 这些标志相“或”之后的结果用于给结构体成员
 * <code>aw_i2c_transfer::flags</code>赋值，未显式给出的标志将使用默认值。
 * 例如，下面的这些赋值将得到不同的控制效果：
 * \code
 * aw_i2c_transfer_t trans;
 * trans.flags = 0;             // 7-bit从机地址(默认)、写操作(默认)
 * trans.flags = AW_I2C_M_WR;   // 7-bit从机地址(默认)、写操作
 * trans.flags = AW_I2C_M_RD;   // 7-bit从机地址(默认)、读操作
 * trans.flags = AW_I2C_M_10BIT | AW_I2C_M_RD;   // 10-bit从机地址、读操作
 *
 * trans.flags = AW_I2C_M_7BIT |
 *               AW_I2C_M_WR |
 *               AW_I2C_M_IGNORE_NAK;// 7-bit从机地址、写操作、忽略无应答错误
 * \endcode
 *
 * \sa struct aw_i2c_transfer
 */
#define AW_I2C_M_7BIT          0x0000u     /**< \brief 7-bit设备地址(默认) */
#define AW_I2C_M_10BIT         0x0001u     /**< \brief 10-bit设备地址 */
#define AW_I2C_M_WR            0x0000u     /**< \brief 写操作(默认) */
#define AW_I2C_M_RD            0x0002u     /**< \brief 读操作 */
#define AW_I2C_M_NOSTART       0x0004u     /**< \brief 不发送 start 条件 */
#define AW_I2C_M_REV_DIR_ADDR  0x0008u     /**< \brief 读写标志位反转 */
#define AW_I2C_M_RECV_LEN      0x0010u     /**< \brief 暂时不支持 */

/** \brief 忽略所有无应答错误 (包括从机地址无应答和数据无应答) */
#define AW_I2C_M_IGNORE_NAK    0x0020u

/** \brief 在读操作中接收数据时不发送应答 */
#define AW_I2C_M_NO_RD_ACK     0x0040u

/** \brief I2C传输控制标志掩码 */
#define AW_I2C_M_MASK          0x00FFu

/** @} */


/**
 * \name I2C从设备属性标志
 * @{
 * 定义I2C从机地址类型、器件内子地址类型和器件内子地址宽度等标志
 *
 * 例如，下面的这些赋值将定义不同的从设备属性：
 * \code
 * aw_i2c_device_t dev;
 * dev.flags = 0;                    // 7-bit 从机地址、无子地址
 * dev.flags = AW_I2C_SUBADDR_1BYTE;  // 7-bit 从机地址、1字节子地址
 * dev.flags = AW_I2C_SUBADDR_2BYTE;  // 7-bit 从机地址、2字节子地址、
 *                                   // 子地址高位地址先传输
 *
 * dev.flags = AW_I2C_SUBADDR_2BYTE |
 *             AW_I2C_SUBADDR_LSB_FIRST; // 7-bit 从机地址、2字节子地址、
 *                                      // 子地址低位字节先传输
 *
 * \endcode
 *
 * \sa struct aw_i2c_device
 */

/** \brief 7位地址模式(默认模式) */
#define AW_I2C_ADDR_7BIT         AW_I2C_M_7BIT

/** \brief 10位地址模式 */
#define AW_I2C_ADDR_10BIT        AW_I2C_M_10BIT

/** \brief 忽略设备的无应答 */
#define AW_I2C_IGNORE_NAK        AW_I2C_M_IGNORE_NAK

/** \brief 器件内子地址高位字节先传输(默认)*/
#define AW_I2C_SUBADDR_MSB_FIRST 0x0000u

/** \brief 器件内子地址低位字节先传输 */
#define AW_I2C_SUBADDR_LSB_FIRST 0x0100u

#define AW_I2C_SUBADDR_NONE      0x0000u  /**< \brief 无子地址(默认) */
#define AW_I2C_SUBADDR_1BYTE     0x1000u  /**< \brief 子地址宽度1字节 */
#define AW_I2C_SUBADDR_2BYTE     0x2000u  /**< \brief 子地址宽度2字节 */

/** \brief 从标志控制字中取得子地址宽度 */
#define AW_I2C_SUBADDR_LEN_GET(flags)  (((flags) & 0xF000) >> 12)

/** @} */

/** \brief I2C从设备描述结构 */
typedef struct aw_i2c_device {
    /** \brief 从机设备 */
    uint8_t     busid;

    uint16_t    addr;       /**< \brief 从机设备地址，7位或10位 */
    uint16_t    flags;      /**< \brief 从机设备属性，见“I2C从设备属性标志”*/
} aw_i2c_device_t;

/** \brief I2C 传输 (推荐使用 aw_i2c_mktrans() 设置本数据结构) */
typedef struct aw_i2c_transfer {
    uint16_t    addr;   /**< \brief 器件地址 */
    uint16_t    flags;  /**< \brief 传输控制标志，见“I2C传输控制标志”*/
    uint8_t    *p_buf;  /**< \brief 数据缓冲区 */
    size_t      nbytes; /**< \brief 数据个数 */
} aw_i2c_transfer_t;

/** \brief I2C 消息 (推荐使用 aw_i2c_mkmsg() 设置本数据结构) */
typedef struct aw_i2c_message {
    struct aw_i2c_transfer *p_transfers;    /**< \brief 组成消息的传输 */
    uint16_t                trans_num;      /**< \brief 请求处理的传输个数 */
    uint16_t                done_num;       /**< \brief 成功处理的传输个数 */

    aw_pfuncvoid_t  pfunc_complete; /**< \brief 传输完成回调函数 */
    void           *p_arg;          /**< \brief 传递给 pfunc_complete 的参数 */
    int             status;         /**< \brief 消息的状态 */
    void           *ctlrdata[2];    /**< \brief 控制器使用 */
} aw_i2c_message_t;

/**
 * \brief 设置I2C设备结构体参数
 *
 * \param[out] p_dev  I2C从机设备描述符指针
 * \param[in]  busid  从机设备所属
 * \param[in]  addr   从机设备地址
 * \param[in]  flags  从机设备标志，见“I2C从设备属性标志”
 *
 * \par 范例
 * \code
 * #include "aw_i2c.h"
 *
 * aw_i2c_device_t cat1025; // CAT1025从设备描述结构
 *
 * // 初始化CAT1025设备描述结构：位于I2C0控制器，设备地址0x50，
 * // 寄存器地址为1字节宽
 * aw_i2c_mkdev(&cat1025,
 *              I2C0,
 *              0x50,
 *              AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE);
 * \endcode
 */
aw_local aw_inline void aw_i2c_mkdev (aw_i2c_device_t *p_dev,
                                      uint8_t          busid,
                                      uint16_t         addr,
                                      uint16_t         flags)
{
    p_dev->busid = busid;
    p_dev->addr  = addr;
    p_dev->flags = flags;
}

/**
 * \brief 设置I2C传输结构体参数
 *
 * \param[in]  p_trans   I2C传输描述符指针
 * \param[in]  addr      目标器件地址
 * \param[in]  flags     传输控制标志，见“I2C传输控制标志”
 * \param[out] p_buf     数据缓冲区
 * \param[in]  nbytes    传输数据个数
 *
 * \par 范例
 * 见 aw_i2c_mkmsg()
 */
aw_local aw_inline void aw_i2c_mktrans (aw_i2c_transfer_t *p_trans,
                                        uint16_t           addr,
                                        uint16_t           flags,
                                        uint8_t           *p_buf,
                                        size_t             nbytes)
{
    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf;
    p_trans->nbytes = nbytes;
}

/**
 * \brief 设置I2C消息结构体参数
 *
 * \param[in,out] p_msg             I2C消息描述符指针
 * \param[in]     p_transfers       组成消息的“I2C传输”
 * \param[in]     trans_num         “I2C传输”的个数
 * \param[in]     pfunc_complete    传输完成回调函数(仅调用 aw_i2c_async() 时此参数有效,
 *                                  调用 aw_i2c_sync()时本参数无效)
 * \param[in]     p_arg             传递给回调函数的参数
 *
 * \par 范例
 * \code
 * #include "aw_i2c.h"
 *
 * aw_i2c_message_t msg;        // 消息描述结构体
 * aw_i2c_transfer_t trans[2];  // 传输描述结构
 * uint8_t data0[16]            // 数据缓冲区 0
 * uint8_t data1[16];           // 数据缓冲区 1
 *
 * // 设置传输描述结构体
 * aw_i2c_mktrans(&trans[0],    // 传输描述结构 0
 *                0x50,         // 要传输的目标器件(从机)地址
 *                AW_I2C_M_7BIT | AW_I2C_M_WR，// 7-bit从机地址、写操作
 *                1,            // 数据长度，1字节
 *                &data0[0]);   // 数据缓冲区 0
 *
 * aw_i2c_mktrans(&trans[1],    // 传输描述结构 1
 *                0x50,         // 要传输的目标器件(从机)地址
 *                AW_I2C_M_7BIT | AW_I2C_M_RD，// 7-bit从机地址、读操作
 *                16,           // 数据长度，16字节
 *                &data1[0]);   // 数据缓冲区1
 *
 * // 设置消息描述结构体
 * aw_i2c_mkmsg(&msg,           // 消息描述结构
 *              &trans[0],      // 组成消息的传输
 *              2,              // 传输个数
 *              my_callback,    // 传输完成回调函数
 *              my_arg);        // 传输完成回调函数的参数
 *
 * \endcode
 */
aw_local aw_inline void aw_i2c_mkmsg (aw_i2c_message_t  *p_msg,
                                      aw_i2c_transfer_t *p_transfers,
                                      uint16_t           trans_num,
                                      aw_pfuncvoid_t     pfunc_complete,
                                      void              *p_arg)
{
    p_msg->p_transfers    = p_transfers;
    p_msg->trans_num      = trans_num;
    p_msg->done_num       = 0;
    p_msg->pfunc_complete = pfunc_complete;
    p_msg->p_arg          = p_arg;
    p_msg->status         = -ENOTCONN;
}

/**
 * \brief 读I2C从机数据
 *
 * \param[in]  p_dev       I2C从机设备描述符
 * \param[in]  subaddr     器件内子地址，从此地址开始读取数据，
 *                         若\a p_dev->flags 设置子地址宽度为0
 *                         (#AW_I2C_SUBADDR_NONE), 则此参数不起作用
 * \param[out] p_buf       数据缓冲区，读取的数据存放于此
 * \param[in]  nbytes      要写入的数据个数
 *
 * \retval AW_OK           读取成功
 * \retval -AW_ENXIO       未找到\a p_dev->masterid 所指定的主机
 * \retval -AW_EFAULT      \a p_buf 为 NULL
 * \retval -AW_AW_EINVAL   参数错误，\a nbytes 为 0
 * \retval -AW_ENOTSUP     \a p_dev->flags 中某些特性不支持
 *                         (例如, #AW_I2C_IGNORE_NAK)
 * \retval -AW_ETIME       超时
 * \retval -AW_ENODEV      从机地址无应答(若\a p_dev->flags 设置了
 *                         #AW_I2C_IGNORE_NAK, 则不会产生此错误)
 * \retval -AW_ENOENT      数据无应答(若\a p_dev->flags 设置了 #AW_I2C_IGNORE_NAK,
 *                         则不会产生此错误)
 * \retval -AW_EIO         读写数据时发生总线错误、总线仲裁失败过多等错误
 * \retval -AW_ECANCELED   因控制器出错，读写操作被取消，可稍后再试
 *
 * \par 范例
 * \code
 * #include "aw_i2c.h"
 *
 * aw_i2c_device_t dev;                     // 设备描述
 * uint8_t         read_buf[16];            // 读缓存区
 *
 * aw_i2c_mkdev(&dev,
 *              I2C0,
 *              0x50,
 *              AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE);
 *
 * aw_i2c_read(&dev, 0, &read_buf[0], 16);  // 从器件子地址0开始读16个字节
 * \endcode
 */
aw_err_t aw_i2c_read(aw_i2c_device_t  *p_dev,
                     uint32_t          subaddr,
                     uint8_t          *p_buf,
                     size_t            nbytes);

/**
 * \brief 写数据到I2C从机
 *
 * \param[in]  p_dev       I2C从机设备描述符
 * \param[in]  subaddr     器件内子地址，从此地址开始写入数据，
 *                         若\a p_dev->flags 设置子地址宽度为0
 *                         (#AW_I2C_SUBADDR_NONE), 则此参数不起作用
 * \param[out] p_buf       数据缓冲区，要写的数据存放于此
 * \param[in]  nbytes      要写入的数据个数
 *
 * \retval AW_OK           写入成功
 * \retval -AW_ENXIO       未找到\a p_dev->masterid 所指定的主机
 * \retval -AW_EFAULT      \a p_buf 为 NULL
 * \retval -AW_AW_EINVAL   参数错误，nbytes 为 0
 * \retval -AW_ENOTSUP     \a p_dev->flags 中某些特性不支持
 *                         (例如, #AW_I2C_IGNORE_NAK)
 * \retval -AW_ETIME       超时
 * \retval -AW_ENODEV      从机地址无应答(若\a p_dev->flags 设置了
 *                         #AW_I2C_IGNORE_NAK, 则不会产生此错误)
 * \retval -AW_ENOENT      数据无应答(若\a p_dev->flags 设置了 #AW_I2C_IGNORE_NAK,
 *                         则不会产生此错误)
 * \retval -AW_EIO         读写数据时发生总线错误、总线仲裁失败过多等错误
 * \retval -AW_ECANCELED   因控制器出错，读写操作被取消，可稍后再试
 *
 * \par 范例
 * \code
 * #include "aw_i2c.h"
 *
 * aw_i2c_device_t dev;                     // 设备描述
 * uint8_t         write_buf[16];           // 写缓存区
 *
 * aw_i2c_mkdev(&dev,
 *              I2C0,
 *              0x50,
 *              AW_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE);
 *
 * // 写入数据到从器件子地址0开始的16个字节
 * aw_i2c_write(&dev, 0, &write_buf[0], 16);
 * \endcode
 */
aw_err_t aw_i2c_write(aw_i2c_device_t  *p_dev,
                      uint32_t          subaddr,
                      const void       *p_buf,
                      size_t            nbytes);

/**
 * \brief 处理消息、异步模式
 *
 * 以异步的方式处理消息，消息的处理状态和结果反映在\a p_msg->status。
 * 消息处理结束(成功、超时或出错)时，将会调用\a p_msg->pfunc_complete 并传递
 * 参数\a p_msg->p_arg。
 *
 * \param[in]       busid   要操作的I2C总线编号
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval  AW_OK       消息排队成功，等待处理
 * \retval  -AW_EINVAL     参数错误
 *
 * 成功处理的传输个数反映在\a p_msg->done_num
 *
 * 消息的处理状态和结果反映在\a p_msg->status ：
 *
 *      \li  -AW_ENOTCONN       消息尚未排队
 *      \li  -AW_EISCONN        消息正在排队处理
 *      \li  -AW_EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果 (可通过\a p_msg->done_num 定位出错的传输)
 *      \li  AW_OK              所有传输成功处理
 *      \li  -AW_ENOTSUP        某次传输的控制标志不支持
 *      \li  -AW_ETIME          超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                              设置超时时间
 *      \li  -AW_ENODEV         某次传输的目标地址无应答
 *      \li  -AW_ENOENT         某次传输发送的数据无应答
 *      \li  -AW_EIO            传输消息时发生总线错误、总线仲裁失败过多等错误
 *      \li  -AW_ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * \par 示例
 * \code
 *  #include "aw_i2c.h"
 *  #include "aw_sem.h"
 *
 *  aw_i2c_message_t  msg;
 *  aw_i2c_transfer_t trans[2];
 *  uint8_t           subaddr;
 *  uint8_t           data[EEPROM_PAGE_SIZE];
 *  int               i;
 *
 *  // 定义并初始化信号量
 *  AW_SEMB_DECL_STATIC(sem_sync);
 *  AW_SEMB_INIT(sem_sync, 0, AW_SEM_Q_PRIORITY);
 *
 *  // 写EEPROM子地址0x00开始的一个页 (时序请参考数据手册)
 *
 *  // 第1个传输发送子地址
 *  subaddr = 0x00;
 *  aw_i2c_mktrans(&trans[0],
 *                 EEPROM_ADDR,                 // 目标器件地址
 *                 AW_I2C_M_7BIT | AW_I2C_M_WR, // 7-bit器件地址, 写操作
 *                 &subaddr,                    // 子地址
 *                 1);                          // 子地址长度，1byte
 *
 *  // 第2个传输发送数据
 *  for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
 *      data[i] = i;
 *  }
 *  aw_i2c_mktrans(&trans[1],
 *                 EEPROM_ADDR,                 // 目标器件地址 (将被忽略)
 *
 *                 // 写操作, 不发送起始信号及从机地址
 *                 AW_I2C_M_WR | AW_I2C_M_NOSTART,
 *
 *                 &data[0],                    // 数据缓冲区
 *                 EEPROM_PAGE_SIZE);           // 数据个数
 *
 *  // 将传输组成消息
 *  aw_i2c_mkmsg(&msg,
 *               &trans[0],
 *               2,
 *               eeprom_callback,
 *               &sem_sync);
 *
 *  // 处理此消息，异步
 *  aw_i2c_async(I2C0, &msg);
 *
 *  // 等待消息处理完成
 *  aw_semb_take(&sem_sync, AW_SEM_WAIT_FOREVER);
 *
 *  // 读EEPROM子地址0x00开始的一个页  (时序请参考数据手册)
 *
 *  // 第1个传输发送子地址
 *  subaddr = 0x00;
 *  aw_i2c_mktrans(&trans[0],
 *                 EEPROM_ADDR,                 // 目标器件地址
 *                 AW_I2C_M_7BIT | AW_I2C_M_WR, // 7-bit器件地址, 写操作
 *                 &subaddr,                    // 子地址
 *                 1);                          // 子地址长度，1byte
 *
 *  // 第2个传输接收数据
 *  for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
 *      data[i] = 0;
 *  }
 *  aw_i2c_mktrans(&trans[1],
 *                 EEPROM_ADDR,                 // 目标器件地址
 *                 AW_I2C_M_7BIT | AW_I2C_M_RD, // 7-bit器件地址, 读操作
 *                 &data[0],                    // 数据缓冲区
 *                 EEPROM_PAGE_SIZE);           // 数据个数
 *
 *  // 将传输组成消息
 *  aw_i2c_mkmsg(&msg,
 *               &trans[0],
 *               2,
 *               NULL,
 *               NULL);
 *
 *  // 处理此消息，同步
 *  aw_i2c_sync(EEPROM_BUSID, &msg);
 *
 *  // 校验数据是否正确
 *
 *  for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
 *      if (data[i] != i) {
 *          return AW_ERROR;
 *      }
 *  }
 *
 *  return AW_OK;
 * \endcode
 */
aw_err_t aw_i2c_async(uint8_t           busid,
                      aw_i2c_message_t *p_msg);

/**
 * \brief 处理消息、同步模式
 *
 * 以同步的方式处理消息，消息的处理状态和结果反映在\a p_msg->status。
 * 参数\a p_msg->pfunc_complete 和\a p_msg->p_arg 由控制器使用。
 *
 * \param[in]       busid   要操作的I2C总线编号
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval AW_OK           消息处理成功
 * \retval -AW_EINVAL      参数错误，\a p_msg 中某些成员参数无效，请检查
 * \retval -AW_ENOTSUP     消息中某些传输设置的 特性不支持
 *                         (例如, #AW_I2C_M_IGNORE_NAK)
 * \retval -AW_ETIME       超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                         设置超时时间
 * \retval -AW_ENODEV      某次传输的目标地址无应答
 * \retval -AW_ENOENT      某次传输发送的数据无应答
 * \retval -AW_EIO         传输消息时发生总线错误、总线仲裁失败过多等错误
 * \retval -AW_ECANCELED   因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * 成功处理的传输个数反映在\a p_msg->done_num
 *
 * 消息的处理状态和结果反映在\a p_msg->status ：
 *
 *      \li  -AW_ENOTCONN       消息尚未排队
 *      \li  -AW_EISCONN        消息正在排队处理
 *      \li  -AW_EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果 (可通过\a p_msg->done_num 定位出错的传输)
 *      \li  AW_OK              所有传输成功处理
 *      \li  -AW_ENOTSUP        某次传输的控制标志不支持
 *      \li  -AW_ETIME          超时，消息未在设定的时间内处理
 *      \li  -AW_ENODEV         某次传输的目标地址无应答
 *      \li  -AW_ENOENT         某次传输发送的数据无应答
 *      \li  -AW_EIO            传输消息时发生总线错误、总线仲裁失败过多等错误
 *      \li  -AW_ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 * \par 示例
 * 请参考 aw_i2c_async()
 */
aw_err_t aw_i2c_sync(uint8_t           busid,
                     aw_i2c_message_t *p_msg);

/** @} grp_aw_if_i2c */

#ifdef __cplusplus
}
#endif

#endif /* __AW_I2C_H */

/* end of file */
