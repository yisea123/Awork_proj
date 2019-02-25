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
 * \brief AWBus �жϿ������ӿ�ͷ�ļ�
 *
 * ʹ�ñ�ģ����Ҫ��������ͷ�ļ���
 * \code
 * #include "awbl_intcltr.h"
 * \endcode
 *
 * ��ģ����� AWBus �ϵ������жϿ�������
 *
 * \internal
 * \par modification history:
 * - 1.00 12-11-06  zen, first implemetation
 * \endinternal
 */

#ifndef __AWBL_INTCTLR_H
#define __AWBL_INTCTLR_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \brief AWBus intctlr �����������Ϣ
 */
struct awbl_intctlr_servinfo {

    /** \brief ֧�ֵ���ʼ�жϺ� */
    int inum_start;

    /** \brief ֧�ֵĽ����жϺ� */
    int inum_end;
};

/**
 * \brief AWBus intctlr ������
 */
struct awbl_intctlr_servfuncs {

    /* \brief �����жϷ����� */
    aw_err_t (*pfunc_int_connect)(void            *p_cookie,
                                  int              inum,
                                  aw_pfuncvoid_t   pfunc_isr,
                                  void            *p_arg);

    /* \brief �Ͽ��жϷ����� */
    aw_err_t (*pfunc_int_disconnect)(void            *p_cookie,
                                     int              inum,
                                     aw_pfuncvoid_t   pfunc_isr,
                                     void            *p_arg);

    /* \brief �ж�ʹ�ܷ����� */
    aw_err_t (*pfunc_int_enable)(void *p_cookie, int inum);

    /* \brief �ж�ʹ�ܷ����� */
    aw_err_t (*pfunc_int_disable)(void *p_cookie, int inum);

};

/**
 * \brief AWBus �жϿ���������
 */
struct awbl_intctlr_service {

    /** \brief ָ����һ�� intctlr ���� */
    struct awbl_intctlr_service *p_next;

    /** \brief intctlr �����������Ϣ */
    const struct awbl_intctlr_servinfo *p_servinfo;

    /** \brief intctlr ����ķ����� */
    const struct awbl_intctlr_servfuncs *p_servfuncs;

    /**
     * \brief intctlr �����Զ��������
     *
     * �˲����� intctlr �ӿ�ģ����������ʱ���������ã�
     * �ڵ��÷�����ʱ��Ϊ��һ��������
     */
    void *p_cookie;
};

/**
 * \brief AWBus �жϿ����������ʼ��
 *
 * \attention ������Ӧ���� awbl_dev_init1() ֮���� awbl_dev_init2() ֮ǰ����
 */
void awbl_intctlr_init(void);

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AWBL_INTCTLR_H */

/* end of file */
