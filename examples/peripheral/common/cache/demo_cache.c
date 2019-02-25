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
 * \brief cache例程
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能
 *      - 对应平台的串口宏
 *      - AW_COM_CONSOLE
 *   2. 将板子中的DURX、DUTX通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *
 * - 实验现象：
 *   1. 串口打印调试信息。
 *
 * - 备注：
 *   2. 如果工程在初始化时出错，请查看此demo所使用GPIO是否存在引脚复用。
 *
 * \par 源代码
 * \snippet demo_cache.c src_cache
 */

/**
 * \addtogroup demo_if_cache
 * \copydoc demo_cache.c
 */

/** [src_cache] */

#include "aworks.h"
#include "aw_cache.h"
#include "aw_vdebug.h"
#include <string.h>

/**
 * \brief cache demo
 * \return 无
 */
void demo_cache_entry (void)
{
    char *p_mem = NULL;

    /* 分配500字节大小的 cache-safe 的缓冲区  */
    p_mem = (char *)aw_cache_dma_malloc(500);
    if(p_mem == NULL){
        aw_kprintf("p_mem is NULL");
        return ;
    }

    memset(p_mem, '\0', 500);
    memcpy(p_mem, "test cache",sizeof("test cache"));
    AW_INFOF(("p_mem data : %s \n", p_mem));

    /* 释放 cache-safe 的缓冲区 */
    aw_cache_dma_free(p_mem);

    /* 分配指定对齐长度的 cache-safe 的缓冲区 */
    p_mem = aw_cache_dma_align(1000, 16);

    memset(p_mem, '\0', 1000);
    memcpy(p_mem, "test cache", sizeof("test cache"));
    AW_INFOF(("p_mem data : %s \n", p_mem));

    /* 释放 cache-safe 的缓冲区 */
    aw_cache_dma_free(p_mem);

    int  i = 0;
    uint8_t   buf[128] = {0};

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = (uint8_t)i;
    }

    /* 回写数据 */
    aw_cache_flush(buf, sizeof(buf));

    /* 将buf通过DMA传输出去 */
    // todo

    memset(buf, 0, sizeof(buf));
    aw_cache_flush(buf, sizeof(buf));
    /* 通过DMA读取数据至 buf */
    // todo

    aw_cache_invalidate(buf, sizeof(buf));

    /* 可以使用buf */
    // todo

    return ;
}

/** [src_cache] */

/* end of file */
