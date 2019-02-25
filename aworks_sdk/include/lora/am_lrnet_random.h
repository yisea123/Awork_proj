/*******************************************************************************
*                                 LoRaNet
*                  ----------------------------------------
*                    LoRa low power network protocol stack
*
* Copyright (c) 2001-present Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief   LoRaNet Random Module
 *
 * \internal
 * \par modification history:
 * - 2017-05-23 ebi, first implementation.
 * \endinternal
 */

#ifndef __AM_LRNET_RANDOM_H
#define __AM_LRNET_RANDOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_lrnet_internal.h"

void am_lrnet_random_module_init (uint32_t seed);

uint32_t am_lrnet_random (uint8_t exp);

#ifdef __cplusplus
}
#endif

#endif /* __AM_LRNET_RANDOM_H */

/* end of file */
