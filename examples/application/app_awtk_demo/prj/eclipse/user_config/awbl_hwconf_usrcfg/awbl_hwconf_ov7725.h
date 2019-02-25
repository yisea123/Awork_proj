/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      Apollo.support@zlg.cn
*******************************************************************************/

#ifndef __AWBL_HWCONF_OV7725_H
#define __AWBL_HWCONF_OV7725_H


#ifdef  AW_DEV_OV7725

#include "driver/camera/awbl_ov7725.h"

aw_local void __ov7725_plfm_init (void)
{
    int ov7725_ctr_gpios[] = { GPIO1_8, GPIO1_9, GPIO1_16, GPIO1_17};

    if (aw_gpio_pin_request("ov7725_ctr_gpios",
            ov7725_ctr_gpios, AW_NELEMENTS(ov7725_ctr_gpios)) == AW_OK) {

        /* csi_rst */
        aw_gpio_pin_cfg(GPIO1_8,  AW_GPIO_OUTPUT_INIT_HIGH | AW_GPIO_PUSH_PULL);

        /* csi_en */
        aw_gpio_pin_cfg(GPIO1_9,  AW_GPIO_OUTPUT_INIT_HIGH | AW_GPIO_PUSH_PULL);

        /* sccb ��������  */

        /* scl */
        aw_gpio_pin_cfg(GPIO1_16, AW_GPIO_OUTPUT_INIT_HIGH );

        /* sda */
        aw_gpio_pin_cfg(GPIO1_17, AW_GPIO_OUTPUT_INIT_HIGH  );
    }
};

/* ov7725 device infomation */
aw_local aw_const struct awbl_ov7725_devinfo __g_ov7725_devinfo = {
        0,                                             /* ����ͷ��������Ӧ��ID��  */
        RGB565,                                        /* ���ظ�ʽ  */
        24000000,                                      /* ����ͷоƬ������ʱ��Ƶ��  */
        (AW_CAM_HREF_ACTIVE_HIGH |
        AW_CAM_DATA_LATCH_ON_RISING_EDGE),             /* ʱ�Ӽ��Ե�����  */
        4,                                             /* Ԥ��buffer����ӦΪ >=3 */
        "ov7725",                                      /* ����ͷ��  */
        {GPIO1_9, GPIO1_8, },                          /* PWDN RST */
        __ov7725_plfm_init
};

/* allocate wdt1 device instance RAM */
aw_local struct awbl_ov7725_dev __g_ov7725_dev;

#define  AWBL_HWCONF_OV7725          \
    {                                \
        AWBL_OV7725_NAME,            \
        0,                           \
        AWBL_BUSID_PLB,              \
        0,                           \
        (struct awbl_dev *)&__g_ov7725_dev, \
        &(__g_ov7725_devinfo)  \
    },

#else
#define AWBL_HWCONF_OV7725

#endif  /* AW_DEV_OV7725 */


#endif /* __AWBL_HWCONF_OV7725_H */
