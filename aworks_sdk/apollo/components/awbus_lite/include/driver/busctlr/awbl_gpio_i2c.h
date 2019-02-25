/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief AWBus GPIO I2C 驱动头文件
 *
 * 本驱动使用 Apollo 标准GPIO接口来模拟I2C主机功能
 *
 * \par 1.驱动信息
 *
 *  - 驱动名:   "gpio_i2c"
 *  - 总线类型: AWBL_BUSID_PLB
 *  - 设备信息: struct awbl_gpio_i2c_devinfo
 *
 * \par 2.兼容设备
 *
 *  - 任何实现Apollo标准GPIO接口的设备
 *
 * \par 3.设备定义/配置
 *
 *  - \ref grp_awbl_gpio_i2c_hwconf
 *
 * \par 4.用户接口
 *
 *  - \ref grp_aw_serv_i2c
 *
 * \internal
 * \par modification history:
 * - 1.00 13-08-26  zen, first implementation
 * \endinternal
 */

#ifndef __AWBL_GPIO_I2C_H
#define __AWBL_GPIO_I2C_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/**
 * \addtogroup grp_awbl_drv_gpio_i2c
 * \copydetails awbl_gpio_i2c.h
 * @{
 */

/**
 * \defgroup  grp_awbl_gpio_i2c_hwconf 设备定义/配置
 *  //TODO
 */

/** @} grp_awbl_drv_gpio_i2c */

#include "aw_task.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbl_i2cbus.h"

#define AWBL_GPIO_I2C_NAME   "gpio_i2c"

/**
 * \brief GPIO I2C 设备信息
 */
struct awbl_gpio_i2c_devinfo {

    /** \brief 继承自 AWBus I2C 控制器设备信息 */
    struct awbl_i2c_master_devinfo i2c_master_devinfo;

    int      pin_scl;               /**< SCL 引脚编号 */
    int      pin_sda;               /**< SDA 引脚编号 */

    unsigned speed_exp;             /**< 总线速度指数, 值越大总线速度越慢, 通常
                                         配合逻辑分析仪来确定实际的总线速度 */

    void (*pfunc_plfm_init)(void);  /**< 平台相关初始化：开启时钟、初始化引脚 */
};

/**
 * \brief GPIO I2C 设备实例
 */
struct awbl_gpio_i2c_dev {

    /** \brief 继承自 AWBus I2C 主机控制器 */
    struct awbl_i2c_master  super;

    /** \brief GPIO I2C 任务ID */
    aw_task_id_t  task_id;

    /** \brief GPIO I2C 同步信号量ID */
    aw_semb_id_t  sync_sem_id;

    /** \brief 当前正在处理的 Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief 当前正在处理的 Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief 传输序列的最后一个传输 */
    struct aw_i2c_transfer *p_trans_seq_last;

    /** \brief 传输数据计数 */
    size_t      data_ptr;

    /** \brief 控制器忙标志 */
    bool_t        busy;

    /** \brief 控制器状态机状态  */
    int         state;
};

/**
 * \brief GPIO I2C master driver register
 */
void awbl_gpio_i2c_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_GPIO_I2C_H */

/* end of file */

