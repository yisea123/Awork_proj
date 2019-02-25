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
 * \brief lffs page buffers manipulations
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */

#ifndef _AW_LFFS_BUF_H
#define _AW_LFFS_BUF_H

#include "aw_lffs_core.h"

#ifdef __cplusplus
extern "C"{
#endif

#define AW_LFFS_CLONE_BUF_MARK      0xffff      //!< set aw_lffs_buf_St::ref_count to this for a 'cloned' buffer

/** for aw_lffs_buf_St::mark */
#define AW_LFFS_BUF_EMPTY      0           //!< buffer is empty
#define AW_LFFS_BUF_VALID      1           //!< buffer is holding valid data
#define AW_LFFS_BUF_DIRTY      2           //!< buffer data is modified

/** for aw_lffs_buf_St::ext_mark */
#define AW_LFFS_BUF_EXT_MARK_TRUNC_TAIL 1  //!< the last page of file (when truncating a file)

/** lffs page buffer */
struct aw_lffs_buf{
    struct aw_list_head     node;
    struct aw_list_head     dirty_node;
    uint8_t type;                            //!< #LFFS_TYPE_DIR or #LFFS_TYPE_FILE or #LFFS_TYPE_DATA
    uint8_t ext_mark;                        //!< extension mark.
    uint16_t parent;                         //!< parent serial
    uint16_t serial;                         //!< serial
    uint16_t page_id;                        //!< page id
    uint16_t mark;                           //!< #LFFS_BUF_EMPTY or #LFFS_BUF_VALID, or #LFFS_BUF_DIRTY ?
    uint16_t ref_count;                      //!< reference counter, or #CLONE_BUF_MARK for a cloned buffer
    uint16_t data_len;                       //!< length of data
    uint16_t check_sum;                      //!< checksum field
    uint8_t *data;                          //!< data buffer
    uint8_t *header;                        //!< header
};

#define aw_lffs_buf_is_free(buf) (buf->ref_count == 0 ? TRUE : FALSE)

/** initialize page buffers */
aw_err_t aw_lffs_buf_init (struct aw_lffs_device *dev, int buf_max, int dirty_buf_max);

/** release page buffers */
aw_err_t aw_lffs_buf_release_all (struct aw_lffs_device *dev);

/** find the page buffer, move to link list head if found */
aw_lffs_buf_t * aw_lffs_buf_get (struct aw_lffs_device *dev, uint16_t parent, uint16_t serial, uint16_t page_id);
aw_lffs_buf_t *aw_lffs_buf_get_ex (struct aw_lffs_device *dev, uint8_t type, aw_lffs_tree_node_t *node, uint16_t page_id, int oflag);

/** alloc a new page buffer */
aw_lffs_buf_t *aw_lffs_buf_new (struct aw_lffs_device *dev, uint8_t type, uint16_t parent, uint16_t serial, uint16_t page_id);

/** find the page buffer (not affect the reference counter) */
aw_lffs_buf_t * aw_lffs_buf_find (aw_lffs_device_t *dev, uint16_t parent, uint16_t serial, uint16_t page_id);

/** find the page buffer from #start (not affect the reference counter) */
aw_lffs_buf_t * aw_lffs_buf_find_ex (aw_lffs_device_t *dev, aw_lffs_buf_t *start,
                        uint16_t parent, uint16_t serial, uint16_t page_id);

/** put page buffer back to pool, called in pair with #lffs_Get,#lffs_GetEx or #aw_lffs_buf_New */
aw_err_t aw_lffs_buf_put (aw_lffs_device_t *dev, aw_lffs_buf_t *buf);

/** increase buffer references */
void aw_lffs_buf_ref_increase (aw_lffs_buf_t *buf);

/** decrease buffer references */
void aw_lffs_buf_ref_decrease (aw_lffs_buf_t *buf);

/** write data to a page buffer */
aw_err_t aw_lffs_buf_write (struct aw_lffs_device *dev, aw_lffs_buf_t *buf, void *data, uint32_t ofs, uint32_t len);

/** read data from a page buffer */
aw_err_t aw_lffs_buf_read (struct aw_lffs_device *dev, aw_lffs_buf_t *buf, void *data, uint32_t ofs, uint32_t len);

/** mark buffer as #LFFS_BUF_EMPTY if ref_count == 0, and discard all data it holds */
void aw_lffs_buf_mark_empty (aw_lffs_device_t *dev, aw_lffs_buf_t *buf);

/** if there is no free dirty group slot, flush the most dirty group */
aw_err_t aw_lffs_buf_flush (struct aw_lffs_device *dev);
aw_err_t aw_lffs_buf_flush_ex (struct aw_lffs_device *dev, bool_t force_block_recover);

/** flush dirty group */
aw_err_t aw_lffs_group_flush (struct aw_lffs_device *dev, uint16_t parent, uint16_t serial);
aw_err_t aw_lffs_group_flush_ex (struct aw_lffs_device *dev, uint16_t parent, uint16_t serial, bool_t force_block_recover);

/** find free dirty group slot */
int aw_lffs_free_group_slot_find (struct aw_lffs_device *dev);

/** find the dirty group slot */
int aw_lffs_group_slot_find (struct aw_lffs_device *dev, uint16_t parent, uint16_t serial);

/** lock dirty group */
aw_err_t aw_lffs_group_lock (struct aw_lffs_device *dev, int slot);

/** unlock dirty group */
aw_err_t aw_lffs_group_unlock (struct aw_lffs_device *dev, int slot);

/** flush most dirty group */
aw_err_t aw_lffs_most_dirty_group_flush (struct aw_lffs_device *dev);

/** flush all groups under the same parent number */
aw_err_t aw_lffs_buf_flush_by_parent (struct aw_lffs_device *dev, uint16_t parent);

/** flush all page buffers */
aw_err_t aw_lffs_buf_all_flush (struct aw_lffs_device *dev);

/** no one holding any page buffer ? safe to release page buffers */
bool_t aw_lffs_buf_is_all_free (struct aw_lffs_device *dev);

/** are all page buffer marked with #LFFS_BUF_EMPTY ? */
bool_t aw_lffs_buf_is_all_empty (struct aw_lffs_device *dev);

/** mark all page buffer as #LFFS_BUF_EMPTY */
aw_err_t aw_lffs_buf_set_all_empty (struct aw_lffs_device *dev);

/** clone a page buffer */
aw_lffs_buf_t * aw_lffs_clone_buf_get (struct aw_lffs_device *dev, aw_lffs_buf_t *buf);

/** release a cloned page buffer, call in pair with #aw_lffs_buf_Clone */
aw_err_t aw_lffs_clone_buf_put (aw_lffs_device_t *dev, aw_lffs_buf_t *buf);

/** showing page buffers info, for debug only */
void aw_lffs_buf_inspect (aw_lffs_device_t *dev);

#ifdef __cplusplus
}
#endif


#endif  /* _AW_LFFS_BUF_H */




