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
 * \brief GPS����
 *
 * - �������裺
 *   1. ��Ҫ�� aw_prj_params.h ͷ�ļ���ʹ��GPS�豸��Ŀǰʹ�õ���CNT226������
 *    - AW_DEV_GNSS_CNT226
 *    - ��Ӧƽ̨�Ĵ����豸�� (cnt226ʹ�õĴ����豸)
 *    - AW_COM_CONSOLE
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *
 * - ʵ������
 *   1. ����������GPS��������ȡGPS��Ϣ������ӡ��������
 *
 * - ��ע��
 *   1. ���ʣ�GPS�豸�ھ�ֹ״̬����Ϊ0��������Ч��������ȡ���ʻ�ʧ�ܣ��豸�ƶ��������ȡ����Ӧ���ʡ�
 *
 * \par Դ����
 * \snippet demo_gps.c src_gps
 *
 * \internal
 * \par Modification history
 * - 1.00 17-09-09  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gps
 * \copydoc demo_gps.c
 */

/** [src_gps] */
#include "aworks.h"
#include "aw_gnss.h"
#include "aw_vdebug.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_time.h"

aw_local aw_err_t  __gps_info_get(void)
{
    aw_err_t  ret = AW_OK;

    float    value[2];
    char     buf[50];
    aw_tm_t  tm;
    bool_t   is_ok = FALSE;

    // ���� GPS ģ���ȡ���ݽ�����һ�㶼��Ҫ���Զ�Σ������ȶ�����
    ret = aw_gnss_dat_get(0, AW_GNSS_RMC_VALID, &is_ok, sizeof(is_ok));
    if (ret != AW_OK) {
        AW_ERRF(("get gps data valid err: %d\n",  ret));
        return  ret;
    }

    // GPS ������Ч����ӡ����������Ϣ
    if (is_ok) {

        AW_INFOF(("\n\n************ GPS Data ****************\n"));

        // ��ȡ��λ����
        ret = aw_gnss_dat_get(0, AW_GNSS_RMC_POSITION, value, 8);
        if (ret != AW_OK) {
            AW_ERRF(("aw_gnss_get_pos err: %d\n",  ret));
            return  ret;
        } else {
            // ����, γ��
            AW_INFOF(("gps local: %f, %f\n", value[0], value[1]));
        }

        // ��ȡ����
        ret = aw_gnss_dat_get(0, AW_GNSS_GGA_ALTITUDE, value, 4);
        if (ret != AW_OK) {
            AW_ERRF(("get gga altitude failed: %d\n",  ret));
        } else {
            AW_INFOF(("altitude: %f\n", value[0]));
        }

        // ��ȡRMC���͵�UTCʱ�䣬�й�ʱ��Ϊ��8��
        ret = aw_gnss_dat_get(0, AW_GNSS_RMC_UTC_TIME, &tm, sizeof(tm));
        if (ret != AW_OK) {
            AW_ERRF(("get utc time failed: %d\n",  ret));
        } else {
            AW_INFOF(("UTC time: %d-%d-%d %02d:%02d:%02d\n",
                    tm.tm_year+1900,
                    tm.tm_mon+1,
                    tm.tm_mday,
                    tm.tm_hour,
                    tm.tm_min,
                    tm.tm_sec));
        }

        // RMC�ĵ��溽��
        ret = aw_gnss_dat_get(0, AW_GNSS_RMC_COURSE, value, 4);
        if (ret != AW_OK) {
            AW_ERRF(("get course failed: %d\n",  ret));
        } else {
            AW_INFOF(("course: %f\n", value[0]));
        }

        // ��ȡ�ٶ�
        ret = aw_gnss_dat_get(0, AW_GNSS_VTG_RATE, value, 4);
        if (ret != AW_OK) {
            AW_ERRF(("get vtg rate failed: %d\n",  ret));
        } else {
            AW_INFOF(("vtg rate: %f\n", value[0]));
        }

        AW_INFOF(("**************************************\n\n"));
    }

    return ret;
}

/**
 * \brief GPS�������
 * \return ��
 */
void demo_gps_entry (void)
{
    aw_err_t  ret = AW_OK;

    int  dev_id = 0;
    int  i      = 0;

    // ��λ GPS ģ�飨����GPS��ʼ�������������Ҫ�ȴ�һ��ʱ�䣬���Զ�Σ�
    // AW_GNSS_HRESET: Ӳ��λ��ʱ��ϳ�
    for (i = 0; i < 20; i++) {
        ret = aw_gnss_ioctl(dev_id, AW_GNSS_HRESET, (void *)AW_GNSS_HOT_STARTUP);
        if (ret == AW_OK) {
            break;
        }
        aw_mdelay(500);
    }
    if (i == 20) {
        AW_ERRF(("aw_gnss_ioctl AW_GNSS_HOT_STARTUP err: %d\n",  ret));
        return;
    }

    // ���� GPS ģ��
    ret = aw_gnss_enable(dev_id);
    if (ret != AW_OK) {
        AW_ERRF(("aw_gnss_start err: %d\n",  ret));
        return;
    }

    // ����˫ģ���
    ret = aw_gnss_ioctl(dev_id, AW_GNSS_SYS_FREQ, (void *)(AW_GNSS_BDS_B1 | AW_GNSS_GPS_L1));
    if (ret != AW_OK) {
        AW_ERRF(("aw_gnss_ioctl err: %d\n",  ret));
        return;
    }

    // ���ý�������ΪRMC  VTG �� GGA
    ret = aw_gnss_ioctl(dev_id,
                        AW_GNSS_NMEA_SELECT,
                        (void *)(AW_GNSS_NMEA_RMC | AW_GNSS_NMEA_VTG | AW_GNSS_NMEA_GGA));
    if (ret != AW_OK) {
        AW_ERRF(("aw_gnss_ioctl AW_GNSS_NMEA_SELECT err: %d\n",  ret));
        return;
    }

    /*
     * ������ȡ GPS ��Ϣ
     */
    for (;;) {
        __gps_info_get();
        aw_mdelay(2000);
    }

}

/** [src_gps] */

/* end of file */
