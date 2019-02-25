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
 * \brief Ftpd服务端例程
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能
 *      - AW_COM_FTPD
 *      - 网卡
 *      - 调试串口
 *      - AW_COM_CONSOLE
 *   2. 将PC机网口与开发板网口0相连，修改IP地址，保证开发板与PC在同个网段下
 *   3. 连接调试串口到PC
 *   4. 使用FTP前，需要将存储器挂载至文件系统中，如使用FAT挂载SD卡，得到一个挂载点
 *   5. 打开FTP客户端上位机，设置目标IP（开发板IP地址），建立连接，账户为AWorks，密码为1234
 *
 * - 实验现象：
 *   1. FTP上位机建立连接后，能够访问到开发板上挂载点下的文件
 *
 * - 备注：
 *   1. 保证电脑与开发板处于同一个网段，可以利用nic_manage例程来配置网络ip，也可通过
 *      修改对应网口的配置文件来修改ip，配置文件为awbl_hwconf_xxx_emacX.h，X为网
 *      口编号。
 *
 * \par 源代码
 * \snippet demo_ftpd_server_auth.c src_ftpd_server_auth
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-07  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_ftpd_server_auth
 * \copydoc demo_ftpd_server_auth.c
 */

/** [src_ftpd_server_auth] */
#include "aworks.h"
#include "aw_ftpd.h"
#include <string.h>

#define __FTPD_LISTEN_PORT     21
#define __FTPD_USER_NAME       "AWorks"
#define __FTPD_USER_PASSWORD   "1234"

aw_local bool_t __ftpd_check_user (const char *user_name, const char *pass_word)
{
    if (0 == strcmp(user_name, __FTPD_USER_NAME)) {
        if (0 == strcmp(pass_word, __FTPD_USER_PASSWORD)) {
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * \brief FTPD例程入口
 * \return 无
 */
void demo_ftpd_server_auth_entry (void)
{
    /* 设置访问路径为"/", 端口号为21（__FTPD_LISTEN_PORT），认证访问   */
    aw_ftpd_init("/", __FTPD_LISTEN_PORT, 0, __ftpd_check_user);
}

/** [src_ftpd_server_auth] */

/* end of file */
