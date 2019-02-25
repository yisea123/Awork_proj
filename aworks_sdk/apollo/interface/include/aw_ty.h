/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief TTY驱动支持头文件
 *
 * \internal
 * \par modification history
 * - 1.00 15-06-20  deo, add aw_tydev_remove
 * - 1.02 12-12-08  orz, change type of size and nbytes to size_t.
 * - 1.00 12-10-19  orz, created
 * \endinternal
 */

#ifndef __AW_TY_H
#define __AW_TY_H

/*
 * \addtogroup grp_aw_ty
 * @{
 */

/*lint ++flb */

#include "aw_common.h"
#include "aw_rngbuf.h"
#include "aw_spinlock.h"
#include "aw_sem.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/**
 * \name serial ioctl option values
 * @{
 */

#define AW_OPT_ECHO     0x01    /**< \brief echo input */
#define AW_OPT_CRMOD    0x02    /**< \brief lf -> crlf */
#define AW_OPT_TANDEM   0x04    /**< \brief ^S/^Q flow control protocol */
#define AW_OPT_7_BIT    0x08    /**< \brief strip parity bit from 8 bit input */
#define AW_OPT_MON_TRAP 0x10    /**< \brief enable trap to monitor */
#define AW_OPT_ABORT    0x20    /**< \brief enable shell restart */
#define AW_OPT_LINE     0x40    /**< \brief enable basic line protocol */

#define AW_OPT_RAW      0       /**< \brief raw mode */

/** \brief terminal mode */
#define AW_OPT_TERMINAL     (AW_OPT_ECHO | AW_OPT_CRMOD | AW_OPT_TANDEM | \
                             AW_OPT_MON_TRAP | AW_OPT_7_BIT | AW_OPT_ABORT | AW_OPT_LINE)
/** @} */

/******************************************************************************/

/**
 * \name tty driver configurations
 * @{
 */
#define AW_CONFIG_SERIAL_SOFT_FLOW_CTRL /**< \brief 使能软流控模块 */
#define AW_CONFIG_SERIAL_THRESHOLD      /**< \brief 使能设置默认收发阈值 */
#define AW_CONFIG_SERIAL_LINE_MODE      /**< \brief 使能行读写模式 */
#define AW_CONFIG_SERIAL_PROTO_HOOK     /**< \brief 使能协议回调接口 */
#define AW_CONFIG_SERIAL_SYNC           /**< \brief 使能同步操作 */

#if 0
#define AW_CONFIG_SERIAL_FLOW_CTRL_TRACE/**< \brief 使能流控跟踪 */
#define AW_CONFIG_SERIAL_CANCELE        /**< \brief 使能支持取消操作 */
#define AW_CONFIG_SERIAL_SELECT         /**< \brief 使能select支持 */
#endif

#ifdef AW_CONFIG_SERIAL_LINE_MODE
#undef  MAX_INPUT
#define MAX_INPUT   64
#endif
/** @} */

/******************************************************************************/

/** \brief tty设备描述结构 */
struct aw_tydev {
    struct aw_rngbuf  rdbuf;            /**< \brief 读数据环形缓冲 */
    struct aw_rngbuf  wrbuf;            /**< \brief 写数据环形缓冲 */

    AW_MUTEX_DECL(mutex_sem);           /**< \brief 设备互斥信号量 */
#ifdef AW_CONFIG_SERIAL_SYNC
    int          rd_timeout;            /**< \brief 读数据超时时间 */
    AW_SEMB_DECL(rdsync_sem);           /**< \brief 读同步信号量 */
    AW_SEMB_DECL(wrsync_sem);           /**< \brief 写同步信号量 */
#endif

    /** \brief 读通道当前状态 */
    struct {
#ifdef AW_CONFIG_SERIAL_CANCELE
        unsigned char canceled;         /**< \brief 读操作已经取消 */
#endif
#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
        unsigned char xoff;             /**< \brief 输入已经被XOFF关掉了 */
        unsigned char pending;          /**< \brief XON/XOFF将在空闲时发送 */
#endif
        unsigned char flushing_rdbuf;   /**< \brief 清读缓冲的临界标志 */
    } rdstate;

    /** \brief 写通道状态 */
    struct {
#ifdef AW_CONFIG_SERIAL_CANCELE
        unsigned char canceled;         /**< \brief 写操作已经取消 */
#endif
        unsigned char busy;             /**< \brief 写通道是否忙（发送中） */
#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
        unsigned char xoff;             /**< \brief 输出已经被XOFF关掉了 */
#endif
#ifdef AW_CONFIG_SERIAL_LINE_MODE
        unsigned char cr;               /**< \brief 是否需要插入回车符 */
#endif
        unsigned char flushing_wrbuf;   /**< \brief 清写缓冲临界标志 */
        unsigned char wrbuf_busy;       /**< \brief 任务正在往缓冲写数据 */
    } wrstate;

#ifdef AW_CONFIG_SERIAL_LINE_MODE
    unsigned char   ln_nbytes;          /**< \brief 未接收完的行中字节数 */
    unsigned char   ln_bytes_left;      /**< \brief 没全部取走的行中剩余字节数*/
#endif

    unsigned short  options;            /**< \brief 设备行为控制 */

    /** \brief 启动发送的函数指针 */
    void (*pfunc_tx_start)(struct aw_tydev *p_tydev);

#ifdef AW_CONFIG_SERIAL_PROTO_HOOK
    /**
     * \brief 协议回调钩子函数
     *
     * 这个钩子函数在串行设备每收到一个字符时回调，用于各种串行协议的实现，
     * 如Modbus
     *
     * \param p_arg 回调参数
     * \param ch    接收到的字符
     *
     * \return      如果协议不需要驱动处理\a ch 则返回1，否则返回0
     */
    int  (*pfunc_proto_hook)(void *p_arg, char ch);
    /** \brief 协议回调参数 */
    void  *p_proto_arg;
#endif

#ifdef AW_CONFIG_SERIAL_SELECT
    /** \brief 调用select而阻塞在这个设备上的线程链表 */
    AW_SEL_WKUP_LIST_DECLARE(sel_wkup_list);
    /** \brief 设备打开计数器 */
    int num_open; /* todo: 使用原子类型？ */
#endif

    int wr_threshold;       /**< \brief 允许其它发送者发送的发送缓冲阈值 */

#ifdef AW_CONFIG_SERIAL_SOFT_FLOW_CTRL
    int xoff_threshold;     /**< \brief 发送XOFF的接收缓冲阈值 */
    int xon_threshold;      /**< \brief 发送XON的接收缓冲阈值 */
    /**
     * \brief 设备相关XOFF/XON回调
     * \param p_arg 回调参数
     * \param xoff  当前发送的是XOFF(1)还是XON(0)
     */
    void  (*pfunc_xoff_hook)(void *p_arg, int xoff);
    /** \brief 设备相关XOFF/XON回调参数 */
    void   *p_xoff_arg;
#endif

#if 0
    int     flags;  /**< \brief 设备标志 */
#endif

    aw_spinlock_isr_t   spinlock_isr; /**< \brief 可在中断中使用的spinlock */
};

aw_err_t aw_tylib_init (int xoff_percent, int xon_percent, int wr_threshold);

aw_err_t aw_tydev_init (struct aw_tydev *p_tydev,
                        char            *rd_buf,
                        size_t           rd_buf_size,
                        char            *wr_buf,
                        size_t           wr_buf_size,
                        void           (*pfunc_tx_start)(struct aw_tydev *));
aw_err_t aw_tydev_remove (struct aw_tydev *p_tydev);

aw_err_t aw_ty_int_tx (struct aw_tydev *p_tydev, char *p_char);
aw_err_t aw_ty_int_rd (struct aw_tydev *p_tydev, char inchar);

aw_err_t aw_ty_ioctl (struct aw_tydev *p_tydev, int request, void *p_arg);

ssize_t aw_ty_write(struct aw_tydev *p_tydev, const char *p_buf, size_t nbytes);
ssize_t aw_ty_read (struct aw_tydev *p_tydev, char *p_buf, size_t maxbytes);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* __AW_TY_H */

/* end of file */
