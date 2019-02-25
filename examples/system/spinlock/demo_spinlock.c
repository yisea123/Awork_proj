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
 * \brief ��������ʾ����
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��AW_COM_CONSOLE��
 *   2. �������е�RX1��TX1ͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *
 * - ʵ������
 *      ��������__USE_SPINLOCK�򴮿ڴ�ӡ__g_counter��ֵ��ÿ�������ӡ5�Σ��м䲻�ᱻ��ϣ�
 *      ���򴮿ڴ�ӡ�Ķ����Ƚ����ң�����1������2��Ƕ�״�ӡ��
 *
 * \par Դ����
 * \snippet demo_spinlock.c src_spinlock
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-05  sup, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spinlock
 * \copydoc demo_spinlock.c
 */

/** [src_spinlock] */
#include "aworks.h"
#include "aw_spinlock.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_vdebug.h"
#include "aw_timer.h"
#include "aw_delay.h"

#define __USE_SPINLOCK  /* ʹ�������� */

/* ������ */
volatile static uint32_t __g_counter = 0;

/* ������ */
#ifdef __USE_SPINLOCK
static aw_spinlock_isr_t __g_spin_lock;
#endif

/**
 * \brief �߳� task0 ���
 * \return ��
 */
static void __task_entry (void *p_arg)
{
    uint8_t i = 0;

    AW_FOREVER {

        /* �������������������ȫ�ֱ��� */
#ifdef __USE_SPINLOCK
        aw_spinlock_isr_take(&__g_spin_lock);
#endif
        for (i = 0; i < 5; i++) {
            AW_INFOF(("%s counter: %d\n", (char *)p_arg, __g_counter++));
        }
#ifdef __USE_SPINLOCK
        aw_spinlock_isr_give(&__g_spin_lock);
#endif
        AW_INFOF(("\n\n"));

        aw_mdelay(500);
    }
}

/**
 * \brief ��������ʾ�������
 *
 * \return ��
 */
void demo_spinlock_entry (void)
{
    AW_TASK_DECL_STATIC(sl_task1, 1024);
    AW_TASK_DECL_STATIC(sl_task2, 1024);

    AW_INFOF(("Spin lock task start...\n"));

#ifdef __USE_SPINLOCK
    aw_spinlock_isr_init(&__g_spin_lock, 0);
#endif

    AW_TASK_INIT(sl_task1,
                 "demo_spinlock_task",
                 3,
                 1024,
                 __task_entry,
                 "task1");

    AW_TASK_STARTUP(sl_task1);

    AW_TASK_INIT(sl_task2,
                 "demo_spinlock_task",
                 3,
                 1024,
                 __task_entry,
                 "task2");

    AW_TASK_STARTUP(sl_task2);
}

/** [src_spinlock] */

/* end of file */
