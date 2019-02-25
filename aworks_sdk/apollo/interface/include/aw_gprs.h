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
 * \brief 通用GPRS定义
 *
 * \par 使用示例
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
 * \brief IO控制的选项
 */
typedef enum aw_gprs_ioctl_req {

    /** \brief 设置使用的协议栈，设为0则为外部协议栈（默认），为1则使用内部协议栈   */
    AW_GPRS_REQ_PROTOCOL_SET,

    /**
     * \brief  PPP拨号，只能在使用外部协议时才能进行该ppp拨号；
     * 如果通过ioctl打开ppp后，则可以在应用层调用socket的接口进行连接和通信，
     * 此时不再调用 aw_gprs_ip_start 、aw_gprs_ip_send、aw_gprs_ip_receive
     * 和 aw_gprs_ip_close 接口；
     */
    AW_GPRS_REQ_PPP_OPEN,

    /** \brief PPP拨号关闭    */
    AW_GPRS_REQ_PPP_CLOSE,

    /** \brief 设备复位，参数给0则为软件复位，给1则为硬件复位    */
    AW_GPRS_REQ_RESET,

    /** \brief GPRS模块信号强度获取   */
    AW_GPRS_REQ_CSQ_GET,

    /** \brief 获取GPRS模块CCID   */
    AW_GPRS_REQ_CCID_GET,

    /** \brief 获取GPRS连接状态  */
    AW_GPRS_REQ_IP_STS_GET,

    /** \brief 获取网络运营商  */
    AW_GPRS_REQ_APN_GET,

    /** \brief PPP拨号的IP地址获取    */
    AW_GPRS_REQ_PPPIF_IP_GET,

    /** \brief 获取GPRS模块的版本号      */
    AW_GPRS_REQ_VERSION_GET,

    /** \brief 获取GPRS模块的IMEI号   */
    AW_GPRS_REQ_IMEI_GET,

    /** \brief 获取GPRS模块的IMSI号    */
    AW_GPRS_REQ_IMSI_GET,

    /** \brief 获取GPRS模块的短信息中心号码   */
    AW_GPRS_REQ_SCA_GET,

    /** \brief 获取网络模式   */
    AW_GPRS_REQ_NET_MODE_GET,

    /** \brief 获取基站信息   */
    AW_GPRS_REQ_BS_GET,

    /** \brief 发送AT命令   */
    AW_GPRS_REQ_AT_SEND,

    /** \brief 接收AT命令的返回结果   */
    AW_GPRS_REQ_AT_RECV,

    /** \brief ping功能   */
    AW_GPRS_REQ_PING,

} aw_gprs_ioctl_req_t;



struct aw_gprs_sms_buf {
    char     *p_sms_buff;                   /**< \brief 短信内容缓存   */
    uint16_t  sms_buff_len;                 /**< \brief 短信内容缓存长度   */

    char     *p_num_buff;                   /**< \brief 手机号码内容缓存   */
    uint16_t  num_buff_len;                 /**< \brief 手机号码内容缓存长度   */

    char     *p_time_buff;                  /**< \brief 时间内容缓存   */
    uint16_t  time_buff_len;                /**< \brief 时间内容缓存长度   */

/** \brief 接收的短信编码类型  */
#define AW_GPRS_SMS_CODE_GB          (0)     /**< \brief GB编码短信   */
#define AW_GPRS_SMS_CODE_HEX         (1)     /**< \brief HEX编码短信  */
    uint8_t   sms_code;                     /**< \brief 短信编码   */
};

/**
 * \brief gprs设备上电并初始化
 *
 * \param[in]  id     设备id
 *
 * \retval AW_OK        :  成功
 * \retval -AW_EINVAL   :  参数无效
 * \retval -AW_EALREADY :  该设备已经上电
 */
aw_err_t aw_gprs_power_on (int   id);

/**
 * \brief gprs设备掉电
 *
 * \param[in]  id     设备id
 *
 * \retval AW_OK        :  成功
 * \retval -AW_EINVAL   :  参数无效
 * \retval -AW_EALREADY :  该设备已经掉电
 */
aw_err_t aw_gprs_power_off (int   id);

/**
 * \brief 建立GPRS连接
 * 使用该接口建立连接时，如果是使用的外部协议，则会自动打开进行ppp拨号
 *
 * \param[in]  id       设备id
 * \param[in]  p_mode   模式: "TCP" 或  "UDP"
 * \param[in]  p_ip     连接服务器的IP地址或域名
 * \param[in]  port     连接服务器的端口号
 * \param[in]  timeout  超时时间，单位为秒
 *
 * \retval  >= 0            : gprs连接成功，返回该连接的句柄
 * \retval  -AW_EINVAL      : 参数无效
 * \retval  -AW_ENOMSG      : GPRS设备无信号
 * \retval  -AW_ENOTSUP     : 该 p_mode 模式不支持
 */
int  aw_gprs_start (int                 id,
                    const char         *p_mode,
                    char               *p_ip,
                    uint16_t            port,
                    uint32_t            timeout);

/**
 * \brief 关闭一个GPRS连接
 * 使用该接口断开连接时，如果是使用的外部协议，则会自动关闭ppp拨号
 *
 * \param[in]  id       设备id
 * \param[in]  hd       gprs连接的句柄
 *
 * \retval AW_OK    成功
 */
aw_err_t aw_gprs_close (int   id, int hd);

/**
 * \brief 发送GPRS数据
 *
 * \note  使用内部协议栈时
 *
 * \param[in]  id       设备id
 * \param[in]  hd       gprs连接的句柄
 * \param[in]  p_data   发送的数据
 * \param[in]  len      发送数据长度
 * \param[in]  timeout  发送超时
 *
 * \retval AW_OK    成功
 */
ssize_t aw_gprs_send (int                 id,
                      int                 hd,
                      void               *p_data,
                      size_t              len,
                      uint32_t            timeout);

/**
 * \brief 接收GPRS数据
 *
 * \param[in]   id       设备id
 * \param[in]   hd       gprs连接的句柄
 * \param[out]  p_buf    接收数据缓存
 * \param[in]   len      接收数据缓存大小
 *
 * \retval AW_OK    成功
 */
ssize_t aw_gprs_recv (int                 id,
                      int                 hd,
                      void               *p_buf,
                      size_t              len);


/**
 * \brief 短信发送
 *
 * \param[in]  id       设备id
 * \param[in]  p_sms    短信内容
 * \param[in]  len      短信内容长度
 * \param[in]  p_num    手机号码
 *
 * \retval AW_OK    成功
 */
aw_err_t aw_gprs_sms_send (int                 id,
                           uint8_t            *p_sms,
                           uint8_t             len,
                           char               *p_num);

/**
 * \brief HEX短信发送
 *
 * \param[in]  id       设备id
 * \param[in]  p_sms    短信内容
 * \param[in]  len      短信内容长度
 * \param[in]  p_num    手机号码
 *
 * \retval AW_OK    成功
 */
aw_err_t aw_gprs_sms_hex_send (int                 id,
                               uint8_t            *p_sms,
                               uint8_t             len,
                               char               *p_num);

/**
 * \brief 短信接收
 *
 * \param[in]   id       设备id
 * \param[out]  p_sms    短信内容
 * \param[in]   timeout  接收到短信的超时时间
 *
 * \retval > 0     还有剩余短信可以继续接收
 *         = 0     短信接收完成
 *         = -1    短信接收失败
 */
aw_err_t aw_gprs_sms_recv (int                      id,
                           struct aw_gprs_sms_buf  *p_sms,
                           uint32_t                 timeout);

/**
 * \brief 删除全部短信
 *
 * \param[in]  id       设备id
 *
 * \retval AW_OK    成功
 */
aw_err_t aw_gprs_all_sms_del (int       id);

/**
 * \brief io控制
 *
 * \param[in]     id      : 设备id
 * \param[in]     req     : io请求
 * \param[in,out] p_arg   : 数据
 *
 * \retval  AW_OK        : 操作成功
 * \retval  -AW_EINVAL   : 参数无效
 * \retval  -AW_ENOTSUP  : 当前设备不支持该req请求
 * \retval  -AW_EPERM    : 不允许进行该操作，例：使用内部协议栈时则不允许进行ppp拨号操作
 * \retval  ELSE         : 其他错误
 *
 * \par 范例
 * \code
 *
 *
 *  aw_err_t ret;
 *
 *
 *  // 通过ioctl启动ppp连接
 *
 *  aw_local void __ppp_cb (void *p_data, bool_t ppp_stat)   //定义ppp回调函数
 *  {
 *      uint32_t *p_flag = p_data;
 *
 *      AW_INFOF((p_ctx, " enter the ppp cb ， ppp stat: %d\n", ppp_stat));
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
 *      // ioctl执行功，等待回调运行
 *      while (ppp_flag != TRUE) {
 *          aw_mdelay(500);
 *      }
 *  }
 *
 *
 *  int  dev_id = 0;   //使用id为0的gprs设备，该id从 awbl_hwconf_gprs_xxx.h 里查找
 *
 *  //获取基站信息
 *  uint32_t bs_info[2];
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_BS_GET, (void *)bs_info);
 *  if (ret == AW_OK) {
 *      // 得到的bs_info[0] 为基站区域编号， bs_info[1] 为小区ID
 *  }
 *
 *  //获取网络模式
 *  char     net_mode[80];
 *  memset(net_mode, 0, sizeof(net_mode));
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_NET_MODE_GET, (void *)net_mode);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get net mode : %s.\n", net_mode));
 *  }
 *
 *  //获取信息强度
 *  int      csq;
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_CSQ_GET, (void *)&csq);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get csq : %d.\n", csq));
 *  }
 *
 *  //获取APN
 *  char     apn[16];
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_APN_GET, (void *)apn);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get apn : %s.\n", apn));
 *  }
 *
 *  //发送AT命令
 *  char  at_buf[] = "AT+MPING="www.baidu.com";   //ping百度
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_AT_SEND, (void *)at_buf);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("send : %s.\n", at_buf));
 *  }
 *
 *  //接收AT命令结果
 *  char  rec_buf[256];
 *  aw_mdelay(1000);    //发送完AT命令后提供一点延时再接收数据
 *
 *  memset(rec_buf, 0, 256);
 *  memcpy(rec_buf, "OK", 2);   //指定要接收的数据（可不指定）
 *
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_AT_RECV, (void *)rec_buf);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("recv : %s.\n", rec_buf));
 *  }
 *
 *  // PPP拨号的IP地址获取
 *  struct in_addr ip_addr;
 *  ret = aw_gprs_dev_ioctl(dev_id, AW_GPRS_REQ_PPPIF_IP_GET, (void *)&ip_addr);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get ppp_ip.\n"));
 *  }
 *
 *  // gprs设备软件复位，给1为硬件复位
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_RESET, (void *)0);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("device software reset ok.\n"));
 *  }
 *
 *  // 获取GPRS模块的版本号
 *  char version[64];
 *  memset(version , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_VERSION_GET, (void *)version);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get gprs device version : %s.\n", version));
 *  }
 *
 *  // 获取GPRS模块CCID
 *  char ccid[64];
 *  memset(ccid , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_CCID_GET, (void *)ccid);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get gprs device ccid : %s.\n", ccid));
 *  }
 *
 *  // 获取GPRS连接状态
 *  int sts;
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IP_STS_GET, (void *)&sts);
 *  if (ret == AW_OK && sts == AW_OK) {
 *      AW_INFOF(("ip connect ok.\n"));
 *  }
 *
 *  // 获取GPRS模块的IMEI号
 *  char imei[64];
 *  memset(imei , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IMEI_GET, (void *)&imei);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get imei: %s.\n", imei));
 *  }
 *
 *  // 获取GPRS模块的IMSI号
 *  char imsi[64];
 *  memset(imsi , 0, 64);
 *  ret = aw_gprs_ioctl(dev_id, AW_GPRS_REQ_IMSI_GET, (void *)&imsi);
 *  if (ret == AW_OK) {
 *      AW_INFOF(("get imsi: %s.\n", imei));
 *  }
 *
 *  // 获取GPRS模块的短信息中心号码
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

