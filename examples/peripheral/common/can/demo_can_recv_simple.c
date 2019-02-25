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
 * \brief 高速CAN控制器接收例程
 *
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      AW_COM_CONSOLE、
 *      CAN、UART。
 *   2. 连接CAN的相关引脚到CAN收发器 RX=>RX TX=>TX，
 *      收发器再接到USBCAN-II设备上 H=>H L=>L, CAN波特率500K。
 *   3. 打开串口调试终端，波特率115200-8-N-1。
 *
 * - 实验现象：
 *   1. 打开cantest上位机发送报文， 串口打印出相关接收信息。
 *
 * \par 源代码
 * \snippet demo_can.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 1.00 18-09-18  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_can_simple_recv
 * \copydoc demo_can_simple_recv.c
 */

/** [src_can_simple_recv] */

#include "aworks.h"
#include "string.h"
#include "aw_can.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_spinlock.h"
#include "aw_prj_params.h"

#define __CAN_CHN                  0     /* CAN通道 */
#define __CAN_RECV_MSG_TIMEOUT     10    /* CAN报文接收超时时间 */
#define __CAN_MSG_CNT              128   /* CAN消息个数 */

#define __CAN_TASK_STACK_SIZE      4096  /* CAN报文接收任务堆栈大小 */
#define __CAN_TASK_PRIO            6     /* CAN报文接收任务优先级 */


#undef AW_INFOF
#define AW_INFOF(x) aw_kprintf("CAN%d : ", __CAN_CHN); aw_kprintf x

/* CAN总线状态 */
static volatile aw_can_bus_status_t __g_can_bus_status = AW_CAN_BUS_STATUS_OK;

static aw_can_baud_param_t __g_can_btr = AW_CFG_CAN_BTR_500K;

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
    ret = aw_can_init(__CAN_CHN,                   /** \brief CAN通道号*/
                      AW_CAN_WORK_MODE_NORMAL,     /** \brief 控制器工作模式*/
                      &__g_can_btr,                /** \brief 当前波特率*/
                      &__g_can_app_callback_fun);  /** \brief 用户回调函数*/

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
 * \brief CAN接收任务入口
 *
 * \param[in] p_arg 任务参数
 *
 * \return 无
 */
static void __can_simple_recv_task (void *p_arg)
{
    aw_can_err_t        ret;
    aw_can_bus_status_t bus_status;         /* CAN bus总线状态 */
    uint32_t            recv_fifo_size = 0; /* CAN FIFO大小 */
    uint32_t            recv_cnt       = 0; /* 一次接收的个数 */
    uint32_t            recv_done_cnt  = 0; /* 接收完成个数 */

    aw_can_std_msg_t    msg[__CAN_MSG_CNT]; /* CAN信息缓冲区 */

    ret = __can_startup();
    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        goto exit;
    }


    /* 获取接收FIFO大小 */
    recv_fifo_size = aw_can_rcv_fifo_size(__CAN_CHN);

    AW_INFOF(("receive fifo size %d messages.\n", recv_fifo_size));

    recv_cnt = min(recv_fifo_size, __CAN_MSG_CNT);

    AW_INFOF(("receive cnt %d messages.\n", recv_cnt));


    AW_FOREVER {


        /* 接收标准CAN报文 */
        ret = aw_can_std_msgs_rcv(__CAN_CHN,
                                  msg,
                                  recv_cnt,
                                  &recv_done_cnt,
                                  __CAN_RECV_MSG_TIMEOUT);

        if ((ret == AW_CAN_ERR_NONE) && (recv_done_cnt > 0)) {

            AW_INFOF(("recv cnt:%d\n", recv_done_cnt));

        }

        bus_status = __g_can_bus_status;
        __g_can_bus_status = AW_CAN_BUS_STATUS_OK;

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

/**
 * \brief 建立CAN接收任务
 *
 * \param[in] 无
 *
 * \return 无
 */
void demo_can_simple_recv (void)
{
    AW_TASK_DECL_STATIC(task, __CAN_TASK_STACK_SIZE);

    AW_TASK_INIT(task,
                 "can_simple_recv",
                 __CAN_TASK_PRIO,
                 __CAN_TASK_STACK_SIZE,
                 __can_simple_recv_task,
                 (void *)0);

    AW_TASK_STARTUP(task);
}

/** [src_can_simple_recv] */

/* end of file */
