/*
 * app_obj_sample.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */



#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_mem.h"
#include "aw_ts.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "EDIT.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "GRAPH.h"

#include "string.h"
#include "stdio.h"

#include "../resource/app_resource.h"


#define ID_FRAMEWIN0        (GUI_ID_USER + 1)
#define ID_GRAPH0           (GUI_ID_USER + 2)
#define ID_SLIDER0          (GUI_ID_USER + 3)
#define ID_SLIDER1          (GUI_ID_USER + 4)
#define ID_BUTTON0          (GUI_ID_USER + 5)
#define ID_CHECK0           (GUI_ID_USER + 6)
#define ID_CHECK1           (GUI_ID_USER + 7)
#define ID_TEXT_CHN0        (GUI_ID_USER + 9)
#define ID_TEXT_CHN1        (GUI_ID_USER + 10)
#define ID_TEXT_CHN0_VAL    (GUI_ID_USER + 11)
#define ID_TEXT_CHN1_VAL    (GUI_ID_USER + 12)


#define __VSCALE_FACTOR     50
#define __VGRID_PIX         30
#define __HGRID_PIX         30



aw_local const GUI_COLOR __g_data_color[2] = {GUI_RED, GUI_GREEN};

struct app_vol_sample {
    FRAMEWIN_Handle     happ;
    GUI_MEMDEV_Handle   hmem;
    GRAPH_DATA_Handle   hdata[2];
    WM_HMEM             tmr;
    int                 ch_val[2];
};




/******************************************************************************/
aw_local void __graph_draw (WM_HWIN hwin, int stage)
{
    struct app_vol_sample *p_app;
    char                   buf[sizeof("--Channel %d: %-4d") + 8];
    GUI_RECT               rect;
    int                    i;
    WM_HWIN                hitem, hframe;

    if (stage == GRAPH_DRAW_LAST) {
        hframe = WM_GetParent(WM_GetParent(hwin));
        hitem = WM_GetDialogItem(hframe, ID_CHECK1);
        if (CHECKBOX_IsChecked(hitem)) {
            FRAMEWIN_GetUserData(hframe, &p_app, sizeof(p_app));
            GUI_SetFont(&GUI_Font16_ASCII);
            WM_GetClientRectEx(hwin, &rect);
            for (i = 0; i < AW_NELEMENTS(p_app->ch_val); i++) {
                aw_snprintf(buf, sizeof(buf), "--Channel %d: %-4d", i, p_app->ch_val[i]);
                GUI_SetColor(__g_data_color[i]);
                GUI_DispStringAt(buf, rect.x0 + 40, rect.y0 + i * 15);
            }
        }
    }
}




/******************************************************************************/
aw_local void __get_adc_data (struct app_vol_sample *p_app)
{
    aw_ts_id             sys_ts;
    struct aw_ts_state   val;

    sys_ts = aw_ts_serv_id_get("480x272", 0x00, 0x00);
    if (sys_ts == NULL) {
        while (1);//todo
    }

    aw_ts_get_phys(sys_ts, &val, 1);

    /* adc通道采样值 */
    p_app->ch_val[0] = val.x;
    GRAPH_DATA_YT_AddValue(p_app->hdata[0],  val.x / __VSCALE_FACTOR);

    p_app->ch_val[1] = val.y;
    GRAPH_DATA_YT_AddValue(p_app->hdata[1],  val.y / __VSCALE_FACTOR);
}




/******************************************************************************/
aw_local void __app_vol_sample_cb (WM_MESSAGE * pMsg)
{
    struct app_vol_sample *p_app;
    WM_HWIN                hitem;
    int                    id;
    bool_t                 stop;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        /* 重新显示光标 */
        GUI_CURSOR_Show();

        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        WM_DeleteTimer(p_app->tmr);
        GUI_MEMDEV_Delete(p_app->hmem);
        aw_mem_free(p_app);
        break;

    case WM_PAINT:
        FRAMEWIN_GetUserData(WM_GetParent(pMsg->hWin), &p_app, sizeof(p_app));
        GUI_MEMDEV_Write(p_app->hmem);
        break;

    case WM_TIMER:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        __get_adc_data(p_app);

        hitem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CHN0_VAL);
        EDIT_SetValue(hitem, p_app->ch_val[0]);
        hitem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_CHN1_VAL);
        EDIT_SetValue(hitem, p_app->ch_val[1]);

        hitem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON0);
        BUTTON_GetUserData(hitem, &stop, sizeof(stop));
        if (!stop) {
            WM_RestartTimer(p_app->tmr,  20);
        }
        break;

    case WM_NOTIFY_PARENT:
        id = WM_GetId(pMsg->hWinSrc);
        switch (id) {
        case ID_BUTTON0:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                BUTTON_GetUserData(pMsg->hWinSrc, &stop, sizeof(stop));
                stop = !stop;
                BUTTON_SetUserData(pMsg->hWinSrc, &stop, sizeof(stop));
                if (stop) {
                    BUTTON_SetText(pMsg->hWinSrc, "Run");
                    BUTTON_SetTextColor(pMsg->hWinSrc, BUTTON_CI_UNPRESSED, GUI_GREEN);
                } else {
                    BUTTON_SetText(pMsg->hWinSrc, "Stop");
                    BUTTON_SetTextColor(pMsg->hWinSrc, BUTTON_CI_UNPRESSED, GUI_RED);
                    FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
                    WM_RestartTimer(p_app->tmr,  20);
                }
            }
            break;

        case ID_CHECK0:
            if (pMsg->Data.v == WM_NOTIFICATION_VALUE_CHANGED) {
                /* Toggle grid */
                hitem = WM_GetDialogItem(pMsg->hWin, ID_GRAPH0);
                if (CHECKBOX_IsChecked(pMsg->hWinSrc)) {
                    GRAPH_SetGridVis(hitem, 1);
                } else {
                    GRAPH_SetGridVis(hitem, 0);
                }
            }
            break;
        default:break;

        }
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/******************************************************************************/
void *app_sample_create (WM_HWIN parent, const char *name)
{
    struct app_vol_sample *p_app;
    WM_HWIN                hwin;
    WM_HWIN                hitem;
    WM_HWIN                hwtmp;
    GUI_MEMDEV_Handle      hmtmp;
    GRAPH_SCALE_Handle     scale;
    int                    i;
    bool_t                 stop = FALSE;
    char                   buf[16];

#define __BORDER_TOP        0
#define __BORDER_BOTTOM     5
#define __BORDER_LEFT       30
#define __BORDER_RIGHT      0

    p_app = aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }
    memset(p_app, 0, sizeof(*p_app));

    p_app->happ = FRAMEWIN_CreateUser(0, 0,
                                      WM_GetWindowSizeX(parent),
                                      WM_GetWindowSizeY(parent),
                                      parent,
                                      WM_CF_SHOW,
                                      0,
                                      ID_FRAMEWIN0,
                                      name,
                                      __app_vol_sample_cb,
                                      sizeof(p_app));
    if (p_app->happ == 0) {
        goto __failed;
    }

    FRAMEWIN_SetUserData(p_app->happ, &p_app, sizeof(p_app));
    FRAMEWIN_SetClientColor(p_app->happ, GUI_LIGHTGRAY);
    FRAMEWIN_SetFont(p_app->happ, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
//    FRAMEWIN_AddMaxButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    hwin = WM_GetClientWindow(p_app->happ);

    p_app->tmr = WM_CreateTimer(hwin, 0, 1000, 0);

    p_app->hmem = GUI_MEMDEV_Create(WM_GetWindowOrgX(hwin),
                                    WM_GetWindowOrgY(hwin),
                                    WM_GetWindowSizeX(hwin),
                                    WM_GetWindowSizeY(hwin));
    if (p_app->hmem == 0) {
        goto __failed;
    }

    hwtmp = WM_SelectWindow(hwin);
    hmtmp = GUI_MEMDEV_Select(p_app->hmem);     /* 激活储存设备 */

    /* 创建图形控件 */
    hitem = GRAPH_CreateEx(0, 0,
                           WM_GetWindowSizeX(hwin),
                           WM_GetWindowSizeY(hwin) - 40,
                           hwin,
                           WM_CF_SHOW,
                           0,
                           ID_GRAPH0);
    GRAPH_SetBorder(hitem,
                    __BORDER_LEFT,
                    __BORDER_TOP,
                    __BORDER_RIGHT,
                    __BORDER_BOTTOM);

    for (i = 0; i < GUI_COUNTOF(p_app->hdata); i++) {
        /* 创建数据对象 */
        p_app->hdata[i] = GRAPH_DATA_YT_Create(__g_data_color[i], 800 , 0, 0);
        /* 将创建的数据对象附件到图形控件  */
        GRAPH_AttachData(hitem, p_app->hdata[i]);
    }

    /* 设置图形控件属性 */
    GRAPH_SetGridDistY(hitem, __VGRID_PIX);         /* 设置垂直方向从一条网格线到下一网格线的距离为8等分 */
    GRAPH_SetGridDistX(hitem, __HGRID_PIX);         /* 设置水平方向从一条网格线到下一网格线的距离为12等分 */
    GRAPH_SetGridVis(hitem, 1);                     /* 网格可见 */
    GRAPH_SetGridFixedX(hitem, 1);                  /* 固定x轴，其坐标不可以随滚动条发生变化  */
    GRAPH_SetUserDraw(hitem, __graph_draw);

    /* 添加垂直刻度 */
    scale = GRAPH_SCALE_Create(__BORDER_LEFT,
                               GUI_TA_RIGHT,
                               GRAPH_SCALE_CF_VERTICAL,
                               __VGRID_PIX);
    GRAPH_SCALE_SetFont(scale, &GUI_Font13B_ASCII);
    GRAPH_SCALE_SetTextColor(scale, GUI_YELLOW);

    /* 0.5个像素点代表一个刻度  */
    GRAPH_SCALE_SetFactor(scale, __VSCALE_FACTOR);
    /* 将垂直刻度对象添加到图形控件 */
    GRAPH_AttachScale(hitem, scale);

    for (i = 0; i < 2; i++) {
        snprintf(buf, sizeof(buf), "通道%d：", i);

        hitem = TEXT_CreateEx(5,
                              WM_GetWindowSizeY(hwin) - 40 + i * 20,
                              60,
                              20,
                              hwin,
                              WM_CF_SHOW,
                              0,
                              ID_TEXT_CHN0,
                              buf);
        TEXT_SetFont(hitem, &GUI_Font_app20);
        TEXT_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);

        hitem = EDIT_CreateEx(65,
                              WM_GetWindowSizeY(hwin) - 40 + i * 20 + 1,
                              50,
                              19,
                              hwin,
                              WM_CF_SHOW,
                              0,
                              ID_TEXT_CHN0_VAL + i,
                              16);
        EDIT_SetFont(hitem, &GUI_Font_app20);
        EDIT_SetBkColor(hitem, EDIT_CI_DISABLED, GUI_GRAY);
        EDIT_SetTextColor(hitem, EDIT_CI_DISABLED, __g_data_color[i]);
        EDIT_SetDecMode(hitem, 0, 0, 9999, 0, GUI_EDIT_SUPPRESS_LEADING_ZEROES);
        EDIT_SetTextAlign(hitem, EDIT_CF_RIGHT);
        EDIT_EnableBlink(hitem, 0, 0);
        WM_DisableWindow(hitem);
    }

    /* 停止按钮*/
    hitem = BUTTON_CreateUser(WM_GetWindowSizeX(hwin) - 85,
                              WM_GetWindowSizeY(hwin) - 35,
                              80,
                              30,
                              hwin,
                              WM_CF_SHOW,
                              0,
                              ID_BUTTON0,
                              sizeof(stop));
    BUTTON_SetFont(hitem, &GUI_Font20B_ASCII);
    BUTTON_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);
    BUTTON_SetText(hitem, "Stop");
    BUTTON_SetTextColor(hitem, BUTTON_CI_UNPRESSED, GUI_RED);
    BUTTON_SetUserData(hitem, &stop, sizeof(stop));

    /* 网格选项 */
    hitem = CHECKBOX_CreateEx(140,
                              WM_GetWindowSizeY(hwin) - 18,
                              50,
                              16,
                              hwin,
                              WM_CF_SHOW,
                              0,
                              ID_CHECK0);
    CHECKBOX_SetText(hitem, "Grid");
    CHECKBOX_SetState(hitem, 1);

    hitem = CHECKBOX_CreateEx(140,
                              WM_GetWindowSizeY(hwin) - 36,
                              50,
                              16,
                              hwin,
                              WM_CF_SHOW,
                              0,
                              ID_CHECK1);
    CHECKBOX_SetText(hitem, "Info");
    CHECKBOX_SetState(hitem, 1);

    /* 返回初始句柄 */
    WM_SelectWindow(hwtmp);
    GUI_MEMDEV_Select(hmtmp);
    GUI_CURSOR_Hide();
    return p_app;

__failed:
    if (p_app->tmr) {
        WM_DeleteTimer(p_app->tmr);
    }
    if (p_app->hmem) {
        GUI_MEMDEV_Delete(p_app->hmem);
    }
    if (p_app->happ) {
        WM_DeleteWindow(p_app->happ);
    }
    aw_mem_free(p_app);
    return NULL;
}


