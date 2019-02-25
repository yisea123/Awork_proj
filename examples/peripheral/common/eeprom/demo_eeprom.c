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
 * \brief EEPROM ��ʾ����
 *
 * - ��������:
 *   1. aw_prj_params.h ��ʹ��
 *      - AW_DEV_EXTEND_EP24CXX_0
 *      - ����Ӧƽ̨�к�EEPROM�豸������I2C�궨��
 *   2. aw_nvram_set �� aw_nvram_get �ӿ��з���ʧ�Դ洢��Ϣ�����ֱ�����
 *      awbl_hwconf_ep24cxx_0.h �еĴ洢������һ�¡�
 *   3. EEPROM ���ò鿴 awbl_hwconf_ep24cxx_0.h
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ EEPROM ���������Ϣ��
 *   
 * \par Դ����
 * \snippet demo_eeprom.c src_eeprom
 *
 * \internal
 * \par History
 * - 1.00 17-09-04  may, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_src_eeprom
 * \copydoc demo_eeprom.c
 */
 
/** [src_eeprom] */
#include "aworks.h"

/* �������õ������·��� */
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_nvram.h"
#include "string.h"

#define BUF_SIZE  16                    /* ��д��������С */

aw_local uint8_t __g_buf[BUF_SIZE];     /* ��д������ */

/**
 * \brief EEPROM ��ʾ�������
 * \return ��
 */
void demo_eeprom_entry (void)
{
    int i = 0;

    for (i = 0; i < BUF_SIZE; i++) {
        __g_buf[i] = i & 0xFF;
    }

    /* ���� nvram �� ep24cxx ����,"ep24cxx"������ awbl_hwconf_ep24cxx_0.h�����ļ��в鿴*/
    if (aw_nvram_set("ep24cxx", 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("ep24cxx NVRAM: Write Failed!\r\n"));
        return;
    }

    memset(__g_buf, 0, BUF_SIZE);

    /* ��ȡ nvram �� ep24cxx ����,"ep24cxx"������ awbl_hwconf_ep24cxx_0.h�����ļ��в鿴*/
    if (aw_nvram_get("ep24cxx", 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("ep24cxx NVRAM: Write Failed!\r\n"));
        return;
    }

    for (i = 0; i < BUF_SIZE; i++) {
        if (__g_buf[i] != (i & 0xFF)) {
            AW_INFOF(("ep24cxx NVRAM: Verify Failed!\r\n"));
            return;
        }
    }

    AW_INFOF(("ep24cxx NVRAM: Verify Successful!\r\n"));
}

/** [src_eeprom] */

/* end of file */
