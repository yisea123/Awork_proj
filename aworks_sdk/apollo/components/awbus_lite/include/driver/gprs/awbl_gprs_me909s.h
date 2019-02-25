/*******************************************************************************
*                                 AWorks
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
 * \brief ME909S GPRSģ������
 *
 * \par ʹ��ʾ��
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.01 17-12-09  vih, redefine the architecture
 * - 1.00 16-10-15  vih, first implementation.
 * \endinternal
 */



#ifndef __AWBL_GPRS_ME909S_H__
#define __AWBL_GPRS_ME909S_H__


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \addtogroup grp_aw_if_gprs_me909s
 * \copydoc awbl_gprs_me909s.h
 * @{
 */

#include "aworks.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */
#include "awbl_gprs.h"
#include "aw_sem.h"
#include "awbus_lite.h"

#define AWBL_GPRS_ME909S_NAME   "HuaWei_me909s"

/** \brief ME909S�豸״̬ */
typedef enum me909s_status {
    AWBL_GPRS_ME909S_RST_ON             = 0x00000001,               /**< \brief ģ��������λ */
//    AWBL_GPRS_ME909S_GPRS_ON            = 0x00000001<<4,            /**< \brief gprs����������ʹ���ڲ�Э��ջ */
    AWBL_GPRS_ME909S_GPRS_PPP_OK        = 0x00000001<<3,            /**< \brief �ڲ�Э��ջ��ppp����  */
    AWBL_GPRS_ME909S_GPRS_PDP_OK        = 0x00000001<<5,            /**< \brief gprs��PDP�������  */
    AWBL_GPRS_ME909S_SIM_OK             = 0x00000001<<6,            /**< \brief SIM������ �����sim���������ź�������ȴ���������ţ���Ƿ�ѣ� */
} awbl_gprs_me909s_status_e;

struct awbl_gprs_me909s_devinfo {

    /** \brief gprs�豸��ΨһID�����ڸ��м���ȡ�豸 */
    int      id;
    char    *buf;
    size_t   buf_size;

    /** \brief gprsģ��Ĳ��� */
    struct awbl_gprs_info       *p_gprs_info;

    /** \brief ���ŵ����ݺ���Ϣ */
    struct aw_gprs_sms_buf      *p_sms_info;
};

/** \brief me909s�豸���ƿ� */
struct awbl_gprs_me909s_dev {
    struct awbl_dev                  dev;              /**< \brief device */
    struct awbl_gprs_dev             gprs;
    const struct awbl_gprs_me909s_devinfo *p_devinfo;
    int                              status;           /**< \brief �豸��״̬ */
    void                            *p_pipe;
    struct ip_addr                   ppp_ipaddr;       /**< \brief ��������� IP��ַ */
    AW_SEMB_DECL(                    lock);            /**< \brief �ź���          */

    uint8_t                          net_mode;
    bool_t                           init_flag;

#define __INTERNAL_SOCKET_NUM        5              /**< \brief ʹ���ڲ�Э��ջʱ��socket����    */
#define __INTERNAL_SOCKET_VAL        {1,2,3,4,5}    /**< \brief ʹ���ڲ�Э��ջʱ��socket��ֵ   */
    uint8_t                          socket[__INTERNAL_SOCKET_NUM];
    uint8_t                          socket_used[__INTERNAL_SOCKET_NUM];
};

void awbl_gprs_me909s_drv_register (void);


/** @}  grp_aw_if_gprs_me909s */

#ifdef __cplusplus
}
#endif /* __cplusplus   */

#endif /* __AWBL_GPRS_ME909S_H__ */

/* end of file */
