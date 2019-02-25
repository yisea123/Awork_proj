/*******************************************************************************
*                                 AWorks
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
 * \brief ����ͨѶ��׼�ӿ�
 *
 * ��ģ���ṩ���ڶ�д�����Ƶȷ���
 *
 * ʹ�ñ�ģ����Ҫ����ͷ�ļ� aw_serial.h
 *
 * \par ��ʾ��
 * \code
 * aw_serial_write(COM0, "Hello!", 7);  // COM0���"Hello!"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-29  orz, first implementation.
 * \endinternal
 */

#ifndef __AW_SERIAL_H
#define __AW_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_serial
 * \copydoc aw_serial.h
 * @{
 */

#include "aw_common.h"
#include "aw_sio_common.h"

/**
 * \name ��������
 * \brief Ŀǰ�ṩ���10�����ڣ���0��ʼ���
 * @{
 */
#define COM0    0
#define COM1    1
#define COM2    2
#define COM3    3
#define COM4    4
#define COM5    5
#define COM6    6
#define COM7    7
#define COM8    8
#define COM9    9
/** @} */

/**
 * \brief �����豸����
 *
 * - ��������������еĴ����豸ioctl����
 * - FIOBAUDRATEӳ�䵽��sio_ioct��SIO_BAUD_SET����������е�ioctl���ֱ��
 *   ������sio_ioctl����
 *
 * \param[in] com     ���ڱ��
 *
 * \param[in] request iotcl�������󣬲μ� aw_ioctl.h �� aw_sio_common.h ��
 *              ���õ����󼰲������£�
 *              @arg AW_FIONREAD���ɶ����ݸ���������Ϊint��ָ��
 *              @arg AW_FIONWRITE���Ѿ�д������ݸ���������Ϊint��ָ��
 *              @arg AW_FIOFLUSH����������������壬�޲���
 *              @arg AW_FIOSYNC��ͬFIOFLUSH
 *              @arg AW_FIODATASYNC��ͬFIOFLUSH
 *              @arg AW_FIOWFLUSH�����д���壬�޲���
 *              @arg AW_FIORFLUSH����ն����壬�޲���
 *              @arg AW_TIOCRDTIMEOUT�����ö��ȴ���ʱʱ�䣬��λ���룬����Ϊint����
 *              @arg AW_TIOISATTY������豸�Ƿ�TTY���ã��޲�����TTY�豸����trueֵ
 *              @arg SIO_BAUD_SET�����ô����豸�Ĳ����ʣ�����Ϊ������ֵ����9600
 *              @arg SIO_BAUD_GET����ȡ�����豸�Ĳ����ʣ�����Ϊint��ָ��
 *              @arg SIO_MODE_SET�����ô����豸��ģʽ������Ϊ��
 *                  - SIO_MODE_POLL����ѯģʽ
 *                  - SIO_MODE_INT���ж�ģʽ
 *              @arg SIO_MODE_GET����ȡ�����豸�ĵ�ǰģʽ������Ϊintָ�룬ֵΪ
 *                  SIO_MODE_POLL �� SIO_MODE_INT
 *              @arg SIO_AVAIL_MODES_GET����ȡ�����豸֧�ֵ�ģʽ������Ϊintָ�룬
 *                  SIO_MODE_POLL �� SIO_MODE_INT �������ࡰ�򡱺��ֵ
 *              @arg SIO_HW_OPTS_SET�����ô����豸��ͨѶ������
 *                  ֧�ֵĲ�������Щ���������໥���򡱣���
 *                  - CLOCAL�� ����Modem��״̬��ʹ��3��UARTʱ����ʹ���������
 *                  - CREAD��ʹ�ܽ������ݣ�Ĭ���Ѿ�ʹ��
 *                  - ����λ����
 *                      - CS5�� 5λ����λ
 *                      - CS6�� 6λ����λ
 *                      - CS7�� 7λ����λ
 *                      - CS8�� 8λ����λ
 *                  - STOPB������ֹͣλ�����������þ�Ĭ��Ϊ1λ��������Ϊ2λ
 *                  - PARENB����żУ��ʹ�����ã���������ر���żУ�飬��������
 *                      - PARENB��ʹ��żУ��
 *                      - (PARENB | PARODD)��ʹ����У��
 *              @arg SIO_HW_OPTS_GET����ȡ�����豸��ͨѶ����������Ϊintָ�룬ֵ
 *                  ��ο� SIO_HW_OPTS_SET �����õ�ֵ
 *
 * \param[in,out] p_arg   ioctl��������������������ͺ�ȡֵȡ���ڶ�Ӧ����������
 *
 * \return ����ֵΪ������룬�� aw_errno.h ������ȡ��������������ͷ���ֵ��
 *  - \b AW_OK     ����ɹ���û�д���
 *  - \b -EINVAL   com��������comֵ����ϵͳ���ô�������
 *  - \b -ENODEV   com��Ӧ�Ĵ����豸û���ҵ���ϵͳ�ڲ�����
 *  - \b -EIO      �豸ִ������ʧ�ܣ����ܵ�ԭ��Ϊ��������Ĳ�������ȷ��
 *                 �������豸�����ʳ����豸�Ŀ����÷�Χ
 *  - \b -ENOSYS   ���豸��֧�������������
 *
 * \par ����
 * \code
 * int baud;
 * aw_serial_ioctl(COM0, SIO_BAUD_SET, (void *)115200); // ���ò�����Ϊ115200bps
 * aw_serial_ioctl(COM0, SIO_BAUD_GET, (void *)baud);   // ��ȡ��ǰ������ֵ
 * aw_serial_ioctl(COM0, AW_TIOCRDTIMEOUT, (void *)20);    // ���ö���ʱΪ20����
 * // ���ô��ڲ���������modem��״̬��8������λ��1��ֹͣλ��ʹ����У��
 * aw_serial_ioctl(COM0, SIO_HW_OPTS_SET, (void *)(CLOCAL | CS8 | PARENB));
 * \endcode
 */
aw_err_t aw_serial_ioctl (int com, int request, void *p_arg);

/**
 * \brief �򴮿��豸д��nbytes���ֽ�����
 *
 * ����ӿ��򴮿��豸д��nbytes���ֽ����ݡ����豸���ڲ����岻�����������´���
 * - ���첽ģʽ�£�ʣ������ݲ��ᱻд�룬����ֵΪ�Ѿ�д������ݸ���
 * - ��ͬ��ģʽ�£����ڱ���ʱ�򿪸����ã������ûᱻ����ֱ�����е����ݶ���д��
 *
 * \param[in] com       ���ڱ��
 * \param[in] p_buffer  Ҫд���豸�����ݻ�����ָ��
 * \param[in] nbytes    Ҫд����ֽڸ���
 *
 * \return �ɹ�д������ݸ�����С��0Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴 errno
 */
ssize_t aw_serial_write (int com, const char *p_buffer, size_t nbytes);

/**
 * \brief �Ӵ����豸��ȡmaxbytes���ֽ�����
 *
 * - ����ӿڴӴ����豸�������maxbytes���ֽ�����
 * - ���豸�ɶ����ݸ���Ϊ0���������´���
 *   - ���첽ģʽ�£���������
 *   - ��ͬ��ģʽ�£����ڱ���ʱ�򿪸����ã������ûᱻ����ֱ�������ݿɶ�
 *
 * \param[in]  com      ���ڱ��
 * \param[out] p_buffer ��Ŷ�ȡ���ݵĻ�����ָ��
 * \param[in]  maxbytes ���Ҫ��ȡ���ֽڸ���
 *
 * \return �ɹ���ȡ�����ݸ�����С��0Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴errno
 */
ssize_t aw_serial_read (int com, char *p_buffer, size_t maxbytes);

/**
 * \brief ��ѯ��ʽ�򴮿��豸д��nbytes���ֽ�����
 *
 * ����ӿ�����ѯ��ʽ�򴮿��豸д��nbytes���ֽ�����
 *
 * \param[in] com       ���ڱ��
 * \param[in] p_buffer  Ҫд���豸�����ݻ�����ָ��
 * \param[in] nbytes    Ҫд����ֽڸ���
 *
 * \return �ɹ�д������ݸ�����С��0Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴errno
 */
ssize_t aw_serial_poll_write (int com, const char *p_buffer, size_t nbytes);

/**
 * \brief ����ѯ��ʽ�Ӵ����豸��ȡmaxbytes���ֽ�����
 *
 * - ����ӿ�����ѯ��ʽ�Ӵ����豸�������maxbytes���ֽ�����
 * - ����ӿڻ�����ֱ��������������
 *
 * \param[in]  com      ���ڱ��
 * \param[out] p_buffer ��Ŷ�ȡ���ݵĻ�����ָ��
 * \param[in]  maxbytes ���Ҫ��ȡ���ֽڸ���
 *
 * \return �ɹ���ȡ�����ݸ�����С��0Ϊʧ�ܣ�ʧ��ԭ��ɲ鿴errno
 */
ssize_t aw_serial_poll_read (int com, char *p_buffer, size_t maxbytes);

/** @} grp_aw_if_serial */

#ifdef __cplusplus
}
#endif

#endif /* __AW_SERIAL_H */

/* end of file */
