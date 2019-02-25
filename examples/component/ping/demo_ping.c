/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief 网卡通信测试例程，本例程适用所有平台。
 *
 * - 本例程用法与 Windows 的 ping 程序相同。
 *
 * - 操作步骤：
 *   1. 需要在 aw_prj_params.h 里使能至少一个网卡，例如：
 *      1) 以太网
 *      2) Wi-Fi
 *   2. 需要在aw_prj_params.h头文件里使能
 *      - AW_COM_CONSOLE
 *      - 调试串口使能宏
 *
 * - 实验现象：
 *   1. 执行 "ping 192.168.0.8" ,ping 一个ip地址
 *   2. 执行 "ping www.baidu.com" ,检查网络是否连接成功(需开启网络)
 *
 * \par 源代码
 * \snippet demo_ping.c src_demo_ping
 *
 * \internal
 * \par modification history:
 * - 1.00 18-06-05  phd, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_ping
 * \copydoc demo_ping.c
 */

/** [src_demo_ping] */
#include "aworks.h"
#include "aw_delay.h"
#include "aw_serial.h"
#include "aw_shell.h"

#include "net/aw_net.h"
#include "net/aw_ping.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aw_prj_params.h"

/** ping receive timeout - in milliseconds */
#define DEFAULT_RCV_TIMEO       2000

/** ping delay - in milliseconds */
#define DEFAULT_DELAY           1000

/** max ping data size - in bytes */
#define MAX_PING_DATA_SIZE      4096

#define DEFAULT_PING_COUNT      4

#define DEFAULT_PING_TTL        96

#define DEFAULT_PING_DATA_SIZE  32


#define DEBUG_PING              0

#ifndef ENDL
    #define ENDL                "\r\n"
#endif

#define aw_kprintl(fmt, args...) \
    aw_kprintf(fmt ENDL, ##args)

#define shell_printf(args...) \
    aw_shell_printf(sh, ##args)

#define shell_printl(fmt, args...) \
    aw_shell_printf(sh, fmt ENDL, ##args)

#if DEBUG_PING
    #define shell_dbg_printl(fmt, args...) \
        aw_shell_printf(sh, fmt ENDL, ##args)
#else
    #define shell_dbg_printl(...)
#endif


typedef struct {
    unsigned sent;
    unsigned received;
    unsigned lost;
    unsigned max_time;
    unsigned min_time;
    unsigned average;
    unsigned ping_time;
} ping_result_t;

typedef struct {
    aw_ping_t ping;
    unsigned cnt;
    ping_result_t result;
} ping_param_t;


aw_local bool_t __ctrlc_pressed (struct aw_shell_user *sh)
{
    int ch = aw_shell_getc(sh);

    if ((3 == ch)) {
        return TRUE;
    }

    return FALSE;
}

aw_local aw_err_t __gethostbyname4 (const char      *host,
                                  struct in_addr  *addr,
                                  char           **official_name)
{
    struct hostent *p_host = gethostbyname(host);
    if (NULL == p_host || (NULL == p_host->h_addr_list[0])) {
        return -AW_EADDRNOTAVAIL;
    }
    if (AF_INET != p_host->h_addrtype) {
        return -AW_EAFNOSUPPORT;
    }
    memcpy(&addr->s_addr, p_host->h_addr_list[0], sizeof(addr->s_addr));
    *official_name = p_host->h_name;
    return AW_OK;
}

aw_local int __shell_ping (int argc, char *argv[], struct aw_shell_user *sh)
{
    aw_local aw_const char help_info[] = {
        "Options:" ENDL
        "    -t             Ping the specified host until stopped." ENDL
        "                   To see statistics and continue - type Control-Break;" ENDL
        "                   To stop - type Control-C." ENDL
        "    -n count       Number of echo requests to send." ENDL
        "    -l size        Send buffer size." ENDL
        "    -i TTL         Time To Live." ENDL
        "    -w timeout     Timeout in milliseconds to wait for each reply." ENDL
        "    -S srcaddr     Source address to use." ENDL
    };

    int result;
    ping_param_t param;

    struct in_addr dest_addr;

    struct in_addr src_addr = {
        INADDR_ANY
    };
    int ttl_send = DEFAULT_PING_TTL;
    char *target_name = NULL;
    char target_addr[sizeof("123.123.123.123")];

    int ping_cnt = DEFAULT_PING_COUNT;
    int timeout_ms = DEFAULT_RCV_TIMEO;
    size_t ping_size = DEFAULT_PING_DATA_SIZE;

    int send_cnt;
    int recv_cnt;
    int ttl_recv;
    int rtt_ms_min;
    int rtt_ms_max;
    int rtt_ms_tot;
    bool_t target_name_is_ipaddr;
    bool_t ping_do_not_stop = FALSE;

    if (!argc) {
        shell_printl("%s", help_info);
        return 0;
    }

    for (;;) {
        if (AW_OK == aw_shell_args_get(sh, "-t", 0)) {
            ping_do_not_stop = TRUE;
            shell_printl("Ctrl + C to stop.");
        }
        else if (AW_OK == aw_shell_args_get(sh, "-n", 1)) {
            ping_cnt = aw_shell_long_arg(sh, 1);
            shell_dbg_printl("Ping count     = %d", ping_cnt);
        }
        else if (AW_OK == aw_shell_args_get(sh, "-l", 1)) {
            ping_size = aw_shell_long_arg(sh, 1);
            shell_dbg_printl("Ping data size = %d", ping_size);
        }
        else if (AW_OK == aw_shell_args_get(sh, "-i", 1)) {
            ttl_send = aw_shell_long_arg(sh, 1);
            shell_dbg_printl("TTL            = %d", ttl_send);
        }
        else if (AW_OK == aw_shell_args_get(sh, "-w", 1)) {
            timeout_ms = aw_shell_long_arg(sh, 1);
            shell_dbg_printl("TimeOut        = %d", timeout_ms);
        }
        else if (AW_OK == aw_shell_args_get(sh, "-S", 1)) {
            char *addr = aw_shell_str_arg(sh, 1);
            inet_aton(addr, &src_addr);
            shell_dbg_printl("Source address = %s", inet_ntoa(src_addr));
        }
        else if (AW_OK == aw_shell_args_get(sh, NULL, 1)) {
            target_name = aw_shell_str_arg(sh, 0);
            shell_dbg_printl("Target address = %s", target_name);
        }
        else {
            break;
        }
    }

    if (!target_name) {
        shell_printl("%s", help_info);
        return 0;
    }

    if (inet_aton(target_name, &dest_addr)) {
        target_name_is_ipaddr = TRUE;
    } else {
        target_name_is_ipaddr = FALSE;
    }

    if (0 != __gethostbyname4(target_name, &dest_addr, &target_name)) {
        shell_printl("Ping request could not find host \"%s\"" ENDL
                "    Please check the name and try again.",
                target_name);
        return 0;
    }

    snprintf(target_addr, sizeof(target_addr), "%s", inet_ntoa(dest_addr));

    shell_dbg_printl("Ping count     = %d", ping_cnt);
    shell_dbg_printl("Ping data size = %d", ping_size);
    shell_dbg_printl("TTL            = %d", ttl_send);
    shell_dbg_printl("TimeOut        = %d", timeout_ms);
    shell_dbg_printl("Source address = %s", inet_ntoa(src_addr));
    shell_dbg_printl("Target address = %s", target_addr);

    if (target_name_is_ipaddr) {
        shell_printl(ENDL "Pinging %s with %d bytes of data:",
                target_name, ping_size);
    } else {
        shell_printl(ENDL "Pinging %s [%s] with %d bytes of data:",
                target_name, target_addr, ping_size);
    }

    rtt_ms_min = timeout_ms;
    rtt_ms_max = 0;
    rtt_ms_tot = 0;
    recv_cnt = 0;

    for (send_cnt = 0; ping_do_not_stop || send_cnt < ping_cnt; send_cnt++) {
        result = aw_ping(&param.ping, &dest_addr, &src_addr, ttl_send,
                (uint8_t *) &ttl_recv, ping_size, timeout_ms);
        if (0 > result) {
            if (-AW_EAGAIN == result) {
                shell_printl("PING: transmit failed. General failure.");
            } else {
                shell_printl("Request timed out.");
            }
        } else {
            recv_cnt++;

            if (result > rtt_ms_max) {
                rtt_ms_max = result;
            }
            if (result < rtt_ms_min) {
                rtt_ms_min = result;
            }

            rtt_ms_tot += result;

            if (result == 0) {
                shell_printl("Reply from %s: bytes=%d time<1ms",
                        target_addr, ping_size);
            } else {
                shell_printl("Reply from %s: bytes=%d time=%dms",
                        target_addr, ping_size, result);
            }

            if (ping_do_not_stop || send_cnt < ping_cnt - 1) {
                aw_mdelay(DEFAULT_DELAY);
            }
        }
        /* ctrl + c, break*/
        if (__ctrlc_pressed(sh)) {
            send_cnt++;
            break;
        }
    }

    shell_printl(ENDL "Ping statistics for %s:", target_addr);
    shell_printl("    Packets: Sent = %d, Received = %d, Lost = %d (%d%% loss),",
            send_cnt, recv_cnt, send_cnt - recv_cnt,
            (send_cnt - recv_cnt) * 100 / send_cnt);

    if (recv_cnt > 0) {
        int rtt_ms_avg = rtt_ms_tot / recv_cnt;
        shell_printl("Approximate round trip times in milli-seconds:");
        shell_printl("    Minimum = %dms, Maximum = %dms, Average = %dms",
                rtt_ms_min, rtt_ms_max, rtt_ms_avg);
    }
    if (ping_do_not_stop) {
        shell_printl("Control-C" ENDL "^C");
    }
    return 0;
}

/******************************************************************************/

void demo_ping_entry (void)
{
    aw_local struct aw_shell_cmd_list cl;
    aw_local aw_const struct aw_shell_cmd tbl[] = {
        {
            __shell_ping,
            "ping",
            "[-t] [-n count] [-l size] [-i TTL] [-w timeout] [-S srcaddr] target_name"
        }
    };

    (void) aw_shell_register_cmds(&cl, &tbl[0], &tbl[AW_NELEMENTS(tbl)]);
}
/** [src_demo_ping] */

/* end of file */
