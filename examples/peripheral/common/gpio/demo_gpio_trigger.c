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
 * \brief gpio�����ж�����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - AW_DEV_GPIO_LED
 *      - ��Ӧƽ̨�Ĵ��ں�
 *   2 .�������ŵĴ�������ʱ�����öŰ��߽�  TEST_GPIO_0 �� TEST_GPIO_1 ��Ӧ����������������
 *
 * - ʵ������
 *  1. �����жϺ�LED����˸��
 *  2. ���ڴ�ӡ������Ϣ��
 *
 * - ��ע��
 *   1. ��ͬ����ƽ̨ʹ�õ����ſ��ܲ�ͬ���ɸ��ݶ�Ӧƽ̨����GPIO���ţ�
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_gpio_trigger.c src_gpio_trigger
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-27  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gpio_trigger
 * \copydoc demo_gpio_trigger.c
 */

/** [src_gpio_trigger] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_gpio.h"
#include "aw_led.h"
#include <stdlib.h>
#include "aw_vdebug.h"

/* ƽ̨GPIO���ɸ��ݾ���ƽ̨�޸�*/
#define TEST_GPIO_0     64      /**< \brief ���ű������ݾ���ƽ̨�޸�*/
#define TEST_GPIO_1     65      /**< \brief ���ű������ݾ���ƽ̨�޸�*/

/**\brief ��¼�жϽ���Ĵ��� */
aw_local uint8_t volatile __g_test_count = 0;

/* gpio ���� �ص�����  */
void test_gpio_trig_isr (void* arg) {
    uint8_t trig_mode = (uint32_t)arg;
    aw_led_toggle(0);
    __g_test_count++;
}

void demo_gpio_trigger_entry(void)
{
    uint32_t i = 0;

    // �����ж����Ų������������
    int gpio0_gpios[] = {TEST_GPIO_0, TEST_GPIO_1};
    if (aw_gpio_pin_request("test_gpios",
                             gpio0_gpios,
                             AW_NELEMENTS(gpio0_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(TEST_GPIO_0, AW_GPIO_PUSH_PULL | AW_GPIO_OUTPUT_INIT_HIGH);
        aw_gpio_pin_cfg(TEST_GPIO_1, AW_GPIO_INPUT);
    }

    //�����жϻص�����
    aw_gpio_trigger_connect(TEST_GPIO_1, test_gpio_trig_isr, (void *)AW_GPIO_TRIGGER_FALL);
    //����Ϊ�½��ش���
    aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_FALL);
    //����Ϊ�����ش���
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_RISE);
    //����Ϊ�͵�ƽ�ش���
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_LOW);
    //����Ϊ�ߵ�ƽ����
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_HIGH);
    //����Ϊ˫���ش���
    //aw_gpio_trigger_cfg(TEST_GPIO_1, AW_GPIO_TRIGGER_BOTH_EDGES);
    //�����ж�
    aw_gpio_trigger_on(TEST_GPIO_1);

    for (i = 0; i < 19; i++) {
        aw_task_delay(500);
        aw_gpio_toggle(TEST_GPIO_0);
    }

    //��ӡ�����жϴ���
    AW_INFOF(("entry gpio int time:%d\r\n",__g_test_count));

    //�Ͽ��жϻص�����
    aw_gpio_trigger_disconnect(TEST_GPIO_1,
                               test_gpio_trig_isr,
                               (void *)AW_GPIO_TRIGGER_FALL);
    //�ر��ж�
    aw_gpio_trigger_off(TEST_GPIO_1);
    //�ͷ�����
    aw_gpio_pin_release(gpio0_gpios, AW_NELEMENTS(gpio0_gpios));
}

/** [src_gpio_trigger] */

/* end of file */
