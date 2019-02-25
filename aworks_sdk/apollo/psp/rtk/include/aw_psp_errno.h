/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief aworks1.0  errno ��׼�ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 13-03-05  zen, first implementation
 * \endinternal
 */

#ifndef __AW_PSP_ERRNO_H
#define __AW_PSP_ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \name ���������������
 * @{
 */
typedef int aw_psp_error_t;    /* ����POSIX�������� */
typedef int aw_psp_aw_err_t;   /* Apollo�������� */
/** @} */

/**
 * \name POSIX���ݴ������ӿ�
 * @{
 */

/* ��ȡ����ֵ��ַ����ƽ̨ʵ�� */
extern aw_psp_error_t *__errno(void);

/**
 * \brief ��ȡ�����ô���ֵ
 * \par ʹ��ʾ��
 * \code
 * if (condition) {      // �Ƿ����
 *     errno = EIO;      // ���ô�����
 * }
 * if (EBUSY == errno) { // �ж��Ƿ��豸æ����
 *     ;                 // �豸æ������
 * }
 * \endcode
 */
#ifndef errno
#ifdef __cplusplus
aw_inline  aw_psp_error_t &__errno_cpp()
{
    return  (*__errno());
}
#define errno   __errno_cpp()
#else  /* __cplusplus */
#define errno   (*__errno())
#endif /* __cplusplus */
#endif /* errno */

/* @} */

/******************************************************************************/
#define AW_PSP_ERRNO_GET(err)  do {(err) = errno;}while(0)
#define AW_PSP_ERRNO_SET(err)  do {errno = (err);}while(0)

/******************************************************************************/
/**
 * \addtogroup grp_aw_if_posix_err ϵͳ�������ֵ��POSIX���ݣ�
 * @{
 */

/**
 * \name POSIX����ֵ
 * @{
 */
#define EPERM           1   /* ���������� */
#define ENOENT          2   /* �ļ���Ŀ¼������ */
#define ESRCH           3   /* ���̲����� */
#define EINTR           4   /* ���ñ��ж� */
#define EIO             5   /* I/O ���� */
#define ENXIO           6   /* �豸���ַ������ */
#define E2BIG           7   /* �����б�̫�� */
#define ENOEXEC         8   /* ��ִ���ļ���ʽ���� */
#define EBADF           9   /* �ļ��������� */
#define ECHILD          10  /* û���ӽ��� */
#define EAGAIN          11  /* ��Դ�����ã������� */
#define ENOMEM          12  /* �ռ䣨�ڴ棩���� */
#define EACCES          13  /* Ȩ�޲��� */
#define EFAULT          14  /* ��ַ���� */
#define ENOTEMPTY       15  /* Ŀ¼�ǿ� */
#define EBUSY           16  /* �豸����Դæ */
#define EEXIST          17  /* �ļ��Ѿ����� */
#define EXDEV           18  /* ���豸���� */
#define ENODEV          19  /* �豸������ */
#define ENOTDIR         20  /* ����Ŀ¼ */
#define EISDIR          21  /* ��Ŀ¼ */
#define EINVAL          22  /* ��Ч���� */
#define ENFILE          23  /* ϵͳ���ļ�̫�࣬������������ */
#define EMFILE          24  /* �򿪵��ļ�̫�� */
#define ENOTTY          25  /* �����ʵ�I/O���Ʋ��� */
#define ENAMETOOLONG    26  /* �ļ���̫�� */
#define EFBIG           27  /* �ļ�̫�� */
#define ENOSPC          28  /* �豸ʣ��ռ䲻�� */
#define ESPIPE          29  /* ��Ч��������Invalid seek�� */
#define EROFS           30  /* �ļ�ϵͳֻ�� */
#define EMLINK          31  /* ����̫�� */
#define EPIPE           32  /* �𻵵Ĺܵ� */
#define EDEADLK         33  /* ��Դ�������� */
#define ENOLCK          34  /* �޿��ã����У����� */
#define ENOTSUP         35  /* ��֧�� */
#define EMSGSIZE        36  /* ��Ϣ̫�� */

#define AW_PSP_EPERM          EPERM         /* ���������� */
#define AW_PSP_ENOENT         ENOENT        /* �ļ���Ŀ¼������ */
#define AW_PSP_ESRCH          ESRCH         /* ���̲����� */
#define AW_PSP_EINTR          EINTR         /* ���ñ��ж� */
#define AW_PSP_EIO            EIO           /* I/O ���� */
#define AW_PSP_ENXIO          ENXIO         /* �豸���ַ������ */
#define AW_PSP_E2BIG          E2BIG         /* �����б�̫�� */
#define AW_PSP_ENOEXEC        ENOEXEC       /* ��ִ���ļ���ʽ���� */
#define AW_PSP_EBADF          EBADF         /* �ļ��������� */
#define AW_PSP_ECHILD         ECHILD        /* û���ӽ��� */
#define AW_PSP_EAGAIN         EAGAIN        /* ��Դ�����ã������� */
#define AW_PSP_ENOMEM         ENOMEM        /* �ռ䣨�ڴ棩���� */
#define AW_PSP_EACCES         EACCES        /* Ȩ�޲��� */
#define AW_PSP_EFAULT         EFAULT        /* ��ַ���� */
#define AW_PSP_ENOTEMPTY      ENOTEMPTY     /* Ŀ¼�ǿ� */
#define AW_PSP_EBUSY          EBUSY         /* �豸����Դæ */
#define AW_PSP_EEXIST         EEXIST        /* �ļ��Ѿ����� */
#define AW_PSP_EXDEV          EXDEV         /* ���豸���� */
#define AW_PSP_ENODEV         ENODEV        /* �豸������ */
#define AW_PSP_ENOTDIR        ENOTDIR       /* ����Ŀ¼ */
#define AW_PSP_EISDIR         EISDIR        /* ��Ŀ¼ */
#define AW_PSP_EINVAL         EINVAL        /* ��Ч���� */
#define AW_PSP_ENFILE         ENFILE        /* ϵͳ���ļ�̫�࣬������������ */
#define AW_PSP_EMFILE         EMFILE        /* �򿪵��ļ�̫�� */
#define AW_PSP_ENOTTY         ENOTTY        /* �����ʵ�I/O���Ʋ��� */
#define AW_PSP_ENAMETOOLONG   ENAMETOOLONG  /* �ļ���̫�� */
#define AW_PSP_EFBIG          EFBIG         /* �ļ�̫�� */
#define AW_PSP_ENOSPC         ENOSPC        /* �豸ʣ��ռ䲻�� */
#define AW_PSP_ESPIPE         ESPIPE        /* ��Ч��������Invalid seek�� */
#define AW_PSP_EROFS          EROFS         /* �ļ�ϵͳֻ�� */
#define AW_PSP_EMLINK         EMLINK        /* ����̫�� */
#define AW_PSP_EPIPE          EPIPE         /* �𻵵Ĺܵ� */
#define AW_PSP_EDEADLK        EDEADLK       /* ��Դ�������� */
#define AW_PSP_ENOLCK         ENOLCK        /* �޿��ã����У����� */
#define AW_PSP_ENOTSUP        ENOTSUP       /* ��֧�� */
#define AW_PSP_EMSGSIZE       EMSGSIZE      /* ��Ϣ̫�� */
/** @} */


/**
 * \name ANSI����ֵ
 * @{
 */
#define EDOM            37  /* ��ѧ��������������Χ */
#define ERANGE          38  /* ��ѧ����������̫�� */
#define EILSEQ          39  /* �Ƿ����ֽ�˳�� */

#define AW_PSP_EDOM            EDOM    /* ��ѧ��������������Χ */
#define AW_PSP_ERANGE          ERANGE  /* ��ѧ����������̫�� */
#define AW_PSP_EILSEQ          EILSEQ  /* �Ƿ����ֽ�˳�� */      
/** @} */ 


/**
 * \name ��������������
 * @{
 */
#define EDESTADDRREQ    40  /* ��ҪĿ���ַ */
#define EPROTOTYPE      41  /* socketЭ�����ʹ��� */
#define ENOPROTOOPT     42  /* Э�鲻���� */
#define EPROTONOSUPPORT 43  /* Э�鲻֧�� */
#define ESOCKTNOSUPPORT 44  /* Socket���Ͳ�֧�� */
#define EOPNOTSUPP      45  /* socket��֧�ָò��� */
#define EPFNOSUPPORT    46  /* Э���岻֧�� */
#define EAFNOSUPPORT    47  /* ��ַ�ز�֧�� */
#define EADDRINUSE      48  /* ��ַ�Ѿ���ռ�� */
#define EADDRNOTAVAIL   49  /* ��ַ������ */
#define ENOTSOCK        50  /* ������������socket */

#define AW_PSP_EDESTADDRREQ    EDESTADDRREQ     /* ��ҪĿ���ַ */
#define AW_PSP_EPROTOTYPE      EPROTOTYPE       /* socketЭ�����ʹ��� */
#define AW_PSP_ENOPROTOOPT     ENOPROTOOPT      /* Э�鲻���� */
#define AW_PSP_EPROTONOSUPPORT EPROTONOSUPPORT  /* Э�鲻֧�� */
#define AW_PSP_ESOCKTNOSUPPORT ESOCKTNOSUPPORT  /* Socket���Ͳ�֧�� */
#define AW_PSP_EOPNOTSUPP      EOPNOTSUPP       /* socket��֧�ָò��� */
#define AW_PSP_EPFNOSUPPORT    EPFNOSUPPORT     /* Э���岻֧�� */
#define AW_PSP_EAFNOSUPPORT    EAFNOSUPPORT     /* ��ַ�ز�֧�� */
#define AW_PSP_EADDRINUSE      EADDRINUSE       /* ��ַ�Ѿ���ռ�� */
#define AW_PSP_EADDRNOTAVAIL   EADDRNOTAVAIL    /* ��ַ������ */
#define AW_PSP_ENOTSOCK        ENOTSOCK         /* ������������socket */
/** @} */


/**
 * \name ��ѡ��ʵ�ֵĴ���ֵ
 * @{
 */
#define ENETUNREACH     51  /* ���粻�ɴ� */
#define ENETRESET       52  /* �����ж������� */
#define ECONNABORTED    53  /* �����ж� */
#define ECONNRESET      54  /* ���Ӹ�λ */
#define ENOBUFS         55  /* ����ռ䲻�� */
#define EISCONN         56  /* Socket�Ѿ����� */
#define ENOTCONN        57  /* Socketû������ */
#define ESHUTDOWN       58  /* Socket�Ѿ��رգ����ܷ������� */
#define ETOOMANYREFS    59  /* ����̫�࣬�޷�ƴ�� */
#define ETIMEDOUT       60  /* ���ӳ�ʱ */
#define ECONNREFUSED    61  /* ���ӱ��ܾ� */
#define ENETDOWN        62  /* �����Ѿ�ֹͣ */
#define ETXTBSY         63  /* �ı��ļ�æ */
#define ELOOP           64  /* �������Ӽ���̫�� */
#define EHOSTUNREACH    65  /* �������ɴ� */
#define ENOTBLK         66  /* �ǿ��豸 */
#define EHOSTDOWN       67  /* �����Ѿ��ر� */

#define AW_PSP_ENETUNREACH   ENETUNREACH   /* ���粻�ɴ� */
#define AW_PSP_ENETRESET     ENETRESET     /* �����ж������� */
#define AW_PSP_ECONNABORTED  ECONNABORTED  /* �����ж� */
#define AW_PSP_ECONNRESET    ECONNRESET    /* ���Ӹ�λ */
#define AW_PSP_ENOBUFS       ENOBUFS       /* ����ռ䲻�� */
#define AW_PSP_EISCONN       EISCONN       /* Socket�Ѿ����� */
#define AW_PSP_ENOTCONN      ENOTCONN      /* Socketû������ */
#define AW_PSP_ESHUTDOWN     ESHUTDOWN     /* Socket�Ѿ��رգ����ܷ������� */
#define AW_PSP_ETOOMANYREFS  ETOOMANYREFS  /* ����̫�࣬�޷�ƴ�� */
#define AW_PSP_ETIMEDOUT     ETIMEDOUT     /* ���ӳ�ʱ */
#define AW_PSP_ECONNREFUSED  ECONNREFUSED  /* ���ӱ��ܾ� */
#define AW_PSP_ENETDOWN      ENETDOWN      /* �����Ѿ�ֹͣ */
#define AW_PSP_ETXTBSY       ETXTBSY       /* �ı��ļ�æ */
#define AW_PSP_ELOOP         ELOOP         /* �������Ӽ���̫�� */
#define AW_PSP_EHOSTUNREACH  EHOSTUNREACH  /* �������ɴ� */
#define AW_PSP_ENOTBLK       ENOTBLK       /* �ǿ��豸 */
#define AW_PSP_EHOSTDOWN     EHOSTDOWN     /* �����Ѿ��ر� */
/** @} */


/**
 * \name ���������ж�I/O����ֵ
 * @{
 */
#define EINPROGRESS     68      /* �������ڽ����� */
#define EALREADY        69      /* ��������ʹ���� */

#define AW_PSP_EINPROGRESS     EINPROGRESS      /* �������ڽ����� */
#define AW_PSP_EALREADY        EALREADY         /* ��������ʹ���� */
/* 70 */

#define EWOULDBLOCK     EAGAIN  /* ������������ͬEAGAIN�� */
#define ENOSYS          71      /* ��֧�ֵĹ��ܣ�����δʵ�֣�*/

#define AW_PSP_EWOULDBLOCK     EWOULDBLOCK      /* ������������ͬEAGAIN�� */
#define AW_PSP_ENOSYS          ENOSYS           /* ��֧�ֵĹ��ܣ�����δʵ�֣�*/
/** @} */


/**
 * \name �첽I/O����ֵ
 * @{
 */
#define ECANCELED              72             /* �����Ѿ�ȡ�� */

#define AW_PSP_ECANCELED       ECANCELED      /* �����Ѿ�ȡ�� */
/* 73 */
/** @} */


/**
 * \name ����ش���ֵ
 * @{
 */
#define ENOSR           74      /* û������Դ */
#define ENOSTR          75      /* �������豸 */
#define EPROTO          76      /* Э����� */
#define EBADMSG         77      /* �𻵵���Ϣ */
#define ENODATA         78      /* ���������� */
#define ETIME           79      /* ��ioctl()��ʱ */
#define ENOMSG          80      /* û���������Ϣ���� */
#define EUCLEAN         81      /* Structure��Ҫ���� */

#define AW_PSP_ENOSR           ENOSR        /* û������Դ */
#define AW_PSP_ENOSTR          ENOSTR       /* �������豸 */
#define AW_PSP_EPROTO          EPROTO       /* Э����� */
#define AW_PSP_EBADMSG         EBADMSG      /* �𻵵���Ϣ */
#define AW_PSP_ENODATA         ENODATA      /* ���������� */
#define AW_PSP_ETIME           ETIME        /* ��ioctl()��ʱ */
#define AW_PSP_ENOMSG          ENOMSG       /* û���������Ϣ���� */
#define AW_PSP_EUCLEAN         EUCLEAN      /* Structure��Ҫ���� */
/** @} */

#define ECOMM       109     /* Communication error on send */
#define EOVERFLOW   112     /* Value too large for defined data type */
#define EREMOTEIO   121     /* Remote I/O error */

/** @} grp_aw_if_posix_err */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_PSP_ERRNO_H */

/* end of file */
