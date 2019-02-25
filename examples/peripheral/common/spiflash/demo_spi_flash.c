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
 * \brief SPI Flash
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��
 *      - AW_DEV_SPI_FLASH0
 *      - ��Ӧƽ̨,��Ӧ��ŵ�SPI��(�û�����awbl_hwconf_spi_flash0.h�������ļ��鿴ʹ�þ����spi bus���)
 *      - AW_COM_CONSOLE
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3. aw_spi_flash_open�ӿ���Flash����("/sflash0")������ awbl_hwconf_spi_flash0.h
 *      �еĴ洢������һ�¡�
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ���������Ϣ��
 *
 * \par Դ����
 * \snippet demo_spi_flash.c src_spi_flash
 *
 * \internal
 * \par History
 * - 1.00 17-09-05  deo, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spi_flash
 * \copydoc demo_spi_flash.c
 */

/** [src_spi_flash] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "aw_spi_flash.h"

/**
 * \brief SPI Flash ��ʾ����
 * \return ��
 */
void demo_spi_flash_entry (void)
{
    aw_spi_flash_t      pflash;
    aw_spi_flash_info_t info;
    aw_err_t            ret;
    static char         buf[512];
    uint32_t            i;

    /* ��SPI Flash */
    pflash = aw_spi_flash_open("/sflash0");
    if (pflash == NULL) {
        aw_kprintf("No SPI Flash found!\r\n");
        while (1) {
            aw_mdelay(-1);
        }
    }

    /* ��ȡ�豸��Ϣ */
    ret = aw_spi_flash_info_get(pflash, &info);
    if (ret == AW_OK) {
        aw_kprintf("SPI-Flash block size   %d bytes.\r\n", info.block_size);
        aw_kprintf("SPI-Flash block counts %d.\r\n",       info.nblocks);
        aw_kprintf("SPI-Flash page size    %d bytes.\r\n", info.page_size);
    }

    /* ������0���� */
    ret = aw_spi_flash_erase(pflash, 0);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash erase Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash erase Flash done.\r\n");

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = (char)(i & 0xFF);
    }

    /* д�����ݵ���0���� */
    ret = aw_spi_flash_write(pflash, 0, buf, sizeof(buf), NULL);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash write Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash write Flash done.\r\n");

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = 0;
    }

    /* ���ص�0�������� */
    ret = aw_spi_flash_read(pflash, 0, buf, sizeof(buf), NULL);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash read Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash read Flash done.\r\n");

    /* У���д�����Ƿ�һ�� */
    for (i = 0; i < sizeof(buf); i++) {
        if (buf[i] != (char)(i & 0xFF)) {
            aw_kprintf("SPI-Flash verify Flash data failed at %d.\r\n", i);
            goto __exit;
        }
    }

    aw_kprintf("SPI-Flash verify Flash data successfully.\r\n");

__exit:
    /* �ر�SPI FLASH�豸 */
    aw_spi_flash_close(pflash);

    return ;
}

/** [src_spi_flash] */

/* end of file */
