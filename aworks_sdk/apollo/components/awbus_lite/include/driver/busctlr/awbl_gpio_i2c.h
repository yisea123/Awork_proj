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
 * \brief AWBus GPIO I2C ����ͷ�ļ�
 *
 * ������ʹ�� Apollo ��׼GPIO�ӿ���ģ��I2C��������
 *
 * \par 1.������Ϣ
 *
 *  - ������:   "gpio_i2c"
 *  - ��������: AWBL_BUSID_PLB
 *  - �豸��Ϣ: struct awbl_gpio_i2c_devinfo
 *
 * \par 2.�����豸
 *
 *  - �κ�ʵ��Apollo��׼GPIO�ӿڵ��豸
 *
 * \par 3.�豸����/����
 *
 *  - \ref grp_awbl_gpio_i2c_hwconf
 *
 * \par 4.�û��ӿ�
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
 * \defgroup  grp_awbl_gpio_i2c_hwconf �豸����/����
 *  //TODO
 */

/** @} grp_awbl_drv_gpio_i2c */

#include "aw_task.h"
#include "aw_sem.h"
#include "aw_spinlock.h"
#include "awbl_i2cbus.h"

#define AWBL_GPIO_I2C_NAME   "gpio_i2c"

/**
 * \brief GPIO I2C �豸��Ϣ
 */
struct awbl_gpio_i2c_devinfo {

    /** \brief �̳��� AWBus I2C �������豸��Ϣ */
    struct awbl_i2c_master_devinfo i2c_master_devinfo;

    int      pin_scl;               /**< SCL ���ű�� */
    int      pin_sda;               /**< SDA ���ű�� */

    unsigned speed_exp;             /**< �����ٶ�ָ��, ֵԽ�������ٶ�Խ��, ͨ��
                                         ����߼���������ȷ��ʵ�ʵ������ٶ� */

    void (*pfunc_plfm_init)(void);  /**< ƽ̨��س�ʼ��������ʱ�ӡ���ʼ������ */
};

/**
 * \brief GPIO I2C �豸ʵ��
 */
struct awbl_gpio_i2c_dev {

    /** \brief �̳��� AWBus I2C ���������� */
    struct awbl_i2c_master  super;

    /** \brief GPIO I2C ����ID */
    aw_task_id_t  task_id;

    /** \brief GPIO I2C ͬ���ź���ID */
    aw_semb_id_t  sync_sem_id;

    /** \brief ��ǰ���ڴ���� Message */
    struct aw_i2c_message *p_cur_msg;

    /** \brief ��ǰ���ڴ���� Transfer */
    struct aw_i2c_transfer *p_cur_trans;

    /** \brief �������е����һ������ */
    struct aw_i2c_transfer *p_trans_seq_last;

    /** \brief �������ݼ��� */
    size_t      data_ptr;

    /** \brief ������æ��־ */
    bool_t        busy;

    /** \brief ������״̬��״̬  */
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

