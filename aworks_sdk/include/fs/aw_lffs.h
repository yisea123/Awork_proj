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
 * \brief  UFFS interface to IO system.
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */


#ifndef __AW_LFFS_H /* { */
#define __AW_LFFS_H


#ifdef __cplusplus
extern "C" {
#endif


/**
 * \addtogroup grp_lffs_ios
 * @{
 */

#include "apollo.h"
#include "aw_types.h"
#include "aw_time.h"
#include "aw_sem.h"
#include "aw_compiler.h"
#include "io/aw_io_device.h"
#include "aw_lffs_flash.h"
#include "aw_lffs_mtb.h"
#include "aw_lffs_fd.h"
#include "aw_lffs_device.h"
#include "mtd/aw_mtd.h"



/** \brief fat file system volume descriptor */
struct aw_lffs_volume {
    struct aw_iodev     ios_dev; /**< \brief I/O system device instance */
    struct aw_mtd_info *mtd;     /**< \brief backing MTD device */
    /**
     * \name UFFS
     * @{
     */
    struct aw_lffs_device           udev;       /**< \brief UFFS flash device */
    struct aw_lffs_storage_attr     attr;       /**< \brief flash attribute */
    struct aw_lffs_mount_table      mtbl;       /**< \brief device mount entry */
    char                            mpoint[16]; /**< \brief mount point in UFFS */
    void                           *pool;
    uint32_t                        pool_size;
    /** @} */
};

/** \brief fat device file descriptor */
struct aw_lffs_file_desc {
    struct aw_lffs_volume       *volume; /**< \brief UFFS volume */
    int                          oflags; /**< \brief flags */
    union {
        int                      fdesc;  /**< \brief UFFS file descriptor */
        struct aw_lffs_dir_info      *dir;
    };
};

/** \brief UFFS initializing data */
struct aw_lffs_init_struct {
    struct aw_lffs_volume      *vol_pool;      /**< \brief volume pool memory */
    unsigned int                vol_pool_size; /**< \brief volume pool size */
    struct aw_lffs_file_desc   *fil_pool;      /**< \brief file descriptor pool */
    unsigned int                fil_pool_size; /**< \brief file descriptor pool size*/

#if ((AW_UFFS_CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR == 0) || \
     (!defined(AW_UFFS_CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR)))
    void                   *buf_pool;
    unsigned int           buf_pool_size;
    unsigned int           buf_item_size;
#endif
};

int aw_lffs_init (const struct aw_lffs_init_struct *init);

void aw_lffs_mtd_init (struct aw_lffs_volume *vol);
void aw_lffs_mtd_erase (struct aw_lffs_volume *vol);
void aw_lffs_flash_init (struct aw_lffs_volume *vol);
void aw_lffs_flash_erase (struct aw_lffs_volume *vol);

int aw_lffs_volume_register   (struct aw_lffs_volume *vol);
int aw_lffs_volume_unregister (struct aw_lffs_volume *vol);


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* } __FS_AW_UFFS_H */

/* end of file */
