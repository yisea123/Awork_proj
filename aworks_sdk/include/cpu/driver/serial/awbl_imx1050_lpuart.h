/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief IMX1050 LPUART
 *
 * \internal
 * \par modification history:
 * - 1.00 17-08-25  smc, first implementation
 * \endinternal
 */

#ifndef __AWBL_IMX1050_LPUART_H__
#define __AWBL_IMX1050_LPUART_H__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_spinlock.h"
#include "aw_serial.h"
#include "awbl_sio.h"

#define AWBL_IMX1050_LPUART_DRV_NAME       "imx1050_lpuart"

/*******************************************************************************
     types
*******************************************************************************/
/**\brief imx1050 lpuart device channel structure  for awbus lite */
typedef struct awbl_imx1050_lpuart_chan {
    struct aw_sio_chan  sio_chan;

    /** \brief pointer to xmitr func */
    int (*pfunc_txchar_get)(void *, char *);
    /** \brief pointer to rcvr func */
    int (*pfunc_rxchar_put)(void *, char );

    void               *txget_arg;   /**< \brief argument for xmitr func */
    void               *rxput_arg;   /**< \brief argument for rcvr func */

    uint8_t             channel_mode;  /**< \brief such as INT, POLL modes */
    uint8_t             channel_no;    /**< \brief channel number */
    uint16_t            options;       /**< \brief hardware setup options */
    uint32_t            baud_rate;     /**< \brief baud rate */
    int                 is_tx_int_en;  /**< \brief is transmit interrupt enable? */

    int                 is_rs485_tx;

    aw_spinlock_isr_t   dev_lock;
    /**
     * \brief next channel for this device
     *
     * Each device may have multiple channels. Here we maintain
     * a linked list of channels per controller.
     */
    struct awbl_imx1050_lpuart_chan *p_next;

}awbl_imx1050_lpuart_chan_t;


/** \brief imx1050 lpuart initialization structure
 *         for plb based AWBus devices
 * */
typedef struct awbl_imx1050_lpuart_dev_info {
    int             inum;                   /**< \brief Actual architectural vector */
    uint32_t        regbase;                /**< \brief Virt address of register set */
    aw_clk_id_t     async_parent_clk_id;    /**< \brief clk id */
    uint32_t        init_baudrate;          /**< \brief baud init */
    /** \brief BSP function to pre initialize the device */
    void            (*pfunc_plfm_init)(void);
    void            (*pfunc_rs485_dir)(uint8_t dir);
}awbl_imx1050_lpuart_dev_info_t;

/** \brief imx1050 uart dev. one dev may contain multi chan.  */
typedef struct awbl_imx1050_uart_dev {
    /** \brief awbl device data */
    struct awbl_dev                      dev;
    /**< \brief imx1050 channel data */
    struct awbl_imx1050_lpuart_chan      chan;
}awbl_imx1050_uart_dev_t;

void awbl_imx1050_lpuart_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_IMX1050_LPUART_H__ */

/* end of file */


