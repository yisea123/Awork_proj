#include "app_meter.h"
#include "aw_time.h"
#include "stdio.h"



/**
 * \brief 日期时间显示
 */
void meter_dis_time (dis_state_t dis_state)
{

    GUI_MEMDEV_Handle h_mem;

    aw_tm_t tm;
    char buf[32] = {0};

    h_mem = GUI_MEMDEV_CreateEx(66, 60, 120, 12, GUI_MEMDEV_HASTRANS);
    GUI_MEMDEV_Select(h_mem);

    /* 清除背景 */
    GUI_SetColor(GUI_BLACK);
    GUI_FillRect(66 , 60, 66 + 120 , 60 + 12);

    if (dis_state == kDisplay_off) {

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 66, 60);
        GUI_MEMDEV_Delete(h_mem);
        return;
    }

    /* 更新时间 */
    aw_tm_get(&tm);
    sprintf(buf, "%d/%d/%d %02d:%02d:%02d",
            tm.tm_year + 1900,
            tm.tm_mon,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec);

    /* 显示数值 */
    GUI_SetFont(&GUI_Font16B_ASCII);
    GUI_SetTextMode(GUI_TM_TRANS);  
    GUI_SetColor(GUI_CYAN);
    GUI_DispStringHCenterAt(buf, 127, 58 ); 

    GUI_MEMDEV_Select(0);
    GUI_MEMDEV_WriteAt(h_mem, 66, 60);
    GUI_MEMDEV_Delete(h_mem);
   
}


/* end of file */
