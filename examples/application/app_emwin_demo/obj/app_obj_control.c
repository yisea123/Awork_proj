/*
 * app_obj_control.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */


#include "aworks.h"
#include "aw_buzzer.h"
#include "aw_led.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "CHECKBOX.h"

#include "../resource/app_resource.h"



#define ID_FRAMEWIN_0  (GUI_ID_USER + 0x00)
#define ID_CHECK_0     (GUI_ID_USER + 0x01)
#define ID_CHECK_1     (GUI_ID_USER + 0x02)

#define LED            0


/******************************************************************************/
aw_local void __chk_cb (WM_MESSAGE * pMsg)
{
    GUI_CONST_STORAGE GUI_BITMAP *p_on, *p_off;
    int               id;

    switch (pMsg->MsgId) {
    case WM_PAINT:
        id = WM_GetId(pMsg->hWin);
        if (id == ID_CHECK_0) {
            p_on  = &bm_led_on;
            p_off = &bm_led_off;
        } else if (id == ID_CHECK_1) {
            p_on  = &bmbuzzer_on;
            p_off = &bmbuzzer_off;
        }

        if (CHECKBOX_IsChecked(pMsg->hWin)) {
            GUI_DrawBitmap(p_on,
                          (WM_GetWindowSizeX(pMsg->hWin) - p_on->XSize) / 2,
                          (WM_GetWindowSizeY(pMsg->hWin) - p_on->YSize) / 2);
        } else {
            GUI_DrawBitmap(p_off,
                          (WM_GetWindowSizeX(pMsg->hWin) - p_off->XSize) / 2,
                          (WM_GetWindowSizeY(pMsg->hWin) - p_off->YSize) / 2);
        }
        break;

    case WM_NOTIFY_PARENT:
//        Id    = WM_GetId(pMsg->hWinSrc);            /* 获取控件ID      */
//        NCode = pMsg->Data.v;                       /* 获取消息                   */
//        switch (NCode) {
//
//        case WM_NOTIFICATION_RELEASED:              /* 控件被释放                */
//
//            if (Id == ID_OK) {                     /* Yes Button    */
//                GUI_EndDialog(hDlg, 0);             /* 结束对话框，返回0 */
//            }
//            break;
//        }
        break;

    default:
        CHECKBOX_Callback(pMsg);
        break;
    }
}




/******************************************************************************/
aw_local void __app_control_handler (WM_MESSAGE * pMsg)
{
    int id;

    switch (pMsg->MsgId) {
    case WM_NOTIFY_PARENT:
        id = WM_GetId(pMsg->hWinSrc);

        switch (id) {
        case ID_CHECK_0:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                if (CHECKBOX_IsChecked(pMsg->hWinSrc)) {
                    /* 打开LED */
                    aw_led_on(LED);
                } else {
                    /* 关闭LED */
                    aw_led_off(LED);
                }
            }
            break;

        case ID_CHECK_1:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                if (CHECKBOX_IsChecked(pMsg->hWinSrc)) {
                    /* 蜂鸣器鸣叫 */
                    aw_buzzer_on();
                } else {
                    /* 蜂鸣器关闭鸣叫 */
                    aw_buzzer_off();
                }
            }
            break;
        }
        break;  /* end of WM_NOTIFY_PARENT */

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/******************************************************************************/
void *app_control_create (WM_HWIN parent, const char *name)
{
    FRAMEWIN_Handle     happ;
    WM_HWIN             hwin;
    CHECKBOX_Handle     hchk;
    int                 xsiz;
    int                 ysiz;

    happ = FRAMEWIN_CreateEx(0, 0,
                             WM_GetWindowSizeX(parent),
                             WM_GetWindowSizeY(parent),
                             parent,
                             WM_CF_SHOW,
                             0,
                             ID_FRAMEWIN_0,
                             name,
                             __app_control_handler);
    FRAMEWIN_SetFont(happ, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(happ, FRAMEWIN_BUTTON_RIGHT, 0);
    hwin = WM_GetClientWindow(happ);

    xsiz = WM_GetWindowSizeX(hwin);
    ysiz = WM_GetWindowSizeY(hwin);

    hchk = CHECKBOX_CreateEx((xsiz / 2 - bm_led_off.XSize) / 2,
                             (ysiz - bm_led_off.XSize) / 2,
                             bm_led_off.XSize,
                             bm_led_off.YSize,
                             hwin,
                             WM_CF_SHOW | WM_CF_HASTRANS,
                             0,
                             ID_CHECK_0);
    CHECKBOX_SetSkinClassic(hchk);
    WM_SetCallback(hchk, __chk_cb);

    hchk = CHECKBOX_CreateEx((xsiz / 2) + (xsiz / 2 - bmbuzzer_off.XSize) / 2,
                             (ysiz - bmbuzzer_off.XSize) / 2,
                             bmbuzzer_off.XSize,
                             bmbuzzer_off.YSize,
                             hwin,
                             WM_CF_SHOW | WM_CF_HASTRANS,
                             0,
                             ID_CHECK_1);
    CHECKBOX_SetSkinClassic(hchk);
    WM_SetCallback(hchk, __chk_cb);

    aw_led_off(LED);
    aw_buzzer_off();

    return (void *)happ;

}
