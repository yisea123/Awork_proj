/*
 * app_net.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "aw_mem.h"
#include "aw_nvram.h"
#include "lwip/inet.h"
#include "net/aw_netif.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "EDIT.h"
#include "BUTTON.h"
#include "DROPDOWN.h"

#include "../resource/app_resource.h"

#include "string.h"
#include "stdio.h"

#define ID_FRAMEWIN0           (GUI_ID_USER + 1)
#define ID_FRAMEWIN1           (GUI_ID_USER + 2)
#define ID_TEXT0               (GUI_ID_USER + 3)
#define ID_TEXT1               (GUI_ID_USER + 4)
#define ID_EDIT_IP             (GUI_ID_USER + 5)
#define ID_EDIT_MASK           (GUI_ID_USER + 6)
#define ID_EDIT_GATE           (GUI_ID_USER + 7)
#define ID_BTN_CANCEL          (GUI_ID_USER + 8)
#define ID_BTN_OK              (GUI_ID_USER + 9)
#define ID_BUTTON              (GUI_ID_USER + 10)
#define ID_OK                  (GUI_ID_USER + 30)
#define ID_DROPDOWN            (GUI_ID_USER + 31)


aw_local const GUI_WIDGET_CREATE_INFO _aMessageOk[] = {
    { FRAMEWIN_CreateIndirect, "注意",            ID_FRAMEWIN1, 120, 101,  240, 105},
    { TEXT_CreateIndirect,     "网络地址输入格式有误", ID_TEXT1,      20,  10,  200, 25},
    { BUTTON_CreateIndirect,   "确定",            ID_OK,        82,  40,  75,  25},
};

aw_local GUI_WIDGET_CREATE_INFO _aMessageNoNet[] = {
    { FRAMEWIN_CreateIndirect, "警告", ID_FRAMEWIN1, 120, 101,  240, 105},
    { TEXT_CreateIndirect,     NULL,  ID_TEXT1,     20,  10,  200, 25},
    { BUTTON_CreateIndirect,   "确定", ID_OK,        82,  40,  75,  25},
};

static char *p_net_str[] = {"eth0", "eth1", "st", "ap"};

struct __net_cfg {
    char ip[16];
    char gate[16];
    char mask[16];
};

struct app_net {
    FRAMEWIN_Handle  happ;
};

#define __NET_NVRAM  "net_cfg"
#define __DEF_IP     "0.0.0.0"
#define __DEF_MASK   "0.0.0.0"
#define __DEF_GATE   "0.0.0.0"


/******************************************************************************/
aw_local void __dlg_ok_cb (WM_MESSAGE * pMsg) {
    int NCode, Id;
    WM_HWIN hDlg, hItem;
    hDlg = pMsg->hWin;

    switch (pMsg->MsgId) {

    case WM_DELETE:

        break;

    case WM_INIT_DIALOG:                               /* 初始化对话框      */
        hItem = WM_GetDialogItem(hDlg, ID_TEXT1);
        /* 设置text的字体 */
        TEXT_SetFont(hItem,&GUI_Font_app20);
        TEXT_SetTextAlign(hItem,TEXT_CF_HCENTER | TEXT_CF_VCENTER);

        FRAMEWIN_SetFont(hDlg,&GUI_Font_app20);

        hItem = WM_GetDialogItem(hDlg, ID_OK);
        BUTTON_SetFont(hItem, &GUI_Font_app20);

        break;

    case WM_NOTIFY_PARENT:
        Id    = WM_GetId(pMsg->hWinSrc);            /* 获取控件ID      */
        NCode = pMsg->Data.v;                       /* 获取消息                   */
        switch (NCode) {

        case WM_NOTIFICATION_RELEASED:              /* 控件被释放                */

            if (Id == ID_OK) {                     /* Yes Button    */
                GUI_EndDialog(hDlg, 0);             /* 结束对话框，返回0 */
            }
            break;
        }
        break;

    default:
      WM_DefaultProc(pMsg);
    }
}

/**
 * \brief 网卡不存在警告信息
 */
aw_local void __warning_net (char *p_net_name, FRAMEWIN_Handle  happ)
{
    char               warning_msg[64] = { 0 };
    WM_HWIN            hsure;

    strcpy(warning_msg, p_net_name);
    strcat(warning_msg, "未使能或不存在！");

    _aMessageNoNet[1].pName = warning_msg;
    hsure = GUI_CreateDialogBox(_aMessageNoNet,
                                GUI_COUNTOF(_aMessageNoNet),
                                &__dlg_ok_cb,
                                happ,
                                0, 0);

    WM_MoveTo(hsure,
              (WM_GetWindowSizeX(happ) - WM_GetWindowSizeX(hsure)) / 2 ,
              (WM_GetWindowSizeY(happ) - WM_GetWindowSizeY(hsure)) / 2);
    WM_MakeModal(hsure);
    if (GUI_ExecCreatedDialog(hsure) == 0) {
        /* 取消模态 */
        WM_MakeModal(0);
    }
}

/* 获得网卡信息 */
aw_local void __get_net_msg(aw_netif_t *p_netif, struct __net_cfg *p_cfg)
{
    struct in_addr     ip;

    aw_netif_ipv4_ip_get(p_netif, &ip);
    inet_ntoa_r(ip, p_cfg->ip, 16);
    aw_netif_ipv4_gw_get(p_netif, &ip);
    inet_ntoa_r(ip, p_cfg->gate, 16);
    aw_netif_ipv4_netmask_get(p_netif, &ip);
    inet_ntoa_r(ip, p_cfg->mask, 16);
}

/******************************************************************************/
aw_local void __key_pad_cb (WM_MESSAGE *pMsg)
{
    WM_HWIN hbtn;
    int     x, y, key;

#define __KEY_X_OFF  3
#define __KEY_Y_OFF  3
#define __KEY_XSIZ   51
#define __KEY_YSIZ   45

    const char *key_str[12] = {"7", "8", "9",
                               "4", "5", "6",
                               "1", "2", "3",
                               ".", "0", "←" };

    switch (pMsg->MsgId) {
    case WM_CREATE:
        for (y = 0; y < 4; y++) {
            for (x = 0; x < 3; x++) {
                hbtn = BUTTON_CreateEx((__KEY_X_OFF + __KEY_XSIZ * x),
                                       (__KEY_Y_OFF + __KEY_YSIZ * y),
                                       __KEY_XSIZ,
                                       __KEY_YSIZ,
                                       pMsg->hWin,
                                       WM_CF_SHOW | WM_CF_HASTRANS,
                                       0,
                                       ID_BUTTON + (y * 3) + x);
                BUTTON_SetText(hbtn, key_str[(y * 3) + x]);
                BUTTON_SetFont(hbtn, &GUI_Font_app20);
                BUTTON_SetBkColor(hbtn, BUTTON_CI_UNPRESSED, GUI_BLACK);
                BUTTON_SetFocussable(hbtn, 0);
            }
        }
        break;

    case WM_NOTIFY_PARENT:
        if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
            key = WM_GetId(pMsg->hWinSrc) - ID_BUTTON;
            if (key < 11) {
                GUI_StoreKeyMsg((int)*key_str[key], 1);
                GUI_StoreKeyMsg((int)*key_str[key], 0);
            } else if (key == 11) {
                GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 1);
                GUI_StoreKeyMsg(GUI_KEY_BACKSPACE, 0);
            }
        }
        break;

    case WM_PAINT:
        x = WM_GetWindowSizeX(pMsg->hWin);
        y = WM_GetWindowSizeY(pMsg->hWin);
        GUI_SetColor(GUI_GRAY);
        GUI_FillRect(0, 0, x, y);
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/******************************************************************************/
aw_local aw_err_t __cfg_check (struct __net_cfg *p_cfg)
{
    struct in_addr tmp = {0};

    if (inet_aton(p_cfg->ip, &tmp) == 0) {
        return -AW_EINVAL;
    }

    if (inet_aton(p_cfg->mask, &tmp) == 0) {
        return -AW_EINVAL;
    }

    if (inet_aton(p_cfg->gate, &tmp) == 0) {
        return -AW_EINVAL;
    }
    return AW_OK;
}




/******************************************************************************/
aw_local void __cfg_load (struct app_net   *p_app,
                          struct __net_cfg *p_cfg)
{
    aw_err_t            ret;
    struct __net_cfg    cfg;

    ret = aw_nvram_get(__NET_NVRAM, 0, (char *)&cfg, 0, sizeof(cfg));
    if (ret == AW_OK) {
        ret = __cfg_check(&cfg);
    }

    if (ret != AW_OK) {
        memset(&cfg, 0, sizeof(cfg));
        app_gbk2utf8(__DEF_IP,   cfg.ip,   sizeof(cfg.ip));
        app_gbk2utf8(__DEF_MASK, cfg.mask, sizeof(cfg.mask));
        app_gbk2utf8(__DEF_GATE, cfg.gate, sizeof(cfg.gate));
    }

    memcpy(p_cfg, &cfg, sizeof(cfg));
}




/******************************************************************************/
aw_local aw_err_t __cfg_save (struct app_net   *p_app,
                              struct __net_cfg *p_cfg)
{
    aw_err_t ret;

    ret = __cfg_check(p_cfg);
    if (ret != AW_OK) {
        return ret;
    }
    aw_nvram_set(__NET_NVRAM, 0, (char *)p_cfg, 0, sizeof(*p_cfg));
    return AW_OK;
}




/******************************************************************************/
aw_local void __app_net_cb (WM_MESSAGE * pMsg)
{
    struct app_net     *p_app;
    int                 id;
    static int          drop_down_sel = 0;
    aw_netif_t          *p_netif = NULL;
    struct __net_cfg    cfg;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        aw_mem_free(p_app);
        break;

    case WM_NOTIFY_PARENT:
        id = WM_GetId(pMsg->hWinSrc);
        switch (id) {
        case ID_BTN_CANCEL:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                /* 关闭窗口 */
                WM_DeleteWindow(pMsg->hWin);
            }
            break;

        case ID_BTN_OK:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                WM_HWIN             hitem;
                struct __net_cfg    cfg_new, cfg_sys;
                char                utf8[32];

                memset(&cfg_new, 0, sizeof(cfg_new));
                FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));

                hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_IP);
                EDIT_GetText(hitem, utf8, sizeof(utf8));
                app_utf82gbk(utf8, cfg_new.ip, sizeof(cfg_new.ip));

                hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MASK);
                EDIT_GetText(hitem, utf8, sizeof(utf8));
                app_utf82gbk(utf8, cfg_new.mask, sizeof(cfg_new.mask));

                hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_GATE);
                EDIT_GetText(hitem, utf8, sizeof(utf8));
                app_utf82gbk(utf8, cfg_new.gate, sizeof(cfg_new.gate));

                __cfg_load(p_app, &cfg_sys);

                if (memcmp(&cfg_new, &cfg_sys, sizeof(cfg_new))) {
                    if (__cfg_save(p_app, &cfg_new) != AW_OK) {
                        WM_HWIN hsure;
                        hsure = GUI_CreateDialogBox(_aMessageOk,
                                                    GUI_COUNTOF(_aMessageOk),
                                                    &__dlg_ok_cb,
                                                    pMsg->hWin,
                                                    0, 0);
                        WM_MoveTo(hsure,
                                (WM_GetWindowSizeX(pMsg->hWin) - WM_GetWindowSizeX(hsure)) / 2 ,
                                (WM_GetWindowSizeY(pMsg->hWin) - WM_GetWindowSizeY(hsure)) / 2);
                        WM_MakeModal(hsure);
                        if (GUI_ExecCreatedDialog(hsure) == 0) {
                            /* 取消模态 */
                            WM_MakeModal(0);
                        }
                    } else {
                        /* 重新配置net的ip地址 */
                        WM_HWIN hitem;
                        struct in_addr addr;
                        int ret;

                        p_netif = aw_netif_dev_open(p_net_str[drop_down_sel]);

                        hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_IP);
                        EDIT_GetText(hitem, cfg.ip, 16);
                        ipaddr_aton(cfg.ip, (ip_addr_t *)&addr);
                        ret = aw_netif_ipv4_ip_set(p_netif, &addr);

                        hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_GATE);
                        EDIT_GetText(hitem, cfg.ip, 16);
                        ipaddr_aton(cfg.ip, (ip_addr_t *)&addr);
                        ret = aw_netif_ipv4_gw_set(p_netif, &addr);

                        hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MASK);
                        EDIT_GetText(hitem, cfg.ip, 16);
                        ipaddr_aton(cfg.ip, (ip_addr_t *)&addr);
                        ret = aw_netif_ipv4_netmask_set(p_netif, &addr);

                        WM_DeleteWindow(pMsg->hWin);
                    }
                } else {
                    /* no change */
                    WM_DeleteWindow(pMsg->hWin);
                }
            }
            break;

        case ID_DROPDOWN:

            if (pMsg->Data.v == WM_NOTIFICATION_SEL_CHANGED) {
                WM_HWIN hitem;

                drop_down_sel = DROPDOWN_GetSel(pMsg->hWinSrc);
                p_netif = aw_netif_dev_open(p_net_str[drop_down_sel]);
                if (p_netif == NULL) {
                    /* 警告网卡不存在 */
                    __warning_net(p_net_str[drop_down_sel], pMsg->hWin);

                    /* 显示全0 */
                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_IP);
                    EDIT_SetText(hitem, "0.0.0.0");

                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MASK);
                    EDIT_SetText(hitem, "0.0.0.0");

                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_GATE);
                    EDIT_SetText(hitem, "0.0.0.0");
                } else {    /* 显示IP */
                    __get_net_msg(p_netif, &cfg);

                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_IP);
                    EDIT_SetText(hitem, cfg.ip);

                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_MASK);
                    EDIT_SetText(hitem, cfg.gate);

                    hitem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_GATE);
                    EDIT_SetText(hitem, cfg.mask);
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
aw_local void __text_edit (struct app_net *p_app,
                           const char     *name,
                           const char     *val,
                           int             y,
                           int             id)
{
    WM_HWIN hwin, hitem;
    char    utf8[48];

    hwin = WM_GetClientWindow(p_app->happ);

    /* 文本框 */
    hitem = TEXT_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2, y,
                          80, 30,
                          hwin,
                          WM_CF_SHOW,
                          TEXT_CF_LEFT | TEXT_CF_VCENTER,
                          ID_TEXT0,
                          name);
    TEXT_SetFont(hitem, &GUI_Font_app20);
    TEXT_SetTextColor(hitem, GUI_BLACK);

    /* 输入框 */
    hitem = EDIT_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2 + 85, y,
                          150, 30 ,
                          hwin,
                          WM_CF_SHOW,
                          0,
                          id,
                          50);
    EDIT_SetBkColor(hitem, EDIT_CI_ENABLED, GUI_WHITE);
    EDIT_SetFont(hitem, &GUI_Font_app20);
    EDIT_SetTextColor(hitem,EDIT_CI_ENABLED, GUI_BLACK);
    EDIT_SetTextAlign(hitem,TEXT_CF_HCENTER|TEXT_CF_VCENTER);
    EDIT_EnableBlink(hitem, 500, 1);

    /* 控件聚焦到输入框上 */
    WM_SetFocus(hitem);

    app_gbk2utf8(val, utf8, sizeof(utf8));
    EDIT_SetText(hitem, utf8);
}




/******************************************************************************/
void *app_net_create (WM_HWIN parent, const char *name)
{
    WM_HWIN            hwin;
    BUTTON_Handle      hbtn;
    DROPDOWN_Handle    hdropdown;
    TEXT_Handle        htext;

    struct app_net    *p_app;
    struct __net_cfg   cfg;
    GUI_RECT           rect;
    int                start_y;    /* 文本框和按键的起始y坐标 */
    int                i;
    aw_netif_t        *p_netif = NULL;

    p_app = aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }
    memset(p_app, 0, sizeof(*p_app));

    __cfg_load(p_app, &cfg);

    /* net */
    p_app->happ = FRAMEWIN_CreateUser(0, 0,
                                      WM_GetWindowSizeX(parent),
                                      WM_GetWindowSizeY(parent),
                                      parent,
                                      WM_CF_SHOW,
                                      0,
                                      ID_FRAMEWIN0,
                                      name,
                                      __app_net_cb,
                                      sizeof(p_app));
    if (p_app->happ == 0) {
        goto __failed;
    }

    FRAMEWIN_SetUserData(p_app->happ, &p_app, sizeof(p_app));
    FRAMEWIN_SetFont(p_app->happ, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    FRAMEWIN_SetClientColor(p_app->happ, GUI_LIGHTGRAY);

    hwin = WM_GetClientWindow(p_app->happ);

    start_y = (WM_GetWindowSizeY(hwin) - 215) / 2;

    /* 下拉菜单 */
    hdropdown = DROPDOWN_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2 + 85,
                                  start_y,
                                  100,
                                  90,
                                  hwin,
                                  WM_CF_SHOW,
                                  DROPDOWN_CF_AUTOSCROLLBAR,
                                  ID_DROPDOWN);

    DROPDOWN_SetFont(hdropdown, &GUI_Font_app20);
    for (i = 0; i < AW_NELEMENTS(p_net_str); i++) {
        DROPDOWN_AddString(hdropdown, p_net_str[i]);
    }

    htext = TEXT_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2, start_y,
                          80, 30,
                          hwin,
                          WM_CF_SHOW,
                          TEXT_CF_LEFT | TEXT_CF_VCENTER,
                          ID_TEXT0,
                          "选择网卡:");
    TEXT_SetFont(htext, &GUI_Font_app20);
    TEXT_SetTextColor(htext, GUI_BLACK);

    p_netif = aw_netif_dev_open(p_net_str[0]);
    if (p_netif == NULL) {  /* 警告网卡不存在 */
        __warning_net(p_net_str[0], p_app->happ);
    } else {                /* 获取网卡信息 */
        __get_net_msg(p_netif, &cfg);
    }

    __text_edit(p_app, "IP 地址:", cfg.ip, start_y + 45, ID_EDIT_IP);
    __text_edit(p_app, "默认网关:", cfg.gate, start_y + 90, ID_EDIT_GATE);
    __text_edit(p_app, "子网掩码:", cfg.mask, start_y + 135, ID_EDIT_MASK);

    /* 初始化BUTTON0 */
    hbtn = BUTTON_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2, start_y + 180,
                           100, 30,
                           hwin,
                           WM_CF_SHOW,
                           0,
                           ID_BTN_CANCEL);
    BUTTON_SetTextAlign(hbtn, TEXT_CF_VCENTER | TEXT_CF_HCENTER);
    BUTTON_SetFont(hbtn, &GUI_Font_app20);
    BUTTON_SetText(hbtn, "取消");
    BUTTON_SetFocussable(hbtn, 0);

    /* 初始化BUTTON1 */
    hbtn = BUTTON_CreateEx((WM_GetWindowSizeX(hwin) - 425) / 2 + 117, start_y + 180,
                           100, 30,
                           hwin,
                           WM_CF_SHOW,
                           0,
                           ID_BTN_OK);
    BUTTON_SetTextAlign(hbtn, TEXT_CF_VCENTER | TEXT_CF_HCENTER);
    BUTTON_SetFont(hbtn, &GUI_Font_app20);
    BUTTON_SetText(hbtn, "确认");
    BUTTON_SetFocussable(hbtn, 0);

    /* 获取客户端窗口的尺寸大小  */
    WM_GetClientRectEx(hwin, &rect);

    WM_CreateWindowAsChild((WM_GetWindowSizeX(hwin) - 425) / 2 + 265,
                           (rect.y1 - rect.y0 - 185) /  2,
                           160,
                           185,
                           hwin ,
                           WM_CF_SHOW | WM_CF_STAYONTOP,
                           __key_pad_cb,
                           0);
    return p_app;
__failed:
    if (p_app->happ) {
        WM_DeleteWindow(p_app->happ);
    }
    aw_mem_free(p_app);
    return NULL;
}




/******************************************************************************/
void app_net_destroy (void *p_arg)
{
    struct app_net *p_app = (struct app_net*)p_app;

    WM_DeleteWindow(p_app->happ);
}
