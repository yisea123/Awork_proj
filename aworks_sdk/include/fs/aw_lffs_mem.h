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
 * \brief
 *
 * \internal
 * \par modification history:
 * - 170923, vih, first implementation.
 * \endinternal
 */

#ifndef _AW_LFFS_MEM_H_
#define _AW_LFFS_MEM_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "aw_lffs_core.h"
#include "aw_lffs_pool.h"

/** lffs memory allocator */
struct aw_lffs_mem_allocator {
    aw_err_t (*init)    (struct aw_lffs_device *dev);            //!< init memory allocator, setup buffer sizes
    aw_err_t (*release) (struct aw_lffs_device *dev);         //!< release memory allocator (for dynamic memory allocation)

    void *   (*malloc)  (struct aw_lffs_device *dev, unsigned int size); //!< allocate memory (for dynamic memory allocation)
    aw_err_t (*free)    (struct aw_lffs_device *dev, void *p);   //!< free memory (for dynamic memory allocation)

    void * blockinfo_pool_buf;          //!< block info cache buffers
    void * pagebuf_pool_buf;            //!< page buffers
    void * tree_nodes_pool_buf;         //!< tree nodes buffer
//    void * spare_pool_buf;              //!< spare buffers

    int blockinfo_pool_size;            //!< block info cache buffers size
    int pagebuf_pool_size;              //!< page buffers size
    int tree_nodes_pool_size;           //!< tree nodes buffer size
//    int spare_pool_size;                //!< spare buffer pool size

    aw_lffs_pool_t tree_pool;
//    aw_lffs_pool_t spare_pool;

    int spare_data_size;                //!< spare size consumed by LFFS,
                                        //!< calculated by LFFS according to the layout information.

    /* for static memory allocator */
    char *buf_start;
    int buf_size;
    int pos;
};

void aw_lffs_mem_allocator_setup (aw_lffs_mem_allocator_t *allocator);

#ifdef __cplusplus
}
#endif


#endif

