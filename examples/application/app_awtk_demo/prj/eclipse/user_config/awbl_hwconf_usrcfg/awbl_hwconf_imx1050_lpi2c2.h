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

/*******************************************************************************
  IMX1050 内置I2C  配置信息
*******************************************************************************/

#ifndef AWBL_HWCONF_IMX1050_LPI2C2_H_
#define AWBL_HWCONF_IMX1050_LPI2C2_H_

#include "driver/lpi2c/awbl_imx1050_lpi2c.h"
#include "imx1050_reg_base.h"

#ifdef AW_DEV_IMX1050_LPI2C2

#define AW_CFG_IMX1050_I2C_BUS_SPEED 1000000  /**< \brief MAX 1000000 */

aw_local void __imx1050_lpi2c2_plat_init (void);

aw_local void __imx1050_lpi2c2_pinmux_init (void) {

    int lpi2c2_gpios[] = {GPIO3_10, GPIO3_11};

    if (aw_gpio_pin_request("lpi2c2_gpios",
                            lpi2c2_gpios,
                            AW_NELEMENTS(lpi2c2_gpios)) == AW_OK) {
        aw_gpio_pin_cfg(GPIO3_10, GPIO3_10_LPI2C2_SDA | AW_GPIO_OPEN_DRAIN);
        aw_gpio_pin_cfg(GPIO3_11, GPIO3_11_LPI2C2_SCL | AW_GPIO_OPEN_DRAIN);
    }
}


/* imx1050 LPI2C2 设备信息 */
aw_local aw_const struct awbl_imx1050_lpi2c_devinfo __g_imx1050_lpi2c2_devinfo = {
    {
        IMX1050_LPI2C2_BUSID,         /* 控制器所对应的总线编号 */
        AW_CFG_IMX1050_I2C_BUS_SPEED, /* 控制器总线速度 */
        AWBL_I2C_WAITFOREVER          /* 超时 */
    },
    1000000,                          /* 总线空闲超时(ns) */
    1000000,                          /* SDA & SCL低电平超时 (ns) */
    200,                              /* SDA滤波宽度  (ns) */
    200,                              /* SCL滤波宽度  (ns) */
    IMX1050_LPI2C2_BASE,
    INUM_LPI2C2,
    IMX1050_CLK_CG_LPI2C2,
    __imx1050_lpi2c2_plat_init
};


aw_local void __imx1050_lpi2c2_plat_init (void) {
    aw_clk_enable(IMX1050_CLK_CG_LPI2C2);
    __imx1050_lpi2c2_pinmux_init();
}


/* imx1050内部UART设备实例内存静态分配 */
aw_local struct awbl_imx1050_lpi2c_dev __g_imx1050_lpi2c2_dev;

#define AWBL_HWCONF_IMX1050_LPI2C2  \
    {                               \
        AWBL_IMX1050_LPI2C_NAME,    \
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        (struct awbl_dev *)&__g_imx1050_lpi2c2_dev,  \
        &(__g_imx1050_lpi2c2_devinfo)   \
    },

#else
#define AWBL_HWCONF_IMX1050_LPI2C2
#endif

#endif /* AWBL_HWCONF_IMX1050_LPI2C2_H_ */
