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
 * \brief ������ʾ���̣�rx�жϻص���ʾ
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *   2. ʹ�ñ�����ʱ��������shell (AW_COM_SHELL_SERIAL)����shell��ʹ�ò���ΪCOM0(��Ϊshell���ȡ��������)
 *
 * - ʵ������
 *   1.����demo�󣬴����������ݣ���rx�ص������м�����ݣ������յ���'A',����������
 *
 * - ��ע��
 *   1. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_serial_rx_callback.c src_serial_rx_callback
 *
 * \internal
 * \par Modification History
 * - 1.00 16-03-24  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_serial_rx_callback
 * \copydoc demo_serial_rx_callback.c
 */

/** [src_serial_rx_callback] */
#include "aworks.h"

#include "aw_delay.h"
#include "aw_serial.h"
#include "aw_ioctl.h"
#include "aw_led.h"
#include "aw_vdebug.h"

#define  TEST_SERIAL_NUM   COM0

/**
 * \brief �����жϻص�����
 * \param p_arg �ص�����
 * \param ch    ���յ����ַ�
 *
 * \return      ���Э�鲻��Ҫ��������\a ch �򷵻�1�����򷵻�0
 */
aw_local int  __rx_callback(void *p_arg, char ch){

    if(ch == 'A'){

        /*����1�� ������ַ�'A'������*/
        return 1;
    }else{

        /*����0����������ַ�'A',����*/
        return 0;
    }

}
/**
 * \brief ���� demo(rx�ж�)
 * \return ��
 */
void demo_serial_rx_callback_entry (void)
{
    char    buf[32];
    int     len = 0;

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

    //����rx�жϻص�����
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOPROTOHOOK,(void *) __rx_callback);

    //����rx�жϻص���������
    aw_serial_ioctl(TEST_SERIAL_NUM, AW_TIOPROTOARG, NULL);

    AW_FOREVER{
        len = aw_serial_read(TEST_SERIAL_NUM,buf,sizeof(buf));
        aw_serial_write(TEST_SERIAL_NUM,buf,len);
    }

    return ;
}
/** [src_serial_rx_callback] */

/* end of file */
