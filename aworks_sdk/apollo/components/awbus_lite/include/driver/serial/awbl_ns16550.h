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
 * \brief National Semiconductor 16550 compatible UART header file
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-25  orz, first implementation
 * \endinternal
 */

#ifndef __AWBL_NS16550_H
#define __AWBL_NS16550_H

/**
 * \addtogroup grp_awbl_drv_ns16550
 * @{
 */

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#include "aw_isr_defer.h"
#include "stdint.h"
#include "aw_delayed_work.h"

/*******************************************************************************
    defines
*******************************************************************************/
#if 0
#define AWBL_CONFIG_NS16550_JOBQ    /* Use job queue for this driver */
#endif

/**
 * \name Register offsets from base address
 * @{
 */
#define __RBR     0x00    /**< \brief receiver buffer register */
#define __THR     0x00    /**< \brief transmit holding register */
#define __DLL     0x00    /**< \brief divisor latch */
#define __IER     0x01    /**< \brief interrupt enable register */
#define __DLM     0x01    /**< \brief divisor latch(MS) */
#define __IIR     0x02    /**< \brief interrupt identification register */
#define __FCR     0x02    /**< \brief FIFO control register */
#define __LCR     0x03    /**< \brief line control register */
#define __MCR     0x04    /**< \brief modem control register */
#define __LSR     0x05    /**< \brief line status register */
#define __MSR     0x06    /**< \brief modem status register */
#define __SCR     0x07    /**< \brief scratch register */
/** @} */

/**
 * \name Line Control Register
 * @{
 */
#define __CHAR_LEN_5  0x00    /**< \brief 5bits data size */
#define __CHAR_LEN_6  0x01    /**< \brief 6bits data size */
#define __CHAR_LEN_7  0x02    /**< \brief 7bits data size */
#define __CHAR_LEN_8  0x03    /**< \brief 8bits data size */
#define __LCR_STB     0x04    /**< \brief 2 stop bits */
#define __ONE_STOP    0x00    /**< \brief one stop bit */
#define __LCR_PEN     0x08    /**< \brief parity enable */
#define __PARITY_NONE 0x00    /**< \brief parity disable */
#define __LCR_EPS     0x10    /**< \brief even parity select */
#define __LCR_SP      0x20    /**< \brief stick parity select */
#define __LCR_SBRK    0x40    /**< \brief break control bit */
#define __LCR_DLAB    0x80    /**< \brief divisor latch access enable */
#define __DLAB        __LCR_DLAB
/** @} */

/**
 * \name Line Status Register
 * @{
 */
#define __LSR_DR      0x01    /**< \brief data ready */
#define __RXCHAR_RDY  __LSR_DR  /**< \brief data ready */
#define __LSR_OE      0x02    /**< \brief overrun error */
#define __LSR_PE      0x04    /**< \brief parity error */
#define __LSR_FE      0x08    /**< \brief framing error */
#define __LSR_BI      0x10    /**< \brief break interrupt */
#define __LSR_THRE    0x20    /**< \brief transmit holding register empty */
#define __LSR_TEMT    0x40    /**< \brief transmitter empty */
#define __LSR_FERR    0x80    /**< \brief in FIFO mode, set when PE,FE,BI error */
/** @} */

/**
 * \name Interrupt Identification Register
 * @{
 */
#define __IIR_IP      0x01
#define __IIR_ID      0x0e
#define __IIR_RLS     0x06    /**< \brief received line status */
#define __RX_INT      __IIR_RLS /**< \brief received line status */
#define __IIR_RDA     0x04    /**< \brief received data available */
#define __RXFIFO_INT  __IIR_RDA /**< \brief received data available */
#define __IIR_THRE    0x02    /**< \brief transmit holding register empty */
#define __TXFIFO_INT  __IIR_THRE
#define __IIR_MSTAT   0x00    /**< \brief modem status */
#define __IIR_TIMEOUT 0x0c    /**< \brief char receive timeout */
/** @} */

/**
 * \name Interrupt Enable Register
 * @{
 */
#define __IER_ERDAI   0x01    /**< \brief received data avail. & timeout int */
#define __RXFIFO_BIT  __IER_ERDAI
#define __IER_ETHREI  0x02    /**< \brief transmitter holding register empty int*/
#define __TXFIFO_BIT  __IER_ETHREI
#define __IER_ELSI    0x04    /**< \brief receiver line status int enable */
#define __RX_BIT      __IER_ELSI
#define __IER_EMSI    0x08    /**< \brief modem status int enable */
/** @} */

/**
 * \name Modem Control Register
 * @{
 */
#define __MCR_DTR     0x01    /**< \brief dtr output */
#define __DTR         __MCR_DTR
#define __MCR_RTS     0x02    /**< \brief rts output */
#define __MCR_OUT1    0x04    /**< \brief output #1 */
#define __MCR_OUT2    0x08    /**< \brief output #2 */
#define __MCR_LOOP    0x10    /**< \brief loopback enable */
/** @} */

/**
 * \name Modem Status Register
 * @{
 */
#define __MSR_DCTS    0x01    /**< \brief cts change */
#define __MSR_DDSR    0x02    /**< \brief dsr change */
#define __MSR_TERI    0x04    /**< \brief ring indicator change */
#define __MSR_DDCD    0x08    /**< \brief data carrier indicator change */
#define __MSR_CTS     0x10    /**< \brief complement of cts */
#define __MSR_DSR     0x20    /**< \brief complement of dsr */
#define __MSR_RI      0x40    /**< \brief complement of ring signal */
#define __MSR_DCD     0x80    /**< \brief complement of dcd */
/** @} */

/**
 * \name FIFO Control Register
 * @{
 */
#define __FCR_EN          0x01        /**< \brief enable xmit and rcvr */
#define __FIFO_ENABLE     __FCR_EN
#define __FCR_RXCLR       0x02        /**< \brief clears rcvr fifo */
#define __RXCLEAR         __FCR_RXCLR
#define __FCR_TXCLR       0x04        /**< \brief clears xmit fifo */
#define __TXCLEAR         __FCR_TXCLR
#define __FCR_DMA         0x08        /**< \brief dma */
#define __FCR_RXTRIG_L    0x40        /**< \brief rcvr fifo trigger lvl low */
#define __FCR_RXTRIG_H    0x80        /**< \brief rcvr fifo trigger lvl high */
/** @} */

/*******************************************************************************
    types
*******************************************************************************/


/** \brief UART 16550 device channel structure for awbus lite */
struct awbl_ns16550_chan {
    /** \brief driver functions, always goes first */
    aw_const struct aw_sio_drv_funcs *p_drv_funcs;

    /** \brief pointer to xmitr func */
    int  (*pfunc_txchar_get)(void *, char *);

    /** \brief pointer to rcvr func */
    int  (*pfunc_rxchar_put)(void *, char);
    
    int  rs485_dir_pin;
    int  rs485_tx_level;
    int  rs485_enable;

    void  *txget_arg;   /**< \brief argument for xmitr func */
    void  *rxput_arg;   /**< \brief argument for rcvr func */

    uint8_t *p_regs;    /**< \brief 16550 registers */

    uint8_t  ier;       /**< \brief copy of ier */
    uint8_t  lcr;       /**< \brief copy of lcr, not used by ns16552 driver */
    uint8_t  mcr;       /**< \brief copy of modem control register */
    uint8_t  ier_init;  /**< \brief initial __IER register value */

    uint8_t  channel_mode;  /**< \brief such as INT, POLL modes */
    uint8_t  channel_no;    /**< \brief channel number */
    uint8_t  tx_defer;      /**< \brief TX interrupt is currently deferred */
    uint8_t  reg_space;     /**< \brief register address spacing */
    uint16_t fifo_size;     /**< \brief FIFO depth */
    uint16_t options;       /**< \brief hardware setup options */
    uint32_t baud_rate;     /**< \brief baud rate */

    awbl_dev_t *p_dev;              /**< \brief bus subsystem: device ID */

    void             *handle;       /**< \brief register access handle */
    aw_spinlock_isr_t spinlock_isr; /**< \brief ISR-callable spinlock */

#ifdef AWBL_CONFIG_NS16550_JOBQ
    struct aw_isr_defer_job  isr_jobq;     /**< \brief Job queue for ISR */
#endif

    /**
     * \brief next channel for this device
     *
     * Each device may have multiple channels. Here we maintain
     * a linked list of channels per controller.
     */
    struct awbl_ns16550_chan *p_next;


//    struct aw_delayed_work dwork_rs485_dir;
};

AWBL_METHOD_IMPORT(aw_sio_dev2chan);
struct awbl_ns16550_chan *awbldev_to_nschan(awbl_dev_t *p_dev);


/** \brief 16550 initialization structure for plb based AWBus devices */
struct awbl_ns16550_chan_param {
    int      vector;    /**< \brief Actual architectural vector */
    uint32_t base_addr; /**< \brief Virt address of register set */
    uint16_t reg_space; /**< \brief Increment between registers - usually 1 */
    uint16_t fifo_size; /**< \brief FIFO depth */
    uint32_t xtal;      /**< \brief UART clock frequency */

    /**
     * \brief BSP function to calculate divisor
     * \param xtal      UART clock frequency
     * \param baudrate  baud rate we want
     */
    uint32_t  (*pfunc_divisor)(uint32_t xtal, uint32_t baudrate);

    /** \brief BSP function to pre initialize the device */
    void      (*pfunc_plfm_init)(void);
    int       rs485_dir_pin;
    int       rs485_tx_level;
};

#define awbldev_get_nschan_param(p_dev) \
        ((struct awbl_ns16550_chan_param *)AWBL_DEVINFO_GET(p_dev))

/*******************************************************************************
    ns16550 driver exports
*******************************************************************************/

/** \brief ns16550 driver functions */
aw_export aw_const struct awbl_drvfuncs g_ns16550_awbl_drvfuncs;

/* NS16550 probe function */
aw_export bool_t ns16550_probe (awbl_dev_t *p_dev);

/* NS16550 SIO methods */
aw_export void ns16550_sio_chan_get     (awbl_dev_t *p_dev, void *p_arg);
aw_export void ns16550_sio_chan_connect (awbl_dev_t *p_dev, void *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AWBL_NS16550_H */
