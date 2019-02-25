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
 * \brief CANFD��������ʾ����
 * \note  �����̽��е��������յ��ٶȲ��ԡ�
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      AW_COM_CONSOLE��
 *      CAN��UART��
 *   2. ����CANFD��������ŵ�CANFD�շ��� RX=>RX TX=>TX��
 *      �շ����ٽӵ�USBCANFD�豸�� H=>H L=>L��
 *      CANFD�ٲ�������1000K ����������5000K��
 *   3. �򿪴��ڵ����նˣ�������115200-8-N-1��
 *
 * - ʵ������
 *   1. __CAN_TEST_MODE = __CAN_TEST_MSG_RECV
 *      ���ZCANPRO��λ�����������豸�����ò��ϵķ��ͱ��ģ�
 *      �ﵽ100000֡�󣬽���ͳ�ƽ����ٶȡ�
 *   2. __CAN_TEST_MODE = __CAN_TEST_MSG_SEND
 *      ���ZCANPRO��λ�����������豸�󣬻᲻�ϵ���ȡ���ģ�
 *      ���ʹﵽ100000֡������ͳ�Ʒ����ٶȡ�
 *   3. ���ڴ�ӡ��ص�����Ϣ��
 *
 * \par Դ����
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

#define __CAN_CHN                  0      /* CANͨ�� */
#define __CAN_RECV_MSG_TIMEOUT     10     /* CAN���Ľ��ճ�ʱʱ�� */
#define __CAN_SEND_MSG_TIMEOUT     300    /* CAN���ķ��ͳ�ʱʱ�� */
#define __CAN_MSG_CNT              32     /* CAN��Ϣ���� */

#define __CAN_TASK_STACK_SIZE      4096   /* CAN���Ľ��������ջ��С */
#define __CAN_TASK_PRIO            6      /* CAN���Ľ����������ȼ� */

#define __CAN_TEST_MSG_CNT         100000 /* CAN���շ�����֡�Ž���ͳ�� */

#define __CAN_TEST_MSG_RECV        0      /* CAN�����ٶȲ��� */
#define __CAN_TEST_MSG_SEND        1      /* CAN�����ٶȲ��� */
#define __CAN_TEST_MODE            __CAN_TEST_MSG_SEND /* CAN����ģʽѡ�� */

#undef AW_INFOF
#define AW_INFOF(x) aw_kprintf("CANFD%d : ", __CAN_CHN); aw_kprintf x

/* CAN����״̬ */
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
 * \brief ʱ�����ȡ�Ļص�����
 *
 * \param[in] timestamp ��ǰ���ĵ�ʱ���
 *
 * \return �û��޸ĺ��ʱ���
 */
static uint32_t __can_timestamp_get_cb (uint32_t timestamp)
{
    return timestamp;
}

/**
 * \brief ����״̬�Ļص�����
 *
 * \param[in] chn ͨ����
 * \param[in] err CAN ���ߵĴ�������
 * \param[in] status CAN ���ߵ�״̬
 *
 * \retval TRUE  ��������Ϣ������rngbuf
 * \retval FALSE ������Ϣ������rngbuf
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

    return TRUE; /* ��������ֵ����������Ϣ�Ƿ����rngbuf,TRUE:������,FALSE:���� */
}

/**
 * \brief CAN��ʼ��
 *
 * \param[in] ��
 *
 * \return AW_CAN_ERR_NONE������������������ο��������
 */
static aw_can_err_t __can_startup (void)
{
    aw_can_err_t ret;

    /** \brief ��ʼ��CAN */
    ret = aw_can_init(__CAN_CHN,                           /* CANͨ����*/
                      AW_CAN_WORK_MODE_NORMAL,             /* ����������ģʽ*/
                      (aw_can_baud_param_t *)&__g_can_btr, /* ��ǰ������*/
                      &__g_can_app_callback_fun);          /* �û��ص�����*/

    AW_INFOF(("controller init...\n"));

    if (ret != AW_CAN_ERR_NONE) {
        goto exit;
    }

    /** \brief ����CAN */
    ret = aw_can_start(__CAN_CHN);
    AW_INFOF(("controller start!\n"));

exit:
    return ret;
}

/**
 * \brief CAN�������
 *
 * \param[in] p_arg �������
 *
 * \return ��
 */
#if __CAN_TEST_MODE == __CAN_TEST_MSG_SEND
static void __can_task_entry (void *p_arg)
{
    uint32_t            i;
    aw_tick_t           t1, t2;
    aw_can_err_t        ret;
    aw_spinlock_isr_t   lock;
    aw_can_bus_status_t bus_status;         /* CAN bus����״̬ */
    uint32_t            total_send_cnt = 0; /* �ܹ����͵ĸ��� */
    uint32_t            send_done_cnt  = 0; /* ������ɸ��� */
    aw_can_fd_msg_t     msg[__CAN_MSG_CNT]; /* CANFD��Ϣ������ */

    ret = __can_startup();

    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        goto exit;
    }

    aw_spinlock_isr_init(&lock, 0);

    /* ���÷��͵Ĳ��� */
    memset(msg, 0x00, sizeof(msg));
    for (i = 0; i < __CAN_MSG_CNT; i++) {
        msg[i].can_msg.length = 64;

        /* ���÷��͵���ϢΪCANFD���ģ�ʹ�ܲ������л� */
        msg[i].can_msg.flags = AW_CAN_MSG_FLAG_FD_CTRL | AW_CAN_MSG_FLAG_BRS;
    }

    AW_FOREVER {

        if (t1 == 0) {
            t1 = aw_sys_tick_get();
        }

        /* ����CANFD���� */
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

            /* ֹͣCAN */
            aw_can_stop(__CAN_CHN);
            AW_INFOF(("controller stop!\n"));

            /* ����CAN */
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
    aw_can_bus_status_t bus_status;         /* CAN bus����״̬ */
    uint32_t            recv_fifo_size = 0; /* CAN FIFO��С */
    uint32_t            recv_cnt       = 0; /* һ�ν��յĸ��� */
    uint32_t            recv_done_cnt  = 0; /* ������ɸ��� */
    uint32_t            total_recv_cnt = 0; /* �����յĸ��� */
    aw_can_fd_msg_t     msg[__CAN_MSG_CNT]; /* CANFD��Ϣ������ */

    ret = __can_startup();

    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        goto exit;
    }

    aw_spinlock_isr_init(&lock, 0);

    /* ��ȡ����FIFO��С */
    recv_fifo_size = aw_can_rcv_fifo_size(__CAN_CHN);

    AW_INFOF(("receive fifo size %d messages.\n", recv_fifo_size));

    recv_cnt = min(recv_fifo_size, __CAN_MSG_CNT);

    AW_INFOF(("receive cnt %d messages.\n", recv_cnt));

    AW_FOREVER {

        /* ����CANFD���� */
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

            /* ֹͣCAN */
            aw_can_stop(__CAN_CHN);
            AW_INFOF(("controller stop!\n"));

            /* ����CAN */
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
 * \brief ����CAN����
 *
 * \param[in] ��
 *
 * \return ��
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
