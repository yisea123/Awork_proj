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
 * \brief ����CAN��������ʾ����
 * \note  �����̽����շ����ԡ�
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      AW_COM_CONSOLE��
 *      CAN��UART��
 *   2. ����CAN��������ŵ�CAN�շ��� RX=>RX TX=>TX��
 *      �շ����ٽӵ�USBCAN-II�豸�� H=>H L=>L, CAN������500K��
 *   3. �򿪴��ڵ����նˣ�������115200-8-N-1��
 *
 * - ʵ������
 *   1. __CAN_TEST_MODE = __CAN_TEST_MSG_SEND
 *      ���ZCANPRO��λ�����������豸�󣬻᲻�ϵ���ȡ�����ġ�
 *   2. __CAN_TEST_MODE = __CAN_TEST_MSG_ECHO
 *      ���ZCANPRO��λ�����������豸�󣬷��ͱ��Ļ���л��ԡ�
 *   3. ���ڴ�ӡ��ص�����Ϣ��
 *
 * \par Դ����
 * \snippet demo_can.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 1.00 18-09-18  anu, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_can
 * \copydoc demo_can.c
 */

/** [src_std_can] */

#include "aworks.h"
#include "string.h"
#include "aw_can.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_spinlock.h"
#include "aw_prj_params.h"

#define __CAN_CHN                  0     /* CANͨ�� */
#define __CAN_RECV_MSG_TIMEOUT     10    /* CAN���Ľ��ճ�ʱʱ�� */
#define __CAN_SEND_MSG_TIMEOUT     300   /* CAN���ķ��ͳ�ʱʱ�� */
#define __CAN_MSG_CNT              128   /* CAN��Ϣ���� */

#define __CAN_TASK_STACK_SIZE      4096  /* CAN���Ľ��������ջ��С */
#define __CAN_TASK_PRIO            6     /* CAN���Ľ����������ȼ� */

#define __CAN_TEST_MSG_ECHO        0     /* CAN������Ϣ���� */
#define __CAN_TEST_MSG_SEND        1     /* CAN������Ϣ���� */
#define __CAN_TEST_MODE            __CAN_TEST_MSG_ECHO /* CAN����ģʽѡ�� */

#undef AW_INFOF
#define AW_INFOF(x) aw_kprintf("CAN%d : ", __CAN_CHN); aw_kprintf x

/* CAN����״̬ */
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
    ret = aw_can_init(__CAN_CHN,                   /** \brief CANͨ����*/
                      AW_CAN_WORK_MODE_NORMAL,     /** \brief ����������ģʽ*/
                      &__g_can_btr,                /** \brief ��ǰ������*/
                      &__g_can_app_callback_fun);  /** \brief �û��ص�����*/

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
static void __can_task_entry (void *p_arg)
{
    aw_can_err_t        ret;
    aw_spinlock_isr_t   lock;
    aw_can_bus_status_t bus_status;         /* CAN bus����״̬ */
    uint32_t            recv_fifo_size = 0; /* CAN FIFO��С */
    uint32_t            recv_cnt       = 0; /* һ�ν��յĸ��� */
    uint32_t            send_done_cnt  = 0; /* ������ɸ��� */
#if !(__CAN_TEST_MODE == __CAN_TEST_MSG_SEND)
    uint32_t            recv_done_cnt  = 0; /* ������ɸ��� */
#endif
    aw_can_std_msg_t    msg[__CAN_MSG_CNT]; /* CAN��Ϣ������ */

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

#if __CAN_TEST_MODE == __CAN_TEST_MSG_SEND
    memset(msg, 0x00, sizeof(msg));
    msg[0].can_msg.length = 8;
#endif

    AW_FOREVER {

#if __CAN_TEST_MODE == __CAN_TEST_MSG_SEND

        msg[0].can_msg.id++;

        /* ���ͱ�׼CAN���� */
        ret = aw_can_std_msgs_send(__CAN_CHN,
                                   msg,
                                   1,
                                   &send_done_cnt,
                                   __CAN_SEND_MSG_TIMEOUT);

        if (ret == AW_CAN_ERR_NONE && send_done_cnt == 1) {
            AW_INFOF(("send done! sent:%d\n", send_done_cnt));
        } else {
            AW_INFOF(("send error! sent:%d\n", send_done_cnt));
        }
#else
        /* ���ձ�׼CAN���� */
        ret = aw_can_std_msgs_rcv(__CAN_CHN,
                                  msg,
                                  recv_cnt,
                                  &recv_done_cnt,
                                  __CAN_RECV_MSG_TIMEOUT);

        if ((ret == AW_CAN_ERR_NONE) && (recv_done_cnt > 0)) {

            AW_INFOF(("recv cnt:%d\n", recv_done_cnt));

            /* ���ͱ�׼CAN���� */
            ret = aw_can_std_msgs_send(__CAN_CHN,
                                       msg,
                                       recv_done_cnt,
                                       &send_done_cnt,
                                       __CAN_SEND_MSG_TIMEOUT);

            if (ret == AW_CAN_ERR_NONE && send_done_cnt == recv_done_cnt) {
                AW_INFOF(("send done! sent:%d\n", send_done_cnt));
            } else {
                AW_INFOF(("send error! sent:%d\n", send_done_cnt));
            }
        }
#endif

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

/**
 * \brief ����CAN����
 *
 * \param[in] ��
 *
 * \return ��
 */
void demo_can (void)
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

/** [src_std_can] */

/* end of file */