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
 * \brief RTK �����׼�ӿ�ͷ�ļ�
 *
 * \internal
 * \par modification history:
 * - 1.00 14-01-23  zen, first implementation
 * \endinternal
 */
#ifndef __AW_PSP_CACHE_H
#define __AW_PSP_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#if defined(AW_CORTEX_M0)
#define AW_PSP_CACHE_LINE_SIZE  4
#endif

#if defined(AW_CORTEX_M4)
#define AW_PSP_CACHE_LINE_SIZE  4
#endif

#if defined(AW_CORTEX_M3)
#define AW_PSP_CACHE_LINE_SIZE  4
#endif

#if defined(AW_CORTEX_M7)
#include "aw_psp_cache_armv7m.h"
#endif

#if defined(AW_ARM926EJ_S)
#include "aw_psp_cache_armv4.h"
#endif

#if defined(AW_ARMV7)
#include "aw_psp_cache_armv7.h"
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_PSP_CACHE_H */

/* end of file */
