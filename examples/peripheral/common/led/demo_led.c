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
 * \brief LED���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��AW_DEV_GPIO_LED
 *   2. ����LEDӲ��������鿴awbl_hwconf_gpio_led.h
 *
 * - ʵ������
 *   1. LED��1Hz��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_led.c src_led
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_led
 * \copydoc demo_led.c
 */

/** [src_led] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "aw_led.h"

#define  LED  0

/**
 * \brief LED demo
 * \return ��
 */
void demo_led_entry (void)
{
    aw_kprintf("\nled demo testing...\n");

    while(1) {
        aw_led_on(LED);            /* ����LED��   */
        aw_mdelay(500);             /* ��ʱ0.5s */
        aw_led_off(LED);
        aw_mdelay(500);

        aw_led_set(LED, TRUE);     /* ����LED��   */
        aw_mdelay(500);
        aw_led_set(LED, FALSE);    /* Ϩ��LED��    */
        aw_mdelay(500);

        aw_led_toggle(LED);        /* LED״̬��ת  */
        aw_mdelay(500);
        aw_led_toggle(LED);        /* LED״̬��ת  */
        aw_mdelay(500);
    }
}

/** [src_led] */

/* end of file */
