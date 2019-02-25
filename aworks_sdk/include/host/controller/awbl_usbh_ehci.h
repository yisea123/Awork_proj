/*
 * awbl_usbh_ehci.h
 *
 *  Created on: 2017年5月18日
 *      Author: wengyedong
 */

#ifndef __AWBL_USBH_EHCI_H
#define __AWBL_USBH_EHCI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_pool.h"
#include "aw_timer.h"
#include "host/awbl_usbh.h"


#define AWBL_USBH_EHCI_FRAME_LIST_SIZE  (1024)  /* 1024(4K), 512(2K), 256(1K) */
#define AWBL_USBH_EHCI_TASK_STACK_SIZE  (8192)
#define AWBL_USBH_EHCI_UFRAME_BANDWIDTH (100)   /* 一个微帧的带宽，125*80% us */
#define AWBL_USBH_EHCI_BANDWIDTH_SIZE   (80)    /* 存储微帧带宽的数量，同时也是最小的周期 */
#define AWBL_USBH_EHCI_TUNE_RL_HS       4       /* nak throttle; see 4.9 */
#define AWBL_USBH_EHCI_TUNE_RL_TT        0
#define AWBL_USBH_EHCI_TUNE_MULT_HS     1       /* 1-3 transactions/uframe; 4.10.3 */
#define AWBL_USBH_EHCI_TUNE_MULT_TT     1



/** \brief EHCI controller */
struct awbl_usbh_ehci {
//    struct awbl_usbh          hc;

    struct aw_pool            qhs;
    struct aw_pool            qtds;
    struct aw_pool            itds;
    struct aw_pool            sitds;

    uint8_t                   evt;

    aw_usb_sem_handle_t       sem;
    aw_usb_mutex_handle_t     lock;
    aw_usb_task_handle_t      task;

    uint32_t                  capregs;
    uint32_t                  optregs;

    uint32_t                  hcs;
    bool_t                    ppcd;
    uint8_t                   nports;
    uint32_t                  status;

    struct awbl_usbh_ehci_qh *async;
    uint32_t                 *periodic;
    uint32_t                  fls;
    uint8_t                   bdwidth[AWBL_USBH_EHCI_BANDWIDTH_SIZE];
    int                       random;
    struct aw_list_head       intr_qhs;

    aw_timer_t                guarder;

    /* root hub */
    uint32_t                  psts[15];       /* ports status */

    void (*pfn_rh_change) (struct awbl_usbh_ehci *p_ehci, uint16_t change);
};




/** \brief EHCI QTD */
struct awbl_usbh_ehci_qtd {
    /* for HC */
    uint32_t                hw_next;
    uint32_t                hw_alt_next;
    uint32_t                hw_token;
    uint32_t                hw_buf[5];
    uint32_t                hw_buf_hi[5];

    /* for HCD */
    struct aw_list_head     node;       /* next QTD */
    struct awbl_usbh_trp   *p_trp;      /* TRP */
    size_t                  len;        /* data length */
};




union __ehci_ptr {
    struct awbl_usbh_ehci_qh    *p_qh;        /* Q_TYPE_QH */
    struct awbl_usbh_ehci_itd   *p_itd;       /* Q_TYPE_ITD */
    struct awbl_usbh_ehci_sitd  *p_sitd;      /* Q_TYPE_SITD */
    struct awbl_usbh_ehci_fstn  *p_fstn;      /* Q_TYPE_FSTN */
    void                        *ptr;
};




/** \brief EHCI QH */
struct awbl_usbh_ehci_qh {
    /* for HC */
    uint32_t                    hw_next;
    uint32_t                    hw_info1;
    uint32_t                    hw_info2;
    uint32_t                    hw_cur_qtd;
    uint32_t                    hw_next_qtd;
    uint32_t                    hw_alt_next_qtd;
    uint32_t                    hw_token;
    uint32_t                    hw_buf [5];
    uint32_t                    hw_buf_hi [5];

    /* for HCD */
    union __ehci_ptr            p_next;        /* next QH or others*/
    struct aw_list_head         qtds;          /* QTDs on this QH */
    struct awbl_usbh_ehci_qtd  *dummy;         /* dummy */
    struct awbl_usbh_ehci      *p_ehci;        /* controller */
    uint8_t                     state;         /* state */
    uint8_t                     retry;          /* XactErr retry count */
    bool_t                      unlink;
    /* for interrupt transfer */
    uint16_t                    f_phase;        /* frame index */
    uint8_t                     u_phase;        /* uframe index */
    uint16_t                    f_period;       /* frame period */
    struct aw_list_head         intr_node;
    struct awbl_usbh_endpoint  *p_ep;

};




/** \brief EHCI ITD */
struct awbl_usbh_ehci_itd {
    uint32_t            hw_next;                /* see EHCI 3.3.1 */
    uint32_t            hw_transaction[8];      /* see EHCI 3.3.2 */
    uint32_t            hw_bufp[7];             /* see EHCI 3.3.3 */
    uint32_t            hw_bufp_hi[7];          /* Appendix B */

    union __ehci_ptr    p_next;         /* ptr to periodic q entry */
    struct aw_list_head itds;           /* list of stream's itds */

};





/** \brief EHCI SITD */
struct awbl_usbh_ehci_sitd {
    uint32_t            hw_next;
    uint32_t            hw_fullspeed_ep;    /* EHCI table 3-9 */
    uint32_t            hw_uframe;      /* EHCI table 3-10 */
    uint32_t            hw_results;     /* EHCI table 3-11 */
    uint32_t            hw_buf[2];         /* EHCI table 3-12 */
    uint32_t            hw_backpointer;     /* EHCI table 3-13 */
    uint32_t            hw_buf_hi[2];      /* Appendix B */

    /* the rest is HCD-private */
    union __ehci_ptr    p_next;     /* ptr to periodic q entry */
    struct aw_list_head sitds;      /* list of stream's sitds */

};




/** \brief EHCI FSTN */
struct awbl_usbh_ehci_fstn {
    uint32_t            hw_next;
    union __ehci_ptr    p_next;
};




aw_err_t awbl_usbh_ehci_init (struct awbl_usbh_ehci *p_ehci,
                              uint32_t               reg_base,
                              int                    task_prio,
                              void (*pfn_rh_change) (
                                      struct awbl_usbh_ehci *p_ehci,
                                      uint16_t               change),
                              int                    nqhs,
                              int                    nqtds,
                              int                    nitds,
                              int                    nsitds);

void awbl_usbh_ehci_irq (struct awbl_usbh_ehci *p_ehci);

aw_err_t awbl_usbh_ehci_ep_enable (struct awbl_usbh_ehci     *p_ehci,
                                   struct awbl_usbh_endpoint *p_ep);

aw_err_t awbl_usbh_ehci_ep_disable (struct awbl_usbh_ehci     *p_ehci,
                                    struct awbl_usbh_endpoint *p_ep);

aw_err_t awbl_usbh_ehci_request (struct awbl_usbh_ehci *p_ehci,
                                 struct awbl_usbh_trp  *p_trp);

aw_err_t awbl_usbh_ehci_cancel (struct awbl_usbh_ehci *p_ehci,
                                struct awbl_usbh_trp  *p_trp);

aw_err_t awbl_usbh_ehci_rh_change_check (struct awbl_usbh_ehci *p_ehci,
                                         uint16_t              *p_change);

aw_err_t awbl_usbh_ehci_rh_ctrl (struct awbl_usbh_ehci *p_ehci,
                                 uint8_t                type,
                                 uint8_t                req,
                                 uint16_t               val,
                                 uint16_t               idx,
                                 uint16_t               len,
                                 void                  *p_buf);



#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_USBH_EHCI_H */
