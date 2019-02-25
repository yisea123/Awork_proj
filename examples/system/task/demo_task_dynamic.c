/*******************************************************************************
*                                 AWorks
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
 * \brief AWorks ��̬�������ط������񴴽���ɾ��������
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_DEV_GPIO_LED
 *      - AW_COM_CONSOLE
 *   2. �������е�RX1��TX1ͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   
 * - ʵ������
 *   1. LED_RUN��500ms��ʱ��������
 *   2. ���ڴ�ӡ��ǰִ��������
 *   3. ����2���ڴ�ӡ20�κ�����ɾ�������ٴ�ӡ
 *
 * \par Դ����
 * \snippet demo_task_dynamic.c src_task_dynamic
 * 
 * \internal
 * \par Modification history
 * - 1.01 17-09-05  anu, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_task_dynamic
 * \copydoc demo_task_dynamic.c
 */

/** [src_task_dynamic] */
#include "aworks.h"
#include "aw_task2.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_led.h"

#define LED_RUN 0

/** 
 * \brief ����2��ں���
 *
 * \param[in] p_arg ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void task2_entry (void *p_arg)
{     
    aw_task_id_t task2_id = aw_task_id_self();  /* ��ȡ��ǰ�����ID  */
    uint8_t      cnt      = 0;
    int          ret;

    /* ����ͨ������ʽ����һ����ѭ��������ѭ�� */
    AW_FOREVER {
        aw_kprintf("Current Task's name is %s, Current Count is %d\r\n",
                    aw_task_name_get(task2_id), ++cnt);

        aw_mdelay(500);

        /* cnt������20�� ��ֹ��ǰ����  */
        if (cnt == 20) {
            aw_kprintf("current task will be terminated\r\n");
            aw_task2_exit(&ret);
        }
    }
}

/** 
 * \brief ����1��ں���
 *
 * \param[in] p_arg ע��ʱ�û�������Զ������
 *
 * \return ��
 */
static void task1_entry(void *p_arg)
{
    aw_task2_id_t task2;                  /* ���弴������������2��ID������ID������񴴽�*/

    /* 
     * �����������д�������һ������������ʾ����������2
     */
    task2 = aw_task2_create("task2",      /* �������� */
                            2048,         /* �����ջ��С */
                            4,            /* �������ȼ� */
                            task2_entry,  /* ������ں��� */
                            (void*)2);    /* ������ڲ��� */

    aw_task2_startup(task2);    /* ����ʹ������ID����һ������ */

    
    /* 
     * ��������ʱ�������һ��������ã���������2���ȼ�������1���ȼ��ߣ����ȼ���ֵԽС�����ȼ�Խ�ߣ�
     * ��ˣ������󣬻�����ȥִ������2����������2����ʱ����ʱ���Ż��ͷ�CPU���ص�����2����ִ��
     *
     */
    
    /* ����ͨ������ʽ����һ����ѭ��������ѭ�� */
    AW_FOREVER {
        
        aw_kprintf("Current Task's name is %s\r\n",
                    aw_task_name_get(aw_task_id_self()));

        aw_led_toggle(LED_RUN);
        /* ������ʱ 100ms����aw_mdelay(500)��ͬ */
        aw_task_delay(aw_sys_clkrate_get() * 500 / 1000);
    }
}

/** 
 * \brief ��̬�����������ں���
 *
 * \return ��
 */
void demo_task_dynamic_entry (void)
{
    aw_task2_id_t task1;

    /*
     * ���õĴ�������ķ�ʽ�����ú괴����
     * ʹ�ú������������������: 1����̬�������� aw_task2_create
     *                         2����������         aw_task2_startup
     */
    task1 = aw_task2_create("task1",      /* �������� */
                            2048,         /* �����ջ��С */
                            5,            /* �������ȼ� */
                            task1_entry,  /* ������ں��� */
                            (void*)1);    /* ������ڲ��� */

    aw_task2_startup(task1);    /* ����task1,���ڵ�ǰ�����ȼ���ߣ��������к���task1_entry */
}

/** [src_task_dynamic] */

/* end of file */
