/*******************************************************************************
 *                                 AWorks
 *                       ---------------------------
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
 * \brief SPI Flash
 *
 * - 操作步骤:
 *   1. aw_prj_params.h中使能
 *      - AW_DEV_SPI_FLASH0
 *      - 对应平台,对应编号的SPI宏(用户可在awbl_hwconf_spi_flash0.h的配置文件查看使用具体的spi bus编号)
 *      - AW_COM_CONSOLE
 *   2. 将板子中的DURX、DUTX通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *   3. aw_spi_flash_open接口中Flash名字("/sflash0")必须与 awbl_hwconf_spi_flash0.h
 *      中的存储段名称一致。
 *
 * - 实验现象:
 *   1. 串口打印操作结果信息。
 *
 * \par 源代码
 * \snippet demo_spi_flash.c src_spi_flash
 *
 * \internal
 * \par History
 * - 1.00 17-09-05  deo, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_spi_flash
 * \copydoc demo_spi_flash.c
 */

/** [src_spi_flash] */
#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "aw_spi_flash.h"

/**
 * \brief SPI Flash 演示程序
 * \return 无
 */
void demo_spi_flash_entry (void)
{
    aw_spi_flash_t      pflash;
    aw_spi_flash_info_t info;
    aw_err_t            ret;
    static char         buf[512];
    uint32_t            i;

    /* 打开SPI Flash */
    pflash = aw_spi_flash_open("/sflash0");
    if (pflash == NULL) {
        aw_kprintf("No SPI Flash found!\r\n");
        while (1) {
            aw_mdelay(-1);
        }
    }

    /* 读取设备信息 */
    ret = aw_spi_flash_info_get(pflash, &info);
    if (ret == AW_OK) {
        aw_kprintf("SPI-Flash block size   %d bytes.\r\n", info.block_size);
        aw_kprintf("SPI-Flash block counts %d.\r\n",       info.nblocks);
        aw_kprintf("SPI-Flash page size    %d bytes.\r\n", info.page_size);
    }

    /* 擦除第0个块 */
    ret = aw_spi_flash_erase(pflash, 0);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash erase Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash erase Flash done.\r\n");

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = (char)(i & 0xFF);
    }

    /* 写入数据到第0个块 */
    ret = aw_spi_flash_write(pflash, 0, buf, sizeof(buf), NULL);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash write Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash write Flash done.\r\n");

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = 0;
    }

    /* 读回第0个块数据 */
    ret = aw_spi_flash_read(pflash, 0, buf, sizeof(buf), NULL);
    if (ret != AW_OK) {
        aw_kprintf("SPI-Flash read Flash failed %d.\r\n", ret);
        goto __exit;
    }
    aw_kprintf("SPI-Flash read Flash done.\r\n");

    /* 校验读写数据是否一致 */
    for (i = 0; i < sizeof(buf); i++) {
        if (buf[i] != (char)(i & 0xFF)) {
            aw_kprintf("SPI-Flash verify Flash data failed at %d.\r\n", i);
            goto __exit;
        }
    }

    aw_kprintf("SPI-Flash verify Flash data successfully.\r\n");

__exit:
    /* 关闭SPI FLASH设备 */
    aw_spi_flash_close(pflash);

    return ;
}

/** [src_spi_flash] */

/* end of file */
