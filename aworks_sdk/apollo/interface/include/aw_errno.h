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
 * \brief 系统错误值
 *
 * 使用本服务需要包含以下头文件：
 * \code
 * #include "aw_errno.h"
 * \endcode
 *
 * - 所有的系统错误值都在这里定义。没有错误返回0，否则返回对应错误值的负值。
 *   为了兼容POSIX，这里定义了所有POSIX错误值。
 * - Apollo平台使用的错误值是在POSIX错误值前面加上AW_前缀。
 *   所有需要使用错误值的文件都应该包含本文件，Apollo平台自身代码应该使用AW_
 *   前缀的错误值，第三方软件如果使用了POSIX错误值在移植时可以直接使用本文件。
 * - 为了提高代码兼容性，不应该使用本文件之外错误值。
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
 * \name 错误编码数据类型
 * @{
 */
typedef aw_psp_error_t     error_t;    /* 兼容POSIX错误类型 */
typedef aw_psp_aw_err_t    aw_err_t;   /* Apollo错误类型 */
/** @} */

/**
 * \name Apollo平台错误编码接口（非POSIX兼容）
 * @{
 */

/**
 * \brief 设置errno
 * \note 这个宏的作用是用于兼容支持errno和不支持errno的系统。当系统不支持errno
 *      时这个宏是个空定义。
 * \par 使用示例
 * \code
 * AW_ERRNO_SET(ENODEV); // 相当于调用：errno = ENODEV;
 * \endcode
 */
#define AW_ERRNO_SET(err)   AW_PSP_ERRNO_SET(err)

/**
 * \brief 获取errno
 * \note
 *  - 这个宏的作用是用于兼容支持errno和不支持errno的系统。当系统不支持errno
 *    时这个宏是个空定义。
 *  - 当系统不支持errno时，使用这个宏获取到错误值无意义，编写程序时应注意。
 * \par 使用示例
 * \code
 * AW_ERRNO_GET(err); // 相当于调用：err = errno;
 * if (err) {
 *     ;              // 错误处理
 * }
 * \endcode
 */
#define AW_ERRNO_GET(err)   AW_PSP_ERRNO_GET(err)
/* @} */

/* 下面的的错误码需要由平台提供 */
#if 1

/**
 * \addtogroup grp_aw_if_posix_err 系统错误编码值（POSIX兼容）
 * @{
 */

/**
 * \name POSIX错误值
 * @{
 */
#define AW_EPERM           AW_PSP_EPERM         /* 操作不允许 */
#define AW_ENOENT          AW_PSP_ENOENT        /* 文件或目录不存在 */
#define AW_ESRCH           AW_PSP_ESRCH         /* 进程不存在 */
#define AW_EINTR           AW_PSP_EINTR         /* 调用被中断 */
#define AW_EIO             AW_PSP_EIO           /* I/O 错误 */
#define AW_ENXIO           AW_PSP_ENXIO         /* 设备或地址不存在 */
#define AW_E2BIG           AW_PSP_E2BIG         /* 参数列表太长 */
#define AW_ENOEXEC         AW_PSP_ENOEXEC       /* 可执行文件格式错误 */
#define AW_EBADF           AW_PSP_EBADF         /* 文件描述符损坏 */
#define AW_ECHILD          AW_PSP_ECHILD        /* 没有子进程 */
#define AW_EAGAIN          AW_PSP_EAGAIN        /* 资源不可用，需重试 */
#define AW_ENOMEM          AW_PSP_ENOMEM        /* 空间（内存）不足 */
#define AW_EACCES          AW_PSP_EACCES        /* 权限不够 */
#define AW_EFAULT          AW_PSP_EFAULT        /* 地址错误 */
#define AW_ENOTEMPTY       AW_PSP_ENOTEMPTY     /* 目录非空 */
#define AW_EBUSY           AW_PSP_EBUSY         /* 设备或资源忙 */
#define AW_EEXIST          AW_PSP_EEXIST        /* 文件已经存在 */
#define AW_EXDEV           AW_PSP_EXDEV         /* 跨设备连接 */
#define AW_ENODEV          AW_PSP_ENODEV        /* 设备不存在 */
#define AW_ENOTDIR         AW_PSP_ENOTDIR       /* 不是目录 */
#define AW_EISDIR          AW_PSP_EISDIR        /* 是目录 */
#define AW_EINVAL          AW_PSP_EINVAL        /* 无效参数 */
#define AW_ENFILE          AW_PSP_ENFILE        /* 系统打开文件太多，描述符不够用 */
#define AW_EMFILE          AW_PSP_EMFILE        /* 打开的文件太多 */
#define AW_ENOTTY          AW_PSP_ENOTTY        /* 不合适的I/O控制操作 */
#define AW_ENAMETOOLONG    AW_PSP_ENAMETOOLONG  /* 文件名太长 */
#define AW_EFBIG           AW_PSP_EFBIG         /* 文件太大 */
#define AW_ENOSPC          AW_PSP_ENOSPC        /* 设备剩余空间不足 */
#define AW_ESPIPE          AW_PSP_ESPIPE        /* 无效的搜索（Invalid seek） */
#define AW_EROFS           AW_PSP_EROFS         /* 文件系统只读 */
#define AW_EMLINK          AW_PSP_EMLINK        /* 链接太多 */
#define AW_EPIPE           AW_PSP_EPIPE         /* 损坏的管道 */
#define AW_EDEADLK         AW_PSP_EDEADLK       /* 资源可能死锁 */
#define AW_ENOLCK          AW_PSP_ENOLCK        /* 无可用（空闲）的锁 */
#define AW_ENOTSUP         AW_PSP_ENOTSUP       /* 不支持 */
#define AW_EMSGSIZE        AW_PSP_EMSGSIZE      /* 消息太大 */
/** @} */

/**
 * \name ANSI错误值
 * @{
 */
#define AW_EDOM            AW_PSP_EDOM    /* 数学函数参数超出范围 */
#define AW_ERANGE          AW_PSP_ERANGE  /* 数学函数计算结果太大 */
#define AW_EILSEQ          AW_PSP_EILSEQ  /* 非法的字节顺序 */
/** @} */

/**
 * \name 网络参数错误相关
 * @{
 */
#define AW_EDESTADDRREQ    AW_PSP_EDESTADDRREQ     /* 需要目标地址 */
#define AW_EPROTOTYPE      AW_PSP_EPROTOTYPE       /* socket协议类型错误 */
#define AW_ENOPROTOOPT     AW_PSP_ENOPROTOOPT      /* 协议不可用 */
#define AW_EPROTONOSUPPORT AW_PSP_EPROTONOSUPPORT  /* 协议不支持 */
#define AW_ESOCKTNOSUPPORT AW_PSP_ESOCKTNOSUPPORT  /* Socket类型不支持 */
#define AW_EOPNOTSUPP      AW_PSP_EOPNOTSUPP       /* socket不支持该操作 */
#define AW_EPFNOSUPPORT    AW_PSP_EPFNOSUPPORT     /* 协议族不支持 */
#define AW_EAFNOSUPPORT    AW_PSP_EAFNOSUPPORT     /* 地址簇不支持 */
#define AW_EADDRINUSE      AW_PSP_EADDRINUSE       /* 地址已经被占用 */
#define AW_EADDRNOTAVAIL   AW_PSP_EADDRNOTAVAIL    /* 地址不可用 */
#define AW_ENOTSOCK        AW_PSP_ENOTSOCK         /* 被操作对象不是socket */
/** @} */

/**
 * \name 可选择实现的错误值
 * @{
 */
#define AW_ENETUNREACH     AW_PSP_ENETUNREACH   /* 网络不可达 */
#define AW_ENETRESET       AW_PSP_ENETRESET     /* 网络中断了连接 */
#define AW_ECONNABORTED    AW_PSP_ECONNABORTED  /* 连接中断 */
#define AW_ECONNRESET      AW_PSP_ECONNRESET    /* 连接复位 */
#define AW_ENOBUFS         AW_PSP_ENOBUFS       /* 缓冲空间不足 */
#define AW_EISCONN         AW_PSP_EISCONN       /* Socket已经连接 */
#define AW_ENOTCONN        AW_PSP_ENOTCONN      /* Socket没有连接 */
#define AW_ESHUTDOWN       AW_PSP_ESHUTDOWN     /* Socket已经关闭，不能发送数据 */
#define AW_ETOOMANYREFS    AW_PSP_ETOOMANYREFS  /* 引用太多，无法拼接 */
#define AW_ETIMEDOUT       AW_PSP_ETIMEDOUT     /* 连接超时 */
#define AW_ECONNREFUSED    AW_PSP_ECONNREFUSED  /* 连接被拒绝 */
#define AW_ENETDOWN        AW_PSP_ENETDOWN      /* 网络已经停止 */
#define AW_ETXTBSY         AW_PSP_ETXTBSY       /* 文本文件忙 */
#define AW_ELOOP           AW_PSP_ELOOP         /* 符号链接级数太多 */
#define AW_EHOSTUNREACH    AW_PSP_EHOSTUNREACH  /* 主机不可达 */
#define AW_ENOTBLK         AW_PSP_ENOTBLK       /* 非块设备 */
#define AW_EHOSTDOWN       AW_PSP_EHOSTDOWN     /* 主机已经关闭 */
/** @} */

/**
 * \name 非阻塞和中断I/O错误值
 * @{
 */
#define AW_EINPROGRESS     AW_PSP_EINPROGRESS      /* 操作正在进行中 */
#define AW_EALREADY        AW_PSP_EALREADY         /* 连接正被使用中 */
/* 70 */
#define AW_EWOULDBLOCK     AW_PSP_EWOULDBLOCK      /* 操作会阻塞（同EAGAIN） */
#define AW_ENOSYS          AW_PSP_ENOSYS           /* 不支持的功能（功能未实现）*/
/** @} */

/**
 * \name 异步I/O错误值
 * @{
 */
#define AW_ECANCELED       AW_PSP_ECANCELED        /* 操作已经取消 */
/* 73 */                                          
/** @} */

/**
 * \name 流相关错误值
 * @{
 */
#define AW_ENOSR           AW_PSP_ENOSR            /* 没有流资源 */
#define AW_ENOSTR          AW_PSP_ENOSTR           /* 不是流设备 */
#define AW_EPROTO          AW_PSP_EPROTO           /* 协议错误 */
#define AW_EBADMSG         AW_PSP_EBADMSG          /* 损坏的消息 */
#define AW_ENODATA         AW_PSP_ENODATA          /* 流中无数据 */
#define AW_ETIME           AW_PSP_ETIME            /* 流ioctl()超时 */
#define AW_ENOMSG          AW_PSP_ENOMSG           /* 没有所需的消息类型 */
#define AW_EUCLEAN         AW_PSP_EUCLEAN          /* Structure需要清理 */
/** @} */

/** @} grp_aw_if_posix_err */

#endif  /* ... */

/** @} grp_aw_if_errno */

#endif /* __AW_ERRNO_H */

/* end of file */
