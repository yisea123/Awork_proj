/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ZM516X ģ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� DUART_RX �������� PC ���ڵ� TXD��
 *       DUART_TX �������� PC ���ڵ� RXD��
 *    2. ���Ա� Demo ������ aw_prj_params.h ��ʹ��
 *       - AW_DEV_ZM516X_0
 *       - ��Ӧƽ̨��zigbeeģ�������Ĵ��ں�
 *
 * - ʵ������
 *   1. ���ڴ�ӡ��ȡ���ı���ģ���������Ϣ��
 *   2. ZM516X ģ��� 11 ͨ���� 26 ͨ����������ģ�顣�������������ģ�飬��ȡ��ģ��
 *      ���ź�ǿ�Ⱥ�������Ϣ����ͨ�����ڴ�ӡ��
 *   3. ���������ɣ����Դ��ڴ�ӡ "ZM516X Search Done\r\n"��
 *      �������ʧ�ܣ����Դ��ڴ�ӡ��Ӧ������Ϣ��
 *   4. ������ģ���ͨ���ָ�Ϊ����ǰ��ͨ���š�
 *
 * - ��ע��
 *   1. Zigbee ģ����GPIO�������ӹ�ϵ��Ҫ�鿴zigbee�������ļ�awbl_hwconf_zm516x.h,
 *      �����Ҫʹ�� Zigbee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_zm516x_search.c src_zm516x_search
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-23  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_zm516x_search
 * \copydoc demo_zm516x_search.c
 */

/** [src_zm516x_search] */
#include "aworks.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "driver/zigbee/awbl_zm516x.h"
#include <string.h>

/** \brief �����豸�ţ���Ҫ�� awbl_hwconf_zm516x.h �ļ��ڵ�ֵ��ͬ */
#define    __ID    0

/**
 * \brief ��ӡ ZM516X ģ���������Ϣ
 */
aw_local void __cfg_info_print (awbl_zm516x_cfg_info_t *p_zm516x_cfg_info)
{
    AW_INFOF(("\r\n__cfg_info_print\r\n"));
    AW_INFOF(("dev_name:%s\r\n"
              "dev_pwd:%s\r\n"
              "dev_mode:%d\r\n"
              "chan:%d\r\n"
              "panid:0x%04x\r\n"
              "my_addr:0x%04x\r\n"
              "my_mac:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n"
              "dst_addr:0x%04x\r\n"
              "power_level:%d\r\n"
              "retry_num:%d\r\n"
              "tran_timeout:%d\r\n"
              "send_mode:%d\r\n"
              "state:0x%02x\r\n"
              "software:%d\r\n"
              "version:0x%04x\r\n",
              p_zm516x_cfg_info->dev_name,
              p_zm516x_cfg_info->dev_pwd,
              p_zm516x_cfg_info->dev_mode,
              p_zm516x_cfg_info->chan,
              p_zm516x_cfg_info->panid,
              p_zm516x_cfg_info->my_addr,
              p_zm516x_cfg_info->my_mac[7],
              p_zm516x_cfg_info->my_mac[6],
              p_zm516x_cfg_info->my_mac[5],
              p_zm516x_cfg_info->my_mac[4],
              p_zm516x_cfg_info->my_mac[3],
              p_zm516x_cfg_info->my_mac[2],
              p_zm516x_cfg_info->my_mac[1],
              p_zm516x_cfg_info->my_mac[0],
              p_zm516x_cfg_info->dst_addr,
              p_zm516x_cfg_info->power_level,
              p_zm516x_cfg_info->retry_num,
              p_zm516x_cfg_info->tran_timeout,
              p_zm516x_cfg_info->send_mode,
              p_zm516x_cfg_info->state,
              p_zm516x_cfg_info->software,
              p_zm516x_cfg_info->version));
    AW_INFOF(("\r\n"));
}

/**
 * \brief ��ӡ ZM516X ģ��Ļ�����Ϣ(ͨ���������� D4 ���)
 */
aw_local void __base_info_print (awbl_zm516x_base_info_t *p_zm516x_base_info,
                                 uint8_t                  num)
{
    uint8_t i = 0;

    AW_INFOF(("\r\n__base_info_print\r\n"));

    for (i = 0; i < num; i++) {
        AW_INFOF(("software:0x%04x\r\n"
                  "chan:%d\r\n"
                  "data_rate:%d\r\n"
                  "panid:0x%04x\r\n"
                  "addr:0x%04x\r\n"
                  "state:0x%02x\r\n",
                  (p_zm516x_base_info + i)->software,
                  (p_zm516x_base_info + i)->chan,
                  (p_zm516x_base_info + i)->data_rate,
                  (p_zm516x_base_info + i)->panid,
                  (p_zm516x_base_info + i)->addr,
                  (p_zm516x_base_info + i)->state));
        AW_INFOF(("\r\n"));
    }
}

/**
 * \brief zm516x �������
 */
void demo_zm516x_search_entry (void)
{
    uint8_t                 i              = 0;
    uint8_t                 j              = 0;
    uint8_t                 get_size       = 0;
    uint8_t                 signal         = 0;
    awbl_zm516x_base_info_t base_info[6];
    awbl_zm516x_cfg_info_t  zm516x_cfg_info;
    awbl_zm516x_cfg_info_t  remote_info;

    /* ��ȡ ZM516X ģ���������Ϣ */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 0 failed\r\n"));
        goto exit;
    }

    /* �ָ� ZM516X ģ��������� */
    if (awbl_zm516x_default_set(__ID, zm516x_cfg_info.my_addr) != AW_OK) {
        AW_INFOF(("awbl_zm516x_default_set failed\r\n"));
        goto exit;
    }

    /* ��ȡ ZM516X ģ���������Ϣ */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 1 failed\r\n"));
        goto exit;
    }
    __cfg_info_print(&zm516x_cfg_info);

    /* ��������ͨ�� */
    for (i = 11; i <= 26; i++) {

        /* ���� ZM516X ģ��ͨ���� */
        if (awbl_zm516x_chan_set(__ID, i, TRUE) != AW_OK) {
            AW_INFOF(("awbl_zm516x_chan_set failed\r\n"));
            goto exit;
        }

        /* ��������ģ�� */
        if (awbl_zm516x_discover(__ID,
                                 6,
                                 base_info,
                                &get_size) != AW_OK) {
            AW_INFOF(("channel %d has not found the device\r\n", i));
        } else {
            AW_INFOF(("\r\nchannel %d has found %d device\r\n", i, get_size));

            for (j = 0; j < get_size; j++) {
                AW_INFOF(("-------------the %d-------------\r\n", j));
                __base_info_print(&base_info[j], 1);

                /* ��ȡָ����ַ�� ZM516X ģ����ź�ǿ�� */
                if (awbl_zm516x_sigal_get(__ID,
                                          base_info[j].addr,
                                         &signal) != AW_OK) {
                    AW_INFOF(("failed to get 0x%04x signal\r\n",
                              base_info[j].addr));
                } else {
                    AW_INFOF(("signal: %ddBm\r\n", signal / 3 - 95));
                }

                /* ��ȡָ����ַ�� ZM516X ģ���������Ϣ */
                if (awbl_zm516x_cfg_info_get(__ID,
                                             FALSE,
                                             base_info[j].addr,
                                            &remote_info) != AW_OK) {
                    AW_INFOF(("failed to get 0x%04x remote info\r\n",
                              base_info[j].addr));
                } else {
                    __cfg_info_print(&remote_info);
                }
            }
        }
    }

    AW_INFOF(("\r\nsearch complete, recovery the channal to %d\r\n",
                zm516x_cfg_info.chan));

    /* �ָ� ZM516X ģ��ͨ���� */
    if (awbl_zm516x_chan_set(__ID, zm516x_cfg_info.chan, TRUE) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_channel_set failed\r\n"));
        goto exit;
    }

    AW_INFOF(("ZM516X Search Done\r\n"));

exit:
    return;
}

/** [src_zm516x_search] */

/* end of file */
