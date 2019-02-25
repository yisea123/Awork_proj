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
 * \brief ·������
 *
 * \internal
 * \par modification history:
 * -17-03-24  deo, first implementation
 * \endinternal
 */


#define AW_IO_PATH_LEN_MAX   255


char *aw_io_pwd (void);
void aw_io_pwd_set (char *path);
aw_err_t aw_io_full_path (char *full, const char *path);

