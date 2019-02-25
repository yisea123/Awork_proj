/*
 * app_obj_sys_info.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "aw_mem.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"

#include "../resource/app_resource.h"




#define ID_FRAMEWIN0           (GUI_ID_USER + 0x00)
#define ID_TEXT0               (GUI_ID_USER + 0x02)




aw_local aw_const char *__g_info_text[] = {
    "欢迎使用AWorks",
    "设备名称:",
    "AWorks版本:",
    "SDK版本:",
    "运行内存:",
    "分辨率",
};


aw_local aw_const char *__g_info_content[] = {
    "",
    "imxrt1050",
    "2.0.0",
    "1.0.1",
    "16M",
    "480*272"
};






/******************************************************************************/
aw_local void __app_sys_info_handler(WM_MESSAGE * pMsg)
{
    int nitem, item_h, i;

    switch (pMsg->MsgId) {
    case WM_PAINT:
        GUI_SetColor(GUI_BLACK);

        nitem  = AW_NELEMENTS(__g_info_text);
        item_h = WM_GetWindowSizeY(pMsg->hWin) / nitem;

        for (i = 0; i < nitem; i++) {
            GUI_DrawHLine(item_h * (i + 1) - 1,
                          0,
                          WM_GetWindowSizeX(pMsg->hWin) * 2 / 3 - 10);
        }

        GUI_DrawBitmap(&bm_aworks,
                       WM_GetWindowSizeX(pMsg->hWin) * 2 / 3 - 10,
                       25);
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/******************************************************************************/
aw_local void __text_line (WM_HWIN     hwin,
                           int         row,
                           int         high,
                           const char *key,
                           const char *val)
{
    TEXT_Handle htext;

    htext = TEXT_CreateEx(5,
                          high * row,
                          WM_GetWindowSizeX(hwin) / 3,
                          high,
                          hwin,
                          WM_CF_SHOW,
                          TEXT_CF_LEFT | TEXT_CF_VCENTER,
                          ID_TEXT0 + row,
                          key);
    TEXT_SetFont(htext, &GUI_Font_app20);

    htext = TEXT_CreateEx(WM_GetWindowSizeX(hwin) / 3,
                          high * row,
                          WM_GetWindowSizeX(hwin) / 3,
                          high,
                          hwin,
                          WM_CF_SHOW,
                          TEXT_CF_LEFT | TEXT_CF_VCENTER,
                          ID_TEXT0 + row,
                          val);
    TEXT_SetFont(htext, &GUI_Font_app20);
}




/******************************************************************************/
void *app_sys_info_create (WM_HWIN parent, const char *name)
{
    FRAMEWIN_Handle         happ;
    WM_HWIN                 hwin;
    int                     nitem, item_h, i;

    happ = FRAMEWIN_CreateEx(0, 0,
                             WM_GetWindowSizeX(parent),
                             WM_GetWindowSizeY(parent),
                             parent,
                             WM_CF_SHOW,
                             0,
                             ID_FRAMEWIN0,
                             name,
                             __app_sys_info_handler);

    FRAMEWIN_AddCloseButton(happ, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_SetFont(happ, &GUI_Font_app20);
    FRAMEWIN_SetTextColor(happ, GUI_WHITE);

    /* 获取框架窗口用户区的句柄 */
    hwin = WM_GetClientWindow(happ);

    nitem  = AW_NELEMENTS(__g_info_text);
    item_h = WM_GetWindowSizeY(hwin) / nitem;

    for (i = 0; i < nitem; i++) {
        __text_line(hwin, i, item_h, __g_info_text[i], __g_info_content[i]);
    }

    return (void *)happ;
}
