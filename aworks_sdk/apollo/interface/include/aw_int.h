/*******************************************************************************
 *                                  AWorks
 *                       ----------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.zlg.cn
 * e-mail:      support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief �жϱ�׼�ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ�
 * \code
 * #include aw_int.h
 * \endcode
 *
 * �������ṩ�˲���ϵͳ�жϵĽӿڡ��жϺ���ƽ̨���塣
 * ��������ɵ��ñ�ģ�������CPU�жϵĿ��أ�
 * �жϷ����������ӡ��Ͽ���ʹ�ܡ����ܵĲ�����
 *
 * \par ��ʾ��
 * \code
 *  #include "apollo.h"
 *  #include "aw_int.h"
 *
 *  void my_isr(void *p_arg)
 *  {
 *      int my_arg = (int)p_arg; //my_arg = 5
 *      //�жϴ�������
 *  }
 *  aw_int_connect(INUM_ADC, my_isr, (void *)5); //����ADC���жϷ�����
 *  aw_int_enable(INUM_ADC);    // ����ADC�ж�
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 12-08-27  zen, first implementation
 * \endinternal
 */

#ifndef __AW_INT_H
#define __AW_INT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_int
 * \copydoc aw_int.h
 * @{
 */

#include "aw_psp_int.h"

/**
 * \brief ����CPU LOCK
 * ���궨��һ���������Ա��� CPU �����ж�״̬
 * \sa AW_INT_CPU_LOCK_DECL_STATIC() AW_INT_CPU_LOCK() AW_INT_CPU_UNLOCK()
 */
#define AW_INT_CPU_LOCK_DECL(flags) \
    AW_PSP_INT_CPU_LOCK_DECL(flags)

/**
 * \brief ����CPU LOCK (��̬)
 * ���궨��һ���������Ա��� CPU �����ж�״̬
 * \sa AW_INT_CPU_LOCK_DECL() AW_INT_CPU_LOCK() AW_INT_CPU_UNLOCK()
 */
#define AW_INT_CPU_LOCK_DECL_STATIC(flags) \
    AW_PSP_INT_CPU_LOCK_DECL_STATIC(flags)

/**
 * \brief �رձ���CPU���ж�
 *
 * ���������Թرյ��ô˺����������ISR����CPU���жϡ�
 * AW_INT_CPU_LOCK() �� AW_INT_CPU_UNLOCK() ֧��Ƕ�׵��ã�����
 * AW_INT_CPU_UNLOCK() ������������CPU���жϣ�ֻ�������� AW_INT_CPU_UNLOCK()
 * �Ż����������жϡ�
 *
 * \attention
 *  - CPU�жϱ��رյ�ʱ��Ӧ�����ܵض�
 *  - ������Ӧ�������� AW_INT_CPU_UNLOCK() ��Ե���
 *  - Ӧ������ʹ�ÿ���CPU�ж���Ϊ�����Ļ����ֶΣ��Ƽ�ʹ��
 *            \ref grp_aw_if_spinlock ����֮
 *  - �������޷��ر�CPU�ġ����������жϡ�
 *
 * \par ʾ��:�����÷�
 * \code
 * int key;
 *
 * AW_INT_CPU_LOCK_DECL(key)
 *
 * AW_INT_CPU_LOCK(key);
 * // ���ܱ���ϵ��ٽ����(ִ��Ӧ�����ܵض�)
 * AW_INT_CPU_UNLOCK(key);
 * \endcode
 *
 * \par ʾ��:Ƕ��
 * \code
 * AW_INT_CPU_LOCK_DECL(key0);
 * AW_INT_CPU_LOCK_DECL(key1);
 * AW_INT_CPU_LOCK_DECL(key2);
 *
 * AW_INT_CPU_LOCK(key0);   //CPU���жϱ������ر�
 * AW_INT_CPU_LOCK(key1);   //CPU���жϼ������ֹر�
 * AW_INT_CPU_LOCK(key2);   //CPU���жϼ������ֹر�
 *
 * AW_INT_CPU_UNLOCK(key2);    //CPU���жϼ������ֹر�
 * AW_INT_CPU_UNLOCK(key1);    //CPU���жϼ������ֹر�
 * AW_INT_CPU_UNLOCK(key0);    //CPU���жϱ���������
 * \endcode
 *
 * \see AW_INT_CPU_UNLOCK()
 */
#define AW_INT_CPU_LOCK(key)    AW_PSP_INT_CPU_LOCK(key)

/**
 * \brief �򿪱���CPU���ж�
 *
 * ���������Դ򿪵��ô˺����������ISR����CPU���жϡ�
 *
 * \attention ������Ӧ�������� AW_INT_CPU_LOCK() ��Ե���
 *
 * \see AW_INT_CPU_LOCK()
 */
#define AW_INT_CPU_UNLOCK(key)  AW_PSP_INT_CPU_UNLOCK(key)

/**
 * \brief �ж��Ƿ����жϵ���������ִ��
 *
 * \retval true     ���жϵ���������ִ��
 * \retval false    ���������������ִ��
 */
#define AW_INT_CONTEXT()    AW_PSP_INT_CONTEXT()

/**
 * \brief ����һ��C������һ��Ӳ���ж�
 *
 * ����������һ��ָ����C������һ��ָ�����ж��ϡ����жϺ�Ϊ \a inum ���жϷ���ʱ��
 * ��������Ȩģʽ�µ��ø�C����( \a pfunc_isr )�������ݲ��� \a p_arg ��
 *
 * \par ʵ�����
 * ƽ̨����֧�����Ӷ��C������ͬһ���ж��ϣ����жϷ���ʱ�����ᰴ�����ӵ��Ⱥ�˳��
 * ������ЩC������ƽ̨Ҳ����ֻ֧������һ��C�����������Ѿ������ӵ��жϽ��᷵��
 * �ռ䲻�����(-ENOSPC)�����������ε��� aw_int_disable()�� aw_int_disconnect()
 * ��ֹ���Ͽ���ǰ�����ӵ�C�������ſ��Գɹ������µ�C������
 *
 * \attention   ����ȷ���ж� \a inum �Ѿ�����ֹ(�ж� \a inum Ĭ���Ǳ���ֹ��)��
 *              ����, �ڱ�����֮ǰӦ���ȵ��� aw_int_disable() ��ֹ��Ӧ���жϡ�
 *
 * \param[in]   inum        �жϺţ���ƽ̨����
 * \param[in]   pfunc_isr   Ҫ���õ�C����(ISR, �жϷ�����)������Ϊ�κ���ͨ��
 *                          C���룬���ǣ������ܵ���ĳЩ�������ĺ�����
 *                          ����Ӧ����֤������ִ�о����ܵض�
 * \param[in]   p_arg       Ҫ���ݸ�C�����Ĳ���
 *
 * \retval      AW_OK       �ɹ�
 * \retval     -AW_ENXIO    \a inum Ϊ�����ڵ��жϺ�
 * \retval     -AW_EFAULT   \a pfunc_isr Ϊ NULL
 * \retval     -AW_ENOSPC   �ռ䲻��
 *
 * \par ʾ���������÷�
 * \code
 *  void my_isr(void *p_arg)
 *  {
 *      int my_arg = (int)p_arg; //my_arg = 5
 *      //�жϴ�������
 *  }
 *  aw_int_connect(INUM_ADC, my_isr, (void *)5); //����ADC���жϷ�����
 * \endcode
 *
 * \par ʾ���������жϷ�����(ISR)
 * ��ʵ��ֻ֧�֡�1���ж�����1��ISR��ʱ�������·�ʽ����ISR:
 * \code
 *  aw_int_disable(INUM_ADC);                        // ��ֹ�ж�
 *  aw_int_disconnect(INUM_ADC, my_isr, (void *)5);  // �Ͽ��ɵ�ISR
 *  aw_int_connect(INUM_ADC, my_isr_new, (void *)6); // �����µ�ISR
 *  aw_int_enable(INUM_ADC);                         // �����ж�
 * \endcode
 *
 * \see aw_int_disconnect()
 */
aw_err_t aw_int_connect(int             inum,
                        aw_pfuncvoid_t  pfunc_isr,
                        void           *p_arg);

/**
 * \brief �Ͽ�һ��C������һ��Ӳ���жϵ�����
 *
 * ��������һ���ж������жϿ�һ������Ϊ \a p_arg ��C������
 *
 * \attention
 *  - Ӧ����֤ \a pfunc_isr �� \a p_arg ����ǰ���ݸ� aw_int_connect() �Ĳ�����ͬ��
 *
 * \param[in]   inum        �жϺ�
 * \param[in]   pfunc_isr   Ҫ�Ͽ���C����
 * \param[in]   p_arg       Ҫ�Ͽ���C�����Ĳ���
 *
 * \retval      AW_OK       �ɹ�
 * \retval     -AW_ENXIO    \a inum Ϊ�����ڵ��жϺ�
 * \retval     -AW_ENOENT   δ�ҵ�����Ϊ \a p_arg �� \a pfunc_isr
 *
 * \see aw_int_connect()
 */
aw_err_t aw_int_disconnect(int             inum,
                           aw_pfuncvoid_t  pfunc_isr,
                           void           *p_arg);

/**
 * \brief ʹ��ָ�����ж�
 *
 * ������ʹ����\a inum ָ�����ж�
 *
 * \param[in]   inum        �жϺ�
 *
 * \retval      AW_OK       �ɹ�
 * \retval     -AW_ENXIO    \a inum Ϊ�����ڵ��жϺ�
 *
 * \see aw_int_disable()
 */
aw_err_t aw_int_enable(int inum);

/**
 * \brief ����ָ�����ж�
 *
 * ������������\a inum ָ�����ж�
 *
 * \param[in]   inum        �жϺ�
 *
 * \retval      AW_OK       �ɹ�
 * \retval     -AW_ENXIO    \a inum Ϊ�����ڵ��жϺ�
 *
 * \see aw_int_enable()
 */
aw_err_t aw_int_disable(int inum);

/** @}  grp_aw_if_int */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AW_INT_H */

/* end of file */
