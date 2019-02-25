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
 * \brief ��Դ����������
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_DEV_PWM_BUZZER
 *      - ��Ӧƽ̨��PWM�ꡣ
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 * - ʵ������
 *   1. ������ÿ��500ms����һ�Ρ�
 *
 * - ��ע��
 *   1. �޸���Դ����������Ƶ�ʣ���Ҫ�޸�awbl_hwconf_buzzer_pwm.h��
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_pwm_buzzer.c src_pwm_buzzer
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-04  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_pwm_buzzer
 * \copydoc demo_pwm_buzzer.c
 */

/** [src_pwm_buzzer] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_buzzer.h"

/**
 * \brief �����������������
 * \return ��
 */
void demo_pwm_buzzer_entry (void)
{
    while(1) {

        aw_buzzer_loud_set(80); /* ���÷���������ǿ��   */
        aw_buzzer_beep(500);    /* ������������ʱ200ms    */

        aw_buzzer_loud_set(50); /* ���÷���������ǿ��   */
        aw_buzzer_on();         /* ����������    */
        aw_mdelay(500);         /* ��ʱ500ms  */
        aw_buzzer_off();        /* �رշ�����    */
        aw_mdelay(500);         /* ��ʱ500ms  */
    }
}

/** [src_pwm_buzzer] */

/* end of file */
