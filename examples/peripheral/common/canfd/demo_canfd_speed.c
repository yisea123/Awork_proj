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
 * \brief CANFD控制器演示例程
 * \note  本例程进行单发、单收的速度测试。
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      AW_COM_CONSOLE、
 *      CAN、UART。
 *   2. 连接CANFD的相关引脚到CANFD收发器 RX=>RX TX=>TX，
 *      收发器再接到USBCANFD设备上 H=>H L=>L，
 *      CANFD仲裁域波特率1000K 数据域波特率5000K。
 *   3. 打开串口调试终端，波特率115200-8-N-1。
 *
 * - 实验现象：
 *   1. __CAN_TEST_MODE = __CAN_TEST_MSG_RECV
 *      则打开ZCANPRO上位机连接启动设备后，设置不断的发送报文，
 *      达到100000帧后，进行统计接收速度。
 *   2. __CAN_TEST_MODE = __CAN_TEST_MSG_SEND
 *      则打开ZCANPRO上位机连接启动设备后，会不断的收取报文，
 *      发送达到100000帧，进行统计发送速度。
 *   3. 串口打印相关调试信息。
 *
 * \par 源代码
 * \snippet demo_canfd_speed.c src_fd_can
 *
 * \internal
 * \par Modification History
 * - 1.00 18-09-18  anu, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_fd_can
 * \copydoc demo_canfd_speed.c
 */

/** [src_fd_can] */

#include "aworks.h"
#include "string.h"
#include "aw_can.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_spinlock.h"
#include "aw_system.h"
#include "aw_prj_params.h"

#define __CAN_CHN                  0      /* CAN通道 */
#define __CAN_RECV_MSG_TIMEOUT     10     /* CAN报文接收超时时间 */
#define __CAN_SEND_MSG_TIMEOUT     300    /* CAN报文发送超时时间 */
#define __CAN_MSG_CNT              32     /* CAN消息个数 */

#define __CAN_TASK_STACK_SIZE      4096   /* CAN报文接收任务堆栈大小 */
#define __CAN_TASK_PRIO            6      /* CAN报文接收任务优先级 */

#define __CAN_TEST_MSG_CNT         100000 /* CAN共收发多少帧才进行统计 */

#define __CAN_TEST_MSG_RECV        0      /* CAN单发速度测试 */
#define __CAN_TEST_MSG_SEND        1      /* CAN单收速度测试 */
#define __CAN_TEST_MODE            __CAN_TEST_MSG_SEND /* CAN测试模式选择 */

#undef AW_INFOF
#define AW_INFOF(x) aw_kprintf("CANFD%d : ", __CAN_CHN); aw_kprintf x

/* CAN总线状态 */
static volatile aw_can_bus_status_t __g_can_bus_status = AW_CAN_BUS_STATUS_OK;

static aw_can_fd_baud_param_t __g_can_btr = {
    AW_CFG_CANFD_NOMINAL_BTR_1000K,
    AW_CFG_CANFD_DATA_BTR_5000K
};

/******************************************************************************/
static uint32_t __can_timestamp_get_cb (uint32_t timestamp);
static bool_t __can_err_sta_cb (
    int chn, aw_can_bus_err_t err, aw_can_bus_status_t status);

static aw_can_app_callbacks_t __g_can_app_callback_fun = {
    __can_timestamp_get_cb,
    NULL,
    NULL,
    __can_err_sta_cb,
    NULL
};

/**
 * \brief 时间戳获取的回调函数
 *
 * \param[in] timestamp 当前报文的时间戳
 *
 * \return 用户修改后的时间戳
 */
static uint32_t __can_timestamp_get_cb (uint32_t timestamp)
{
    return timestamp;
}

/**
 * \brief 错误状态的回调函数
 *
 * \param[in] chn 通道号
 * \param[in] err CAN 总线的错误类型
 * \param[in] status CAN 总线的状态
 *
 * \retval TRUE  不保存消息到接收rngbuf
 * \retval FALSE 保存消息到接收rngbuf
 */
static bool_t __can_err_sta_cb (
    int chn, aw_can_bus_err_t err, aw_can_bus_status_t status)
{
    aw_can_err_cnt_t  can_err_reg;

    aw_can_err_cnt_get(chn, &can_err_reg);
    if ((can_err_reg.tx_err_cnt > 127) || (can_err_reg.rx_err_cnt > 127)) {
        aw_can_err_cnt_clr(chn);
    }

    __g_can_bus_status = status;

    return TRUE; /* 函数返回值决定错误消息是否存入rngbuf,TRUE:不保存,FALSE:保存 */
}

/**
 * \brief CAN初始化
 *
 * \param[in] 无
 *
 * \return AW_CAN_ERR_NONE正常启动其他错误请参考错误代码
 */
static aw_can_err_t __can_startup (void)
{
    aw_can_err_t ret;

    /** \brief 初始化CAN */
    ret = aw_can_init(__CAN_CHN,                           /* CAN通道号*/
                      AW_CAN_WORK_MODE_NORMAL,             /* 控制器工作模式*/
                      (aw_can_baud_param_t *)&__g_can_btr, /* 当前波特率*/
                      &__g_can_app_callback_fun);          /* 用户回调函数*/

    AW_INFOF(("controller init...\n"));

    if (ret != AW_CAN_ERR_NONE) {
        goto exit;
    }

    /** \brief 启动CAN */
    ret = aw_can_start(__CAN_CHN);
    AW_INFOF(("controller start!\n"));

exit:
    return ret;
}

/**
 * \brief CAN任务入口
 *
 * \param[in] p_arg 任务参数
 *
 * \return 无
 */
#if __CAN_TEST_MODE == __CAN_TEST_MSG_SEND
static void __can_task_entry (void *p_arg)
{
    uint32_t            i;
    aw_tick_t           t1, t2;
    aw_can_err_t        ret;
    aw_spinlock_isr_t   lock;
    aw_can_bus_status_t bus_status;         /* CAN bus总线状态 */
    uint32_t            total_send_cnt = 0; /* 总共发送的个数 */
    uint32_t            send_done_cnt  = 0; /* 发送完成个数 */
    aw_can_fd_msg_t     msg[__CAN_MSG_CNT]; /* CANFD信息缓冲区 */

    ret = __can_startup();

    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        goto exit;
    }

    aw_spinlock_isr_init(&lock, 0);

    /* 配置发送的参数 */
    memset(msg, 0x00, sizeof(msg));
    for (i = 0; i < __CAN_MSG_CNT; i++) {
        msg[i].can_msg.length = 64;

        /* 设置发送的消息为CANFD报文，使能波特率切换 */
        msg[i].can_msg.flags = AW_CAN_MSG_FLAG_FD_CTRL | AW_CAN_MSG_FLAG_BRS;
    }

    AW_FOREVER {

        if (t1 == 0) {
            t1 = aw_sys_tick_get();
        }

        /* 发送CANFD报文 */
        ret = aw_can_fd_msgs_send(__CAN_CHN,
                                  msg,
                                  __CAN_MSG_CNT,
                                  &send_done_cnt,
                                  __CAN_SEND_MSG_TIMEOUT);

        total_send_cnt += send_done_cnt;

        if (total_send_cnt >= __CAN_TEST_MSG_CNT) {

            t2 = aw_sys_tick_get() - t1;

            AW_INFOF(("send total cnt:%d tick:%d, speed:%d frame/s\n",
                      total_send_cnt,
                      t2,
                      (uint32_t)((uint64_t)total_send_cnt * 1000 / t2)));

            t1 = 0;
            total_send_cnt = 0;
        }

        aw_spinlock_isr_take(&lock);
        bus_status = __g_can_bus_status;
        __g_can_bus_status = AW_CAN_BUS_STATUS_OK;
        aw_spinlock_isr_give(&lock);

        if (bus_status == AW_CAN_BUS_STATUS_OFF) {

            /* 停止CAN */
            aw_can_stop(__CAN_CHN);
            AW_INFOF(("controller stop!\n"));

            /* 启动CAN */
            aw_can_start(__CAN_CHN);
            AW_INFOF(("controller start!\n"));
        }
    }

exit:
    AW_FOREVER {
        aw_mdelay(1000);
    }
}
#else
static void __can_task_entry (void *p_arg)
{
    aw_can_err_t        ret;
    aw_spinlock_isr_t   lock;
    aw_tick_t           t1 = 0, t2 = 0;
    aw_can_bus_status_t bus_status;         /* CAN bus总线状态 */
    uint32_t            recv_fifo_size = 0; /* CAN FIFO大小 */
    uint32_t            recv_cnt       = 0; /* 一次接收的个数 */
    uint32_t            recv_done_cnt  = 0; /* 接收完成个数 */
    uint32_t            total_recv_cnt = 0; /* 共接收的个数 */
    aw_can_fd_msg_t     msg[__CAN_MSG_CNT]; /* CANFD信息缓冲区 */

    ret = __can_startup();

    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        goto exit;
    }

    aw_spinlock_isr_init(&lock, 0);

    /* 获取接收FIFO大小 */
    recv_fifo_size = aw_can_rcv_fifo_size(__CAN_CHN);

    AW_INFOF(("receive fifo size %d messages.\n", recv_fifo_size));

    recv_cnt = min(recv_fifo_size, __CAN_MSG_CNT);

    AW_INFOF(("receive cnt %d messages.\n", recv_cnt));

    AW_FOREVER {

        /* 接收CANFD报文 */
        ret = aw_can_fd_msgs_rcv(__CAN_CHN,
                                 msg,
                                 recv_cnt,
                                 &recv_done_cnt,
                                 __CAN_RECV_MSG_TIMEOUT);

        if ((ret == AW_CAN_ERR_NONE) && (recv_done_cnt > 0)) {
            if (t1 == 0) {
                t1 = aw_sys_tick_get();
            }

            total_recv_cnt += recv_done_cnt;

            if (total_recv_cnt >= __CAN_TEST_MSG_CNT) {

                t2 = aw_sys_tick_get() - t1;

                AW_INFOF(("recv total cnt:%d tick:%d, speed:%d frame/s\n",
                          total_recv_cnt,
                          t2,
                          (uint32_t)((uint64_t)total_recv_cnt * 1000 / t2)));

                t1 = 0;
                total_recv_cnt = 0;
            }
        }

        aw_spinlock_isr_take(&lock);
        bus_status = __g_can_bus_status;
        __g_can_bus_status = AW_CAN_BUS_STATUS_OK;
        aw_spinlock_isr_give(&lock);

        if (bus_status == AW_CAN_BUS_STATUS_OFF) {

            /* 停止CAN */
            aw_can_stop(__CAN_CHN);
            AW_INFOF(("controller stop!\n"));

            /* 启动CAN */
            aw_can_start(__CAN_CHN);
            AW_INFOF(("controller start!\n"));
        }
    }

exit:
    AW_FOREVER {
        aw_mdelay(1000);
    }
}
#endif

/**
 * \brief 建立CAN任务
 *
 * \param[in] 无
 *
 * \return 无
 */
void demo_canfd_speed (void)
{
    AW_TASK_DECL_STATIC(task, __CAN_TASK_STACK_SIZE);

    AW_TASK_INIT(task,
                 "can_task",
                 __CAN_TASK_PRIO,
                 __CAN_TASK_STACK_SIZE,
                 __can_task_entry,
                 (void *)0);

    AW_TASK_STARTUP(task);
}

/** [src_fd_can] */

/* end of file */
