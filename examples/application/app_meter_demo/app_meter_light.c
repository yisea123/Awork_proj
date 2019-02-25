#include "app_meter.h"


/**
 * \brief 仪表工作状态指示
 */
void meter_dis_work_state (work_state_t work_state)
{
    GUI_MEMDEV_Handle h_mem;

    h_mem = GUI_MEMDEV_CreateEx(630, 56, 80, 16, GUI_MEMDEV_HASTRANS);
    GUI_MEMDEV_Select(h_mem);

    if (work_state == kPower_on) {
        
        GUI_DrawBitmap(&bmp_work_on, 630, 56);
        GUI_SetColor(GUI_CYAN);
        GUI_SetFont(&GUI_Font8x16 );
        GUI_SetTextMode(GUI_TM_TRANS);  
        GUI_DispStringHCenterAt("working", 680, 56 );

    } else if (work_state == kPower_off) {

        /* 清除文字的背景  */
        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(630 , 56, 630 + 80 , 56 + 16);
        GUI_DrawBitmap(&bmp_work_off, 630, 56);
    }

    GUI_MEMDEV_Select(0);
    GUI_MEMDEV_WriteAt(h_mem, 630, 56);
    GUI_MEMDEV_Delete(h_mem);
}



/**
 * \brief 左转指示灯
 */
void meter_dis_leftlight (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_leftlight_disable.XSize;
    uint16_t rect_h = bmp_leftlight_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_leftlight_enable, 240, 86);
    } else if (light_state == kLight_off) {

        h_mem = GUI_MEMDEV_CreateEx(240, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        /* 清除残影  */
        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(240 , 86, 240 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_leftlight_disable, 240, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 240, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}



/**
 * \brief 行车灯指示
 */
void meter_dis_frontlight (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_frontlight_disable.XSize;
    uint16_t rect_h = bmp_frontlight_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_frontlight_enable, 290, 86);
    } else if (light_state == kLight_off) {

        h_mem = GUI_MEMDEV_CreateEx(290, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(290 , 86, 290 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_frontlight_disable, 290, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 290, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 近光灯指示
 */
void meter_dis_headlightlow (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_headlightlow_disable.XSize;
    uint16_t rect_h = bmp_headlightlow_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_headlightlow_enable, 338, 86);
    } else if (light_state == kLight_off) {

        h_mem = GUI_MEMDEV_CreateEx(338, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(338 , 86, 338 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_headlightlow_disable, 338, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 338, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 远光灯指示
 */
void meter_dis_headlighthigh (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_headlighthigh_disable.XSize;
    uint16_t rect_h = bmp_headlighthigh_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_headlighthigh_enable, 385, 86); 
    } else if (light_state == kLight_off) {

        h_mem = GUI_MEMDEV_CreateEx(385, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(385 , 86, 385 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_headlighthigh_disable, 385, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 385, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 后雾灯指示
 */
void meter_dis_foglightrear (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_foglightrear_disable.XSize;
    uint16_t rect_h = bmp_foglightrear_disable.YSize;
    
    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_foglightrear_enable, 432, 86); 
    } else if (light_state == kLight_off) {

        h_mem = GUI_MEMDEV_CreateEx(432, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(432 , 86, 432 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_foglightrear_disable, 432, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 432, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 前雾灯指示
 */
void meter_dis_foglightfont (light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_foglightfont_disable.XSize;
    uint16_t rect_h = bmp_foglightfont_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_foglightfont_enable, 480, 86);    
    } else if (light_state == kLight_off) {
        h_mem = GUI_MEMDEV_CreateEx(480, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(480 , 86, 480 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_foglightfont_disable, 480, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 480, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}


/**
 * \brief 右转指示灯
 */
void meter_dis_rightlight(light_state_t light_state)
{
    GUI_MEMDEV_Handle h_mem;
    uint16_t rect_w = bmp_rightlight_disable.XSize;
    uint16_t rect_h = bmp_rightlight_disable.YSize;

    if (light_state == kLight_on) {
        GUI_DrawBitmap(&bmp_rightlight_enable, 525, 86);    
    } else if (light_state == kLight_off) {
        h_mem = GUI_MEMDEV_CreateEx(525, 86, rect_w, rect_h, GUI_MEMDEV_HASTRANS);
        GUI_MEMDEV_Select(h_mem);

        GUI_SetColor(GUI_BLACK);
        GUI_FillRect(525 , 86, 525 + rect_w , 86 + rect_h);
        GUI_DrawBitmap(&bmp_rightlight_disable, 525, 86);

        GUI_MEMDEV_Select(0);
        GUI_MEMDEV_WriteAt(h_mem, 525, 86);
        GUI_MEMDEV_Delete(h_mem);
    }
}

/* end of file */
