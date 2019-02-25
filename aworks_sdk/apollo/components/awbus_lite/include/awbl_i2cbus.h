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
 * \brief AWBus I2C总线接口头文件
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * #include "awbl_i2cbus.h"
 * \endcode
 * 本模块为 I2C 总线的精简版实现
 *
 * 更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-10  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_I2CBUS_H
#define __AWBL_I2CBUS_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "aw_list.h"
#include "aw_i2c.h"         /* 通用I2C接口文件 */
#include "aw_sem.h"
#include "aw_spinlock.h"

/** \brief 永久等待 */
#define AWBL_I2C_WAITFOREVER    (AW_SEM_WAIT_FOREVER)

/** \biref 得到I2C从机设备的父控制器 */
#define AWBL_I2C_PARENT_GET(p_dev) \
    ((struct awbl_i2c_master *) \
        (((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))

/** \biref 得到I2C从机设备的父控制器编号 */
#define AWBL_I2C_PARENT_BUSID_GET(p_dev) \
        (((struct awbl_i2c_master_devinfo *) \
            AWBL_DEVINFO_GET( \
                ((struct awbl_dev *)(p_dev))->p_parentbus->p_ctlr))->bus_index)

struct awbl_i2c_master;

/** \biref AWBus I2C 总线控制器 (I2C 主机) 设备信息 (平台配置部分) */
struct awbl_i2c_master_devinfo {

    /** \brief 控制器所对应的总线编号 */
    uint8_t     bus_index;

    /** \brief 控制器总线速度 */
    uint32_t    speed;

    /** \brief 超时, 单位 ms，永久等待： #AWBL_I2C_WAITFOREVER */
    int          timeout;
};


/** \biref AWBus I2C 总线控制器 (I2C 主机) 设备信息 (驱动配置部分) */
struct awbl_i2c_master_devinfo2 {

    uint16_t    features;       /**< 控制器的特性(支持的传输控制标志)  */

    /** \brief 启动传输 */
    aw_err_t (*pfunc_xfer_startup)(struct awbl_i2c_master *p_master);
};

/** \biref I2C bus 从机设备驱动注册信息结构体 */
typedef struct awbl_i2c_drvinfo {
    struct awbl_drvinfo super;  /**< \brief 继承自 AWBus 设备驱动信息 */
} awbl_i2c_drvinfo_t;

/** \brief AWBus I2C 总线设备 (I2C从机) 实例 */
struct awbl_i2c_device {
    struct awbl_dev super;      /**< \brief 继承自 AWBus 设备 */
};

/** \brief AWBus I2C 总线控制器 (I2C主机) 实例 */
struct awbl_i2c_master {
    struct awbl_busctlr super;      /**< \brief 继承自 AWBus 总线控制器 */
    struct awbl_i2c_master *p_next; /**< \brief 指向下一个 I2C 控制器 */


    /** \brief I2C 控制器相关信息 (驱动配置部分) */
    const struct awbl_i2c_master_devinfo2 *p_devinfo2;

    /** \brief 设备锁 */
    aw_spinlock_isr_t lock_dev;

    /** \brief I2C 控制器消息队列 */
    struct aw_list_head msg_list;

    /** \brief 设备互斥量 */
    AW_MUTEX_DECL(dev_mux);

    /** \brief 消息内存分配 (aw_i2c_read() 等函数使用此内存) */
    struct aw_i2c_message msg;

    /** \brief 传输内存分配 (aw_i2c_read() 等函数使用此内存) */
    struct aw_i2c_transfer trans[2];

    /** \brief 子地址内存分配 (aw_i2c_read() 等函数使用此内存) */
    uint8_t subaddr[4];
};

/** \brief 锁定控制器 */
#define AWBL_I2C_MASTER_LOCK(p_master) \
    aw_spinlock_isr_take(&((struct awbl_i2c_master *)p_master)->lock_dev)

/** \brief 解除控制器锁定 */
#define AWBL_I2C_MASTER_UNLOCK(p_master) \
    aw_spinlock_isr_give(&((struct awbl_i2c_master *)p_master)->lock_dev)

/**
 * \brief 添加一条 message 到控制器传输列表末尾
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline void awbl_i2c_msg_in (struct awbl_i2c_master *p_master,
                                         struct aw_i2c_message *p_msg)
{
    aw_list_add_tail((struct aw_list_head *)(&p_msg->ctlrdata),
                     &p_master->msg_list);
}

/**
 * \brief 从控制器传输列表表头取出一条 message
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline struct aw_i2c_message *
    awbl_i2c_msg_out (struct awbl_i2c_master *p_master)
{
    if (aw_list_empty_careful(&p_master->msg_list)) {
        return NULL;
    } else {
        struct aw_list_head *p_node = p_master->msg_list.next;
        aw_list_del(p_node);
        return aw_list_entry(p_node, struct aw_i2c_message, ctlrdata);
    }
}

/**
 * \brief 取消指定的 message (从队列中移除此 message)
 *
 * 只有消息尚未被处理时才可以被取消
 *
 * \retval  AW_OK       成功
 * \retval  AW_ERROR    失败，message正在被处理
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline aw_err_t awbl_i2c_msg_cancel (struct aw_i2c_message *p_msg)
{
    if ((p_msg->status == -ENOTCONN) ||
        (p_msg->status == -EISCONN)) {

        aw_list_del((struct aw_list_head *)p_msg->ctlrdata);
        return AW_OK;
    }

    return AW_ERROR;
}

/**
 * \brief 检查控制器传输列表是否为空
 * \attention 调用此函数必须锁定控制器
 */
aw_local aw_inline int awbl_i2c_msg_empty (struct awbl_i2c_master *p_master)
{
    return aw_list_empty_careful(&p_master->msg_list);
}

/**
 * \brief AWBus i2c 总线模块初始化函数
 *
 * \attention 本函数应当在 awbus_lite_init() 之后、awbl_dev_init1() 之前调用
 */
void awbl_i2cbus_init(void);

/**
 * \brief 创建 AWBus I2C 总线实例以及枚举总线上的设备
 *
 * 本接口提供给 AWBus I2C 总线控制器(主机设备)驱动使用
 *
 */
aw_err_t awbl_i2cbus_create(struct awbl_i2c_master *p_master);

/**
 * \brief 处理消息、异步模式
 *
 * 本接口提供给 AWBus I2C 从设备驱动使用
 *
 * 以异步的方式处理消息，消息的处理状态和结果反映在 p_msg->status。
 * 消息处理结束(成功、超时或出错)时，将会调用 p_msg->pfunc_complete 并传递
 * 参数 p_msg->p_arg。
 *
 * \param[in]       p_dev   AWBus I2C 从设备实例
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval  AW_OK       消息排队成功，等待处理
 * \retval  -EINVAL     参数错误
 *
 * 成功处理的传输个数反映在 p_msg->done_num
 *
 * 消息的处理状态和结果反映在 p_msg->status ：
 *
 *      \li  -ENOTCONN       消息尚未排队
 *      \li  -EISCONN        消息正在排队处理
 *      \li  -EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果 (可通过 p_msg->done_num 定位出错的传输)
 *      \li  AW_OK           所有传输成功处理
 *      \li  -ENOTSUP        某次传输的控制标志不支持
 *      \li  -ETIME          超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                           设置超时时间
 *      \li  -ENODEV         某次传输的目标地址无应答
 *      \li  -ENOENT         某次传输发送的数据无应答
 *      \li  -EIO            传输消息时发生总线错误、总线仲裁失败过多等错误
 *      \li  -ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 */
aw_err_t awbl_i2c_async(struct awbl_i2c_device *p_dev,
                        struct aw_i2c_message  *p_msg);

/**
 * \brief 处理消息、同步模式
 *
 * 本接口提供给 AWBus I2C 从设备驱动使用
 *
 * 以同步的方式处理消息，消息的处理状态和结果反映在 p_msg->status。
 * 参数 p_msg->pfunc_complete 和 p_msg->p_arg 由控制器使用。
 *
 * \param[in]       p_dev   AWBus I2C 从设备实例
 * \param[in,out]   p_msg   要处理的消息
 *
 * 函数的返回值如下：
 * \retval AW_OK        消息处理成功
 * \retval -AW_EINVAL   参数错误，p_msg 中某些成员参数无效，请检查
 * \retval -ENOTSUP     消息中某些传输设置的 特性不支持
 *                      (例如, AW_I2C_M_IGNORE_NAK)
 * \retval -ETIME       超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                      设置超时时间
 * \retval -ENODEV      某次传输的目标地址无应答
 * \retval -ENOENT      某次传输发送的数据无应答
 * \retval -EIO         传输消息时发生总线错误、总线仲裁失败过多等错误
 * \retval -ECANCELED   因控制器出错或处理队列满，消息被取消，可稍后再试
 *
 * 成功处理的传输个数反映在 p_msg->done_num
 *
 * 消息的处理状态和结果反映在 p_msg->status ：
 *
 *      \li  -ENOTCONN       消息尚未排队
 *      \li  -EISCONN        消息正在排队处理
 *      \li  -EINPROGRESS    消息正在被处理
 * 下面为消息处理完毕的结果 (可通过 p_msg->done_num 定位出错的传输)
 *      \li  AW_OK           所有传输成功处理
 *      \li  -ENOTSUP        某次传输的控制标志不支持
 *      \li  -ETIME          超时，消息未在设定的时间内处理
 *      \li  -ENODEV         某次传输的目标地址无应答
 *      \li  -ENOENT         某次传输发送的数据无应答
 *      \li  -EIO            传输消息时发生总线错误、总线仲裁失败过多等错误
 *      \li  -ECANCELED      因控制器出错或处理队列满，消息被取消，可稍后再试
 */
aw_err_t awbl_i2c_sync(struct awbl_i2c_device *p_dev,
                       struct aw_i2c_message  *p_msg);

/**
 * \brief 读I2C从机数据
 *
 * 本接口提供给 AWBus I2C 从设备驱动使用
 *
 * \param[in]  p_dev    AWBus I2C从机设备实例， 见 \ref struct awbl_i2c_device
 * \param[in]  flags    从机设备属性，见“I2C从设备属性标志 (aw_i2c.h)”
 * \param[in]  addr     从机设备地址，7位或10位
 * \param[in]  subaddr  器件内子地址，从此地址开始读取数据，若 flags 设置子地址
 *                      宽度为0 (AW_I2C_SUBADDR_NONE), 则此参数不起作用
 * \param[out] p_buf    数据缓冲区，读取的数据存放于此
 * \param[in]  nbytes   要写入的数据个数
 *
 * \retval AW_OK        读取成功
 * \retval -ENXIO       未找到从设备所在主机
 * \retval -EFAULT      p_buf 为 NULL
 * \retval -AW_EINVAL   参数错误，nbytes 为 0
 * \retval -ENOTSUP     flags 中某些特性不支持 (例如, AW_I2C_IGNORE_NAK)
 * \retval -ETIME       超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                      设置超时时间
 * \retval -ENODEV      从机地址无应答(若 flags 设置了 AW_I2C_IGNORE_NAK,
 *                      则不会产生此错误)
 * \retval -ENOENT      数据无应答(若 flags 设置了 AW_I2C_IGNORE_NAK,
 *                      则不会产生此错误)
 * \retval -EIO         读写数据时发生总线错误、总线仲裁失败过多等错误
 * \retval -ECANCELED   因控制器出错，读写操作被取消，可稍后再试
 *
 * \par 范例
 * \code
 *  uint8_t read_buf[16];
 *
 *  awbl_i2c_read((struct awbl_i2c_device *)p_dev,  // AWBus 从设备实例
 *                 AW_I2C_ADDR_7BIT |
 *                 AW_I2C_SUBADDR_1BYTE,  // 7-bit 器件地址 1-byte 器件内子地址
 *                 0x50,                 // 器件地址，0x50
 *                 0,                    // 器件内子地址，0x00
 *                 p_buf,                // 读缓冲区
 *                 16);                  // 读取数据长度，16字节
 * \endcode
 */
aw_err_t awbl_i2c_read(struct awbl_i2c_device *p_dev,
                       uint16_t                flags,
                       uint16_t                addr,
                       uint32_t                subaddr,
                       void                   *p_buf,
                       size_t                  nbytes);

/**
 * \brief 写数据到I2C从机
 *
 * 本接口提供给 AWBus I2C 从设备驱动使用
 *
 * \param[in]  p_dev    AWBus I2C从机设备实例， 见 \ref struct awbl_i2c_device
 * \param[in]  flags    从机设备属性，见“I2C从设备属性标志 (aw_i2c.h)”
 * \param[in]  addr     从机设备地址，7位或10位
 * \param[in]  subaddr  器件内子地址，从此地址开始读取数据，若 flags 设置子地址
 *                      宽度为0 (AW_I2C_SUBADDR_NONE), 则此参数不起作用
 * \param[out] p_buf    数据缓冲区，要写入的数据存放于此
 * \param[in]  nbytes   要写入的数据个数
 *
 * \retval AW_OK        读取成功
 * \retval -ENXIO       未找到从设备所在主机
 * \retval -EFAULT      p_buf 为 NULL
 * \retval -AW_EINVAL   参数错误，nbytes 为 0
 * \retval -ENOTSUP     flags 中某些特性不支持 (例如, AW_I2C_IGNORE_NAK)
 * \retval -ETIME       超时，消息未在设定的时间内处理，在控制器的devinfo中
 *                      设置超时时间
 * \retval -ENODEV      从机地址无应答(若 flags 设置了 AW_I2C_IGNORE_NAK,
 *                      则不会产生此错误)
 * \retval -ENOENT      数据无应答(若 flags 设置了 AW_I2C_IGNORE_NAK,
 *                      则不会产生此错误)
 * \retval -EIO         读写数据时发生总线错误、总线仲裁失败过多等错误
 * \retval -ECANCELED   因控制器出错，读写操作被取消，可稍后再试
 *
 * \par 范例
 * \code
 *  uint8_t write_buf[16];
 *
 *  awbl_i2c_write((struct awbl_i2c_device *)p_dev,  // AWBus 从设备实例
 *                  AW_I2C_ADDR_7BIT |
 *                  AW_I2C_SUBADDR_1BYTE,  // 7-bit 器件地址 1-byte 器件内子地址
 *                  0x50,                 // 器件地址，0x50
 *                  0,                    // 器件内子地址，0x00
 *                  p_buf,                // 读缓冲区
 *                  16);                  // 读取数据长度，16字节
 * \endcode
 */
aw_err_t awbl_i2c_write(struct awbl_i2c_device *p_dev,
                        uint16_t                flags,
                        uint16_t                addr,
                        uint32_t                subaddr,
                        const void             *p_buf,
                        size_t                  nbytes);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_I2CBUS_H */

/* end of file */
