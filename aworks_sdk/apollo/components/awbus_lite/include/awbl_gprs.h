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
 * \brief gprs�ӿ�
 *
 * \internal
 * \par modification history:
 * - 1.00 2017-11-29   vih, first implementation.
 * \endinternal
 */

#ifndef __AWBL_GPRS_H
#define __AWBL_GPRS_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \addtogroup grp_awbl_if_gprs
 * \copydoc aw_gprs.h
 * @{
 */

#include "aworks.h"

#include "aw_gprs.h"
#include "aw_sem.h"
#include "ppp/sio_mgn.h"

#define AWBL_GPRS_USE_LWIP_1_4     1
#define AWBL_GPRS_USE_LWIP_2_0     0

#if AWBL_GPRS_USE_LWIP_1_4
#include "ppp/ppp.h"
#endif /* AWBL_GPRS_USE_LWIP_1_4 */

#if AWBL_GPRS_USE_LWIP_2_0
#include "ppp/pppos.h"
#endif /* AWBL_GPRS_USE_LWIP_2_0 */

struct awbl_gprs_dev;

/** \brief GPRSģ��Ĳ�����Ϣ  */
struct awbl_gprs_info
{
    char     *p_dial_num;                   /**< \brief ����ҵ�񲦺ź���   */
    char     *p_apn;                        /**< \brief APN����   */
    char     *p_user;                       /**< \brief APN�û���   */
    char     *p_password;                   /**< \brief APN����   */
    char     *p_center_num;                 /**< \brief ����Ϣ���ĺ���   */
    char     *p_at_err;                     /**< \brief AT �������ʱ���յ����ַ���  */

    /** \brief ���Ž����жϻص�����, �ú�������֪ͨ�û����յ�����Ϣ */
    void    (*pfn_sms_int_cb)(void);

    uint16_t  pwren_gpio;                   /**< \brief poweren gpio */
    uint16_t  pwrkey_gpio;                  /**< \brief power key gpio */
    uint16_t  w_dis_gpio;                   /**< \brief w disable */
    uint16_t  rst_gpio;                     /**< \brief reset gpio */
    uint16_t  ri_gpio;                      /**< \brief ri gpio  */

    ssize_t  (*pfn_at_cmd_send) (struct awbl_gprs_dev *p_this, char *p_buf);
    ssize_t  (*pfn_at_cmd_recv) (struct awbl_gprs_dev *p_this, char *p_buf, size_t buf_size);

};

typedef enum {
    AWBL_GPRS_PPP_PHASE_UNINIT = 0,
    AWBL_GPRS_PPP_PHASE_INIT,
    AWBL_GPRS_PPP_PHASE_DIAL_UP,
    AWBL_GPRS_PPP_PHASE_CREATE,
    AWBL_GPRS_PPP_PHASE_CONNECT,
    AWBL_GPRS_PPP_PHASE_RUNNING,
}awbl_gprs_ppp_phase_t;

struct awbl_gprs_ppp {
    struct sio_mgn               sio_mgn;          /**< \brief sio���� */

#if AWBL_GPRS_USE_LWIP_1_4
    int                          ppp_fd;           /**< \brief PPP��� */
    struct ppp_addrs            *p_pppaddr;        /**< \brief PPP��ȡ���ĵ�ַ  */

    /** \brief ����ppp���ӹرյ��ź��� */
    AW_SEMB_DECL(link_close);
#endif /* AWBL_GPRS_USE_LWIP_1_4 */

    awbl_gprs_ppp_phase_t        phase;

#if AWBL_GPRS_USE_LWIP_2_0
    /** \brief ppp���ƿ�ָ�� */
    ppp_pcb     *p_pcb;

    /** \brief ppp���� */
    struct netif netif;

    /** \brief ����buf,����������ݴ�Ŵ� */
    u_char       rxbuf[PPP_MRU + PPP_HDRLEN];

    /** \brief ����ppp�߳� */
    AW_TASK_DECL(thread, PPP_THREAD_STACKSIZE);

    /** \brief ����ppp�̵߳Ĺر��ź��� */
    AW_SEMB_DECL(thread_close);
#endif /* AWBL_GPRS_USE_LWIP_2_0 */

    /** \brief gprs�豸���Žӿ�  */
    aw_err_t (*pfn_dial_up)   (struct awbl_gprs_dev *p_this);

    /** \brief gprs�豸�رղ��Žӿ�  */
    aw_err_t (*pfn_dial_down) (struct awbl_gprs_dev *p_this);

    /** \brief �û�ppp�ص�  */
    void (*pfn_user_cb)       (void *p_user_arg, bool_t ppp_stat);

    /** \brief �û�ppp�ص�����  */
    void  *p_user_arg;
};

/** \brief GPRS�豸�ķ���ӿ�   */
struct awbl_gprs_service {

    /** \brief GPRSģ�������ӿ� */
    aw_err_t (*pfn_gprs_power_on)(struct awbl_gprs_dev *p_this);

    /** \brief GPRSģ��رսӿ� */
    aw_err_t (*pfn_gprs_power_off)(struct awbl_gprs_dev *p_this);

    aw_err_t (*pfn_gprs_ioctl)(struct awbl_gprs_dev *p_this,
                               aw_gprs_ioctl_req_t   req,
                               void                 *p_arg);

    /** \brief ���ŷ��ͽӿ�    */
    aw_err_t (*pfn_gprs_sms_send)(struct awbl_gprs_dev *p_this,
                                  uint8_t              *p_sms,
                                  uint8_t               len,
                                  char                 *p_num);

    /** \brief HEX���ŷ��ͽӿ�    */
    aw_err_t (*pfn_gprs_sms_hex_send)(struct awbl_gprs_dev *p_this,
                                      uint8_t              *p_sms,
                                      uint8_t               len,
                                      char                 *p_num);

    /** \brief ���Ž��սӿ�   */
    aw_err_t (*pfn_gprs_sms_recv)(struct awbl_gprs_dev      *p_this,
                                  struct aw_gprs_sms_buf    *p_sms,
                                  uint32_t                   timeout);

    /** \brief ɾ��ȫ������     */
    aw_err_t (*pfn_gprs_all_sms_del)(struct awbl_gprs_dev *p_this);


    /** \brief ����GPRS����  */
    int (*pfn_gprs_start)(struct awbl_gprs_dev *p_this,
                          uint8_t               mode,
                          char                 *p_ip,
                          uint16_t              port,
                          uint32_t              timeout);

    /** \brief �ر�GPRS����  */
    aw_err_t (*pfn_gprs_close)(struct awbl_gprs_dev *p_this, int   hd);

    /** \brief ����GPRS����  */
    ssize_t (*pfn_gprs_send)(struct awbl_gprs_dev *p_this,
                             int                   hd,
                             void                 *p_data,
                             size_t                len,
                             uint32_t              timeout);

    /** \brief ����GPRS����   */
    ssize_t (*pfn_gprs_recv)(struct awbl_gprs_dev *p_this,
                             int                   hd,
                             void                 *p_buf,
                             size_t                len);
};


/** \brief GPRS�豸�ṹ��   */
struct awbl_gprs_dev {

    struct awbl_gprs_dev        *p_next;

    /** \brief GPRS�豸�ķ���ӿ�   */
    aw_const struct awbl_gprs_service    *p_serv;

    /** \brief gprsģ��Ĳ��� */
    struct awbl_gprs_info       *p_info;

    /** \brief ���ŵ����ݺ���Ϣ */
    struct aw_gprs_sms_buf      *p_sms;

    struct awbl_gprs_ppp         ppp;

    /** \brief gprs�豸��ΨһID�����ڸ��м���ȡ�豸 */
    int                          dev_id;

    /** \brief gprs��׼�ӿ�ʹ�õĻ����� */
    AW_MUTEX_DECL(               mutex);

    bool_t                       mutex_inited;

    /** \brief �²���gprs�豸��ָ��  */
    void                        *p_gprs_dev;

    /** \brief socktet���ӵ����� */
    uint8_t                      socket_num;

    /** \brief �Ƿ�ʹ���ⲿЭ��ջ��־ */
    bool_t                       use_external_protocol;

    /** \brief �Ƿ��Ѿ���ʼ�� */
    bool_t                       already_init;

    /** \brief �Ѿ��ϵ��־ */
    bool_t                       power_on;
};

/**
 * \brief ��ppp��sio_mgn��ͨ����Դ�ĳ�ʼ��
 *
 * \param[in]  p_gprs         gprs�豸ָ��
 *
 * \return  ��
 */
aw_err_t awbl_gprs_init_tail (struct awbl_gprs_dev *p_gprs);

/**
 * \brief ���� AT ����
 *
 * \param[in]  p_this         gprs�豸ָ��
 * \param[in]  p_str          ���͵�AT����
 *
 * \return  ��
 */
void awbl_gprs_at_send (struct awbl_gprs_dev  *p_this, char *p_str);


/**
 * \brief ָ������ AT ����صĽ��
 *
 * \param[in]  this           gprs�豸ָ��
 * \param[in]  p_buf          �������ݵĻ���buf
 * \param[in]  buf_size       �����С
 * \param[in]  p_cond         ָ�����ص��ַ�������
 * \param[in]  arg_num        �ж����ֿ��ܵķ������ݣ�ָ��ָ���������м���Ԫ�أ�
 * \param[in]  wait_ms        ���ĵȴ�ʱ�䣬��λS��Ϊ0�򲻵ȴ�
 *
 * \retval   >= 0              : ���յ���p_arg������ݣ����Է���ֵ��Ϊ�±���Ǹ�����
 * \retval   -AW_ETIMEDOUT 0   : ���յ���p_arg������ݣ����Է���ֵ��Ϊ�±���Ǹ�����
 * \retval   -AW_ENOMSG 0      : ���յ���p_arg������ݣ����Է���ֵ��Ϊ�±���Ǹ�����
 */
int awbl_gprs_at_recv (struct awbl_gprs_dev     *p_this,
                       char                     *p_buf,
                       uint32_t                  buf_size,
                       char                     *p_cond[],
                       uint32_t                  arg_num,
                       uint32_t                  wait_ms);

/**
 * \brief �����ݴ����PDU��protocol data unit����
 *
 * \param[in]  message   ��Ŵ�������ݵ�buf
 * \param[in]  msg_size  buf��С
 * \param[in]  p_sca     ����Ϣ�������ĵ�ַ
 * \param[in]  p_sms     ��������
 * \param[in]  len       ���ų���
 * \param[in]  p_num     ���շ�����
 * \param[in]  is_en     �Ƿ���Ӣ�Ķ���
 * \param[in]  is_hex    ���������Ƿ���hex����
 *
 * \retval AW_OK        :  �ɹ�
 */
aw_err_t awbl_gprs_pdu_pack (char     *message,
                             size_t    msg_size,
                             char     *p_sca,
                             uint8_t  *p_sms,
                             uint8_t   len,
                             char     *p_num,
                             bool_t    is_en,
                             bool_t    is_hex);

/**
 * \brief ����PDU��protocol data unit����
 *
 * \param[in]  p_pdu_data     pdu����
 * \param[in]  p_to_sms       ��Ž��͵���pdu���ݵĽṹ��
 *
 * \retval AW_OK        :  �ɹ�
 * \retval -AW_EBADMSG  :  ������ȷ�����ݰ�
 */
aw_err_t awbl_gprs_pdu_unpack (char                   *p_pdu_data,
                               struct aw_gprs_sms_buf *p_to_sms);

void awbl_gprs_init (void);

/** @}  grp_awbl_if_gprs */

#ifdef __cplusplus
}
#endif /* __cplusplus   */

#endif /* __AWBL_GPRS_H */

/* end of file */
