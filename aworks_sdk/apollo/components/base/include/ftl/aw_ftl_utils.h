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
 * \brief utilities
 *
 * \internal
 * \par modification history:
 * - 1.00 2017-4-15   vih, first implementation.
 * \endinternal
 */

#ifndef __AW_FTL_UTILS_H
#define __AW_FTL_UTILS_H

/**
 * \addtogroup grp_aw_if_ftl_utils
 * \copydoc aw_ftl_utils.h
 * @{
 */

#include "aworks.h"


#ifdef __cplusplus
extern "C" {
#endif


//#define AW_FTL_UTILS_DEBUG_OUTPUT

#if  defined(AW_FTL_UTILS_DEBUG_OUTPUT)

#include "aw_shell.h"

extern int aw_ftl_message_mask;

#define AW_FTL_PRINTF(fmt, ...)  aw_shell_printf(AW_DBG_SHELL_IO, fmt, ##__VA_ARGS__)
//#define AW_FTL_PRINTF(fmt, ...)  aw_kprintf(fmt, ##__VA_ARGS__)

#define AW_FTL_MSG(mask, fmt, ...)   \
    do {\
        if ((mask) & aw_ftl_message_mask) {\
            if (((mask) & AW_FTL_MSG_NO_PFX) == 0) {\
                AW_FTL_PRINTF("%s(%d): ", PFX, __LINE__);\
            }\
            AW_FTL_PRINTF(fmt, ##__VA_ARGS__);\
            if (((mask) & AW_FTL_MSG_NO_PFX) == 0) {\
                AW_FTL_PRINTF("\n");\
            }\
        }\
    } while (0)

#define AW_FTL_ERR_MSG(mask, fmt, ...) \
    do {\
        if ((mask) & aw_ftl_message_mask) {\
            aw_shell_color_set(AW_DBG_SHELL_IO, AW_SHELL_FCOLOR_RED);\
            AW_FTL_PRINTF(" \n%s ERROR: ", PFX);\
            aw_shell_color_set(AW_DBG_SHELL_IO, AW_SHELL_FCOLOR_DEFAULT);\
            AW_FTL_PRINTF(fmt, ##__VA_ARGS__);\
            AW_FTL_PRINTF(".\n%s ERROR: at file %s"\
                          ".\n%s ERROR: at line %d in %s()\n\n", \
                           PFX, __FILE__, \
                           PFX, __LINE__, \
                           __FUNCTION__); \
        }\
    } while(0)
#endif

#ifndef AW_FTL_MSG
#define AW_FTL_MSG
#endif

#ifndef AW_FTL_ERR_MSG
#define AW_FTL_ERR_MSG
#endif

typedef enum {
    AW_FTL_MSG_MASK_FLASH       = (0x00000001 << 1),
    AW_FTL_MSG_MASK_SYS         = (0x00000001 << 2),
    AW_FTL_MSG_MASK_BLK         = (0x00000001 << 3),
    AW_FTL_MSG_MASK_UTILS       = (0x00000001 << 4),
    AW_FTL_MSG_MASK_MAP         = (0x00000001 << 5),
    AW_FTL_MSG_MASK_ITF         = (0x00000001 << 6),
    AW_FTL_MSG_MASK_RD          = (0x00000001 << 7),
    AW_FTL_MSG_MASK_WD          = (0x00000001 << 8),
    AW_FTL_MSG_MASK_FORMAT      = (0x00000001 << 9),

    AW_FTL_MSG_MASK_UNDEF       = (0x00000001 << 29),
    AW_FTL_MSG_MASK_ERR         = (0x00000001 << 30),
    AW_FTL_MSG_NO_PFX           = (0x00000001 << 31),
} aw_ftl_msg_mask_t;

struct aw_ftl_pb_hdr;
struct aw_ftl_dev;
struct aw_ftl_blk_info;

bool_t aw_ftl_blk_hdr_format_verify (struct aw_ftl_pb_hdr *p_blk_hdr);

uint32_t aw_ftl_blk_id_get (struct aw_ftl_dev *p_ftl, uint32_t pbn);

struct aw_ftl_blk_info *aw_ftl_pbn_info_get (struct aw_ftl_dev *p_ftl,
                                             uint16_t           pbn);

struct aw_ftl_blk_info * aw_ftl_free_node_get (struct aw_ftl_dev *p_ftl);

void aw_ftl_free_node_add (struct aw_ftl_dev *p_ftl,
                           uint16_t           pbn);

void aw_ftl_dirty_blk_recover (struct aw_ftl_dev *p_ftl);

int aw_ftl_dirty_node_add (struct aw_ftl_dev      *p_ftl,
                           struct aw_ftl_blk_info *blk_info);

void aw_ftl_dirty_node_del (struct aw_ftl_dev      *p_ftl,
                            struct aw_ftl_blk_info *blk_info);

/**
 * \brief ���������뵽���������У�����Ըÿ��Ƿ�����Ļ���
 *
 * \param[in] p_ftl : FTL�豸�ṹ��
 * \param[in] pbn : �������
 *
 * \return ��
 */
void aw_ftl_bad_node_add (struct aw_ftl_dev *p_ftl,
                          uint16_t           pbn);

/**
 * \brief ������������������еĿ��Ƿ�����ǻ��飬���������Ὣ�ÿ�Ż�free����
 *
 * \param[in] p_ftl : FTL�豸�ṹ��
 *
 * \return ��
 */
void aw_ftl_bad_list_process (struct aw_ftl_dev *p_ftl);


void *aw_ftl_mem_alloc (struct aw_ftl_dev *p_ftl, int size);
void aw_ftl_mem_free (struct aw_ftl_dev *p_ftl, void **pp_mem);

int aw_ftl_defer_job_init (struct aw_ftl_dev *p_this,
                       void              (*pfunc) (void *));
void aw_ftl_defer_job_start (struct aw_ftl_dev *p_this, uint32_t ms_tim);
void aw_ftl_defer_job_stop (struct aw_ftl_dev *p_this);



/** @}  grp_aw_if_ftl_utils */

#ifdef __cplusplus
}
#endif

#endif /* __AW_FTL_UTILS_H */



/* end of file */
