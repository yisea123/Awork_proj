/**
 * file:   main_loop_aworks_raw.c
 * Author: AWTK Develop Team
 * brief:  main loop for aworks
 *
 * copyright (c) 2018 - 2018 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-05-23 li xianjing <xianjimli@hotmail.com> created
 *
 */

#include "aw_ts.h"
#include "aw_cache.h"
#include "aw_emwin_fb.h"
#include "base/idle.h"
#include "base/timer.h"
#include "aw_prj_params.h"
#include "lcd/lcd_mem_bgr565.h"
#include "main_loop/main_loop_simple.h"

static aw_ts_id ts_app_init(void) {
  aw_ts_id sys_ts = aw_ts_serv_id_get("480x272", 0, 0);

  return_value_if_fail(sys_ts != NULL, NULL);
//  return_value_if_fail(aw_ts_calc_data_read(sys_ts) == AW_OK, NULL);

  return sys_ts;
}

ret_t platform_disaptch_input(main_loop_t* loop) {
  int tsret = 0;
  static aw_ts_id ts_id = NULL;
  struct aw_ts_state ts_state;

  memset(&ts_state, 0x00, sizeof(ts_state));
  if (ts_id == NULL) {
    ts_id = ts_app_init();
  }

  return_value_if_fail(ts_id != NULL, RET_FAIL);

  tsret = aw_ts_exec(ts_id, &ts_state, 1);
  if (tsret >= 0) {
    if (ts_state.pressed) {
      main_loop_post_pointer_event(loop, ts_state.pressed, ts_state.x,
          ts_state.y);
    } else {
      main_loop_post_pointer_event(loop, ts_state.pressed, ts_state.x,
          ts_state.y);
    }
  }

  return RET_OK;
}

extern uint32_t* aworks_get_online_fb(void);
extern uint32_t* aworks_get_offline_fb(void);
extern aw_emwin_fb_info_t* aworks_get_fb(void);
extern int aworks_get_fb_size();
static lcd_flush_t s_lcd_flush_default = NULL;

static ret_t lcd_aworks_fb_flush(lcd_t* lcd) {
#if 0  // �Ƿ�ȴ���ֱͬ��
  // aw_emwin_fb_vram_addr_set �� aw_cache_flush �����Ч����ã����еȴ�ʱ��
  aw_emwin_fb_vram_addr_set(aworks_get_fb(), aworks_get_online_fb()); // max 13ms wait
#endif

  if (s_lcd_flush_default != NULL) {
    s_lcd_flush_default(lcd);
  }

  // ���� aw_cache_flush �ܼ�����Ƹ��������⣬��������ȫȥ��
  aw_cache_flush(aworks_get_online_fb(), aworks_get_fb_size()); // max 2ms wait
  return RET_OK;
}

static ret_t lcd_aworks_begin_frame(lcd_t* lcd, rect_t* dirty_rect) {
  if (lcd_is_swappable(lcd)) {
    lcd_mem_t* mem = (lcd_mem_t*)lcd;
    (void)mem;

#if 0 // ������һ�����ݵ�offline fb��Ϊ����, begin_frame֮��ֻ�������������
    // ��ǰ��awtk�����ʵ�ֻ���: ÿ֡begin_frameʱ�������������һ֡������κϲ�һ��
    // ����, ��ǰ֡����ʱҲ�����һ֡��������Ҳ����һ��, ����������ִ�������memcpy(������һ�����ݵ�offline fb��Ϊ����)
    // ������Ժ�awtk�޸����������, �ͱ���ִ�������memcpy��
    memcpy(mem->offline_fb, mem->online_fb, aworks_get_fb_size());
#endif

#if 0 // �����ô���, offline fb ���հ�, �������Թ۲�ÿ�λ��Ƶ������
    memset(mem->offline_fb, 0, aworks_get_fb_size());
#endif
  }

  return RET_OK;
}

static ret_t lcd_aworks_swap(lcd_t* lcd) {
  lcd_mem_t* mem = (lcd_mem_t*)lcd;

  uint8_t* next_online_fb = mem->offline_fb;
  mem->offline_fb = mem->online_fb;
  mem->online_fb = next_online_fb;

  aw_cache_flush(next_online_fb, aworks_get_fb_size()); // max 2ms wait
  aw_emwin_fb_vram_addr_set(aworks_get_fb(), (uintptr_t)next_online_fb); // max 13ms wait, �ȴ���ֱͬ��������fb
  return RET_OK;
}

lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  lcd_t* lcd = lcd_mem_bgr565_create_double_fb(w, h, (uint8_t*) aworks_get_online_fb(),
      (uint8_t*) aworks_get_offline_fb());

  if (lcd != NULL) {
#if 0
    // �Ľ�flush����, ÿ��flush�����cache_flush
    s_lcd_flush_default = lcd->flush;
    lcd->flush = lcd_aworks_fb_flush;
#else
    // ʹ��swap����
    lcd->begin_frame = lcd_aworks_begin_frame;
    lcd->swap = lcd_aworks_swap;
#endif
  }

  return lcd;
}

#include "main_loop/main_loop_raw.inc"
