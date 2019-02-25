/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * @file
 * @brief System DNS client interface.
 *
 * @internal
 * @par History
 * - 18-06-05, phd, first implementation.
 * @endinternal
 */

#ifndef __AW_DNS_H /* { */
#define __AW_DNS_H

#include "aworks.h"
#include "net/aw_sockets.h"

aw_err_t aw_dns_get (int idx, struct in_addr *addr);
aw_err_t aw_dns_set (int idx, struct in_addr *addr);

#endif /* } __AW_DNS_H */

/* end of file */
