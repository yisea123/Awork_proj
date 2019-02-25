/*
 * awbl_usbh_cfg.c
 *
 *  Created on: 2017Äê5ÔÂ20ÈÕ
 *      Author: wengyedong
 */


#include "aw_task.h"
#include "aw_sem.h"
#include "aw_cache.h"
#include "aw_assert.h"
#include "aw_mem.h"
#include "aw_usb_common.h"
#include "aw_usb_mem.h"
#include "host/awbl_usbh.h"

#include "aw_usb_mem.c"
#include "aw_usb_os.c"

#if (defined(AW_COM_USBH) || \
     defined(AW_COM_USBD) || \
     defined(AW_COM_AWBL_USBH) || \
     defined(AW_COM_AWBL_USBD))
#ifndef AW_CFG_USB_MEM_SIZE
#define AW_CFG_USB_MEM_SIZE (32 * 1024)
#endif

#ifdef AW_COM_USB_MEM_STATIC
aw_local uint32_t __g_usb_mem[(AW_CFG_USB_MEM_SIZE + 3) / 4];
#else
aw_local uint32_t *__g_usb_mem = NULL;
#endif
#endif



void awbl_usb_cfg (void)
{
#if (defined(AW_COM_USBH) || \
     defined(AW_COM_AWBL_USBH))
    aw_err_t ret;
#endif
    
#if (defined(AW_COM_USBH) || \
     defined(AW_COM_USBD) || \
     defined(AW_COM_AWBL_USBH) || \
     defined(AW_COM_AWBL_USBD))

#ifndef AW_COM_USB_MEM_STATIC
    __g_usb_mem = aw_mem_alloc((AW_CFG_USB_MEM_SIZE + 3) / 4);
    aw_assert(__g_usb_mem != NULL);
#endif
    aw_usb_mem_lib_init(__g_usb_mem, (AW_CFG_USB_MEM_SIZE + 3) / 4);
#endif

#if (defined(AW_COM_USBH) || \
     defined(AW_COM_AWBL_USBH))
    ret = awbl_usbh_lib_init();
    aw_assert(ret == AW_OK);
#endif
}




