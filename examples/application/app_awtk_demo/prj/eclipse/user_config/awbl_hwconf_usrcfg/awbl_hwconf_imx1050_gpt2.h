/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief AWBus-lite iMX1050 GPT �����ļ�
 *
 * iMX1050 GPT Ϊ iMX1050 ϵ�� MCU ��ͨ�ö�ʱ�����ṩ���¹���:
 *  - �������жϣ�����ʱ����
 *  - ���벶��
 *  - ����Ƚ�
 *
 * ��Ӧ�Ĺ������ü� awbl_imx1050_gpt_devinfo_t ���ͣ�����������ʾ�����ã�
 * ͨ���� #__GPT_FOR_TIMER��__GPT_FOR_INPUT �� __GPT_FOR_OUTPUT �����й���ѡ��
 *
 * - ���ó�ͨ�ö�ʱ����ʱ��ֻ��Ҫ�� mode ����Ϊ IMX1050_GPT_MODE_TIMER��
 *   ���ԡ�ͨ���Լ�����Ƚ�ֵ����Ҫ���ã��� 0 ���ɣ�
 *
 * - ���ó����벶���ʱ����Ҫ�� mode ����Ϊ IMX1050_GPT_MODE_INPUT��
 *   Ȼ����Ҫ����������ԣ��������ش������½��ش�������˫���ش�����
 *   ͨ��ѡ������ͨ��1��2��������Ƚ�ֵ����Ҫ���ã��� 0 ���ɣ�
 *
 * - ���ó�����Ƚϵ�ʱ����Ҫ�� mode ����Ϊ IMX1050_GPT_MODE_OUTPUT��
 *   Ȼ����Ҫ����������ԣ��������ת�������λ����������㣻
 *   ͨ��ѡ�����ͨ��1��2��3�����Լ�����Ƚ�ֵ�������Ժ�� imx1050_gpt_regs.h��
 *
 * \internal
 * \par modification history
 * - 1.00 2017-11-10  pea, first implementation
 * \endinternal
 */

#ifndef  __AWBL_HWCONF_IMX1050_GPT2_H
#define  __AWBL_HWCONF_IMX1050_GPT2_H

#ifdef AW_DEV_IMX1050_GPT2

#include "aw_int.h"
#include "driver/timer/awbl_imx1050_gpt.h"

#define __GPT2_FOR_TIMER     /**< \brief ���� GPT Ϊ��ʱ��ģʽ */
//#define __GPT2_FOR_INPUT     /**< \brief ���� GPT Ϊ���벶��ģʽ */
//#define __GPT2_FOR_OUTPUT    /**< \brief ���� GPT Ϊ����Ƚ�ģʽ */

/**
 * \brief ���� GPT ʹ�õ�ͨ��
 *
 * ��ʱ��ģʽʱ��ͨ��������Ч��
 * ���벶��ģʽʱ��ͨ��������Ϊ 1 ���� 2��
 * ����Ƚ�ģʽʱ��ͨ��������Ϊ 1��2 ���� 3��
 */
#define __GPT2_CHAN  3

/** \brief GPT2 ������Ϣ */
aw_local aw_const uint32_t __gpt2_gpios[5][2] = {
    {GPIO3_27, GPIO3_27_GPT2_CAPTURE1},
    {GPIO3_26, GPIO3_26_GPT2_CAPTURE2},
    {GPIO1_6, GPIO1_6_GPT2_COMPARE1},
    {GPIO1_7, GPIO1_7_GPT2_COMPARE2},
    {GPIO1_8, GPIO1_8_GPT2_COMPARE3}
};

/** \brief GPT2 ƽ̨��ʼ������ */
aw_local void __imx1050_gpt2_plfm_init (void)
{
#if defined __GPT2_FOR_INPUT
    int gpt2_gpios[] = {__gpt2_gpios[__GPT2_CHAN - 1][0]};

    if (aw_gpio_pin_request("gpt2_gpios",
                             gpt2_gpios,
                             AW_NELEMENTS(gpt2_gpios)) == AW_OK) {

        /* ���ù������� */
        aw_gpio_pin_cfg(__gpt2_gpios[__GPT2_CHAN - 1][0],
                        __gpt2_gpios[__GPT2_CHAN - 1][1]);
    }
#elif defined __GPT2_FOR_OUTPUT
    int gpt2_gpios[] = {__gpt2_gpios[__GPT2_CHAN + 1][0]};

    if (aw_gpio_pin_request("gpt2_gpios",
                             gpt2_gpios,
                             AW_NELEMENTS(gpt2_gpios)) == AW_OK) {

        /* ���ù������� */
        aw_gpio_pin_cfg(__gpt2_gpios[__GPT2_CHAN + 1][0],
                        __gpt2_gpios[__GPT2_CHAN + 1][1]);
    }
#endif
}

#if defined  __GPT2_FOR_TIMER

/** \brief GPT2 �豸��Ϣ */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* ͨ�����Ʒ��䶨ʱ�� */
    IMX1050_GPT2_BASE,              /* �Ĵ�������ַ */
    INUM_GPT2,                      /* �жϺ� */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* ʱ�� ID */
    IMX1050_GPT_MODE_TIMER,         /* ��ʱ������ */
    0,                              /* ������ */
    0,                              /* ��ʹ���������ͨ�� */
    0,                              /* ������Ƚ�ֵ */
    __imx1050_gpt2_plfm_init        /* ƽ̨��ʼ������ */
};
/* __GPT_FOR_TIMER */

#elif defined  __GPT2_FOR_INPUT

/** \brief GPT2 �豸��Ϣ */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* ͨ�����Ʒ��䶨ʱ�� */
    IMX1050_GPT2_BASE,              /* �Ĵ�������ַ */
    INUM_GPT2,                      /* �жϺ� */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* ʱ�� ID */
    IMX1050_GPT_MODE_INPUT,         /* ���벶��ģʽ */
    IMX1050_GPT_INPUT_FALL,         /* �����½��ش��� */
    __GPT2_CHAN,                    /* ͨ�� */
    0,                              /* ������Ƚ�ֵ */
    __imx1050_gpt2_plfm_init        /* ƽ̨��ʼ������ */
};
/* __GPT2_FOR_INPUT */

#elif defined  __GPT2_FOR_OUTPUT

/** \brief �豸��Ϣ */
aw_local aw_const awbl_imx1050_gpt_devinfo_t __g_imx1050_gpt2_param = {
    1,                              /* ͨ�����Ʒ��䶨ʱ�� */
    IMX1050_GPT2_BASE,              /* �Ĵ�������ַ */
    INUM_GPT2,                      /* �жϺ� */
    IMX1050_CLK_CG_GPT2_SERIAL,     /* ʱ�� ID */
    IMX1050_GPT_MODE_OUTPUT,        /* ����Ƚ�ģʽ */
    IMX1050_GPT_OUTPUT_TOG,         /* �����ת */
    __GPT2_CHAN,                    /* ͨ�� */
    0x0000FFFF,                     /* ����Ƚ�ֵ */
    __imx1050_gpt2_plfm_init,       /* ƽ̨��ʼ������ */
};
#endif /* __GPT2_FOR_OUTPUT */

/** \brief �豸ʵ���ڴ澲̬���� */
aw_local struct awbl_imx1050_gpt_dev __g_imx1050_gpt2_dev;

#define AWBL_HWCONF_IMX1050_GPT2    \
    {                               \
        AWBL_IMX1050_GPT_DRV_NAME,  \
        IMX1050_GPT2_BUSID,         \
        AWBL_BUSID_PLB,             \
        0,                          \
        &__g_imx1050_gpt2_dev.dev,  \
        &__g_imx1050_gpt2_param     \
    },

#else
#define AWBL_HWCONF_IMX1050_GPT2

#endif  /* AW_DEV_IMX1050_GPT2 */

#endif  /* __AWBL_HWCONF_IMX1050_GPT2_H */

/* end of file */
