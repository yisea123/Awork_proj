/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief
 *
 * 使用本模块需要包含以下头文件：
 * \code
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 16-11-10  win, first implementation
 * \endinternal
 */

#ifndef __AWBL_UDA1380_H
#define __AWBL_UDA1380_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbus_lite.h"
#include "awbl_plb.h"
#include "aw_i2c.h"
#include "awbl_i2cbus.h"

#include "soc/awsa_soc_internal.h"

#define AWBL_UDA1380_NAME "uda1380_codec"

#define AWBL_UDA1380_DAC_CLK_SYSCLK 0
#define AWBL_UDA1380_DAC_CLK_WSPLL  1

struct awbl_uda1380_devinfo {
    int    gpio_power;
    int    gpio_reset;
    int    dac_clk;

    /** \brief power, reset use gpio ? */
    bool_t gpio_is_valid;

    /** \brief 设备从机地址 */
    uint8_t addr;
};

/**
 * \brief UDA1380 设备实例
 */
struct awbl_uda1380_dev {

    /** \brief 继承自 AWBus I2C device 设备 */
    struct awbl_i2c_device                       super;

    const struct awbl_snd_codec_uda1380_devinfo *p_devinfo;

    uint32_t                                     dac_clk;

    struct awsa_soc_codec                        codec;
    struct awsa_soc_dai                          dai[3];

    struct awsa_core_ctl_elem                    ctl_elem[19];
    struct awsa_soc_dapm_widget                  widget[18];
    struct awsa_core_ctl_elem                    widget_ctl_elem[3];

    struct awsa_soc_dapm_path                    path[20];
};

void awbl_uda1380_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_UDA1380_H */

/* end of file */
