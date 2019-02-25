/*******************************************************************************
*                                  AWorks
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
 * \brief TODO文件描述
 *
 * 使用本服务需要包含头文件
 * \code
 * #include "aw_usbd_cdc_serial.h"
 * \endcode
 *
 * \internal
 * \par Modification History
 * - 1.00 17-12-26  xdn, first implementation
 * \endinternal
 */

#ifndef __AW_USBD_CDC_SERIAL_H
#define __AW_USBD_CDC_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * \addtogroup grp_aw_if_xx
 * \copydoc aw_usbd_cdc_serial.h
 * @{
 */


#define AW_USBD_CDC_SERIAL_NAME       "aw_usbd_cdc_serial"


struct aw_usbd_cdc_serial {
    struct awbl_dev          dev;
    struct awbl_devhcf       devhcf;
    int                      com;
    const struct aw_sio_drv_funcs *p_drv_funcs;

    int  (*pfunc_txchar_get)(void *, char *);
    int  (*pfunc_rxchar_put)(void *, char);
    void  *txget_arg;
    void  *rxput_arg;
};


/** @} grp_aw_if_xx */

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* __AW_USBD_CDC_SERIAL_H */

/* end of file */
