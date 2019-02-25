/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * @file
 * @brief serial shell impl
 *
 * @internal
 * @par History
 * - 160107, deo, add user.
 * - 150513, rnk, first implementation.
 * @endinternal
 */

#ifndef __AW_SHELL_SERIAL_H
#define __AW_SHELL_SERIAL_H

#include "aw_task.h"

#include "shell/aw_shell_core.h"

#ifdef __cplusplus
extern "C" {
#endif

struct aw_serial_shell_dev {
	struct aw_shell_context sc;
	struct aw_shell_user    sh;
	int                     com; /* ´®¿ÚºÅ */
    aw_task_id_t            tsk;
};

int aw_serial_shell_run(int arg);
aw_err_t aw_serial_shell_init(struct aw_serial_shell_dev *dev,
                              int                         com,
                              const char                 *user,
                              struct aw_shell_opt *p_shell_opt);

#ifdef __cplusplus
}
#endif

#endif /* __AW_SHELL_SERIAL_H */

/* end of file */
