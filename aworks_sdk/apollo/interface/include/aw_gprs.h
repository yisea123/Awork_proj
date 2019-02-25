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
 * \brief ͨ��GPRS����
 *
 * \par ʹ��ʾ��
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.04 17-12-09  vih, redefine the architecture
 * - 1.03 15-03-06  ops, add sms if and aw_gprs_sms_data.
 * - 1.02 15-01-23  ops, add signal strength if.
 * - 1.01 15-01-09  ops, create the gprs abstract class, and redefine the std if.
 * - 1.00 14-12-15  afm, first implementation.
 * \endinternal
 */

#ifndef __AW_GPRS_H_
#define __AW_GPRS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_gprs
 * \copydoc aw_gprs.h
 * @{
 */

#include "aworks.h"
#include "aw_types.h"

//#include "arpa/inet.h"

/**
 * \brief IO���Ƶ�ѡ��
 */
typedef enum aw_gprs_ioctl_req {

    /** \brief ����ʹ�õ�Э��ջ����Ϊ0��Ϊ�ⲿЭ��ջ��Ĭ�ϣ���Ϊ1��ʹ���ڲ�Э��ջ   */
    AW_GPRS_REQ_PROTOCOL_SET,

    /**
     * \brief  PPP���ţ�ֻ����ʹ���ⲿЭ��ʱ���ܽ��и�ppp���ţ�
     * ���ͨ��ioctl��ppp���������Ӧ�ò����socket�Ľӿڽ������Ӻ�ͨ�ţ�
     * ��ʱ���ٵ��� aw_gprs_ip_start ��aw_gprs_ip_send��aw_gprs_ip_receive
     * �� aw_gprs_ip_close �ӿڣ�
     */
    AW_GPRS_REQ_PPP_OPEN,

    /** \brief PPP���Źر�    */
    AW_GPRS_REQ_PPP_CLOSE,

    /** \brief �豸��λ��������0��Ϊ�����λ����1��ΪӲ����λ    */
    AW_GPRS_REQ_RESET,

    /** \brief GPRSģ���ź�ǿ�Ȼ�ȡ   */
    AW_GPRS_REQ_CSQ_GET,

    /** \brief ��ȡGPRSģ��CCID   */
    AW_GPRS_REQ_CCID_GET,

    /** \brief ��ȡGPRS����״̬  */
    AW_GPRS_REQ_IP_STS_GET,

    /** \brief ��ȡ������Ӫ��  */
    AW_GPRS_REQ_APN_GET,

    /** \brief PPP���ŵ�IP��ַ��ȡ    */
    AW_GPRS_REQ_PPPIF_IP_GET,

    /** \brief ��ȡGPRSģ��İ汾��      */
    AW_GPRS_REQ_VERSION_GET,

    /** \brief ��ȡGPRSģ���IMEI��   */
    AW_GPRS_REQ_IMEI_GET,

    /** \brief ��ȡGPRSģ���IMSI��    */
    AW_GPRS_REQ_IMSI_GET,

    /** \brief ��ȡGPRSģ��Ķ���Ϣ���ĺ���   */
    AW_GPRS_REQ_SCA_GET,

    /** \brief ��ȡ����ģʽ   */
    AW_GPRS_REQ_NET_MODE_GET,

    /** \brief ��ȡ��վ��Ϣ   */
    AW_GPRS_REQ_BS_GET,

    /** \brief ����AT����   */
    AW_GPRS_REQ_AT_SEND,

    /** \brief ����AT����ķ��ؽ��   */
    AW_GPRS_REQ_AT_RECV,

    /** \brief ping����   */
    AW_GPRS_REQ_PING,

} aw_gprs_ioctl_req_t;



struct aw_gprs_sms_buf {
    char     *p_sms_buff;                   /**< \brief �������ݻ���   */
    uint16_t  sms_buff_len;                 /**< \brief �������ݻ��泤��   */

    char     *p_num_buff;                   /**< \brief �ֻ��������ݻ���   */
    uint16_t  num_buff_len;                 /**< \brief �ֻ��������ݻ��泤��   */

    char     *p_time_buff;                  /**< \brief ʱ�����ݻ���   */
    uint16_t  time_buff_len;                /**< \brief ʱ�����ݻ��泤��   */

/** \brief ���յĶ��ű�������  */
#define AW_GPRS_SMS_CODE_GB          (0)     /**< \brief GB�������   */
#define AW_GPRS_SMS_CODE_HEX         (1)     /**< \brief HEX�������  */
    uint8_t   sms_code;                     /**< \brief ���ű���   */
};

/**
 * \brief gprs�豸�ϵ粢��ʼ��
 *
 * \param[in]  id     �豸id
 *
 * \retval AW_OK        :  �ɹ�
 * \retval -AW_EINVAL   :  ������Ч
 * \retval -AW_EALREADY :  ���豸�Ѿ��ϵ�
 */
aw_err_t aw_gprs_power_on (int   id);

/**
 * \brief gprs�豸����
 *
 * \param[in]  id     �豸id
 *
 * \retval AW_OK        :  �ɹ�
 * \retval -AW_EINVAL   :  ������Ч
 * \retval -AW_EALREADY :  ���豸�Ѿ�����
 */
aw_err_t aw_gprs_power_off (int   id);

/**
 * \brief ����GPRS����
 * ʹ�øýӿڽ�������ʱ�������ʹ�õ��ⲿЭ�飬����Զ��򿪽���ppp����
 *
 * \param[in]  id       �豸id
 * \param[in]  p_mode   ģʽ: "TCP" ��  "UDP"
 * \param[in]  p_ip     ���ӷ�������IP��ַ������
 * \param[in]  port     ���ӷ������Ķ˿ں�
 * \param[in]  timeout  ��ʱʱ�䣬��λΪ��
 *
 * \retval  >= 0            : gprs���ӳɹ������ظ����ӵľ��
 * \retval  -AW_EINVAL      : ������Ч
 * \retval  -AW_ENOMSG      : GPRS�豸���ź�
 * \retval  -AW_ENOTSUP     : �� p_mode ģʽ��֧��
 */
int  aw_gprs_start (int                 id,
                    const char         *p_mode,
                    char               *p_ip,
                    uint16_t            port,
                    uint32_t            timeout);

/**
 * \brief �ر�һ��GPRS����
 * ʹ�øýӿڶϿ�����ʱ�������ʹ�õ��ⲿЭ�飬����Զ��ر�ppp����
 *
 * \param[in]  id       �豸id
 * \param[in]  hd       gprs���ӵľ��
 *
 * \retval AW_OK    �ɹ�
 */
aw_err_t aw_gprs_close (int   id, int hd);

/**
 * \brief ����GPRS����
 *
 * \note  ʹ���ڲ�Э��ջʱ
 *
 * \param[in]  id       �豸id
 * \param[in]  hd       gprs���ӵľ��
 * \param[in]  p_data   ���͵�����
 * \param[in]  len      �������ݳ���
 * \param[in]  timeout  ���ͳ�ʱ
 *
 * \retval AW_OK    �ɹ�
 */
ssize_t aw_gprs_send (int                 id,
                      int                 hd,
                      void               *p_data,
                      size_t              len,
                      uint32_t            timeout);

/**
 * \brief ����GPRS����
 *
 * \param[in]   id       �豸id
 * \param[in]   hd       gprs���ӵľ��
 * \param[out]  p_buf    �������ݻ���
 * \param[in]   len      �������ݻ����С
 *
 * \retval AW_OK    �ɹ�
 */
ssize_t aw_gprs_recv (int                 id,
                      int                 hd,
                      void               *p_buf,
                      size_t              len);


/**
 * \brief ���ŷ���
 *
 * \param[in]  id       �豸id
 * \param[in]  p_sms    ��������
 * \param[in]  len      �������ݳ���
 * \param[in]  p_num    �ֻ�����
 *
 * \retval AW_OK    �ɹ�
 */
aw_err_t aw_gprs_sms_send (int                 id,
                           uint8_t            *p_sms,
                           uint8_t             len,
                           char               *p_num);

/**
 * \brief HEX���ŷ���
 *
 * \param[in]  id       �豸id
 * \param[in]  p_sms    ��������
 * \param[in]  len      �������ݳ���
 * \param[in]  p_num    �ֻ�����
 *
 * \retval AW_OK    �ɹ�
 */
aw_err_t aw_gprs_sms_hex_send (int                 id,
                               uint8_t            *p_sms,
                               uint8_t             len,
                               char               *p_num);

/**
 * \brief ���Ž���
 *
 * \param[in]   id       �豸id
 * \param[out]  p_sms    ��������
 * \param[in]   timeout  ���յ����ŵĳ�ʱʱ��
 *
 * \retval > 0     ����ʣ����ſ��Լ�������
 *         = 0     ���Ž������
 *         = -1    ���Ž���ʧ��
 */
aw_err_t aw_gprs_sms_recv (int                      id,
                           struct aw_gprs_sms_buf  *p_sms,
                           uint32_t                 timeout);

/**
 * \brief ɾ��ȫ������
 *
 * \param[in]  id       �豸id
 *
 * \retval AW_OK    �ɹ�
 */
aw_err_t aw_gprs_all_sms_del (int       id);

/**
 * \brief io����
 *
 * \param[in]     id      : �豸id
 * \param[in]     req     : io����
 * \param[in,out] p_arg   : ����
 *
 * \retval  AW_OK        : �����ɹ�
 * \retval  -AW_EINVAL   : ������Ч
 * \retval  -AW_ENOTSUP  : ��ǰ�豸��֧�ָ�req����
 * \retval  -AW_EPERM    : ��������иò���������ʹ���ڲ�Э��ջʱ���������ppp���Ų���
 * \retval  ELSE         : ��������
 *
 * \par ����
 * \code
 *
 *
 *  aw_err_t ret;
 *
 *
 *  // ͨ��ioctl����ppp����
 *
 *  aw_local void __ppp_cb (void *p_data, bool_t ppp_stat)   //����ppp�ص�����
 *  {
 *      uint32_t *p_flag = p_data;
 *
 *      AW_INFOF((p_ctx, " enter the ppp cb �� ppp stat: %d\n", ppp_stat));
 *      *p_flag = ppp_stat;
 *  }
 *
 *  uint32_t *arg[2];
 *  uint32_t  ppp_flag;
 *
 *  arg[0] = (uint32_t *)__ppp_cb;
 *  arg[1] = &ppp_flag;
 *
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_PPP_OPEN, (void *)arg);
 *  if (ret == AW_OK) {
 *      // ioctlִ�й����ȴ��ص�����
 *      while (ppp_flag != TRUE) {
 *          aw_mdelay(500);
 *      }
 *  }
 *
 *
 *  int  dev_id = 0;   //ʹ��idΪ0��gprs�豸����id�� awbl_hwconf_gprs_xxx.h �����
 *
 *  //��ȡ��վ��Ϣ
 *  uint32_t bs_info[2];
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_BS_GET, (void *)bs_info);
 *  if (ret == AW_OK) {
 *      // �õ���bs_info[0] Ϊ��վ�����ţ� bs_info[1] ΪС��ID
 *  }
 *
 *  //��ȡ����ģʽ
 *  char     net_mode[80];
 *  memset(net_mode, 0, sizeof(net_mode));
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_NET_MODE_GET, (void *)net_mode);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get net mode : %s.\n", net_mode));
 *  }
 *
 *  //��ȡ��Ϣǿ��
 *  int      csq;
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_CSQ_GET, (void *)&csq);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get csq : %d.\n", csq));
 *  }
 *
 *  //��ȡAPN
 *  char     apn[16];
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_APN_GET, (void *)apn);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get apn : %s.\n", apn));
 *  }
 *
 *  //����AT����
 *  char  at_buf[] = "AT+MPING="www.baidu.com";   //ping�ٶ�
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_AT_SEND, (void *)at_buf);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("send : %s.\n", at_buf));
 *  }
 *
 *  //����AT������
 *  char  rec_buf[256];
 *  aw_mdelay(1000);    //������AT������ṩһ����ʱ�ٽ�������
 *
 *  memset(rec_buf, 0, 256);
 *  memcpy(rec_buf, "OK", 2);   //ָ��Ҫ���յ����ݣ��ɲ�ָ����
 *
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_AT_RECV, (void *)rec_buf);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("recv : %s.\n", rec_buf));
 *  }
 *
 *  // PPP���ŵ�IP��ַ��ȡ
 *  struct in_addr ip_addr;
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_PPPIF_IP_GET, (void *)&ip_addr);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get ppp_ip.\n"));
 *  }
 *
 *  // gprs�豸�����λ����1ΪӲ����λ
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_RESET, (void *)0);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("device software reset ok.\n"));
 *  }
 *
 *  // ��ȡGPRSģ��İ汾��
 *  char version[64];
 *  memset(version , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_VERSION_GET, (void *)version);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get gprs device version : %s.\n", version));
 *  }
 *
 *  // ��ȡGPRSģ��CCID
 *  char ccid[64];
 *  memset(ccid , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_CCID_GET, (void *)ccid);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get gprs device ccid : %s.\n", ccid));
 *  }
 *
 *  // ��ȡGPRS����״̬
 *  int sts;
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IP_STS_GET, (void *)&sts);
 *  if (ret == AW_OK && sts == AW_OK) {
 *      AW_INFOF(("ip connect ok.\n"));
 *  }
 *
 *  // ��ȡGPRSģ���IMEI��
 *  char imei[64];
 *  memset(imei , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IMEI_GET, (void *)&imei);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get imei: %s.\n", imei));
 *  }
 *
 *  // ��ȡGPRSģ���IMSI��
 *  char imsi[64];
 *  memset(imsi , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IMSI_GET, (void *)&imsi);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get imsi: %s.\n", imei));
 *  }
 *
 *  // ��ȡGPRSģ��Ķ���Ϣ���ĺ���
 *  char sca[32];
 *  memset(sca , 0, 32);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_SCA_GET, (void *)&sca);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get sca: %s.\n", sca));
 *  }
 *
 * \endcode
 */
aw_err_t aw_gprs_ioctl (int                   id,
                        aw_gprs_ioctl_req_t   req,
                        void                 *p_arg);

/** @} grp_aw_if_gprs */

#ifdef __cplusplus
}
#endif

#endif /* __AW_GPRS_H_ */

/* end of file */

