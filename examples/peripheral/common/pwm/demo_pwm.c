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
 * \brief PWM��ʾ����(PWM������Դ������)
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨��PWM�ꡣ
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *
 * - ʵ������
 *   1. ��������500msΪ�������С�
 *
 * \par Դ����
 * \snippet demo_pwm.c src_pwm
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-25  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_pwm
 * \copydoc demo_pwm.c
 */

/** [src_pwm] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_pwm.h"
#include "aw_prj_params.h"

#define AW_PWM_ID              10
/**
 * \brief PWM��ʾ�������
 * \return ��
 */
void demo_pwm_entry (void)
{
    uint32_t    period1 = 2000000;      // (ns)
    uint32_t    period2 = 1000000;      // (ns)

    while(1) {

        /* ���� PWM ����Чʱ�䣨�ߵ�ƽʱ�䣩50% ,���� period1*/
        aw_pwm_config(AW_PWM_ID, period1 / 2, period1);
        aw_pwm_enable(AW_PWM_ID);      /* ʹ��ͨ�� */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* ����ͨ��  */
        aw_mdelay(250);


        /* ���� PWM ����Чʱ�䣨�ߵ�ƽʱ�䣩2% ,���� period1*/
        aw_pwm_config(AW_PWM_ID, period1 / 50, period1);
        aw_pwm_enable(AW_PWM_ID);      /* ʹ��ͨ�� */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* ����ͨ��  */
        aw_mdelay(250);


        /* ���� PWM ����Чʱ�䣨�ߵ�ƽʱ�䣩50% ,���� period2*/
        aw_pwm_config(AW_PWM_ID, period2 / 2, period2);
        aw_pwm_enable(AW_PWM_ID);      /* ʹ��ͨ�� */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* ����ͨ��  */
        aw_mdelay(250);


        /* ���� PWM ����Чʱ�䣨�ߵ�ƽʱ�䣩2% ,���� period2*/
        aw_pwm_config(AW_PWM_ID, period2 / 50, period2);
        aw_pwm_enable(AW_PWM_ID);      /* ʹ��ͨ�� */
        aw_mdelay(250);
        aw_pwm_disable(AW_PWM_ID);     /* ����ͨ��  */
        aw_mdelay(250);
    }
}

/** [src_pwm] */

/* end of file */
