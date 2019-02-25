/*******************************************************************************
*                                 Apollo
*                       ---------------------------
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
 * \brief configuration file for serial devices, internal use only
 *
 * This file can't be compiled into the library, but link it when build image.
 *
 * \internal
 * \par modification history:
 * - 1.00 12-10-31  orz, first implementation
 * - 1.00 15-06-20  deo, modify buffer define¡¢init, add COM alloc¡¢free¡¢register
 * 					and remove interface.
 * \endinternal
 */

/*******************************************************************************
  headers
*******************************************************************************/

//#include "awbl_serial_usrcfg.h"

#if AW_CFG_NUM_COM > 0

#include "driver/serial/awbl_serial_private.h"

/*******************************************************************************
    local defines
*******************************************************************************/
#define __COM_TX_BUF_SIZE(num)  (AW_CFG_COM ##num ##_TX_BUF_SIZE + 1)
#define __COM_RX_BUF_SIZE(num)  (AW_CFG_COM ##num ##_RX_BUF_SIZE + 1)
#define __COM_BUF_SIZE(n)       (__COM_RX_BUF_SIZE(n) + __COM_TX_BUF_SIZE(n))
#define __COM_BUF_INFO(n)       {__COM_RX_BUF_SIZE(n), __COM_TX_BUF_SIZE(n), FALSE}
#define __G_COM_BUF_DEF(num)	static char __g_com##num##_buf[__COM_BUF_SIZE(num)]
#define __G_COM_BUF(num)		__g_com##num##_buf

/*******************************************************************************
    local types
*******************************************************************************/
struct __com_buf_info {
    unsigned short rx_size;
    unsigned short tx_size;
    bool_t used;
};

/*******************************************************************************
    import external functions
*******************************************************************************/
extern void aw_serial_init2 (void);

extern int aw_serdev_init (int   com,
                           char *p_rdbuf,
                           int   rd_buf_size,
                           char *p_wrbuf,
                           int   wr_buf_size);

extern int aw_serdev_remove (int com);

aw_err_t aw_serial_register_com (int com);
aw_err_t aw_serial_remove_com (int com);
int aw_serial_com_alloc (void);
void aw_serial_com_free (int com);

/*******************************************************************************
    globals used for serial driver
*******************************************************************************/
struct aw_serial g_serial_devices[AW_CFG_NUM_COM];
const int        g_num_serial_devices = AW_NELEMENTS(g_serial_devices);
/*******************************************************************************
    local variables
*******************************************************************************/
aw_spinlock_isr_t __g_serial_lock;

#if AW_CFG_NUM_COM > 0
__G_COM_BUF_DEF(0);
#endif
#if AW_CFG_NUM_COM > 1
__G_COM_BUF_DEF(1);
#endif
#if AW_CFG_NUM_COM > 2
__G_COM_BUF_DEF(2);
#endif
#if AW_CFG_NUM_COM > 3
__G_COM_BUF_DEF(3);
#endif
#if AW_CFG_NUM_COM > 4
__G_COM_BUF_DEF(4);
#endif
#if AW_CFG_NUM_COM > 5
__G_COM_BUF_DEF(5);
#endif
#if AW_CFG_NUM_COM > 6
__G_COM_BUF_DEF(6);
#endif
#if AW_CFG_NUM_COM > 7
__G_COM_BUF_DEF(7);
#endif
#if AW_CFG_NUM_COM > 8
__G_COM_BUF_DEF(8);
#endif
#if AW_CFG_NUM_COM > 9
__G_COM_BUF_DEF(9);
#endif

static char *__g_com_buf[] = {
#if AW_CFG_NUM_COM > 0
__G_COM_BUF(0),
#endif
#if AW_CFG_NUM_COM > 1
__G_COM_BUF(1),
#endif
#if AW_CFG_NUM_COM > 2
__G_COM_BUF(2),
#endif
#if AW_CFG_NUM_COM > 3
__G_COM_BUF(3),
#endif
#if AW_CFG_NUM_COM > 4
__G_COM_BUF(4),
#endif
#if AW_CFG_NUM_COM > 5
__G_COM_BUF(5),
#endif
#if AW_CFG_NUM_COM > 6
__G_COM_BUF(6),
#endif
#if AW_CFG_NUM_COM > 7
__G_COM_BUF(7),
#endif
#if AW_CFG_NUM_COM > 8
__G_COM_BUF(8),
#endif
#if AW_CFG_NUM_COM > 9
__G_COM_BUF(9),
#endif
};

/* the serial port buffer informations */
static struct __com_buf_info __g_com_buf_info[] = {
    __COM_BUF_INFO(0)
#if AW_CFG_NUM_COM > 1
    , __COM_BUF_INFO(1)
#endif
#if AW_CFG_NUM_COM > 2
    , __COM_BUF_INFO(2)
#endif
#if AW_CFG_NUM_COM > 3
    , __COM_BUF_INFO(3)
#endif
#if AW_CFG_NUM_COM > 4
    , __COM_BUF_INFO(4)
#endif
#if AW_CFG_NUM_COM > 5
    , __COM_BUF_INFO(5)
#endif
#if AW_CFG_NUM_COM > 6
    , __COM_BUF_INFO(6)
#endif
#if AW_CFG_NUM_COM > 7
    , __COM_BUF_INFO(7)
#endif
#if AW_CFG_NUM_COM > 8
    , __COM_BUF_INFO(8)
#endif
#if AW_CFG_NUM_COM > 9
    , __COM_BUF_INFO(9)
#endif
};

#endif /* AW_CFG_NUM_COM > 0 */

/******************************************************************************/
void aw_serial_init (void)
{
#if AW_CFG_NUM_COM > 0
    int   i;

    aw_spinlock_isr_init(&__g_serial_lock, 0);

    aw_serial_init2();

    for (i = 0; i < AW_CFG_NUM_COM; i++) {
    	if (__g_com_buf_info[i].used == TRUE) {
    		continue;
    	}
    	aw_spinlock_isr_take(&__g_serial_lock);
    	__g_com_buf_info[i].used = TRUE;
    	aw_spinlock_isr_give(&__g_serial_lock);

    	if (AW_OK != aw_serial_register_com(i)) {
        	aw_spinlock_isr_take(&__g_serial_lock);
        	__g_com_buf_info[i].used = FALSE;
        	aw_spinlock_isr_give(&__g_serial_lock);
    	}
    }

#endif /* AW_CFG_NUM_COM > 0 */
}

int aw_serial_com_alloc (void)
{
	int i;
	aw_spinlock_isr_take(&__g_serial_lock);

	for (i=0; i<AW_CFG_NUM_COM; ++i) {
		if (__g_com_buf_info[i].used == FALSE) {
			__g_com_buf_info[i].used = TRUE;
			goto _exit;
		}
	}
	i = -ENOSPC;
_exit:
	aw_spinlock_isr_give(&__g_serial_lock);
	return i;
}
void aw_serial_com_free (int com)
{
	if (com >= AW_CFG_NUM_COM) {
		return;
	}
	aw_spinlock_isr_take(&__g_serial_lock);
	__g_com_buf_info[com].used = FALSE;
	aw_spinlock_isr_give(&__g_serial_lock);
}

aw_err_t aw_serial_register_com (int com)
{
	aw_err_t err = AW_OK;
#if AW_CFG_NUM_COM > 0
	if (com >= AW_CFG_NUM_COM) {
		return -EINVAL;
	}

    err = aw_serdev_init(com,
					   __g_com_buf[com],
					   __g_com_buf_info[com].rx_size,
					   __g_com_buf[com] + __g_com_buf_info[com].rx_size,
					   __g_com_buf_info[com].tx_size);

#endif /* AW_CFG_NUM_COM > 0 */
	return err;
}

aw_err_t aw_serial_remove_com (int com)
{
	aw_err_t err = AW_OK;
#if AW_CFG_NUM_COM > 0
	if (com >= AW_CFG_NUM_COM) {
		return -EINVAL;
	}

	err = aw_serdev_remove(com);

#endif /* AW_CFG_NUM_COM > 0 */
	return err;
}


/* end of file */
