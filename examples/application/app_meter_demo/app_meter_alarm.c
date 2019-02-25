#include "app_meter.h"


/**
 * \brief 点火警告指示灯
 */
void meter_dis_battery (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_battery_disable.XSize;
    uint16_t rect_h = bmp_battery_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_battery_enable, 240, 376);
    } else if (alarm_state == kAlarm_off) {

        h_mem = GUI_MEMDEV_CreateEx(240, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        /* 清除残影  */
        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(240 , 376, 240 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_battery_disable, 240, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 240, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 发动机故障警告指示灯
 */
void meter_dis_engine (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_engine_disable.XSize;
    uint16_t rect_h = bmp_engine_disable.YSize;
    
    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_engine_enable, 290, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(290, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(290 , 376, 290 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_engine_disable, 290, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 290, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 机油压力警告指示灯
 */
void meter_dis_engineoil (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_engineoil_disable.XSize;
    uint16_t rect_h = bmp_engineoil_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_engineoil_enable, 340, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(340, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(340 , 376, 340 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_engineoil_disable, 340, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 340, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 传动系统警告指示灯
 */
void meter_dis_fix (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_fix_disable.XSize;
    uint16_t rect_h = bmp_fix_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_fix_enable, 395, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(395, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(395 , 376, 395 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_fix_disable, 395, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 395, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 制动系统警告指示灯
 */
void meter_dis_barke (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_barke_disable.XSize;
    uint16_t rect_h = bmp_barke_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_barke_enable, 440, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(440, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(440 , 376, 440 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_barke_disable, 440, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 440, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 安全带警告指示灯
 */
void meter_dis_safebelt (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_safebelt_disable.XSize;
    uint16_t rect_h = bmp_safebelt_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_safebelt_enable, 490, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(490, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(490 , 376, 490 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_safebelt_disable, 490, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 490, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 车门警告指示灯
 */
void meter_dis_cardoor (alarm_state_t alarm_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_cardoor_disable.XSize;
    uint16_t rect_h = bmp_cardoor_disable.YSize;

    if (alarm_state == kAlarm_on) {
        GUI_DrawBitmap(&bmp_cardoor_enable, 535, 376);
    } else if (alarm_state == kAlarm_off) {
        h_mem = GUI_MEMDEV_CreateEx(535, 376, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(535 , 376, 535 + rect_w , 376 + rect_h);
        GUI_DrawBitmap(&bmp_cardoor_disable, 535, 376);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 535, 376);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/* end of file */
