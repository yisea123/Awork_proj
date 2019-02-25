/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.embedcontrol.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Header file for serial driver interface
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-26  orz, created
 * \endinternal
 */

#ifndef __AW_SIO_H
#define __AW_SIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_common.h"
#include "aw_sio_common.h"
#include "aw_ioctl.h"
#include "awbus_lite.h"

/**
 * \name SIO回调类型
 * @{
 */
#define AW_SIO_CALLBACK_GET_TX_CHAR     0
#define AW_SIO_CALLBACK_PUT_RCV_CHAR    1
#define AW_SIO_CALLBACK_ERROR           3
/** @} */

/**
 * \name SIO错误回调返回值
 * @{
 */
#define AW_SIO_ERROR_NONE               (-1)
#define AW_SIO_ERROR_FRAMING            0
#define AW_SIO_ERROR_PARITY             1
#define AW_SIO_ERROR_OFLOW              2
#define AW_SIO_ERROR_UFLOW              3
#define AW_SIO_ERROR_CONNECT            4
#define AW_SIO_ERROR_DISCONNECT         5
#define AW_SIO_ERROR_NO_CLK             6
#define AW_SIO_ERROR_UNKNWN             7
/** @} */

/**
 * \name SIO回调类型
 * @{
 */

/** \brief Get Tx Char callback */
typedef int  (*pfunc_sio_txchar_get_t)(void *p_arg, char *p_char);

/** \brief Put Rx Char callback */
typedef int  (*pfunc_sio_rxchar_put_t)(void *p_arg, char  ch);

/** \brief Error callback codes */
typedef int  (*pfunc_sio_err_t)(void *p_arg, int code, void *p_data, int size);

/** @} */

/**
 * \name serial device data structures
 * @{
 */

struct aw_sio_drv_funcs;

/** \brief a serial channel */
struct aw_sio_chan {
    struct aw_sio_drv_funcs *p_drv_funcs;
    /* device data */
};

/** \brief serial io channel information */
struct aw_sio_chan_info {
    int   chan_no;  /**< \brief channel number desired */
    void *p_chan;   /**< \brief p_chan for specified channel */
};

/** \brief serial io driver functions */
struct aw_sio_drv_funcs {
    /** \brief sio ioctl function */
    int (*pfunc_ioctl) (struct aw_sio_chan *p_siochan, int cmd, void *p_arg);

    /** \brief sio tx startup function */
    int (*pfunc_tx_startup) (struct aw_sio_chan *p_siochan);

    /** \brief sio call back install */
    int (*pfunc_callback_install) (struct aw_sio_chan *p_siochan,
                             int                       callback_type,
                             int                     (*pfunc_callback)(void *),
                             void                     *p_callback_arg);

    /** \brief sio poll input */
    int (*pfunc_poll_input) ( struct aw_sio_chan *p_siochan, char *p_inchar);

    /** \brief sio pool output */
    int (*pfunc_poll_output) (struct aw_sio_chan *p_siochan, char outchar);
};

/** @} */

/**
 * \name sio macros
 * @{
 */

#define aw_sio_ioctl(p_siochan, cmd, p_arg) \
    ((p_siochan)->p_drv_funcs->pfunc_ioctl(p_siochan, cmd, p_arg))

#define aw_sio_tx_startup(p_siochan) \
    ((p_siochan)->p_drv_funcs->pfunc_tx_startup(p_siochan))

#define aw_sio_callback_install(p_siochan,      callback_type,   \
                                pfunc_callback, callback_arg)    \
    ((p_siochan)->p_drv_funcs->pfunc_callback_install(p_siochan, \
                callback_type, pfunc_callback, callback_arg))

#define aw_sio_poll_input(p_siochan, inchar) \
    ((p_siochan)->p_drv_funcs->pfunc_poll_input(p_siochan, inchar))

#define aw_sio_poll_output(p_siochan, thischar) \
    ((p_siochan)->p_drv_funcs->pfunc_poll_output(p_siochan, thischar))

/** @} */

/** \brief sio methods */
AWBL_METHOD_IMPORT(aw_sio_chan_get);
AWBL_METHOD_IMPORT(aw_sio_chan_connect);

#ifdef __cplusplus
}
#endif

#endif  /* __AW_SIO_H */
