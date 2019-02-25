/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * @file
 * @brief shell config
 *
 * @internal
 * @par History
 * - 160107, deo, add "serial shell"
 * - 150428, rnk, First implementation.
 * @endinternal
 */

#include "aw_serial.h"
#include "aw_shell.h"

#include "shell/aw_shell_serial.h"

#ifndef AW_CFG_SHELL_THREAD_PRIO
#define AW_CFG_SHELL_THREAD_PRIO       6u
#endif

#ifndef AW_CFG_SHELL_THREAD_STK_SIZ
#define AW_CFG_SHELL_THREAD_STK_SIZ    12 * 1024u
#endif

#ifndef AW_CFG_SHELL_BUF_SIZ
#define AW_CFG_SHELL_BUF_SIZ           1024
#endif

#ifndef AW_CFG_SHELL_SERIAL_COMID
#define AW_CFG_SHELL_SERIAL_COMID      COM0
#endif

static struct aw_serial_shell_dev __g_serial_shell;
static char                       __g_shell_buffer[AW_CFG_SHELL_BUF_SIZ];
AW_TASK_DECL_STATIC(              __g_shell_task, AW_CFG_SHELL_THREAD_STK_SIZ);

static struct aw_shell_opt __g_dbg_shell_opt = {
    .use_chart      = 1,
    .use_color      = 1,
    .use_history    = 1,
    .use_escape_seq = 1,
    .use_cmdset     = 1,
    .use_cursor     = 1,
    .use_complete   = 1,

    .p_endchar      = NULL,
    .p_desc         = "|AWorks->>> ",
    .p_desc_color   = AW_SHELL_FCOLOR_CYAN,
    .p_his_buf      = __g_shell_buffer,
    .his_buf_size   = sizeof(__g_shell_buffer),
};

aw_err_t aw_serial_shell_cfg (void)
{
    int ret;

    __g_serial_shell.tsk = AW_TASK_INIT(__g_shell_task,
            "Serial Shell",
            AW_CFG_SHELL_THREAD_PRIO,
            AW_CFG_SHELL_THREAD_STK_SIZ,
            aw_serial_shell_run,
            &__g_serial_shell);

    ret = aw_serial_shell_init(&__g_serial_shell,
                               AW_CFG_SHELL_SERIAL_COMID,
                               "serial shell",
                               &__g_dbg_shell_opt);

    /* ����logo */
    // todo

    /* ����ָʾ�� */
//    aw_shell_system("shell -desc   |AWorks->>\\ ");

    /* ����ָʾ����ɫ */
//    aw_shell_system("shell -desccol " AW_SHELL_FCOLOR_CYAN);

    (void) ret;
    return AW_OK;
}

/* end of file */
