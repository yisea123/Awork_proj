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
 * \brief 串口通讯驱动内部头文件
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-29  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_SERIAL_PRIVATE_H
#define __AWBL_SERIAL_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "awbl_sio.h"
#include "aw_ty.h"

/**
 * \addtogroup grp_aw_serial_if
 * @{
 */

/* data types */
struct aw_serial {
    struct aw_tydev     tydev;
    struct aw_sio_chan *p_siochan;
};

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_SERIAL_PRIVATE_H */

/* end of file */
