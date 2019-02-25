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
 * \brief ���Ź���WDT����ʾ����
 *
 * - ��������:
 *   1. ��Ҫ��aw_prj_params.h��ʹ��
 *      - ��Ӧƽ̨���ڲ����Ź� �� �ⲿ���Ź�(AW_DEV_GPIO_WDT)��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *   2. ������ʾ����AWorks������Ź��÷���ʵ����ֻҪʹ�ܿ��Ź��豸�꣬Ӳ�����Ź�ϵͳ�ᶨʱ
 *      ι�������������Ź�û�м�ʱι����ôϵͳ�ͻ�ֹͣιӲ�����Ź����Ӷ�����ϵͳ����λ��
 *   3. ����WDT����ʱ�����ܴ�ϵ���ԣ��������Ϊϵͳû��ι�������¸�λ��
 *
 * - ʵ������:
 *   1. �������������ڴ�ӡ"Add WDT device!"
 *   2. ÿι��һ�Σ���ӡ"WDT Feed!"
 *   3. ��ι����ʱ������λ�����´�ӡ��"Add WDT device!".
 *
 * - ��ע��
 *   1. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��ã�
 *   2. �ⲿ���Ź�ʹ�ú�Ϊ����Ӳ����λ�������ε��ⲿ���Ź��ĺꡣ
 *
 * \par Դ����
 * \snippet demo_wdt.c src_wdt
 *
 * \internal
 * \par History
 * - 1.00 18-06-25  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_wdt
 * \copydoc demo_wdt.c
 */

/** [src_wdt] */
#include "aworks.h"     /* ��ͷ�ļ����뱻���Ȱ��� */

/* �������õ������·��� */
#include "aw_delay.h"
#include "aw_wdt.h"
#include "aw_vdebug.h"
#include "aw_led.h"

#define WDT_TIMEOUT_MS     1000   /* ���Ź�ʱ��  */
#define FEED_TIME_MS       600    /* ι��ʱ��  */

#define LED      0
/**
 * \brief WDT ����
 * \return ��
 */
void demo_wdt_entry (void)
{
    struct awbl_wdt wdt_dev;
    aw_err_t  ret = AW_OK;

    /* ���ÿ��Ź�ʱ�� */
    ret = aw_wdt_add(&wdt_dev, WDT_TIMEOUT_MS);
    if (ret != AW_OK) {
        AW_ERRF(("*ERR: WDT add error %d\n", ret));
        return;
    }

    AW_INFOF(("Add WDT device!\r\n"));
    AW_INFOF(("WDT timeout is %d ms!\r\n", WDT_TIMEOUT_MS));

    /* LED0 �����˸ */
    while (1) {
        aw_wdt_feed(&wdt_dev);    /* ι��   */
        aw_mdelay(FEED_TIME_MS);
        aw_led_toggle(LED);
        AW_INFOF(("WDT Feed!\r\n"));
    }
}

/** [src_wdt] */

/* end of file */
