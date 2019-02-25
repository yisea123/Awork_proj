/*
 * app_resource.h
 *
 *  Created on: 2018Äê5ÔÂ11ÈÕ
 *      Author: wengyedong
 */

#ifndef __APP_RESOURCE_APP_RESOURCE_H
#define __APP_RESOURCE_APP_RESOURCE_H

#include "GUI.h"


extern GUI_CONST_STORAGE GUI_BITMAP bm_aworks;
extern GUI_CONST_STORAGE GUI_BITMAP bm_zlglogo;

extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_0_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_1_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_10_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_20_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_40_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_60_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_80_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery_100_20x20;
extern GUI_CONST_STORAGE GUI_BITMAP bm_battery;

extern GUI_CONST_STORAGE GUI_BITMAP bm_led_on;
extern GUI_CONST_STORAGE GUI_BITMAP bm_led_off;

extern GUI_CONST_STORAGE GUI_BITMAP bmbuzzer_on;
extern GUI_CONST_STORAGE GUI_BITMAP bmbuzzer_off;

extern GUI_CONST_STORAGE GUI_BITMAP bm_button_refresh;

extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_folder;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_net;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_taskmanager;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_sysinfo;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_control;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_sample;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_clock;




extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_update;
extern GUI_CONST_STORAGE GUI_BITMAP bm_icon_calibration;


extern GUI_CONST_STORAGE GUI_FONT GUI_Font_app20;
extern GUI_CONST_STORAGE GUI_FONT GUI_Font_app24;




uint8_t app_utf82gbk (const char *p_utf8,
                      char       *p_gbk,
                      uint32_t    size);

uint8_t app_gbk2utf8 (const char *p_gbk,
                      char       *p_utf8,
                      uint32_t    size);


#endif /* __APP_RESOURCE_APP_RESOURCE_H */
