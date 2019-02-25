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
 * \brief ZM516X ģ�鴫���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ա� Demo ��Ҫʹ�����鿪���壬���鿪������Ҫ���ز�ͬ�ĳ���
 *      ����һ�鿪����򿪺� USE_BORD0���رպ� USE_BORD1�����벢���س���
 *      ����һ�鿪����򿪺� USE_BORD1���رպ� USE_BORD0�����벢���س���
 *   2. ���Ա� Demo ������ aw_prj_params.h ��ʹ��
 *       - AW_DEV_ZM516X_0
 *       - ��Ӧƽ̨��zigbeeģ�������Ĵ��ں�
 *   3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� DUART_RX �������� PC ���ڵ� TXD��
 *       DUART_TX �������� PC ���ڵ� RXD��
 *
 * - ʵ������
 *   1. ��� ZM516X ģ���ʼ�������óɹ������Դ��ڴ�ӡ "ZM516X Initial Done\r\n"��
 *      �����ʼ��ʧ�ܣ����Դ��ڴ�ӡ��Ӧ������Ϣ��
 *   2. ���Դ��ڴ�ӡ��ȡ����ģ��������Ϣ��
 *   3. �������Է����� 10 �����ݣ�������ͳɹ�����ͨ�����ڴ�ӡ
 *      "send data success"�������ʧ�ܣ���ͨ�����ڴ�ӡ
 *      "send data failed"��
 *   4. ���պ����յ��Է����͹��������ݺ󣬵��Դ��ڽ����յ��������������������Ϊ
 *      "received data from 0x****: I'm 0x**"��
 *
 * - ��ע��
 *   1. Zigbee ģ����GPIO�������ӹ�ϵ��Ҫ�鿴zigbee�������ļ�awbl_hwconf_zm516x.h,
 *      �����Ҫʹ�� Zigbee����Щ IO �ڲ�������������;��
 *
 * \par Դ����
 * \snippet demo_zm516x_transfer.c src_zm516x_transfer
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-23  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_zm516x_transfer
 * \copydoc demo_zm516x_transfer.c
 */

/** [src_zm516x_transfer] */
#include "aworks.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "driver/zigbee/awbl_zm516x.h"
#include <string.h>

#define USE_BORD0            /**< \brief ʹ�øú�ʱ�����������ڵ��� 0 */
//#define USE_BORD1          /**< \brief ʹ�øú�ʱ�����������ڵ��� 1 */

/** \brief �����豸�ţ���Ҫ�� awbl_hwconf_zm516x_0.h �ļ��ڵ�ֵ��ͬ */
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
 * \brief zm516x�����շ��������
 */
void demo_zm516x_transfer_entry (void)
{
    char                   send_buf[11] = "I'm 0x00\r\n";
    int                    ret = 0;

#ifdef USE_BORD0
    uint16_t               src_addr = 0x2001;
    uint16_t               dst_addr = 0x2002;
#endif

#ifdef  USE_BORD1
    uint16_t               src_addr = 0x2002;
    uint16_t               dst_addr = 0x2001;
#endif
    uint16_t               addr_tmp;

    uint8_t                buf[20] = {0};
    uint32_t               send_tick = 0;
    awbl_zm516x_cfg_info_t zm516x_cfg_info;

    AW_INFOF(("src_addr: 0x%04x dst_addr: 0x%04x\n", src_addr, dst_addr));

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
    addr_tmp = zm516x_cfg_info.my_addr;

    zm516x_cfg_info.my_addr = src_addr;
    zm516x_cfg_info.dst_addr = dst_addr;
    zm516x_cfg_info.panid = 0x1001;

    /* �޸� ZM516X ģ���������Ϣ */
    if (awbl_zm516x_cfg_info_set(__ID, addr_tmp, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_set failed\r\n"));
        goto exit;
    }

    /* ����ָ����ַ�� ZM516X ģ����յ����ݰ���ͷ�Ƿ���ʾԴ��ַ */
    if (awbl_zm516x_display_head_set(__ID, TRUE, TRUE) != AW_OK) {
        AW_INFOF(("awbl_zm516x_display_head_set failed\r\n"));
        goto exit;
    }

    /**
     * ���� ZM516X ģ������������ģʽ����Ҫ�������ԣ�ZM516X ������ߺ�
     * ֻ�ܸ�λģ����ģ��� WAKE ��������������ģ��
     */
//    awbl_zm516x_enter_deep_sleep(__ID);

    /* ��ȡ ZM516X ģ���������Ϣ */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 2 failed\r\n"));
        goto exit;
    }
    __cfg_info_print(&zm516x_cfg_info);

    AW_INFOF(("ZM516X Initial Done\r\n"));

    AW_FOREVER {

        if ((send_tick++ % 100) == 0) {
            send_buf[7] = (src_addr & 0x0F) + '0';
            if (awbl_zm516x_send_with_ack(__ID,
                                        send_buf,
                                        strlen(send_buf)) != strlen(send_buf)) {
                AW_INFOF(("send data failed\r\n"));

            } else {
                AW_INFOF(("send data success\r\n"));
            }
        }

        /* awbl_zm516x_receive �����Ķ���ʱΪ 10ms */
        ret = awbl_zm516x_receive(__ID, buf, sizeof(buf));

        if (ret > 0) {
            AW_INFOF(("received data from 0x%02x%02x: %s\r\n",
                      buf[0],
                      buf[1],
                      buf + 2));
            memset(buf, 0x00, sizeof(buf));
        }

        if (send_tick == 1000) {
            goto exit;
        }
        aw_mdelay(1);
    }

exit:
    return;
}

/** [src_zm516x_transfer] */

/* end of file */
