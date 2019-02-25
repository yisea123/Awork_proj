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
 * \brief aworks1.0  errno 标准接口头文件
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
 * \name 错误编码数据类型
 * @{
 */
typedef int aw_psp_error_t;    /* 兼容POSIX错误类型 */
typedef int aw_psp_aw_err_t;   /* Apollo错误类型 */
/** @} */

/**
 * \name POSIX兼容错误编码接口
 * @{
 */

/* 获取错误值地址，由平台实现 */
extern aw_psp_error_t *__errno(void);

/**
 * \brief 获取或设置错误值
 * \par 使用示例
 * \code
 * if (condition) {      // 是否出错
 *     errno = EIO;      // 设置错误编号
 * }
 * if (EBUSY == errno) { // 判断是否设备忙错误
 *     ;                 // 设备忙错误处理
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
 * \addtogroup grp_aw_if_posix_err 系统错误编码值（POSIX兼容）
 * @{
 */

/**
 * \name POSIX错误值
 * @{
 */
#define EPERM           1   /* 操作不允许 */
#define ENOENT          2   /* 文件或目录不存在 */
#define ESRCH           3   /* 进程不存在 */
#define EINTR           4   /* 调用被中断 */
#define EIO             5   /* I/O 错误 */
#define ENXIO           6   /* 设备或地址不存在 */
#define E2BIG           7   /* 参数列表太长 */
#define ENOEXEC         8   /* 可执行文件格式错误 */
#define EBADF           9   /* 文件描述符损坏 */
#define ECHILD          10  /* 没有子进程 */
#define EAGAIN          11  /* 资源不可用，需重试 */
#define ENOMEM          12  /* 空间（内存）不足 */
#define EACCES          13  /* 权限不够 */
#define EFAULT          14  /* 地址错误 */
#define ENOTEMPTY       15  /* 目录非空 */
#define EBUSY           16  /* 设备或资源忙 */
#define EEXIST          17  /* 文件已经存在 */
#define EXDEV           18  /* 跨设备连接 */
#define ENODEV          19  /* 设备不存在 */
#define ENOTDIR         20  /* 不是目录 */
#define EISDIR          21  /* 是目录 */
#define EINVAL          22  /* 无效参数 */
#define ENFILE          23  /* 系统打开文件太多，描述符不够用 */
#define EMFILE          24  /* 打开的文件太多 */
#define ENOTTY          25  /* 不合适的I/O控制操作 */
#define ENAMETOOLONG    26  /* 文件名太长 */
#define EFBIG           27  /* 文件太大 */
#define ENOSPC          28  /* 设备剩余空间不足 */
#define ESPIPE          29  /* 无效的搜索（Invalid seek） */
#define EROFS           30  /* 文件系统只读 */
#define EMLINK          31  /* 链接太多 */
#define EPIPE           32  /* 损坏的管道 */
#define EDEADLK         33  /* 资源可能死锁 */
#define ENOLCK          34  /* 无可用（空闲）的锁 */
#define ENOTSUP         35  /* 不支持 */
#define EMSGSIZE        36  /* 消息太大 */

#define AW_PSP_EPERM          EPERM         /* 操作不允许 */
#define AW_PSP_ENOENT         ENOENT        /* 文件或目录不存在 */
#define AW_PSP_ESRCH          ESRCH         /* 进程不存在 */
#define AW_PSP_EINTR          EINTR         /* 调用被中断 */
#define AW_PSP_EIO            EIO           /* I/O 错误 */
#define AW_PSP_ENXIO          ENXIO         /* 设备或地址不存在 */
#define AW_PSP_E2BIG          E2BIG         /* 参数列表太长 */
#define AW_PSP_ENOEXEC        ENOEXEC       /* 可执行文件格式错误 */
#define AW_PSP_EBADF          EBADF         /* 文件描述符损坏 */
#define AW_PSP_ECHILD         ECHILD        /* 没有子进程 */
#define AW_PSP_EAGAIN         EAGAIN        /* 资源不可用，需重试 */
#define AW_PSP_ENOMEM         ENOMEM        /* 空间（内存）不足 */
#define AW_PSP_EACCES         EACCES        /* 权限不够 */
#define AW_PSP_EFAULT         EFAULT        /* 地址错误 */
#define AW_PSP_ENOTEMPTY      ENOTEMPTY     /* 目录非空 */
#define AW_PSP_EBUSY          EBUSY         /* 设备或资源忙 */
#define AW_PSP_EEXIST         EEXIST        /* 文件已经存在 */
#define AW_PSP_EXDEV          EXDEV         /* 跨设备连接 */
#define AW_PSP_ENODEV         ENODEV        /* 设备不存在 */
#define AW_PSP_ENOTDIR        ENOTDIR       /* 不是目录 */
#define AW_PSP_EISDIR         EISDIR        /* 是目录 */
#define AW_PSP_EINVAL         EINVAL        /* 无效参数 */
#define AW_PSP_ENFILE         ENFILE        /* 系统打开文件太多，描述符不够用 */
#define AW_PSP_EMFILE         EMFILE        /* 打开的文件太多 */
#define AW_PSP_ENOTTY         ENOTTY        /* 不合适的I/O控制操作 */
#define AW_PSP_ENAMETOOLONG   ENAMETOOLONG  /* 文件名太长 */
#define AW_PSP_EFBIG          EFBIG         /* 文件太大 */
#define AW_PSP_ENOSPC         ENOSPC        /* 设备剩余空间不足 */
#define AW_PSP_ESPIPE         ESPIPE        /* 无效的搜索（Invalid seek） */
#define AW_PSP_EROFS          EROFS         /* 文件系统只读 */
#define AW_PSP_EMLINK         EMLINK        /* 链接太多 */
#define AW_PSP_EPIPE          EPIPE         /* 损坏的管道 */
#define AW_PSP_EDEADLK        EDEADLK       /* 资源可能死锁 */
#define AW_PSP_ENOLCK         ENOLCK        /* 无可用（空闲）的锁 */
#define AW_PSP_ENOTSUP        ENOTSUP       /* 不支持 */
#define AW_PSP_EMSGSIZE       EMSGSIZE      /* 消息太大 */
/** @} */


/**
 * \name ANSI错误值
 * @{
 */
#define EDOM            37  /* 数学函数参数超出范围 */
#define ERANGE          38  /* 数学函数计算结果太大 */
#define EILSEQ          39  /* 非法的字节顺序 */

#define AW_PSP_EDOM            EDOM    /* 数学函数参数超出范围 */
#define AW_PSP_ERANGE          ERANGE  /* 数学函数计算结果太大 */
#define AW_PSP_EILSEQ          EILSEQ  /* 非法的字节顺序 */      
/** @} */ 


/**
 * \name 网络参数错误相关
 * @{
 */
#define EDESTADDRREQ    40  /* 需要目标地址 */
#define EPROTOTYPE      41  /* socket协议类型错误 */
#define ENOPROTOOPT     42  /* 协议不可用 */
#define EPROTONOSUPPORT 43  /* 协议不支持 */
#define ESOCKTNOSUPPORT 44  /* Socket类型不支持 */
#define EOPNOTSUPP      45  /* socket不支持该操作 */
#define EPFNOSUPPORT    46  /* 协议族不支持 */
#define EAFNOSUPPORT    47  /* 地址簇不支持 */
#define EADDRINUSE      48  /* 地址已经被占用 */
#define EADDRNOTAVAIL   49  /* 地址不可用 */
#define ENOTSOCK        50  /* 被操作对象不是socket */

#define AW_PSP_EDESTADDRREQ    EDESTADDRREQ     /* 需要目标地址 */
#define AW_PSP_EPROTOTYPE      EPROTOTYPE       /* socket协议类型错误 */
#define AW_PSP_ENOPROTOOPT     ENOPROTOOPT      /* 协议不可用 */
#define AW_PSP_EPROTONOSUPPORT EPROTONOSUPPORT  /* 协议不支持 */
#define AW_PSP_ESOCKTNOSUPPORT ESOCKTNOSUPPORT  /* Socket类型不支持 */
#define AW_PSP_EOPNOTSUPP      EOPNOTSUPP       /* socket不支持该操作 */
#define AW_PSP_EPFNOSUPPORT    EPFNOSUPPORT     /* 协议族不支持 */
#define AW_PSP_EAFNOSUPPORT    EAFNOSUPPORT     /* 地址簇不支持 */
#define AW_PSP_EADDRINUSE      EADDRINUSE       /* 地址已经被占用 */
#define AW_PSP_EADDRNOTAVAIL   EADDRNOTAVAIL    /* 地址不可用 */
#define AW_PSP_ENOTSOCK        ENOTSOCK         /* 被操作对象不是socket */
/** @} */


/**
 * \name 可选择实现的错误值
 * @{
 */
#define ENETUNREACH     51  /* 网络不可达 */
#define ENETRESET       52  /* 网络中断了连接 */
#define ECONNABORTED    53  /* 连接中断 */
#define ECONNRESET      54  /* 连接复位 */
#define ENOBUFS         55  /* 缓冲空间不足 */
#define EISCONN         56  /* Socket已经连接 */
#define ENOTCONN        57  /* Socket没有连接 */
#define ESHUTDOWN       58  /* Socket已经关闭，不能发送数据 */
#define ETOOMANYREFS    59  /* 引用太多，无法拼接 */
#define ETIMEDOUT       60  /* 连接超时 */
#define ECONNREFUSED    61  /* 连接被拒绝 */
#define ENETDOWN        62  /* 网络已经停止 */
#define ETXTBSY         63  /* 文本文件忙 */
#define ELOOP           64  /* 符号链接级数太多 */
#define EHOSTUNREACH    65  /* 主机不可达 */
#define ENOTBLK         66  /* 非块设备 */
#define EHOSTDOWN       67  /* 主机已经关闭 */

#define AW_PSP_ENETUNREACH   ENETUNREACH   /* 网络不可达 */
#define AW_PSP_ENETRESET     ENETRESET     /* 网络中断了连接 */
#define AW_PSP_ECONNABORTED  ECONNABORTED  /* 连接中断 */
#define AW_PSP_ECONNRESET    ECONNRESET    /* 连接复位 */
#define AW_PSP_ENOBUFS       ENOBUFS       /* 缓冲空间不足 */
#define AW_PSP_EISCONN       EISCONN       /* Socket已经连接 */
#define AW_PSP_ENOTCONN      ENOTCONN      /* Socket没有连接 */
#define AW_PSP_ESHUTDOWN     ESHUTDOWN     /* Socket已经关闭，不能发送数据 */
#define AW_PSP_ETOOMANYREFS  ETOOMANYREFS  /* 引用太多，无法拼接 */
#define AW_PSP_ETIMEDOUT     ETIMEDOUT     /* 连接超时 */
#define AW_PSP_ECONNREFUSED  ECONNREFUSED  /* 连接被拒绝 */
#define AW_PSP_ENETDOWN      ENETDOWN      /* 网络已经停止 */
#define AW_PSP_ETXTBSY       ETXTBSY       /* 文本文件忙 */
#define AW_PSP_ELOOP         ELOOP         /* 符号链接级数太多 */
#define AW_PSP_EHOSTUNREACH  EHOSTUNREACH  /* 主机不可达 */
#define AW_PSP_ENOTBLK       ENOTBLK       /* 非块设备 */
#define AW_PSP_EHOSTDOWN     EHOSTDOWN     /* 主机已经关闭 */
/** @} */


/**
 * \name 非阻塞和中断I/O错误值
 * @{
 */
#define EINPROGRESS     68      /* 操作正在进行中 */
#define EALREADY        69      /* 连接正被使用中 */

#define AW_PSP_EINPROGRESS     EINPROGRESS      /* 操作正在进行中 */
#define AW_PSP_EALREADY        EALREADY         /* 连接正被使用中 */
/* 70 */

#define EWOULDBLOCK     EAGAIN  /* 操作会阻塞（同EAGAIN） */
#define ENOSYS          71      /* 不支持的功能（功能未实现）*/

#define AW_PSP_EWOULDBLOCK     EWOULDBLOCK      /* 操作会阻塞（同EAGAIN） */
#define AW_PSP_ENOSYS          ENOSYS           /* 不支持的功能（功能未实现）*/
/** @} */


/**
 * \name 异步I/O错误值
 * @{
 */
#define ECANCELED              72             /* 操作已经取消 */

#define AW_PSP_ECANCELED       ECANCELED      /* 操作已经取消 */
/* 73 */
/** @} */


/**
 * \name 流相关错误值
 * @{
 */
#define ENOSR           74      /* 没有流资源 */
#define ENOSTR          75      /* 不是流设备 */
#define EPROTO          76      /* 协议错误 */
#define EBADMSG         77      /* 损坏的消息 */
#define ENODATA         78      /* 流中无数据 */
#define ETIME           79      /* 流ioctl()超时 */
#define ENOMSG          80      /* 没有所需的消息类型 */
#define EUCLEAN         81      /* Structure需要清理 */

#define AW_PSP_ENOSR           ENOSR        /* 没有流资源 */
#define AW_PSP_ENOSTR          ENOSTR       /* 不是流设备 */
#define AW_PSP_EPROTO          EPROTO       /* 协议错误 */
#define AW_PSP_EBADMSG         EBADMSG      /* 损坏的消息 */
#define AW_PSP_ENODATA         ENODATA      /* 流中无数据 */
#define AW_PSP_ETIME           ETIME        /* 流ioctl()超时 */
#define AW_PSP_ENOMSG          ENOMSG       /* 没有所需的消息类型 */
#define AW_PSP_EUCLEAN         EUCLEAN      /* Structure需要清理 */
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
