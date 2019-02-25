/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ���Եļ�ʵ��
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_assert.h
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-23  orz, first implementation
 * \endinternal
 */

#ifndef __AW_ASSERT_H
#define __AW_ASSERT_H

/*lint ++flb */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_assert
 * \copydoc aw_assert.h
 * @{
 */

#ifdef AW_DEBUG

/* help macro */
#define _AW_VTOS(n)     #n          /* Convert n to string */
#define _AW_SVAL(m)     _AW_VTOS(m) /* Get string value of macro m */

/**
 * \brief ����һ�����ʽ
 *
 * �����ʽΪ��ʱ����겻���κ����飬Ϊ��ʱ�����aw_assert_msg()���������Ϣ��
 * ������Ϣ��ʽΪ��
 * �ļ������кţ����ʽ
 * \hideinitializer
 */
#define aw_assert(e) \
    ((e) ? (void)0 : aw_assert_msg(__FILE__":"_AW_SVAL(__LINE__)":("#e")\n"))

extern void aw_assert_msg (const char *msg);

#else

/**
 * \brief ����һ�����ʽ
 *
 * �����ʽΪ��ʱ����겻���κ����飬Ϊ��ʱ�����aw_assert_msg()���������Ϣ��
 * ������Ϣ��ʽΪ��
 * �ļ������кţ����ʽ
 * \hideinitializer
 */
#define aw_assert(e)    ((void)0)
#endif

#ifdef __cplusplus
}
#endif

/** @}  aw_grp_if_assert */

#endif /* __AW_ASSERT_H */

/* end of file */
