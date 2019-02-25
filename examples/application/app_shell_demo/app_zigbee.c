/*******************************************************************************
*                                  AWorks
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

#include "aworks.h"                     /* 此头文件必须被首先包含 */
#include "aw_shell.h"
#include "app_config.h"
#include "stdio.h"

#include "driver/zigbee/awbl_zm516x.h"

#ifdef APP_ZIGBEE

#define    __DEVID    0


/******************************************************************************/
int app_zigbee (int argc, char **argv, struct aw_shell_user *p_user)
{
    uint16_t               src = 0;
    uint16_t               dst = 0;
    uint16_t               addr = 0;
    uint16_t               id  = 0x1001;
    int                    mode = -1;
    int                    chn;
    char                  *arg;
    awbl_zm516x_cfg_info_t info;
    aw_err_t               ret;
    char                   buf[255];
    char                   ch = 0;
    uint32_t               size;
    int                    idx = 0;

    ret = awbl_zm516x_cfg_info_get(__DEVID, TRUE, 0, &info);
    if (ret != AW_OK) {
        aw_kprintf("get device config failed %d.\r\n", ret);
        goto __exit;
    }

//    ret = awbl_zm516x_default_set(__DEVID, info.my_addr);
//    if (ret != AW_OK) {
//        aw_kprintf("set device default config failed %d.\r\n", ret);
//    }
//
//    ret = awbl_zm516x_cfg_info_get(__DEVID, TRUE, 0, &info);
//    if (ret != AW_OK) {
//        aw_kprintf("get device config failed %d.\r\n", ret);
//        goto __exit;
//    }

    addr = info.my_addr;

    while (1) {
        if (aw_shell_args_get(p_user, "-l", 1) == AW_OK) {
            arg = aw_shell_str_arg(p_user, 1);
            sscanf(arg, "%x", &idx);
            info.my_addr = (uint16_t)idx;

        } else if (aw_shell_args_get(p_user, "-t", 1) == AW_OK) {
            arg = aw_shell_str_arg(p_user, 1);
            sscanf(arg, "%x", &idx);
            info.dst_addr = (uint16_t)idx;

        } else if (aw_shell_args_get(p_user, "-i", 1) == AW_OK) {
            arg = aw_shell_str_arg(p_user, 1);
            sscanf(arg, "%x", &idx);
            info.panid = (uint16_t)idx;

        } else if (aw_shell_args_get(p_user, "-c", 1) == AW_OK) {
            info.chan = aw_shell_long_arg(p_user, 1);

        } else if (aw_shell_args_get(p_user, "-d", 0) == AW_OK) {
            ret = awbl_zm516x_default_set(__DEVID, addr);
            if (ret != AW_OK) {
                aw_kprintf("set device default config failed %d.\r\n", ret);
            }

            ret = awbl_zm516x_cfg_info_get(__DEVID, TRUE, 0, &info);
            if (ret != AW_OK) {
                aw_kprintf("get device config failed %d.\r\n", ret);
                goto __exit;
            }

            addr = info.my_addr;
        } else if (aw_shell_args_get(p_user, "-m", 1) == AW_OK) {
            mode = aw_shell_long_arg(p_user, 1);
            if ((mode > 1) || (mode < 0)) {
                aw_kprintf("mode error, must between 0 and 1.\r\n");
                return -AW_EINVAL;
            }
        } else {
            break;
        }
    }

    ret = awbl_zm516x_cfg_info_set(__DEVID, addr, &info);
    if (ret != AW_OK) {
        aw_kprintf("set device config failed %d.\r\n", ret);
        goto __exit;
    }

//    ret = awbl_zm516x_display_head_set(__DEVID, TRUE, FALSE);
//    if (ret != AW_OK) {
//        aw_kprintf("disk play head set failed %d\r\n", ret);
//        goto __exit;
//    }

    aw_kprintf("Name:           %s\r\n", info.dev_name);
    aw_kprintf("Local Addr:     %04x\r\n", info.my_addr);
    aw_kprintf("Target Addr:    %04x\r\n", info.dst_addr);
    aw_kprintf("Mac:            %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n",
                info.dst_mac[0], info.dst_mac[1], info.dst_mac[2], info.dst_mac[3],
                info.dst_mac[4], info.dst_mac[5], info.dst_mac[6], info.dst_mac[7]);
    aw_kprintf("PanID:          %04x\r\n", info.panid);
    aw_kprintf("Channel:        %d\r\n", info.chan);
    aw_kprintf("Mode:           %s\r\n", info.dev_name);
    aw_kprintf("Version:        V%d.%02x\r\n", info.version >> 8, info.version & 0x00FF);

    if (mode < 0) {
        goto __exit;
    }

    aw_kprintf("enter %s mode.\r\n", mode ? "send" : "receive");
    aw_kprintf("Ctrl + C to exit.\r\n\r\n");

    idx = 0;
    while (1) {
        if (mode == 0) {
            ret = awbl_zm516x_receive(__DEVID, buf, sizeof(buf) - 1);
            if (ret > 0) {
                buf[ret] = '\0';
                aw_kprintf("received data(%d): %s\r\n", ret, buf);
            } else if (ret < 0){
                aw_kprintf("received data failed %d.\r\n", ret);
            }

            size = aw_serial_read(0, (void *)&ch, 1);
            if ((size == 1) && (ch == 0x03)) {
                break;
            }
        } else {
            size = aw_serial_read(0, (void *)&ch, 1);
            if (size == 1) {
                if (ch == 0x03) {
                    break;
                }

                if (ch == '\r') {
                    aw_kprintf("\r\n");
                    if (idx ){
                        ret = awbl_zm516x_send_with_ack(__DEVID, buf, idx);
                        if (ret != idx) {
                            aw_kprintf("send data failed %d.\r\n\r\n", ret);
                        } else {
                            aw_kprintf("send data(%d) success.\r\n\r\n", ret);
                        }
                        idx = 0;
                    }
                } else if (ch == '\b') {
                    if (idx) {
                        idx--;
                    }
                    aw_kprintf("\b \b");
                } else {
                    if (idx < sizeof(buf)) {
                        buf[idx++] = ch;
                    }
                    aw_kprintf("%c", ch);
                }
            }
        }
    }

__exit:
    return AW_OK;
}
#endif /* APP_VERSION */
