/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief hwtimer ���Գ���
 *
 * hwtimer ͨ�ö�ʱ�����ṩ���¹���:
 *
 * - �������裺
 *   1. ��aw_prj_params.h��ʹ��
 *      - ��Ӧƽ̨��Ӳ����ʱ����
 *      - AW_DEV_GPIO_LED
 *
 * - ʵ������
 *   1. LED��1Hz��Ƶ����˸��
 *   2. ���ڴ�ӡ��Ӧ��Ϣ��
 *
 * - ��ע��
 *   1. ��ʹ�ø�����ʱ���뱣֤ʹ�õĶ�ʱ�����ܽ�֧�������Ʋ��ң������ڶ�ʱ���������ļ��е��豸��Ϣ�ж��塣
 *
 * \par Դ����
 * \snippet demo_hwtimer.c src_hwtimer
 *
 * \internal
 * \par modification history:
 * - 1.00 2018-07-03  sdq, first implementation
 * \endinternal
 */
/**
 * \addtogroup demo_if_hwtimer
 * \copydoc demo_hwtimer.c
 */

/** [src_hwtimer] */
#include "aworks.h"
#include "aw_hwtimer.h"
#include "aw_vdebug.h"
#include "aw_led.h"
#include "aw_delay.h"

#define  LED  0

/**
 * \brief Ӳ����ʱ���жϷ�������
 * \param[in] p_arg : �������
 */
static void mytimer_isr (void *p_arg)
{
    aw_led_toggle(LED);
}

/**
 * \brief hwtimer ���Ժ���
 */
void demo_hwtimer_entry (void)
{
    aw_hwtimer_handle_t mytimer;

    /* ͨ���������붨ʱ�� */
    mytimer = aw_hwtimer_alloc(1000,                   /* ��������Ƶ��1 */
                               1,                      /* ��СƵ��1Hz */
                               1000000,                /* ���Ƶ��1MHz */
                               AW_HWTIMER_AUTO_RELOAD, /* �Զ���װ */
                               mytimer_isr,            /* �жϷ����� */
                               (void *) NULL);         /* �жϷ�������ں��� */

    if (mytimer) {
        aw_hwtimer_enable(mytimer, 2);                 /* ʹ�ܶ�ʱ�ж� 2Hz */
    } else {
        aw_kprintf("Timer allocation fail!\n");
    }

    for (;;) {
        aw_mdelay(1000);
    }

}
/** [src_hwtimer] */

/*end of file */
