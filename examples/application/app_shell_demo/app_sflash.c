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
 * \brief ͨ��shell�������SPI Flash
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_DEV_SPI_FLASH0
 *      - ��Ӧƽ̨�ģ���Ӧ��ŵ�SPI��
 *      - AW_CFG_SPI_FLASH_NVRAM
 *   2. ��shell�������".test"��Ŀ¼������"sflash -w ƫ�Ƶ�ַ   ����"��ָ��ƫ�Ƶ�ַ��д�����ݣ��磺
 *      sflash -w 0 AWorks
 *   3. ����"sflash -r ���˵�ַ ���ݸ���"��ָ��ƫ�Ƶ�ַ������ָ�������ݣ��磺
 *      sflash -r 0 6
 *
 * - ��ע��
 *   1. �����__APP_NVRAM_ITEM�����ֱ�����awbl_hwconf_spi_flash1.h �еĴ洢������һ�¡�
 *
 * \par Դ����
 * \snippet app_sflash.c app_sflash
 *
 * \internal
 * \par Modification History
 * - 1.00 18-07-11  sdq, first implementation.
 * \endinternal
 */

/** [src_app_sflash] */

#include "aworks.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */
#include "aw_shell.h"
#include "aw_nvram.h"
#include "aw_vdebug.h"
#include "app_config.h"
#include "string.h"

/* ����洢������ */
#define __APP_NVRAM_ITEM  "spi_flash0_nvram"

#ifdef APP_NVRAM
/******************************************************************************/
int app_sflash (int argc, char **argv, struct aw_shell_user *p_user)
{
    int       offs, len;
    char      buf[255];
    aw_err_t  ret;

    if (aw_shell_args_get(p_user, "-w", 2) == AW_OK) {
        char *pdat;
        /* ��ȡд��ƫ���������� */
        offs = aw_shell_long_arg(p_user, 1);
        pdat = aw_shell_str_arg(p_user, 2);
        if (pdat) {
            len = strlen(pdat);
        }

        /* д������ */
        ret = aw_nvram_set(__APP_NVRAM_ITEM, 0, pdat, offs, len);
        if (ret != AW_OK) {
            aw_kprintf("SPI-Flash write failed %d.\n", ret);
        } else {
            aw_kprintf("SPI-Flash write ok(%d).\n", len);
        }

    } else if (aw_shell_args_get(p_user, "-r", 2) == AW_OK) {
        /* ��ȡ��ȡƫ�ƺ����ݳ��� */
        offs = aw_shell_long_arg(p_user, 1);
        len  = aw_shell_long_arg(p_user, 2);
        len = min(sizeof(buf), len);

        /* ��ȡ���� */
        ret = aw_nvram_get(__APP_NVRAM_ITEM, 0, buf, offs, len);
        if (ret != AW_OK) {
            aw_kprintf("SPI-Flash read failed %d.\n", ret);
        } else {
            aw_kprintf("SPI-Flash read ok(%d).\n", len);
            buf[len] = '\0';
            aw_kprintf("data: %s\n", buf);
        }
    } else {
        return -AW_EINVAL;
    }

    return AW_OK;
}

/** [src_app_sflash] */
#endif /* APP_SFLASH */
