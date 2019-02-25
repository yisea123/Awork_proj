
#include "app_meter.h"

const GUI_BITMAP *  __bmp_res_water[] = {
    &bmp_water_static,
    &bmp_water_state1,
    &bmp_water_state2,
    &bmp_water_state3,
    &bmp_water_state4,
    &bmp_water_state5,
    &bmp_water_state6,
    &bmp_water_state7,
    &bmp_water_state8,
};

/**
 * \brief Ë®ÎÂÏÔÊ¾
 */
void  meter_dis_water_temp (uint8_t temp)
{
    GUI_MEMDEV_Handle h_mem;

    if (temp  >= 8) {
        temp  = 8;
    } 

    h_mem = GUI_MEMDEV_CreateEx(596, 304, 128, 128, GUI_MEMDEV_HASTRANS);
    GUI_MEMDEV_Select(h_mem);

    GUI_DrawBitmap(__bmp_res_water[0], 596, 304);
    if (temp != 0) {
        GUI_DrawBitmap(__bmp_res_water[temp], 605, 312);
    }
    GUI_MEMDEV_Select(0);

    GUI_MEMDEV_WriteAt(h_mem, 596, 304);
    GUI_MEMDEV_Delete(h_mem);
}

/* end of file */
