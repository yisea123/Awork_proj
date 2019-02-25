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
 * \brief AWBus ʹ��GPIOι�� �ӿ�ͷ�ļ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "awbl_gpio_wdt.h"
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 14-08-27  may, first implementation
 * \endinternal
 */

#ifndef __AWBL_GPIO_WDT_H
#define __AWBL_GPIO_WDT_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */


/*******************************************************************************
  includes
*******************************************************************************/
#include "apollo.h"
#include "awbus_lite.h"
#include "awbl_wdt.h"


/*******************************************************************************
  define
*******************************************************************************/

/** \brief  ������GPIOι�������� */
#define  GPIO_WDT_NAME  "gpio-wdt"


/******************************************************************************/

/** \brief ����GPIOι���Ĳ��� */
struct  awbl_gpio_wdt_param {
    uint32_t    gpio_num;           /**< GPIO number the feed watchdog */
    uint32_t    wdt_time;           /**< watchdog time (ms)*/
    void (*pfunc_plfm_init)(void);  /**< device init */
};

/** \brief ����GPIOι���Ŀ��Ź��豸 */
struct  awbl_gpio_wdt_dev {
    struct awbl_dev          dev;    /**< the AWBus device */
    struct awbl_hwwdt_info   info;   /**< hwwdt info */
    uint16_t                 gpio_num;
};

/**
 * \brief gpio wdt driver register
 */
void  awbl_gpio_wdt_drv_register (void);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* __AWBL_GPIO_WDT_H */
