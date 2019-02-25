
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
    NO_OPERATION,                                               /**< \brief 无操作  */
    PLAY_DONE,                                                  /**< \brief 正常播放完成操作  */
    PLAY_BUTTON_CLICKED_OPERATION,                              /**< \brief 播放键按下操作  */
};

typedef struct play_opt_format{
    int play_file_change_flag;                                  /**< \brief 列表文件改变标志 */
    int stop_btn_opt_state;                                     /**< \brief 停止按钮操作状态 */
    enum PLAY_BTN_OPT             play_btn_opt_state;           /**< \brief 播放按钮操作状态 */
}play_opt_format_t;


enum LIST_BTN_OPT{
    LIST_SHOW,                                                  /**< \brief 文件列表处于显示状态  */
    LIST_HIDE,                                                  /**< \brief 文件列表处于隐藏状态  */
};

enum LIST_FILE_OPT{
    LIST_FILE_CHANGE_OPERATION,                                /**< \brief 列表键按下操作  */
    LIST_FILE_NO_OPERATION,                                     /**< \brief 列表键所选项改变操作  */
};

typedef struct  list_opt_format{
    char                      ready_to_play_filename[50];       /**< \brief 选中的文件的路径及名字 */
    enum LIST_BTN_OPT         list_btn_opt_state;               /**< \brief 列表按钮操作状态 */
    enum LIST_FILE_OPT        list_file_opt_state;              /**< \brief 列表按钮操作状态 */
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
