
#include "app_meter.h"

const GUI_BITMAP *  __bmp_res_oil[] = {
    &bmp_oil_static,
    &bmp_oil_state1,
    &bmp_oil_state2,
    &bmp_oil_state3,
    &bmp_oil_state4,
    &bmp_oil_state5,
    &bmp_oil_state6,
    &bmp_oil_state7,
    &bmp_oil_state8,
};


/**
 * \brief сма©отй╬
 */
void  meter_dis_oil (uint8_t oil)
{
    GUI_MEMDEV_Handle h_mem;

    if (oil >= 8) {
        oil = 8;
    } 

    h_mem = GUI_MEMDEV_CreateEx(74, 304, 128, 128, GUI_MEMDEV_HASTRANS);
    GUI_MEMDEV_Select(h_mem);

    GUI_DrawBitmap(__bmp_res_oil[0], 74, 304);
    if (oil != 0) {
        GUI_DrawBitmap(__bmp_res_oil[oil], 83, 312);
    }
    GUI_MEMDEV_Select(0);

    GUI_MEMDEV_WriteAt(h_mem, 74, 304);
    GUI_MEMDEV_Delete(h_mem);
}


/* end of file */
