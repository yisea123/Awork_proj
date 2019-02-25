/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SATA disk driver head file
 *
 * define SATA disk driver data structure and functions
 *
 * \internal
 * \par modification history:
 * - 1.00 17-07-28  anu, first implementation
 * \endinternal
 */


#ifndef __AWBL_SATA_DISK_H
#define __AWBL_SATA_DISK_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "fs/aw_blk_dev.h"
#include "awbl_satabus.h"
#include "aw_sem.h"

struct awbl_sata_disk_dev;

#define AWBL_SATA_DISK_NAME    "awbl_sata_disk_driver"

typedef uint32_t awbl_sata_disk_flag_t;
#define AWBL_SATA_DISK_FLAG_LBA            (0X0001) /* 该设备支持LBA寻址 */
#define AWBL_SATA_DISK_FLAG_LBA48          (0X0002) /* 该设备支持LBA48寻址 */
#define AWBL_SATA_DISK_FLAG_NCQ            (0X0004) /* 该设备支持NCQ */
#define AWBL_SATA_DISK_FLAG_DMA            (0X0008) /* 该设备支持DMA */

/* 磁盘辨识信息 */
typedef struct awbl_sata_disk_identify {

    uint8_t  serial[20 + 1];        /* serial number */
    uint8_t  fw_rev[8 + 1];         /* firmware revision */
    uint8_t  model_num[40 + 1];     /* model number */

    uint32_t num_cylinders;     /* number of cylinders         (CHS) */
    uint32_t num_heads;         /* number of heads             (CHS) */
    uint32_t num_sectors;       /* number of sectors per track (CHS) */
    uint32_t sectors_cnt;       /* total number of sectors in LBA mode */

    uint32_t sector_size;       /* 扇区的大小 Byte */
    uint32_t disk_capacity;     /* 磁盘容量 MByte */

    awbl_sata_disk_flag_t flag; /* 该设备支持的功能 */

} awbl_sata_disk_identify_t;

/* 磁盘操作的驱动函数 */
typedef struct awbl_sata_disk_drv_funs {

    bool_t (*pfn_disk_type_probe) (
            struct awbl_sata_disk_dev *p_this);

    aw_err_t (*pfn_disk_identify_get) (
            struct awbl_sata_disk_dev *p_this,
            awbl_sata_disk_identify_t *p_identify_data);

    aw_err_t (*pfn_read) (struct awbl_sata_disk_dev *p_this,
                          uint32_t                   block_addr,
                          uint8_t                   *p_buf,
                          uint32_t                   len);

    aw_err_t (*pfn_write) (struct awbl_sata_disk_dev *p_this,
                           uint32_t                   block_addr,
                           uint8_t                   *p_buf,
                           uint32_t                   len);

} awbl_sata_disk_drv_funs_t;

/** \brief disk sata struct */
struct awbl_sata_disk_dev {

    struct awbl_satabus_dev *p_sata_dev;
    struct aw_blk_dev        bd;             /** \brief block device */

    awbl_sata_disk_drv_funs_t *p_drv_funs;
    awbl_sata_disk_identify_t  identify_data;

    bool_t   is_removed; /** \brief 是否被移除 */

    AW_MUTEX_DECL(mutex);

};


/**
 * \brief disk sata register
 */
void awbl_sata_disk_drv_register (void);

struct awbl_sata_disk_dev *aw_sata_disk_dev_get (const char *p_name);

aw_err_t aw_sata_disk_dev_put (struct awbl_sata_disk_dev *p_this);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_SATA_DISK_H */

