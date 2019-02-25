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
 * \brief GPIO����
 *
 * - ������
 *   1. ����������aw_prj_params.hͷ�ļ��н���
 *      - AW_DEV_GPIO_LED
 *
 * - ʵ������
 *   1. ������LED��0.5s��������˸5�Σ�ÿ�δ�ӡ��ӦLED�Ĺܽŵ�ƽֵ
 *   2. ������LED��0.1s��������˸4s��
 *
 * - ��ע��
 *   1. ��ͬ����ƽ̨ʹ�õ����ſ��ܲ�ͬ���ɸ��ݶ�Ӧƽ̨����GPIO���ţ�
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_gpio.c src_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 18-02-26  hsg, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gpio
 * \copydoc demo_gpio.c
 */

/** [src_gpio] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_led.h"
#include <stdlib.h>

#define GPIO_LED (19) /* ��LED������GPIO �ܽţ����ݾ���ƽ̨�޸�*/

/**
 * \brief GPIO demo ���
 * \return ��
 */
void demo_gpio_entry(void)
{
    int      i   = 0;
    aw_err_t ret = AW_OK;

    aw_kprintf("\nGPIO demo testing...\n");

    int gpio_led_test[] = {GPIO_LED};
    if (aw_gpio_pin_request("gpio_led_test",
                             gpio_led_test,
                             AW_NELEMENTS(gpio_led_test)) == AW_OK) {

        /* GPIO �������� */
        aw_gpio_pin_cfg(GPIO_LED, AW_GPIO_OUTPUT | AW_GPIO_PULL_UP);

    }

    /* LED��0.5s��������˸5�� */
    for (i = 0; i < 5; i++) {
        aw_gpio_set(GPIO_LED, 0);
        ret = aw_gpio_get(GPIO_LED);
        if (AW_ENXIO != ret) {
            aw_kprintf("GPIO1_19 is %d\n", ret);
        }
        aw_mdelay(500);

        aw_gpio_set(GPIO_LED, 1);
        ret = aw_gpio_get(GPIO_LED);
        if (AW_ENXIO != ret) {
            aw_kprintf("GPIO1_19 is %d\n", ret);
        }
        aw_mdelay(500);
    }

    /* LED��0.1s�����ڳ�����˸ */
    for (i = 0; i < 40; i++) {
        aw_gpio_toggle(GPIO_LED);
        aw_mdelay(100);
    }

    aw_gpio_pin_release(gpio_led_test, AW_NELEMENTS(gpio_led_test));
}

/** [src_gpio] */

/* end of file */
