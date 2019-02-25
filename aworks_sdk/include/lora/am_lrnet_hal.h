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
 * \brief   LoRaNet Hardware Adapter Layer Interface
 *
 * \internal
 * \par modification history:
 * - 2017-05-23 ebi, first implementation.
 * \endinternal
 */

#ifndef __AM_LRNET_HAL_H
#define __AM_LRNET_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
  Hardware Adapter
*******************************************************************************/

#include "am_lrnet.h"

typedef enum {
    AM_LRNET_HAL_CAD_DONE,
    AM_LRNET_HAL_CAD_NONE,
} am_lrnet_hal_lora_cad_result_t;

typedef enum {
    AM_LRNET_HAL_TX_DONE,
    AM_LRNET_HAL_TX_TIMEOUT,
} am_lrnet_hal_lora_tx_result_t;

typedef enum {
    AM_LRNET_HAL_RX_DONE,
    AM_LRNET_HAL_RX_TIMEOUT,
    AM_LRNET_HAL_RX_CRC_ERROR,
} am_lrnet_hal_lora_rx_result_t;

typedef struct {
    am_lrnet_hal_lora_cad_result_t cad;
    am_lrnet_hal_lora_tx_result_t  tx;
    am_lrnet_hal_lora_rx_result_t  rx;
    uint8_t                     rx_payload_size;
    uint8_t                    *p_rx_payload;
    int16_t                     rx_rssi;
    uint32_t                    rx_crc_err_cnt; /* �������ֵ ����crc����ʱ�ۼ� */
} am_lrnet_hal_lora_result_t;

extern volatile am_lrnet_hal_lora_result_t g_lrnet_hal_lora_result;

am_lora_static_inline
uint32_t am_lrnet_hal_lora_crc_err_cnt_get (void)
{
    return g_lrnet_hal_lora_result.rx_crc_err_cnt;
}

/*******************************************************************************
  HAL System
*******************************************************************************/

/* ��ȡÿ����������systick */
uint32_t am_lrnet_hal_systick (void);

/* ����systick��ֵ */
void am_lrnet_hal_systick_set (uint32_t tick);

/* ����͹���ģʽ */
void am_lrnet_hal_sleep (void);

/* ƽ̨��ʼ�� */
void am_lrnet_hal_pltm_init (void *p_handle);

/*******************************************************************************
  HAL LoRa
*******************************************************************************/

typedef struct {
    uint32_t           frequency;  /**< \brief LoRa RF Frequency */
    am_lrnet_rf_cr_t   cr;         /**< \brief LoRa RF Coding Rate */
    uint8_t            sf;         /**< \brief LoRa RF Spreading Factor, 7-12 */
    uint8_t            bw;         /**< \brief 0:125k  1:250k */
    int8_t             tx_power;   /**< \brief LoRa RF TX Power, unit: dBm */
} am_lrnet_hal_lora_rf_cfg_t;

typedef struct {

    /* �жϻص����� */
    void (*p_rx_finish) (void);
    void (*p_tx_finish) (void);
    void (*p_cad_finish) (void);

    /* ��Ƶ���� */
    am_lrnet_hal_lora_rf_cfg_t rf_cfg;
} am_lrnet_hal_lora_cfg_t;

/* lora��ʼ�� */
int am_lrnet_hal_lora_init (const am_lrnet_hal_lora_cfg_t *p_cfg);

/* lora����rf���� */
int am_lrnet_hal_lora_rf_reset (const am_lrnet_hal_lora_rf_cfg_t *p_rf_cfg);

/* lora����Ƶ�� */
int am_lrnet_hal_lora_freq_set (uint32_t freq);

/* ��ʼ���� ������ */
void am_lrnet_hal_lora_tx (const uint8_t *p_buf, uint8_t size);

/* ��ʼ���� ������ */
void am_lrnet_hal_lora_rx (uint32_t timeout_ms, uint8_t is_continuous);

/* ��ʼCAD��� */
void am_lrnet_hal_lora_cad (void);

/* lora����͹���˯��ģʽ */
void am_lrnet_hal_lora_sleep (void);

/* lora�ڿ�ʱ�� */
uint32_t am_lrnet_hal_lora_time_on_air (uint8_t payload_len);

/* lora�ӿ��л��32λ����� */
uint32_t am_lrnet_hal_lora_random (void);

/* �ظ����� ���ı䲿��payload */
void am_lrnet_hal_lora_tx_repeat (uint8_t *p_data, uint8_t size, uint8_t offset);

/*******************************************************************************
  HAL RTC
*******************************************************************************/

/* ����rtc */
void am_lrnet_hal_rtc_set (uint32_t value);

/* ��ȡrtc */
uint32_t am_lrnet_hal_rtc_get (void);

#ifdef __cplusplus
}
#endif

#endif /* __AM_LRNET_HAL_H */

/* end of file */
