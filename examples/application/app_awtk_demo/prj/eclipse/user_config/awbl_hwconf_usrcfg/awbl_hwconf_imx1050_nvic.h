/*******************************************************************************
*                                 AnyWhere
*                       ---------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/*******************************************************************************
  �жϿ�����������Ϣ
*******************************************************************************/
#include "driver/intctlr/awbl_armcm_nvic.h"

/*******************************************************************************
  ARM Cortex-M NVIC ������Ϣ
*******************************************************************************/

/* ISR ��Ϣӳ���ڴ澲̬���� */
aw_local uint8_t __g_armcm_nvic_infomap[160];

/* ISR ��Ϣ�ڴ澲̬���� */
aw_local struct awbl_armcm_nvic_isrinfo
    __g_armcm_nvic_isrinfos[AW_CFG_ARMCM_NVIC_ISRINFO_COUNT];

/* NVIC �豸��Ϣ */
aw_local aw_const struct awbl_armcm_nvic_devinfo __g_armcm_nvic_devinfo = {

    16,

    {
        0,                /* ֧�ֵ���ʼ�жϺ� */
        159,              /* ֧�ֵĽ����жϺ� */
    },

    160,      /* �жϸ��� */

    &__g_armcm_nvic_infomap[0],       /* ISR ӳ����Ϣ�ڴ�(��С����input_cnt) */

    AW_CFG_ARMCM_NVIC_ISRINFO_COUNT,  /* ISR ��Ϣ���� */
    &__g_armcm_nvic_isrinfos[0],      /* ISR ��Ϣ���ڴ�(��С����isrinfo_cnt) */
};

/* NVIC �豸ʵ���ڴ澲̬����*/
aw_local struct awbl_armcm_nvic_dev __g_armcm_nvic_dev;

#define AWBL_HWCONF_IMX1050_NVIC   \
    {                              \
        AWBL_ARMCM_NVIC_NAME,      \
        0,                         \
        AWBL_BUSID_PLB,            \
        0,                         \
        (struct awbl_dev *)&__g_armcm_nvic_dev, \
        &__g_armcm_nvic_devinfo    \
    },



/* end of file */

