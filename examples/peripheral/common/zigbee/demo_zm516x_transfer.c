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
 * \file
 * \brief ZM516X 模块传输数据例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 测试本 Demo 需要使用两块开发板，两块开发板需要下载不同的程序，
 *      其中一块开发板打开宏 USE_BORD0，关闭宏 USE_BORD1，编译并下载程序，
 *      另外一块开发板打开宏 USE_BORD1，关闭宏 USE_BORD0，编译并下载程序。
 *   2. 测试本 Demo 必须在 aw_prj_params.h 内使能
 *       - AW_DEV_ZM516X_0
 *       - 对应平台和zigbee模块相连的串口宏
 *   3. 如需观察串口打印的调试信息，需要将 DUART_RX 引脚连接 PC 串口的 TXD，
 *       DUART_TX 引脚连接 PC 串口的 RXD；
 *
 * - 实验现象：
 *   1. 如果 ZM516X 模块初始化并配置成功，调试串口打印 "ZM516X Initial Done\r\n"，
 *      如果初始化失败，调试串口打印相应错误信息；
 *   2. 调试串口打印读取到的模块配置信息；
 *   3. 两块板向对方发送 10 次数据，如果发送成功，将通过串口打印
 *      "send data success"如果发送失败，将通过串口打印
 *      "send data failed"；
 *   4. 接收函数收到对方发送过来的数据后，调试串口将接收到的数据内容输出，内容为
 *      "received data from 0x****: I'm 0x**"。
 *
 * - 备注：
 *   1. Zigbee 模块内GPIO具体连接关系需要查看zigbee的配置文件awbl_hwconf_zm516x.h,
 *      如果需要使用 Zigbee，这些 IO 口不能用作其它用途。
 *
 * \par 源代码
 * \snippet demo_zm516x_transfer.c src_zm516x_transfer
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-23  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_zm516x_transfer
 * \copydoc demo_zm516x_transfer.c
 */

/** [src_zm516x_transfer] */
#include "aworks.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "driver/zigbee/awbl_zm516x.h"
#include <string.h>

#define USE_BORD0            /**< \brief 使用该宏时，本例程用于单板 0 */
//#define USE_BORD1          /**< \brief 使用该宏时，本例程用于单板 1 */

/** \brief 定义设备号，需要与 awbl_hwconf_zm516x_0.h 文件内的值相同 */
#define    __ID    0

/**
 * \brief 打印 ZM516X 模块的配置信息
 */
aw_local void __cfg_info_print (awbl_zm516x_cfg_info_t *p_zm516x_cfg_info)
{
    AW_INFOF(("\r\n__cfg_info_print\r\n"));
    AW_INFOF(("dev_name:%s\r\n"
              "dev_pwd:%s\r\n"
              "dev_mode:%d\r\n"
              "chan:%d\r\n"
              "panid:0x%04x\r\n"
              "my_addr:0x%04x\r\n"
              "my_mac:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\r\n"
              "dst_addr:0x%04x\r\n"
              "power_level:%d\r\n"
              "retry_num:%d\r\n"
              "tran_timeout:%d\r\n"
              "send_mode:%d\r\n"
              "state:0x%02x\r\n"
              "software:%d\r\n"
              "version:0x%04x\r\n",
              p_zm516x_cfg_info->dev_name,
              p_zm516x_cfg_info->dev_pwd,
              p_zm516x_cfg_info->dev_mode,
              p_zm516x_cfg_info->chan,
              p_zm516x_cfg_info->panid,
              p_zm516x_cfg_info->my_addr,
              p_zm516x_cfg_info->my_mac[7],
              p_zm516x_cfg_info->my_mac[6],
              p_zm516x_cfg_info->my_mac[5],
              p_zm516x_cfg_info->my_mac[4],
              p_zm516x_cfg_info->my_mac[3],
              p_zm516x_cfg_info->my_mac[2],
              p_zm516x_cfg_info->my_mac[1],
              p_zm516x_cfg_info->my_mac[0],
              p_zm516x_cfg_info->dst_addr,
              p_zm516x_cfg_info->power_level,
              p_zm516x_cfg_info->retry_num,
              p_zm516x_cfg_info->tran_timeout,
              p_zm516x_cfg_info->send_mode,
              p_zm516x_cfg_info->state,
              p_zm516x_cfg_info->software,
              p_zm516x_cfg_info->version));
    AW_INFOF(("\r\n"));
}

/**
 * \brief zm516x数据收发例程入口
 */
void demo_zm516x_transfer_entry (void)
{
    char                   send_buf[11] = "I'm 0x00\r\n";
    int                    ret = 0;

#ifdef USE_BORD0
    uint16_t               src_addr = 0x2001;
    uint16_t               dst_addr = 0x2002;
#endif

#ifdef  USE_BORD1
    uint16_t               src_addr = 0x2002;
    uint16_t               dst_addr = 0x2001;
#endif
    uint16_t               addr_tmp;

    uint8_t                buf[20] = {0};
    uint32_t               send_tick = 0;
    awbl_zm516x_cfg_info_t zm516x_cfg_info;

    AW_INFOF(("src_addr: 0x%04x dst_addr: 0x%04x\n", src_addr, dst_addr));

    /* 获取 ZM516X 模块的配置信息 */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 0 failed\r\n"));
        goto exit;
    }

    /* 恢复 ZM516X 模块出厂设置 */
    if (awbl_zm516x_default_set(__ID, zm516x_cfg_info.my_addr) != AW_OK) {
        AW_INFOF(("awbl_zm516x_default_set failed\r\n"));
        goto exit;
    }

    /* 获取 ZM516X 模块的配置信息 */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 1 failed\r\n"));
        goto exit;
    }
    addr_tmp = zm516x_cfg_info.my_addr;

    zm516x_cfg_info.my_addr = src_addr;
    zm516x_cfg_info.dst_addr = dst_addr;
    zm516x_cfg_info.panid = 0x1001;

    /* 修改 ZM516X 模块的配置信息 */
    if (awbl_zm516x_cfg_info_set(__ID, addr_tmp, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_set failed\r\n"));
        goto exit;
    }

    /* 设置指定地址的 ZM516X 模块接收的数据包包头是否显示源地址 */
    if (awbl_zm516x_display_head_set(__ID, TRUE, TRUE) != AW_OK) {
        AW_INFOF(("awbl_zm516x_display_head_set failed\r\n"));
        goto exit;
    }

    /**
     * 设置 ZM516X 模块进入深度休眠模式，需要单独测试，ZM516X 深度休眠后
     * 只能复位模块或把模块的 WAKE 引脚拉低来唤醒模块
     */
//    awbl_zm516x_enter_deep_sleep(__ID);

    /* 获取 ZM516X 模块的配置信息 */
    if (awbl_zm516x_cfg_info_get(__ID, TRUE, 0, &zm516x_cfg_info) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_info_get 2 failed\r\n"));
        goto exit;
    }
    __cfg_info_print(&zm516x_cfg_info);

    AW_INFOF(("ZM516X Initial Done\r\n"));

    AW_FOREVER {

        if ((send_tick++ % 100) == 0) {
            send_buf[7] = (src_addr & 0x0F) + '0';
            if (awbl_zm516x_send_with_ack(__ID,
                                        send_buf,
                                        strlen(send_buf)) != strlen(send_buf)) {
                AW_INFOF(("send data failed\r\n"));

            } else {
                AW_INFOF(("send data success\r\n"));
            }
        }

        /* awbl_zm516x_receive 函数的读超时为 10ms */
        ret = awbl_zm516x_receive(__ID, buf, sizeof(buf));

        if (ret > 0) {
            AW_INFOF(("received data from 0x%02x%02x: %s\r\n",
                      buf[0],
                      buf[1],
                      buf + 2));
            memset(buf, 0x00, sizeof(buf));
        }

        if (send_tick == 1000) {
            goto exit;
        }
        aw_mdelay(1);
    }

exit:
    return;
}

/** [src_zm516x_transfer] */

/* end of file */
