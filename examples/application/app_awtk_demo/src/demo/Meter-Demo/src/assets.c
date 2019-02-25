#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/inc/strings/en_US.data"
#include "assets/inc/strings/zh_CN.data"
#include "assets/inc/styles/default.data"
#ifdef WITH_STB_IMAGE
#include "assets/inc/images/bg.res"
#include "assets/inc/images/pointer_big.res"
#include "assets/inc/images/pointer_small.res"
#else
#include "assets/inc/images/bg.data"
#include "assets/inc/images/pointer_big.data"
#include "assets/inc/images/pointer_small.data"
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
  assets_manager_add(rm, image_bg);
  assets_manager_add(rm, image_pointer_big);
  assets_manager_add(rm, image_pointer_small);
  assets_manager_add(rm, style_default);
#endif

  tk_init_assets();
  return RET_OK;
}
