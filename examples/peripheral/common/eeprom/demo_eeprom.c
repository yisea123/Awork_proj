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

/**
 * \file
 * \brief EEPROM 演示例程
 *
 * - 操作步骤:
 *   1. aw_prj_params.h 中使能
 *      - AW_DEV_EXTEND_EP24CXX_0
 *      - 及对应平台中和EEPROM设备相连的I2C宏定义
 *   2. aw_nvram_set 和 aw_nvram_get 接口中非易失性存储信息的名字必须与
 *      awbl_hwconf_ep24cxx_0.h 中的存储段名称一致。
 *   3. EEPROM 配置查看 awbl_hwconf_ep24cxx_0.h
 *
 * - 实验现象:
 *   1. 串口打印 EEPROM 操作结果信息。
 *   
 * \par 源代码
 * \snippet demo_eeprom.c src_eeprom
 *
 * \internal
 * \par History
 * - 1.00 17-09-04  may, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_src_eeprom
 * \copydoc demo_eeprom.c
 */
 
/** [src_eeprom] */
#include "aworks.h"

/* 本程序用到了以下服务 */
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "aw_nvram.h"
#include "string.h"

#define BUF_SIZE  16                    /* 读写缓冲区大小 */

aw_local uint8_t __g_buf[BUF_SIZE];     /* 读写缓冲区 */

/**
 * \brief EEPROM 演示例程入口
 * \return 无
 */
void demo_eeprom_entry (void)
{
    int i = 0;

    for (i = 0; i < BUF_SIZE; i++) {
        __g_buf[i] = i & 0xFF;
    }

    /* 设置 nvram 段 ep24cxx 数据,"ep24cxx"名字在 awbl_hwconf_ep24cxx_0.h配置文件中查看*/
    if (aw_nvram_set("ep24cxx", 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("ep24cxx NVRAM: Write Failed!\r\n"));
        return;
    }

    memset(__g_buf, 0, BUF_SIZE);

    /* 读取 nvram 段 ep24cxx 数据,"ep24cxx"名字在 awbl_hwconf_ep24cxx_0.h配置文件中查看*/
    if (aw_nvram_get("ep24cxx", 0, __g_buf, 0, BUF_SIZE) != AW_OK) {
        AW_INFOF(("ep24cxx NVRAM: Write Failed!\r\n"));
        return;
    }

    for (i = 0; i < BUF_SIZE; i++) {
        if (__g_buf[i] != (i & 0xFF)) {
            AW_INFOF(("ep24cxx NVRAM: Verify Failed!\r\n"));
            return;
        }
    }

    AW_INFOF(("ep24cxx NVRAM: Verify Successful!\r\n"));
}

/** [src_eeprom] */

/* end of file */
