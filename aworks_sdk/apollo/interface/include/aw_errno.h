/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ϵͳ����ֵ
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "aw_errno.h"
 * \endcode
 *
 * - ���е�ϵͳ����ֵ�������ﶨ�塣û�д��󷵻�0�����򷵻ض�Ӧ����ֵ�ĸ�ֵ��
 *   Ϊ�˼���POSIX�����ﶨ��������POSIX����ֵ��
 * - Apolloƽ̨ʹ�õĴ���ֵ����POSIX����ֵǰ�����AW_ǰ׺��
 *   ������Ҫʹ�ô���ֵ���ļ���Ӧ�ð������ļ���Apolloƽ̨�������Ӧ��ʹ��AW_
 *   ǰ׺�Ĵ���ֵ��������������ʹ����POSIX����ֵ����ֲʱ����ֱ��ʹ�ñ��ļ���
 * - Ϊ����ߴ�������ԣ���Ӧ��ʹ�ñ��ļ�֮�����ֵ��
 *
 * \internal
 * \par modification history:
 * - 1.10 14-01-17  zen, move errno code to platform
 * - 1.00 12-09-04  orz, first implementation.
 * \endinternal
 */

#ifndef __AW_ERRNO_H
#define __AW_ERRNO_H

#include "aw_psp_errno.h"

/**
 * \addtogroup grp_aw_if_errno
 * \copydoc aw_errno.h
 * @{
 */

/**
 * \name ���������������
 * @{
 */
typedef aw_psp_error_t     error_t;    /* ����POSIX�������� */
typedef aw_psp_aw_err_t    aw_err_t;   /* Apollo�������� */
/** @} */

/**
 * \name Apolloƽ̨�������ӿڣ���POSIX���ݣ�
 * @{
 */

/**
 * \brief ����errno
 * \note ���������������ڼ���֧��errno�Ͳ�֧��errno��ϵͳ����ϵͳ��֧��errno
 *      ʱ������Ǹ��ն��塣
 * \par ʹ��ʾ��
 * \code
 * AW_ERRNO_SET(ENODEV); // �൱�ڵ��ã�errno = ENODEV;
 * \endcode
 */
#define AW_ERRNO_SET(err)   AW_PSP_ERRNO_SET(err)

/**
 * \brief ��ȡerrno
 * \note
 *  - ���������������ڼ���֧��errno�Ͳ�֧��errno��ϵͳ����ϵͳ��֧��errno
 *    ʱ������Ǹ��ն��塣
 *  - ��ϵͳ��֧��errnoʱ��ʹ��������ȡ������ֵ�����壬��д����ʱӦע�⡣
 * \par ʹ��ʾ��
 * \code
 * AW_ERRNO_GET(err); // �൱�ڵ��ã�err = errno;
 * if (err) {
 *     ;              // ������
 * }
 * \endcode
 */
#define AW_ERRNO_GET(err)   AW_PSP_ERRNO_GET(err)
/* @} */

/* ����ĵĴ�������Ҫ��ƽ̨�ṩ */
#if 1

/**
 * \addtogroup grp_aw_if_posix_err ϵͳ�������ֵ��POSIX���ݣ�
 * @{
 */

/**
 * \name POSIX����ֵ
 * @{
 */
#define AW_EPERM           AW_PSP_EPERM         /* ���������� */
#define AW_ENOENT          AW_PSP_ENOENT        /* �ļ���Ŀ¼������ */
#define AW_ESRCH           AW_PSP_ESRCH         /* ���̲����� */
#define AW_EINTR           AW_PSP_EINTR         /* ���ñ��ж� */
#define AW_EIO             AW_PSP_EIO           /* I/O ���� */
#define AW_ENXIO           AW_PSP_ENXIO         /* �豸���ַ������ */
#define AW_E2BIG           AW_PSP_E2BIG         /* �����б�̫�� */
#define AW_ENOEXEC         AW_PSP_ENOEXEC       /* ��ִ���ļ���ʽ���� */
#define AW_EBADF           AW_PSP_EBADF         /* �ļ��������� */
#define AW_ECHILD          AW_PSP_ECHILD        /* û���ӽ��� */
#define AW_EAGAIN          AW_PSP_EAGAIN        /* ��Դ�����ã������� */
#define AW_ENOMEM          AW_PSP_ENOMEM        /* �ռ䣨�ڴ棩���� */
#define AW_EACCES          AW_PSP_EACCES        /* Ȩ�޲��� */
#define AW_EFAULT          AW_PSP_EFAULT        /* ��ַ���� */
#define AW_ENOTEMPTY       AW_PSP_ENOTEMPTY     /* Ŀ¼�ǿ� */
#define AW_EBUSY           AW_PSP_EBUSY         /* �豸����Դæ */
#define AW_EEXIST          AW_PSP_EEXIST        /* �ļ��Ѿ����� */
#define AW_EXDEV           AW_PSP_EXDEV         /* ���豸���� */
#define AW_ENODEV          AW_PSP_ENODEV        /* �豸������ */
#define AW_ENOTDIR         AW_PSP_ENOTDIR       /* ����Ŀ¼ */
#define AW_EISDIR          AW_PSP_EISDIR        /* ��Ŀ¼ */
#define AW_EINVAL          AW_PSP_EINVAL        /* ��Ч���� */
#define AW_ENFILE          AW_PSP_ENFILE        /* ϵͳ���ļ�̫�࣬������������ */
#define AW_EMFILE          AW_PSP_EMFILE        /* �򿪵��ļ�̫�� */
#define AW_ENOTTY          AW_PSP_ENOTTY        /* �����ʵ�I/O���Ʋ��� */
#define AW_ENAMETOOLONG    AW_PSP_ENAMETOOLONG  /* �ļ���̫�� */
#define AW_EFBIG           AW_PSP_EFBIG         /* �ļ�̫�� */
#define AW_ENOSPC          AW_PSP_ENOSPC        /* �豸ʣ��ռ䲻�� */
#define AW_ESPIPE          AW_PSP_ESPIPE        /* ��Ч��������Invalid seek�� */
#define AW_EROFS           AW_PSP_EROFS         /* �ļ�ϵͳֻ�� */
#define AW_EMLINK          AW_PSP_EMLINK        /* ����̫�� */
#define AW_EPIPE           AW_PSP_EPIPE         /* �𻵵Ĺܵ� */
#define AW_EDEADLK         AW_PSP_EDEADLK       /* ��Դ�������� */
#define AW_ENOLCK          AW_PSP_ENOLCK        /* �޿��ã����У����� */
#define AW_ENOTSUP         AW_PSP_ENOTSUP       /* ��֧�� */
#define AW_EMSGSIZE        AW_PSP_EMSGSIZE      /* ��Ϣ̫�� */
/** @} */

/**
 * \name ANSI����ֵ
 * @{
 */
#define AW_EDOM            AW_PSP_EDOM    /* ��ѧ��������������Χ */
#define AW_ERANGE          AW_PSP_ERANGE  /* ��ѧ����������̫�� */
#define AW_EILSEQ          AW_PSP_EILSEQ  /* �Ƿ����ֽ�˳�� */
/** @} */

/**
 * \name ��������������
 * @{
 */
#define AW_EDESTADDRREQ    AW_PSP_EDESTADDRREQ     /* ��ҪĿ���ַ */
#define AW_EPROTOTYPE      AW_PSP_EPROTOTYPE       /* socketЭ�����ʹ��� */
#define AW_ENOPROTOOPT     AW_PSP_ENOPROTOOPT      /* Э�鲻���� */
#define AW_EPROTONOSUPPORT AW_PSP_EPROTONOSUPPORT  /* Э�鲻֧�� */
#define AW_ESOCKTNOSUPPORT AW_PSP_ESOCKTNOSUPPORT  /* Socket���Ͳ�֧�� */
#define AW_EOPNOTSUPP      AW_PSP_EOPNOTSUPP       /* socket��֧�ָò��� */
#define AW_EPFNOSUPPORT    AW_PSP_EPFNOSUPPORT     /* Э���岻֧�� */
#define AW_EAFNOSUPPORT    AW_PSP_EAFNOSUPPORT     /* ��ַ�ز�֧�� */
#define AW_EADDRINUSE      AW_PSP_EADDRINUSE       /* ��ַ�Ѿ���ռ�� */
#define AW_EADDRNOTAVAIL   AW_PSP_EADDRNOTAVAIL    /* ��ַ������ */
#define AW_ENOTSOCK        AW_PSP_ENOTSOCK         /* ������������socket */
/** @} */

/**
 * \name ��ѡ��ʵ�ֵĴ���ֵ
 * @{
 */
#define AW_ENETUNREACH     AW_PSP_ENETUNREACH   /* ���粻�ɴ� */
#define AW_ENETRESET       AW_PSP_ENETRESET     /* �����ж������� */
#define AW_ECONNABORTED    AW_PSP_ECONNABORTED  /* �����ж� */
#define AW_ECONNRESET      AW_PSP_ECONNRESET    /* ���Ӹ�λ */
#define AW_ENOBUFS         AW_PSP_ENOBUFS       /* ����ռ䲻�� */
#define AW_EISCONN         AW_PSP_EISCONN       /* Socket�Ѿ����� */
#define AW_ENOTCONN        AW_PSP_ENOTCONN      /* Socketû������ */
#define AW_ESHUTDOWN       AW_PSP_ESHUTDOWN     /* Socket�Ѿ��رգ����ܷ������� */
#define AW_ETOOMANYREFS    AW_PSP_ETOOMANYREFS  /* ����̫�࣬�޷�ƴ�� */
#define AW_ETIMEDOUT       AW_PSP_ETIMEDOUT     /* ���ӳ�ʱ */
#define AW_ECONNREFUSED    AW_PSP_ECONNREFUSED  /* ���ӱ��ܾ� */
#define AW_ENETDOWN        AW_PSP_ENETDOWN      /* �����Ѿ�ֹͣ */
#define AW_ETXTBSY         AW_PSP_ETXTBSY       /* �ı��ļ�æ */
#define AW_ELOOP           AW_PSP_ELOOP         /* �������Ӽ���̫�� */
#define AW_EHOSTUNREACH    AW_PSP_EHOSTUNREACH  /* �������ɴ� */
#define AW_ENOTBLK         AW_PSP_ENOTBLK       /* �ǿ��豸 */
#define AW_EHOSTDOWN       AW_PSP_EHOSTDOWN     /* �����Ѿ��ر� */
/** @} */

/**
 * \name ���������ж�I/O����ֵ
 * @{
 */
#define AW_EINPROGRESS     AW_PSP_EINPROGRESS      /* �������ڽ����� */
#define AW_EALREADY        AW_PSP_EALREADY         /* ��������ʹ���� */
/* 70 */
#define AW_EWOULDBLOCK     AW_PSP_EWOULDBLOCK      /* ������������ͬEAGAIN�� */
#define AW_ENOSYS          AW_PSP_ENOSYS           /* ��֧�ֵĹ��ܣ�����δʵ�֣�*/
/** @} */

/**
 * \name �첽I/O����ֵ
 * @{
 */
#define AW_ECANCELED       AW_PSP_ECANCELED        /* �����Ѿ�ȡ�� */
/* 73 */                                          
/** @} */

/**
 * \name ����ش���ֵ
 * @{
 */
#define AW_ENOSR           AW_PSP_ENOSR            /* û������Դ */
#define AW_ENOSTR          AW_PSP_ENOSTR           /* �������豸 */
#define AW_EPROTO          AW_PSP_EPROTO           /* Э����� */
#define AW_EBADMSG         AW_PSP_EBADMSG          /* �𻵵���Ϣ */
#define AW_ENODATA         AW_PSP_ENODATA          /* ���������� */
#define AW_ETIME           AW_PSP_ETIME            /* ��ioctl()��ʱ */
#define AW_ENOMSG          AW_PSP_ENOMSG           /* û���������Ϣ���� */
#define AW_EUCLEAN         AW_PSP_EUCLEAN          /* Structure��Ҫ���� */
/** @} */

/** @} grp_aw_if_posix_err */

#endif  /* ... */

/** @} grp_aw_if_errno */

#endif /* __AW_ERRNO_H */

/* end of file */
