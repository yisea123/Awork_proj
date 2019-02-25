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
 * \brief ZM516X 模块搜索例程，通过标准接口实现
 *
 * - 操作步骤：
 *    1. 如需观察串口打印的调试信息，需要将 DUART_RX 引脚连接 PC 串口的 TXD，
 *       DUART_TX 引脚连接 PC 串口的 RXD；
 *    2. 测试本 Demo 必须在 aw_prj_params.h 内使能
 *       - AW_DEV_ZM516X_0
 *       - 对应平台和zigbee模块相连的串口宏
 *
 * - 实验现象：
 *   1. 串口打印读取到的本地模块的配置信息；
 *   2. ZM516X 模块从 11 通道到 26 通道搜索其它模块。如果搜索到其它模块，获取该模块
 *      的信号强度和配置信息，并通过串口打印；
 *   3. 如果搜索完成，调试串口打印 "ZM516X Search Done\r\n"，
 *      如果搜索失败，调试串口打印相应错误信息；
 *   4. 将本地模块的通道恢复为搜索前的通道号。
 *
 * - 备注：
 *   1. Zigbee 模块内GPIO具体连接关系需要查看zigbee的配置文件awbl_hwconf_zm516x.h,
 *      如果需要使用 Zigbee，这些 IO 口不能用作其它用途。
 *
 * \par 源代码
 * \snippet demo_zm516x_search.c src_zm516x_search
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-23  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_zm516x_search
 * \copydoc demo_zm516x_search.c
 */

/** [src_zm516x_search] */
#include "aworks.h"
#include "aw_task.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "driver/zigbee/awbl_zm516x.h"
#include <string.h>

/** \brief 定义设备号，需要与 awbl_hwconf_zm516x.h 文件内的值相同 */
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
 * \brief 打印 ZM516X 模块的基本信息(通过搜索命令 D4 获得)
 */
aw_local void __base_info_print (awbl_zm516x_base_info_t *p_zm516x_base_info,
                                 uint8_t                  num)
{
    uint8_t i = 0;

    AW_INFOF(("\r\n__base_info_print\r\n"));

    for (i = 0; i < num; i++) {
        AW_INFOF(("software:0x%04x\r\n"
                  "chan:%d\r\n"
                  "data_rate:%d\r\n"
                  "panid:0x%04x\r\n"
                  "addr:0x%04x\r\n"
                  "state:0x%02x\r\n",
                  (p_zm516x_base_info + i)->software,
                  (p_zm516x_base_info + i)->chan,
                  (p_zm516x_base_info + i)->data_rate,
                  (p_zm516x_base_info + i)->panid,
                  (p_zm516x_base_info + i)->addr,
                  (p_zm516x_base_info + i)->state));
        AW_INFOF(("\r\n"));
    }
}

/**
 * \brief zm516x 例程入口
 */
void demo_zm516x_search_entry (void)
{
    uint8_t                 i              = 0;
    uint8_t                 j              = 0;
    uint8_t                 get_size       = 0;
    uint8_t                 signal         = 0;
    awbl_zm516x_base_info_t base_info[6];
    awbl_zm516x_cfg_info_t  zm516x_cfg_info;
    awbl_zm516x_cfg_info_t  remote_info;

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
    __cfg_info_print(&zm516x_cfg_info);

    /* 遍历所有通道 */
    for (i = 11; i <= 26; i++) {

        /* 设置 ZM516X 模块通道号 */
        if (awbl_zm516x_chan_set(__ID, i, TRUE) != AW_OK) {
            AW_INFOF(("awbl_zm516x_chan_set failed\r\n"));
            goto exit;
        }

        /* 搜索其它模块 */
        if (awbl_zm516x_discover(__ID,
                                 6,
                                 base_info,
                                &get_size) != AW_OK) {
            AW_INFOF(("channel %d has not found the device\r\n", i));
        } else {
            AW_INFOF(("\r\nchannel %d has found %d device\r\n", i, get_size));

            for (j = 0; j < get_size; j++) {
                AW_INFOF(("-------------the %d-------------\r\n", j));
                __base_info_print(&base_info[j], 1);

                /* 读取指定地址的 ZM516X 模块的信号强度 */
                if (awbl_zm516x_sigal_get(__ID,
                                          base_info[j].addr,
                                         &signal) != AW_OK) {
                    AW_INFOF(("failed to get 0x%04x signal\r\n",
                              base_info[j].addr));
                } else {
                    AW_INFOF(("signal: %ddBm\r\n", signal / 3 - 95));
                }

                /* 获取指定地址的 ZM516X 模块的配置信息 */
                if (awbl_zm516x_cfg_info_get(__ID,
                                             FALSE,
                                             base_info[j].addr,
                                            &remote_info) != AW_OK) {
                    AW_INFOF(("failed to get 0x%04x remote info\r\n",
                              base_info[j].addr));
                } else {
                    __cfg_info_print(&remote_info);
                }
            }
        }
    }

    AW_INFOF(("\r\nsearch complete, recovery the channal to %d\r\n",
                zm516x_cfg_info.chan));

    /* 恢复 ZM516X 模块通道号 */
    if (awbl_zm516x_chan_set(__ID, zm516x_cfg_info.chan, TRUE) != AW_OK) {
        AW_INFOF(("awbl_zm516x_cfg_channel_set failed\r\n"));
        goto exit;
    }

    AW_INFOF(("ZM516X Search Done\r\n"));

exit:
    return;
}

/** [src_zm516x_search] */

/* end of file */
