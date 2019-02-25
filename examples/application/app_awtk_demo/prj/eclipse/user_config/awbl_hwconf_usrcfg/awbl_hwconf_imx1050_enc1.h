/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_HWCONF_IMX1050_ENC1_H
#define __AWBL_HWCONF_IMX1050_ENC1_H

#ifdef AW_DEV_IMX1050_ENC1

#include "driver/enc/awbl_imx1050_enc.h"
#include "driver/gpio/awbl_imx1050_gpio_private.h"


/* Macros for entire XBARA_SELx register.  */
#define XBARA_SELx(base, output) \
    (*(volatile uint16_t *)((base) + ((output) / 2U) * 2U))

/* Set the XBARA_SELx_SELx field to a new value. */
#define XBARA_WR_SELx_SELx(base, input, output)                                   \
    (XBARA_SELx((base), (output)) =                                               \
         ((XBARA_SELx((base), (output)) & ~(0xFFU << (8UL * ((output) % 2UL)))) | \
          ((input) << (8UL * ((output) % 2UL)))))


#define ENC_PAD_CTRL    (PKE_1_Pull_Keeper_Enabled | \
                         SPEED_2_medium_100MHz     | \
                         DSE_6_R0_6 )

#define ENC_XBARA_SET_SIGNALS_CONNECT(base, input, output) \
    XBARA_WR_SELx_SELx(base, (((uint16_t)(input)) & 0xFFU), (((uint16_t)(output)) & 0xFFU))

aw_local void __imx1050_enc1_plfm_init (void)
{

    aw_local aw_const int enc1_gpios[] = {
        GPIO1_9,
        GPIO1_10,
        GPIO1_11,
    };

    if (aw_gpio_pin_request("enc1_gpios",
                             enc1_gpios,
                             AW_NELEMENTS(enc1_gpios)) == AW_OK) {

        /* A相输入 */
        aw_gpio_pin_cfg(GPIO1_9, GPIO1_9_XBAR1_IN21 | IMX1050_PAD_CTL(ENC_PAD_CTRL));

        /* B相输入 */
        aw_gpio_pin_cfg(GPIO1_10, GPIO1_10_XBAR1_IN22 | IMX1050_PAD_CTL(ENC_PAD_CTRL));

        /* Z相输入 */
        aw_gpio_pin_cfg(GPIO1_11, GPIO1_11_XBAR1_IN23 | IMX1050_PAD_CTL(ENC_PAD_CTRL));
    }
    aw_clk_enable(IMX1050_CLK_CG_ENC1);
    aw_clk_enable(IMX1050_CLK_CG_XBAR1);

    ENC_XBARA_SET_SIGNALS_CONNECT(IMX1050_XBARA1_BASE, 0x115, 0x142);
    ENC_XBARA_SET_SIGNALS_CONNECT(IMX1050_XBARA1_BASE, 0x116, 0x143);
    ENC_XBARA_SET_SIGNALS_CONNECT(IMX1050_XBARA1_BASE, 0x117, 0x144);
};


/* 设备信息 */
aw_local aw_const struct awbl_imx1050_enc_devinfo __g_imx1050_enc1_devinfo = {
    IMX1050_ENC1_BASE,              /**< \brief 寄存器基地址*/
    INUM_ENC1,                      /**< \brief 中断号 */
    IMX1050_ENC1,                   /**< \brief 当前通道号 */
    enc_index_trigger_rising_edge,     /**< \brief index触发 */
    0,                              /**< \brief 滤波器采样计数 */
    10,                             /**< \brief 滤波器采样周期 */
    __imx1050_enc1_plfm_init        /**< \brief 平台初始化 */
};

/* 设备实例内存静态分配 */
aw_local struct awbl_imx1050_enc_dev __g_imx1050_enc1_dev;

#define AWBL_HWCONF_IMX1050_ENC1                 \
{                                                \
    IMX1050_ENC_NAME,                            \
    0,                                           \
    AWBL_BUSID_PLB,                              \
    0,                                           \
    (struct awbl_dev *)&__g_imx1050_enc1_dev,    \
    &(__g_imx1050_enc1_devinfo)                  \
},

#else
#define AWBL_HWCONF_IMX1050_ENC1
#endif  /* AW_DEV_IMX1050_ENC1 */

#endif /* __AWBL_HWCONF_IMX1050_ENC1_H */

/* end of file */
