/*
 * app_task_manage.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */
#include "aworks.h"
#include "aw_mem.h"
#include "aw_vdebug.h"
#include "aw_delayed_work.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "MULTIPAGE.h"

#include "cpu_usage.h"
#include "rtk.h"

#include "../resource/app_resource.h"

#include "string.h"

#define ID_FRAMEWIN0           (GUI_ID_USER + 0x02)
#define ID_MULTIPAGE0          (GUI_ID_USER + 0x03)
#define ID_LISTVIEW0           (GUI_ID_USER + 0x04)
#define ID_GRAPH0              (GUI_ID_USER + 0x05)
#define WM_MSG_REFRESH         (WM_USER + 1)

/** \brief最大的统计任务为40个  */
#define AWORKS_TASK_NUM_MAX      40

#define __REFRESH_PERIOD        1000
#define __WORK_PERIOD           1000

struct __load_data {
    char taskprio[AWORKS_TASK_NUM_MAX][8];
    char stackuse[AWORKS_TASK_NUM_MAX][16];
    char stack_total[AWORKS_TASK_NUM_MAX][16];
    char taskload[AWORKS_TASK_NUM_MAX][8];
    const char *taskname[AWORKS_TASK_NUM_MAX];
    char cpuload;
};

struct app_task_manage {
    FRAMEWIN_Handle             happ;
    WM_HMEM                     tmr;
    GRAPH_DATA_Handle           hdata;
};

CPU_USAGE_DEF(                       __g_cpu_usage, AWORKS_TASK_NUM_MAX);
aw_local struct __load_data          __g_load_data;
aw_local bool_t                      __g_load_start = FALSE;
aw_local int                         __g_tsk_cnt;
aw_local struct aw_delayed_work      __g_dwork;
aw_local bool_t                      __g_work_run = FALSE;



/******************************************************************************/
aw_local void __graph_draw (WM_HWIN hWin, int stage)
{

    char     buf[36] = {0};
    GUI_RECT rect;

    if (stage == GRAPH_DRAW_LAST) {

        GUI_SetFont(&GUI_Font_app20);
        WM_GetInsideRect(&rect);
        rect.x0 = rect.x0 + 40;

        aw_snprintf(buf, sizeof(buf), "--使用率: %d%%", __g_load_data.cpuload);

        /* 显示采样值 */
        GUI_SetColor(GUI_GREEN);
        GUI_DispStringAt(buf, rect.x0, rect.y0);

    } else {
        /* 重新设置网格属性 */


    }
}




/******************************************************************************/
aw_local int __stk_chk (void            *p_arg,
                        struct rtk_task *p_task)
{
    unsigned int ntotal, nfree;

    int *pos = (int *)p_arg;

    if (aw_task_stack_check(p_task, &ntotal, &nfree) == 0) {

        aw_snprintf(__g_load_data.stackuse[*pos],
                    sizeof(__g_load_data.stackuse[*pos]),
                    "%d",
                    ntotal - nfree);

        aw_snprintf(__g_load_data.stack_total[*pos],
                    sizeof(__g_load_data.stack_total[*pos]),
                    "%d",
                    ntotal);
        *pos = *pos + 1;
    }

    return 0;
}




/******************************************************************************/
aw_local int __cpuload_get (void *arg, struct rtk_task *task, int percent)
{
    int *pos = (int *)arg;

    __g_load_data.taskname[*pos] = task->name;

    if (percent > 100) {
        percent = 100;
    }

    /* 判断那一个IDLE任务 */
    if (strcmp(task->name, "idle") == 0) {
        __g_load_data.cpuload = (char)(100 - percent);
    }

    aw_snprintf(__g_load_data.taskprio[*pos],
                sizeof(__g_load_data.taskprio[*pos]),
                "%d",
                task->current_priority);

    aw_snprintf(__g_load_data.taskload[*pos],
                sizeof(__g_load_data.taskload[*pos]),
                "%d",
                percent);

    *pos = *pos + 1;

    return 0;
}




/******************************************************************************/
aw_local void  __work_callback (void *p_arg)
{
    if (!__g_load_start) {
        cpu_usage_init(__g_cpu_usage);
        cpu_usage_clear(__g_cpu_usage);
        cpu_usage_start(__g_cpu_usage);
    } else {
        int tsk_cnt = 0;

        cpu_usage_stop(__g_cpu_usage);
        cpu_usage_for_each(__g_cpu_usage, __cpuload_get, &tsk_cnt);
        cpu_usage_destroy(__g_cpu_usage);

        tsk_cnt = 0;
        task_for_each((void *)__stk_chk, &tsk_cnt);

        __g_tsk_cnt = tsk_cnt;
    }
    __g_load_start = !__g_load_start;
    aw_delayed_work_start(&__g_dwork, 100);
}




aw_local void  __work_init (void)
{
    if (__g_work_run) {
        return;
    }
    __g_work_run = TRUE;
    aw_delayed_work_init(&__g_dwork, __work_callback, NULL);
    aw_delayed_work_start(&__g_dwork, 1000);
}




/******************************************************************************/
aw_local void __win_task_info_init (WM_MESSAGE * pMsg)
{
    WM_HWIN hitem, hhdr;
    int x_size;

    hitem = LISTVIEW_CreateEx(0, 0,
                              WM_GetWindowSizeX(pMsg->hWin),
                              WM_GetWindowSizeY(pMsg->hWin) - 20,
                              pMsg->hWin,
                              WM_CF_SHOW,
                              0,
                              ID_LISTVIEW0);

    /* 标题宽度 */
    hhdr = LISTVIEW_GetHeader(hitem);
    HEADER_SetHeight(hhdr, 30);
    HEADER_SetFont(hhdr, &GUI_Font_app20);
    HEADER_SetDragLimit(hhdr, 1);

    LISTVIEW_SetFont(hitem, &GUI_Font16_ASCII);
    LISTVIEW_SetAutoScrollV(hitem, 1);              /* 启用垂直滚动条 */

    LISTVIEW_SetBkColor(hitem,  LISTVIEW_CI_UNSEL, GUI_BLACK);
    LISTVIEW_SetBkColor(hitem,  LISTVIEW_CI_SEL,   GUI_BLACK);
    LISTVIEW_SetTextColor(hitem, LISTVIEW_CI_UNSEL,  GUI_GREEN);
    LISTVIEW_SetTextColor(hitem, LISTVIEW_CI_SEL,    GUI_GREEN);

    x_size = WM_GetWindowSizeX(hitem);

    LISTVIEW_AddColumn(hitem, x_size / 6, "优先级",   GUI_TA_VCENTER  | GUI_TA_LEFT);
    LISTVIEW_AddColumn(hitem, x_size / 6, "栈使用",   GUI_TA_VCENTER  | GUI_TA_LEFT);
    LISTVIEW_AddColumn(hitem, x_size / 6, "栈总量",   GUI_TA_VCENTER  | GUI_TA_LEFT);
    LISTVIEW_AddColumn(hitem, x_size / 6, "CPU",    GUI_TA_VCENTER  | GUI_TA_LEFT);
    LISTVIEW_AddColumn(hitem, x_size / 3, "任务名",   GUI_TA_VCENTER  | GUI_TA_LEFT);
}




/******************************************************************************/
aw_local void __task_info_cb (WM_MESSAGE * pMsg)
{
    WM_HWIN hitem;
    char    num[8] = {0};
    int     i, nrow, sel;
    char   *row_str[7]={" "," "," "," "," "," "," "};

    switch (pMsg->MsgId)  {
    case WM_CREATE:
        __win_task_info_init(pMsg);
        break;

    case WM_MSG_REFRESH:
        hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW0);

        sel = LISTVIEW_GetSel(hitem);
        nrow = LISTVIEW_GetNumRows(hitem);
        if (nrow != __g_tsk_cnt) {
            LISTVIEW_DeleteAllRows(hitem);
            nrow = 0;
        }

        for (i = 0; i < __g_tsk_cnt; i++) {
            if (nrow == 0) {
                LISTVIEW_AddRow(hitem, (GUI_ConstString *)row_str);
            }
            aw_snprintf(num,  sizeof(num), "%d", i);
            LISTVIEW_SetItemText(hitem, 0, i, __g_load_data.taskprio[i]);
            LISTVIEW_SetItemText(hitem, 1, i, __g_load_data.stackuse[i]);
            LISTVIEW_SetItemText(hitem, 2, i, __g_load_data.stack_total[i]);
            LISTVIEW_SetItemText(hitem, 3, i, __g_load_data.taskload[i]);
            LISTVIEW_SetItemText(hitem, 4, i, __g_load_data.taskname[i]);
        }
        LISTVIEW_SetSelUnsorted(hitem, sel);
        break;
    default:
        WM_DefaultProc(pMsg);
    }
}




/******************************************************************************/
aw_local void __cpu_used_init (struct app_task_manage *p_app,
                               WM_HWIN                 hwin)
{
    WM_HWIN                 hitem;
    GUI_RECT                rect;
    GRAPH_SCALE_Handle      hscale;
    GRAPH_SCALE_Handle      vscale;
    int                     dist_v = 0;
    int                     dist_h = 0;
#define __BORDER_TOP        0
#define __BORDER_BOTTOM     20
#define __BORDER_LEFT       28
#define __BORDER_RIGHT      0

#define __VSCALE_FACTOR      1

    /* 创建图形控件 */
    hitem = GRAPH_CreateEx(0, 0,
                           WM_GetWindowSizeX(hwin),
                           WM_GetWindowSizeY(hwin) - 20,
                           hwin,
                           WM_CF_SHOW,
                           0,
                           ID_GRAPH0);
    GRAPH_SetBorder(hitem,
                    __BORDER_LEFT,
                    __BORDER_TOP,
                    __BORDER_RIGHT,
                    __BORDER_BOTTOM);
    /* 创建数据对象 */
    p_app->hdata = GRAPH_DATA_YT_Create(GUI_GREEN, 800 , 0, 0);

    /* 将创建的数据对象附件到图形控件  */
    GRAPH_AttachData(hitem, p_app->hdata);

    /* 获取hGraph窗口的尺寸大小  */
    WM_GetClientRectEx(hitem, &rect);

    dist_v = (rect.y1 - rect.y0 - __BORDER_BOTTOM) / 5 ;
    dist_h = (rect.x1 - rect.x0 - __BORDER_LEFT) / 8;

    /* 设置图形控件属性 */
    GRAPH_SetGridDistY(hitem, dist_v);      /* 设置垂直方向从一条网格线到下一网格线的距离为5等分 */
    GRAPH_SetGridDistX(hitem, dist_h);      /* 设置水平方向从一条网格线到下一网格线的距离为8等分 */
    GRAPH_SetGridVis(hitem, 1);             /* 网格可见 */
    GRAPH_SetGridFixedX(hitem, 1);          /* 固定x轴，其坐标不可以随滚动条发生变化  */
    GRAPH_SetUserDraw(hitem, __graph_draw);

    /* 添加垂直刻度 */
    vscale = GRAPH_SCALE_Create(__BORDER_LEFT,
                                GUI_TA_RIGHT,
                                GRAPH_SCALE_CF_VERTICAL,
                                dist_v);
    GRAPH_SCALE_SetFont(vscale, &GUI_Font13B_ASCII);
    GRAPH_SCALE_SetTextColor(vscale, GUI_YELLOW);

    /* 1个像素点代表一个刻度  */
    if (LCD_GetXSize() <= 480) {
        GRAPH_SCALE_SetFactor(vscale, 1 * __VSCALE_FACTOR);
    } else {
        GRAPH_SCALE_SetFactor(vscale, 0.4 * __VSCALE_FACTOR);
    }

    /* 将垂直刻度对象添加到图形控件 */
    GRAPH_AttachScale(hitem, vscale);

    /* 添加水平刻度 */
    hscale = GRAPH_SCALE_Create(WM_GetWindowSizeY(hitem) - __BORDER_BOTTOM,
                                GUI_TA_TOP,
                                GRAPH_SCALE_CF_HORIZONTAL,
                                dist_h);
    GRAPH_SCALE_SetTextColor(hscale, GUI_DARKGREEN);
    GRAPH_SCALE_SetFont(hscale, &GUI_Font13B_ASCII);
    GRAPH_SCALE_SetFactor(hscale, 1);

    /* 将水平刻度对象添加到图形控件 */
    GRAPH_AttachScale(hitem, hscale);
}




/******************************************************************************/
aw_local void __cpu_used_cb (WM_MESSAGE * pMsg)
{
    struct app_task_manage *p_app;
    int                     i;
    float                   m;

    switch (pMsg->MsgId)  {
    case WM_DELETE:
        GUI_CURSOR_Show();
        break;

    case WM_MSG_REFRESH:
        FRAMEWIN_GetUserData(pMsg->hWinSrc, &p_app, sizeof(p_app));
        /* 1个像素点代表一个刻度  */
        if (LCD_GetXSize() <= 480) {
            m = 1;
        } else {
            m = 0.4;
        }

        for (i = 0; i < 3; i++) {
            /* 利用定时器更新数据 */
            GRAPH_DATA_YT_AddValue(p_app->hdata, __g_load_data.cpuload / m);
        }
        break;

    default:
        WM_DefaultProc(pMsg);
    }
}




/******************************************************************************/
aw_local void __app_task_manage_cb (WM_MESSAGE * pMsg)
{
    struct app_task_manage *p_app;
    WM_HWIN                 hitem, hpage;
    WM_MESSAGE              msg;
    int                     i;

    switch (pMsg->MsgId) {
    case WM_DELETE:
        /* 重新显示光标 */
        GUI_CURSOR_Show();

        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        WM_DeleteTimer(p_app->tmr);
        aw_mem_free(p_app);
        break;

    case WM_TIMER:
        FRAMEWIN_GetUserData(pMsg->hWin, &p_app, sizeof(p_app));
        hitem = WM_GetClientWindow(pMsg->hWin);
        hitem = WM_GetDialogItem(hitem, ID_MULTIPAGE0);

        for (i = 0; TRUE ;i++) {
            hpage = MULTIPAGE_GetWindow(hitem, i);
            if (hpage == 0) {
                break;
            }
            msg.hWinSrc  = pMsg->hWin;
            msg.hWin     = hpage;
            msg.MsgId    = WM_MSG_REFRESH;
            msg.Data.v   = 0;
            WM_SendMessage(hpage, &msg);
        }
        WM_RestartTimer(p_app->tmr, 1000);
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




/******************************************************************************/
void *app_task_manage_create (WM_HWIN parent, const char *name)
{
    struct app_task_manage *p_app;
    WM_HWIN                 hwin;
    WM_HWIN                 hmult, htmp;

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
                                      __app_task_manage_cb,
                                      sizeof(p_app));
    if (p_app->happ == 0) {
        goto __failed;
    }

    FRAMEWIN_SetUserData(p_app->happ, &p_app, sizeof(p_app));
    FRAMEWIN_SetFont(p_app->happ, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(p_app->happ, FRAMEWIN_BUTTON_RIGHT, 0);
    hwin = WM_GetClientWindow(p_app->happ);

    p_app->tmr = WM_CreateTimer(hwin, 0, 1000, 0);

    hmult = MULTIPAGE_CreateEx(0, 0,
                               WM_GetWindowSizeX(hwin),
                               WM_GetWindowSizeY(hwin),
                               hwin,
                               WM_CF_SHOW,
                               0,
                               ID_MULTIPAGE0);
    MULTIPAGE_SetFont(hmult, &GUI_Font_app20);

    htmp = WM_CreateWindowAsChild(0, 0,
                                  WM_GetWindowSizeX(hmult) ,
                                  WM_GetWindowSizeY(hmult) ,
                                  WM_UNATTACHED ,
                                  WM_CF_SHOW,
                                  __task_info_cb,
                                  0);
    MULTIPAGE_AddPage(hmult, htmp, "线程信息");

    htmp = WM_CreateWindowAsChild(0, 0,
                                  WM_GetWindowSizeX(hmult),
                                  WM_GetWindowSizeY(hmult),
                                  WM_UNATTACHED ,
                                  WM_CF_SHOW,
                                  __cpu_used_cb,
                                  0);
    MULTIPAGE_AddPage(hmult, htmp, " CPU ");
    MULTIPAGE_SelectPage(hmult, 0);
    __cpu_used_init(p_app, htmp);

    __work_init();
    return p_app;

__failed:
    if (p_app->happ) {
        WM_DeleteWindow(p_app->happ);
    }
    aw_mem_free(p_app);
    return NULL;
}
