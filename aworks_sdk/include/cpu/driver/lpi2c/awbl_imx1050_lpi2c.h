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
 * \brief imx1050 LPI2C �豸��Ϣ
 */
struct awbl_imx1050_lpi2c_devinfo {

    /** \brief �̳��� AWBus LPI2C �������豸��Ϣ */
    struct awbl_i2c_master_devinfo lpi2c_master_devinfo;

    uint32_t    bus_idle_timeout;       /**< ���߿��г�ʱ  */
    uint32_t    pin_low_timeout;        /**< PIN LOW��ʱ  */
    uint8_t     sda_filter_wide;        /**< SDA�˲����  */
    uint8_t     scl_filter_wide;        /**< SCL�˲����  */
    uint32_t    regbase;                /**< �Ĵ�������ַ */
    int         inum;                   /**< �жϺ� */
    aw_clk_id_t ref_clk_id;             /**< ����ʱ��ID */
    void (*pfunc_plfm_init)(void);      /**< ƽ̨��س�ʼ��������ʱ�ӡ���ʼ������ */
};


/**
 * \brief imx1050 LPI2C �豸ʵ��
 */
struct awbl_imx1050_lpi2c_dev {

    /** \brief �̳��� AWBus LPI2C ���������� */
    struct awbl_i2c_master  super;

    /** \brief ��ǰ���ڴ���� Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief ��ǰ���ڴ���� Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief �������ݼ��� */
    volatile size_t      data_ptr;

    /** \brief дFIFO���� */
    volatile size_t      data_count;

    /** \brief ������æ��־ */
    volatile bool_t      busy;

    volatile uint16_t    sent_flags;

    /** \brief ������״̬��״̬  */
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
