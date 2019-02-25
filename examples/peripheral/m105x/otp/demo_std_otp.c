/*******************************************************************************
*                                  AWorks
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
 * \brief OPT例程，向OPT区域 写入/读出 数据并读出（注意OPT只能写入一次）
 *
 * - 操作步骤：
 *   1. 需要在aw_prj_params.h头文件里使能AW_DEV_IMX1050_OCOTP
 *   2. 具体std_otp硬件配置需查看awbl_hwconf_imx1050_ocotp.h
 *
 * - 实验现象：
 *   1. 串口打印调试信息。
 *
 * \par 源代码
 * \snippet demo_std_otp.c src_std_otp
 *
 * \internal
 * \par modification history:
 * - 1.00 17-11-16, mex, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_otp
 * \copydoc demo_std_otp.c
 */

/** [src_std_otp] */
#include "aworks.h"
#include "aw_nvram.h"
#include "aw_vdebug.h"
#include "aw_psp_errno.h"
#include "stdio.h"

/* 是否使能OTP写测试，如果使能了，将会对OTP进行写操作，注意OTP只能写一次 */
#define OTP_WRITE_ENABLE  0

/* otp存储段名称和单元号，在awbl_hwconf_imx1050_ocotp.h 中查看修改  */
#define OTP_MEM           "otp_osp"
#define OTP_MEM_UNIT       0

/**
 * \brief OTP操作入口
 * \return 无
 */
void demo_std_otp_entry (void)
{
    aw_err_t ret = AW_OK;
    uint64_t read_data;

#if OTP_WRITE_ENABLE
    uint32_t write_data = 0;

    write_data = 7;

    /* 写入数据 */
    ret = aw_nvram_set(OTP_MEM, OTP_MEM_UNIT, (char *)&write_data, 0, 4);
    if(AW_OK != ret){
        aw_kprintf("aw_nvram_set error.\r\n");
        return ;
    }
    aw_kprintf("write data: %x\n", write_data);
#endif

    /* 读取数据 */
    ret = aw_nvram_get(OTP_MEM, OTP_MEM_UNIT, (char *)&read_data, 0, 8);
    if(AW_OK != ret){
        aw_kprintf("aw_nvram_get error.\r\n");
        return ;
    }
    printf("read data: 0x%llx\n", read_data);

    return ;
}


/** [src_std_otp] */

/* end of file */
