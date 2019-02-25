/*
 * app_desktop.c
 *
 *  Created on: 2018年5月11日
 *      Author: wengyedong
 */


#include "aworks.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_time.h"
#include "aw_delay.h"
#include "aw_vdebug.h"

#include "stdio.h"

#include "resource/app_resource.h"

#include "GUI.h"
#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "FRAMEWIN.h"
#include "HEADER.h"
#include "PROGBAR.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "MULTIPAGE.h"




/* 桌面任务配置 */
#define __DESKTOP_TASK_PRIO          3
#define __DESKTOP_TASK_STACK_SIZE    (64 * 1024)
AW_TASK_DECL_STATIC(__desktop_task, __DESKTOP_TASK_STACK_SIZE);


/* 状态栏控件ID */
#define __ID_TEXT_LOGO              GUI_ID_TEXT0
#define __ID_TEXT_TIME              GUI_ID_TEXT1
#define __ID_PROGBAR_POWER          GUI_ID_PROGBAR0
#define __ID_ICON_PAGE0             GUI_ID_ICONVIEW0


/* APP接口 */
extern void *app_explorer_create (WM_HWIN hwin, const char *name);
extern void *app_net_create (WM_HWIN parent, const char *name);
extern void *app_task_manage_create (WM_HWIN parent, const char *name);
extern void *app_sys_info_create (WM_HWIN parent, const char *name);
extern void *app_control_create (WM_HWIN parent, const char *name);
extern void *app_sample_create (WM_HWIN parent, const char *name);
extern void *app_clock_create (WM_HWIN parent, const char *name);
extern void *app_explorer_create (WM_HWIN parent, const char *name);
extern void *app_update_create (WM_HWIN parent, const char *name);
extern void *app_calibrate_create (WM_HWIN parent, const char *name);


struct app_desktop {
    WM_HWIN hwsta;       /* 状态栏窗口句柄（顶部） */
    WM_HWIN hwicon;      /* 图标窗口句柄 */
} __app_desktop;


struct app_obj {
  const GUI_BITMAP *p_icon;       /* 图标 */
  const char       *p_name;       /* 标题 */
  void *(*pfn_create)(WM_HWIN hwin, const char *name);
  void (*pfn_destory)(void *p_handle);
};




/********************************************************************************/
aw_local aw_const struct app_obj __g_app_objs[] = {
        {&bm_icon_folder,         "文件浏览",   app_explorer_create,   NULL},
        {&bm_icon_net,            "网络设置",   app_net_create,   NULL},
        {&bm_icon_taskmanager,    "任务管理",   app_task_manage_create,   NULL},
        {&bm_icon_sysinfo,        "系统信息",   app_sys_info_create,   NULL},
        {&bm_icon_control,        "外设控制",   app_control_create,   NULL},
        {&bm_icon_sample,         "数据采集",   app_sample_create,   NULL},
        {&bm_icon_clock,          "时钟",      app_clock_create,   NULL},
        {&bm_icon_update,         "系统升级",   app_update_create,   NULL},
        {&bm_icon_calibration,    "触摸校准",   app_calibrate_create,   NULL},
};




/********************************************************************************/
aw_local void __def_set (void)
{
    GUI_CURSOR_Select(&GUI_CursorArrowM);
    GUI_CURSOR_SetPositionEx(30, 10, 0);
    GUI_CURSOR_Show();
    GUI_TOUCH_SetLayer(0);

    /* 默认是500ms， 参数 一定程度上决定的灵敏度，能决定灵敏度， */
    WM_MOTION_SetDefaultPeriod(500);

    WM_MULTIBUF_Enable(1);
    WM_EnableMemdev(WM_HBKWIN);

    /* 启用Alpha */
    GUI_EnableAlpha(1);

    /* Unicode中文支持 */
    GUI_UC_SetEncodeUTF8();         /* UTF-8支持 */

    /* 设计使用的默认字体 */
    GUI_SetDefaultFont(&GUI_Font_app20);

    /* 设置空间默认皮肤 */
    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
    SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

    SCROLLBAR_SetDefaultWidth(16);
}




/********************************************************************************/
aw_local void __win_status_cb (WM_MESSAGE *pMsg)
{
    WM_HWIN hitem;
    WM_HMEM timer = 0;
    aw_tm_t tm;
    char    buf[9];
    int     len_x;

    switch (pMsg->MsgId) {
    case WM_PAINT:
        /* 绘制状态栏背景 */
        len_x = WM_GetWindowSizeX(pMsg->hWin);
        GUI_SetBkColor(0x383838);
        GUI_Clear();
        GUI_DrawBitmap(&bm_zlglogo, 0, 5);
        GUI_DispStringAt("AWorks", len_x / 2 - 40, 5);
        GUI_DrawBitmap(&bm_battery, len_x - 80 - 4, 7);

        GUI_SetColor(0x080808);
        GUI_DrawHLine(27, 0, LCD_GetXSize());
        break;

    case WM_CREATE:
        /* 创建一个进度条，用于显示电量 */
        len_x = WM_GetWindowSizeX(pMsg->hWin);
        hitem = PROGBAR_CreateEx(len_x - 80, 11,
                                 bm_battery.XSize -10,
                                 bm_battery.YSize -8,
                                 pMsg->hWin,
                                 WM_CF_SHOW,
                                 0,
                                 __ID_PROGBAR_POWER);
        PROGBAR_SetText(hitem, "");
        PROGBAR_SetSkinClassic(hitem);
        PROGBAR_SetBarColor(hitem, 0, GUI_GREEN);
        PROGBAR_SetBarColor(hitem, 1, 0x383838);
        PROGBAR_SetValue(hitem, 30);

        /* 创建文本框用户显示时间 */
        hitem = TEXT_CreateEx(len_x - 60, 0, 60, 28,
                              pMsg->hWin,
                              WM_CF_SHOW,
                              TEXT_CF_LEFT | TEXT_CF_VCENTER | WM_CF_SHOW,
                              __ID_TEXT_TIME,
                              "00:00:00");
        TEXT_SetFont(hitem, &GUI_Font_app20);
        TEXT_SetTextColor(hitem, GUI_WHITE);

        /* 定时器，用于定时更新时间文本 */
        timer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);
        WM_SetUserData(pMsg->hWin, &timer, sizeof(timer));
        break;

    case WM_DELETE:
        WM_GetUserData(pMsg->hWin, &timer, sizeof(timer));
        WM_DeleteTimer(timer);
        break;

    case WM_TIMER:
        /* 更新时间 */
        aw_tm_get(&tm);

        sprintf(buf, "%02d:%02d:%02d",
                tm.tm_hour,
                tm.tm_min,
                tm.tm_sec);

        hitem = WM_GetDialogItem(pMsg->hWin, __ID_TEXT_TIME);
        TEXT_SetText(hitem,buf);

        /* 更新电量  */
        hitem = WM_GetDialogItem(pMsg->hWin, __ID_PROGBAR_POWER);
        PROGBAR_SetValue(hitem, 80);//todo

        /* 重启定时器 */
        WM_RestartTimer(pMsg->Data.v,  1000);
        break;

    default:
        WM_DefaultProc(pMsg);
        break;

    }
}




/********************************************************************************/
aw_local void __win_icon_cb (WM_MESSAGE *pMsg)
{
    WM_HWIN hitem;
    int     i;

    switch (pMsg->MsgId) {
    case WM_CREATE:
        /* 创建图标控件 */
        hitem = ICONVIEW_CreateEx(
                        0, 0,
                        WM_GetWindowSizeX(pMsg->hWin),
                        WM_GetWindowSizeY(pMsg->hWin),
                        pMsg->hWin,
                        WM_CF_SHOW | WM_CF_HASTRANS,
                        0,
                        __ID_ICON_PAGE0,
                        70, 75);
        /* 设置选定图标的颜色 */
        ICONVIEW_SetBkColor(hitem, ICONVIEW_CI_SEL, GUI_BLUE | 0xC0000000);
        /* 设置小工具与图标的框架大小 */
        ICONVIEW_SetFrame(hitem, GUI_COORD_X, 20);
        /* 设置小工具与图标的框架大小 */
        ICONVIEW_SetFrame(hitem, GUI_COORD_Y, 30);

        /* 设置图标的字体 */
        ICONVIEW_SetFont(hitem, &GUI_Font_app20);

        /* 设置图标对齐方式 */
        ICONVIEW_SetIconAlign(hitem, ICONVIEW_IA_HCENTER | ICONVIEW_IA_TOP);
        ICONVIEW_SetTextAlign(hitem, GUI_TA_HCENTER | GUI_TA_BOTTOM);

        /* 设置图标间距 */
        ICONVIEW_SetSpace(hitem, GUI_COORD_X, 24);
        ICONVIEW_SetSpace(hitem, GUI_COORD_Y, 25);

        /* 设置初始选择的图标为 -1(尚未选择)*/
        ICONVIEW_SetSel(hitem, -1);

        /* 添加图标到图标控件 */
        for (i = 0 ; i < AW_NELEMENTS(__g_app_objs); i++) {
            ICONVIEW_AddBitmapItem(hitem, __g_app_objs[i].p_icon, __g_app_objs[i].p_name);
        }
        break;

    case WM_PAINT:
        /* 设置背景颜色  */
        GUI_SetBkColor(0x202020);
        GUI_Clear();
        break;

    case WM_NOTIFY_PARENT:  /* 发消息给父窗口 */
        if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
            int sel;

            /* 获取被选中的图标 */
            sel = ICONVIEW_GetSel(pMsg->hWinSrc);
            if (sel < AW_NELEMENTS(__g_app_objs)) {
                /* 执行对应APP */
                if (__g_app_objs[sel].pfn_create) {
                    __g_app_objs[sel].pfn_create(pMsg->hWin, __g_app_objs[sel].p_name);
                }

                ICONVIEW_SetSel(pMsg->hWinSrc, -1);
            }
        }
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/********************************************************************************/
aw_local void __desktp_task_handel (void *p_arg)
{
    /* 默认设置 */
    __def_set();

    /* 创建状态栏 */
    __app_desktop.hwsta = WM_CreateWindowAsChild(
                                0, 0,
                                LCD_GetXSize(),
                                28,//TODO
                                WM_HBKWIN,
                                WM_CF_SHOW,
                                __win_status_cb,
                                sizeof(WM_HMEM));

    /* 创建桌面图标 */
    __app_desktop.hwicon = WM_CreateWindowAsChild(
                                0, 28,
                                LCD_GetXSize(),
                                LCD_GetYSize() - 28,
                                WM_HBKWIN,
                                WM_CF_SHOW,
                                __win_icon_cb,
                                0);

    AW_FOREVER {
        /* 持续运行UI */
        GUI_Exec();
        aw_mdelay(10);
    }
}





/********************************************************************************/
void app_desktop_init (void)
{
    AW_TASK_INIT(__desktop_task,                  /* 任务实体 */
                 "desktop",                       /* 任务名字 */
                 __DESKTOP_TASK_PRIO,             /* 任务优先级 */
                 __DESKTOP_TASK_STACK_SIZE,       /* 任务堆栈大小 */
                 __desktp_task_handel,            /* 任务入口函数 */
                 NULL);                           /* 任务入口参数 */

    /* 启动任务 */
    AW_TASK_STARTUP(__desktop_task);
}
