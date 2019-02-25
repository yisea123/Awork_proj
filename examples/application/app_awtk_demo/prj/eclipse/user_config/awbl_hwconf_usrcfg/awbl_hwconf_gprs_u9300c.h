/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      aworks.support@zlg.cn
*******************************************************************************/
#ifndef __AWBL_HWCONF_GPRS_U9300C_H
#define __AWBL_HWCONF_GPRS_U9300C_H

#ifdef AW_DEV_GPRS_U9300C

#include "driver/gprs/awbl_gprs_u9300c.h"
#include "aw_serial.h"

/*******************************************************************************
    ≈‰÷√–≈œ¢
*******************************************************************************/


aw_local struct awbl_gprs_info   __g_u9300c_gprs_info = {
    .p_dial_num     = "*99***1#",
    .p_apn          = NULL,
    .p_user         = NULL,
    .p_password     = NULL,
    .p_center_num   = NULL,
    .p_at_err       = "ERROR",
    .pfn_sms_int_cb = NULL,

    .rst_gpio       = -1,
    .pwren_gpio     = -1,
    .w_dis_gpio     = -1,
};

aw_local char __u9300c_sms_buf[320];
aw_local char __u9300c_num_buf[20];
aw_local char __u9300c_time_buf[50];


aw_local struct aw_gprs_sms_buf  __g_u9300c_sms_info = {
    .p_sms_buff     = __u9300c_sms_buf,
    .sms_buff_len   = sizeof(__u9300c_sms_buf) - 1,

    .p_num_buff     = __u9300c_num_buf,
    .num_buff_len   = sizeof(__u9300c_num_buf) - 1,

    .p_time_buff     = __u9300c_time_buf,
    .time_buff_len   = sizeof(__u9300c_time_buf) - 1,
};

aw_local char __g_u9300c_msg_buffer[1500];

aw_local struct  awbl_gprs_u9300c_devinfo __g_u9300c_devinfo = {
    .id             = 0,
    .buf            = __g_u9300c_msg_buffer,
    .buf_size       = sizeof(__g_u9300c_msg_buffer),
    .p_gprs_info    = &__g_u9300c_gprs_info,
    .p_sms_info     = &__g_u9300c_sms_info,
};

aw_local struct awbl_gprs_u9300c_dev __g_u9300c_dev;

#define AWBL_HWCONF_GPRS_U9300C                           \
    {                                                     \
        AWBL_GPRS_U9300C_NAME,                            \
        0,                                                \
        AWBL_BUSID_PLB,                                   \
        0,                                                \
        (struct awbl_dev *)&__g_u9300c_dev.dev,           \
        &__g_u9300c_devinfo                               \
    },

#else
#define AWBL_HWCONF_GPRS_U9300C

#endif    /* AW_DEV_GPRS_U9300C */

#endif  /* __AWBL_HWCONF_GPRS_U9300C_H */

/* end of file */
