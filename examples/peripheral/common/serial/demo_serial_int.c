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
 * \brief ������ʾ���̣��ж�ģʽ
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *   2. ʹ�ñ�����ʱ��������shell (AW_COM_SHELL_SERIAL)����shell��ʹ�ò���ΪCOM0(��Ϊshell���ȡ��������)
 *
 * - ʵ������
 *   1. �������ȴ�ӡ"Hello,Enter Serial INT Mode:"��
 *   2. Ȼ�󴮿ڽ����ж϶�дģʽ��������������λ���������ݣ����ڽ����յ������ݷ��ظ���λ����
 *
 * - ��ע��
 *   1. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_serial_int.c src_serial_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_serial_int
 * \copydoc demo_serial_int.c
 */

/** [src_serial_int] */
#include "aworks.h"

#include "aw_delay.h"
#include "aw_serial.h"
#include "aw_ioctl.h"

#define  TEST_SERIAL_NUM   COM0

/**
 * \brief ���� demo
 * \return ��
 */
void demo_serial_int_entry (void)
{
    char    buf[32];
    int     len = 0;
    int     i   = 0;

    /* ���ڳ�ʼ������ ������115200 */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_BAUD_SET, (void *)115200);

    /* ���ڲ��� ��8������λ 1��ֹͣλ������żУ�� */
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_HW_OPTS_SET, (void *)(CS8 | CLOCAL | CREAD));

    // ��մ����������������
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_FIOFLUSH, NULL);

    // ���ô��ڶ�ȡ��ʱʱ��
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOCRDTIMEOUT, (void *)10);

    // ����Ϊ�ж�ģʽ
    aw_serial_ioctl(TEST_SERIAL_NUM, SIO_MODE_SET, (void *)SIO_MODE_INT);

    // ��������
    aw_serial_write(TEST_SERIAL_NUM, "Hello,Enter Serial INT  Mode:\r\n", 32);

    AW_FOREVER {
        // ��ȡ����
        len = aw_serial_read(TEST_SERIAL_NUM, buf, 10);
        if (len > 0) {
            aw_serial_write(TEST_SERIAL_NUM, buf, len);
        }
        aw_serial_write(TEST_SERIAL_NUM, "\r\n", 2);
    }

}

/** [src_serial_int] */

/* end of file */
