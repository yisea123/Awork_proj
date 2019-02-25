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
 * \brief ADC��ȡ������ѹ����(ͬ����ȡ)
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�� ADC1 ��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 * - ʵ������
 *   1. ����ÿ��500ms����ӡ��������������5����ѹֵ��
 *
 * - ��ע��
 *   1. �û����ڶ�Ӧƽ̨�� awbl_hwconf_xxxxxx_adc1.h �ļ������޸�adc��������;
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_adc.c src_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-23  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_adc
 * \copydoc demo_adc.c
 */

/** [src_adc] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_adc.h"
#include "aw_vdebug.h"
#include "string.h"

/* ADCͨ���� */
#define ADC_CHANNEL    0

/* ����5�β��� */
#define SAMPLES_NUM    5

/**
 * \brief ADC ͬ����ȡ��ѹֵ demo
 * \return ��
 */
void demo_adc_entry (void)
{
    uint16_t adc_val[SAMPLES_NUM];
    uint32_t vol_val[SAMPLES_NUM];
    int      i;

    memset(adc_val, 0, sizeof(adc_val));

    while(1) {
    
        /* ��ȡͨ����ADֵ */
        aw_adc_sync_read(ADC_CHANNEL, adc_val, SAMPLES_NUM, FALSE);

        /* ת��Ϊʵ�ʵ�ѹֵ */
        aw_adc_val_to_mv(ADC_CHANNEL, adc_val, SAMPLES_NUM, vol_val);

        for (i = 0; i < SAMPLES_NUM; i++) {
            aw_kprintf(" %d conversion result : %dmV\n", i + 1, vol_val[i]);
        }
        aw_mdelay(500);
        aw_kprintf("\r\n");
    }
}

/** [src_adc] */
 
/* end of file */
