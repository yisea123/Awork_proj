/*******************************************************************************
 *                                 AWorks
 *                       ---------------------------
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
 * \brief ʹ��NVRAM �ӿڶ�д SPI Flash ��ʾ����
 *
 * - ��������:
 *   1. aw_prj_params.h ��ʹ��
 *      - AW_DEV_SPI_FLASH0
 *      - ��Ӧƽ̨�ģ���Ӧ��ŵ�SPI��
 *      - AW_COM_CONSOLE
 *      - AW_CFG_SPI_FLASH_NVRAM
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3.  aw_nvram_set �� aw_nvram_get �ӿ��з���ʧ�Դ洢��Ϣ�����ֱ�����
 *      awbl_hwconf_spi_flash1.h �еĴ洢������һ�¡�
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ���������Ϣ��
 *
 * \par Դ����
 * \snippet demo_spi_flash_nvram.c src_spi_flash_nvram
 *
 * \internal
 * \par History
 * - 1.00 17-09-05  deo, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spi_flash_nvram
 * \copydoc demo_spi_flash_nvram.c
 */

/** [src_spi_flash_nvram] */
#include "aworks.h"             /* ��ͷ�ļ����뱻���Ȱ��� */

/* �������õ������·��� */
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_nvram.h"
#include "string.h"

#define BUF_SIZE  255               /* ��д��������С */

static uint8_t __g_buf[BUF_SIZE];   /* ��д������ */

#define TEST_MEM_NAME       "spi_flash0_nvram"          /*�洢�����ƣ����������޸�*/
/**
 * \brief ʹ��NVRAM �ӿڶ�д SPI Flash ��ʾ����
 * \return ��
 */
void demo_spi_flash_nvram_entry (void)
{
    uint32_t i;

    for (i = 0; i < BUF_SIZE; i++) {
        __g_buf[i] = i & 0xFF;
    }

    /* ���� nvram �� spi_flash0_nvram ����*/
    if (aw_nvram_set(TEST_MEM_NAME, 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("SPIFLASH NVRAM: Write Failed!\r\n"));
        return ;
    }

    memset(__g_buf, 0, BUF_SIZE);

    /* ��ȡ nvram �� spi_flash0_nvram0 ����*/
    if (aw_nvram_get(TEST_MEM_NAME, 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("SPIFLASH NVRAM: Write Failed!\r\n"));
        return ;
    }

    for (i = 0; i < BUF_SIZE; i++) {
        if (__g_buf[i] != (i & 0xFF)) {
            AW_INFOF(("SPIFLASH NVRAM: Verify Failed!\r\n"));
            return;
        }
    }

    AW_INFOF(("SPIFLASH NVRAM: Verify Successful!\r\n"));
}

/** [src_spi_flash_nvram] */

/* end of file */
