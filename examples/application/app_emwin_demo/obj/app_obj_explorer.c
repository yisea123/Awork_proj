/*
 * app_obj_explorer.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_mem.h"

#include "io/aw_dirent.h"
#include "io/sys/aw_stat.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TREEVIEW.h"
#include "TEXT.h"
#include "BUTTON.h"

#include "../resource/app_resource.h"

#include "string.h"
#include "stdio.h"
#include "stdlib.h"

struct app_explorer {
    FRAMEWIN_Handle      happ;
    TREEVIEW_Handle      htree;
    char                *path_get;
    char                 pwd[255];
};


#define __ROOT_DIR      "/"
#define __UP_LAYER_DIR  "..(上级目录)"
#define __PATH_LEN      256

#define ID_FRAMEWIN0           (GUI_ID_USER + 0x00)
#define ID_TREEVIEW0           (GUI_ID_USER + 0x01)

#define ID_FRAMEWIN1           (GUI_ID_USER + 0x02)
#define ID_TEXT0               (GUI_ID_USER + 0x03)
#define ID_NO                  (GUI_ID_USER + 0x04)
#define ID_YES                 (GUI_ID_USER + 0x05)



int app_explorer_destroy (void *p_arg);

extern bool_t app_dialog (WM_HWIN hwin, const char *info);
extern void app_message_box (const char *msg, const char *capt, int flags);




/******************************************************************************/
aw_local TREEVIEW_Handle __tree_clr (TREEVIEW_Handle htree)
{
    TREEVIEW_Handle      uplayer = 0;
    TREEVIEW_ITEM_Handle hitem;
    TREEVIEW_ITEM_INFO   info;
    char                 utf8[255];
    do {
        hitem = TREEVIEW_GetItem(htree, 0, TREEVIEW_GET_LAST);
        if (hitem) {
            TREEVIEW_ITEM_GetInfo(hitem, &info);
            if (info.IsNode) {
                TREEVIEW_ITEM_GetText(hitem, (U8*)utf8, sizeof(utf8));
                if (strcmp(__UP_LAYER_DIR, utf8) == 0) {
                    uplayer = (TREEVIEW_Handle)TREEVIEW_ITEM_GetUserData(hitem);
                }
            }
            TREEVIEW_ITEM_Detach(hitem);
            TREEVIEW_ITEM_Delete(hitem);
        }
    } while (hitem);

    return uplayer;
}




/******************************************************************************/
aw_local TREEVIEW_ITEM_Handle __dir_to_tree_scan (TREEVIEW_Handle  htree,
                                                  char            *path)
{
    TREEVIEW_ITEM_Handle  item = 0;
    struct aw_dir        *p_dir;
    struct aw_dirent     *p_dirent;
    struct aw_stat        sta;
    int                   end;
    aw_err_t              ret;
    char                  buf[__PATH_LEN];

    p_dir = aw_opendir(path);
    if (p_dir == NULL) {
        return 0;
    }

    end = strlen(path);

    while ((p_dirent = aw_readdir(p_dir)) != NULL) {
        /* 点表示当前目录，跳过  */
        if (*p_dirent->d_name == '.') {
            continue;
        }

        /*合成完整路径 , 递归检索*/
        sprintf(&path[end], "/%s", p_dirent->d_name);
        ret = aw_stat(path, &sta);

        if (ret != AW_OK) {
            /* 无法获取文件信息 */
            break;
        }

        app_gbk2utf8(p_dirent->d_name, buf, sizeof(buf));

        item = TREEVIEW_InsertItem(htree,
                                   S_ISDIR(sta.st_mode) ? 1 : 0,
                                   item,
                                   0,
                                   buf);
    }
    path[end] = '\0';
    aw_closedir(p_dir);
    return item;
}




/******************************************************************************/
aw_local char *__path_up (char *path)
{
    int idx;

    idx = strlen(path);
    if (idx == 0) {
        return path;
    }
    idx--;

    while ((path[idx] == '/') && (idx != 0)) {
        idx--;
    }

    if (idx == 0) {
        return path;
    }

    while ((path[idx] != '/') && (idx != 0)) {
        idx--;
    }

    path[idx + 1] = '\0';

    return path;
}




/******************************************************************************/
aw_local char *__path_down (char *path, const char *name)
{
    int idx;

    idx = strlen(path);

    if (idx && (path[idx - 1] != '/')) {
        path[idx] = '/';
        idx++;
    }

    strcpy(&path[idx], name);
    return path;
}




/******************************************************************************/
aw_local TREEVIEW_Handle __tree_create (struct app_explorer *p_app,
                                        const char          *name)
{
    TREEVIEW_Handle       htree;
    TREEVIEW_ITEM_Handle  hitem;
    WM_HWIN               hwin;

    hwin  = WM_GetClientWindow(p_app->happ);
    htree = TREEVIEW_CreateEx(0, 0,
                              WM_GetWindowSizeX(hwin),
                              WM_GetWindowSizeY(hwin),
                              hwin,
                              WM_CF_SHOW,
                              TREEVIEW_CF_AUTOSCROLLBAR_H,
                              ID_TREEVIEW0);
    if (htree) {
        TREEVIEW_SetAutoScrollV(htree, 1);
        TREEVIEW_SetSelMode(htree, TREEVIEW_SELMODE_ROW);
        TREEVIEW_SetFont(htree, &GUI_Font_app20);

        __path_down(p_app->pwd, name);
        __dir_to_tree_scan(htree, p_app->pwd);
        if (p_app->htree) {
            hitem = TREEVIEW_GetItem(htree, 0, TREEVIEW_GET_FIRST);
            hitem = TREEVIEW_InsertItem(htree, 1, hitem, 0, __UP_LAYER_DIR);
            TREEVIEW_ITEM_SetUserData(hitem, (U32)p_app->htree);
        }
        p_app->htree = htree;
    }

    return htree;
}




/******************************************************************************/
aw_local void __tree_delete (struct app_explorer *p_app,
                             TREEVIEW_Handle      htree,
                             TREEVIEW_ITEM_Handle uplayer)
{
    if (htree == 0) {
        return;
    }
    p_app->htree = (TREEVIEW_Handle)TREEVIEW_ITEM_GetUserData(uplayer);
    __path_up(p_app->pwd);
    WM_DeleteWindow(htree);
}




/******************************************************************************/
aw_local aw_err_t __open_item (struct app_explorer *p_app,
                               TREEVIEW_Handle      htree,
                               TREEVIEW_ITEM_Handle item)
{
    TREEVIEW_ITEM_INFO  info;
    char                gbk[__PATH_LEN];
    char                utf8[__PATH_LEN];

    TREEVIEW_ITEM_GetInfo(item, &info);
    TREEVIEW_ITEM_GetText(item, (U8*)utf8, sizeof(utf8));

    if (info.IsNode) {
        if (strcmp(__UP_LAYER_DIR, utf8) == 0) {
            __tree_delete(p_app, htree, item);
            return AW_OK;
        }

        app_utf82gbk(utf8, gbk, sizeof(gbk));

        __tree_create(p_app, gbk);
    } else {
        int  len;
        sprintf(gbk, "%s/", p_app->pwd);
        len = strlen(gbk);

        app_utf82gbk(utf8, &gbk[len], sizeof(gbk) - len);

        aw_kprintf("the file or dir name gbk %s \r\n", gbk);

        if (p_app->path_get == NULL) {
            if (app_dialog(p_app->happ, "是否打开文件？")) {
                /* 联消模态窗口  */
                WM_MakeModal(0);
                //todo 执行选中文件
                app_message_box("文件类型不支持", "错误", GUI_MESSAGEBOX_CF_MODAL);
            }
        }
    }

    return AW_OK;
}




/******************************************************************************/
aw_local int __button_skin_cb (const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo)
{
    uint8_t  pensize = 0;
    int      id;
    GUI_RECT rect;

    id = WM_GetId(pDrawItemInfo->hWin);

    if (pDrawItemInfo->Cmd == WIDGET_ITEM_DRAW_BITMAP) {
        switch (id) {
        case GUI_ID_CLOSE:
            /* 设置显示方框的颜色 */
            GUI_SetColor(GUI_BLACK);
            pensize = GUI_GetPenSize();
            WM_GetWindowRectEx(pDrawItemInfo->hWin,   &rect);

            GUI_SetPenSize(2);

            GUI_AA_DrawLine(5, 5, rect.x1 - rect.x0 -5 , rect.y1 - rect.y0 - 5);
            GUI_AA_DrawLine(5, rect.y1 - rect.y0 - 5, rect.x1 - rect.x0 -5 , 5);

            GUI_SetPenSize(pensize);
            break;

        case GUI_ID_MINIMIZE:
            GUI_DrawBitmap(&bm_button_refresh,
                           (WM_GetWindowSizeX(pDrawItemInfo->hWin) - bm_button_refresh.XSize) / 2,
                           (WM_GetWindowSizeY(pDrawItemInfo->hWin) - bm_button_refresh.YSize) / 2);
            break;

        case GUI_ID_MAXIMIZE:
            /* 设置显示方框的颜色 */
            GUI_SetColor(GUI_BLACK);

            pensize = GUI_GetPenSize();
            WM_GetWindowRectEx(pDrawItemInfo->hWin, &rect);

            GUI_SetPenSize(2);

            GUI_AA_DrawLine(5, (rect.y1 - rect.y0) / 2, 9 , (rect.y1 - rect.y0) / 2 + 6);
            GUI_AA_DrawLine(9, (rect.y1 - rect.y0) / 2 + 6, rect.x1 - rect.x0 -5 , 5);

            GUI_SetPenSize(pensize);
            break;
        }
    } else {
        BUTTON_DrawSkinFlex(pDrawItemInfo);
    }

    return 0;
}




/******************************************************************************/
aw_local void __close_cb (WM_MESSAGE * pMsg)
{
    struct app_explorer *p_app;
    GUI_PID_STATE        state;
    WM_HWIN              hwin;

    switch (pMsg->MsgId) {

    case WM_PID_STATE_CHANGED:
        GUI_TOUCH_GetState(&state);
        if (!state.Pressed) {
            hwin = WM_GetParent(pMsg->hWin);
            FRAMEWIN_GetUserData(hwin, &p_app, sizeof(p_app));
            app_explorer_destroy(p_app);
            return;
        }
        break;
    default:
        BUTTON_Callback(pMsg);
        break;

    }
}


/******************************************************************************/
aw_local void __refresh_cb (WM_MESSAGE * pMsg)
{
    struct app_explorer *p_app;
    GUI_PID_STATE        state;
    WM_HWIN              hwin;

    switch (pMsg->MsgId) {

    case WM_PID_STATE_CHANGED:
        GUI_TOUCH_GetState(&state);
        if (!state.Pressed) {
            hwin = WM_GetParent(pMsg->hWin);
            FRAMEWIN_GetUserData(hwin, &p_app, sizeof(p_app));
            if (p_app->htree) {
                TREEVIEW_Handle uplayer;

                uplayer = __tree_clr(p_app->htree);
                __dir_to_tree_scan(p_app->htree, p_app->pwd);

                if (uplayer) {
                    TREEVIEW_ITEM_Handle hitem;
                    hitem = TREEVIEW_GetItem(p_app->htree, 0, TREEVIEW_GET_FIRST);
                    hitem = TREEVIEW_InsertItem(p_app->htree, 1, hitem, 0, __UP_LAYER_DIR);
                    TREEVIEW_ITEM_SetUserData(hitem, (U32)uplayer);
                }
            }
        }
        break;
    default:
        BUTTON_Callback(pMsg);
        break;

    }
}

/******************************************************************************/
aw_local void __confirm_cb (WM_MESSAGE * pMsg)
{
    struct app_explorer *p_app;
    GUI_PID_STATE        state;
    WM_HWIN              hwin;

    switch (pMsg->MsgId) {

    case WM_PID_STATE_CHANGED:
        GUI_TOUCH_GetState(&state);
        if (!state.Pressed) {
            TREEVIEW_ITEM_Handle choose;
            char                 utf8[255];
            int                  len;

            hwin = WM_GetParent(pMsg->hWin);
            FRAMEWIN_GetUserData(hwin, &p_app, sizeof(p_app));

            if (p_app->htree) {
                choose = TREEVIEW_GetSel(p_app->htree);

                if (p_app->path_get) {
                    if (choose) {
                        TREEVIEW_ITEM_GetText(choose, (U8*)utf8, sizeof(utf8));
                        len = strlen(p_app->pwd);
                        p_app->pwd[len++] = '/';
                        app_utf82gbk(utf8, &p_app->pwd[len], sizeof(p_app->pwd[len]) - len);
                    }
                    strcpy(p_app->path_get, p_app->pwd);
                    app_explorer_destroy(p_app);
                } else {
                    if (choose) {
                        if (__open_item(p_app,
                                        p_app->htree,
                                        choose) == AW_OK) {

                        }
                    }
                }
            }
            return;
        }
        break;
    default:
        BUTTON_Callback(pMsg);
        break;
    }
}



/******************************************************************************/
aw_local void __app_explorer_cb (WM_MESSAGE * pMsg)
{
    struct app_explorer            *p_app;
    TREEVIEW_ITEM_Handle            cur_item = 0;
    aw_local TREEVIEW_ITEM_Handle   last_item = 0;
    TREEVIEW_ITEM_INFO              item_info;
    aw_local GUI_TIMER_TIME         last_tm = 0;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        aw_mem_free(p_app);
        break;

    case WM_NOTIFY_PARENT:
        switch(pMsg->Data.v)    {
        case WM_NOTIFICATION_CLICKED:
            break;

        case WM_NOTIFICATION_RELEASED:    /* 释放消息 */

            /* 查看选中了哪个项目 */
            cur_item = TREEVIEW_GetSel(pMsg->hWinSrc);
            /* 获取该项目的信息 */
            TREEVIEW_ITEM_GetInfo(cur_item, &item_info);

            if (last_item == cur_item) {
                GUI_TIMER_TIME tm;

                tm = GUI_GetTime() - last_tm;
                if(abs(tm) > 800) {
                    last_tm = GUI_GetTime();
                } else {
                    FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
                    if (__open_item(p_app,
                                    pMsg->hWinSrc,
                                    cur_item) == AW_OK) {

                    }
                }
                last_item = 0;
            } else {
                last_item = cur_item;
                last_tm = GUI_GetTime();
            }
        }
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}



/******************************************************************************/
void *app_explorer_create_ex (WM_HWIN     parent,
                              const char *name,
                              char       *path_get)
{
    struct app_explorer    *p_app;
    WM_HWIN                 hwin = 0;

    p_app = aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }
    memset(p_app, 0, sizeof(*p_app));

    if (path_get) {
        p_app->path_get = path_get;
    }

    /* 创建文件浏览器  */
    p_app->happ = FRAMEWIN_CreateUser(0, 0,
                                      WM_GetWindowSizeX(parent),
                                      WM_GetWindowSizeY(parent),
                                      parent,
                                      WM_CF_SHOW,
                                      0,
                                      0,
                                      name,
                                      __app_explorer_cb,
                                      sizeof(p_app));
    if (p_app->happ == 0) {
        goto __failed;
    }

    FRAMEWIN_SetUserData(p_app->happ, &p_app, sizeof(p_app));

    /* 设置字体 */
    FRAMEWIN_SetFont(p_app->happ, &GUI_Font_app20);

    /* 使能关闭按钮 */
    hwin = FRAMEWIN_AddCloseButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    WM_SetCallback(hwin, __close_cb);
    BUTTON_SetFont(hwin, &GUI_Font_app20);
    BUTTON_SetSkin(hwin, __button_skin_cb);

    hwin = FRAMEWIN_AddMinButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    WM_SetCallback(hwin, __refresh_cb);
    BUTTON_SetFont(hwin, &GUI_Font_app20);
    BUTTON_SetSkin(hwin, __button_skin_cb);

    hwin = FRAMEWIN_AddMaxButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    BUTTON_SetFont(hwin, &GUI_Font_app20);
    WM_SetCallback(hwin, __confirm_cb);
    BUTTON_SetSkin(hwin, __button_skin_cb);

    if (__tree_create(p_app, __ROOT_DIR) == 0) {
        goto __failed;
    }

    return (void *)p_app;

__failed:
    if (p_app->happ) {
        WM_DeleteWindow(p_app->happ);
    }
    aw_mem_free(p_app);
    return NULL;
}



/******************************************************************************/
void *app_explorer_create (WM_HWIN hwin, const char *name)
{
    return app_explorer_create_ex(hwin, name, NULL);
}




/******************************************************************************/
int app_explorer_destroy (void *p_arg)
{
    struct app_explorer  *p_app;

    p_app = (struct app_explorer *)p_arg;

    /* 阻塞等待确认是否关闭程序 */
    if ((p_app->path_get) || (app_dialog(p_app->happ, "是否关闭程序？"))) {
        /* 关闭程序 */
        WM_DeleteWindow(p_app->happ);
        return 0;
    } else {
        return 1;
    }
}
