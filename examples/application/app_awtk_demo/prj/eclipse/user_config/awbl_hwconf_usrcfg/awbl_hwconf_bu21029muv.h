/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief ����������������������Ϣ
 *
 * \internal
 * \par modification history:
 * - 1.01 16-08-18  anu, first implemetation
 * \endinternal
 */

#ifndef __AWBL_HWCONF_BU21029MUV_H
#define __AWBL_HWCONF_BU21029MUV_H

#ifdef AW_DEV_BU21029MUV

#include "aw_gpio.h"
#include "aw_ts.h"

#include "driver/input/touchscreen/awbl_bu21029muv.h"
#include "imx1050_pin.h"

/* ƽ̨��س�ʼ�� */
aw_local void __bu21029muv_plfm_init (void)
{   int i2c_touch_gpios[] = {GPIO1_11};

    if (aw_gpio_pin_request("i2c_touch_gpios", i2c_touch_gpios,
                             AW_NELEMENTS(i2c_touch_gpios)) == AW_OK) {
         /* ��λ����rc��·���� */
//       aw_gpio_pin_cfg(GPIO1_11, AW_GPIO_OUTPUT_INIT_LOW | AW_GPIO_PULL_UP);
//        for (int i = 0; i < 20; i++) {
//               aw_udelay(1000);
//       }
//       aw_gpio_set(GPIO1_11, 1);

         /* �ж����ű���ʹ�� */
        aw_gpio_pin_cfg(GPIO1_11, AW_GPIO_INPUT | AW_GPIO_PULL_UP);

    }
}

/* configure infomation */
aw_local struct awbl_bu21029muv_cfg __g_bu21029cfg={
        /*.int_pin  = */ GPIO1_11,
        /*.dev_addr = */ 0x40,
        {
         "480x272",                    /**< \brief ������������ʾ������       */
         0x00,                         /**< \brief ������������ʾ������ID */
         0x00,                         /**< \brief ������������ʾ����ƷID */
         5,                            /**< \brief ֧����ഥ����ĸ���.    */
         3,                            /**< \brief ��������, ��СֵΪ1  */
         1,                            /**< \brief �˲�����, ���ܴ��ڲ�������, ��СֵΪ1 */
         10,                           /**< \brief ����ʱ��      */
         10,                           /**< \brief �������޷�ֵ,��������,���ݹ�����ͬ����ʾ�������������. */
         5,                            /**< \brief У׼���޷�ֵ,������֤У׼ϵ��,���ݹ�����ͬ����ʾ�������������. */
         AW_TS_LIB_FIVE_POINT,         /**< \brief ���У׼�㷨   */
        },
        /* .pfn_plfm_init = */ __bu21029muv_plfm_init
};

/* �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_bu21029muv __g_bu21029muv;

#define AWBL_HWCONF_BU21029MUV       \
    {                            \
        AWBL_TOUCHSCREEN_NAME,   \
        0,                       \
        AWBL_BUSID_I2C,          \
        IMX1050_LPI2C1_BUSID,      \
        &(__g_bu21029muv.super),      \
        &(__g_bu21029cfg)    \
    },
#else

#define AWBL_HWCONF_BU21029MUV

#endif /* AW_DEV_BU21029MUV */

#endif /* __AWBL_HWCONF_BU21029MUV_H */

