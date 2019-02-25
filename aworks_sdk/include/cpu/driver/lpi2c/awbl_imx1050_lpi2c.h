/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-present Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief imx1050 lpi2c driver  header file
 *
 * \internal
 * \par modification history:
 * - 1.00 17-10-18  like, first implementation
 * \endinternal
 */

#ifndef AWBL_IMX1050_LPI2C_H
#define AWBL_IMX1050_LPI2C_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "awbl_i2cbus.h"
#include "aw_spinlock.h"
#include "awbl_sio.h"
#include "aw_cpu_clk.h"

#define AWBL_IMX1050_LPI2C_NAME               "imx1050_lpi2c"

/**
 * \brief imx1050 LPI2C 设备信息
 */
struct awbl_imx1050_lpi2c_devinfo {

    /** \brief 继承自 AWBus LPI2C 控制器设备信息 */
    struct awbl_i2c_master_devinfo lpi2c_master_devinfo;

    uint32_t    bus_idle_timeout;       /**< 总线空闲超时  */
    uint32_t    pin_low_timeout;        /**< PIN LOW超时  */
    uint8_t     sda_filter_wide;        /**< SDA滤波宽度  */
    uint8_t     scl_filter_wide;        /**< SCL滤波宽度  */
    uint32_t    regbase;                /**< 寄存器基地址 */
    int         inum;                   /**< 中断号 */
    aw_clk_id_t ref_clk_id;             /**< 输入时钟ID */
    void (*pfunc_plfm_init)(void);      /**< 平台相关初始化：开启时钟、初始化引脚 */
};


/**
 * \brief imx1050 LPI2C 设备实例
 */
struct awbl_imx1050_lpi2c_dev {

    /** \brief 继承自 AWBus LPI2C 主机控制器 */
    struct awbl_i2c_master  super;

    /** \brief 当前正在处理的 Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief 当前正在处理的 Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief 传输数据计数 */
    volatile size_t      data_ptr;

    /** \brief 写FIFO计数 */
    volatile size_t      data_count;

    /** \brief 控制器忙标志 */
    volatile bool_t      busy;

    volatile uint16_t    sent_flags;

    /** \brief 控制器状态机状态  */
    volatile int         state;
};

/**
 * \brief imx1050 LPI2C master driver register
 */
void awbl_imx1050_lpi2c_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */


#endif /* AWBL_IMX1050_LPI2C_H */
