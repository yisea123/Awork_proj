/*******************************************************************************
*                                  AWorks
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
 * \brief ADC���ÿͻ��˻�ȡ������ѹ����
 *
 * һ��ʹ�ÿͻ�����Ϊ�������Ϊ���ӵĵ�ѹ����Ҫ���û��ɸ���ʵ�������������
 * ���á�
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧ����ƽ̨��ADC1��.
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 * - ʵ������
 *   1. ����ÿ��1s��ӡ����ǰ�������еĵ�ѹֵ��
 *
 * - ��ע��
 *   1. �û����ڶ�Ӧƽ̨�� awbl_hwconf_xxxxxx_adc1.h �ļ������޸�adc��������;
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_adc_client.c src_adc_client
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_adc_client
 * \copydoc demo_adc_client.c
 */

/** [src_adc_client] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_adc.h"
#include "aw_vdebug.h"
#include "aw_msgq.h"

/* ADCͨ����
 *
 * ˵����"LRADC0", 0,
 *       "LRADC1", 1,
 *       "LRADC6", 6,
 *       "HSADC",  23,
 */
#define ADC_CHANNEL    0

#define SAMPLES_NUM    5            /* ����5�β���  */
#define ADC_READ_CNT   20           /* ��ȡADC��    */
/******************************************************************************/

/** adc complete data*/
struct adc_complete {
    int stat;    /**< \brief ת�����  */
    int seq;     /**< \brief ת������  */
};
/******************************************************************************/
/* ��Ϣ����   */
AW_MSGQ_DECL_STATIC(adc_msgq, 20, sizeof(struct adc_complete));

static uint16_t __adc_val0[ADC_READ_CNT];  /* adc���ջ�����0   */
static uint16_t __adc_val1[ADC_READ_CNT];  /* adc���ջ�����1   */
static uint32_t __vol_val[ADC_READ_CNT];   /* adcת��������  */

/******************************************************************************/
/**
 * \brief ADCת����ɻص�
 * \param[in] p_arg : �������
 * \param[in] stat  : ת�������־
 * \return ��
 */
static void __adc_complete_cb (void *p_arg, int stat)
{
    struct adc_complete msg = {stat, (int)p_arg};
    
    /* ����һ����Ϣ */
    AW_MSGQ_SEND(adc_msgq,
                 &msg,
                 sizeof(struct adc_complete),
                 AW_MSGQ_NO_WAIT,
                 AW_MSGQ_PRI_NORMAL);
}

/**
 * \brief ADC �ͻ��� demo
 * \return ��
 */
void demo_adc_client_entry (void)
{
    aw_adc_client_t     client;
    aw_adc_buf_desc_t   desc[2];
    struct adc_complete info;
    uint32_t            i;

    AW_MSGQ_INIT(adc_msgq, 20, sizeof(struct adc_complete), AW_SEM_Q_PRIORITY);

    /* ADC������������0 */
    aw_adc_mkbufdesc(&desc[0], __adc_val0, ADC_READ_CNT, __adc_complete_cb, (void *)0);

    /* ADC������������1*/
    aw_adc_mkbufdesc(&desc[1], __adc_val1, ADC_READ_CNT, __adc_complete_cb, (void *)1);

    /* ��ʼ��ADC�ͻ��� */
    aw_adc_client_init(&client, ADC_CHANNEL, FALSE);

    /* ����ת�� */
    aw_adc_client_start(&client, desc, 2, 0);
    
    while(1) {

        AW_MSGQ_RECEIVE(adc_msgq,
                        &info,
                        sizeof(struct adc_complete),
                        AW_MSGQ_WAIT_FOREVER);

        if (info.stat != AW_OK) {
            aw_kprintf("������ %d ת����������\r\n",info.seq);
        } else {

            if (info.seq == 0) {
                aw_kprintf("seq 0 complete!\r\n");
                aw_adc_val_to_mv(ADC_CHANNEL, __adc_val0, ADC_READ_CNT, __vol_val);
            }
            if (info.seq == 1) {
                aw_kprintf("seq 1 complete!\r\n");
                aw_adc_val_to_mv(ADC_CHANNEL, __adc_val1, ADC_READ_CNT, __vol_val);
            }

            for (i = 0; i < ADC_READ_CNT; i++) {
                aw_kprintf("%d conversion result : %dmV\n", i + 1, __vol_val[i]);
            }
        }

        aw_mdelay(1000);
    }
}

/** [src_adc_client] */
 
/* end of file */
