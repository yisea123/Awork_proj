/*
 * app_update.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_mem.h"
#include "aw_delay.h"
#include "aw_wdt.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "EDIT.h"
#include "BUTTON.h"
#include "PROGBAR.h"


#include "../resource/app_resource.h"

#include "string.h"





#define ID_FRAMEWIN0           (GUI_ID_USER + 1)
#define ID_FRAMEWIN1           (GUI_ID_USER + 2)
#define ID_TEXT0               (GUI_ID_USER + 3)
#define ID_TEXT1               (GUI_ID_USER + 4)
#define ID_EDIT0               (GUI_ID_USER + 5)
#define ID_BUTTON0             (GUI_ID_USER + 6)
#define ID_BUTTON1             (GUI_ID_USER + 7)
#define ID_NO                  (GUI_ID_USER + 8)
#define ID_YES                 (GUI_ID_USER + 9)
#define ID_PROGBAR0            (GUI_ID_USER + 10)



extern void *app_explorer_create_ex (WM_HWIN parent, const char *name, char *path_get);
extern bool_t app_dialog (WM_HWIN hwin, const char *info);
extern void app_message_box (const char *msg, const char *capt, int flags);


aw_local const GUI_WIDGET_CREATE_INFO __dialog_progbar[] = {
    { FRAMEWIN_CreateIndirect, "",   ID_FRAMEWIN1, 110, 42,  250, 60 },
    { PROGBAR_CreateIndirect,  "",   ID_PROGBAR0,  5,  5,  230, 30 },
};




/******************************************************************************/
aw_local void __app_update_cb (WM_MESSAGE * pMsg)
{
    WM_HWIN  hwin;
    int      id;
    char    *p_buf;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_buf, sizeof(p_buf));
        if (p_buf) {
            aw_mem_free(p_buf);
        }
        break;

    case WM_PAINT:
        FRAMEWIN_GetUserData(WM_GetParent(pMsg->hWin), &p_buf, sizeof(p_buf));
        hwin = WM_GetDialogItem(pMsg->hWin, ID_EDIT0);
        if (p_buf[0] == '\0') {
            EDIT_SetText(hwin, "请选择固件文件（*.bin）");
            EDIT_SetTextColor(hwin, EDIT_CI_ENABLED, GUI_LIGHTGRAY);
        } else {
            char utf8[255];
            app_gbk2utf8(p_buf, utf8, sizeof(utf8));
            EDIT_SetText(hwin, utf8);
            EDIT_SetTextColor(hwin, EDIT_CI_ENABLED, GUI_BLACK);
        }
        break;

    case WM_NOTIFY_PARENT:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_buf, sizeof(p_buf));
        id = WM_GetId(pMsg->hWinSrc);
        if ((id == ID_BUTTON0) &&
            (pMsg->Data.v == WM_NOTIFICATION_RELEASED)) {
            app_explorer_create_ex(pMsg->hWin, "选择文件", p_buf);

        } else if ((id == ID_BUTTON1) &&
                   (pMsg->Data.v == WM_NOTIFICATION_RELEASED)) {

            if (app_dialog(pMsg->hWin, "是否进行升级？")) {
                WM_HWIN hitem;
                int     val;

                if (strstr(p_buf,".bin")) {
                    hwin = GUI_CreateDialogBox(__dialog_progbar,
                                                GUI_COUNTOF(__dialog_progbar),
                                                &WM_DefaultProc,
                                                pMsg->hWin,
                                                0, 0);
                    WM_MoveTo(hwin,
                             (WM_GetWindowSizeX(pMsg->hWin) - WM_GetWindowSizeX(hwin)) / 2 ,
                             (WM_GetWindowSizeY(pMsg->hWin) - WM_GetWindowSizeY(hwin)) / 2);
                    WM_MakeModal(hwin);

                    hitem = WM_GetDialogItem(hwin, ID_PROGBAR0);
                    PROGBAR_SetMinMax(hitem, 0, 100);
                    PROGBAR_SetFont(hitem, &GUI_Font_app20);

                    for (val = 0; val <= 100; val++) {
                        PROGBAR_SetValue(hitem, val);
                        aw_mdelay(100);
                        GUI_Exec();

                        //升级
                    }
                    GUI_EndDialog(hwin, 0);

                    if (app_dialog(pMsg->hWin, "是否重启系统？")) {
                        //reboot
//                        struct awbl_wdt  wdt;
//                        aw_wdt_add(&wdt, 1);
//                        while(1);//todo 等待重启
                    }
                } else {
                    app_message_box("文件不正确", "错误", GUI_MESSAGEBOX_CF_MODAL);
                }
            }
        }
        break;
    default:
        WM_DefaultProc(pMsg);
        break;

    }
}




/******************************************************************************/
void *app_update_create (WM_HWIN parent, const char *name)
{
    FRAMEWIN_Handle hframe;
    EDIT_Handle     hedit;
    BUTTON_Handle   hbutton;
    TEXT_Handle     htext;
    WM_HWIN         hwin;
    void           *p_buf;
    int             x_size;
    int             y_size;
    int             x_start;
    int             y_start;

#define __EDIT_BUF_SIZE  255

    p_buf = aw_mem_alloc(__EDIT_BUF_SIZE);
    if (p_buf == NULL) {
        return NULL;
    }
    memset(p_buf, 0, __EDIT_BUF_SIZE);

    hframe = FRAMEWIN_CreateUser(0, 0,
                                 WM_GetWindowSizeX(parent),
                                 WM_GetWindowSizeY(parent),
                                 parent,
                                 WM_CF_SHOW,
                                 0,
                                 ID_FRAMEWIN0,
                                 name,
                                 __app_update_cb,
                                 sizeof(p_buf));
    if (hframe == 0) {
        aw_mem_free(p_buf);
        return NULL;
    }

    FRAMEWIN_SetUserData(hframe, &p_buf, sizeof(p_buf));

    FRAMEWIN_SetFont(hframe, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(hframe, FRAMEWIN_BUTTON_RIGHT, 0);

    hwin = WM_GetClientWindow(hframe);

    x_size = WM_GetWindowSizeX(hwin);
    y_size = WM_GetWindowSizeY(hwin);
    x_start = (x_size - 440) / 2;
    y_start = (y_size - 100) / 2;

    htext = TEXT_CreateEx(x_start, y_start, 32, 30, hwin, WM_CF_SHOW , 0, ID_TEXT0, "固件");
    TEXT_SetFont(htext, &GUI_Font_app20);
    TEXT_SetTextAlign(htext, TEXT_CF_VCENTER | TEXT_CF_HCENTER);

    hedit = EDIT_CreateEx(x_start + 45, y_start, 355, 30, hwin, WM_CF_SHOW, 0, ID_EDIT0, 255);
    EDIT_SetFont(hedit, &GUI_Font_app20);
    EDIT_SetText(hedit, (char*)p_buf);

    hbutton = BUTTON_CreateEx(x_start + 410, y_start, 30, 30, hwin, WM_CF_SHOW, 0, ID_BUTTON0);
    BUTTON_SetFont(hbutton, &GUI_Font_app20);
    BUTTON_SetText(hbutton, "...");

    hbutton = BUTTON_CreateEx((x_size - 70) / 2, y_start + 60, 70, 40, hwin, WM_CF_SHOW, 0, ID_BUTTON1);
    BUTTON_SetFont(hbutton, &GUI_Font_app20);
    BUTTON_SetText(hbutton, "升级");

    return (void *)hframe;
}



