/*******************************************************************************
*                                 AWorks
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
 * \brief Ftpd���������
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_FTPD
 *      - ����
 *      - ���Դ���
 *      - AW_COM_CONSOLE
 *   2. ��PC�������뿪��������0�������޸�IP��ַ����֤��������PC��ͬ��������
 *   3. ���ӵ��Դ��ڵ�PC
 *   4. ʹ��FTPǰ����Ҫ���洢���������ļ�ϵͳ�У���ʹ��FAT����SD�����õ�һ�����ص�
 *   5. ��FTP�ͻ�����λ��������Ŀ��IP��������IP��ַ������������
 *
 * - ʵ������
 *   1. FTP��λ���������Ӻ��ܹ����ʵ��������Ϲ��ص��µ��ļ�
 *
 * - ��ע��
 *   1. ��֤�����뿪���崦��ͬһ�����Σ���������nic_manage��������������ip��Ҳ��ͨ��
 *      �޸Ķ�Ӧ���ڵ������ļ����޸�ip�������ļ�Ϊawbl_hwconf_xxx_emacX.h��XΪ��
 *      �ڱ�š�
 *
 * \par Դ����
 * \snippet demo_ftpd_server.c src_ftpd_server
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-07  cod, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_ftpd_server
 * \copydoc demo_ftpd_server.c
 */

/** [src_ftpd_server] */
#include "aworks.h"
#include "aw_ftpd.h"

#define __FTPD_LISTEN_PORT     21

/**
 * \brief FTPD�������
 * \return ��
 */
void demo_ftpd_server_entry (void)
{
    /* ���÷���·��Ϊ"/", �˿ں�Ϊ21��__FTPD_LISTEN_PORT������������   */
    aw_ftpd_init("/", __FTPD_LISTEN_PORT, 1, NULL);
}

/** [src_ftpd_server] */

/* end of file */
