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
 * \brief ʹ���ļ�ϵͳ��д SPI Flash ʾ��
 *
 * - ��������:
 *   1. aw_prj_params.h��ʹ��
 *      - AW_DEV_SPI_FLASH0
 *      - ��Ӧƽ̨,��Ӧ��ŵ�SPI��(�û�����awbl_hwconf_spi_flash0.h�������ļ��鿴ʹ�þ����spi bus���)
 *      - AW_COM_FS_LFFS
 *      - AW_CFG_SPI_FLASH_MTD
 *      - AW_COM_CONSOLE
 *      - AW_COM_MTD_DEV
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3. aw_spi_flash_open�ӿ���Flash����("/sflash0")������ awbl_hwconf_spi_flash0.h
 *      �еĴ洢������һ�¡�
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ���������Ϣ��
 *
 * \par Դ����
 * \snippet demo_spi_flash_fs.c src_spi_flash_fs
 *
 * \internal
 * \par History
 * - 1.00 17-09-05  deo, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spi_flash_fs
 * \copydoc demo_spi_flash_fs.c
 */

/** [src_spi_flash_fs] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "fs/aw_mount.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "io/aw_dirent.h"
#include "io/sys/aw_stat.h"

/**
 * \brief ʹ���ļ�ϵͳ��д SPI Flash ʾ��
 * \return ��
 */
void demo_spi_flash_fs_entry (void)
{
    aw_err_t    ret;
    int         fd, i;
    static char buf[512];

    /* ��һ��ʹ�ý��и�ʽ��
     * "/sflash0" ������Ҫ�鿴 awbl_hwconf_spi_flash0.h
     */
    struct aw_fs_format_arg fmt = {"awdisk", 4*1024, 1};
    ret = aw_make_fs("/sflash0", "lffs", &fmt );
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash make LFFS failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash make LFFS done.\r\n");

    /* ���� ��/sflash0�� �� ��/sf�� */
    ret = aw_mount("/sf", "/sflash0", "lffs", 0);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash mount LFFS failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash mount LFFS done.\r\n");

    /* ��test.txt�ļ�������������򴴽� */
    fd = aw_open("/sf/test.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd < 0) {
        aw_kprintf("SPI-Flash create file failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash create file done.\r\n");

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = (char)(i & 0xFF);
    }

    /* д������ */
    ret = aw_write(fd, buf, sizeof(buf));
    if (ret != sizeof(buf)) {
        aw_close(fd);
        aw_kprintf("SPI-Flash write file failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash write file done.\r\n");

    /* �ر��ļ� */
    aw_close(fd);
    aw_kprintf("SPI-Flash close file.\r\n");

    /* ���´��ļ� */
    fd = aw_open("/sf/test.txt", O_RDONLY, 0777);
    if (fd < 0) {
        aw_kprintf("SPI-Flash open file failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash open file done.\r\n");

    /* �������� */
    ret = aw_read(fd, buf, sizeof(buf));
    if (ret != sizeof(buf)) {
        aw_close(fd);
        aw_kprintf("SPI-Flash read file failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash read file done.\r\n");

    /* �ر��ļ� */
    aw_close(fd);
    aw_kprintf("SPI-Flash close file.\r\n");

    /* У���д�����Ƿ�һ�� */
    for (i = 0; i < sizeof(buf); i++) {
        if (buf[i] != (char)(i & 0xFF)) {
            aw_kprintf("SPI-Flash verify file data failed at %d.\r\n", i);
            goto __exit;
        }
    }

    aw_kprintf("SPI-Flash verify file data successfully.\r\n");

__exit:
    return ;
}

/** [src_spi_flash_fs] */

/* end of file */
