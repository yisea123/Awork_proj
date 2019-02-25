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
 * \brief U��ʹ���ļ�ϵͳ���ж�д��ʾ����
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨��USB��
 *      - AW_COM_FS_FATFS
 *      - AW_COM_CONSOLE
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *   3. �ڿ����� USBHost1 ����U��.
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ϣ��
 *
 * \par Դ����
 * \snippet demo_udisk_fs.c src_udisk_fs
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-08  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_udisk_fs
 * \copydoc demo_udisk_fs.c
 */

/** [src_udisk_fs] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "fs/aw_mount.h"
#include "io/aw_fcntl.h"
#include "io/aw_unistd.h"
#include "io/sys/aw_stat.h"
#include "fs/aw_blk_dev.h"
#include "string.h"

/*
 * U�̿��豸����/dev/hx-dy-z
 * 1. x: ���� USB host�ڱ�ţ�
 *    �����USB1, ��ôx==0
 *    �����USB2, ��ôx==1
 * 2. y: �����豸����host��ַ
 * 3. z�������߼���Ԫ��
 * 4. �����ȷ���豸�������Բ鿴U�̲���󴮿ڴ�ӡ��Ϣ���磺
      USB-HUB:new device (VID&048d_PID&1172).
      Manufacturer: Generic
      Product: USB Mass Storage Device
      Serial: 5EE8D32C07043B44
      USBH-MS: luns0's capacity is: 7800 MB
      USBH-MS: /dev/h1-d1-0.
      ���Կ������豸��Ϊ��/dev/h1-d1-0
 */
#define     __BLK_NAME              "/dev/h1-d1-0"


static void __disk_evt_cb (const char *name, int event, void *p_arg)
{
    /* ͨ�� U�� �Ŀ��豸�����ж��Ƿ�Ϊ U�� ��� */
    if (strcmp(name, __BLK_NAME)) {
        return;
    }

    if (event == AW_BD_EVT_INJECT) {
        AW_INFOF(("udisk insert...\r\n"));
    }

    if (event == AW_BD_EVT_EJECT) {
        AW_INFOF(("udisk remove...\r\n"));
    }
}


static void __fs_file_rw (void)
{
    int         i = 0;
    int         handle;
    char       *p_file_name = "/u/aworks_udisk_test.txt";
    uint8_t     str_buf[256] = {0};

    /*
     * д�ļ����ԣ������������ļ�д�������رղ�����
     */
    /* �������ļ� */
    handle = aw_open(p_file_name, O_RDWR | O_CREAT, 0777);
    if (handle < 0) {
        AW_ERRF(("creat file error: %d\n", handle));
        return;
    }
    AW_INFOF(("creat file %s ok\n", p_file_name));

    for (i = 0; i < sizeof(str_buf); i++) {
        str_buf[i] = (uint8_t)i;
    }

    /* д�ļ� */
    if (aw_write(handle, str_buf, sizeof(str_buf)) != sizeof(str_buf)) {
        aw_close(handle);
        AW_ERRF(("write file error\n"));
        return;
    }
    AW_INFOF(("write file %s ok\n", p_file_name));

    /* �ر��ļ� */
    aw_close(handle);
    AW_INFOF(("close file %s ok\n", p_file_name));

    /*
     * ���ļ����ԣ������򿪣��ļ����������رղ�����
     */
    /* ���ļ� */
    handle = aw_open(p_file_name, O_RDONLY, 0777);
    if (handle < 0) {
        AW_ERRF(("open file error: %d\n", handle));
        return;
    }
    AW_INFOF(("open file %s ok\n", p_file_name));

    memset(str_buf, 0, sizeof(str_buf));

    /* ��ȡ�ļ� */
    if (aw_read(handle, str_buf, sizeof(str_buf)) != sizeof(str_buf)) {
        aw_close(handle);
        AW_ERRF(("read file error!\n"));
        return;
    }
    AW_INFOF(("read file %s ok\n", p_file_name));

    /* ���������Ƿ���ȷ */
    for (i = 0; i < sizeof(str_buf); i++) {
        if ((uint8_t)i != str_buf[i]) {
            AW_ERRF(("file data error!\n"));
            aw_close(handle);
            return;
        }
    }
    AW_INFOF(("file %s data check ok\n", p_file_name));
}

/**
 * \brief U���ļ�ϵͳ�������
 * \return ��
 *
 * \note ����12B�汾fatfs�ļ�ϵͳ����Ҫ��֤�����ջ��С��4K
 */
void demo_udisk_fs_entry (void)
{
    aw_err_t ret;
    bool_t   regist_ok = TRUE;
    int      event_index = 0;


    /*
     * ��ӿ��豸����¼����, ����U�̲��ʱ, ��ص�__disk_evt_cb
     */
    ret = aw_blk_dev_event_register(__disk_evt_cb, NULL, &event_index);
    if (ret != AW_OK) {
        AW_ERRF(("block event register error: %d!\n", ret));
        regist_ok = FALSE;
    }

    /* ���U�̿��豸�Ƿ���� */
    ret = aw_blk_dev_wait_install(__BLK_NAME, 10000);
    if (ret != AW_OK) {
        AW_ERRF(("wait udisk insert failed, err = %d\r\n", ret));
        goto __task_udisk_fs_end;
    }


#if 0  /* ��ʽ��һ�μ���  */
    /* ����Ϊ"awdisk"�� ���СΪ4k  */
    struct aw_fs_format_arg fmt = {"awdisk", 1024 * 4, 0};
    /* �����ļ�ϵͳ �����洢����Ϊ "/dev/sd0"����Ϊ"vfat"���͵��ļ�ϵͳ  */
    if ((ret = aw_make_fs(__BLK_NAME, "vfat", &fmt)) != AW_OK) {
        AW_ERRF(("failed: %d\n", ret));
        goto __task_udisk_fs_end;
    }
    AW_INFOF(("make fs OK\n"));

#endif

    /* �ļ�ϵͳ���ص� "/u" ���  */
    ret = aw_mount("/u", __BLK_NAME, "vfat", 0);
    if (ret != AW_OK) {
        AW_ERRF(("/u mount FATFS error: %d!\n", ret));
        goto __task_udisk_fs_end;
    }
    AW_INFOF(("mount OK\n"));

    /* U�̶�д����  */
    __fs_file_rw();


__task_udisk_fs_end:
    /* ע���¼� */
    if (regist_ok) {
        ret = aw_blk_dev_event_unregister(event_index);
        if (ret != AW_OK) {
            AW_ERRF(("block event unregister error: %d!\n", ret));
        }
    }

    return ;
}

/** [src_udisk_fs] */
 
/* end of file */
