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
 * \brief RTOS信号量操作抽象接口
 *
 * 使用本服务需要包含头文件 aw_sem.h
 *
 * \par 简单示例
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);   // 定义任务 task_a
 *  AW_TASK_DECL_STATIC(task_b, 512);   // 定义任务 task_b
 *
 *  AW_SEMB_DECL_STATIC(sem);           // 定义二进制信号量 sem
 *
 *  void func_a (void *arg)
 *  {
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(sem);          //释放信号量
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER); //等待信号量
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // 初始化信号量
 *      AW_SEMB_INI(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(task_a,            // 任务实体
 *                   "task_a",          // 任务名字
 *                   5,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_a,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      AW_TASK_INIT(task_b,            // 任务实体
 *                   "task_b",          // 任务名字
 *                   6,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_b,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * //更多内容待添加。。。
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
 * \name 超时参数定义
 * @{
 */
/**
 * \brief 永久等待
 * \hideinitializer
 */
#define AW_SEM_WAIT_FOREVER     AW_PSP_SEM_WAIT_FOREVER

/**
 * \brief 无等待
 * \hideinitializer
 */
#define AW_SEM_NO_WAIT          AW_PSP_SEM_NO_WAIT
/** @} 超时参数定义 */


/**
 * \name 二进制信号量初始化状态
 */
/**
 * \brief 信号量空
 * \hideinitializer
 */
#define AW_SEM_EMPTY            AW_PSP_SEM_EMPTY

/**
 * \brief 信号量满（用于二进制信号量）
 * \hideinitializer
 */
#define AW_SEM_FULL            AW_PSP_SEM_FULL
/** @} 二进制信号量初始化状态 */


/**
 * \name 信号量初始化选项
 * @{
 */
/**
 * \brief 排队方式为 FIFO (先进先出)
 * \hideinitializer
 */
#define AW_SEM_Q_FIFO         AW_PSP_SEM_Q_FIFO

/**
 * \brief 排队方式为优先级
 * \hideinitializer
 */
#define AW_SEM_Q_PRIORITY     AW_PSP_SEM_Q_PRIORITY

/**
 * \brief 互斥信号量删除安全 (用于互斥信号量)
 * \hideinitializer
 */
#define AW_SEM_DELETE_SAFE    AW_PSP_SEM_DELETE_SAFE

/**
 * \brief 防止互斥信号量优先级反转 (用于互斥信号量)
 * \hideinitializer
 */
#define AW_SEM_INVERSION_SAFE   AW_PSP_SEM_INVERSION_SAFE
/** @} 信号量初始化选项 */

/**
 * \name 信号量类型定义
 * @{
 */
typedef aw_psp_semb_id_t    aw_semb_id_t;      /**< 二进制信号量ID     */
typedef aw_psp_semc_id_t    aw_semc_id_t;      /**< 计数信号量ID       */
typedef aw_psp_mutex_id_t   aw_mutex_id_t;     /**< 互斥信号量ID       */
/** @} 信号量类型定义 */

/**
 *  \brief 定义二进制信号量
 *
 * 本宏定义一个二进制信号量,在编译时完成信号量所需内存的分配; 在运行时, 需要调用
 * AW_SEMB_INIT() 完成信号量的初始化；调用 AW_SEMB_TERMINATE()终止信号量。
 *
 * 参数\a sem 只能作为宏 AW_SEMB_INIT(),  AW_SEMB_TAKE(),  AW_SEMB_GIVE()和
 * AW_SEMB_TERMINATE()的参数。
 *
 * AW_SEMB_INIT()返回信号量的\a sem_id, \a sem_id 作为函数 aw_semb_take() ,
 * aw_semb_give()和 aw_semb_terminate()的参数;这些函数的功能与对应的宏的功能相同,
 * 区别在于, 函数使用\a sem_id 作为参数,\a sem_id 可以作为信号量的句柄在函数调
 * 用之间传递。
 *
 * 可以使用本宏将信号量实体嵌入到另一个数据结构中,这样的话,分配那个大的数据对象
 * 的时候就自动完成了信号量实体的内存分配, 如下面的范例所示。
 *
 * \attention 若信号量没有跨模块(文件)使用的需求，推荐使用 AW_SEMB_DECL_STATIC()
 *            代替本宏，这样可避免模块之间信号量命名污染。
 *
 * \attention 除特殊用法外不, 切莫在函数内使用此宏来定义信号量，因为在函数内此宏
 *            分配的内存来自于栈上，一旦函数返回，分配的内存被自动回收。
 *            在函数内部使用 AW_SEMB_DECL_STATIC()来定义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_SEMB_INIT(),  AW_SEMB_TAKE(), AW_SEMB_GIVE()
 *                和 AW_SEMB_TERMINATE() 一起使用。
 *
 * \par 范例：常规用法
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_TASK_DECL_STATIC(task_a, 512);   // 定义任务 task_a
 *  AW_TASK_DECL_STATIC(task_b, 512);   // 定义任务 task_b
 *
 *  AW_SEMB_DECL_STATIC(sem);           // 定义二进制信号量 sem
 *
 *  void func_a (void *arg)
 *  {
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(sem);          //释放信号量
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER); //等待信号量
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *      // 初始化信号量
 *      AW_SEMB_INI(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(task_a,            // 任务实体
 *                   "task_a",          // 任务名字
 *                   5,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_a,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      AW_TASK_INIT(task_b,            // 任务实体
 *                   "task_b",          // 任务名字
 *                   6,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_b,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par 范例：将信号量实体嵌入另一个数据结构
 * \code
 *  #include "aw_sem.h"
 *
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);          // 任务实体task_a, 堆栈512
 *      AW_TASK_DECL(task_b, 512);          // 任务实体task_b, 堆栈512
 *      AW_SEMB_DECL(sem);                  // 信号量实体
 *      aw_semb_id_t sem_id;                // 信号量ID
 *  };
 *  struct my_struct   my_object;           // 定义大的数据对象
 *
 *  void func_a (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          //...
 *          AW_SEMB_GIVE(p_myobj->sem);     //释放信号量(使用信号量实体)
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          // 等待信号量(使用信号量ID)
 *          aw_semb_take(p_myobj->sem_id, AW_SEM_WAIT_FOREVER);
 *          //...
 *      }
 *  }
 *
 *  int main ()
 *  {
 *
 *      // 初始化信号量
 *      my_object.sem_id = AW_SEMB_INIT(my_object.sem,
 *                                      AW_SEM_EMPTY,
 *                                      AW_SEM_Q_PRIORITY);
 *      if (my_object.sem_id == NULL) {
 *          return -1;                      // 信号量初始化失败
 *      }
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(my_object.task_a,      // 任务实体
 *                   "task_a",              // 任务名字
 *                   5,                     // 任务优先级
 *                   512,                   // 任务堆栈大小
 *                   func_a,                // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      AW_TASK_INIT(my_object.task_b,      // 任务实体
 *                   "task_b",              // 任务名字
 *                   6,                     // 任务优先级
 *                   512,                   // 任务堆栈大小
 *                   func_b,                // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //延时20秒
 *
 *      // AW_SEMB_TERMINATE(my_object.sem);    // 终止信号量
 *      // aw_semb_terminate(my_object.sem_id); // 终止信号量(使用信号量ID)
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
 * \brief 定义二进制信号量(静态)
 *
 * 本宏与 AW_SEMB_DECL() 的功能相同, 区别在于, AW_SEMB_DECL_STATIC() 在定义信
 * 号量所需内存时, 使用关键字 \b static , 如此一来, 便可以将信号量实体的作用域
 * 限制在模块内(文件内)从而避免模块之间的信号量命名冲突；还可以在函数内使用本
 * 宏定义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *                AW_SEMB_GIVE() 和 aw_semb_terminate() 一起使用。
 *
 * \par 范例
 * 见 AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_INIT(), AW_SEMB_TAKE(), AW_SEMB_GIVE,
 *     AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_DECL_STATIC(sem)    AW_PSP_SEMB_DECL_STATIC(sem)

/**
 * \brief 引用二进制信号量
 *
 * 本宏引入一个二进制信号量, 相当于使用关键 \b extern 声明一个外部符号。
 * 如果要使用另一个模块(文件)中定义的信号量, 首先使用本宏引入该信号量, 然后就
 * 可以操作该信号量。被引入的信号量应当是使用 AW_SEMB_DECL()定义的。
 *
 * \param[in] sem  信号量实体
 *
 * \par 范例
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_IMPORT(sem_x);      // 引入信号量 sem_x
 *
 *  int func ()
 *  {
 *      AW_SEMB_TAKE(sem_x);    // 等待信号量 sem_x
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
 * \brief 二进制信号量初始化
 *
 * 初始化由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC()静态定义的二进制信号量,
 * 或嵌入到另一个大数据对象中的二进制信号量。信号量被初始化为 #AW_SEM_EMPTY 或
 * #AW_SEM_FULL 状态。
 *
 * 二进制信号量的选项决定了阻塞于此信号量的任务的排队方式, 可以按任务本身优先级
 * 或先进先出的方式排队, 它们分别对应 #AW_SEM_Q_PRIORITY 和 #AW_SEM_Q_FIFO 。
 *
 * \param[in] sem           信号量实体,由 AW_SEMB_DECL()或
 *                          AW_SEMB_DECL_STATIC()定义
 * \param[in] initial_state 初始状态:
 *                              - #AW_SEM_EMPTY
 *                              - #AW_SEM_FULL
 * \param[in] options       初始化选项标志:
 *                              - #AW_SEM_Q_FIFO
 *                              - #AW_SEM_Q_PRIORITY
 *
 * \return 成功返回二进制信号量的ID, 失败则返回NULL
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
 * \brief 获取二进制信号量
 *
 * 获取信号量。如果信号量为空, 则任务将会被挂起直到信号量变得可用(其它任务调用
 * 了 AW_SEMB_GIVE()或 aw_semb_give())。如果信号量已经是可用的, 则本调用将会
 * 清空该信号量, 则其它任务不能获取到该信号量, 直到调用的任务释放此信号量。
 *
 * 参数 \a timeout 控制调用的阻塞:
 *   - 为 #AW_SEM_WAIT_FOREVER 时, 调用将会被阻塞, 直到该信号量被释放或删除,
 *     可以通过返回值来判断调用结果:AW_OK -成功获取到信号量；-AW_ENXIO -信号量已经
 *     被摧毁
 *
 *   - 为 #AW_SEM_NO_WAIT 时, 调用不会被阻塞, 立即返回, 通过返回值来判断调用结果;
 *     AW_OK -成功获取到信号量; -AW_EAGAIN -未获取到信号量,稍后再试;
 *     -AW_ENXIO -信号量已经被终止
 *
 *   - 正数值为超时时间, 此时调用有超时地阻塞, 在设定的超时时间到达时, 若还未获
 *     取到信号量, 则调用返回, 可以通过返回值来判断调用结果： AW_OK -成功获取到
 *     信号量; -AW_ETIME -超时,未获取到信号量,稍后再试; -AW_ENXIO -信号量已经被终止
 *
 *   - 其它负数值为非法参数
 *
 * \param[in]   sem      信号量实体,由 AW_SEMB_DECL() 或
 *                       AW_SEMB_DECL_STATIC() 定义
 * \param[in]   timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                       由函数 aw_sys_clkrate_get()获得, 可使用 aw_ms_to_ticks()
 *                       将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                       #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 * \retval  -AW_EPERM  不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME  获取信号量超时
 * \retval  -AW_ENXIO  信号量已经被终止
 * \retval  -AW_EAGAIN 获取信号量失败, 稍后再试 (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 AW_SEMB_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_TAKE(sem, AW_SEM_WAIT_FOREVER);         // 永久等待
 *
 *  aw_err_t ret;
 *  ret = AW_SEMB_TAKE(sem, aw_ms_to_ticks(500));   //超时等待,超时时间 500ms
 *  if (ret == -AW_ETIME) {                         // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_SEMB_TAKE(sem, AW_SEM_NO_WAIT);        // 无等待
 *  if (ret == -AW_EAGAIN) {                        // 未获取到信号量
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
 * \brief 释放二进制信号量
 *
 * 释放信号量。如果有更高优先级的任务获取了该信号量, 该任务就准备好了运行, 并且
 * 会立即抢占调用 AW_SEMB_GIVE() 的任务。若信号量是满的(即信号量被释放, 但是没
 * 有任务获取), 则没有任何操作。
 *
 * \param[in] sem 信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMB_DECL()
 */
#define AW_SEMB_GIVE(sem)   AW_PSP_SEMB_GIVE(sem)

/**
 * \brief 重置二进制信号量
 *
 * \param[in] sem         二进制信号量实体,由 AW_SEMB_DECL() 或 
 *                        AW_SEMB_DECL_STATIC() 定义
 * \param[in] reset_value 二进制信号量的重置值(0或者非0)
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMB_RESET(sem, reset_value)   AW_PSP_SEMB_RESET(sem, reset_value)

/**
 * \brief 终止二进制信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param[in] sem 信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMB_DECL() 和 AW_SEMB_DECL_STATIC()
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE()
 * \sa aw_semb_take(), aw_semb_give(), aw_semb_terminate()
 * \hideinitializer
 */
#define AW_SEMB_TERMINATE(sem)  AW_PSP_SEMB_TERMINATE(sem)

/**
 * \brief 二进制信号量是否有效的判断
 *
 * \param[in] sem  二进制信号量实体,由 AW_SEMB_DECL() 或
 *                 AW_SEMB_DECL_STATIC() 定义
 *
 * \retval  TRUE       二进制信号量有效
 * \retval  FALSE      二进制信号量无效
 * \hideinitializer
 */
#define AW_SEMB_VALID(sem)          AW_PSP_SEMB_VALID(sem)

/**
 * \brief 将二进制信号量设置为无效
 *
 * \param[in] sem  信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
#define AW_SEMB_SET_INVALID(sem)    AW_PSP_SEMB_SET_INVALID(sem)

/**
 * \brief 获取二进制信号量
 *
 * 本函数的功能与 AW_SEMB_TAKE() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_SEMB_INIT() 返回。
 *
 * \param[in]   sem_id   信号量ID,由 AW_SEMB_INIT()返回
 * \param[in]   timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                       由函数 aw_sys_clkrate_get()获得, 可使用 aw_ms_to_ticks()
 *                       将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                       #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 * \retval  -AW_EPERM  不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME  获取信号量超时
 * \retval  -AW_ENXIO  信号量已经被终止
 * \retval  -AW_EAGAIN 获取信号量失败, 稍后再试 (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 AW_SEMB_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMB_DECL_STATIC(sem);                   // 定义信号量实体
 *  aw_semb_id_t  sem_id;                       // 信号量ID
 *
 *  sem_id = AW_SEMB_INI(sem);                  // 初始化信号量, 得到信号量ID
 *
 *  aw_semb_take(sem_id, AW_SEM_WAIT_FOREVER);  // 永久等待
 *
 *  aw_err_t ret;
 *  ret = aw_semb_take(sem_id, aw_ms_to_ticks()); // 超时时间 500ms
 *  if (ret == -AW_ETIME) {                       // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_semb_take(sem, AW_SEM_NO_WAIT);    // 无等待
 *  if (ret == -AW_EAGAIN) {                    // 未获取到信号量
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
 * \brief 释放二进制信号量
 *
 * 本函数的功能与 AW_SEMB_GIVE() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_SEMB_INIT() 返回。
 *
 * \param[in] sem_id 信号量ID,由 AW_SEMB_INIT()返回
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_terminate()
 * \hideinitializer
 */
aw_err_t aw_semb_give (aw_semb_id_t sem_id);

/**
 * \brief 重置二进制信号量
 *
 * \param[in] sem_id      二进制信号量ID,由 AW_SEMB_INIT()返回
 * \param[in] reset_value 二进制信号量的重置值(0或者非0)
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semb_reset (aw_semb_id_t sem_id, int reset_value);

/**
 * \brief 终止二进制信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param[in] sem_id 信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMB_DECL()
 *
 * \sa AW_SEMB_DECL(), AW_SEMB_DECL_STATIC(), AW_SEMB_INIT(), AW_SEMB_TAKE(),
 *     AW_SEMB_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semb_take(), aw_semb_give()
 * \hideinitializer
 */
aw_err_t aw_semb_terminate (aw_semb_id_t sem_id);

/**
 * \brief 二进制信号量是否有效的判断
 *
 * \param[in] sem_id  信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC() 定义
 *
 * \retval  TRUE       二进制信号量有效
 * \retval  FALSE      二进制信号量无效
 * \hideinitializer
 */
bool_t aw_semb_valid (aw_semb_id_t sem_id);

/**
 * \brief 将二进制信号量设置为无效
 *
 * \param[in] p_sem_id  信号量实体,由 AW_SEMB_DECL() 或 AW_SEMB_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
void aw_semb_set_invalid (aw_semb_id_t *p_sem_id);

/**
 *  \brief 定义计数信号量
 *
 * 本宏定义一个计数信号量, 在编译时完成信号量所需内存的分配; 在运行时, 需要调用
 * AW_SEMC_INIT() 完成信号量的初始化；调用 AW_SEMC_TERMINATE()终止信号量。
 *
 * 参数\a sem 只能作为宏 AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 * 和 AW_SEMC_TERMINATE()的参数。
 *
 * AW_SEMC_INIT() 返回信号量的\a sem_id, \a sem_id 作为函数 aw_semc_take() ,
 * aw_semc_give() 和 aw_semc_terminate()的参数; 这些函数的功能与对应的宏的功能
 * 相同, 区别在于, 函数使用\a sem_id 作为参数,\a sem_id 可以作为信号量的句柄在
 * 函数调用之间传递。
 *
 * 可以使用本宏将信号量实体嵌入到另一个数据结构中,这样的话,分配那个大的数据对象
 * 的时候就自动完成了信号量实体的内存分配, 如下面的范例所示。
 *
 * \attention 若信号量没有跨模块(文件)使用的需求，推荐使用 AW_SEMC_DECL_STATIC()
 *            代替本宏，这样可避免模块之间信号量命名污染。
 *
 * \attention 除特殊用法外不, 切莫在函数内使用此宏来定义信号量，因为在函数内此宏
 *            分配的内存来自于栈上，一旦函数返回，分配的内存被自动回收。
 *            在函数内部使用 AW_SEMC_DECL_STATIC()来定义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 *                和 AW_SEMC_TERMINATE() 一起使用。
 *
 * \par 范例：常规用法
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
 *          AW_SEMC_GIVE(sem);                      //释放信号量
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      while (1) {
 *          AW_SEMC_TAKE(sem, AW_SEM_WAIT_FOREVER); //等待信号量
 *          //...
 *      }
 *  }
 *
 *  int main() {
 *
 *      // 初始化信号量
 *      AW_SEMC_INIT(sem, AW_SEM_EMPTY, AW_SEM_Q_PRIORITY);
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(task_a,            // 任务实体
 *                   "task_a",          // 任务名字
 *                   5,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_a,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      AW_TASK_INIT(task_b,            // 任务实体
 *                   "task_b",          // 任务名字
 *                   6,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_b,            // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par 范例：将信号量实体嵌入另一个数据结构
 * \code
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);      // 任务实体task_a, 堆栈512
 *      AW_TASK_DECL(task_b, 512);      // 任务实体task_b, 堆栈512
 *      AW_SEMC_DECL(sem);              // 信号量实体
 *      aw_semb_id_t sem_id;            // 信号量ID
 *  };
 *  struct my_struct   my_object;       // 定义大的数据对象
 *
 *  void func_a (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          //...
 *          AW_SEMC_GIVE(p_myobj->sem);  //释放信号量(使用信号量实体)
 *      }
 *  }
 *
 *  void func_b (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          // 等待信号量(使用信号量ID)
 *          aw_semc_take(p_myobj->sem_id, AW_SEM_WAIT_FOREVER);
 *          //...
 *      }
 *  }
 *
 *  int main() {
 *
 *      // 初始化信号量
 *      my_object.sem_id = AW_SEMC_INIT(my_object.sem,
 *                                      AW_SEM_EMPTY,
 *                                      AW_SEM_Q_PRIORITY);
 *      if (my_object.sem_id == NULL) {
 *          return -1;                      // 信号量初始化失败
 *      }
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(my_object.task_a,      // 任务实体
 *                   "task_a",              // 任务名字
 *                   5,                     // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_a,                // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      AW_TASK_INIT(my_object.task_b,      // 任务实体
 *                   "task_b",              // 任务名字
 *                   6,                     // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_b,                // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //延时20秒
 *
 *      // AW_SEMC_TERMINATE(my_object.sem);    // 终止信号量
 *      // aw_semc_terminate(my_object.sem_id); // 终止信号量(使用信号量ID)
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
 * \brief 定义计数信号量(静态)
 *
 * 本宏与 AW_SEMC_DECL() 的功能相同, 区别在于, AW_SEMC_DECL_STATIC() 在定义
 * 信号量所需内存时, 使用关键字\b static , 如此一来, 便可以将信号量实体的作用域限
 * 制在模块内(文件内)从而避免模块之间的信号量命名冲突；还可以在函数内使用本宏定
 * 义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE()
 *                和 AW_SEMC_TERMINATE() 一起使用。
 *
 * \par 范例
 * 见 AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_INIT(), AW_SEMC_TAKE(), AW_SEMC_GIVE,
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_DECL_STATIC(sem)    AW_PSP_SEMC_DECL_STATIC(sem)

/**
 * \brief 引用计数信号量
 *
 * 本宏引入一个计数信号量, 相当于使用关键\b extern 声明一个外部符号。
 * 如果要使用另一个模块(文件)中定义的信号量, 首先使用本宏引入该信号量, 然后就
 * 可以操作该信号量。被引入的信号量应当是使用 AW_SEMC_DECL()定义的。
 *
 * \param[in] sem 信号量实体
 *
 * \par 范例
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMC_IMPORT(sem_x);      // 引入信号量 sem_x
 *
 *  int func () {
 *      AW_SEMC_TAKE(sem_x);    // 等待信号量 sem_x
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
 * \brief 计数信号量初始化
 *
 * 初始化由 AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC()静态定义的计数信号量,
 * 或嵌入到另一个大数据对象中的二进制信号量。
 *
 * 计数信号量的选项决定了阻塞于此信号量的任务的排队方式, 可以按任务本身优先级
 * 或先进先出的方式排队, 它们分别对应 #AW_SEM_Q_PRIORITY 和 #AW_SEM_Q_FIFO 。
 *
 * \param[in]  sem            信号量实体,由 AW_SEMC_DECL()或
 *                            AW_SEMC_DECL_STATIC()定义
 * \param[in]  initial_count  初始计数值, 非负数
 * \param[in]  options        初始化选项标志:
 *                                - #AW_SEM_Q_FIFO
 *                                - #AW_SEM_Q_PRIORITY
 *
 * \return 成功返回计数信号量的ID, 失败则返回NULL
 *
 * \par 示例
 *  请参考 AW_SEMC_DECL()
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
 * \brief 获取计数信号量
 *
 * 获取信号量。如果信号量计数值为0, 则任务将会被挂起直到信号量变得可用(其它任务
 * 调用了 AW_SEMC_GIVE()或 aw_semc_give())。如果信号量已经是可用的(计数值 > 0),
 * 则本调用将会使计数值减 1。
 *
 *  参数 \a timeout 控制调用的阻塞:
 *   - 为 #AW_SEM_WAIT_FOREVER 时, 调用将会被阻塞, 直到该信号量被释放或删除,
 *     可以通过返回值来判断调用结果:AW_OK -成功获取到信号量；-AW_ENXIO -信号量已经
 *     被摧毁
 *
 *   - 为 #AW_SEM_NO_WAIT 时,调用不会被阻塞, 立即返回, 通过返回值来判断调用结果;
 *     AW_OK -成功获取到信号量; -AW_EAGAIN -未获取到信号量,稍后再试;
 *     -AW_ENXIO -信号量已经被终止
 *
 *   - 正数值为超时时间, 此时调用有超时地阻塞, 在设定的超时时间到达时, 若还未获
 *     取到信号量, 则调用返回, 可以通过返回值来判断调用结果： AW_OK -成功获取到
 *     信号量; -AW_ETIME -超时,未获取到信号量,稍后再试; -AW_ENXIO -信号量已经被终止
 *
 *   - 其它负数值为非法参数
 *
 * \param[in] sem      信号量实体,由 AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 * \param[in] timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                     由函数 aw_sys_clkrate_get()获得,  可使用 aw_ms_to_ticks()
 *                     将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                     #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK      成功
 * \retval  -AW_EINVAL  参数无效
 * \retval  -AW_EPERM   不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME   获取信号量超时
 * \retval  -AW_ENXIO   信号量已经被终止
 * \retval  -AW_EAGAIN  获取信号量失败, 稍后再试 (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 AW_SEMC_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_SEMC_TAKE(sem, AW_SEM_WAIT_FOREVER);         // 永久等待
 *
 *  aw_err_t ret;
 *  ret = AW_SEMC_TAKE(sem, aw_ms_to_ticks(500));   //超时等待,超时时间 500ms
 *  if (ret == -AW_ETIME) {                         // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_SEMC_TAKE(sem, AW_SEM_NO_WAIT);        // 无等待
 *  if (ret == -AW_EAGAIN) {                        // 未获取到信号量
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
 * \brief 释放计数信号量
 *
 * 释放信号量。如果有更高优先级的任务获取了该信号量, 该任务就准备好了运行, 并且
 * 会立即抢占调用 aw_semc_give() 的任务。若信号量是满的(即信号量被释放, 但是没
 * 有任务获取), 则没有任何操作。本函数会使信号量的计数值加1。
 *
 * \param[in] sem   信号量实体,由 AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_GIVE(sem)   AW_PSP_SEMC_GIVE(sem)

/**
 * \brief 重置计数信号量
 *
 * \param[in] sem         计数信号量实体,由 AW_SEMC_DECL() 或 
 *                        AW_SEMC_DECL_STATIC() 定义
 * \param[in] reset_value 计数信号量的重置值
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_RESET(sem, reset_value )   AW_PSP_SEMC_RESET(sem, reset_value)

/**
 * \brief 终止计数信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param[in]  sem  信号量实体,由 AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE()
 * \sa aw_semc_take(), aw_semc_give(), aw_semc_terminate()
 * \hideinitializer
 */
#define AW_SEMC_TERMINATE(sem)  AW_PSP_SEMC_TERMINATE(sem)

/**
 * \brief 信号量是否有效的判断
 *
 * \param[in] sem  信号量实体,由  AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \retval  TRUE   信号量有效
 * \retval  FALSE  信号量无效
 * \hideinitializer
 */
#define AW_SEMC_VALID(sem)          AW_PSP_SEMC_VALID(sem)

/**
 * \brief 信号量设置为无效
 *
 * \param[in] sem 信号量实体,由  AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
#define AW_SEMC_SET_INVALID(sem)    AW_PSP_SEMC_SET_INVALID(sem)

/**
 * \brief 获取计数信号量
 *
 * 本函数的功能与 AW_SEMC_TAKE() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_SEMC_INIT() 返回。
 *
 * \param[in] sem_id   信号量ID, 由 AW_SEMC_INIT()返回
 * \param[in] timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                     由函数 aw_sys_clkrate_get()获得, 可使用 aw_ms_to_ticks()
 *                     将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                     #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 * \retval  -AW_EPERM  不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME  获取信号量超时
 * \retval  -AW_ENXIO  信号量已经被终止
 * \retval  -AW_EAGAIN 获取信号量失败, 稍后再试 (timeout = AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 #AW_SEMC_DECL() 和 #AW_SEMC_DECL_STATIC()
 * \code
 *  AW_SEMC_DECL_STATIC(sem);                       // 定义信号量实体
 *  aw_semc_id_t  sem_id;                           // 信号量ID
 *
 *  sem_id = AW_SEMC_INI(sem);                      // 初始化信号量,得到信号量ID
 *
 *  aw_semc_take(sem_id, AW_SEM_WAIT_FOREVER);      // 永久等待
 *
 *  aw_err_t ret;
 *  ret = aw_semc_take(sem_id, aw_ms_to_ticks(500));// 超时时间 500ms
 *  if (ret == -AW_ETIME) {                         // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_semc_take(sem, AW_SEM_NO_WAIT);        // 无等待
 *  if (ret == -AW_EAGAIN) {                        // 未获取到信号量
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
 * \brief 释放计数信号量
 *
 * 本函数的功能与 AW_SEMC_GIVE() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_SEMC_INIT() 返回。
 *
 * \param[in] sem_id 信号量ID, 由 AW_SEMC_INIT()返回
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semc_give (aw_semc_id_t sem_id);

/**
 * \brief 重置计数信号量
 *
 * 本函数的功能与 AW_SEMC_RESET() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_SEMC_INIT() 返回。
 *
 * \param[in] sem_id      计数信号量ID, 由 AW_SEMC_INIT()返回
 * \param[in] reset_value 计数信号量的重置值
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMC_TERMINATE()
 * \sa aw_semc_take(), aw_semc_terminate()
 * \hideinitializer
 */
aw_err_t aw_semc_reset (aw_semc_id_t sem_id, int reset_value );

/**
 * \brief 终止计数信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param[in] sem_id 信号量ID, 由 AW_SEMC_INIT()返回
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_SEMC_DECL()
 *
 * \sa AW_SEMC_DECL(), AW_SEMC_DECL_STATIC(), AW_SEMC_INIT(), AW_SEMC_TAKE(),
 *     AW_SEMC_GIVE(), AW_SEMB_TERMINATE()
 * \sa aw_semc_take(), aw_semc_give()
 * \hideinitializer
 */
aw_err_t aw_semc_terminate (aw_semc_id_t sem_id);

/**
 * \brief 信号量是否有效的判断
 *
 * \param[in] sem_id 信号量实体,由  AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \retval  TRUE   信号量有效
 * \retval  FALSE  信号量无效
 * \hideinitializer
 */
bool_t aw_semc_valid (aw_semc_id_t sem_id);

/**
 * \brief 信号量设置为无效
 *
 * \param[in] p_sem_id 信号量实体,由  AW_SEMC_DECL() 或 AW_SEMC_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
void aw_semc_set_invalid (aw_semc_id_t *p_sem_id);

/**
 *  \brief 定义互斥信号量
 *
 * 本宏定义一个互斥信号量, 在编译时完成信号量所需内存的分配; 在运行时, 需要调用
 * AW_MUTEX_INIT() 完成信号量的初始化；调用 AW_MUTEX_TERMINATE()终止
 * 信号量。信号量被初始化为满状态。
 *
 * 参数\a sem 只能作为宏 AW_MUTEX_INIT(), AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK() 和
 * AW_MUTEX_TERMINATE()的参数。
 *
 * AW_MUTEX_INIT() 返回信号量的\a sem_id, \a sem_id 作为函数 aw_mutex_lock() ,
 * aw_mutex_unlock() 和 aw_mutex_terminate()的参数; 这些函数的功能与对应的宏的
 * 功能相同, 区别在于, 函数使用\a sem_id 作为参数,\a sem_id 可以作为信号量的句柄
 * 在函数调用之间传递。
 *
 * 可以使用本宏将信号量实体嵌入到另一个数据结构中,这样的话,分配那个大的数据对象
 * 的时候就自动完成了信号量实体的内存分配, 如下面的范例所示。
 *
 * \attention 若信号量没有跨模块(文件)使用的需求,推荐使用 AW_MUTEX_DECL_STATIC()
 *            代替本宏，这样可避免模块之间信号量命名污染。
 *
 * \attention 除特殊用法外不, 切莫在函数内使用此宏来定义信号量，因为在函数内此宏
 *            分配的内存来自于栈上，一旦函数返回，分配的内存被自动回收。
 *            在函数内部使用 AW_MUTEX_DECL_STATIC()来定义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_MUTEX_INIT(), AW_MUTEX_LOCK(),
 *                AW_MUTEX_UNLOCK() 和 AW_MUTEX_TERMINATE() 一起使用。
 *
 * \par 范例：常规用法, 保护资源的访问
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
 *      //... 要保护的程序代码
 *      AW_MUTEX_UNLOCK(mutex);
 *  }
 *  void func_proccess (void *arg)
 *  {
 *      while (1) {
 *          public_service();           // 访问公共服务
 *          aw_mdelay(50);              // 延时50ms
 *      }
 *  }
 *
 *  int main() {
 *
 *      // 初始化信号量
 *      AW_MUTEX_INIT(sem, AW_SEM_Q_PRIORITY);
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(task_a,            // 任务实体
 *                   "task_a",          // 任务名字
 *                   5,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_proccess,     // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      AW_TASK_INIT(task_b,            // 任务实体
 *                   "task_b",          // 任务名字
 *                   6,                 // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_proccess,     // 任务入口函数
 *                   NULL);             // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(task_a);
 *      AW_TASK_STARTUP(task_b);
 *
 *      return 0;
 *  }
 * \endcode
 *
 * \par 范例：将信号量实体嵌入另一个数据结构
 * \code
 *  #include "aw_sem.h"
 *
 *  struct my_struct {
 *      int my_data1;
 *      AW_TASK_DECL(task_a, 512);      // 任务实体task_a, 堆栈512
 *      AW_TASK_DECL(task_b, 512);      // 任务实体task_b, 堆栈512
 *      AW_MUTEX_DECL(mutex);           // 信号量实体
 *      aw_mutex_id_t mutex_id;         // 信号量ID
 *  };
 *  struct my_struct   my_object;       // 定义大的数据对象
 *
 *  void public_service (struct my_struct *p_myobj)
 *  {
 *      aw_mutex_lock(p_myobj->mutex_id);
 *      //... 要保护的程序代码
 *      aw_mutex_unlock(p_myobj->mutex_id);
 *  }
 *
 *  void func_proccess (void *arg)
 *  {
 *      struct my_struct *p_myobj = arg;
 *      while (1) {
 *          public_service(p_myobj);        // 访问公共服务
 *          aw_mdelay(50);                  // 延时50ms
 *      }
 *  }
 *
 *  int main() {
 *
 *      // 初始化信号量
 *      my_object.mutex_id = AW_MUTEX_INIT(my_object.mutex, AW_SEM_Q_PRIORITY);
 *      if (my_object.mutex_id == NULL) {
 *          return -1;                      // 信号量初始化失败
 *      }
 *
 *      // 初始化任务：
 *      AW_TASK_INIT(my_object.task_a,      // 任务实体
 *                   "task_a",              // 任务名字
 *                   5,                     // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_proccess,         // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      AW_TASK_INIT(my_object.task_b,      // 任务实体
 *                   "task_b",              // 任务名字
 *                   6,                     // 任务优先级
 *                   512,               // 任务堆栈大小
 *                   func_proccess,         // 任务入口函数
 *                   (void *)&my_object);   // 任务入口参数
 *
 *      // 启动任务
 *      AW_TASK_STARTUP(my_object.task_a);
 *      AW_TASK_STARTUP(my_object.task_b);
 *
 *      aw_mdelay(20 * 1000);   //延时20秒
 *
 *      // AW_SEMC_TERMINATE(my_object.mutex);    // 终止信号量
 *      // aw_semc_terminate(my_object.mutex_id); // 终止信号量(使用信号量ID)
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
 * \brief 定义互斥信号量(静态)
 *
 * 本宏与 AW_MUTEX_DECL() 的功能相同, 区别在于, AW_MUTEX_DECL_STATIC() 在定义
 * 信号量所需内存时, 使用关键字\b static ,如此一来, 便可以将信号量实体的作用域限
 * 制在模块内(文件内), 从而避免模块之间的信号量命名冲突；还可以在函数内使用本宏
 * 定义信号量。
 *
 * \param[in] sem 信号量实体, 与 AW_MUTEX_INIT(), AW_MUTEX_LOCK(),
 *                AW_MUTEX_UNLOCK() 和 AW_MUTEX_TERMINATE() 一起使用
 *
 * \par 范例
 * 见 AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_INIT(), AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK,
 *     AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_DECL_STATIC(sem)    AW_PSP_MUTEX_DECL_STATIC(sem)

/**
 * \brief 引用互斥信号量
 *
 * 本宏引入一个互斥信号量, 相当于使用关键 \b extern 声明一个外部符号。
 * 如果要使用另一个模块(文件)中定义的信号量, 首先使用本宏引入该信号量, 然后就
 * 可以操作该信号量。被引入的信号量应当是使用 AW_MUTEX_DECL()定义的。
 *
 * \param[in] sem 任务实体
 *
 * \par 范例
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_MUTEX_IMPORT(sem_x);     // 引入信号量 sem_x
 *
 *  int func () {
 *      AW_MUTEX_LOCK(sem_x);   // 等待信号量 sem_x
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
 * \brief 互斥信号量初始化
 *
 * 初始化由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC()静态定义的互斥信号量,
 * 或嵌入到另一个大数据对象中的二进制信号量。
 *
 * 互斥信号量的选项决定了阻塞于此信号量的任务的排队方式, 可以按任务本身优先级
 * 或先进先出的方式排队, 它们分别对应 #AW_SEM_Q_PRIORITY 和 #AW_SEM_Q_FIFO 。
 *
 * 选项 #AW_SEM_DELETE_SAFE 保护了当前拥有此信号量的任务避免非期望的删除。该选项
 * 隐含的操作是为每次 aw_mutex_lock() 添加一个 AW_TASK_SAFE() 调用, 为每次
 * aw_mutex_unlock() 添加一个 AW_TASK_UNSAFE() 调用。
 *
 * 选项 #AW_SEM_INVERSION_SAFE 保护了系统避免优先级反转, 该选项必须和
 * #AW_SEM_Q_PRIORITY 排队方式一起使用。
 *
 * \param[in]  sem      信号量实体,由 AW_MUTEX_DECL()或 AW_MUTEX_DECL_STATIC()定义
 * \param[in]  options  初始化选项标志("()"表示可选):
 *                          - #AW_SEM_Q_FIFO | (#AW_SEM_DELETE_SAFE)
 *                          - #AW_SEM_Q_PRIORITY | (#AW_SEM_DELETE_SAFE) |
                              (#AW_SEM_INVERSION_SAFE)
 *
 * \return 成功返回互斥信号量的ID, 失败则返回NULL
 *
 * \par 示例
 *  请参考 AW_MUTEX_DECL()
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
 * \brief 获取互斥信号量
 *
 * 获取信号量。如果信号量为空, 则任务将会被挂起直到信号量变得可用(其它任务调用
 * 了 AW_MUTEX_UNLOCK()或 aw_mutex_unlock())。如果信号量已经是可用的, 则本调用
 * 将会清空该信号量, 则其它任务不能获取到该信号量, 直到调用的任务释放此信号量。
 *
 * 如果删除安全选项(#AW_SEM_DELETE_SAFE)被使能, 则本函数会有一个隐含的
 * AW_TASK_SAFE()调用。
 *
 *  参数 \a timeout 控制调用的阻塞:
 *   - 为 #AW_SEM_WAIT_FOREVER 时, 调用将会被阻塞, 直到该信号量被释放或删除,
 *     可以通过返回值来判断调用结果:AW_OK -成功获取到信号量；-AW_ENXIO -信号量已经
 *     被摧毁
 *
 *   - 为 #AW_SEM_NO_WAIT 时,调用不会被阻塞, 立即返回, 通过返回值来判断调用结果;
 *     AW_OK -成功获取到信号量; -AW_EAGAIN -未获取到信号量,稍后再试;
 *     -AW_ENXIO -信号量已经被终止
 *
 *   - 正数为超时时间, 此时调用有超时地阻塞, 在设定的超时时间到达时, 若还未获
 *     取到信号量, 则调用返回, 可以通过返回值来判断调用结果： AW_OK -成功获取到
 *     信号量; -AW_ETIME -超时,未获取到信号量,稍后再试; -AW_ENXIO -信号量已经被终止
 *
 *   - 其它负数值为非法参数
 *
 * \param[in] sem      信号量实体,由 AW_MUTEX_DECL()或 AW_MUTEX_DECL_STATIC() 定义
 * \param[in] timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                     由函数 aw_sys_clkrate_get()获得, 可使用 aw_ms_to_ticks()
 *                     将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                     #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 * \retval  -AW_EPERM  不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME  获取信号量超时
 * \retval  -AW_ENXIO  信号量已经被终止
 * \retval  -AW_EAGAIN 获取信号量失败, 稍后再试 (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 AW_MUTEX_DECL()
 * \code
 *  #include "aw_sem.h"
 *
 *  AW_MUTEX_LOCK(sem, AW_SEM_WAIT_FOREVER);        // 永久等待
 *
 *  aw_err_t ret;
 *  ret = AW_MUTEX_LOCK(sem, aw_ms_to_ticks(500));  //超时等待,超时时间500ms
 *  if (ret == -AW_ETIME) {                         // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = AW_MUTEX_LOCK(sem, AW_SEM_NO_WAIT);       // 无等待
 *  if (ret == -AW_EAGAIN) {                        // 未获取到信号量
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
 * \brief 释放互斥信号量
 *
 * 释放信号量。如果有更高优先级的任务获取了该信号量, 该任务就准备好了运行, 并且
 * 会立即抢占调用 AW_MUTEX_UNLOCK() 的任务。若信号量是满的(即信号量被释放,
 * 但是没有任务获取), 则没有任何操作。
 *
 * 如果删除安全选项(#AW_SEM_DELETE_SAFE)被使能, 则本函数会有一个隐含的
 * AW_TASK_UNSAFE()调用。
 *
 * \param[in] sem   信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_MUTEX_DECL()
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_UNLOCK(sem)   AW_PSP_MUTEX_UNLOCK(sem)

/**
 * \brief 终止互斥信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param[in] sem   信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK()
 * \sa aw_mutex_lock(), aw_mutex_unlock(), aw_mutex_terminate()
 * \hideinitializer
 */
#define AW_MUTEX_TERMINATE(sem)  AW_PSP_MUTEX_TERMINATE(sem)


/**
 * \brief 互斥信号量是否有效的判断
 *
 * \param[in] sem  信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \retval  TRUE   信号量有效
 * \retval  FALSE  信号量无效
 * \hideinitializer
 */
#define AW_MUTEX_VALID(sem)          AW_PSP_MUTEX_VALID(sem)

/**
 * \brief 互斥信号量设置为无效
 *
 * \param[in]  sem  信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
#define AW_MUTEX_SET_INVALID(sem)    AW_PSP_MUTEX_SET_INVALID(sem)

/**
 * \brief 获取互斥信号量
 *
 * 本函数的功能与 AW_MUTEX_LOCK() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_MUTEX_INIT() 返回。
 *
 * \param   sem_id   信号量ID,由 AW_MUTEX_INIT()返回
 * \param   timeout  最大等待时间(超时时间), 单位是系统节拍, 系统时钟节拍频率
 *                   由函数 aw_sys_clkrate_get()获得, 可使用 aw_ms_to_ticks()
 *                   将毫秒转换为节拍数; #AW_SEM_NO_WAIT 为无阻塞;
 *                   #AW_SEM_WAIT_FOREVER 为一直等待, 无超时
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 * \retval  -AW_EPERM  不允许的操作,在中断中调用了本函数
 * \retval  -AW_ETIME  获取信号量超时
 * \retval  -AW_ENXIO  信号量已经被终止
 * \retval  -AW_EAGAIN 获取信号量失败, 稍后再试 (\a timeout = #AW_SEM_NO_WAIT)
 *
 * \par 范例
 * 更多范例请参考 AW_MUTEX_DECL()
 * \code
 *  AW_MUTEX_DECL_STATIC(sem);                  // 定义信号量实体
 *  aw_mutex_id_t  sem_id;                      // 信号量ID
 *
 *  sem_id = AW_MUTEX_INI(sem);                 // 初始化信号量, 得到信号量ID
 *
 *  aw_mutex_lock(sem_id, AW_SEM_WAIT_FOREVER);         // 永久等待
 *
 *  aw_err_t ret;
 *  ret = aw_mutex_lock(sem_id, aw_ms_to_ticks(500));   // 超时时间 500ms
 *  if (ret == -AW_ETIME) {                             // 等待信号量超时
 *      //...
 *  }
 *
 *  aw_err_t ret;
 *  ret = aw_mutex_lock(sem, AW_SEM_NO_WAIT);           // 无等待
 *  if (ret == -AW_EAGAIN) {                            // 未获取到信号量
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
 * \brief 释放互斥信号量
 *
 * 本函数的功能与 AW_MUTEX_UNLOCK() 相同, 差别在于, 本函数使用\a sem_id 作为参数。
 * \a sem_id 由 AW_MUTEX_INIT() 返回。
 *
 * \param   sem_id  信号量ID,由 AW_MUTEX_INIT()返回
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_terminate()
 * \hideinitializer
 */
aw_err_t aw_mutex_unlock (aw_mutex_id_t sem_id);

/**
 * \brief 终止互斥信号量
 *
 * 终止信号量。任何等待此信号量的任务将会解阻塞, 并返回 -AW_ENXIO 。此函数不会释放
 * 信号量相关的任何内存。
 *
 * \param   sem_id  信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \retval   AW_OK     成功
 * \retval  -AW_EINVAL 参数无效
 *
 * \par 范例
 * 请参考 AW_MUTEX_DECL()
 *
 * \sa AW_MUTEX_DECL(), AW_MUTEX_DECL_STATIC(), AW_MUTEX_INIT(),
 *     AW_MUTEX_LOCK(), AW_MUTEX_UNLOCK(), AW_MUTEX_TERMINATE()
 * \sa aw_mutex_lock(), aw_mutex_unlock()
 * \hideinitializer
 */
aw_err_t aw_mutex_terminate (aw_mutex_id_t sem_id);

/**
 * \brief 互斥信号量是否有效的判断
 *
 * \param[in] sem_id 信号量实体,由 AW_MUTEX_DECL() 或 AW_MUTEX_DECL_STATIC() 定义
 *
 * \retval  TRUE   信号量有效
 * \retval  FALSE  信号量无效
 * \hideinitializer
 */
bool_t aw_mutex_valid (aw_mutex_id_t sem_id);

/**
 * \brief 互斥信号量设置为无效
 *
 * \param[in] p_sem_id 信号量实体,由 AW_MUTEX_DECL() 或
 *                     AW_MUTEX_DECL_STATIC() 定义
 *
 * \return 无
 * \hideinitializer
 */
void aw_mutex_set_invalid (aw_mutex_id_t *p_sem_id);

/** \cond */

#define AW_SEL_WRITE    AW_PSP_SEL_WRITE /**< \brief 写标志 */
#define AW_SEL_READ     AW_PSP_SEL_READ  /**< \brief 读标志 */

/**
 * \brief 定义唤醒列表
 */
#define AW_SEL_WKUP_LIST_DECL(list)       AW_PSP_SEL_WKUP_LIST_DECL(list)

/**
 * \brief 初始化唤醒列表
 */
#define AW_SEL_WKUP_LIST_INIT(list)       AW_PSP_SEL_WKUP_LIST_INIT(list)

/**
 * \brief 唤醒所有
 */
#define AW_SEL_WAKEUP_All(list, sel_flag) AW_PSP_SEL_WAKEUP_All(list, sel_flag)

/** \endcond */

/** @} grp_aw_if_sem */

#ifdef __cplusplus
}
#endif

#endif /* __AW_SEMAPHORE */

/* end of file */
