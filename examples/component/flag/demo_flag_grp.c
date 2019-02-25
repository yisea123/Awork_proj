/*******************************************************************************
*                                  AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief flag_grp 事件标志组件例程,该例程实现一对多线程间的同步操作
 *
 * - 操作步骤：
 *   1. 本例程需在aw_prj_params.h头文件里使能AW_COM_CONSOLE和调试串口对应的宏；
 *   2. 将板子中的RX1、TX1通过USB转串口和PC连接，串口调试助手设置：
 *      波特率为115200，8位数据长度，1个停止位，无流控
 *
 * - 实验现象：
 *   1. 子任务1、2、3等待主任务设置事件组标记条件TEST_NODE0_FLAG:
 *    - 若子任务1已接收到主任务指定事件标志位0x10，则将该位清0；串口打印出相应信息，并将事件组标志位中最7位置1。
 *    - 若子任务2已接收到主任务指定事件标志位0x08，则将该位清0；串口打印出相应信息，并将事件组标志位中第6位置1；
 *    - 若子任务3已接收到主任务指定事件标志位0x04，则将该位清0；串口打印出相应信息，并将事件组标志位中第5位置1；
 *   2. 主任务等待子任务1、2、3设设置事件组标记条件，若主任务已接收到3个子任务的指定事件标志位，则将标志位清0，打印出正确信息。
 *
 *
 * \par 源代码
 * \snippet demo_flag_grp.c src_flag_grp
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-06  may, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_flag_grp
 * \copydoc demo_flag_grp.c
 */

/** [src_flag_grp] */
#include "aw_flag_grp.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "aw_task.h"

/* 定义事件组及节点 */
aw_local aw_flag_grp_t      __g_flg_grp;    /* 定义事件标志组 */
aw_local aw_flag_node_t     __g_flg_node0;  /* 定义事件标志节点，子任务使用 */
aw_local aw_flag_node_t     __g_flg_node1;  /* 定义事件标志节点 ，主任务使用*/
aw_local aw_flag_node_t     __g_flg_node2;  /* 定义事件标志节点 ，主任务使用*/
aw_local aw_flag_node_t     __g_flg_node3;  /* 定义事件标志节点 ，主任务使用*/


#define  TEST_FLAG_TASK_STACK_SIZE    512
AW_TASK_DECL_STATIC(test1_flg_task, TEST_FLAG_TASK_STACK_SIZE);
AW_TASK_DECL_STATIC(test2_flg_task, TEST_FLAG_TASK_STACK_SIZE);
AW_TASK_DECL_STATIC(test3_flg_task, TEST_FLAG_TASK_STACK_SIZE);

#define  TEST_NODE0_FLAG   0x1C
#define  TEST_NODE1_FLAG   0xE3

aw_local void __task1_flag_entry (void *p_arg)
{
    aw_err_t  ret = AW_OK;
    for(;;){

        /* 等待事件组标志满足条件 TEST_NODE0_FLAG */
        ret = aw_flag_pend(&__g_flg_grp,
                           &__g_flg_node1,
                           0x10,
                           AW_FLAG_NODE_WAIT_AND|AW_FLAG_NODE_WAIT_CLEAR,
                           AW_SEM_WAIT_FOREVER,
                           NULL);

        if (ret == AW_OK) {
            aw_kprintf("task1_flag_pend successful!\r\n");
            /* 将事件组标志第7位置1 */
            ret = aw_flag_post(&__g_flg_grp,0x83,AW_FLAG_OPT_SET);

            if (ret == AW_OK) {
                aw_kprintf("task1_flag_post successful!\r\n");
            }else{
                AW_ERRF(("task1_flag_post err: %d\n", ret));
            }

        }else{
            AW_ERRF(("task1_flag_pend err: %d\n", ret));
        }

        aw_mdelay(100);
    }
}

aw_local void __task2_flag_entry (void *p_arg)
{
    aw_err_t  ret = AW_OK;
    for(;;){

        // 等待事件组标志满足条件 TEST_NODE0_FLAG
        ret = aw_flag_pend(&__g_flg_grp,
                           &__g_flg_node2,
                           0x08,
                           AW_FLAG_NODE_WAIT_AND|AW_FLAG_NODE_WAIT_CLEAR,
                           AW_SEM_WAIT_FOREVER,
                           NULL);

        if (ret == AW_OK) {
            aw_kprintf("task2_flag_pend successful!\r\n");
            //将事件组标志第7位置1
            ret = aw_flag_post(&__g_flg_grp,0x43,AW_FLAG_OPT_SET);

            if (ret == AW_OK) {
                aw_kprintf("task2_flag_post successful!\r\n");
            }else{
                AW_ERRF(("task2_flag_post err: %d\n", ret));
            }

        }else{
            AW_ERRF(("task2_flag_pend err: %d\n", ret));
        }

        aw_mdelay(200);
    }
}

aw_local void __task3_flag_entry (void *p_arg)
{
    aw_err_t  ret = AW_OK;
    for(;;){

        // 等待事件组标志满足条件 TEST_NODE0_FLAG，等待成功后并将事件组标志清0
        ret = aw_flag_pend(&__g_flg_grp,
                           &__g_flg_node3,
                           0x04,
                           AW_FLAG_NODE_WAIT_AND|AW_FLAG_NODE_WAIT_CLEAR,
                           AW_SEM_WAIT_FOREVER,
                           NULL);

        if (ret == AW_OK) {
            aw_kprintf("task3_flag_pend successful!\r\n");
            //将事件组标志第7位置1
            ret = aw_flag_post(&__g_flg_grp,0x23,AW_FLAG_OPT_SET);

            if (ret == AW_OK) {
                aw_kprintf("task3_flag_post successful!\r\n");
            }else{
                AW_ERRF(("task3_flag_post err: %d\n", ret));
            }

        }else{
            AW_ERRF(("task3_flag_pend err: %d\n", ret));
        }

        aw_mdelay(300);
    }
}
/**
 * \brief 事件标志组件demo
 *
 * \return 无
 */
void  demo_flag_grp_entry(void)
{
    aw_err_t  ret   = AW_OK;
    uint32_t  flag  = 0;
    int i = 0;

    /* 初始化事件组 */
    ret = aw_flag_init(&__g_flg_grp,
                       0,
                       AW_FLAG_WAIT_Q_PRIORITY);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_init err: %d\n", ret));
        return;
    }

    /* 初始化事件组节点0 */
    ret = aw_flag_node_init(&__g_flg_node0);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node0_init err: %d\n", ret));
        return;
    }

    /* 初始化事件组节点1 */
    ret = aw_flag_node_init(&__g_flg_node1);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node1_init err: %d\n", ret));
        return;
    }

    /* 初始化事件组节点2 */
    ret = aw_flag_node_init(&__g_flg_node2);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node2_init err: %d\n", ret));
        return;
    }
    /* 初始化事件组节点3 */
    ret = aw_flag_node_init(&__g_flg_node3);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node3_init err: %d\n", ret));
        return;
    }
    /* 初始化任务1 */
    AW_TASK_INIT(test1_flg_task,
                 "demo_flg_task1",
                 3,
                 TEST_FLAG_TASK_STACK_SIZE,
                 __task1_flag_entry,
                 NULL);
    /* 启动任务1 */
    AW_TASK_STARTUP(test1_flg_task);

    /* 初始化任务2 */
    AW_TASK_INIT(test2_flg_task,
                 "demo_flg_task2",
                 4,
                 TEST_FLAG_TASK_STACK_SIZE,
                 __task2_flag_entry,
                 NULL);
    /* 启动任务2 */
    AW_TASK_STARTUP(test2_flg_task);

    /* 初始化任务3 */
    AW_TASK_INIT(test3_flg_task,
                 "demo_flg_task3",
                 5,
                 TEST_FLAG_TASK_STACK_SIZE,
                 __task3_flag_entry,
                 NULL);
    /* 启动任务3 */
    AW_TASK_STARTUP(test3_flg_task);

    for(i = 0;i < 5;i++ ){

        /* 设置事件组标志 TEST_NODE0_FLAG */
        ret = aw_flag_post(&__g_flg_grp,
                           TEST_NODE0_FLAG,
                           AW_FLAG_OPT_SET);
        if (ret != AW_OK) {
            AW_ERRF(("aw_flag_post err: %d\n", ret));
            return;
        }

        /* 等待事件组标志满足条件 TEST_NODE1_FLAG，需要等待子任务1、2、3都释放标志位之后才能向下
         * 执行，等待成功后并将事件组标志清0 */
        ret = aw_flag_pend(&__g_flg_grp,
                           &__g_flg_node0,
                           TEST_NODE1_FLAG,
                           AW_FLAG_NODE_WAIT_AND|AW_FLAG_NODE_WAIT_CLEAR,
                           AW_SEM_WAIT_FOREVER,
                           &flag);
        if (ret != AW_OK) {
            AW_ERRF(("test aw_flag_pend err: %d\n\n", ret));
        }else{
            aw_kprintf("test aw_flag_grp successful.\n\n");
        }
    }

    /* 销毁子任务1 */
    AW_TASK_TERMINATE(test1_flg_task);
    /* 销毁子任务2 */
    AW_TASK_TERMINATE(test2_flg_task);
    /* 销毁子任务3 */
    AW_TASK_TERMINATE(test3_flg_task);

    /* 销毁节点 */
    ret = aw_flag_node_terminate(&__g_flg_node0);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node_terminate err: %d\n", ret));
        return;
    }
    ret = aw_flag_node_terminate(&__g_flg_node1);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node_terminate err: %d\n", ret));
        return;
    }

    /* 销毁事件组对象 */
    ret = aw_flag_terminate(&__g_flg_grp);
    if (ret != AW_OK) {
        AW_ERRF(("aw_flag_node_terminate err: %d\n", ret));
        return;
    }
}
/** [src_flag_grp] */

/* end of file */
