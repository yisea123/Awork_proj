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
 * \brief I/O API for application.
 *
 * \internal
 * \par modification history:
 * - 160726 deo, first implementation.
 * \endinternal
 */

#ifndef __AW_IO_LIB_H
#define __AW_IO_LIB_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_iosys_list
 * @{
 */

#include "aw_list.h"

/**
 * \brief ɾ���ļ�
 *
 * \param[in]        path     �ļ�·��
 *
 * \return �ɹ�����AW_OK�����򷵻�ֵΪ������룬�� aw_errno.h ��
 */
int aw_delete (const char *path);

/** @} grp_iosys_list */

#ifdef __cplusplus
}
#endif

#endif /* __AW_IO_LIB_H */
