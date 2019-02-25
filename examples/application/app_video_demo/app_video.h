
#ifndef __VIDEO_AUDIO_H
#define __VIDEO_AUDIO_H

#include "aworks.h"
#include "WM.h"
#include "GUI.h"
#include "aw_delay.h"
#include "aw_vdebug.h"
#include "stdio.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "string.h"

enum PLAY_BTN_OPT{
    NO_OPERATION,                                               /**< \brief �޲���  */
    PLAY_DONE,                                                  /**< \brief ����������ɲ���  */
    PLAY_BUTTON_CLICKED_OPERATION,                              /**< \brief ���ż����²���  */
};

typedef struct play_opt_format{
    int play_file_change_flag;                                  /**< \brief �б��ļ��ı��־ */
    int stop_btn_opt_state;                                     /**< \brief ֹͣ��ť����״̬ */
    enum PLAY_BTN_OPT             play_btn_opt_state;           /**< \brief ���Ű�ť����״̬ */
}play_opt_format_t;


enum LIST_BTN_OPT{
    LIST_SHOW,                                                  /**< \brief �ļ��б�����ʾ״̬  */
    LIST_HIDE,                                                  /**< \brief �ļ��б�������״̬  */
};

enum LIST_FILE_OPT{
    LIST_FILE_CHANGE_OPERATION,                                /**< \brief �б�����²���  */
    LIST_FILE_NO_OPERATION,                                     /**< \brief �б����ѡ��ı����  */
};

typedef struct  list_opt_format{
    char                      ready_to_play_filename[50];       /**< \brief ѡ�е��ļ���·�������� */
    enum LIST_BTN_OPT         list_btn_opt_state;               /**< \brief �б�ť����״̬ */
    enum LIST_FILE_OPT        list_file_opt_state;              /**< \brief �б�ť����״̬ */
}list_opt_format_t;


void app_touch_task(void);

void app_desktop_task(void);

void app_vedio_task(void);

extern WM_HWIN  g_main_win;
extern WM_HWIN  g_list_win;
extern list_opt_format_t * gp_list_state;
extern play_opt_format_t * gp_play_state;
extern WM_HWIN         hitem_play;

#endif
