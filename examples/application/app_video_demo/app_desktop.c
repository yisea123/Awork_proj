/*
 * app_desktop.c
 *
 *  Created on: 2018年5月11日
 *      Author: wengyedong
 */

#include "app_video.h"


/** \brief 定义全局界面句柄*/
WM_HWIN  g_main_win;    /*主窗口句柄*/
WM_HWIN  g_tools_win;   /*工具窗口句柄*/
WM_HWIN  g_list_win;    /*问价列表窗口句柄*/

/** \brief 定义全局按钮操作状态*/
list_opt_format_t * gp_list_state;  /*文件列表操作状态*/
play_opt_format_t * gp_play_state;  /*播放按钮操作状态*/

/** \brief 桌面任务配置 */
#define __DESKTOP_TASK_PRIO          3                              /*优先级*/
#define __DESKTOP_TASK_STACK_SIZE    (64 * 1024)                    /*堆栈大小*/
AW_TASK_DECL_STATIC(__desktop_task, __DESKTOP_TASK_STACK_SIZE);     /*定义桌面任务*/


extern WM_HWIN CreateWindow(void);
extern WM_HWIN CreateTOOL(WM_HWIN hwin);
extern WM_HWIN CreateList(WM_HWIN hwin);

/** \brief
 * 桌面任务入口函数
 */
aw_local void __desktp_task_entry (void *p_arg)
{
    /* 默认设置 */
    GUI_CURSOR_Hide();
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();

    g_main_win  = CreateWindow();           /* 创建主窗口 */
    g_tools_win = CreateTOOL(g_main_win);   /* 控制按钮，进度条等 */
    g_list_win  = CreateList(g_main_win);   /* 创建文件列表 */

    AW_FOREVER {
        /* 持续运行UI */
        GUI_Exec();
        aw_mdelay(10);
    }
}

/**
 * 创建桌面任务
 */
void app_desktop_task (void)
{
    /*初始化文件列表按钮操作状态*/
    gp_list_state = (list_opt_format_t *)aw_mem_alloc(sizeof(list_opt_format_t));
    gp_list_state->list_btn_opt_state = LIST_SHOW; /*显示文件列表*/
    gp_list_state->list_file_opt_state = LIST_FILE_NO_OPERATION; /*文件列表误操作*/
    memset(gp_list_state->ready_to_play_filename,'\0',50); /*清空存储文件名字的数组*/

    /*初始化播放按钮操作状态*/
    gp_play_state = (play_opt_format_t *)aw_mem_alloc(sizeof(play_opt_format_t));
    gp_play_state->play_file_change_flag = 0; /*播放文件改变标志*/
    gp_play_state->stop_btn_opt_state = 0;
    gp_play_state->play_btn_opt_state = NO_OPERATION; /*播放按钮无操作*/

    /*初始化桌面任务*/
    AW_TASK_INIT(__desktop_task,                  /* 任务实体 */
                 "desktop",                       /* 任务名字 */
                 __DESKTOP_TASK_PRIO,             /* 任务优先级 */
                 __DESKTOP_TASK_STACK_SIZE,       /* 任务堆栈大小 */
                 __desktp_task_entry,            /* 任务入口函数 */
                 NULL);                           /* 任务入口参数 */

    /* 启动任务 */
    AW_TASK_STARTUP(__desktop_task);
}
