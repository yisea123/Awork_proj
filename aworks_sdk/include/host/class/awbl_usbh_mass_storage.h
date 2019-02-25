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
 * \brief USB host mass storage class
 *
 * \internal
 * \par modification history:
 * - 1.00 17-08-01  deo, first implementation
 * \endinternal
 */
#ifndef __AWBL_USBH_MASS_STORAGE_H
#define __AWBL_USBH_MASS_STORAGE_H



#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_delayed_work.h"
#include "fs/aw_blk_dev.h"
#include "host/awbl_usbh.h"
#include "aw_usb_os.h"




#define AWBL_USBH_MS_SC_RBC               0x01    /* flash devices.            */
#define AWBL_USBH_MS_SC_8020              0x02    /* CD's DVD's.               */
#define AWBL_USBH_MS_SC_QIC               0x03    /* Tapes.                    */
#define AWBL_USBH_MS_SC_UFI               0x04    /* Floppy.                   */
#define AWBL_USBH_MS_SC_8070              0x05    /* Floppies(mostly).         */
#define AWBL_USBH_MS_SC_SCSI              0x06    /* SCSI devices.             */
#define AWBL_USBH_MS_SC_RAMD              0x13    /* Ram disk device.          */


/** \brief MS logic unit */
struct awbl_usbh_ms_lun {
    struct awbl_usbh_mass_storage   *p_ms;
    struct aw_blk_dev                bd;
    char                             name[32];
    uint8_t                          lun;
    uint32_t                         nblks;
    uint32_t                         bsize;
    bool_t                           wp;
    struct aw_delayed_work           work;
    void                            *p_buf;
};





struct awbl_usbh_ms_sclass {
    uint8_t    id;


    aw_err_t (*pfn_init) (struct awbl_usbh_ms_lun *p_lun);

    aw_err_t (*pfn_read) (struct awbl_usbh_ms_lun *p_lun,
                          uint_t                   blk,
                          uint_t                   nblks,
                          void                    *p_buf);

    aw_err_t (*pfn_write) (struct awbl_usbh_ms_lun *p_lun,
                           uint_t                   blk,
                           uint_t                   nblks,
                           void                    *p_data);

};




/** \brief USB host MS device */
struct awbl_usbh_mass_storage {
    struct awbl_usbh_function   *p_fun;
    aw_usb_mutex_handle_t        lock;
    struct awbl_usbh_endpoint   *p_in;
    struct awbl_usbh_endpoint   *p_out;
    struct awbl_usbh_endpoint   *p_intr;

    struct awbl_usbh_ms_sclass  *p_sclass;

    int                          id;
    uint8_t                      nluns;
    struct aw_refcnt             ref;
    uint8_t                      pro;
    uint32_t                     tag;
    struct awbl_usbh_ms_lun     *luns;
    bool_t                       removed;
    void                        *p_cbw;
    void                        *p_csw;
};


void awbl_usbh_mass_storage_drv_register (int buffer_size);



#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_MASS_STORAGE_H */
