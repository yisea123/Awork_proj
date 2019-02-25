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

/**
 * \file
 * \brief emWin 帧缓冲驱动
 *
 * \internal
 * \par modification history:
 * - 1.00  17-11-21  mex, first implementation.
 * \endinternal
 */


#ifndef __AWBL_IMX1050_EMWIN_FB_H
#define __AWBL_IMX1050_EMWIN_FB_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_emwin_fb.h"

#include "driver/display/awbl_imx1050_lcdif.h"
#include "aw_spinlock.h"

#define AWBL_IMX1050_EMWIN_FB_NAME      "imx1050_emwin_fb"

/** \brief 设备信息 */
typedef struct awbl_imx1050_emwin_fb_devinfo {
    awbl_imx1050_lcdif_devinfo_t lcdif_info;
} awbl_imx1050_emwin_fb_devinfo_t;

/** \brief LCDC设备 */
typedef struct awbl_imx1050_emwin_fb {

    awbl_dev_t           dev;
    awbl_imx1050_lcdif_t lcdif;
    aw_emwin_fb_info_t   fb_info;
    aw_spinlock_isr_t    lock;

} awbl_imx1050_emwin_fb_t;


/**
 * \brief iMX RT1050 帧缓冲驱动注册
 */
void awbl_imx1050_emwin_fb_drv_register (void);


#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AWBL_IMX1050_EMWIN_FB_H */

/* end of file */

