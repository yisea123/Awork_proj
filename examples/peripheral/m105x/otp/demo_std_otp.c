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
 * \brief OPT���̣���OPT���� д��/���� ���ݲ�������ע��OPTֻ��д��һ�Σ�
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��AW_DEV_IMX1050_OCOTP
 *   2. ����std_otpӲ��������鿴awbl_hwconf_imx1050_ocotp.h
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ϣ��
 *
 * \par Դ����
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

/* �Ƿ�ʹ��OTPд���ԣ����ʹ���ˣ������OTP����д������ע��OTPֻ��дһ�� */
#define OTP_WRITE_ENABLE  0

/* otp�洢�����ƺ͵�Ԫ�ţ���awbl_hwconf_imx1050_ocotp.h �в鿴�޸�  */
#define OTP_MEM           "otp_osp"
#define OTP_MEM_UNIT       0

/**
 * \brief OTP�������
 * \return ��
 */
void demo_std_otp_entry (void)
{
    aw_err_t ret = AW_OK;
    uint64_t read_data;

#if OTP_WRITE_ENABLE
    uint32_t write_data = 0;

    write_data = 7;

    /* д������ */
    ret = aw_nvram_set(OTP_MEM, OTP_MEM_UNIT, (char *)&write_data, 0, 4);
    if(AW_OK != ret){
        aw_kprintf("aw_nvram_set error.\r\n");
        return ;
    }
    aw_kprintf("write data: %x\n", write_data);
#endif

    /* ��ȡ���� */
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
