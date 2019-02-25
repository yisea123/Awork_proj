/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief iMX RT1050 Analog Comparator demo
 *
 * - ʵ�鲽�裺
 *   1. ��Ҫ�� aw_prj_params.h �д�
 *      - AW_DEV_XXXX_ACMP1
 *      - AW_DEV_GPIO_LED
 *   2. ʹ��GPIO1_22(�װ��ϵ�TX3)���ŽӴ�VCC��GND
 *
 * - ʵ������
 *    1. ��GPIO1_22(�װ��ϵ�TX3)���Ž�VCC��LED��
 *    2. ��GPIO1_22���Ž�GND��LED��
 *
 * \internal
 * \par modification history:
 * - 1.00 18-04-12  mex, first implementation
 * \endinternal
 */

#include "aworks.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */
#include "aw_vdebug.h"
#include "aw_prj_params.h"
#include "aw_led.h"
#include "driver/acmp/awbl_acmp.h"

/** \brief ACMP��ID */
#define  ACMP_ID                  1

/** \brief �ο���ѹ����ͨ��ѡ��*/
#define  ACMP_VREF_SRC            VREF_SOURCE_VIN2

/** \brief �ο���ѹ�������ѹ */
#define  ACMP_VREF_IN_VOLT        33000

/** \brief �ο���ѹ�������ѹ(�����ڲ���64��T�͵�������ת��) */
#define  ACMP_VREF_DAC_OUT_VOLT   15000

/** \brief ͬ�������ͨ��ѡ��(������ŵĳ�ʼ��������ͷ�ļ���) */
#define  ACMP_POSITIVE_CAH         1

/** \brief ���������ͨ��ѡ�� */
#define  ACMP_NEGATIVE_CAH         7


/* ACMP�жϻص����� */
aw_local void __acmp_isr_func (void *p_arg)
{
    cmp_status_flags_t *flag = (cmp_status_flags_t *)p_arg;

    if (*flag == kCMP_OutputRisingEventFlag) {
        aw_led_on(0);
    } else if (*flag == kCMP_OutputFallingEventFlag) {
        aw_led_off(0);
    }
}


void demo_acmp_entry(void)
{
    /* ��ʼ����ע���жϻص����� */
    awbl_acmp_init(ACMP_ID, __acmp_isr_func);

    /* ���òο���ѹΪ1.5V */
    awbl_acmp_config_dac(ACMP_ID,
                         ACMP_VREF_SRC,
                         ACMP_VREF_IN_VOLT,
                         ACMP_VREF_DAC_OUT_VOLT);

    /* ���ñȽ���������ͨ�� */
    awbl_acmp_set_input_chan(ACMP_ID,
                             ACMP_POSITIVE_CAH,
                             ACMP_NEGATIVE_CAH);

    return ;
}

/** [src_acmp] */

/* end of file */
