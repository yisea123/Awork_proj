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
 * \brief lffs device structures definition
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */


#ifndef _AW_LFFS_DEVICE_H
#define _AW_LFFS_DEVICE_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * \addtogroup grp_aw_if_lffs_device
 * \copydoc aw_lffs_device.h
 * @{
 */

#include "aw_lffs_core.h"
#include "aw_lffs_tree.h"
#include "aw_lffs_mem.h"
#include "aw_lffs_os.h"

#if (AW_LFFS_CONFIG_ENABLE_INFO_TABLE == 1)
#include "aw_delayed_work.h"
#include "aw_sys_defer.h"
#endif

/**
 * \def AW_LFFS_MAX_DIRTY_BUF_GROUPS
 */
#define AW_LFFS_MAX_DIRTY_BUF_GROUPS    3

/**
 * \struct lffs_BlockInfoCacheSt
 * \brief block information structure, used to manager block information caches
 */
typedef struct aw_lffs_block_info_cache {
	struct aw_list_head      list;              //!< buffer list of block info(spares)
	void                    *mem_pool;	     	//!< internal memory pool, used for release whole buffer
} aw_lffs_block_info_cache_t;

/**
 * \struct lffs_PartitionSt
 * \brief partition basic information
 */
struct aw_lffs_partition {
	uint16_t start;		//!< start block number of partition
	uint16_t end;		//!< end block number of partition
};

/**
 * \struct lffs_LockSt
 * \brief lock stlffs
 */
struct aw_lffs_lock {
	aw_lffs_sem_t sem;
	int task_id;
	int counter;
};

/**
 * \struct lffs_DirtyGroupSt
 * \brief manager dirty page buffers
 */
typedef struct aw_lffs_dirty_group {
	int                  count;					//!< dirty buffers count
	int                  lock;					//!< dirty group lock (0: unlocked, >0: locked)
	struct aw_list_head  dirty_list;
} aw_lffs_dirty_group_t;

/**
 * \struct lffs_PageBufDescSt
 * \brief lffs page buffers descriptor
 */
typedef struct aw_lffs_page_buf {
    struct aw_list_head     list;
    struct aw_list_head     clone_list;

	aw_lffs_dirty_group_t   dirtyGroup[AW_LFFS_MAX_DIRTY_BUF_GROUPS];	//!< dirty buffer groups
	int                     buf_max;			//!< maximum buffers
	int                     dirty_buf_max;		//!< maximum dirty buffer allowed
	void                   *pool;				//!< memory pool for buffers
} aw_lffs_page_buf_t;


/**
 * \struct lffs_PageCommInfoSt
 * \brief common data for device, should be initialised at early
 * \note it is possible that pg_size is smaller than physical page size, but normally they are the same.
 * \note page data layout: [HEADER] + [DATA]
 */
typedef struct aw_lffs_page_info {
	uint16_t pg_data_size;			//!< page data size
	uint16_t header_size;			//!< header size
	uint16_t pg_size;				//!< page size
} aw_lffs_page_info_t;

/**
 * \struct lffs_FlashStatSt
 * \typedef lffs_FlashStat
 * \brief statistic data of flash read/write/erase activities
 */
typedef struct aw_lffs_flash_stat {
	int block_erase_count;
	int page_write_count;
	int page_read_count;
	int page_header_read_count;
	int spare_write_count;
	int spare_read_count;
	unsigned long io_read;
	unsigned long io_write;
} aw_lffs_flash_stat_t;


/**
 * \struct lffs_ConfigSt
 * \typedef lffs_Config
 * \brief lffs config parameters
 */
typedef struct aw_lffs_config {
	int bc_caches;
	int page_buffers;
	int dirty_pages;
	int dirty_groups;
	int reserved_free_blocks;
} aw_lffs_config_t;


/** pending block mark definitions */
#define AW_LFFS_PENDING_BLK_RECOVER	0		/* require block recovery and mark bad block */
#define AW_LFFS_PENDING_BLK_REFRESH	1		/* require refresh the block (erase and re-use it) */
#define AW_LFFS_PENDING_BLK_CLEANUP	2		/* require block cleanup (due to interrupted write, erase and re-use it) */

/**
 * \struct lffs_PendingBlockSt
 * \typedef lffs_PendingBlock
 * \brief Pending block descriptor
 */
typedef struct aw_lffs_pending_block {
	uint16_t block;			//!< pending block number
	uint8_t  mark;			//!< pending block mark
} aw_lffs_pending_block_t;

/**
 * \struct lffs_PendingListSt
 * \brief Pending block list
 */
typedef struct aw_lffs_pending_list {
	int                     count;				//!< pending block counter
	aw_lffs_pending_block_t list[AW_LFFS_CONFIG_MAX_PENDING_BLOCKS];	//!< pending block list
	uint16_t                block_in_recovery;         //!< pending block being recovered
} aw_lffs_pending_list_t;


#if (AW_LFFS_CONFIG_ENABLE_INFO_TABLE == 1)
/**
 * \brief 文件信息表
 */
typedef struct aw_lffs_info_table {
    struct aw_delayed_work  delay_work;
    struct aw_defer_djob    defer_job;
    struct aw_lffs_tree_node *p_node;   /**< \brief 当前使用的节点  */
    uint16_t sector_use_cnt;        /**< \brief 当前物理块的扇区使用记数  */
    uint16_t sector_valid_begin;    /**< \brief   */
    uint16_t sector_valid_cnt;      /**< \brief   */
    bool_t   is_valid;              /**< \brief 表中的数据是否有效  */
    aw_err_t err;
} aw_lffs_info_table_t;
#endif

/**
 * \brief The core data structure of LFFS, all information needed by manipulate LFFS object
 * \note one partition corresponding one lffs device.
 */
struct aw_lffs_device {
	aw_err_t (*Init)   (struct aw_lffs_device *dev);			//!< low level initialisation
	aw_err_t (*Release)(struct aw_lffs_device *dev);			//!< low level release
	void      *_private;								//!< private data for device

	struct aw_lffs_storage_attr		   *attr;		//!< storage attribute
	struct aw_lffs_partition			par;		//!< partition information
	struct aw_lffs_flash_ops		   *ops;		//!< flash operations
	struct aw_lffs_block_info_cache	    bc;			//!< block info cache
	struct aw_lffs_lock  				lock;		//!< lock data structure
	struct aw_lffs_page_buf     		buf;		//!< page buffers
	struct aw_lffs_page_info		    page_info;	//!< common information
	struct aw_lffs_tree 				tree;		//!< tree list of block
	struct aw_lffs_pending_list         pending;	//!< pending block list, to be recover/mark 'bad'/refresh
	struct aw_lffs_flash_stat			st;			//!< statistic (counters)
	struct aw_lffs_mem_allocator		mem;		//!< lffs memory allocator
	struct aw_lffs_config   			cfg;		//!< lffs config
	struct aw_lffs_info_table           info_tbl;   //!< lffs info table
	uint32_t	ref_count;								//!< device reference count
	int	        dev_num;								//!< device number (partition number)
	uint32_t    malloc_cnt;
};


/** create the lock for lffs device */
void aw_lffs_devicelock_init(aw_lffs_device_t *dev);

/** delete the lock of lffs device */
void aw_lffs_devicelock_release(aw_lffs_device_t *dev);

/** lock lffs device */
void aw_lffs_devicelock_lock(aw_lffs_device_t *dev);

/** unlock lffs device */
void aw_lffs_devicelock_unlock(aw_lffs_device_t *dev);


/** @}  grp_aw_if_lffs_device */

#ifdef __cplusplus
}
#endif


#endif

