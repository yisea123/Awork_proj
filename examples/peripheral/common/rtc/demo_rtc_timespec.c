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
 * \brief RTC��ʾ���̣�ʹ��aw_rtc_timespec_set��aw_rtc_timespec_get�ӿ�
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
 * \snippet demo_rtc_timespec.c src_rtc_timespec
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rtc_timespec
 * \copydoc demo_rtc_timespec.c
 */

/** [src_rtc_timespec] */
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
void demo_rtc_timespec_entry (void)
{
    aw_timespec_t timespec; /* ����ʱ�� */

    /* ����ϸ��ʱ�� */
    aw_tm_t tm = {
        0,                  /* seconds after the minute     - [0, 59] */
        0,                  /* minutes after the hour       - [0, 59] */
        15,                 /* hours after midnight         - [0, 23] */
        14,                 /* day of the month      - [1, 31] */
        8 - 1,              /* months since January  - [0, 11] */
        2018 - 1900         /* years since 1900                */
    };

    aw_tm_to_time(&tm, &timespec.tv_sec);     /* ϸ��ת��Ϊ����ʱ�� */
    timespec.tv_nsec = 0;                     /* ���벿����0 */

    aw_rtc_timespec_set(RTC_ID, &timespec);   /* ����RTC����ʱ�� */

    while(1) {

        aw_rtc_timespec_get(RTC_ID, &timespec);  /* ��ȡRTC����ʱ�� */
        aw_time_to_tm(&timespec.tv_sec, &tm);    /* ��������������ʱ��ת��Ϊϸ��ʱ�� */

        aw_kprintf("current time is: %d-%d-%d  %02d:%02d:%02d.%d\n",
                    tm.tm_year + 1900,
                    tm.tm_mon + 1,
                    tm.tm_mday,
                    tm.tm_hour,
                    tm.tm_min,
                    tm.tm_sec,
                    timespec.tv_nsec / 1000000);
        aw_mdelay(1);
    }
}
/** [src_rtc_timespec] */

/* end of file */
