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
 * \brief imx1050 SNVS RTC����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-08-30  mex, first implementation
 * \endinternal
 */

#ifndef AWBL_IMX1050_RTC_H
#define AWBL_IMX1050_RTC_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aworks.h"
#include "awbus_lite.h"
#include "awbl_rtc.h"
#include "aw_sem.h"
#include "imx1050_reg_base.h"

/** \brief ������ */
#define AWBL_IMX1050_RTC_NAME    "imx1050_rtc"

/**
 * \brief imx1050 RTC �豸��Ϣ
 */
struct awbl_imx1050_rtc_devinfo {

    /** \brief RTC ����������Ϣ */
    struct awbl_rtc_servinfo  rtc_servinfo;

    uint32_t                  regbase;  /**< �Ĵ�������ַ */
    void (*pfunc_plfm_init)(void);      /**< ƽ̨��س�ʼ��������ʱ�� */
};


/**
 * \brief imx1050 RTC �豸ʵ��
 */
struct awbl_imx1050_rtc_dev {

    /** \brief �����豸 */
    struct awbl_dev super;

    /** \brief �ṩ RTC ���� */
    struct awbl_rtc_service rtc_serv;

    /** \brief �豸�� */
    AW_MUTEX_DECL(dev_lock);
};

/**
 * \brief imx1050 RTC driver register
 */
void awbl_imx1050_rtc_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_IMX1050_RTC_H */

/* end of file */
