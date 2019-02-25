/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AWBL_HWCONF_EMWIN_FB_H
#define __AWBL_HWCONF_EMWIN_FB_H

#ifdef AW_DEV_EMWIN_FB

/*******************************************************************************
  HW480272 ������Ϣ
*******************************************************************************/
#include "driver/display/awbl_imx1050_emwin_fb.h"


/**
 * \brief ����Ҫʹ��PWM���Ʊ���ʱ��PWM_ID��ָ��Ϊ��Ӧ��PWM�ţ�
 *        �粻��ҪPWM���Ʊ��⣬�뽫PWM_ID����Ϊ-1��
 *        PWM���Ʊ����GPIO�ܽſ��Ʊ��⣬ͬʱֻ��ѡ��һ�ַ�ʽ
 */
#define  PWM_ID     (-1)

/**
 * \brief ����Ҫʹ��GPIO�ܽſ��Ʊ���ʱ��GPIO_BACKLIGHT��ָ��Ϊ��Ӧ��GPIO�ܽźţ�
 *        �粻��ҪGPIO�ܽſ��Ʊ��⣬�뽫GPIO_BACKLIGHT����Ϊ-1��
 *        PWM���Ʊ����GPIO�ܽſ��Ʊ��⣬ͬʱֻ��ѡ��һ�ַ�ʽ
 */
#define  GPIO_BACKLIGHT     GPIO1_10

const static aw_clk_id_t emwin_fb_clks[2] = {

        IMX1050_CLK_CG_LCD,
        IMX1050_CLK_CG_LCDIF_PIX
};


/* �豸��Ϣ */
aw_local aw_const awbl_imx1050_emwin_fb_devinfo_t  __g_emwin_fb_param = {

    /* lcdif_info */
    {
         "tft_panel",              /** \brief Ĭ������� */
         0,                        /** \brief Ĭ����嵥Ԫ�� */
         PWM_ID,                   /** \brief Ĭ�ϱ�����Ƶ�PWM�� */
         GPIO_BACKLIGHT,           /** \brief Ĭ�ϱ�����Ƶ�GPIO�ܽ� */
         NULL,                     /** \brief ����ʹ���ĸ���� (ΪNULL��ʧ��ʱ��ʹ��Ĭ�����) */
         IMX1050_LCDIF_BASE,       /** \brief LCDIF�Ĵ�������ַ */
         INUM_LCDIF,               /** \brief LCD�жϺ� */
         emwin_fb_clks,
         2,
         IMX1050_CLK_CG_LCDIF_PIX
    }
};

/* �豸ʵ���ڴ澲̬���� */
aw_local awbl_imx1050_emwin_fb_t __g_emwin_fb;

#define AWBL_HWCONF_EMWIN_FB        \
    {                               \
        AWBL_IMX1050_EMWIN_FB_NAME, \
        0,                          \
        AWBL_BUSID_PLB,             \
        0,                          \
        &(__g_emwin_fb.dev),        \
        &(__g_emwin_fb_param)       \
    },

#else
#define AWBL_HWCONF_EMWIN_FB

#endif  /* AW_DEV_EMWIN_FB */

#endif  /* __AWBL_HWCONF_EMWIN_FB_H */

/* end of file */
