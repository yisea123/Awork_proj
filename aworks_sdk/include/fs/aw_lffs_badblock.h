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
 * \brief bad block management
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */

#ifndef _AW_LFFS_BADBLOCK_H_
#define _AW_LFFS_BADBLOCK_H_

#include "aw_lffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif  /* __cplusplus  */


#define AW_LFFS_HAVE_BADBLOCK(dev) (dev->pending.count > 0)

/** initialize bad block management data structures for lffs device */
void aw_lffs_bad_block_init (aw_lffs_device_t *dev);

/** processing bad block: erase bad block,
	mark it as 'bad' and put it to bad block list */
void aw_lffs_bad_block_node_process (aw_lffs_device_t *dev, aw_lffs_tree_node_t *node);

/** try to recover data from a new discovered bad block */
void aw_lffs_bad_block_recover (aw_lffs_device_t *dev);

/** put a new block to the bad block waiting list */
void aw_lffs_bad_block_add (aw_lffs_device_t *dev, int block, uint8_t mark);

/** Check if a block is in bad block pending list */
bool_t aw_lffs_block_is_in_pending (aw_lffs_device_t *dev, int block);

/** Remove block from pending list */
aw_err_t aw_lffs_bad_block_pending_remove (aw_lffs_device_t *dev, int block);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif

