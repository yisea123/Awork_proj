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
 * \brief I/O system shell commands.
 *
 * \internal
 * \par modification history:
 * - 140825 orz, first implementation.
 * \endinternal
 */

#ifndef __IO_SHELL_H /* { */
#define __IO_SHELL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_iosys_shell
 * @{
 */


#include "aworks.h"

/**
 * \brief io 命令初始化
 */
void aw_io_shell_init (void);

/**
 * \brief ramdisk命令初始化
 */
void aw_io_shell_ramdisk_init (void);


#ifdef __cplusplus
}
#endif

/** @} grp_iosys_shell */

#endif /* } __IO_SHELL_H */

/* end of file */
