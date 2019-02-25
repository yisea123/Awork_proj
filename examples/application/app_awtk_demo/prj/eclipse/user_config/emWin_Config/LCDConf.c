/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2014  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.24 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
 * \file
 * \brief emwin LCD configuration.
 *
 * \par 使用说明
 *
 * \internal
 * \par modification history
 * - 1.00 14-08-4  ops, based on the original file of emwin.
 * \endinternal
 */

#include <string.h>
#include "GUI.h"
#include "GUIDRV_Lin.h"
#include "GUIDRV_FlexColor.h"

#include "aw_emwin_fb.h"
#include "aw_ts.h"
#include "aw_int.h"
#include "aw_vdebug.h"
#include "aw_delay.h"
#include "LCDConf.h"
#include "aw_cache.h"
#include "aw_mem.h"

aw_emwin_fb_info_t *__gp_emwin_fb = NULL;

//
// RGB565 Display driver
//
//#define RGB565_DISPLAY_DRIVER GUIDRV_LIN_16
extern const GUI_DEVICE_API IMX_1050_GUIDRV_Lin_16_API;
#define RGB565_DISPLAY_DRIVER  &IMX_1050_GUIDRV_Lin_16_API

//
// RGB88 Display driver
//
#define RGB888_DISPLAY_DRIVER GUIDRV_LIN_24



/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/**
 * \breif 配置多层显示
 *
 * \param  info          帧缓冲设备信息
 * \param  color_conv    调色板模式(每一层都需要配置调色板)
 * \param  layer_num    层数
 *
 * \return -EINVAL      待配置的层数大于 GUI_NUM_LAYERS(该值在GUIConf.h中定义)
 */
aw_local int __lcd_multi_layer_config(aw_emwin_fb_info_t *info, const LCD_API_COLOR_CONV* (*color_conv), int layer_num)
{
    int i = 0;

    if (layer_num < 0 || layer_num == 0 || layer_num > GUI_NUM_LAYERS) {
        return -EINVAL;
    }

    for (i = 0; i < layer_num; i++) {

        if (info->bpp == 24) {
            GUI_DEVICE_CreateAndLink(RGB888_DISPLAY_DRIVER, color_conv[i], 0, i);

        } else {

            GUI_DEVICE_CreateAndLink(RGB565_DISPLAY_DRIVER, color_conv[i], 0, i);
        }

        LCD_SetPosEx(i, 0, 0);

        LCD_SetSizeEx    (i, info->x_res, info->y_res);

        /* 设置虚拟显示尺寸 */
        LCD_SetVSizeEx   (i, info->x_res, info->y_res);

        if (info->orientation == AW_FB_VERTICAL_SCREEN) {

            GUI_SetOrientationEx(GUI_MIRROR_X | GUI_SWAP_XY, i);
        }

        LCD_SetVRAMAddrEx(i, (void *)info->v_addr);
    }

    return AW_OK;
}

/**
 * \breif 缓冲区复制函数
 *
 * \param  layer_index    层索引
 * \param  index_src      前置缓冲区
 * \param  index_dst      后置缓冲区
 *
 */
aw_local void __copy_buffer(int layer_index, int index_src, int index_dst)
{
    uint32_t buf_size = 0, addr_src = 0, addr_dst = 0;

    buf_size = (__gp_emwin_fb->x_res * __gp_emwin_fb->y_res * __gp_emwin_fb->bpp) / 8;

    addr_src = __gp_emwin_fb->v_addr + buf_size * (index_src);
    addr_dst = __gp_emwin_fb->v_addr + buf_size * (index_dst);

    memcpy((void *)addr_dst, (void *)addr_src, buf_size);
    aw_cache_flush((void*)addr_dst, buf_size);

}

/**
 * \breif 配置双缓冲
 *
 * \param  info         帧缓冲设备信息
 * \param  layer_num    层数
 * \return -EINVAL      层数小于0
 */
aw_local int __lcd_multi_buffer_config(aw_emwin_fb_info_t *info, int layer_num)
{
    int i = 0;

    if (layer_num < 0 || layer_num == 0) {
        return -EINVAL;
    }

    for (i = 0; i < layer_num; i++) {
        GUI_MULTIBUF_ConfigEx(i, 2);
        LCD_SetDevFunc(i, LCD_DEVFUNC_COPYBUFFER, (void(*)(void))__copy_buffer);
    }

    return AW_OK;
}

/**
 * \breif 设置校准
 *
 * \param  info   帧缓冲设备信息
 */
aw_local void __gui_touch_calibration(aw_emwin_fb_info_t *info, int layer_num)
{
    uint32_t TouchOrientation;

    TouchOrientation = (GUI_MIRROR_X * LCD_GetMirrorXEx(0)) |
                       (GUI_MIRROR_Y * LCD_GetMirrorYEx(0)) |
                       (GUI_SWAP_XY  * LCD_GetSwapXYEx(0)) ;

    GUI_TOUCH_SetOrientation(TouchOrientation);
}

/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {

    uint32_t *p_vaddr = NULL;
    uint32_t size = 0;

    const LCD_API_COLOR_CONV* color_conv[3];

    __gp_emwin_fb = aw_emwin_fb_open("imx1050_emwin_fb", 0);

    /* 大小 cache line 对齐  */
    size = (__gp_emwin_fb->x_res * __gp_emwin_fb->y_res * (__gp_emwin_fb->bpp / 8)
            * 2 + AW_CACHE_LINE_SIZE - 1) / AW_CACHE_LINE_SIZE * AW_CACHE_LINE_SIZE;

    /* 基地址对齐  */
    p_vaddr = aw_mem_align(size, AW_CACHE_LINE_SIZE);

    memset(p_vaddr, 0x00, size);

    /* 清0后刷到内存中 */
    aw_cache_flush(p_vaddr,  size);

    /* frame buffer 初始化 */ /* AW_FB_VERTICAL_SCREEN  AW_FB_HORIZONTAL_SCREEN */
    aw_emwin_fb_init(__gp_emwin_fb, p_vaddr, AW_FB_HORIZONTAL_SCREEN);

    /* frame buffer 运行 */
    aw_emwin_fb_run(__gp_emwin_fb);

    /* 设置背光亮度 */
    aw_emwin_fb_backlight(__gp_emwin_fb, 100);

    if (__gp_emwin_fb->bpp == 24 || __gp_emwin_fb->bpp == 18) {

        color_conv[0] = GUICC_M888;
        color_conv[1] = GUICC_M888;
        color_conv[2] = GUICC_M888;

    } else if (__gp_emwin_fb->bpp == 16) {

        color_conv[0] = GUICC_M565;
        color_conv[1] = GUICC_M565;
        color_conv[2] = GUICC_M565;

    } else {


    }

    /* 多层显示支持 (先设置显示支持)*/
    __lcd_multi_layer_config(__gp_emwin_fb, color_conv, 1);

    /* 触摸屏校准 (后设置触屏校准)*/
    __gui_touch_calibration(__gp_emwin_fb, 1);

    /* 双缓冲支持 */
    __lcd_multi_buffer_config(__gp_emwin_fb, 1);

    //
    // Set user palette data (only required if no fixed palette is used)
    //
    #if defined(PALETTE)
        LCD_SetLUTEx(0, PALETTE);
    #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {

    int r;

    switch (Cmd) {
    case LCD_X_SETORG : {

        uint32_t ysize, offset, addr;

        LCD_X_SETORG_INFO *p;
        p = (LCD_X_SETORG_INFO *)pData;

        ysize = (p->yPos/__gp_emwin_fb->y_res);

        offset = (__gp_emwin_fb->x_res * ysize * __gp_emwin_fb->y_res * __gp_emwin_fb->bpp) / 8;

        /* 根据虚拟屏幕的偏移, 计算待显示的缓冲区首地址 */
        addr = __gp_emwin_fb->v_addr + offset;

        aw_emwin_fb_vram_addr_set(__gp_emwin_fb, addr);

        return 0;

    }

    case LCD_X_SETPOS : {
        return 0;
    }

    case LCD_X_SHOWBUFFER : {

        uint32_t addr = 0;
        uint32_t buf_size = 0;

        LCD_X_SHOWBUFFER_INFO * p;
        p = (LCD_X_SHOWBUFFER_INFO *)pData;

        buf_size = (__gp_emwin_fb->x_res * __gp_emwin_fb->y_res * __gp_emwin_fb->bpp) / 8;

        /* 根据缓冲区索引, 计算待显示的缓冲区首地址 */
        addr = __gp_emwin_fb->v_addr + buf_size * p->Index;

        aw_cache_flush((void*)addr, buf_size);
        aw_emwin_fb_vram_addr_set(__gp_emwin_fb, addr);

        GUI_MULTIBUF_Confirm(p->Index);

        return 0;
    }

    /* todo 修改帧缓冲的数据格式 , 适配16位的数据总线 */
    case LCD_X_SETLUTENTRY: {
        //
        // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
        //
//        LCD_X_SETLUTENTRY_INFO *pData;
//        pData = (LCD_X_SETLUTENTRY_INFO *)p;
//        //
//        // Call hardware routine to write a LUT entry to the controller
//        //
//        color = pData->Color;
//        colorB = (color & 0xFF0000) >> 16;
//        colorG = (color & 0x00FF00) >> 8;
//        colorR = (color & 0x0000FF);
//
//        /* 16-bit bus */
//        lutData[pData->Pos] = ((colorR >> 3) << 11) | ((colorG >> 2) << 5) | ((colorB >> 3) << 0);

        return 0;
    }

    default:
        r = -1;
        break;
    }
    return r;
}

/*********************************************************************
*
*       Global functions for GUI touch
*
**********************************************************************
*/

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateX()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on X-axis,
*   prepares measurement for Y-axis.
*   Voltage on Y-axis is switched off.
*/
void GUI_TOUCH_X_ActivateX(void) {
}

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateY()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on Y-axis,
*   prepares measurement for X-axis.
*   Voltage on X-axis is switched off.
*/
void GUI_TOUCH_X_ActivateY(void) {
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureX()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of X-axis.
*/
int  GUI_TOUCH_X_MeasureX(void) {

    return 0;
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureY()
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of Y-axis.
*/
int  GUI_TOUCH_X_MeasureY(void) {

    return 0;
}

#endif  // GUI_SUPPORT_TOUCH
/*************************** End of file ****************************/
