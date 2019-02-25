/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief FatFs AWorks adapter layer
 *
 * \internal
 * \par modification history:
 * - 1.00 16-11-07  deo, first implementation
 * \endinternal
 */

#ifndef __AW_FATFS_OS_H
#define __AW_FATFS_OS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_sem.h"

struct aw_fatfs_mutex {
    AW_MUTEX_DECL(lock);
};

typedef struct aw_fatfs_mutex  aw_fatfs_mutex_t;
typedef struct aw_fatfs_mutex* aw_fatfs_mutex_pt;

#ifdef __cplusplus
}
#endif

#endif /* __AW_FATFS_OS_H */
