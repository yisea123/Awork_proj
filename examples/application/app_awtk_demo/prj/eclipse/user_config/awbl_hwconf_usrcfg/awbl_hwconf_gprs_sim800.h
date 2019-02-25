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
#ifndef __AWBL_HWCONF_GPRS_SIM800_H
#define __AWBL_HWCONF_GPRS_SIM800_H

#ifdef AW_DEV_GPRS_SIM800

#include "driver/gprs/awbl_gprs_sim800.h"
#include "aw_serial.h"

/*******************************************************************************
    ������Ϣ
*******************************************************************************/


aw_local struct awbl_gprs_info   __g_sim800_gprs_info = {
    .p_dial_num     = "*99#",
    .p_apn          = "CTNET",
    .p_user         = NULL,
    .p_password     = NULL,
    .p_center_num   = NULL,
    .p_at_err       = NULL,
    .pfn_sms_int_cb = NULL,

//    .pwrkey_gpio    = PIO2_4,
//    .ri_gpio        = PIO2_3,

    .rst_gpio       = -1,
    .pwren_gpio     = -1,
    .w_dis_gpio     = -1,
};

aw_local char __sim800_sms_buf[320];
aw_local char __sim800_num_buf[20];
aw_local char __sim800_time_buf[50];


aw_local struct aw_gprs_sms_buf  __g_sim800_sms_info = {
    .p_sms_buff     = __sim800_sms_buf,
    .sms_buff_len   = sizeof(__sim800_sms_buf) - 1,

    .p_num_buff     = __sim800_num_buf,
    .num_buff_len   = sizeof(__sim800_num_buf) - 1,

    .p_time_buff    = __sim800_time_buf,
    .time_buff_len  = sizeof(__sim800_time_buf) - 1,
};

//aw_local char __g_sim800_msg_buffer[128];

aw_local struct  awbl_gprs_sim800_devinfo __g_sim800_devinfo = {
    .id             = 1,
//    .buf            = __g_sim800_msg_buffer,
//    .buf_size       = sizeof(__g_sim800_msg_buffer),
    .buf            = NULL,
    .buf_size       = 0,
    .p_gprs_info    = &__g_sim800_gprs_info,
    .p_sms_info     = &__g_sim800_sms_info,

    .com            = COM1,
    .baud           = 9600,
    .com_timeover   = 10,
};

aw_local struct awbl_gprs_sim800_dev __g_sim800_dev;

#define AWBL_HWCONF_GPRS_SIM800                           \
    {                                                     \
        AWBL_GPRS_SIM800_NAME,                            \
        0,                                                \
        AWBL_BUSID_PLB,                                   \
        0,                                                \
        (struct awbl_dev *)&__g_sim800_dev.dev,           \
        &__g_sim800_devinfo                               \
    },

#else
#define AWBL_HWCONF_GPRS_SIM800

#endif    /* AW_DEV_GPRS_SIM800 */

#endif  /* __AWBL_HWCONF_GPRS_SIM800_H */

/* end of file */
