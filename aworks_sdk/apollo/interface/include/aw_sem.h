/*******************************************************************************
*                                 AWorks
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
 * \brief RTOS�ź�����������ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_sem.h
 *
 * \par ��ʾ��
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);   // �������� task_a
 *  AW_TASK_DECL_STATIC(task_b, 512);   // �������� task_b
 *
 *  AW_SEMB_DECL_STATIC(sem);           // ����������ź��� sem
 *
 *  void func_a (void *arg)
 *  {
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(sem);          //�ͷ��ź���
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER); //�ȴ��ź���
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // ��ʼ���ź���
 *      AW_SEMB_INI(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(task_a,            // ����ʵ��
 *                   "task_a",          // ��������
 *                   5,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_a,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      AW_TASK_INIT(task_b,            // ����ʵ��
 *                   "task_b",          // ��������
 *                   6,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_b,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * //�������ݴ���ӡ�����
 *
 * \internal
 * \par modification history
 * - 1.12 17-09-05  anu, refine the description
 * - 1.11 17-09-06  zen, refine the description
 * - 1.10 13-03-04  zen, refine the description
 * - 1.02 12-11-20  lyzh, rename some MACRO name. Merge aw_semb.h, aw_semc.h,
 *                  and aw_mutex.h
 * - 1.01 12-11-05  orz, implement with aw_task.h
 * - 1.00 12-10-23  orz, created
 * \endinternal
 */

#ifndef __AW_SEM_H
#define __AW_SEM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_sem
 * \copydoc aw_sem.h
 * @{
 */

#include "aw_psp_sem.h"

/**
 * \name ��ʱ��������
 * @{
 */
/**
 * \brief ���õȴ�
 * \hideinitializer
 */
#define AW_SEM_WAIT_FOREVER     AW_PSP_SEM_WAIT_FOREVER

/**
 * \brief �޵ȴ�
 * \hideinitializer
 */
#define AW_SEM_NO_WAIT          AW_PSP_SEM_NO_WAIT
/** @} ��ʱ�������� */


/**
 * \name �������ź�����ʼ��״̬
 */
/**
 * \brief �ź�����
 * \hideinitializer
 */
#define AW_SEM_EMPTY            AW_PSP_SEM_EMPTY

/**
 * \brief �ź����������ڶ������ź�����
 * \hideinitializer
 */
#define AW_SEM_FULL            AW_PSP_SEM_FULL
/** @} �������ź�����ʼ��״̬ */


/**
 * \name �ź�����ʼ��ѡ��
 * @{
 */
/**
 * \brief �Ŷӷ�ʽΪ FIFO (�Ƚ��ȳ�)
 * \hideinitializer
 */
#define AW_SEM_Q_FIFO         AW_PSP_SEM_Q_FIFO

/**
 * \brief �Ŷӷ�ʽΪ���ȼ�
 * \hideinitializer
 */
#define AW_SEM_Q_PRIORITY     AW_PSP_SEM_Q_PRIORITY

/**
 * \brief �����ź���ɾ����ȫ (���ڻ����ź���)
 * \hideinitializer
 */
#define AW_SEM_DELETE_SAFE    AW_PSP_SEM_DELETE_SAFE

/**
 * \brief ��ֹ�����ź������ȼ���ת (���ڻ����ź���)
 * \hideinitializer
 */
#define AW_SEM_INVERSION_SAFE   AW_PSP_SEM_INVERSION_SAFE
/** @} �ź�����ʼ��ѡ�� */

/**
 * \name �ź������Ͷ���
 * @{
 */
typedef aw_psp_semb_id_t    aw_semb_id_t;      /**< �������ź���ID     */
typedef aw_psp_semc_id_t    aw_semc_id_t;      /**< �����ź���ID       */
typedef aw_psp_mutex_id_t   aw_mutex_id_t;     /**< �����ź���ID       */
/** @} �ź������Ͷ��� */

/**
 *  \brief ����������ź���
 *
 * ���궨��һ���������ź���,�ڱ���ʱ����ź��������ڴ�ķ���; ������ʱ, ��Ҫ����
 * AW_SEMB_INIT() ����ź����ĳ�ʼ�������� AW_SEMB_TERMINATE()��ֹ�ź�����
 *
 * ����\a sem ֻ����Ϊ�� AW_SEMB_INIT(),  AW_SEMB_TAKE(),  AW_SEMB_GIVE()��
 * AW_SEMB_TERMINATE()�Ĳ�����
 *
 * AW_SEMB_INIT()�����ź�����\a sem_id, \a sem_id ��Ϊ���� aw_semb_take() ,
 * aw_semb_give()�� aw_semb_terminate()�Ĳ���;��Щ�����Ĺ������Ӧ�ĺ�Ĺ�����ͬ,
 * ��������, ����ʹ��\a sem_id ��Ϊ����,\a sem_id ������Ϊ�ź����ľ���ں�����
 * ��֮�䴫�ݡ�
 *
 * ����ʹ�ñ��꽫�ź���ʵ��Ƕ�뵽��һ�����ݽṹ��,�����Ļ�,�����Ǹ�������ݶ���
 * ��ʱ����Զ�������ź���ʵ����ڴ����, ������ķ�����ʾ��
 *
 * \attention ���ź���û�п�ģ��(�ļ�)ʹ�õ������Ƽ�ʹ�� AW_SEMB_DECL_STATIC()
 *            ���汾�꣬�����ɱ���ģ��֮���ź���������Ⱦ��
 *
 * \attention �������÷��ⲻ, ��Ī�ں�����ʹ�ô˺��������ź�������Ϊ�ں����ڴ˺�
 *            ������ڴ�������ջ�ϣ�һ���������أ�������ڴ汻�Զ����ա�
 *            �ں����ڲ�ʹ�� AW_SEMB_DECL_STATIC()�������ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_SEMB_INIT(),  AW_SEMB_TAKE(), AW_SEMB_GIVE()
 *                �� AW_SEMB_TERMINATE() һ��ʹ�á�
 *
 * \par �����������÷�
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);   // �������� task_a
 *  AW_TASK_DECL_STATIC(task_b, 512);   // �������� task_b
 *
 *  AW_SEMB_DECL_STATIC(sem);           // ����������ź��� sem
 *
 *  void func_a (void *arg)
 *  {
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(sem);          //�ͷ��ź���
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER); //�ȴ��ź���
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *      // ��ʼ���ź���
 *      AW_SEMB_INI(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(task_a,            // ����ʵ��
 *                   "task_a",          // ��������
 *                   5,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_a,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      AW_TASK_INIT(task_b,            // ����ʵ��
 *                   "task_b",          // ��������
 *                   6,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_b,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par ���������ź���ʵ��Ƕ����һ�����ݽṹ
 * \code
 *  #include "aw_sem.h"
 *
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);          // ����ʵ��task_a, ��ջ512
 *      AW_TASK_DECL(task_b, 512);          // ����ʵ��task_b, ��ջ512
 *      AW_SEMB_DECL(sem);                  // �ź���ʵ��
 *      aw_semb_id_t sem_id;                // �ź���ID
 *  };
 *  struct my_struct   my_object;           // ���������ݶ���
 *
 *  void func_a (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(p_myobj->sem);     //�ͷ��ź���(ʹ���ź���ʵ��)
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          // �ȴ��ź���(ʹ���ź���ID)
 *          aw_semb_take(p_myobj->sem_id, AW_SEM_WAIT_FOREVER);
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // ��ʼ���ź���
 *      my_object.sem_id = AW_SEMB_INIT(my_object.sem,
 *                                      AW_SEM_EMPTY,
 *                                      AW_SEM_Q_PRIORITY);
 *      if (my_object.sem_id == NULL) {
 *          return -1;                      // �ź�����ʼ��ʧ��
 *      }
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_object.task_a,      // ����ʵ��
 *                   "task_a",              // ��������
 *                   5,                     // �������ȼ�
 *                   512,                   // �����ջ��С
 *                   func_a,                // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      AW_TASK_INIT(my_object.task_b,      // ����ʵ��
 *                   "task_b",              // ��������
 *                   6,                     // �������ȼ�
 *                   512,                   // �����ջ��С
 *                   func_b,                // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //��ʱ20��
 *
 *      // AW_SEMB_TERMINATE(my_object.sem);    // ��ֹ�ź���
 *      // aw_semb_terminate(my_object.sem_id); // ��ֹ�ź���(ʹ���ź���ID)
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(), AW_SEMB_GIVE,
 *     AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_DECL(sem)       AW_PSP_SEMB_DECL(sem)

/**
 * \brief ����������ź���(��̬)
 *
 * ������ AW_SEMB_DECL() �Ĺ�����ͬ, ��������, AW_SEMB_DECL_STATIC() �ڶ�����
 * ���������ڴ�ʱ, ʹ�ùؼ��� \b static , ���һ��, ����Խ��ź���ʵ���������
 * ������ģ����(�ļ���)�Ӷ�����ģ��֮����ź���������ͻ���������ں�����ʹ�ñ�
 * �궨���ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *                AW_SEMB_GIVE() �� aw_semb_terminate() һ��ʹ�á�
 *
 * \par ����
 * �� AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_INIT(), AW_SEMB_TAKE(), AW_SEMB_GIVE,
 *     AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_DECL_STATIC(sem)    AW_PSP_SEMB_DECL_STATIC(sem)

/**
 * \brief ���ö������ź���
 *
 * ��������һ���������ź���, �൱��ʹ�ùؼ� \b extern ����һ���ⲿ���š�
 * ���Ҫʹ����һ��ģ��(�ļ�)�ж�����ź���, ����ʹ�ñ���������ź���, Ȼ���
 * ���Բ������ź�������������ź���Ӧ����ʹ�� AW_SEMB_DECL()����ġ�
 *
 * \param[in] sem  �ź���ʵ��
 *
 * \par ����
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_IMPORT(sem_x);      // �����ź��� sem_x
 *
 *  int func ()
 *  {
 *      AW_SEMB_TAKE(sem_x);    // �ȴ��ź��� sem_x
 *  }
 * \endcode
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_IMPORT(sem)     AW_PSP_SEMB_IMPORT(sem)

/**
 * \brief �������ź�����ʼ��
 *
 * ��ʼ���� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC()��̬����Ķ������ź���,
 * ��Ƕ�뵽��һ�������ݶ����еĶ������ź������ź�������ʼ��Ϊ #AW_SEM_EMPTY ��
 * #AW_SEM_FULL ״̬��
 *
 * �������ź�����ѡ������������ڴ��ź�����������Ŷӷ�ʽ, ���԰����������ȼ�
 * ���Ƚ��ȳ��ķ�ʽ�Ŷ�, ���Ƿֱ��Ӧ #AW_SEM_Q_PRIORITY �� #AW_SEM_Q_FIFO ��
 *
 * \param[in] sem           �ź���ʵ��,�� AW_SEMB_DECL()��
 *                          AW_SEMB_DECL_STATIC()����
 * \param[in] initial_state ��ʼ״̬:
 *                              - #AW_SEM_EMPTY
 *                              - #AW_SEM_FULL
 * \param[in] options       ��ʼ��ѡ���־:
 *                              - #AW_SEM_Q_FIFO
 *                              - #AW_SEM_Q_PRIORITY
 *
 * \return �ɹ����ض������ź�����ID, ʧ���򷵻�NULL
 *
 * \sa AW_SEM_Q_FIFO, AW_SEM_Q_PRIORITY
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_TAKE(), AW_SEMB_GIVE(),
 *     AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_INIT(sem, initial_state, options) \
            AW_PSP_SEMB_INIT(sem, initial_state, options)

/**
 * \brief ��ȡ�������ź���
 *
 * ��ȡ�ź���������ź���Ϊ��, �����񽫻ᱻ����ֱ���ź�����ÿ���(�����������
 * �� AW_SEMB_GIVE()�� aw_semb_give())������ź����Ѿ��ǿ��õ�, �򱾵��ý���
 * ��ո��ź���, �����������ܻ�ȡ�����ź���, ֱ�����õ������ͷŴ��ź�����
 *
 * ���� \a timeout ���Ƶ��õ�����:
 *   - Ϊ #AW_SEM_WAIT_FOREVER ʱ, ���ý��ᱻ����, ֱ�����ź������ͷŻ�ɾ��,
 *     ����ͨ������ֵ���жϵ��ý��:AW_OK -�ɹ���ȡ���ź�����-AW_ENXIO -�ź����Ѿ�
 *     ���ݻ�
 *
 *   - Ϊ #AW_SEM_NO_WAIT ʱ, ���ò��ᱻ����, ��������, ͨ������ֵ���жϵ��ý��;
 *     AW_OK -�ɹ���ȡ���ź���; -AW_EAGAIN -δ��ȡ���ź���,�Ժ�����;
 *     -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ����ֵΪ��ʱʱ��, ��ʱ�����г�ʱ������, ���趨�ĳ�ʱʱ�䵽��ʱ, ����δ��
 *     ȡ���ź���, ����÷���, ����ͨ������ֵ���жϵ��ý���� AW_OK -�ɹ���ȡ��
 *     �ź���; -AW_ETIME -��ʱ,δ��ȡ���ź���,�Ժ�����; -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ��������ֵΪ�Ƿ�����
 *
 * \param[in]   sem      �ź���ʵ��,�� AW_SEMB_DECL() ��
 *                       AW_SEMB_DECL_STATIC() ����
 * \param[in]   timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                       �ɺ��� aw_sys_clkrate_get()���, ��ʹ�� aw_ms_to_ticks()
 *                       ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                       #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 * \retval  -AW_EPERM  ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME  ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO  �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN ��ȡ�ź���ʧ��, �Ժ����� (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� AW_SEMB_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER);         // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = AW_SEMB_TAKE(sem, aw_ms_to_ticks(500));   //��ʱ�ȴ�,��ʱʱ�� 500ms
 *  if (ret == -AW_ETIME) {                         // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_SEMB_TAKE(sem, AW_SEM_NO_WAIT);        // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                        // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_GIVE(),
 *     AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_TAKE(sem, timeout)  AW_PSP_SEMB_TAKE(sem, timeout)

/**
 * \brief �ͷŶ������ź���
 *
 * �ͷ��ź���������и������ȼ��������ȡ�˸��ź���, �������׼����������, ����
 * ��������ռ���� AW_SEMB_GIVE() ���������ź���������(���ź������ͷ�, ����û
 * �������ȡ), ��û���κβ�����
 *
 * \param[in] sem �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMB_DECL()
 */
#define AW_SEMB_GIVE(sem)   AW_PSP_SEMB_GIVE(sem)

/**
 * \brief ���ö������ź���
 *
 * \param[in] sem         �������ź���ʵ��,�� AW_SEMB_DECL() �� 
 *                        AW_SEMB_DECL_STATIC() ����
 * \param[in] reset_value �������ź���������ֵ(0���߷�0)
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMB_RESET(sem, reset_value)   AW_PSP_SEMB_RESET(sem, reset_value)

/**
 * \brief ��ֹ�������ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param[in] sem �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC()
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_TERMINATE(sem)  AW_PSP_SEMB_TERMINATE(sem)

/**
 * \brief �������ź����Ƿ���Ч���ж�
 *
 * \param[in] sem  �������ź���ʵ��,�� AW_SEMB_DECL() ��
 *                 AW_SEMB_DECL_STATIC() ����
 *
 * \retval  TRUE       �������ź�����Ч
 * \retval  FALSE      �������ź�����Ч
 * \hideinitializer
 */
#define AW_SEMB_VALID(sem)          AW_PSP_SEMB_VALID(sem)

/**
 * \brief ���������ź�������Ϊ��Ч
 *
 * \param[in] sem  �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
#define AW_SEMB_SET_INVALID(sem)    AW_PSP_SEMB_SET_INVALID(sem)

/**
 * \brief ��ȡ�������ź���
 *
 * �������Ĺ����� AW_SEMB_TAKE() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_SEMB_INIT() ���ء�
 *
 * \param[in]   sem_id   �ź���ID,�� AW_SEMB_INIT()����
 * \param[in]   timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                       �ɺ��� aw_sys_clkrate_get()���, ��ʹ�� aw_ms_to_ticks()
 *                       ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                       #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 * \retval  -AW_EPERM  ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME  ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO  �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN ��ȡ�ź���ʧ��, �Ժ����� (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� AW_SEMB_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_DECL_STATIC(sem);                   // �����ź���ʵ��
 *  aw_semb_id_t  sem_id;                       // �ź���ID
 *
 *  sem_id = AW_SEMB_INI(sem);                  // ��ʼ���ź���, �õ��ź���ID
 *
 *  aw_semb_take(sem_id, AW_SEM_WAIT_FOREVER);  // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = aw_semb_take(sem_id, aw_ms_to_ticks()); // ��ʱʱ�� 500ms
 *  if (ret == -AW_ETIME) {                       // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_semb_take(sem, AW_SEM_NO_WAIT);    // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                    // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
aw_err_t aw_semb_take (aw_semb_id_t sem_id, int timeout);

/**
 * \brief �ͷŶ������ź���
 *
 * �������Ĺ����� AW_SEMB_GIVE() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_SEMB_INIT() ���ء�
 *
 * \param[in] sem_id �ź���ID,�� AW_SEMB_INIT()����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_terminate()
 * \hideinitializer
 */
aw_err_t aw_semb_give (aw_semb_id_t sem_id);

/**
 * \brief ���ö������ź���
 *
 * \param[in] sem_id      �������ź���ID,�� AW_SEMB_INIT()����
 * \param[in] reset_value �������ź���������ֵ(0���߷�0)
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semb_reset (aw_semb_id_t sem_id, int reset_value);

/**
 * \brief ��ֹ�������ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param[in] sem_id �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give()
 * \hideinitializer
 */
aw_err_t aw_semb_terminate (aw_semb_id_t sem_id);

/**
 * \brief �������ź����Ƿ���Ч���ж�
 *
 * \param[in] sem_id  �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC() ����
 *
 * \retval  TRUE       �������ź�����Ч
 * \retval  FALSE      �������ź�����Ч
 * \hideinitializer
 */
bool_t aw_semb_valid (aw_semb_id_t sem_id);

/**
 * \brief ���������ź�������Ϊ��Ч
 *
 * \param[in] p_sem_id  �ź���ʵ��,�� AW_SEMB_DECL() �� AW_SEMB_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
void aw_semb_set_invalid (aw_semb_id_t *p_sem_id);

/**
 *  \brief ��������ź���
 *
 * ���궨��һ�������ź���, �ڱ���ʱ����ź��������ڴ�ķ���; ������ʱ, ��Ҫ����
 * AW_SEMC_INIT() ����ź����ĳ�ʼ�������� AW_SEMC_TERMINATE()��ֹ�ź�����
 *
 * ����\a sem ֻ����Ϊ�� AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 * �� AW_SEMC_TERMINATE()�Ĳ�����
 *
 * AW_SEMC_INIT() �����ź�����\a sem_id, \a sem_id ��Ϊ���� aw_semc_take() ,
 * aw_semc_give() �� aw_semc_terminate()�Ĳ���; ��Щ�����Ĺ������Ӧ�ĺ�Ĺ���
 * ��ͬ, ��������, ����ʹ��\a sem_id ��Ϊ����,\a sem_id ������Ϊ�ź����ľ����
 * ��������֮�䴫�ݡ�
 *
 * ����ʹ�ñ��꽫�ź���ʵ��Ƕ�뵽��һ�����ݽṹ��,�����Ļ�,�����Ǹ�������ݶ���
 * ��ʱ����Զ�������ź���ʵ����ڴ����, ������ķ�����ʾ��
 *
 * \attention ���ź���û�п�ģ��(�ļ�)ʹ�õ������Ƽ�ʹ�� AW_SEMC_DECL_STATIC()
 *            ���汾�꣬�����ɱ���ģ��֮���ź���������Ⱦ��
 *
 * \attention �������÷��ⲻ, ��Ī�ں�����ʹ�ô˺��������ź�������Ϊ�ں����ڴ˺�
 *            ������ڴ�������ջ�ϣ�һ���������أ�������ڴ汻�Զ����ա�
 *            �ں����ڲ�ʹ�� AW_SEMC_DECL_STATIC()�������ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 *                �� AW_SEMC_TERMINATE() һ��ʹ�á�
 *
 * \par �����������÷�
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);
 *  AW_TASK_DECL_STATIC(task_b, 512);
 *
 *  AW_SEMC_DECL_STATIC(sem);
 *
 *  void func_a (void *arg)
 *  {
 *      while (1) {
 *          //...
 *          AW_SEMC_GIVE(sem);                      //�ͷ��ź���
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMC_TAKE(sem, AW_SEM_WAIT_FOREVER); //�ȴ��ź���
 *          //...
 *      }
 *  }
 *
 *  int main() {
 *
 *      // ��ʼ���ź���
 *      AW_SEMC_INIT(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(task_a,            // ����ʵ��
 *                   "task_a",          // ��������
 *                   5,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_a,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      AW_TASK_INIT(task_b,            // ����ʵ��
 *                   "task_b",          // ��������
 *                   6,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_b,            // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par ���������ź���ʵ��Ƕ����һ�����ݽṹ
 * \code
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);      // ����ʵ��task_a, ��ջ512
 *      AW_TASK_DECL(task_b, 512);      // ����ʵ��task_b, ��ջ512
 *      AW_SEMC_DECL(sem);              // �ź���ʵ��
 *      aw_semb_id_t sem_id;            // �ź���ID
 *  };
 *  struct my_struct   my_object;       // ���������ݶ���
 *
 *  void func_a (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          //...
 *          AW_SEMC_GIVE(p_myobj->sem);  //�ͷ��ź���(ʹ���ź���ʵ��)
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          // �ȴ��ź���(ʹ���ź���ID)
 *          aw_semc_take(p_myobj->sem_id, AW_SEM_WAIT_FOREVER);
 *          //...
 *      }
 *  }
 *
 *  int main() {
 *
 *      // ��ʼ���ź���
 *      my_object.sem_id = AW_SEMC_INIT(my_object.sem,
 *                                      AW_SEM_EMPTY,
 *                                      AW_SEM_Q_PRIORITY);
 *      if (my_object.sem_id == NULL) {
 *          return -1;                      // �ź�����ʼ��ʧ��
 *      }
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_object.task_a,      // ����ʵ��
 *                   "task_a",              // ��������
 *                   5,                     // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_a,                // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      AW_TASK_INIT(my_object.task_b,      // ����ʵ��
 *                   "task_b",              // ��������
 *                   6,                     // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_b,                // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //��ʱ20��
 *
 *      // AW_SEMC_TERMINATE(my_object.sem);    // ��ֹ�ź���
 *      // aw_semc_terminate(my_object.sem_id); // ��ֹ�ź���(ʹ���ź���ID)
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE,
 *     AW_SEMB_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_DECL(sem)       AW_PSP_SEMC_DECL(sem)

/**
 * \brief ��������ź���(��̬)
 *
 * ������ AW_SEMC_DECL() �Ĺ�����ͬ, ��������, AW_SEMC_DECL_STATIC() �ڶ���
 * �ź��������ڴ�ʱ, ʹ�ùؼ���\b static , ���һ��, ����Խ��ź���ʵ�����������
 * ����ģ����(�ļ���)�Ӷ�����ģ��֮����ź���������ͻ���������ں�����ʹ�ñ��궨
 * ���ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 *                �� AW_SEMC_TERMINATE() һ��ʹ�á�
 *
 * \par ����
 * �� AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE,
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_DECL_STATIC(sem)    AW_PSP_SEMC_DECL_STATIC(sem)

/**
 * \brief ���ü����ź���
 *
 * ��������һ�������ź���, �൱��ʹ�ùؼ�\b extern ����һ���ⲿ���š�
 * ���Ҫʹ����һ��ģ��(�ļ�)�ж�����ź���, ����ʹ�ñ���������ź���, Ȼ���
 * ���Բ������ź�������������ź���Ӧ����ʹ�� AW_SEMC_DECL()����ġ�
 *
 * \param[in] sem �ź���ʵ��
 *
 * \par ����
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMC_IMPORT(sem_x);      // �����ź��� sem_x
 *
 *  int func () {
 *      AW_SEMC_TAKE(sem_x);    // �ȴ��ź��� sem_x
 *  }
 * \endcode
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_IMPORT(sem)     AW_PSP_SEMC_IMPORT(sem)

/**
 * \brief �����ź�����ʼ��
 *
 * ��ʼ���� AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC()��̬����ļ����ź���,
 * ��Ƕ�뵽��һ�������ݶ����еĶ������ź�����
 *
 * �����ź�����ѡ������������ڴ��ź�����������Ŷӷ�ʽ, ���԰����������ȼ�
 * ���Ƚ��ȳ��ķ�ʽ�Ŷ�, ���Ƿֱ��Ӧ #AW_SEM_Q_PRIORITY �� #AW_SEM_Q_FIFO ��
 *
 * \param[in]  sem            �ź���ʵ��,�� AW_SEMC_DECL()��
 *                            AW_SEMC_DECL_STATIC()����
 * \param[in]  initial_count  ��ʼ����ֵ, �Ǹ���
 * \param[in]  options        ��ʼ��ѡ���־:
 *                                - #AW_SEM_Q_FIFO
 *                                - #AW_SEM_Q_PRIORITY
 *
 * \return �ɹ����ؼ����ź�����ID, ʧ���򷵻�NULL
 *
 * \par ʾ��
 *  ��ο� AW_SEMC_DECL()
 *
 * \sa AW_SEM_Q_FIFO, AW_SEM_Q_PRIORITY
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_TAKE(), AW_SEMC_GIVE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_INIT(sem, initial_count, options) \
            AW_PSP_SEMC_INIT(sem, initial_count, options)

/**
 * \brief ��ȡ�����ź���
 *
 * ��ȡ�ź���������ź�������ֵΪ0, �����񽫻ᱻ����ֱ���ź�����ÿ���(��������
 * ������ AW_SEMC_GIVE()�� aw_semc_give())������ź����Ѿ��ǿ��õ�(����ֵ > 0),
 * �򱾵��ý���ʹ����ֵ�� 1��
 *
 *  ���� \a timeout ���Ƶ��õ�����:
 *   - Ϊ #AW_SEM_WAIT_FOREVER ʱ, ���ý��ᱻ����, ֱ�����ź������ͷŻ�ɾ��,
 *     ����ͨ������ֵ���жϵ��ý��:AW_OK -�ɹ���ȡ���ź�����-AW_ENXIO -�ź����Ѿ�
 *     ���ݻ�
 *
 *   - Ϊ #AW_SEM_NO_WAIT ʱ,���ò��ᱻ����, ��������, ͨ������ֵ���жϵ��ý��;
 *     AW_OK -�ɹ���ȡ���ź���; -AW_EAGAIN -δ��ȡ���ź���,�Ժ�����;
 *     -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ����ֵΪ��ʱʱ��, ��ʱ�����г�ʱ������, ���趨�ĳ�ʱʱ�䵽��ʱ, ����δ��
 *     ȡ���ź���, ����÷���, ����ͨ������ֵ���жϵ��ý���� AW_OK -�ɹ���ȡ��
 *     �ź���; -AW_ETIME -��ʱ,δ��ȡ���ź���,�Ժ�����; -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ��������ֵΪ�Ƿ�����
 *
 * \param[in] sem      �ź���ʵ��,�� AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 * \param[in] timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                     �ɺ��� aw_sys_clkrate_get()���,  ��ʹ�� aw_ms_to_ticks()
 *                     ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                     #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK      �ɹ�
 * \retval  -AW_EINVAL  ������Ч
 * \retval  -AW_EPERM   ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME   ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO   �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN  ��ȡ�ź���ʧ��, �Ժ����� (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� AW_SEMC_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMC_TAKE(sem, AW_SEM_WAIT_FOREVER);         // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = AW_SEMC_TAKE(sem, aw_ms_to_ticks(500));   //��ʱ�ȴ�,��ʱʱ�� 500ms
 *  if (ret == -AW_ETIME) {                         // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_SEMC_TAKE(sem, AW_SEM_NO_WAIT);        // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                        // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_GIVE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_TAKE(sem, timeout)  AW_PSP_SEMC_TAKE(sem, timeout)

/**
 * \brief �ͷż����ź���
 *
 * �ͷ��ź���������и������ȼ��������ȡ�˸��ź���, �������׼����������, ����
 * ��������ռ���� aw_semc_give() ���������ź���������(���ź������ͷ�, ����û
 * �������ȡ), ��û���κβ�������������ʹ�ź����ļ���ֵ��1��
 *
 * \param[in] sem   �ź���ʵ��,�� AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_GIVE(sem)   AW_PSP_SEMC_GIVE(sem)

/**
 * \brief ���ü����ź���
 *
 * \param[in] sem         �����ź���ʵ��,�� AW_SEMC_DECL() �� 
 *                        AW_SEMC_DECL_STATIC() ����
 * \param[in] reset_value �����ź���������ֵ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_RESET(sem, reset_value )   AW_PSP_SEMC_RESET(sem, reset_value)

/**
 * \brief ��ֹ�����ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param[in]  sem  �ź���ʵ��,�� AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_TERMINATE(sem)  AW_PSP_SEMC_TERMINATE(sem)

/**
 * \brief �ź����Ƿ���Ч���ж�
 *
 * \param[in] sem  �ź���ʵ��,��  AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \retval  TRUE   �ź�����Ч
 * \retval  FALSE  �ź�����Ч
 * \hideinitializer
 */
#define AW_SEMC_VALID(sem)          AW_PSP_SEMC_VALID(sem)

/**
 * \brief �ź�������Ϊ��Ч
 *
 * \param[in] sem �ź���ʵ��,��  AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
#define AW_SEMC_SET_INVALID(sem)    AW_PSP_SEMC_SET_INVALID(sem)

/**
 * \brief ��ȡ�����ź���
 *
 * �������Ĺ����� AW_SEMC_TAKE() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_SEMC_INIT() ���ء�
 *
 * \param[in] sem_id   �ź���ID, �� AW_SEMC_INIT()����
 * \param[in] timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                     �ɺ��� aw_sys_clkrate_get()���, ��ʹ�� aw_ms_to_ticks()
 *                     ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                     #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 * \retval  -AW_EPERM  ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME  ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO  �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN ��ȡ�ź���ʧ��, �Ժ����� (timeout = AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� #AW_SEMC_DECL() �� #AW_SEMC_DECL_STATIC()
 * \code
 *  AW_SEMC_DECL_STATIC(sem);                       // �����ź���ʵ��
 *  aw_semc_id_t  sem_id;                           // �ź���ID
 *
 *  sem_id = AW_SEMC_INI(sem);                      // ��ʼ���ź���,�õ��ź���ID
 *
 *  aw_semc_take(sem_id, AW_SEM_WAIT_FOREVER);      // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = aw_semc_take(sem_id, aw_ms_to_ticks(500));// ��ʱʱ�� 500ms
 *  if (ret == -AW_ETIME) {                         // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_semc_take(sem, AW_SEM_NO_WAIT);        // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                        // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semc_take (aw_semc_id_t sem_id, int timeout);

/**
 * \brief �ͷż����ź���
 *
 * �������Ĺ����� AW_SEMC_GIVE() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_SEMC_INIT() ���ء�
 *
 * \param[in] sem_id �ź���ID, �� AW_SEMC_INIT()����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semc_give (aw_semc_id_t sem_id);

/**
 * \brief ���ü����ź���
 *
 * �������Ĺ����� AW_SEMC_RESET() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_SEMC_INIT() ���ء�
 *
 * \param[in] sem_id      �����ź���ID, �� AW_SEMC_INIT()����
 * \param[in] reset_value �����ź���������ֵ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semc_reset (aw_semc_id_t sem_id, int reset_value );

/**
 * \brief ��ֹ�����ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param[in] sem_id �ź���ID, �� AW_SEMC_INIT()����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give()
 * \hideinitializer
 */
aw_err_t aw_semc_terminate (aw_semc_id_t sem_id);

/**
 * \brief �ź����Ƿ���Ч���ж�
 *
 * \param[in] sem_id �ź���ʵ��,��  AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \retval  TRUE   �ź�����Ч
 * \retval  FALSE  �ź�����Ч
 * \hideinitializer
 */
bool_t aw_semc_valid (aw_semc_id_t sem_id);

/**
 * \brief �ź�������Ϊ��Ч
 *
 * \param[in] p_sem_id �ź���ʵ��,��  AW_SEMC_DECL() �� AW_SEMC_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
void aw_semc_set_invalid (aw_semc_id_t *p_sem_id);

/**
 *  \brief ���廥���ź���
 *
 * ���궨��һ�������ź���, �ڱ���ʱ����ź��������ڴ�ķ���; ������ʱ, ��Ҫ����
 * AW_MUTEX_INIT() ����ź����ĳ�ʼ�������� AW_MUTEX_TERMINATE()��ֹ
 * �ź������ź�������ʼ��Ϊ��״̬��
 *
 * ����\a sem ֻ����Ϊ�� AW_MUTEX_INIT(), AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK() ��
 * AW_MUTEX_TERMINATE()�Ĳ�����
 *
 * AW_MUTEX_INIT() �����ź�����\a sem_id, \a sem_id ��Ϊ���� aw_mutex_lock() ,
 * aw_mutex_unlock() �� aw_mutex_terminate()�Ĳ���; ��Щ�����Ĺ������Ӧ�ĺ��
 * ������ͬ, ��������, ����ʹ��\a sem_id ��Ϊ����,\a sem_id ������Ϊ�ź����ľ��
 * �ں�������֮�䴫�ݡ�
 *
 * ����ʹ�ñ��꽫�ź���ʵ��Ƕ�뵽��һ�����ݽṹ��,�����Ļ�,�����Ǹ�������ݶ���
 * ��ʱ����Զ�������ź���ʵ����ڴ����, ������ķ�����ʾ��
 *
 * \attention ���ź���û�п�ģ��(�ļ�)ʹ�õ�����,�Ƽ�ʹ�� AW_MUTEX_DECL_STATIC()
 *            ���汾�꣬�����ɱ���ģ��֮���ź���������Ⱦ��
 *
 * \attention �������÷��ⲻ, ��Ī�ں�����ʹ�ô˺��������ź�������Ϊ�ں����ڴ˺�
 *            ������ڴ�������ջ�ϣ�һ���������أ�������ڴ汻�Զ����ա�
 *            �ں����ڲ�ʹ�� AW_MUTEX_DECL_STATIC()�������ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_MUTEX_INIT(), AW_MUTEX_LOCK(),
 *                AW_MUTEX_UNLOCK() �� AW_MUTEX_TERMINATE() һ��ʹ�á�
 *
 * \par �����������÷�, ������Դ�ķ���
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);
 *  AW_TASK_DECL_STATIC(task_b, 512);
 *
 *  AW_SEMC_DECL_STATIC(mutex);
 *
 *  void public_service (void)
 *  {
 *      AW_MUTEX_LOCK(mutex);
 *      //... Ҫ�����ĳ������
 *      AW_MUTEX_UNLOCK(mutex);
 *  }
 *  void func_proccess (void *arg)
 *  {
 *      while (1) {
 *          public_service();           // ���ʹ�������
 *          aw_mdelay(50);              // ��ʱ50ms
 *      }
 *  }
 *
 *  int main() {
 *
 *      // ��ʼ���ź���
 *      AW_MUTEX_INIT(sem, AW_SEM_Q_PRIORITY);
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(task_a,            // ����ʵ��
 *                   "task_a",          // ��������
 *                   5,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_proccess,     // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      AW_TASK_INIT(task_b,            // ����ʵ��
 *                   "task_b",          // ��������
 *                   6,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_proccess,     // ������ں���
 *                   NULL);             // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par ���������ź���ʵ��Ƕ����һ�����ݽṹ
 * \code
 *  #include "aw_sem.h"
 *
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);      // ����ʵ��task_a, ��ջ512
 *      AW_TASK_DECL(task_b, 512);      // ����ʵ��task_b, ��ջ512
 *      AW_MUTEX_DECL(mutex);           // �ź���ʵ��
 *      aw_mutex_id_t mutex_id;         // �ź���ID
 *  };
 *  struct my_struct   my_object;       // ���������ݶ���
 *
 *  void public_service (struct my_struct *p_myobj)
 *  {
 *      aw_mutex_lock(p_myobj->mutex_id);
 *      //... Ҫ�����ĳ������
 *      aw_mutex_unlock(p_myobj->mutex_id);
 *  }
 *
 *  void func_proccess (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          public_service(p_myobj);        // ���ʹ�������
 *          aw_mdelay(50);                  // ��ʱ50ms
 *      }
 *  }
 *
 *  int main() {
 *
 *      // ��ʼ���ź���
 *      my_object.mutex_id = AW_MUTEX_INIT(my_object.mutex, AW_SEM_Q_PRIORITY);
 *      if (my_object.mutex_id == NULL) {
 *          return -1;                      // �ź�����ʼ��ʧ��
 *      }
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_object.task_a,      // ����ʵ��
 *                   "task_a",              // ��������
 *                   5,                     // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_proccess,         // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      AW_TASK_INIT(my_object.task_b,      // ����ʵ��
 *                   "task_b",              // ��������
 *                   6,                     // �������ȼ�
 *                   512,               // �����ջ��С
 *                   func_proccess,         // ������ں���
 *                   (void *)&my_object);   // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //��ʱ20��
 *
 *      // AW_SEMC_TERMINATE(my_object.mutex);    // ��ֹ�ź���
 *      // aw_semc_terminate(my_object.mutex_id); // ��ֹ�ź���(ʹ���ź���ID)
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(), AW_MUTEX_LOCK(),
 *     AW_MUTEX_UNLOCK, AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_DECL(sem)       AW_PSP_MUTEX_DECL(sem)

/**
 * \brief ���廥���ź���(��̬)
 *
 * ������ AW_MUTEX_DECL() �Ĺ�����ͬ, ��������, AW_MUTEX_DECL_STATIC() �ڶ���
 * �ź��������ڴ�ʱ, ʹ�ùؼ���\b static ,���һ��, ����Խ��ź���ʵ�����������
 * ����ģ����(�ļ���), �Ӷ�����ģ��֮����ź���������ͻ���������ں�����ʹ�ñ���
 * �����ź�����
 *
 * \param[in] sem �ź���ʵ��, �� AW_MUTEX_INIT(), AW_MUTEX_LOCK(),
 *                AW_MUTEX_UNLOCK() �� AW_MUTEX_TERMINATE() һ��ʹ��
 *
 * \par ����
 * �� AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_INIT(), AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK,
 *     AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_DECL_STATIC(sem)    AW_PSP_MUTEX_DECL_STATIC(sem)

/**
 * \brief ���û����ź���
 *
 * ��������һ�������ź���, �൱��ʹ�ùؼ� \b extern ����һ���ⲿ���š�
 * ���Ҫʹ����һ��ģ��(�ļ�)�ж�����ź���, ����ʹ�ñ���������ź���, Ȼ���
 * ���Բ������ź�������������ź���Ӧ����ʹ�� AW_MUTEX_DECL()����ġ�
 *
 * \param[in] sem ����ʵ��
 *
 * \par ����
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_MUTEX_IMPORT(sem_x);     // �����ź��� sem_x
 *
 *  int func () {
 *      AW_MUTEX_LOCK(sem_x);   // �ȴ��ź��� sem_x
 *  }
 * \endcode
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_IMPORT(sem)     AW_PSP_MUTEX_IMPORT(sem)

/**
 * \brief �����ź�����ʼ��
 *
 * ��ʼ���� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC()��̬����Ļ����ź���,
 * ��Ƕ�뵽��һ�������ݶ����еĶ������ź�����
 *
 * �����ź�����ѡ������������ڴ��ź�����������Ŷӷ�ʽ, ���԰����������ȼ�
 * ���Ƚ��ȳ��ķ�ʽ�Ŷ�, ���Ƿֱ��Ӧ #AW_SEM_Q_PRIORITY �� #AW_SEM_Q_FIFO ��
 *
 * ѡ�� #AW_SEM_DELETE_SAFE �����˵�ǰӵ�д��ź�������������������ɾ������ѡ��
 * �����Ĳ�����Ϊÿ�� aw_mutex_lock() ���һ�� AW_TASK_SAFE() ����, Ϊÿ��
 * aw_mutex_unlock() ���һ�� AW_TASK_UNSAFE() ���á�
 *
 * ѡ�� #AW_SEM_INVERSION_SAFE ������ϵͳ�������ȼ���ת, ��ѡ������
 * #AW_SEM_Q_PRIORITY �Ŷӷ�ʽһ��ʹ�á�
 *
 * \param[in]  sem      �ź���ʵ��,�� AW_MUTEX_DECL()�� AW_MUTEX_DECL_STATIC()����
 * \param[in]  options  ��ʼ��ѡ���־("()"��ʾ��ѡ):
 *                          - #AW_SEM_Q_FIFO | (#AW_SEM_DELETE_SAFE)
 *                          - #AW_SEM_Q_PRIORITY | (#AW_SEM_DELETE_SAFE) |
                              (#AW_SEM_INVERSION_SAFE)
 *
 * \return �ɹ����ػ����ź�����ID, ʧ���򷵻�NULL
 *
 * \par ʾ��
 *  ��ο� AW_MUTEX_DECL()
 *
 * \sa AW_SEM_Q_FIFO, AW_SEM_Q_PRIORITY
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_LOCK(),
 *     AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_INIT(sem, options) \
            AW_PSP_MUTEX_INIT(sem, options)

/**
 * \brief ��ȡ�����ź���
 *
 * ��ȡ�ź���������ź���Ϊ��, �����񽫻ᱻ����ֱ���ź�����ÿ���(�����������
 * �� AW_MUTEX_UNLOCK()�� aw_mutex_unlock())������ź����Ѿ��ǿ��õ�, �򱾵���
 * ������ո��ź���, �����������ܻ�ȡ�����ź���, ֱ�����õ������ͷŴ��ź�����
 *
 * ���ɾ����ȫѡ��(#AW_SEM_DELETE_SAFE)��ʹ��, �򱾺�������һ��������
 * AW_TASK_SAFE()���á�
 *
 *  ���� \a timeout ���Ƶ��õ�����:
 *   - Ϊ #AW_SEM_WAIT_FOREVER ʱ, ���ý��ᱻ����, ֱ�����ź������ͷŻ�ɾ��,
 *     ����ͨ������ֵ���жϵ��ý��:AW_OK -�ɹ���ȡ���ź�����-AW_ENXIO -�ź����Ѿ�
 *     ���ݻ�
 *
 *   - Ϊ #AW_SEM_NO_WAIT ʱ,���ò��ᱻ����, ��������, ͨ������ֵ���жϵ��ý��;
 *     AW_OK -�ɹ���ȡ���ź���; -AW_EAGAIN -δ��ȡ���ź���,�Ժ�����;
 *     -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ����Ϊ��ʱʱ��, ��ʱ�����г�ʱ������, ���趨�ĳ�ʱʱ�䵽��ʱ, ����δ��
 *     ȡ���ź���, ����÷���, ����ͨ������ֵ���жϵ��ý���� AW_OK -�ɹ���ȡ��
 *     �ź���; -AW_ETIME -��ʱ,δ��ȡ���ź���,�Ժ�����; -AW_ENXIO -�ź����Ѿ�����ֹ
 *
 *   - ��������ֵΪ�Ƿ�����
 *
 * \param[in] sem      �ź���ʵ��,�� AW_MUTEX_DECL()�� AW_MUTEX_DECL_STATIC() ����
 * \param[in] timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                     �ɺ��� aw_sys_clkrate_get()���, ��ʹ�� aw_ms_to_ticks()
 *                     ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                     #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 * \retval  -AW_EPERM  ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME  ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO  �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN ��ȡ�ź���ʧ��, �Ժ����� (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� AW_MUTEX_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_MUTEX_LOCK(sem, AW_SEM_WAIT_FOREVER);        // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = AW_MUTEX_LOCK(sem, aw_ms_to_ticks(500));  //��ʱ�ȴ�,��ʱʱ��500ms
 *  if (ret == -AW_ETIME) {                         // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_MUTEX_LOCK(sem, AW_SEM_NO_WAIT);       // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                        // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_LOCK(sem, timeout)  AW_PSP_MUTEX_LOCK(sem, timeout)

/**
 * \brief �ͷŻ����ź���
 *
 * �ͷ��ź���������и������ȼ��������ȡ�˸��ź���, �������׼����������, ����
 * ��������ռ���� AW_MUTEX_UNLOCK() ���������ź���������(���ź������ͷ�,
 * ����û�������ȡ), ��û���κβ�����
 *
 * ���ɾ����ȫѡ��(#AW_SEM_DELETE_SAFE)��ʹ��, �򱾺�������һ��������
 * AW_TASK_UNSAFE()���á�
 *
 * \param[in] sem   �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_MUTEX_DECL()
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_UNLOCK(sem)   AW_PSP_MUTEX_UNLOCK(sem)

/**
 * \brief ��ֹ�����ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param[in] sem   �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_TERMINATE(sem)  AW_PSP_MUTEX_TERMINATE(sem)


/**
 * \brief �����ź����Ƿ���Ч���ж�
 *
 * \param[in] sem  �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \retval  TRUE   �ź�����Ч
 * \retval  FALSE  �ź�����Ч
 * \hideinitializer
 */
#define AW_MUTEX_VALID(sem)          AW_PSP_MUTEX_VALID(sem)

/**
 * \brief �����ź�������Ϊ��Ч
 *
 * \param[in]  sem  �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
#define AW_MUTEX_SET_INVALID(sem)    AW_PSP_MUTEX_SET_INVALID(sem)

/**
 * \brief ��ȡ�����ź���
 *
 * �������Ĺ����� AW_MUTEX_LOCK() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_MUTEX_INIT() ���ء�
 *
 * \param   sem_id   �ź���ID,�� AW_MUTEX_INIT()����
 * \param   timeout  ���ȴ�ʱ��(��ʱʱ��), ��λ��ϵͳ����, ϵͳʱ�ӽ���Ƶ��
 *                   �ɺ��� aw_sys_clkrate_get()���, ��ʹ�� aw_ms_to_ticks()
 *                   ������ת��Ϊ������; #AW_SEM_NO_WAIT Ϊ������;
 *                   #AW_SEM_WAIT_FOREVER Ϊһֱ�ȴ�, �޳�ʱ
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 * \retval  -AW_EPERM  ������Ĳ���,���ж��е����˱�����
 * \retval  -AW_ETIME  ��ȡ�ź�����ʱ
 * \retval  -AW_ENXIO  �ź����Ѿ�����ֹ
 * \retval  -AW_EAGAIN ��ȡ�ź���ʧ��, �Ժ����� (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par ����
 * ���෶����ο� AW_MUTEX_DECL()
 * \code
 *  AW_MUTEX_DECL_STATIC(sem);                  // �����ź���ʵ��
 *  aw_mutex_id_t  sem_id;                      // �ź���ID
 *
 *  sem_id = AW_MUTEX_INI(sem);                 // ��ʼ���ź���, �õ��ź���ID
 *
 *  aw_mutex_lock(sem_id, AW_SEM_WAIT_FOREVER);         // ���õȴ�
 *
 *  aw_err_t ret;
 *  ret = aw_mutex_lock(sem_id, aw_ms_to_ticks(500));   // ��ʱʱ�� 500ms
 *  if (ret == -AW_ETIME) {                             // �ȴ��ź�����ʱ
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_mutex_lock(sem, AW_SEM_NO_WAIT);           // �޵ȴ�
 *  if (ret == -AW_EAGAIN) {                            // δ��ȡ���ź���
 *      //...
 *  }
 * \endcode
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
aw_err_t aw_mutex_lock (aw_mutex_id_t sem_id, int timeout);

/**
 * \brief �ͷŻ����ź���
 *
 * �������Ĺ����� AW_MUTEX_UNLOCK() ��ͬ, �������, ������ʹ��\a sem_id ��Ϊ������
 * \a sem_id �� AW_MUTEX_INIT() ���ء�
 *
 * \param   sem_id  �ź���ID,�� AW_MUTEX_INIT()����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_terminate()
 * \hideinitializer
 */
aw_err_t aw_mutex_unlock (aw_mutex_id_t sem_id);

/**
 * \brief ��ֹ�����ź���
 *
 * ��ֹ�ź������κεȴ����ź��������񽫻������, ������ -AW_ENXIO ���˺��������ͷ�
 * �ź�����ص��κ��ڴ档
 *
 * \param   sem_id  �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�
 * \retval  -AW_EINVAL ������Ч
 *
 * \par ����
 * ��ο� AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock()
 * \hideinitializer
 */
aw_err_t aw_mutex_terminate (aw_mutex_id_t sem_id);

/**
 * \brief �����ź����Ƿ���Ч���ж�
 *
 * \param[in] sem_id �ź���ʵ��,�� AW_MUTEX_DECL() �� AW_MUTEX_DECL_STATIC() ����
 *
 * \retval  TRUE   �ź�����Ч
 * \retval  FALSE  �ź�����Ч
 * \hideinitializer
 */
bool_t aw_mutex_valid (aw_mutex_id_t sem_id);

/**
 * \brief �����ź�������Ϊ��Ч
 *
 * \param[in] p_sem_id �ź���ʵ��,�� AW_MUTEX_DECL() ��
 *                     AW_MUTEX_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
void aw_mutex_set_invalid (aw_mutex_id_t *p_sem_id);

/** \cond */

#define AW_SEL_WRITE    AW_PSP_SEL_WRITE /**< \brief д��־ */
#define AW_SEL_READ     AW_PSP_SEL_READ  /**< \brief ����־ */

/**
 * \brief ���廽���б�
 */
#define AW_SEL_WKUP_LIST_DECL(list)       AW_PSP_SEL_WKUP_LIST_DECL(list)

/**
 * \brief ��ʼ�������б�
 */
#define AW_SEL_WKUP_LIST_INIT(list)       AW_PSP_SEL_WKUP_LIST_INIT(list)

/**
 * \brief ��������
 */
#define AW_SEL_WAKEUP_All(list, sel_flag) AW_PSP_SEL_WAKEUP_All(list, sel_flag)

/** \endcond */

/** @} grp_aw_if_sem */

#ifdef __cplusplus
}
#endif

#endif /* __AW_SEMAPHORE */

/* end of file */
