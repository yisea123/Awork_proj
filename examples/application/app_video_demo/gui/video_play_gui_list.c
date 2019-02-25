#include "aw_sem.h"
#include "LISTBOX.h"
#include "DIALOG.h"
#include "io/aw_dirent.h"
#include "video_play_gui.h"

extern WM_HWIN         hitem_play;  /*���Ű�ť*/
extern const  GUI_BITMAP  btn_stop; /*ֹͣ��ťͼƬ*/

/******************************************************************************/
#define __NS  0   /* ��Ҫ������Ļ��С���� */

#define ID_WINDOW_0  (GUI_ID_USER + 0x00)
#define ID_ListBox_0 (GUI_ID_USER + 0x01)

static GUI_WIDGET_CREATE_INFO __adialogcreate[] = {
    { WINDOW_CreateIndirect,  "List",    ID_WINDOW_0, __NS, 0, 110, 252, 0, 0x0, 0 },
    { LISTBOX_CreateIndirect, "ListBox", ID_ListBox_0,   0, 0, 110, 252, 0, 0x0, 0 },
};
/******************************************************************************/

int DialogMsg (WM_HWIN hObj, int msgid, int data)
{
    int ret = -1;
    WM_MESSAGE Message;
    WM_HWIN hClient;

    Message.MsgId = msgid;
    Message.Data.v = data;

    hClient = WM_GetClientWindow(hObj);     /* ��ȡ�û����þ�� */
    WM_SendMessage(hClient, &Message);
    ret = 0;

    return ret;
}

/******************************************************************************/
/**
 * \brief  LIST����Ļص�����
 * param[in]  pmsg :����ʱ����Ϣ
 *
 */
static void cb_dialog(WM_MESSAGE * pMsg)
{
    int               ncode;
    int               id;
    int               count = 1;
    char              file_name_temp[30];
    WM_HWIN           hitem;

    struct aw_dir     *p_dirp;
    struct aw_dirent  *p_direntp;

    switch (pMsg->MsgId) {

    case WM_INIT_DIALOG:
        p_dirp = aw_opendir(MOVIES_PATH);/*���ļ�ϵͳĿ¼*/
        if (p_dirp == NULL) {
            printf("\n\rFailed to open file directory.");
            exit(1);
        }

        hitem = WM_GetDialogItem(pMsg->hWin,ID_ListBox_0);/*�����б���*/
        LISTBOX_SetBkColor(hitem,0,GUI_TRANSPARENT);
        LISTBOX_SetBkColor(hitem,1,0x00770000);
        LISTBOX_SetBkColor(hitem,2,GUI_BLUE);
        LISTBOX_SetTextColor(hitem,0,GUI_WHITE);
        LISTBOX_SetTextColor(hitem,1,GUI_WHITE);
        LISTBOX_SetTextColor(hitem,2,GUI_WHITE);
        LISTBOX_SetTextAlign(hitem,GUI_TA_VCENTER|GUI_TA_LEFT);

        /* ��ȡSD���ڵ��ļ����������б�� */
        while ((p_direntp = aw_readdir(p_dirp)) != NULL){
            LISTBOX_InsertString(hitem,p_direntp->d_name,count);
            if (count == 1) {
                memcpy(gp_list_state->ready_to_play_filename,MOVIES_PATH,4);
                gp_list_state->ready_to_play_filename[4] = '/';
                memcpy(gp_list_state->ready_to_play_filename+5,
                       p_direntp->d_name,
                       strlen(p_direntp->d_name));
                gp_list_state->ready_to_play_filename[5+strlen(p_direntp->d_name)] = '\0';
            }
            count ++ ;
        }
        /*�ر�Ŀ¼*/
        aw_closedir(p_dirp);
        break;

    case WM_NOTIFY_PARENT:
        id    = WM_GetId(pMsg->hWinSrc);
        ncode = pMsg->Data.v;

        /* ���ļ���ѡ��ʱ   ��·��+�ļ�������ʽ��������  */
        if(id == ID_ListBox_0) {
            switch(ncode){

            case WM_NOTIFICATION_SEL_CHANGED:
                hitem = WM_GetDialogItem(pMsg->hWin,ID_ListBox_0);
                LISTBOX_GetItemText(hitem,(LISTBOX_GetSel(hitem)),file_name_temp,30);/*��ȡ�б����ı�*/
                memcpy(gp_list_state->ready_to_play_filename,MOVIES_PATH,4);
                gp_list_state->ready_to_play_filename[4] = '/';
                memcpy(gp_list_state->ready_to_play_filename+5,
                       file_name_temp,
                       strlen(file_name_temp));
                gp_list_state->ready_to_play_filename[5+strlen(file_name_temp)] = '\0';
                gp_list_state->list_file_opt_state = LIST_FILE_CHANGE_OPERATION;
                gp_play_state->play_file_change_flag = 1;
                gp_play_state->play_btn_opt_state = PLAY_BUTTON_CLICKED_OPERATION;
                BUTTON_SetBitmapEx(hitem_play, 0, &btn_stop, 0, 0);
                gp_play_state->stop_btn_opt_state = 0;
                WM_ShowWindow(hitem_play);/*��ʾ��ͣ��ť*/

                /* �������ڷ���һ���ػ���Ϣ */
                DialogMsg (g_main_win, WM_PAINT, 0);
                break;

            case WM_NOTIFICATION_RELEASED:
                /* ������Ƶʱ�����б� */
                if (gp_list_state->list_btn_opt_state == LIST_SHOW){
                    WM_HideWindow(g_list_win);
                    gp_list_state->list_btn_opt_state = LIST_HIDE;
                }else if (gp_list_state->list_btn_opt_state == LIST_HIDE) {
                    WM_ShowWindow(g_list_win);
                    gp_list_state->list_btn_opt_state = LIST_SHOW;
                }
                break;
            }
        }
        break;

    case WM_PAINT:
        break;

    default:
        WM_DefaultProc(pMsg);
        break;
    }
}

/******************************************************************************/
/**
 * \brief �����б�������
 * param[in] hwin        :  ��������
 *
 * \return   hWin_return :  ���ھ��
 */
WM_HWIN CreateList(WM_HWIN hwin)
{
    WM_HWIN hWin_return;

    __adialogcreate[0].x0 = LCD_GetXSize() - __adialogcreate[0].xSize;

    hWin_return = GUI_CreateDialogBox(__adialogcreate,
                                      GUI_COUNTOF(__adialogcreate),
                                      cb_dialog,
                                      hwin,
                                      0,
                                      0);
    return hWin_return;
}
