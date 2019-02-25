/*
 * app_common.c
 *
 *  Created on: 2018年5月18日
 *      Author: wengyedong
 */

#include "aworks.h"

#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "BUTTON.h"
#include "MESSAGEBOX.h"

#include "resource/app_resource.h"

#include "string.h"


#define __ID_DLG             (GUI_ID_USER + 0xFFF)

#define __ID_DLG_FRAMEWIN           (__ID_DLG + 0)
#define __ID_DLG_TEXT               (__ID_DLG + 1)
#define __ID_DLG_NO                 (__ID_DLG + 2)
#define __ID_DLG_YES                (__ID_DLG + 3)




/******************************************************************************/
aw_local void __dialog_cb (WM_MESSAGE * pMsg)
{
    int      key;
    WM_HWIN  hitem;

    switch (pMsg->MsgId) {

    case WM_INIT_DIALOG:
        hitem = WM_GetDialogItem(pMsg->hWin, __ID_DLG_TEXT);
        TEXT_SetFont(hitem, &GUI_Font_app20);
        TEXT_SetTextAlign(hitem,TEXT_CF_HCENTER | TEXT_CF_VCENTER);

        hitem = WM_GetDialogItem(pMsg->hWin, __ID_DLG_YES);
        BUTTON_SetFont(hitem, &GUI_Font_app20);

        hitem = WM_GetDialogItem(pMsg->hWin, __ID_DLG_NO);
        BUTTON_SetFont(hitem, &GUI_Font_app20);
        break;

    case WM_NOTIFY_PARENT:
        key = WM_GetId(pMsg->hWinSrc);
        if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
            if (key == __ID_DLG_YES) {                     /* Yes Button    */
                GUI_EndDialog(pMsg->hWin, 0);
            } else if (key == __ID_DLG_NO) {               /* No Button     */
                GUI_EndDialog(pMsg->hWin, 1);
            }
        }
        break;

    default:
       WM_DefaultProc(pMsg);
    }
}




/******************************************************************************/
bool_t app_dialog (WM_HWIN hwin, const char *info)
{
    WM_HWIN                 hdlg;
    GUI_WIDGET_CREATE_INFO  dlg[] = {
        { FRAMEWIN_CreateIndirect, "",        __ID_DLG_FRAMEWIN, 110, 42,  250, 150 },
        { TEXT_CreateIndirect,     info,      __ID_DLG_TEXT,     65,  15,  130, 30 },
        { BUTTON_CreateIndirect,   "确定",     __ID_DLG_YES,       22,  69,  80,  30 },
        { BUTTON_CreateIndirect,   "取消",     __ID_DLG_NO,        140, 69,  80,  30 },
    };

    hdlg = GUI_CreateDialogBox(dlg, 4, &__dialog_cb, hwin, 0, 0);
    WM_MoveTo(hdlg,
             (WM_GetWindowSizeX(hwin) - WM_GetWindowSizeX(hdlg)) / 2 ,
             (WM_GetWindowSizeY(hwin) - WM_GetWindowSizeY(hdlg)) / 2);
    WM_MakeModal(hdlg);
    if (GUI_ExecCreatedDialog(hdlg) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}




/******************************************************************************/
void app_message_box (const char *msg, const char *capt, int flags)
{
    WM_HWIN  hwin;
    WM_HWIN  hitem;
    GUI_RECT rect;
    int      len, x;
    char     buf[64];
#define __FONT_WIDTH  8
#define __FONT_HIGH   18

    hwin = MESSAGEBOX_Create(msg, capt, flags);
    if (hwin == 0) {
        return;
    }
    FRAMEWIN_SetFont(hwin, &GUI_Font_app20);

    WM_GetWindowRectEx(hwin, &rect);
    WM_SetWindowPos(hwin,
                    rect.x0 - 40,
                    rect.y0 - 15,
                    rect.x1 - rect.x0 + 1 + 80,
                    rect.y1 - rect.y0 + 1 + 30);

    hitem = WM_GetDialogItem(hwin, GUI_ID_TEXT0);
    TEXT_SetFont(hitem, &GUI_Font_app20);

    app_utf82gbk(msg, buf, sizeof(buf));
    len = strlen(buf);
    len = len * __FONT_WIDTH;

    WM_GetWindowRectEx(hwin, &rect);
    rect.x0 += 5;
    rect.x1 -= 5;
    if (len >= (rect.x1 - rect.x0)) {
        x   = rect.x0 ;
        len = rect.x1 - rect.x0;
    } else {
        x = rect.x0 + (((rect.x1 - rect.x0) - len) / 2) + 8;
    }
    WM_SetWindowPos(hitem,
                    x,
                    rect.y0 + 32,
                    len,
                    __FONT_HIGH);

    hitem = WM_GetDialogItem(hwin, GUI_ID_OK);
    BUTTON_SetFont(hitem, &GUI_Font_app20);

    len = rect.x1 - rect.x0;
    x   = rect.x0;
    WM_GetWindowRectEx(hitem, &rect);
    if ((rect.x1 - rect.x0) < len) {
        x = x + ((len - (rect.x1 - rect.x0)) / 2) + 2;
    }

    WM_SetWindowPos(hitem,
                    x,
                    rect.y0 + 15,
                    rect.x1 - rect.x0,
                    rect.y1 - rect.y0);

    GUI_ExecCreatedDialog(hwin);
}


