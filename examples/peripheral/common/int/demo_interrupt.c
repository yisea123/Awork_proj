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
 * \brief interrupt����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�Ĵ��ں�
 *   2 .�������ŵĴ�������ʱ�����öŰ��߽�  TEST_GPIO_0 �� TEST_GPIO_1 ��Ӧ����������������
 *
 * - ʵ������
 *  1. ���ڴ�ӡ������Ϣ
 *
 *
 * \par Դ����
 * \snippet demo_interrupt.c src_interrupt
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-27  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_interrupt
 * \copydoc demo_interrupt.c
 */

/** [src_interrupt] */
#include "aworks.h"
#include "aw_gpio.h"
#include "aw_sem.h"
#include "aw_vdebug.h"
#include "aw_delay.h"

/* ƽ̨GPIO���ɸ��ݾ���ƽ̨�޸�*/
#define TEST_IO_INTR    64      /**< \brief ���ű������ݸ��ݾ���ƽ̨�޸�*/
#define TEST_IO_OUTPUT  65      /**< \brief ���ű������ݸ��ݾ���ƽ̨�޸�*/

/**\brief ��¼�Ƿ�����ж� */
AW_SEMB_DECL_STATIC(__gpio_intr_semb);


/* gpio ���� �ص�����  */
static void __test_gpio_trig_isr (void* arg)
{
    AW_SEMB_GIVE(__gpio_intr_semb);
}


void demo_interrupt_entry(void)
{
    aw_err_t            err;
    int                 i;
    /*�ź�����ʼ��*/
    AW_SEMB_INIT(__gpio_intr_semb,AW_SEM_EMPTY,AW_SEM_Q_FIFO);

    // �����ж����Ų������������
    int gpio0_gpios[] = {TEST_IO_INTR, TEST_IO_OUTPUT};
    if (aw_gpio_pin_request("spi0_gpios",
                             gpio0_gpios,
                             AW_NELEMENTS(gpio0_gpios)) == AW_OK) {

        aw_gpio_pin_cfg(TEST_IO_OUTPUT, AW_GPIO_PUSH_PULL | AW_GPIO_OUTPUT_INIT_HIGH);
        aw_gpio_pin_cfg(TEST_IO_INTR, AW_GPIO_INPUT);

    }

    /*�����жϻص�����*/
    aw_gpio_trigger_connect(TEST_IO_INTR, __test_gpio_trig_isr, (void *)AW_GPIO_TRIGGER_FALL);
    /*����Ϊ�½��ش���*/
    aw_gpio_trigger_cfg(TEST_IO_INTR, AW_GPIO_TRIGGER_FALL);
    /*�������ŵĴ���*/
    aw_gpio_trigger_on(TEST_IO_INTR);

    for(i = 0;i < 100 ;i++){
        /*��������ܽ�Ϊ�͵�ƽ*/
        aw_gpio_set(TEST_IO_OUTPUT,0);

        /*�ȴ��жϴ���*/
        err = AW_SEMB_TAKE(__gpio_intr_semb,1000);
        if (AW_OK == err) {
            aw_kprintf("enter gpio interrupt!\n");
        }

        /*��������ܽ�Ϊ�ߵ�ƽ*/
        aw_gpio_set(TEST_IO_OUTPUT,1);

        aw_mdelay(100);
    }

    /*�Ͽ��ж����ӻص�����*/
    aw_gpio_trigger_disconnect(TEST_IO_INTR,
                               __test_gpio_trig_isr,
                               (void *)AW_GPIO_TRIGGER_FALL);
    /*�������ŵĴ���*/
    aw_gpio_trigger_off(TEST_IO_INTR);
    /*�ͷ�����*/
    aw_gpio_pin_release(gpio0_gpios, AW_NELEMENTS(gpio0_gpios));
    /*��ֹ�ź���*/
    AW_SEMB_TERMINATE(__gpio_intr_semb);
}


/** [src_interrupt] */

/* end of file */
