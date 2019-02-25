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
 * \brief RTC��ʾ���̣�ͨ��shell��������ʱ��
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
 *   1. ִ��shell����"test_rtc":��������rtc��ʱ5��
 *   2. ִ��shell����"test_rtc 2018-11-13 15:05:00":����ָ��ʱ�䣬��������rtc��ʱ5�Ρ�
 *
 * \par Դ����
 * \snippet demo_rtc_time_set.c src_rtc_time_set
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rtc_time_set
 * \copydoc demo_rtc_time_set.c
 */

/** [src_rtc_time_set] */
#include "aworks.h"     /* ��ͷ�ļ��������ȱ����� */

#include "aw_delay.h"
#include "aw_rtc.h"
#include "aw_vdebug.h"
#include "aw_prj_params.h"
#include "aw_shell.h"
#include "stdio.h"

//#define RTC_ID    RTC_ID0        /* PCF85063 RTC */
#define RTC_ID    RTC_ID1      /* ���İ��ڲ�RTC */

static aw_tm_t      __g_old_time = {0};

/**
 * \brief �ж�����ʱ���Ƿ���Ч
 *
 * \param[in] hour      ʱ
 * \param[in] minute    ��
 * \param[in] second    ��
 *
 * \return �жϽ��
 */
aw_local int __is_time_invalid(int hour,int minute,int second)
{
    int                 ret = -EINVAL;

    if( hour < 0 || hour > 23) {
        goto cleanup;
    }
    if (minute < 0 || minute > 59) {
        goto cleanup;
    }
    if (second < 0 || second > 59) {
        goto cleanup;
    }

    ret = 0;

cleanup:
    return ret;
}


/**
 * \brief �ж����������Ƿ���Ч
 *
 * \param[in] year      ��
 * \param[in] month     ��
 * \param[in] date      ��
 *
 * \return �жϽ��
 */
aw_local int __is_date_invalid(int year,int month,int date)
{
    static const int    month_days[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int                 ret = -EINVAL;

    if ( year <2000 || year >2050) {
        goto cleanup;
    }
    if (month <=0 || month > 12 ) {
        goto cleanup;
    }
    if (date <= 0 || date > month_days[month-1] ) {
        goto cleanup;
    }

    //���������
    if ( ((year%4)==0 && (year%100)!=0 ) || (year%400) == 0) {

    }else {
        if (2 == month) {
            if (date >= 29) {
                goto cleanup;
            }
        }
    }

    ret = 0;

cleanup:
    return ret;
}

static void __rtc_time_run(void)
{
    int                 i;
    aw_tm_t             tm;
    aw_time_t           t1,t2;
    int                 ret;
    char                time_str[30];

    ret = aw_tm_to_time(&__g_old_time, &t1);
    if(ret != AW_OK){
        goto __exit ;
    }

    for (i = 0;i < 5; i++) {
        ret = aw_rtc_time_get(RTC_ID, &tm);
        if(ret != AW_OK){
            goto __exit ;
        }

        ret = aw_tm_to_time(&tm, &t2);

        /* ���������ʱ����Ϣת�����ַ�����ʽ */
        asctime_r((struct tm*)&tm, time_str);
        aw_kprintf("%s", time_str);
        if(ret != AW_OK){
            goto __exit ;
        }

        aw_mdelay(1000);
    }

__exit:
    return ;
}


int __rtc_cmd (int argc, char *argv[], struct aw_shell_user *sh)
{
    const char             *sz_date = "2018-1-19";
    const char             *sz_time = "09:00:00";
    int                     ret = 0;
    int                     t1,t2,t3;

    if (argc >= 1) {
        sz_date = argv[0];
    }
    if (argc >= 2) {
        sz_time = argv[1];
    }

    ret = sscanf(sz_date,"%d-%d-%d",&t1,&t2,&t3);
    if (ret != 3) {
        aw_shell_printf(sh,"invalid date string\n");
        ret = -EINVAL;
        goto cleanup;
    }
    ret = __is_date_invalid(t1,t2,t3);
    if (ret != 0) {
        aw_shell_printf(sh,"invalid date \n");
        ret = -EINVAL;
        goto cleanup;
    }
    __g_old_time.tm_year = t1 -1900;
    __g_old_time.tm_mon = t2 -1;
    __g_old_time.tm_mday = t3;

    ret = sscanf(sz_time,"%d:%d:%d",&t1,&t2,&t3);
    if (ret != 3) {
        aw_shell_printf(sh,"invalid time string\n");
        ret = -EINVAL;
        goto cleanup;
    }
    ret = __is_time_invalid(t1,t2,t3);
    if (ret != 0) {
        aw_shell_printf(sh,"invalid time \n");
        ret = -EINVAL;
        goto cleanup;
    }

    __g_old_time.tm_hour = t1;
    __g_old_time.tm_min = t2;
    __g_old_time.tm_sec = t3;

    /* ����ʱ�� */
    ret = aw_rtc_time_set(RTC_ID, &__g_old_time);

    if (ret != 0) {
        aw_shell_printf(sh,"invalid aw_rtc_time_set failed \n");
        ret = -EINVAL;
        goto cleanup;
    }

    __rtc_time_run();

cleanup:
    return ret;
}

static const struct aw_shell_cmd __g_rtc_test_cmds[] = {
    {__rtc_cmd,  "test_rtc",  "[2018-1-19] [09:00:00] "},
};

/**
 * \brief RTC��ʾ�������
 * \return ��
 */
void demo_rtc_time_set_entry (void)
{
    static struct aw_shell_cmd_list cl;
    (void)AW_SHELL_REGISTER_CMDS(&cl, __g_rtc_test_cmds);
}
/** [src_rtc_time_set] */

/* end of file */
