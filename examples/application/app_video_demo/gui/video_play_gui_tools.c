
#include "video_play_gui.h"
#include "DIALOG.h"

/******************************************************************************/
#define __NS  0   /* 需要根据屏幕大小设置 */

#define ID_WINDOW_0           (GUI_ID_USER + 0x00)  /*主场口ID*/
#define ID_BUTTON_PLAY_STOP   (GUI_ID_USER + 0x01)  /*播放按钮ID*/
#define ID_BUTTON_LIST        (GUI_ID_USER + 0x02)  /*列表按钮ID*/

static GUI_WIDGET_CREATE_INFO __g_adialogcreate[] = {
  { WINDOW_CreateIndirect, "TOOL",   ID_WINDOW_0,          0, __NS, __NS, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_PLAY_STOP,  0,    0,   20, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_LIST,       460,  0,   20, 20, 0, 0x0, 0 },
};
/******************************************************************************/

WM_HWIN         hitem_play;             /*创建全局播放按钮句柄*/

extern const  GUI_BITMAP  btn_stop;     /*暂停按钮图片*/
extern const  GUI_BITMAP  btn_play;     /*播放按钮图片*/
extern const  GUI_BITMAP  btn_list;     /*播放列表图片*/

/**
 * \brief  TOOL窗体的回调函数
 * param[in]  pmsg :窗体时间消息
 *
 */
static void cb_dialog(WM_MESSAGE * p_msg)
{
    int                     id;
    int                     ncode;
    WM_HWIN                 hitem;
    GUI_RECT                prect;
    prect.x0 = 0;
    prect.y0 = 0;
    prect.x1 = 0;
    prect.y1 = 0;

    switch (p_msg->MsgId) {

    case WM_INIT_DIALOG:
        /*创建列表按钮*/
        hitem = WM_GetDialogItem(p_msg->hWin, ID_BUTTON_LIST);
        BUTTON_SetText(hitem," ");
        BUTTON_SetBitmapEx(hitem, 0, &btn_list, 0, 0);

        /*创建播放按钮*/
        hitem_play = WM_GetDialogItem(p_msg->hWin, ID_BUTTON_PLAY_STOP);
        BUTTON_SetText(hitem_play," ");
        BUTTON_SetBitmapEx(hitem_play, 0, &btn_stop, 0, 0);
        WM_HideWindow(hitem_play);
        break;

    case WM_NOTIFY_PARENT:
        id    = WM_GetId(p_msg->hWinSrc);
        ncode = p_msg->Data.v;
        switch(id) {

        /*播放按钮*/
        case ID_BUTTON_PLAY_STOP:
            if (gp_list_state->list_file_opt_state == LIST_FILE_CHANGE_OPERATION){
                switch (ncode) {

                case WM_NOTIFICATION_RELEASED:
                    if(gp_play_state->stop_btn_opt_state == 0){
                        BUTTON_SetBitmapEx(hitem_play,0,&btn_play, 0, 0);
                        gp_play_state->stop_btn_opt_state = 1;
                    }else{
                        BUTTON_SetBitmapEx(hitem_play,0,&btn_stop, 0, 0);
                        gp_play_state->stop_btn_opt_state = 0;
                    }
                    break;

                default :
                    break ;
                }
            }
            break;

        /* 列表显示按钮 */
        case ID_BUTTON_LIST:
            switch(ncode) {

            case WM_NOTIFICATION_RELEASED:
                if (gp_list_state->list_btn_opt_state == LIST_SHOW) {
                    WM_HideWindow(g_list_win);
                    gp_list_state->list_btn_opt_state = LIST_HIDE;
                } else if (gp_list_state->list_btn_opt_state == LIST_HIDE){
                    WM_ShowWindow(g_list_win);
                    gp_list_state->list_btn_opt_state = LIST_SHOW;
                }
                break;

            default :
                break ;
            }
            break;
        }
        break;

    case WM_PAINT:
        GUI_SetBkColor(GUI_BLACK);/* 背景设置为黑色 */
        GUI_Clear();
        break;

    default:
        WM_DefaultProc(p_msg);
        break;
    }
}
/******************************************************************************/
/**
 * \brief 创建工具栏窗口
 * param[in] hwin        :  父窗体句柄
 * \return   hWin_return :  窗口句柄
 */
WM_HWIN CreateTOOL(WM_HWIN hwin)
{
    WM_HWIN hWin_return;
    int lcd_xsize = LCD_GetXSize();
    int lcd_ysize = LCD_GetYSize();

    /* 设定各工具初始坐标 */
    __g_adialogcreate[ID_WINDOW_0 - GUI_ID_USER].y0    = lcd_ysize - 20;
    __g_adialogcreate[ID_WINDOW_0 - GUI_ID_USER].xSize = lcd_xsize;
    __g_adialogcreate[ID_BUTTON_LIST - GUI_ID_USER].x0 = lcd_xsize - 20;

    hWin_return = GUI_CreateDialogBox(__g_adialogcreate,
                                      GUI_COUNTOF(__g_adialogcreate),
                                      cb_dialog,
                                      hwin,
                                      0,
                                      0);
    return hWin_return;
}



/* end of file */
