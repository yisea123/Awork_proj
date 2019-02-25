/*******************************************************************************
*                                 AnyWhere
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      anywhere.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ARMv6-M �жϿ�ͷ�ļ�
 *
 * ��ģ��ΪCortex-M0(ARMv6-M�ܹ�)���ж�ģ��ʵ�֡�
 *
 * \par ����
 * - �жϺŵĶ�����ο� \ref grp_aw_int_inums
 * - ֻ������һ��C������һ���ж��ϣ������Ѿ������ӵ��жϽ��᷵�ؿռ䲻�����
 *   (-ENOSPC)��
 *
 * \internal
 * \par modification history:
 * - 1.00 12-09-04  zen, first implementation
 * \endinternal 
 */

#ifndef __ARMV6M_INT_H
#define __ARMV6M_INT_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/** \brief �жϺŵ����ֵ */
#define ARMV6M_INTNUM_MAX       239

/** \brief �жϺŵĸ��� */
#define ARMV6M_INTNUM_COUNT     (ARMV6M_INTNUM_MAX + 1)

/**
 * \brief ARMv6-M �жϿ��ʼ������
 */
void armv6m_int_init(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __ARMV6M_INT_H */

/* end of file */
