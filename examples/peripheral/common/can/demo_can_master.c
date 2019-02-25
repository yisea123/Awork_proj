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
 * \note  ��������Ϊ���ƶˣ������ƶ˿����� demo_can_slave.c��
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      AW_DEV_GPIO_KEY
 *      AW_DEV_PWM_BUZZER
 *      AW_COM_INPUT_EV_KEY��
 *      AW_COM_CONSOLE��
 *      CAN��UART��
 *   2. ����CAN��������ŵ�CAN�շ��� RX=>RX TX=>TX��
 *      �շ����ٽӵ���ҪͨѶ���豸��ͨ��CAN���շ����� H=>H L=>L��
 *   3. �򿪴��ڵ����նˣ�������115200-8-N-1��
 *
 * - ʵ������
 *   1. ���°���KEY_1����ͨ���ᷢ�Ϳ���LED���ģ�DATAÿbit����һ����״̬���ر����е�
 *      (��׼֡ ID=0X01 DATA=0X00 0X00 0X00 0X00 0X00 0X00 0X00 0X00)��
 *   2. �ɿ�����KEY_1����ͨ���ᷢ�Ϳ���LED���ģ�DATAÿbit����һ����״̬�������е�
 *      (��׼֡ ID=0X01 DATA=0XFF 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF)��
 *   3. �յ�LED����Ӧ���ģ�������������
 *      (��׼֡ ID=0X81 DATA=0X00 0X00 0X00 0X00 0X00 0X00 0X00 0X00)��
 *   4. ���ڴ�ӡ��ص�����Ϣ��
 *
 * \par Դ����
 * \snippet demo_can_master.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 1.00 18-09-18  anu, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_can
 * \copydoc demo_can_master.c
 */

/** [src_std_can] */

#include "aworks.h"
#include "string.h"
#include "aw_can.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_buzzer.h"
#include "aw_vdebug.h"
#include "aw_input.h"
#include "aw_rngbuf.h"
#include "aw_spinlock.h"
#include "aw_prj_params.h"

#define __CAN_CHN                  0     /* CANͨ�� */
#define __CAN_RECV_MSG_TIMEOUT     10    /* CAN���Ľ��ճ�ʱʱ�� */
#define __CAN_SEND_MSG_TIMEOUT     300   /* CAN���ķ��ͳ�ʱʱ�� */
#define __CAN_MSG_CNT              10    /* CAN��Ϣ���� */

#define __CAN_RECV_TASK_STACK_SIZE 2048  /* CAN���Ľ��������ջ��С */
#define __CAN_SEND_TASK_STACK_SIZE 2048  /* CAN���ķ��������ջ��С */
#define __CAN_RECV_TASK_PRIO       7     /* CAN���Ľ����������ȼ� */
#define __CAN_SEND_TASK_PRIO       8     /* CAN���ķ����������ȼ� */

#define __CAN_MSG_ID_LED           0X01  /* ��ϢID��LED���ƹ����� */
#define __CAN_MSG_ID_LED_ACK       0X81  /* ��ϢID��LED����Ӧ������ */

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

/******************************************************************************/
/**
 * \brief �����ص�����
 * \param[in] p_input_data  ����/ָ�������¼�����
 * \param[in] p_usr_data    �û��Զ�������
 */
aw_local void __key_proc_cb (aw_input_event_t *p_input_data, void *p_usr_data)
{
    struct aw_input_key_data *p_key_data =
                             (struct aw_input_key_data *)p_input_data;

    aw_can_std_msg_t msg;

    if (AW_INPUT_EV_KEY != p_input_data->ev_type || p_usr_data == NULL) {
        return;
    }

    if (p_key_data->key_code == KEY_1) {
        if (p_key_data->key_state) {
            AW_INFOF(("KEY1 is up\n"));

            /* ���ñ��ģ���������LED�ƴ� */
            memset(&msg, 0x00, sizeof(msg));
            msg.can_msg.id = __CAN_MSG_ID_LED;
            memset(msg.msgbuff, 0xFF, sizeof(msg.msgbuff));
            msg.can_msg.length = sizeof(msg.msgbuff);

            aw_rngbuf_put(p_usr_data, (char *)&msg, sizeof(msg));
        } else {
            AW_INFOF(("KEY1 is down\n"));

            /* ���ñ��ģ���������LED�ƹر� */
            memset(&msg, 0x00, sizeof(msg));
            msg.can_msg.id = __CAN_MSG_ID_LED;
            msg.can_msg.length = sizeof(msg.msgbuff);

            aw_rngbuf_put(p_usr_data, (char *)&msg, sizeof(msg));
        }
    }
}

/**
 * \brief CAN�����������
 *
 * \param[in] p_arg �������
 *
 * \return ��
 */
static void __can_send_task_entry (void *p_arg)
{
    aw_can_err_t        ret;
    aw_spinlock_isr_t   lock;
    aw_can_bus_status_t bus_status;         /* CAN bus����״̬ */
    uint32_t            send_cnt      = 0;  /* ���͸��� */
    uint32_t            send_done_cnt = 0;  /* ������ɸ��� */
    aw_can_std_msg_t    msg[__CAN_MSG_CNT]; /* CAN��Ϣ������ */

    AW_RNGBUF_DEFINE(rngbuf, aw_can_std_msg_t, __CAN_MSG_CNT);

    struct aw_input_handler key_hdlr;

    /* ע��һ��������������������ϵͳ */
    aw_input_handler_register(&key_hdlr, __key_proc_cb, &rngbuf);

    aw_spinlock_isr_init(&lock, 0);

    AW_FOREVER {

        send_cnt = aw_rngbuf_nbytes(&rngbuf) / sizeof(aw_can_std_msg_t);
        if (send_cnt > 0) {
            aw_rngbuf_get(&rngbuf,
                          (char *)msg,
                          send_cnt * sizeof(aw_can_std_msg_t));

            /* ���ͱ�׼CAN���� */
            ret = aw_can_std_msgs_send(__CAN_CHN,
                                       msg,
                                       send_cnt,
                                       &send_done_cnt,
                                       __CAN_SEND_MSG_TIMEOUT);

            if (ret == AW_CAN_ERR_NONE && send_done_cnt == send_cnt) {
                AW_INFOF(("send done! sent:%d\n", send_done_cnt));
            } else {
                AW_INFOF(("send error! sent:%d\n", send_done_cnt));
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

        aw_mdelay(100);
    }
}

/**
 * \brief CAN�����������
 *
 * \param[in] p_arg �������
 *
 * \return ��
 */
static void __can_recv_task_entry (void *p_arg)
{
    aw_can_err_t     ret;
    uint32_t         recv_done_cnt = 0;  /* ������ɸ��� */
    aw_can_std_msg_t msg[__CAN_MSG_CNT]; /* CAN��Ϣ������ */

    AW_FOREVER {

        /* ���ձ�׼CAN���� */
        ret = aw_can_std_msgs_rcv(__CAN_CHN,
                                  msg,
                                  __CAN_MSG_CNT,
                                  &recv_done_cnt,
                                  __CAN_RECV_MSG_TIMEOUT);

        while ((ret == AW_CAN_ERR_NONE) && (recv_done_cnt--)) {

            AW_INFOF(("recv cnt:%d\n", recv_done_cnt + 1));
            if (msg[recv_done_cnt].can_msg.id == __CAN_MSG_ID_LED_ACK) {
                aw_buzzer_beep(100); /* ����������100���� */
            }
        }
    }
}

/**
 * \brief ����CAN��������CAN����
 *
 * \param[in] ��
 *
 * \return ��
 */
void demo_can_master (void)
{
    aw_can_err_t ret;

    AW_TASK_DECL_STATIC(send_task, __CAN_SEND_TASK_STACK_SIZE);
    AW_TASK_DECL_STATIC(recv_task, __CAN_RECV_TASK_STACK_SIZE);

    ret = __can_startup();

    if (ret != AW_CAN_ERR_NONE) {
        AW_INFOF(("controller startup failed:%d!\n", ret));
        return;
    }

    AW_TASK_INIT(send_task,
                 "can_send_task",
                 __CAN_SEND_TASK_PRIO,
                 __CAN_SEND_TASK_STACK_SIZE,
                 __can_send_task_entry,
                 (void *)0);

    AW_TASK_INIT(recv_task,
                 "can_recv_task",
                 __CAN_RECV_TASK_PRIO,
                 __CAN_RECV_TASK_STACK_SIZE,
                 __can_recv_task_entry,
                 (void *)0);

    AW_TASK_STARTUP(send_task);
    AW_TASK_STARTUP(recv_task);
}

/** [src_std_can] */

/* end of file */
