#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/inc/strings/en_US.data"
#include "assets/inc/strings/zh_CN.data"
#include "assets/inc/styles/default.data"
#include "assets/inc/styles/keyboard.data"
#include "assets/inc/ui/calibration_win.data"
#include "assets/inc/ui/kb_ascii.data"
#include "assets/inc/ui/kb_default.data"
#include "assets/inc/ui/kb_float.data"
#include "assets/inc/ui/kb_hex.data"
#include "assets/inc/ui/kb_int.data"
#include "assets/inc/ui/kb_phone.data"
#include "assets/inc/ui/kb_ufloat.data"
#include "assets/inc/ui/kb_uint.data"
#include "assets/inc/ui/keyboard.data"
#include "assets/inc/ui/main.data"
#include "assets/inc/ui/record.data"
#include "assets/inc/ui/setting.data"
#include "assets/inc/ui/timing.data"
#ifdef WITH_STB_IMAGE
#include "assets/inc/images/arr_left.res"
#include "assets/inc/images/arr_left_hover.res"
#include "assets/inc/images/arr_left_push.res"
#include "assets/inc/images/arr_right.res"
#include "assets/inc/images/arr_right_hover.res"
#include "assets/inc/images/arr_right_push.res"
#include "assets/inc/images/backspace.res"
#include "assets/inc/images/bell.res"
#include "assets/inc/images/bg0_mix.res"
#include "assets/inc/images/bg1_mix.res"
#include "assets/inc/images/btn_1.res"
#include "assets/inc/images/btn_1_hover.res"
#include "assets/inc/images/btn_1_push.res"
#include "assets/inc/images/btn_2.res"
#include "assets/inc/images/btn_2a.res"
#include "assets/inc/images/btn_2a_hover.res"
#include "assets/inc/images/btn_2a_push.res"
#include "assets/inc/images/btn_2_hover.res"
#include "assets/inc/images/btn_2_push.res"
#include "assets/inc/images/btn_3.res"
#include "assets/inc/images/btn_3_hover.res"
#include "assets/inc/images/btn_3_push.res"
#include "assets/inc/images/btn_4.res"
#include "assets/inc/images/btn_4_hover.res"
#include "assets/inc/images/btn_4_push.res"
#include "assets/inc/images/btn_5.res"
#include "assets/inc/images/btn_5_hover.res"
#include "assets/inc/images/btn_5_push.res"
#include "assets/inc/images/clock.res"
#include "assets/inc/images/fan_1a.res"
#include "assets/inc/images/fan_1b.res"
#include "assets/inc/images/fan_2.res"
#include "assets/inc/images/wind_in.res"
#include "assets/inc/images/wind_out.res"
#else
#include "assets/inc/images/arr_left.data"
#include "assets/inc/images/arr_left_hover.data"
#include "assets/inc/images/arr_left_push.data"
#include "assets/inc/images/arr_right.data"
#include "assets/inc/images/arr_right_hover.data"
#include "assets/inc/images/arr_right_push.data"
#include "assets/inc/images/backspace.data"
#include "assets/inc/images/bell.data"
#include "assets/inc/images/bg0_mix.data"
#include "assets/inc/images/bg1_mix.data"
#include "assets/inc/images/btn_1.data"
#include "assets/inc/images/btn_1_hover.data"
#include "assets/inc/images/btn_1_push.data"
#include "assets/inc/images/btn_2.data"
#include "assets/inc/images/btn_2a.data"
#include "assets/inc/images/btn_2a_hover.data"
#include "assets/inc/images/btn_2a_push.data"
#include "assets/inc/images/btn_2_hover.data"
#include "assets/inc/images/btn_2_push.data"
#include "assets/inc/images/btn_3.data"
#include "assets/inc/images/btn_3_hover.data"
#include "assets/inc/images/btn_3_push.data"
#include "assets/inc/images/btn_4.data"
#include "assets/inc/images/btn_4_hover.data"
#include "assets/inc/images/btn_4_push.data"
#include "assets/inc/images/btn_5.data"
#include "assets/inc/images/btn_5_hover.data"
#include "assets/inc/images/btn_5_push.data"
#include "assets/inc/images/clock.data"
#include "assets/inc/images/fan_1a.data"
#include "assets/inc/images/fan_1b.data"
#include "assets/inc/images/fan_2.data"
#include "assets/inc/images/wind_in.data"
#include "assets/inc/images/wind_out.data"
#endif/*WITH_STB_IMAGE*/
#ifdef WITH_STB_FONT
#ifdef WITH_MINI_FONT
#include "assets/inc/fonts/default.mini.res"
#else/*WITH_MINI_FONT*/
#include "assets/inc/fonts/default.res"
#endif/*WITH_MINI_FONT*/
#else/*WITH_STB_FONT*/
#endif/*WITH_STB_FONT*/
#endif/*WITH_FS_RES*/

ret_t assets_init(void) {
  assets_manager_t* rm = assets_manager();

#ifdef WITH_FS_RES
#ifdef WITH_MINI_FONT
  asset_info_t* info = assets_manager_load(rm, ASSET_TYPE_FONT, "default.mini");
  if (info) {
    strcpy(info->name, "default");
  }
#else 
  assets_manager_load(rm, ASSET_TYPE_FONT, "default");
#endif
  assets_manager_load(rm, ASSET_TYPE_STYLE, "default");
#else
#ifdef WITH_STB_FONT
  assets_manager_add(rm, font_default);
#else
#endif
  assets_manager_add(rm, image_arr_left);
  assets_manager_add(rm, image_arr_left_hover);
  assets_manager_add(rm, image_arr_left_push);
  assets_manager_add(rm, image_arr_right);
  assets_manager_add(rm, image_arr_right_hover);
  assets_manager_add(rm, image_arr_right_push);
  assets_manager_add(rm, image_backspace);
  assets_manager_add(rm, image_bell);
  assets_manager_add(rm, image_bg0_mix);
  assets_manager_add(rm, image_bg1_mix);
  assets_manager_add(rm, image_btn_1);
  assets_manager_add(rm, image_btn_1_hover);
  assets_manager_add(rm, image_btn_1_push);
  assets_manager_add(rm, image_btn_2);
  assets_manager_add(rm, image_btn_2a);
  assets_manager_add(rm, image_btn_2a_hover);
  assets_manager_add(rm, image_btn_2a_push);
  assets_manager_add(rm, image_btn_2_hover);
  assets_manager_add(rm, image_btn_2_push);
  assets_manager_add(rm, image_btn_3);
  assets_manager_add(rm, image_btn_3_hover);
  assets_manager_add(rm, image_btn_3_push);
  assets_manager_add(rm, image_btn_4);
  assets_manager_add(rm, image_btn_4_hover);
  assets_manager_add(rm, image_btn_4_push);
  assets_manager_add(rm, image_btn_5);
  assets_manager_add(rm, image_btn_5_hover);
  assets_manager_add(rm, image_btn_5_push);
  assets_manager_add(rm, image_clock);
  assets_manager_add(rm, image_fan_1a);
  assets_manager_add(rm, image_fan_1b);
  assets_manager_add(rm, image_fan_2);
  assets_manager_add(rm, image_wind_in);
  assets_manager_add(rm, image_wind_out);
  assets_manager_add(rm, style_default);
  assets_manager_add(rm, style_keyboard);
  assets_manager_add(rm, ui_calibration_win);
  assets_manager_add(rm, ui_kb_ascii);
  assets_manager_add(rm, ui_kb_default);
  assets_manager_add(rm, ui_kb_float);
  assets_manager_add(rm, ui_kb_hex);
  assets_manager_add(rm, ui_kb_int);
  assets_manager_add(rm, ui_kb_phone);
  assets_manager_add(rm, ui_kb_ufloat);
  assets_manager_add(rm, ui_kb_uint);
  assets_manager_add(rm, ui_keyboard);
  assets_manager_add(rm, ui_main);
  assets_manager_add(rm, ui_record);
  assets_manager_add(rm, ui_setting);
  assets_manager_add(rm, ui_timing);
#endif

  tk_init_assets();
  return RET_OK;
}
