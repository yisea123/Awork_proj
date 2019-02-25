/*
 * awbl_usbh.h
 *
 *  Created on: 2017Äê5ÔÂ17ÈÕ
 *      Author: wengyedong
 */

#ifndef __AWBL_USBH_H
#define __AWBL_USBH_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "aw_refcnt.h"
#include "aw_list.h"
#include "aw_delayed_work.h"
#include "aw_usb_common.h"
#include "aw_usb_os.h"



#define __AWBL_USBH_DECL(p_hc, p_awdev) \
    struct awbl_usbh *p_hc = \
        (struct awbl_usbh *)AW_CONTAINER_OF( \
            p_awdev, struct awbl_usbh, super)

#define __AWBL_USBH_INFO_DECL(p_info, p_awdev) \
    struct awbl_usbh_info *p_info = \
        (struct awbl_usbh_info *)AWBL_DEVINFO_GET(p_awdev)

#define __AWBL_USBH_FUN_DECL(p_fun, p_awdev) \
    struct awbl_usbh_function *p_fun = \
        (struct awbl_usbh_function *)AW_CONTAINER_OF( \
            p_awdev, struct awbl_usbh_function, awdev)

#define __AWBL_USBH_FUN_DRV(p_drv, p_awdrv) \
    struct awbl_usbh_fundrv_info *p_drv = \
        (struct awbl_usbh_fundrv_info *)AW_CONTAINER_OF( \
            p_awdrv, struct awbl_usbh_fundrv_info, awdrv)



#define AWBL_USBH_ROOT_HUB_NUM     2
#define AWBL_USBH_HUB_MAX_PORTS    15  /* must less than 16 */
//#define AWBL_USBH_MAX_INTERFACES   32
#define AWBL_USBH_MAX_CONFIG       5
#define AWBL_USBH_MAX_EP_NUM       32



#define AWBL_USBH_TRP_SHORT_NOT_OK  0x00000001    /* Short packets are errors */
#define AWBL_USBH_TRP_ISO_ASAP      0x00000002    /* Start ISO transfer at the earliest */
#define AWBL_USBH_TRP_ZERO_PACKET   0x00000004    /* End OUT transfer with short packet */
#define AWBL_USBH_TRP_NO_INTERRUPT  0x00000008    /* no interrupt needed,except for error */



#define AWBL_USBH_FUNDRV_INFO_END  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}




struct awbl_usbh_hub;
struct awbl_usbh;
struct awbl_usbh_config;
struct awbl_usbh_interface;
struct awbl_usbh_device;
struct awbl_usbh_endpoint;
struct awbl_usbh_function;





/** \brief USB host transfer request packet */
struct awbl_usbh_trp {
    struct awbl_usbh_endpoint       *p_ep;
    struct aw_usb_ctrlreq           *p_ctrl;
    void                            *p_data;
    size_t                           len;
    void                            *p_ctrl_dma;
    void                            *p_data_dma;
    void                           (*pfn_done) (void *p_arg);
    void                            *p_arg;
    size_t                           act_len;
    int                              status;
    int                              flag;
    void                            *priv;  /* for host driver */
};




/** \brief USB hub */
struct awbl_usbh_hub {
    struct awbl_usbh_function   *p_fun;
    struct aw_list_head          evt;
    struct aw_list_head          node;
    struct awbl_usbh_trp         trp;
    struct awbl_usbh_device     *ports[AWBL_USBH_HUB_MAX_PORTS];
    uint32_t                    *p_sta;
    uint8_t                      err_cnt;
    uint8_t                      nports;
    uint8_t                      pwrtim;
};






/** \brief USB host driver */
struct awbl_usbh_drv {
    /* request transfer */
    aw_err_t (*pfn_request) (struct awbl_usbh     *p_hc,
                             struct awbl_usbh_trp *p_trp);

    /* cancel transfers */
    aw_err_t (*pfn_cancel) (struct awbl_usbh     *p_hc,
                            struct awbl_usbh_trp *p_trp);

    /* enable EP */
    aw_err_t (*pfn_ep_en) (struct awbl_usbh          *p_hc,
                           struct awbl_usbh_endpoint *p_ep);

    /* disable EP */
    aw_err_t (*pfn_ep_dis) (struct awbl_usbh          *p_hc,
                            struct awbl_usbh_endpoint *p_ep);

    /* get root hub status */
    aw_err_t (*pfn_rh_check) (struct awbl_usbh *p_hc,
                              uint16_t         *p_change);

    /* root hub control */
    aw_err_t (*pfn_rh_ctrl) (struct awbl_usbh        *p_hc,
                             uint8_t                  type,
                             uint8_t                  req,
                             uint16_t                 val,
                             uint16_t                 idx,
                             uint16_t                 len,
                             void                    *p_data);
};




/** \brief USB host */
struct awbl_usbh {
    struct awbl_busctlr         super;
    aw_usb_mutex_handle_t       lock;
    uint32_t                    map[4];
    struct awbl_usbh_hub        rh;
    struct aw_delayed_work      rh_work;
    const struct awbl_usbh_drv *p_drv;
    struct awbl_usbh           *p_next;
};




/** \brief USB host information */
struct awbl_usbh_info {
    uint8_t     bus_index;
};




/** \brief USB host EndPoint */
struct awbl_usbh_endpoint {
    struct awbl_usbh_device     *p_udev;
    struct aw_usb_endpoint_desc *p_desc;
    bool_t                       enabled;
    int                          bandwidth;
    struct aw_list_head          node;
    aw_usb_sem_handle_t          sem;
    void                        *priv;
};




struct awbl_usbh_config {
    struct aw_usb_config_desc       *p_desc;
    char                            *string;
    struct awbl_usbh_function       *funs;
    int                              nfuns;
};






/** \brief USB device */
struct awbl_usbh_device {
    struct awbl_usbh               *p_hc;
    char                            name[32];
    struct aw_refcnt                ref;
    aw_usb_mutex_handle_t           lock;
    struct aw_list_head             node;
    uint8_t                         addr;
    uint8_t                         speed;
    struct awbl_usbh_hub           *p_hub;
    uint8_t                         port;
    uint8_t                         status;
#define AWBL_USBH_DEV_STA_CONN      0x01
#define AWBL_USBH_DEV_STA_INJECT    0x02
#define AWBL_USBH_DEV_STA_CFG       0x04

#define AWBL_USBH_DEV_CONN(p_dev) \
            ((p_dev)->status & AWBL_USBH_DEV_STA_CONN)
#define AWBL_USBH_DEV_INJECT(p_dev) \
            ((p_dev)->status & AWBL_USBH_DEV_STA_INJECT)
#define AWBL_USBH_DEV_CFG(p_dev) \
            ((p_dev)->status & AWBL_USBH_DEV_STA_CFG)
#define AWBL_USBH_DEV_VALID(p_dev) \
            ((p_dev)->status == (AWBL_USBH_DEV_STA_CONN | \
                                 AWBL_USBH_DEV_STA_CFG | \
                                 AWBL_USBH_DEV_STA_INJECT))
    struct aw_usb_ctrlreq          *p_ctrl;
    struct aw_usb_device_desc      *p_desc;
    char                           *p_str_mft;
    char                           *p_str_pdt;
    char                           *p_str_snum;
    struct awbl_usbh_config         cfg;
    struct awbl_usbh_endpoint       ep0;
    struct aw_usb_endpoint_desc     ep0_desc;
    struct awbl_usbh_endpoint      *ep_in[16];
    struct awbl_usbh_endpoint      *ep_out[16];
    uint16_t                        langid;
};




/** \brief USB Function */
struct awbl_usbh_function {
    struct awbl_dev                      awdev;
    struct awbl_devhcf                   devhcf;
    char                                 name[16];
    struct awbl_usbh_device             *p_udev;
    struct aw_list_head                  node;

    uint8_t                              ifirst;
    uint8_t                              nitfs;
    uint8_t                              clss;
    uint8_t                              sclss;
    uint8_t                              proto;

    struct aw_list_head                  itfs;
    void                                *prive; /* for driver */
};




/** \brief USB interface device */
struct awbl_usbh_interface {
    struct aw_list_head              node;
    struct aw_usb_interface_desc    *p_desc;
    struct awbl_usbh_endpoint       *eps;
};




struct awbl_usbh_fundrv_info_tab {
    uint16_t                    flags;
#define AWBL_USBH_FUNDRV_MATCH_VENDOR          0x0001
#define AWBL_USBH_FUNDRV_MATCH_PRODUCT         0x0002
#define AWBL_USBH_FUNDRV_MATCH_DEV_CLASS       0x0010
#define AWBL_USBH_FUNDRV_MATCH_DEV_SUBCLASS    0x0020
#define AWBL_USBH_FUNDRV_MATCH_DEV_PROTOCOL    0x0040
#define AWBL_USBH_FUNDRV_MATCH_FUN_CLASS       0x0080
#define AWBL_USBH_FUNDRV_MATCH_FUN_SUBCLASS    0x0100
#define AWBL_USBH_FUNDRV_MATCH_FUN_PROTOCOL    0x0200
#define AWBL_USBH_FUNDRV_MATCH_FUN_NUMBER      0x0400
    uint16_t                    vid;
    uint16_t                    pid;

    uint8_t                     dclss;
    uint8_t                     dsclss;
    uint8_t                     dproto;

    uint8_t                     iclss;
    uint8_t                     isclss;
    uint8_t                     iproto;
    uint8_t                     inum;
};




/** \brief USB device driver info */
struct awbl_usbh_fundrv_info {
    struct awbl_drvinfo                     awdrv;
    const struct awbl_usbh_fundrv_info_tab *p_tab;
};




#define AWBL_USBH_EP_TYPE(p_ep)   ((p_ep)->p_desc->bmAttributes & 0x03)
#define AWBL_USBH_EP_DIR(p_ep)    ((p_ep)->p_desc->bEndpointAddress & 0x80)
#define AWBL_USBH_EP_NUM(p_ep)    ((p_ep)->p_desc->bEndpointAddress & 0x0F)
#define AWBL_USBH_EP_MPS(p_ep)    (AW_USB_CPU_TO_LE16((p_ep)->p_desc->wMaxPacketSize))
#define AWBL_USBH_EP_INTVAL(p_ep) ((p_ep)->p_desc->bInterval)

#define AWBL_USBH_DEV_VID(p_udev)           (AW_USB_CPU_TO_LE16((p_udev)->p_desc->idVendor))
#define AWBL_USBH_DEV_PID(p_udev)           (AW_USB_CPU_TO_LE16((p_udev)->p_desc->idProduct))
#define AWBL_USBH_DEV_CLASS(p_udev)         ((p_udev)->p_desc->bDeviceClass)
#define AWBL_USBH_DEV_SUB_CLASS(p_udev)     ((p_udev)->p_desc->bDeviceSubClass)
#define AWBL_USBH_DEV_PROTOCOL(p_udev)      ((p_udev)->p_desc->bDeviceProtocol)
#define AWBL_USBH_DEV_NCFGS(p_udev)         ((p_udev)->p_desc->bNumConfigurations)

/**
 * \brief USB host bus function
 */

/** \brief USB host bus initialize */
void awbl_usbh_bus_init (void);

/** \brief USB host resource initialize */
aw_err_t awbl_usbh_lib_init (void);




/**
 * \brief USB host API for host driver
 */
/** \brief create a USB host */
aw_err_t awbl_usbh_host_create (struct awbl_usbh           *p_hc,
                                uint8_t                     nports,
                                const struct awbl_usbh_drv *p_drv);

/** \brief root hub status change */
void awbl_usbh_host_rh_change (struct awbl_usbh *p_hc, uint16_t change);

/** \brief finish */
void awbl_usbh_host_trp_done (struct awbl_usbh_trp *p_trp, int status);




/**
 * \brief USB device API for all driver
 */
/** \brief reference a USB device */
aw_err_t awbl_usbh_dev_get (struct awbl_usbh_device *p_udev);

/** \brief put a USB device */
aw_err_t awbl_usbh_dev_put (struct awbl_usbh_device *p_udev);

/** \brief check if device connect */
bool_t awbl_usbh_dev_is_connect (struct awbl_usbh_device *p_udev);

/** \brief reset a USBH EndPoint */
aw_err_t awbl_usbh_ep_reset (struct awbl_usbh_endpoint *p_ep);

/** \brief clean EndPoint halt */
aw_err_t awbl_usbh_ep_halt_clr (struct awbl_usbh_endpoint *p_ep);

/** \brief submit a TRP */
aw_err_t awbl_usbh_trp_submit (struct awbl_usbh_trp *p_trp);

/** \brief cancel a TRP */
aw_err_t awbl_usbh_trp_cancel (struct awbl_usbh_trp *p_trp);

/** \brief submit a TRP and wait for it */
aw_err_t awbl_usbh_trp_sync (struct awbl_usbh_endpoint *p_ep,
                             struct aw_usb_ctrlreq     *p_ctrl,
                             void                      *p_data,
                             int                        len,
                             int                        timeout,
                             int                        flag);

/** \brief submit a control TRP and wait for it */
aw_err_t awbl_usbh_ctrl_sync (struct awbl_usbh_endpoint *p_ep,
                              uint8_t                    type,
                              uint8_t                    req,
                              uint16_t                   val,
                              uint16_t                   idx,
                              uint16_t                   len,
                              void                      *p_data,
                              int                        timeout,
                              int                        flag);

/** \brief get descriptor from device */
aw_err_t awbl_usbh_desc_get (struct awbl_usbh_device *p_dev,
                             uint16_t                 type,
                             uint16_t                 value,
                             uint16_t                 index,
                             uint16_t                 len,
                             void                    *p_buf);

/** \brief set device address */
aw_err_t awbl_usbh_addr_set (struct awbl_usbh_device *p_dev);

/** \brief get string */
char *awbl_usbh_string_get (struct awbl_usbh_device *p_udev,
                            uint8_t                  index);

/** \brief set a new config for device */
aw_err_t awbl_usbh_dev_cfg_set (struct awbl_usbh_device *p_dev,
                                uint8_t                  val);




/**
 * \brief USB host hub driver
 */
/** \brief USB host hub driver register */
void awbl_usbh_hub_drv_register (void);





aw_usb_task_handle_t aw_usb_task_create (const char  *name,
                                         int          prio,
                                         size_t       stk_s,
                                         void       (*pfnc) (void *p_arg),
                                         void        *p_arg);

aw_err_t aw_usb_task_delete (aw_usb_task_handle_t tsk);

aw_err_t aw_usb_task_startup (aw_usb_task_handle_t tsk);

aw_usb_sem_handle_t aw_usb_sem_create (void);

void aw_usb_sem_delete (aw_usb_sem_handle_t sem);

aw_err_t aw_usb_sem_take (aw_usb_sem_handle_t sem,
                          int                 timeout);

aw_err_t aw_usb_sem_give (aw_usb_sem_handle_t sem);

aw_usb_mutex_handle_t aw_usb_mutex_create (void);

void aw_usb_mutex_delete (aw_usb_mutex_handle_t mutex);

aw_err_t aw_usb_mutex_lock (aw_usb_mutex_handle_t mutex,
                            int                   timeout);

aw_err_t aw_usb_mutex_unlock (aw_usb_mutex_handle_t mutex);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_H */
