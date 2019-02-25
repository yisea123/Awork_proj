/*
 * app_obj_clock.c
 *
 *  Created on: 2018年5月12日
 *      Author: wengyedong
 */




#include "aworks.h"
#include "aw_mem.h"
#include "aw_time.h"
#include "aw_rtc.h"


#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "TEXT.h"
#include "BUTTON.h"
#include "LISTWHEEL.h"

#include "../resource/app_resource.h"
#include "string.h"

#define ID_TEXT_0           (GUI_ID_USER + 1)

#define ID_BUTTON_CONFIRM   (GUI_ID_USER + 2)
#define ID_BUTTON_CANCEL    (GUI_ID_USER + 3)

#define ID_LISTWHEEL_YEAR   (GUI_ID_USER + 4)
#define ID_LISTWHEEL_MON    (GUI_ID_USER + 5)
#define ID_LISTWHEEL_DAY    (GUI_ID_USER + 6)
#define ID_LISTWHEEL_HOUR   (GUI_ID_USER + 7)
#define ID_LISTWHEEL_MIN    (GUI_ID_USER + 8)
#define ID_LISTWHEEL_SEC    (GUI_ID_USER + 9)


#define __WHEEL_X      60
#define __WHEEL_Y      30
#define __WHEEL_WIDTH  50
#define __WHEEL_HITH   110

#define __YEAR_BASE 1965


extern void app_message_box (const char *msg, const char *capt, int flags);


/** \brief 年 */
aw_local const char *__g_str_year[]=
{
    "1965", "1966", "1967", "1968", "1969", "1970", "1971",
    "1972", "1973", "1974", "1975", "1976", "1977", "1978",
    "1979", "1980", "1981", "1982", "1983", "1984", "1985",
    "1986", "1987", "1988", "1989", "1990", "1991", "1992",
    "1993", "1994", "1995", "1996", "1997", "1998", "1999",
    "2000", "2001", "2002", "2003", "2004", "2005", "2006",
    "2007", "2008", "2009", "2010", "2011", "2012", "2013",
    "2014", "2015", "2016", "2017", "2018", "2019", "2020",
    "2021", "2022", "2023", "2024", "2025", "2026", "2027",
    "2028", "2029", "2030", "2031", "2032", "2033", "2034",
    "2035", "2036", "2037", "2038", "2039", "2040", "2041",
    "2042", "2043", "2044", "2045", "2046", "2047", "2048",
    "2049", "2050", "2051", "2052", "2053", "2054", "2055",
};


/** \brief 月 日 时 分 秒 */
aw_local const char *__g_str_time[]=
{
    "00", "01", "02", "03", "04", "05",
    "06", "07", "08", "09", "10", "11",
    "12", "13", "14", "15", "16", "17",
    "18", "19", "20", "21", "22", "23",
    "24", "25", "26", "27", "28", "29",
    "30", "31", "32", "33", "34", "35",
    "36", "37", "38", "39", "40", "41",
    "42", "43", "44", "45", "46", "47",
    "48", "49", "50", "51", "52", "53",
    "54", "55", "56", "57", "58", "59"
};





/* 判断某一年相应月份的天数  */
aw_local int __month_day_calc (int year, int mon)
{
    int day = 0;

    switch (mon) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        day = 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        day = 30;
        break;
    case 2:
        /* 判断闰年 */
        if ((((year % 4) == 0)   &&
            ((year % 100) != 0)) ||
            (year % 400 == 0)) {
            day = 29;
        } else {
            day = 28;
        }

        break;

    default:
        break;

    }

    return day;

}




/******************************************************************************/
aw_local int ___lwheel_owner_draw_cb (const WIDGET_ITEM_DRAW_INFO *pDrawItemInfo)
{
    switch(pDrawItemInfo->Cmd) {
    case WIDGET_ITEM_DRAW_OVERLAY:
        GUI_SetColor(0x531b30);
        GUI_DrawHLine((pDrawItemInfo->y1 - pDrawItemInfo->y0) / 3,
                      pDrawItemInfo->x0, pDrawItemInfo->x1);
        GUI_DrawHLine((pDrawItemInfo->y1 - pDrawItemInfo->y0) / 3 * 2,
                      pDrawItemInfo->x0, pDrawItemInfo->x1);
        break;
    default:
        return LISTWHEEL_OwnerDraw(pDrawItemInfo);
    }
    return 0;
}




/******************************************************************************/
aw_local void __app_clock_handler (WM_MESSAGE * pMsg)
{
    int     id;
    int     sel;
    WM_HWIN hitem;

    switch (pMsg->MsgId) {
    case WM_NOTIFY_PARENT:

        id = WM_GetId(pMsg->hWinSrc);
        switch(id) {
        case ID_LISTWHEEL_YEAR:
        case ID_LISTWHEEL_MON:
        case ID_LISTWHEEL_DAY:
        case ID_LISTWHEEL_HOUR:
        case ID_LISTWHEEL_MIN:
        case ID_LISTWHEEL_SEC:
            if (pMsg->Data.v == WM_NOTIFICATION_SEL_CHANGED) {
                sel = LISTWHEEL_GetPos(pMsg->hWinSrc);
                LISTWHEEL_SetSel(pMsg->hWinSrc, sel);

            }
            break;

        case ID_BUTTON_CONFIRM:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                aw_tm_t tm;

                aw_tm_get(&tm);

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_YEAR);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_year = __YEAR_BASE + sel - 1900;

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MON);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_mon = sel;

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_DAY);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_mday = sel + 1;

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_HOUR);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_hour = sel;

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_MIN);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_min = sel;

                hitem = WM_GetDialogItem(pMsg->hWin, ID_LISTWHEEL_SEC);
                sel = LISTWHEEL_GetPos(hitem);
                tm.tm_sec = sel;

                if (tm.tm_mday > __month_day_calc(tm.tm_year + 1900,
                                                  tm.tm_mon + 1)) {
                    app_message_box("日期不合法", "错误", GUI_MESSAGEBOX_CF_MODAL);
                } else {
                    aw_tm_set(&tm);
                }
            }
            break;

        case ID_BUTTON_CANCEL:
            if (pMsg->Data.v == WM_NOTIFICATION_RELEASED) {
                WM_DeleteWindow(pMsg->hWin);
            }
            break;
        default:
            break;
        }
        break;
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}





/******************************************************************************/
aw_local WM_HWIN  __list_wheel_create (WM_HWIN      hwin,
                                       int          x,
                                       int          y,
                                       int          id,
                                       const char  *name,
                                       const char **str_item,
                                       int          nstr,
                                       int          idx)
{
    WM_HWIN   hitem;
    int       i;

    hitem = TEXT_CreateEx(x,
                          y,
                          __WHEEL_WIDTH,
                          20,
                          hwin,
                          WM_CF_SHOW,
                          0,
                          ID_TEXT_0,
                          name);
    TEXT_SetFont(hitem, &GUI_Font_app24);
    TEXT_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);

    hitem = LISTWHEEL_CreateEx(x,
                               y + 20,
                               __WHEEL_WIDTH,
                               __WHEEL_HITH,
                               hwin,
                               WM_CF_SHOW | WM_CF_HASTRANS,
                               0,
                               id,
                               NULL);
    LISTWHEEL_SetFont(hitem, &GUI_Font24_ASCII);
    LISTWHEEL_SetBkColor(hitem, LISTWHEEL_CI_UNSEL, 0x461327);
    LISTWHEEL_SetBkColor(hitem, LISTWHEEL_CI_SEL,   0x461327);

    LISTWHEEL_SetTextAlign(hitem, GUI_TA_VCENTER | GUI_TA_HCENTER);

    LISTWHEEL_SetSnapPosition(hitem, __WHEEL_HITH / 3);
    LISTWHEEL_SetLineHeight(hitem, __WHEEL_HITH / 3);

    LISTWHEEL_SetTextColor(hitem, LISTWHEEL_CI_UNSEL, GUI_LIGHTGRAY);
    LISTWHEEL_SetTextColor(hitem, LISTWHEEL_CI_SEL, GUI_BLACK);
    LISTWHEEL_SetOwnerDraw(hitem, ___lwheel_owner_draw_cb);

    for (i = 0; i < nstr; i++) {
        LISTWHEEL_AddString(hitem, (const char *)(str_item[i]));
    }
    LISTWHEEL_SetPos(hitem, idx);
    LISTWHEEL_SetSel(hitem, idx);

    return hitem;
}




/******************************************************************************/
void *app_clock_create (WM_HWIN parent, const char *name)
{
    WM_HWIN                hwin;
    WM_HWIN                hitem;
    FRAMEWIN_Handle        happ;
    aw_tm_t                tm;
    int                    wheel_x;
    int                    len_x;
    int                    len_y;

    /* Time app*/
    happ = FRAMEWIN_CreateEx(0, 0,
                             WM_GetWindowSizeX(parent),
                             WM_GetWindowSizeY(parent),
                             parent,
                             WM_CF_SHOW,
                             0,
                             0,
                             name,
                             __app_clock_handler);
    if (happ == 0) {
        goto __failed;
    }

    FRAMEWIN_SetFont(happ, &GUI_Font_app20);
    FRAMEWIN_AddCloseButton(happ, FRAMEWIN_BUTTON_RIGHT, 0);
    hwin = WM_GetClientWindow(happ);

    len_x = WM_GetWindowSizeX(hwin);
    len_y = WM_GetWindowSizeY(hwin);

    /* 初始化时间日期控件标题 */
    hitem = TEXT_CreateEx(len_x / 2 - 80,
                          (len_y - 203) / 2,
                          135,
                          20,
                          hwin,
                          WM_CF_SHOW,
                          0, ID_TEXT_0, "时间设置");
    TEXT_SetFont(hitem, &GUI_Font_app24);
    TEXT_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);

    aw_tm_get(&tm);

    wheel_x = (len_x - 60 * 6) / 2;

    __list_wheel_create(hwin,
                        wheel_x,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_YEAR,
                        "年",
                        __g_str_year,
                        AW_NELEMENTS(__g_str_year),
                        tm.tm_year + 1900 - __YEAR_BASE);

    __list_wheel_create(hwin,
                        wheel_x + __WHEEL_WIDTH + 10,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_MON,
                        "月",
                        &__g_str_time[1],
                        12,
                        tm.tm_mon);

    __list_wheel_create(hwin,
                        wheel_x + (__WHEEL_WIDTH + 10) * 2,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_DAY,
                        "日",
                        &__g_str_time[1],
                        31,//todo
                        tm.tm_mday - 1);

    __list_wheel_create(hwin,
                        wheel_x + (__WHEEL_WIDTH + 10) * 3,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_HOUR,
                        "时",
                        __g_str_time,
                        24,
                        tm.tm_hour);

    __list_wheel_create(hwin,
                        wheel_x + (__WHEEL_WIDTH + 10) * 4,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_MIN,
                        "分",
                        __g_str_time,
                        60,
                        tm.tm_min);

    __list_wheel_create(hwin,
                        wheel_x + (__WHEEL_WIDTH + 10) * 5,
                        (len_y - 203) / 2 + 30,
                        ID_LISTWHEEL_SEC,
                        "秒",
                        __g_str_time,
                        60,
                        tm.tm_sec);

    hitem = BUTTON_CreateEx((len_x - 335) / 2,
                            (len_y - 203) / 2 + 170,
                            80,
                            33,
                            hwin,
                            WM_CF_SHOW,
                            0,
                            ID_BUTTON_CONFIRM);
    BUTTON_SetFont(hitem, &GUI_Font_app20);
    BUTTON_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);
    BUTTON_SetText(hitem, "确认");
    BUTTON_SetSkinClassic(hitem);
    BUTTON_SetBkColor(hitem, BUTTON_CI_UNPRESSED, GUI_WHITE);
    BUTTON_SetBkColor(hitem, BUTTON_CI_PRESSED, GUI_LIGHTBLUE);

    hitem = BUTTON_CreateEx((len_x - 335) / 2 + 255,
                            (len_y - 203) / 2 + 170,
                            80,
                            33,
                            hwin,
                            WM_CF_SHOW,
                            0,
                            ID_BUTTON_CANCEL);
    BUTTON_SetFont(hitem, &GUI_Font_app20);
    BUTTON_SetTextAlign(hitem, TEXT_CF_VCENTER | TEXT_CF_HCENTER);
    BUTTON_SetText(hitem, "取消");
    BUTTON_SetSkinClassic(hitem);
    BUTTON_SetBkColor(hitem, BUTTON_CI_UNPRESSED, GUI_WHITE);
    BUTTON_SetBkColor(hitem, BUTTON_CI_PRESSED, GUI_LIGHTBLUE);


__failed:

    return (void *)happ;
}
