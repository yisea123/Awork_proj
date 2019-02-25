
#include "video_play_gui.h"
#include "DIALOG.h"

/******************************************************************************/
#define __NS  0   /* ��Ҫ������Ļ��С���� */

#define ID_WINDOW_0           (GUI_ID_USER + 0x00)  /*������ID*/
#define ID_BUTTON_PLAY_STOP   (GUI_ID_USER + 0x01)  /*���Ű�ťID*/
#define ID_BUTTON_LIST        (GUI_ID_USER + 0x02)  /*�б�ťID*/

static GUI_WIDGET_CREATE_INFO __g_adialogcreate[] = {
  { WINDOW_CreateIndirect, "TOOL",   ID_WINDOW_0,          0, __NS, __NS, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_PLAY_STOP,  0,    0,   20, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_LIST,       460,  0,   20, 20, 0, 0x0, 0 },
};
/******************************************************************************/

WM_HWIN         hitem_play;             /*����ȫ�ֲ��Ű�ť���*/

extern const  GUI_BITMAP  btn_stop;     /*��ͣ��ťͼƬ*/
extern const  GUI_BITMAP  btn_play;     /*���Ű�ťͼƬ*/
extern const  GUI_BITMAP  btn_list;     /*�����б�ͼƬ*/

/**
 * \brief  TOOL����Ļص�����
 * param[in]  pmsg :����ʱ����Ϣ
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
        /*�����б�ť*/
        hitem = WM_GetDialogItem(p_msg->hWin, ID_BUTTON_LIST);
        BUTTON_SetText(hitem," ");
        BUTTON_SetBitmapEx(hitem, 0, &btn_list, 0, 0);

        /*�������Ű�ť*/
        hitem_play = WM_GetDialogItem(p_msg->hWin, ID_BUTTON_PLAY_STOP);
        BUTTON_SetText(hitem_play," ");
        BUTTON_SetBitmapEx(hitem_play, 0, &btn_stop, 0, 0);
        WM_HideWindow(hitem_play);
        break;

    case WM_NOTIFY_PARENT:
        id    = WM_GetId(p_msg->hWinSrc);
        ncode = p_msg->Data.v;
        switch(id) {

        /*���Ű�ť*/
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

        /* �б���ʾ��ť */
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
        GUI_SetBkColor(GUI_BLACK);/* ��������Ϊ��ɫ */
        GUI_Clear();
        break;

    default:
        WM_DefaultProc(p_msg);
        break;
    }
}
/******************************************************************************/
/**
 * \brief ��������������
 * param[in] hwin        :  ��������
 * \return   hWin_return :  ���ھ��
 */
WM_HWIN CreateTOOL(WM_HWIN hwin)
{
    WM_HWIN hWin_return;
    int lcd_xsize = LCD_GetXSize();
    int lcd_ysize = LCD_GetYSize();

    /* �趨�����߳�ʼ���� */
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
