#include <stdio.h>
#include "DIALOG.h"
#include "aw_sem.h"
#include "video_play_gui.h"
#include "aw_mem.h"

/******************************************************************************/

#define ID_WINDOW_0  (GUI_ID_USER + 0x00)  /* ������ID */
#define ID_IMAGE_0   (GUI_ID_USER + 0x01)  /* ͼ�񴰿�ID */

static GUI_WIDGET_CREATE_INFO __adialogcreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 0, 0, 0, 0x0, 0 },
  { IMAGE_CreateIndirect,  "image",  ID_IMAGE_0,  0, 0, 0, 0, 0, 0x0, 0 },
};

/******************************************************************************/

/*
 * \brief  ������Ļص�����
 * param[in]  pmsg :����ʱ����Ϣ
 */
static void cb_dialog(WM_MESSAGE * p_msg)
{
    int                           ncode;
    int                           id;

    switch (p_msg->MsgId) {

    case WM_PAINT:
        GUI_SetBkColor(GUI_BLACK);/* ��������Ϊ��ɫ */
        GUI_Clear();
        break;

    case WM_NOTIFY_PARENT:
        id    = WM_GetId(p_msg->hWinSrc);
        ncode = p_msg->Data.v;
        switch(id) {

        case ID_IMAGE_0:
            switch (ncode) {

            case WM_NOTIFICATION_RELEASED:
                break;

            default:
                break ;
            }
            break ;

        default:
            break ;
        }
        break;

    default:
        WM_DefaultProc(p_msg);
    }
}


/**
 * \brief ���������崰��
 * \return   hWin_return : ���ھ��
 */
WM_HWIN CreateWindow(void)
{

    WM_HWIN hWin_return;
    int status_tool_hight = 20;  /* ״̬���ĸ߶� */

    /* ������Ļ��С������ʾ���� */
    __adialogcreate[0].xSize = LCD_GetXSize();
    __adialogcreate[0].ySize = LCD_GetYSize();

    __adialogcreate[1].xSize = LCD_GetXSize();
    __adialogcreate[1].ySize = LCD_GetYSize() - status_tool_hight;

    hWin_return = GUI_CreateDialogBox(__adialogcreate,
                                      GUI_COUNTOF(__adialogcreate),
                                      cb_dialog,
                                      WM_HBKWIN, 0, 0);
  return hWin_return;
}

