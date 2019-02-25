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
 * \brief gprs接口
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

/** \brief GPRS模块的参数信息  */
struct awbl_gprs_info
{
    char     *p_dial_num;                   /**< \brief 数据业务拨号号码   */
    char     *p_apn;                        /**< \brief APN名称   */
    char     *p_user;                       /**< \brief APN用户名   */
    char     *p_password;                   /**< \brief APN密码   */
    char     *p_center_num;                 /**< \brief 短信息中心号码   */
    char     *p_at_err;                     /**< \brief AT 命令出错时接收到的字符串  */

    /** \brief 短信接收中断回调函数, 该函数用于通知用户接收到短信息 */
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
    struct sio_mgn               sio_mgn;          /**< \brief sio管理 */

#if AWBL_GPRS_USE_LWIP_1_4
    int                          ppp_fd;           /**< \brief PPP句柄 */
    struct ppp_addrs            *p_pppaddr;        /**< \brief PPP获取到的地址  */

    /** \brief 定义ppp连接关闭的信号量 */
    AW_SEMB_DECL(link_close);
#endif /* AWBL_GPRS_USE_LWIP_1_4 */

    awbl_gprs_ppp_phase_t        phase;

#if AWBL_GPRS_USE_LWIP_2_0
    /** \brief ppp控制块指针 */
    ppp_pcb     *p_pcb;

    /** \brief ppp网卡 */
    struct netif netif;

    /** \brief 接收buf,被编码的数据存放处 */
    u_char       rxbuf[PPP_MRU + PPP_HDRLEN];

    /** \brief 定义ppp线程 */
    AW_TASK_DECL(thread, PPP_THREAD_STACKSIZE);

    /** \brief 定义ppp线程的关闭信号量 */
    AW_SEMB_DECL(thread_close);
#endif /* AWBL_GPRS_USE_LWIP_2_0 */

    /** \brief gprs设备拨号接口  */
    aw_err_t (*pfn_dial_up)   (struct awbl_gprs_dev *p_this);

    /** \brief gprs设备关闭拨号接口  */
    aw_err_t (*pfn_dial_down) (struct awbl_gprs_dev *p_this);

    /** \brief 用户ppp回调  */
    void (*pfn_user_cb)       (void *p_user_arg, bool_t ppp_stat);

    /** \brief 用户ppp回调参数  */
    void  *p_user_arg;
};

/** \brief GPRS设备的服务接口   */
struct awbl_gprs_service {

    /** \brief GPRS模块启动接口 */
    aw_err_t (*pfn_gprs_power_on)(struct awbl_gprs_dev *p_this);

    /** \brief GPRS模块关闭接口 */
    aw_err_t (*pfn_gprs_power_off)(struct awbl_gprs_dev *p_this);

    aw_err_t (*pfn_gprs_ioctl)(struct awbl_gprs_dev *p_this,
                               aw_gprs_ioctl_req_t   req,
                               void                 *p_arg);

    /** \brief 短信发送接口    */
    aw_err_t (*pfn_gprs_sms_send)(struct awbl_gprs_dev *p_this,
                                  uint8_t              *p_sms,
                                  uint8_t               len,
                                  char                 *p_num);

    /** \brief HEX短信发送接口    */
    aw_err_t (*pfn_gprs_sms_hex_send)(struct awbl_gprs_dev *p_this,
                                      uint8_t              *p_sms,
                                      uint8_t               len,
                                      char                 *p_num);

    /** \brief 短信接收接口   */
    aw_err_t (*pfn_gprs_sms_recv)(struct awbl_gprs_dev      *p_this,
                                  struct aw_gprs_sms_buf    *p_sms,
                                  uint32_t                   timeout);

    /** \brief 删除全部短信     */
    aw_err_t (*pfn_gprs_all_sms_del)(struct awbl_gprs_dev *p_this);


    /** \brief 建立GPRS连接  */
    int (*pfn_gprs_start)(struct awbl_gprs_dev *p_this,
                          uint8_t               mode,
                          char                 *p_ip,
                          uint16_t              port,
                          uint32_t              timeout);

    /** \brief 关闭GPRS连接  */
    aw_err_t (*pfn_gprs_close)(struct awbl_gprs_dev *p_this, int   hd);

    /** \brief 发送GPRS数据  */
    ssize_t (*pfn_gprs_send)(struct awbl_gprs_dev *p_this,
                             int                   hd,
                             void                 *p_data,
                             size_t                len,
                             uint32_t              timeout);

    /** \brief 接收GPRS数据   */
    ssize_t (*pfn_gprs_recv)(struct awbl_gprs_dev *p_this,
                             int                   hd,
                             void                 *p_buf,
                             size_t                len);
};


/** \brief GPRS设备结构体   */
struct awbl_gprs_dev {

    struct awbl_gprs_dev        *p_next;

    /** \brief GPRS设备的服务接口   */
    aw_const struct awbl_gprs_service    *p_serv;

    /** \brief gprs模块的参数 */
    struct awbl_gprs_info       *p_info;

    /** \brief 短信的数据和信息 */
    struct aw_gprs_sms_buf      *p_sms;

    struct awbl_gprs_ppp         ppp;

    /** \brief gprs设备的唯一ID，用于给中间层获取设备 */
    int                          dev_id;

    /** \brief gprs标准接口使用的互斥锁 */
    AW_MUTEX_DECL(               mutex);

    bool_t                       mutex_inited;

    /** \brief 下层以gprs设备的指针  */
    void                        *p_gprs_dev;

    /** \brief socktet连接的数量 */
    uint8_t                      socket_num;

    /** \brief 是否使用外部协议栈标志 */
    bool_t                       use_external_protocol;

    /** \brief 是否已经初始化 */
    bool_t                       already_init;

    /** \brief 已经上电标志 */
    bool_t                       power_on;
};

/**
 * \brief 对ppp和sio_mgn等通用资源的初始化
 *
 * \param[in]  p_gprs         gprs设备指针
 *
 * \return  无
 */
aw_err_t awbl_gprs_init_tail (struct awbl_gprs_dev *p_gprs);

/**
 * \brief 发送 AT 命令
 *
 * \param[in]  p_this         gprs设备指针
 * \param[in]  p_str          发送的AT命令
 *
 * \return  无
 */
void awbl_gprs_at_send (struct awbl_gprs_dev  *p_this, char *p_str);


/**
 * \brief 指定接收 AT 命令返回的结果
 *
 * \param[in]  this           gprs设备指针
 * \param[in]  p_buf          接收数据的缓存buf
 * \param[in]  buf_size       缓存大小
 * \param[in]  p_cond         指定返回的字符串数据
 * \param[in]  arg_num        有多少种可能的返回数据（指明指针数组里有几个元素）
 * \param[in]  wait_ms        最大的等待时间，单位S，为0则不等待
 *
 * \retval   >= 0              : 接收到了p_arg里的数据，是以返回值作为下标的那个数据
 * \retval   -AW_ETIMEDOUT 0   : 接收到了p_arg里的数据，是以返回值作为下标的那个数据
 * \retval   -AW_ENOMSG 0      : 接收到了p_arg里的数据，是以返回值作为下标的那个数据
 */
int awbl_gprs_at_recv (struct awbl_gprs_dev     *p_this,
                       char                     *p_buf,
                       uint32_t                  buf_size,
                       char                     *p_cond[],
                       uint32_t                  arg_num,
                       uint32_t                  wait_ms);

/**
 * \brief 将数据打包成PDU（protocol data unit）包
 *
 * \param[in]  message   存放打包的数据的buf
 * \param[in]  msg_size  buf大小
 * \param[in]  p_sca     短消息服务中心地址
 * \param[in]  p_sms     短信内容
 * \param[in]  len       短信长度
 * \param[in]  p_num     接收方号码
 * \param[in]  is_en     是否是英文短信
 * \param[in]  is_hex    数据类型是否是hex类型
 *
 * \retval AW_OK        :  成功
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
 * \brief 解释PDU（protocol data unit）包
 *
 * \param[in]  p_pdu_data     pdu数据
 * \param[in]  p_to_sms       存放解释到的pdu数据的结构体
 *
 * \retval AW_OK        :  成功
 * \retval -AW_EBADMSG  :  不是正确的数据包
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
