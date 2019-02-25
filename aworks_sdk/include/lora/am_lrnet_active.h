/*******************************************************************************
*                                 LoRaNet
*                  ----------------------------------------
*                    LoRa low power network protocol stack
*
* Copyright (c) 2001-present Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief   LoRaNet Active Module Interface
 *
 * \internal
 * \par modification history:
 * - 2017-05-23 ebi, first implementation.
 * \endinternal
 */

#ifndef __LRNET_ACTIVE_H
#define __LRNET_ACTIVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_lrnet_internal.h"

enum {
    AM_LRNET_EVT_DELAY_FINISH = AM_SM_EVENT_USER,

    /* events for active_rxtx */
    AM_LRNET_EVT_LORA_RX_FINISH,    /* LoRa RF Rx Finish */
    AM_LRNET_EVT_LORA_TX_FINISH,    /* LoRa RF Tx Finish */
    AM_LRNET_EVT_LORA_CAD_FINISH,   /* LoRa RF CAD Finish */
    AM_LRNET_EVT_CMD_WAKEUPRX,
    AM_LRNET_EVT_CMD_RX,
    AM_LRNET_EVT_CMD_TX,
    AM_LRNET_EVT_CMD_TX_LBT,
    AM_LRNET_EVT_CMD_FORCE_IDLE,    /* RXTX return to idle state without finish message */

    /* Common API */
    AM_LRNET_EVT_API_ADDR_SET,
    AM_LRNET_EVT_API_MODE_SET,

    /* Center API */
    AM_LRNET_EVT_API_TX,
    AM_LRNET_EVT_API_FETCH,
    AM_LRNET_EVT_API_PING,
    AM_LRNET_EVT_API_UPSTREAM_BC,
    AM_LRNET_EVT_API_TIMEBC,
    AM_LRNET_EVT_API_GFETCH,
    AM_LRNET_EVT_API_GFETCH_S,
    AM_LRNET_EVT_API_DETECT,

    /* Raw API */
    AM_LRNET_EVT_API_RAW_TX,

    /* Terminal API */
    AM_LRNET_EVT_API_EREPORT,
    AM_LRNET_EVT_API_BURST_REPORT,

    /* events from active_rxtx to active_proc  */
    AM_LRNET_EVT_RX_FINISH,    /* Packet Rx Finish, p_arg is ((am_lrnet_packet_t*) p_packet) */
    AM_LRNET_EVT_TX_FINISH,    /* Packet Tx Finish, p_arg is ((int) error_no) */

    /* events to active_proc */
    /* mount a state to proc and transform state to it */
    AM_LRNET_EVT_MOUNT,
    AM_LRNET_EVT_UNMOUNT,
    AM_LRNET_EVT_LOOP_WAKEUP,
    AM_LRNET_EVT_GO_TOP,
    AM_LRNET_EVT_RX_WINDOW_OPEN,       /* p_argΪ�������յĺ���ʱ�� */

    AM_LRNET_EVT_SM_WAITRX_EXIT,
};

/* �����л��Ѳ��� */
#define AM_LRNET_TX_CTRL_NO_WAKEUP          __BIT(0)

/* ������һ���Ҳ����л��ѣ�
 * ����Ҫack�����Խ���ack�󷵻أ���ʱ������ֵ��ΪAM_OK����ʾδ�յ�ack��
 * ������ack��������Ϻ�ֱ�ӷ���AM_OK
 */
#define AM_LRNET_TX_CTRL_NO_RETRY           __BIT(1)

/* ��ֹ�̻��ѣ���֤���ѿɿ� */
#define AM_LRNET_TX_CTRL_NO_SHORT_WAKEUP    __BIT(2)

extern am_sm_active_t *gp_lrnet_active_rxtx;

const char* am_lrnet_active_evt_to_str (uint32_t evt);

void am_lrnet_active_rxtx_init (void);

void am_lrnet_active_rxtx_post (uint32_t evt, void *p_arg);

void am_lrnet_active_rxtx_packet_tx (am_lrnet_packet_t *p_packet,
                                     uint32_t           tx_ctrl,
                                     uint32_t           delay_ms);

void am_lrnet_active_rxtx_packet_tx_lbt (am_lrnet_packet_t *p_packet,
                                         uint32_t           timeout);

void am_lrnet_active_rxtx_packet_rx (uint32_t timeout_ms, am_lora_bool_t is_continuous);

am_lora_bool_t am_lrnet_active_rxtx_busy (void);

extern am_sm_active_t *gp_lrnet_active_proc;

void am_lrnet_active_proc_init (
        am_sm_state_t         *p_top_state,
        am_sm_event_handler_t  p_top_handler,
        am_sm_state_t         *p_idle_state,
        am_sm_event_handler_t  p_idle_handler,
        am_sm_state_t         *p_busy_state,
        am_sm_event_handler_t  p_busy_handler);

void am_lrnet_active_proc_post (uint32_t evt, void *p_arg);

void am_lrnet_active_proc_mount (am_sm_event_handler_t p_handler);

void am_lrnet_active_proc_unmount (void);

void am_lrnet_active_proc_delay_timer_set (uint32_t value_ms, uint32_t msg);

void am_lrnet_active_proc_delay_timer_cancel (void);

/*
 * �˳�proc�ĵ�ǰ״̬��hookһ��rxwin״̬��idle_state��
 * rxwin��LoRa Single Packet Rxģʽ���� ������Ϻ�
 *  1. ��δ�յ�����ת�����ϲ�״̬
 *  2. ���յ����򽻸���״̬����
 */
void am_lrnet_active_proc_rxwin (uint32_t ms);

am_lora_bool_t am_lrnet_active_proc_busy (void);

am_lora_static_inline
void am_lrnet_active_proc_go_top (void)
{
    am_lrnet_active_proc_post(AM_LRNET_EVT_GO_TOP, 0);
}

#ifdef __cplusplus
}
#endif

#endif /* __LRNET_ACTIVE_H */

/* end of file */
