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
 * \brief RTC��ʾ���̣�ʹ��aw_rtc_time_set��aw_rtc_time_get�ӿ�
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�Ͷ�Ӧ��ŵ�I2C
 *      - AW_DEV_EXTEND_PCF85063
 *      - AW_COM_CONSOLE
 *      ע�⣺�����ʼ��ʧ�ܣ��鿴�����ļ��Ƿ����������ó�ͻ������ǣ���aw_prj_params.h�йرղ�ʹ�õĺ�
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3. ����ϵͳ��RTCΪ��ʵ�������ֻ�ܿ���һ��RTC����
 *
 * - ʵ������
 *   1. �趨�ó�ʼʱ�䣬ͨ�����ڿ��Թ۲�ʱ������������Ϣ��1�����1�����ݡ�
 *
 * \par Դ����
 * \snippet demo_rtc_std.c src_rtc_std
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rtc_std
 * \copydoc demo_rtc_std.c
 */

/** [src_rtc_std] */
#include "aworks.h"     /* ��ͷ�ļ��������ȱ����� */

#include "aw_delay.h"
#include "aw_rtc.h"
#include "aw_vdebug.h"
#include "aw_prj_params.h"

//#define RTC_ID    RTC_ID0        /* PCF85063 RTC */
#define RTC_ID    RTC_ID1      /* ���İ��ڲ�RTC */

/**
 * \brief RTC��ʾ�������
 * \return ��
 */
void demo_rtc_std_entry (void)
{
    aw_err_t ret = AW_OK;

    /* ������ʼʱ�� */
    aw_tm_t tm = {
        0,                      /* second */
        30,                     /* minute */
        12,                     /* hour   */
        30,                     /* day of the month      */
        8 - 1,                  /* months since January  */
        2017 - 1900,            /* years since 1900      */
    };

    ret = aw_rtc_time_set(RTC_ID, &tm);    /* ������ʼʱ�� */
    if (ret != AW_OK) {
        AW_ERRF(("RTC set error: %d\n", ret));
    }

    while (1) {

        ret = aw_rtc_time_get (RTC_ID, &tm);    /* �õ�ϸ��ʱ�� */

        if (ret != AW_OK) {
            AW_INFOF(("rtc ����ʧ�� %d \r\n", ret));
        } else {
            /* ��ӡϸ��ʱ�� */
            AW_INFOF(("current time: %s\n",
                      asctime((const struct tm *)&tm)));
        }

        aw_mdelay(1000);
    }
}

/** [src_rtc_std] */

/* end of file */
