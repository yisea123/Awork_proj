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
 * \brief relay driver.
 *
 * \internal
 * \par modification history
 * - 1.00 14-07-30  hbt, first implementation.
 * \endinternal
 */

#ifndef __AWBL_RELAY_H
#define __AWBL_RELAY_H

#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup awbl_relay
 * @{
 */
 
void awbl_relay_set (unsigned int id, bool_t on);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_RELAY_H */

/* end of file */
