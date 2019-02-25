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
 * \brief AWorks������ϵͳʹ������
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ���Դ��ڶ�Ӧ�ĺ�
 *      - AW_COM_CONSOLE
 *      - AW_COM_INPUT_EV
 *      - AW_COM_INPUT_EV_KEY
 *   2. ��������64��GPIO�ܽ����ӵ��û�������·��
 *   3. �������еĵ��Դ���USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *
 * - ʵ������
 *   1. ����״̬�仯�����ڴ�ӡ������Ϣ��
 *
 * \par Դ����
 * \snippet demo_input.c src_input
 * 
 * \internal
 * \par Modification history
 * - 1.00 16-04-05  cod, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_input
 * \copydoc demo_input.c
 */

/** [src_input] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_gpio.h"
#include "aw_input.h"
#include "aw_defer.h"

/******************************************************************************/
#define GPIO_KEY   64      /**< \brief GPIO�����ܽź�GPIOn_x����ƽ̨������ */
#define DELAY_MS   25      /**< \brief ��ʱʱ��-ms */
/******************************************************************************/

aw_local struct aw_defer        __g_defer;  /* ����defer���� */
aw_local struct aw_defer_djob   __g_djob;   /* ���幤���ڵ� */

/**
 * \brief GPIO ���������ص�����
 * \param[in] p_arg  �ص���������
 */
aw_local void gpio_key_callback (void *p_arg)
{
    /* �ر�GPIO�������� */
    aw_gpio_trigger_off(GPIO_KEY);

    /* ��һ�������ڵ�������ӳ���ҵ���� */
    aw_defer_commit(&__g_defer, &__g_djob);
}

/**
 * \brief �ӳٹ����ص�����
 * \param[in] p_arg  �ص�����
 */
aw_local void delayed_work_func (void *p_arg)
{
    uint32_t key      = (uint32_t)p_arg;
    uint32_t cur_stat = aw_gpio_get(key);

    /* �ϱ������¼� */
    aw_input_report_key(AW_INPUT_EV_KEY, KEY_0, cur_stat);

    /* ������������ */
    aw_gpio_trigger_on(key);
}

/**
 * \brief ������ϵͳ�ص�����
 * \param[in] p_input_data  �����¼�����
 * \param[in] p_usr_data    �û�����
 */
aw_local void key_proc_cb (struct aw_input_event *p_input_data, void *p_usr_data)
{
    struct aw_input_key_data *p_key_data = NULL;

    if ((p_input_data != NULL) &&
        (p_input_data->ev_type != AW_INPUT_EV_KEY)) {
        return;
    }

    p_key_data = (struct aw_input_key_data *)p_input_data;
    if (p_key_data->key_code == KEY_0) {
        if (p_key_data->key_state) {
            AW_INFOF(("KEY is up : %d. \n", p_key_data->key_state));
        } else {
            AW_INFOF(("KEY is down : %d. \n", p_key_data->key_state));
        }
    }
}

/**
 * \brief ������ں���
 * \param[in] p_arg  ������ڲ���
 */
void demo_input_entry (void)
{
    struct aw_input_handler input_handler;

    AW_INFOF(("\ninput system testing...\n"));

    /* ��ʼ��һ���ӳ���ҵ */
    aw_defer_init(&__g_defer);

    /* ��ʼ��һ�������ڵ� */
    aw_defer_job_init(&__g_djob, delayed_work_func, (void *)GPIO_KEY);

    /* ����GPIO�����ܽ�Ϊ���빦�� */
    int gpio0_gpios[] = {GPIO_KEY};
    if (aw_gpio_pin_request("gpios",
                             gpio0_gpios,
                             AW_NELEMENTS(gpio0_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(GPIO_KEY, AW_GPIO_INPUT | AW_GPIO_PULL_UP);
    }

    /* ���ӻص����������� */
    aw_gpio_trigger_connect(GPIO_KEY, gpio_key_callback, NULL);

    /* �������Ŵ������ͣ��½��ش��� */
    aw_gpio_trigger_cfg(GPIO_KEY, AW_GPIO_TRIGGER_FALL);

    /* ע�ᰴ�������¼���������ϵͳ�� */
    aw_input_handler_register(&input_handler, key_proc_cb, NULL);

    /* �����ӳ���ҵ������1�����ȼ�Ϊ0����ջ��СΪ4096���̣߳��������� */
    AW_DEFER_START(&__g_defer, 1, 0, 4096, "demo_input");

    /* ���������ϵĴ�����  */
    aw_gpio_trigger_on(GPIO_KEY);
}

/** [src_input] */

/* end of file */
