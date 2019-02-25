﻿/**
 * File:   app_main.c
 * Author: AWTK Develop Team
 * Brief:  app main
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-13 TangJunJie created
 *
 */

#include "awtk.h"
#include "assets.h"
#include "base/mem.h"
#include "base/path.h"
#include "base/system_info.h"
#include "ext_widgets/ext_widgets.h"

ret_t open_main_window(void);

#ifdef USE_GUI_MAIN
int gui_app_start(int lcd_w, int lcd_h) {
  tk_init(lcd_w, lcd_h, APP_MOBILE, NULL, NULL);
#else

#ifdef WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow) {
#else
int main(void) {
#endif

  int  lcd_w = 800;
  int  lcd_h = 480;

#ifdef WITH_FS_RES
  char res_root[MAX_PATH + 1];
  char app_root[MAX_PATH + 1];
  path_app_root(app_root);
  memset(res_root, 0x00, sizeof(res_root));
  path_build(res_root, MAX_PATH, app_root, "src", NULL);
  tk_init(lcd_w, lcd_h, APP_MOBILE, NULL, res_root);
#else
  tk_init(lcd_w, lcd_h, APP_MOBILE, NULL, NULL);
#endif

#endif

//#define WITH_LCD_PORTRAIT 1
#if defined(USE_GUI_MAIN) && defined(WITH_LCD_PORTRAIT)
  if (lcd_w > lcd_h) {
    tk_set_lcd_orientation(LCD_ORIENTATION_90);
  }
#endif /*WITH_LCD_PORTRAIT*/

#ifdef WITH_LCD_LANDSCAPE
  if (lcd_w < lcd_h) {
    tk_set_lcd_orientation(LCD_ORIENTATION_90);
  }
#endif /*WITH_LCD_PORTRAIT*/

  /* 初始化资源 */
  assets_init();
  
  /* 初始化扩展控件 */
  tk_ext_widgets_init();
  
  /* 打开主屏幕 */
  open_main_window();

  /* 进入awtk事件循环 */
  tk_run();

  return 0;
}
