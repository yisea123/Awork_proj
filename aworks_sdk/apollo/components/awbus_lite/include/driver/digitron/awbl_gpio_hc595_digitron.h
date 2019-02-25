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
 * \brief ����hc595������������ඨ��
 *
 *
 * \par ʹ��ʾ��
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-12-05  ops, first implementation.
 * \endinternal
 */

#ifndef AWBL_GPIO_HC595_DIGITRON_H_
#define AWBL_GPIO_HC595_DIGITRON_H_

#include "awbl_digitron_if.h"
#include "awbl_gpio_hc595.h"
#include "driver/board/awbl_matrix_key_lite.h"

#ifdef __cplusplus
extern "C" {
#endif

struct awbl_gpio_hc595_digitron_param {

	/**
	 * \brief ͨ����������ò���
	 */
	struct awbl_digitron_disp_param  ddparam;

	/**
	 * \brief λ�� GPIO��������(��������������̵����߸���)
	 */
    const uint16_t                   *p_com_pins;

	/**
	 * \brief ��������ܶ����hc595����
	 */
	uint8_t                          hc595_seg_nums;

	/**
	 * \brief ���������λ���GPIO�ܽ�λ��
	 */
	uint8_t                          gpio_com_nums;

	/**
	 * \brief �������ݻ�����
	 */
	uint8_t                          *p_seg_data;


    /**
     * \brief �Ƿ��������豸��������
     */
    bool_t                           multi_io;

    /**
     * \brief �������������豸��������ʱ��ֵ��Ч
     */
    struct awbl_matrix_key_lite_par *p_matrix_par;

};

struct awbl_gpio_hc595_digitron_dev {

	/**
	 * \brief �̳���ͨ�������awbl_digitron_dev
	 */
	struct awbl_digitron_dev          digitron_dev;

	/**
	 * \brief ����ͨ��hc595�豸
	 */
	struct aw_hc595_dev               *p_hc595_dev;

	/**
	 * \brief hc595��������ò���
	 */
	struct awbl_gpio_hc595_digitron_param  *p_par;

	/**
	 * \brief λ�����ݷ��ͽӿ�
	 */
	void (*pfn_com_data_send)(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx);

    /**
     * \brief �������ݷ��ͽӿ�
     */
    void (*pfn_seg_data_send)(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx);

    /**
     * \brief ���ڹܽŸ���ʱ�ӿ�
     */
    void (*pfn_black_cb)(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx);

};

aw_local aw_inline void awbl_gpio_hc595_digitron_com_data_send(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx)
{
	p_this->pfn_com_data_send(p_this, idx);
}

aw_local aw_inline void awbl_gpio_hc595_digitron_seg_data_send(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx)
{
    p_this->pfn_seg_data_send(p_this, idx);
}

aw_local aw_inline void awbl_gpio_hc595_digitron_black_cb(struct awbl_gpio_hc595_digitron_dev *p_this, uint8_t idx)
{
    if (p_this->pfn_black_cb != NULL) {
        p_this->pfn_black_cb(p_this, idx);
    }
}

void awbl_gpio_hc595_digitron_dev_ctor(struct awbl_gpio_hc595_digitron_dev   *p_this,
		                               struct aw_hc595_dev              *p_hc,
		                               struct awbl_gpio_hc595_digitron_param *p_par,
		                               uint8_t                           disp_dev_id);

#ifdef __cplusplus
}
#endif


#endif /* AWBL_GPIO_HC595_DIGITRON_H_ */