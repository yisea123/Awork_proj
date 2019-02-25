/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB wireless module driver source file (GPRS,3G,4G)
 *
 * \internal
 * \par modification history:
 * - 1.00 17-07-08  deo, first implementation
 * \endinternal
 */

#ifndef __AWBL_SERIAL_USBH_WIRELESS_H
#define __AWBL_SERIAL_USBH_WIRELESS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


#define AWBL_USBH_SERIAL_WIRELESS_DRV_NAME     "awbl_usbh_serial_wireless_driver"


/** \brief register USB wireless driver */
void awbl_usbh_serial_wireless_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_SERIAL_USBH_WIRELESS_H */
