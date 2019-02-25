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
 * \brief  ������ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� aw_task.h
 *
 * \note ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7��������ȼ�Ϊ0
 *
 * \par ��ʾ��
 * \code
 *  #include "aworks.h"
 *  #include "aw_task.h"
 *
 *  AW_TASK_DECL(my_task, 256);                     // ��������ʵ�� my_task
 *
 *  // ������ں���
 *  void taska (void *p_arg)
 *  {
 *      while (1) {
 *          // ...
 *          aw_task_delay(aw_sys_clkrate_get());    // ��ʱ 1S
 *      }
 *  }
 *
 *  int main()
 *  {
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_task,                       // ����ʵ��
 *                   "taskname",                    // ��������
 *                   5,                             // �������ȼ�
 *                   taska,                         // ������ں���
 *                   (void*)1);                     // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_task);
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_sys_clkrate_get() * 20);
 *
 *      // ��ֹ����
 *      AW_TASK_TERMINATE(my_task);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.11 17-09-05  anu, refine the description
 * - 1.10 13-02-28  zen, refine the description
 * - 1.00 12-10-23  liangyaozhan, first implementation
 * \endinternal
 */

#ifndef __AW_TASK_H
#define __AW_TASK_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_task
 * \copydoc aw_task.h
 * @{
 */

#include "aw_psp_task.h"

typedef aw_psp_task_id_t    aw_task_id_t;           /**< ����ID     */
#define AW_TASK_ID_INVALID  AW_PSP_TASK_ID_INVALID  /**< ��Ч����ID  */

/**
 * \brief ��������
 *
 * ���궨��һ�������ڱ���ʱ������������ڴ�ķ���; ������ʱ����Ҫ�ֱ����
 * AW_TASK_INIT()�� AW_TASK_STARTUP()�������ĳ�ʼ��������������
 * AW_TASK_TERMINATE()��ֹ����
 *
 * ���� \a task ֻ����Ϊ�� AW_TASK_INIT()�� AW_TASK_STARTUP()��
 * AW_TASK_TERMINATE()�Ĳ�����
 *
 * AW_TASK_INIT()���������\a task_id,\a task_id ��Ϊ���� aw_task_startup() ��
 * aw_task_terminate()�Ĳ���; ��Щ�����Ĺ������Ӧ�ĺ�Ĺ�����ͬ���������ڣ�����
 * ʹ��\a task_id ��Ϊ������\a task_id ������Ϊ����ľ���ں�������֮�䴫�ݡ�
 *
 * ����ʹ�ñ��꽫����ʵ��Ƕ�뵽��һ�����ݽṹ�У������Ļ������������ݶ����ʱ
 * ����Զ����������ʵ����ڴ���䣬������ķ�����ʾ��
 *
 * \attention ������û�п�ģ��(�ļ�)ʹ�õ������Ƽ�ʹ�� AW_TASK_DECL_STATIC()
 *            ���汾�꣬�����ɱ���ģ��֮������������Ⱦ��
 *
 * \attention �������÷��ⲻ, ��Ī�ں�����ʹ�ô˺�������������Ϊ�ں����ڴ˺��
 *            ����ڴ�������ջ�ϣ�һ���������أ�������ڴ汻�Զ����ա��ں����ڲ�
 *            ʹ�� AW_TASK_DECL_STATIC()����������
 *
 * \param[in] task          ����ʵ�壬�� AW_TASK_INIT() �� AW_TASK_STARTUP()��
 *                      AW_TASK_TERMINATE() һ��ʹ�á�
 *
 * \param[in] stack_size    �����ջ��С���˲�������� AW_TASK_INIT() һ��!
 *
 * \par �����������÷�
 * \code
 *  #include "aw_task.h"
 *
 *  AW_TASK_DECL(my_task, 512);         // ��������ʵ�� my_task
 *
 *  // ������ں���
 *  void taska (void *p_arg)
 *  {
 *      while (1) {
 *          // ...
 *          aw_task_delay(aw_sys_clkrate_get());    // ��ʱ 1S
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_task,       // ����ʵ��
 *                   "taskname",    // ��������
 *                   5,             // �������ȼ�
 *                   512,           // �����ջ��С(�� AW_TASK_DECL()һ��)
 *                   taska,         // ������ں���
 *                   (void*)1);     // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_task);
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_sys_clkrate_get() * 20);
 *
 *      // ��ֹ����
 *      AW_TASK_TERMINATE(my_task);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par ������������ʵ��Ƕ����һ�����ݽṹ
 * \code
 *  struct my_struct {
 *      int my_data1;
 *      int my_data2;
 *      AW_TASK_DECL(my_task, 512);     // ����ʵ��my_task, ��ջ512
 *  };
 *  struct my_struct   my_object;       // ���������ݶ���
 *
 *  int main ()
 *  {
 *
 *      //...
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_object.my_task, // ����ʵ��
 *                   "taskname",        // ��������
 *                   5,                 // �������ȼ�
 *                   512,               // �����ջ��С
 *                   taska,             // ������ں���
 *                   (void*)1);         // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_object.my_task);
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_sys_clkrate_get() * 20);
 *
 *      // ��ֹ����
 *      AW_TASK_TERMINATE(my_object.my_task);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa AW_TASK_DECL_STATIC(), AW_TASK_INIT(), AW_TASK_STARTUP(),
 *     AW_TASK_TERMINATE()
 * \hideinitializer
 */
#define AW_TASK_DECL(task, stack_size)  \
            AW_PSP_TASK_DECL(task, stack_size)

/**
 * \brief ��������(��̬)
 *
 * ������ AW_TASK_DECL() �Ĺ�����ͬ���������ڣ�AW_TASK_DECL_STATIC() �ڶ���
 * ���������ڴ�ʱ��ʹ�ùؼ��� \b static �����һ��������Խ�����ʵ���������������
 * ģ����(�ļ���)�Ӷ�����ģ��֮�������������ͻ;�������ں�����ʹ�ñ��궨������
 *
 * \param[in] task          ����ʵ�壬�� AW_TASK_INIT() �� AW_TASK_STARTUP()��
 *                          AW_TASK_TERMINATE() һ��ʹ�á�
 *
 * \param[in] stack_size    ����ջ��С, �˲�������� AW_TASK_INIT() һ��!
 *
 * \par ����
 * \code
 *  #include "aw_task.h"
 *
 *  // ������ں���
 *  void taska (void *p_arg)
 *  {
 *      while (1) {
 *          // ...
 *          aw_task_delay(aw_sys_clkrate_get());    // ��ʱ 1S
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // ��������ʵ�� my_task
 *      AW_TASK_DECL_STATIC(my_task, 512);
 *
 *      // ��ʼ������
 *      AW_TASK_INIT(my_task,       // ����ʵ��
 *                   "taskname",    // ��������
 *                   5,             // �������ȼ�
 *                   512,           // �����ջ��С
 *                   taska,         // ������ں���
 *                   (void*)1);     // ������ڲ���
 *
 *      // ��������
 *      AW_TASK_STARTUP(my_task);
 *
 *      // ��ʱ 20S.
 *      aw_task_delay(aw_sys_clkrate_get() * 20);
 *
 *      // ��ֹ����
 *      AW_TASK_TERMINATE(my_task);
 *
 *      return 0;
 *  }
 *  \endcode
 *
 * \sa AW_TASK_DECL(), AW_TASK_INIT(), AW_TASK_STARTUP(), AW_TASK_TERMINATE()
 * \hideinitializer
 */
#define AW_TASK_DECL_STATIC(task, stack_size) \
            AW_PSP_TASK_DECL_STATIC(task, stack_size)

/**
 * \brief ��������
 *
 * ��������һ�������൱��ʹ�ùؼ� \b extern ����һ���ⲿ���š����Ҫʹ����һ��
 * ģ��(�ļ�)�ж������������ʹ�ñ������������Ȼ��Ϳ��Բ��������񡣱�����
 * ����Ӧ����ʹ�� AW_TASK_DECL() ����ġ�
 *
 * \param[in] task  ����ʵ��
 *
 * \par ����
 * \code
 *  #include "aw_task.h"
 *
 *  AW_TASK_IMPORT(his_task);    // �������� his_task
 *
 *  int func ()
 *  {
 *      AW_TASK_TERMINATE(his_task); // ��ֹ���� his_task
 *  }
 *  \endcode
 *
 * \sa AW_TASK_DECL(), AW_TASK_INIT(), AW_TASK_STARTUP(), AW_TASK_TERMINATE()
 * \hideinitializer
 */
#define AW_TASK_IMPORT(task)    AW_PSP_TASK_IMPORT(task)

/**
 * \brief ��ʼ������
 *
 * \param[in] task      ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 * \param[in] name      ��������
 * \param[in] priority  �������ȼ�, 0 ���ȼ����, ������ȼ���ͨ��
 *                      aw_task_lowest_priority() ��ȡ��
 *                      ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7, ������ȼ�Ϊ0��
 *
 * \param[in] stack_size    �����ջ��С���˲�������� AW_TASK_DECL() һ��!
 * \param[in] func      ��ں���
 * \param[in] arg       ��ڲ���
 *
 * \return          �ɹ����������ID��ʧ���򷵻�NULL
 *
 * \note ���� \a priority ���û���������ȼ���ϵͳ�������������ȼ����ڲ�ϵͳ����
 * ���豸����ʹ�á�������Щϵͳ������豸������ʹ�ú� AW_TASK_SYS_PRIORITY(pri)
 * ��ʾϵͳ�������ȼ���
 *
 * \par ����
 * �� AW_TASK_DECL() �� AW_TASK_DECL_STATIC()
 *
 * \sa AW_TASK_DECL(), AW_TASK_DECL_STATIC(), AW_TASK_INIT(), AW_TASK_STARTUP(),
 *  AW_TASK_TERMINATE()
 * \hideinitializer
 */
#define AW_TASK_INIT(task, name, priority, stack_size, func, arg)    \
            AW_PSP_TASK_INIT(task, name, priority, stack_size, func, arg)

/**
 * \brief ϵͳ�������ȼ�
 *
 * ϵͳ�������������ȼ����ڲ�ϵͳ������豸����ʹ��,������Щϵͳ������豸����,
 * �����漰���ȼ���API��������ʹ�ú� AW_TASK_SYS_PRIORITY(pri) ����ʾϵͳ�����
 * ���ȼ�,\a pri Ϊ 0 ʱ���ȼ����,\a pri ֵԽ�����ȼ�Խ�͡�
 * ����ϵͳ�������ȼ��������û��������ȼ���
 *
 * \param[in] priority  �������ȼ�, 0 ���ȼ����, ������ȼ���ͨ��
 *                      aw_task_lowest_priority() ��ȡ��
 *                      ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7, ������ȼ�Ϊ0��
 *
 * \par ʾ��
 * \code
 *  #include "aw_task.h"
 *
 *  AW_TASK_DECL_STATIC(sys_task, 512);
 *
 *  AW_TASK_INIT(sys_task,
 *               "sys_task",
 *               AW_TASK_SYS_PRIORITY(0),   // ���ϵͳ���ȼ�
 *               512,               // �����ջ��С
 *               sys_task_entry,
 *               NULL;
 * \endcode
 * \hideinitializer
 */
#define AW_TASK_SYS_PRIORITY(priority)  \
            AW_PSP_TASK_SYS_PRIORITY(priority)

/**
 * \brief ��������
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \par ����
 * \code
 *  #include "aw_task.h"
 *
 *  // ������ں���
 *  void taska (void *p_arg)
 *  {
 *      while (1) {
 *          // ...
 *          aw_task_delay(aw_sys_clkrate_get());    // ��ʱ 1S
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      aw_task_id_t task_id;   // ����ID
 *
 *      // ��������ʵ�� my_task
 *      AW_TASK_DECL_STATIC(my_task, 512);
 *
 *      // ��ʼ������
 *      task_id = AW_TASK_INIT(my_task,       // ����ʵ��
 *                             "taskname",    // ��������
 *                             5,             // �������ȼ�
 *                             512,           // �����ջ��С
 *                             taska,         // ������ں���
 *                             (void*)1);     // ������ڲ���
 *
 *      if (task_id != NULL) {
 *
 *          // ��������
 *          aw_task_startup(task_id);
 *
 *          // ��ʱ 20S.
 *          aw_task_delay(aw_sys_clkrate_get() * 20);
 *
 *          // ��ֹ����
 *          aw_task_terminate(task_id);
 *      }
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \sa AW_TASK_DECL(), AW_TASK_DECL_STATIC(), AW_TASK_INIT(), AW_TASK_STARTUP(),
 *  AW_TASK_TERMINATE()
 * \hideinitializer
 */
#define AW_TASK_STARTUP(task)           AW_PSP_TASK_STARTUP(task)

/**
 * \brief ��ֹ����
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ���ֹ
 * \retval  -AW_EPERM  ��ֹ�������ܾ�
 * \hideinitializer
 */
#define AW_TASK_TERMINATE(task)         AW_PSP_TASK_TERMINATE(task)

/**
 * \brief �����Ƿ���Ч���ж�
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \retval  TRUE       ������Ч
 * \retval  FALSE      ������Ч
 * \hideinitializer
 */
#define AW_TASK_VALID(task)             AW_PSP_TASK_VALID(task)

/**
 * \brief ����������Ϊ��Ч
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \return ��
 * \hideinitializer
 */
#define AW_TASK_SET_INVALID(task)       AW_PSP_TASK_SET_INVALID(task)

/**
 * \brief �����ӳٵ�tick��
 *
 * \param[in] tick  �δ���
 *
 * \return ��
 * \hideinitializer
 */
#define AW_TASK_DELAY(tick)             AW_PSP_TASK_DELAY(tick)

/**
 * \brief ��������
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ�����
 * \retval  -AW_EPERM  ����������ܾ�
 * \hideinitializer
 */
#define AW_TASK_SUSPEND(task)           AW_PSP_TASK_SUSPEND(task)

/**
 * \brief �ָ�����
 *
 * \param[in] task  ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 *
 * \retval   AW_OK     �ɹ��ָ�
 * \retval  -AW_EPERM  �ָ��������ܾ�
 * \hideinitializer
 */
#define AW_TASK_RESUME(task)            AW_PSP_TASK_RESUME(task)

/**
 * \brief �ȴ���һ�������˳�
 *
 * \param[in] task ����ID���� AW_TASK_INIT() ���أ�
 * \param[out] p_status p_statusָ��һ����ַ�����ڴ�ŵȴ�������˳���

 * \retval AW_OK �ȴ�������ɹ��˳�
 * \retval ���Ĵ�����
 * \hideinitializer
 */
#define AW_TASK_JOIN(task,p_status)     AW_PSP_TASK_JOIN(task,p_status)

/**
 * \brief ʹ�������������ɾ����ȫģʽ
 *
 * ����ɾ��������������������񽫻�������ֱ��������������� AW_TASK_UNSAFE()
 * �˳�ɾ����ȫģʽ��
 *
 * \return  AW_OK   ���ǳɹ�
 * \hideinitializer
 */
#define AW_TASK_SAFE()                  AW_PSP_TASK_SAFE()

/**
 * \brief ʹ�����������˳�ɾ����ȫģʽ
 *
 * ����ɾ��������������������񽫻�������ֱ��������������� AW_TASK_UNSAFE()
 * �˳�ɾ����ȫģʽ��
 *
 * \return  AW_OK   ���ǳɹ�
 * \hideinitializer
 */
#define AW_TASK_UNSAFE()            AW_PSP_TASK_UNSAFE()

/**
 * \brief ��ȡָ�������ջ�ռ��ʹ�����
 *
 * \param[in]  task    ����ʵ�壬�� AW_TASK_DECL() �� AW_TASK_DECL_STATIC() ����
 * \param[out] p_total �ܹ���ջ��С
 * \param[out] p_free  ���е�ջ��С
 *
 * \par ����
 * \code
 *  #include "aw_task_stkchk.h"
 *  #include "aw_vdebug.h"
 *   
 *  AW_TASK_DECL_STATIC(task1, 512);
 *  AW_TASK_DECL_STATIC(task2, 512);
 *
 *  task1_entry () 
 *  {
 *      unsigned int total;
 *      unsigned int free;
 *
 *      AW_FOREVER {
 *          //... do something
 *          AW_TASK_STACK_CHECK(task2, &total, &free);
 *          aw_kprintf("task2 stack total: %d bytes, free��%d bytes", total, free);
 *      }
 *  }
 *
 *  task2_entry () 
 *  {
 *      AW_FOREVER {
 *       
 *          //... do something
 *       
 *      }
 *  }
 *
 *  void aw_main ()
 *  {
 *      
 *      AW_TASK_INIT(task1,   "task1",   5, 512, task1_entry,   0); 
 *      AW_TASK_INIT(task1,   "task1",   6, 512, task2_entry,   0); 
 *      AW_TASK_STARTUP(task1);
 *      AW_TASK_STARTUP(task2);
 *      
 *      AW_FOREVER {
 *          //... do something
 *          aw_mdelay(10);
 *      }
 *  }
 * \endcode
 *
 * \retval  0:  ջ���ɹ�
 *
 * \note  ���������ջ�ռ��С����ʱ�Ĳο���ʱ��Խ���������Խ׼ȷ�� 
 */     
#define AW_TASK_STACK_CHECK(task, p_total, p_free)  \
            AW_PSP_TASK_STACK_CHECK(task, p_total, p_free)

/**
 * \brief ��ȡ��ǰ�����ջ�ռ��ʹ�����
 *
 * \param[out] p_total �ܹ���ջ��С
 * \param[out] p_free  ���е�ջ��С
 *
 * \par ����
 * \code
 *  #include "aw_task_stkchk.h"
 *  #include "aw_vdebug.h"
 *   
 *  AW_TASK_DECL_STATIC(task1, 512);
 *
 *
 *  task1_entry () 
 *  {
 *      unsigned int total;
 *      unsigned int free;
 *
 *      AW_FOREVER {
 *          //... do something
 *          AW_TASK_STACK_CHECK_SELF(&total, &free);
 *          aw_kprintf("task1 stack total: %d bytes, free��%d bytes",
 *                     total,
 *                     free);
 *          aw_mdelay(10);
 *      }
 *  }
 *
 *  void aw_main ()
 *  {
 *      
 *      AW_TASK_INIT(task1,   "task1",   5, 512, task1_entry,   0); 
 *
 *      AW_TASK_STARTUP(task1);
 *
 *      AW_FOREVER {
 *          //... do something
 *          aw_mdelay(10);
 *      }
 *  }
 * \endcode
 *
 * \return  0:  ջ���ɹ�
 *
 * \note  ���������ջ�ռ��С����ʱ�Ĳο���ʱ��Խ���������Խ׼ȷ�� 
 */  
#define AW_TASK_STACK_CHECK_SELF(p_total, p_free)  \
            AW_PSP_TASK_STACK_CHECK_SELF(p_total, p_free)
 
/**
 * \brief ��������
 *
 * \param[in] name      ��������
 * \param[in] priority  �������ȼ�, 0 ���ȼ����, ������ȼ���ͨ��
 *                      aw_task_lowest_priority() ��ȡ��
 *
 * \param[in] stack_size  �����ջ��С
 * \param[in] func        ��ں���
 * \param[in] arg         ��ڲ���
 *
 * \return          �ɹ����������ID��ʧ���򷵻�NULL
 *
 * \note ���� \a priority ���û���������ȼ���ϵͳ�������������ȼ����ڲ�ϵͳ����
 * ���豸����ʹ�á�������Щϵͳ������豸������ʹ�ú� AW_TASK_SYS_PRIORITY(pri)
 * ��ʾϵͳ�������ȼ���
 */
aw_task_id_t aw_task_create (const char     *name,
                             int             priority,
                             size_t          stack_size,
                             aw_pfuncvoid_t  func,
                             void           *arg);

/**
 * \brief ��ֹ����ɾ����ص��ڴ�
 *
 * \param[in]   task_id ����ID
 *
 * \return  AW_OK   �ɹ�
 */
aw_err_t aw_task_delete (aw_task_id_t task_id);

/**
 * \brief ���������û�����
 *
 * tls: ��ֵ�߳��ڲ��洢����¼
 *
 * \param[in]   task_id ����ID
 * \param[in]   data    �û�����
 *
 * \return  �ɵĵ�tls
 */
void *aw_task_set_tls (aw_task_id_t task_id, void *data);

/**
 * \brief ��ȡ�����û�����
 *
 * tls: ��ֵ�߳��ڲ��洢����¼
 *
 * \param[in]   task_id ����ID
 *
 * \return  ��ǰ��tls
 */
void *aw_task_get_tls (aw_task_id_t task_id);

/**
 * \brief ��ǰ�������ռ��CPU
 *
 * \return  ��
 */
void aw_task_yield (void);

/**
 * \brief ��������
 *
 * \param[in]   task_id     ����ID���� AW_TASK_INIT() ����
 *
 * \retval   AW_OK      �ɹ�����
 * \retval  -AW_EPERM   �����������ܾ�
 *
 * \par ����
 *  �� AW_TASK_DECL()
 *
 * \sa AW_TASK_DECL(), AW_TASK_DECL_STATIC(), AW_TASK_INIT(), AW_TASK_STARTUP(),
 *  AW_TASK_TERMINATE()
 */
aw_err_t aw_task_startup (aw_task_id_t task_id);

/**
 * \brief ��ֹ����
 *
 * \param[in]   task_id     ����ID���� AW_TASK_INIT() ����
 *
 * \retval   AW_OK      �ɹ���ֹ
 * \retval  -AW_EPERM   ��ֹ�������ܾ�
 */
aw_err_t aw_task_terminate (aw_task_id_t task_id);

/**
 * \brief ����͢ʱ
 *
 * ����͢ʱ����λΪʱ���������ʹ�� aw_sys_clkrate_get() ��ȡϵͳʱ�ӽ���Ƶ�ʣ�
 * ��1���ӵ�ϵͳʱ�ӽ�������
 *
 * - �뼶��ʱ��ʾ��ʽΪ       (aw_sys_clkrate_get() * delay_x_s);
 * - ���뼶��ʱ�ı�ʾ��ʽΪ   (aw_sys_clkrate_get() * delay_x_ms / 1000);
 * - ��ʹ�� aw_ms_to_ticks() ��������ת��Ϊ������
 *
 * \param[in] ticks �δ���
 *
 * \return ��
 *
 * \par ����
 * \code
 *  #include "aw_task.h"
 *  void taska ( int a, int b )
 *  {
 *      while (1){
 *          // ...
 *          aw_task_delay(aw_sys_clkrate_get() * 1);            // ��ʱ1S
 *          aw_task_delay(aw_sys_clkrate_get() * 100 / 1000);   // ��ʱ100ms
 *          aw_task_delay(aw_ms_to_ticks(100));                 // ��ʱ100ms
 *      }
 *  }
 *
 *  \endcode
 *  \sa aw_sys_clkrate_get()
 *  \hideinitializer
 */
void aw_task_delay (int ticks);

/**
 * \brief ��̬��������������ȼ�
 *
 * \param[in] task_id      ����ID���� AW_TASK_INIT() ����
 * \param[in] new_priority �µ����ȼ�
 *                         ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7, ������ȼ�Ϊ0��
 *
 * \retval    AW_OK      �ɹ�����
 * \retval   -AW_EPERM   �������ܾ�
 */
aw_err_t aw_task_priority_set (aw_task_id_t task_id, unsigned int new_priority);

/**
 * \brief ��ȡ���ȼ���Ŀ
 *
 * \note ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7, ������ȼ�Ϊ0
 * ���ȼ��ķ�Χ�ǣ�0 (������ȼ�) ~ aw_task_priority_count() - 1 (������ȼ�)
 *
 * \return  ���ȼ���Ŀ
 * \hideinitializer
 */
unsigned int aw_task_priority_count (void);

/**
 * \brief ��ȡ��͵����ȼ�
 *
 * \note ��ǰƽ̨���ȼ�����Ϊ8, ������ȼ�Ϊ7, ������ȼ�Ϊ0��
 * ������ȼ� = aw_task_priority_count() - 1
 *
 * \return  ������ȼ�
 * \hideinitializer
 */
unsigned int aw_task_lowest_priority (void);

/**
 * \brief ��ȡ��ǰ�����ID
 *
 * \attention   �������ж��е��ñ�����
 *
 * \return  ��ǰ�����ID
 */
aw_task_id_t aw_task_id_self (void);

/**
 * \brief ��ȡ��ǰ���������
 *
 * \attention   �������ж��е��ñ�����
 *
 * \param[in] task_id ����ID���� AW_TASK_INIT() ����
 *
 * \return  ��ǰ���������
 * \hideinitializer
 */
const char *aw_task_name_get (aw_task_id_t task_id);

/**
 * \brief ��ȡ��ǰ��������ȼ�
 *
 * \attention   �������ж��е��ñ�����
 *
 * \param[in] task_id ����ID���� AW_TASK_INIT() ����
 *
 * \return  ��ǰ��������ȼ�
 * \hideinitializer
 */
unsigned int aw_task_priority_get (aw_task_id_t task_id);

/**
 * \brief �ж�����ID�Ƿ���Ч
 *
 * \param[in] task_id ����ID���� AW_TASK_INIT() ����
 *
 * \retval TRUE  ������Ч
 * \retval FALSE ������Ч
 * \hideinitializer
 */
bool_t aw_task_valid (aw_task_id_t task_id);

/**
 * \brief ����ID����Ϊ��Ч
 *
 * \param[in] p_task_id ����ID���� AW_TASK_INIT() ���أ���ַ
 *
 * \retval TRUE  ������Ч
 * \retval FALSE ������Ч
 * \hideinitializer
 */
void aw_task_set_invalid (aw_task_id_t *p_task_id);

/**
 * \brief �ȴ���һ�������˳�
 *
 * \param[in] task_id ����ID���� AW_TASK_INIT() ���أ�
 * \param[out] p_status p_statusָ��һ����ַ�����ڴ�ŵȴ�������˳���

 * \retval AW_OK �ȴ�������ɹ��˳�
 * \retval ���Ĵ�����
 * \hideinitializer
 */
aw_err_t aw_task_join(aw_task_id_t task_id,void **p_status);

/** @} grp_aw_if_task */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif    /* __AW_TASK_H */

/* end of file */
