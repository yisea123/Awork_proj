﻿/**
 * File:   window_main.c
 * Author: AWTK Develop Team
 * Brief:  main window
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
#include <time.h>
#include <math.h>
#include "base/view.h"
#include "base/utils.h"
#include "base/timer.h"
#include "base/image.h"
#include "base/label.h"
#include "base/window.h"
#include "base/window_manager.h"
#include "widget_animators/widget_animator_rotation.h"

#define SMALL_RADIUS    150
#define BIG_RADIUS      240
#define PROP_NEEDLE_LEN "needle_len"
#define PROP_ANCHOR_X   "anchor_x"
#define PROP_ANCHOR_Y   "anchor_y"

/**
 * 重绘
 */
static ret_t on_paint_needle(void* ctx, event_t* e) {
  value_t v;
  paint_event_t* evt = (paint_event_t*)e;
  canvas_t* c = evt->c;
  widget_t* widget = WIDGET(evt->e.target);
  vgcanvas_t* vg = lcd_get_vgcanvas(c->lcd);

  int needle_len = 0;
  int anchor_x = 0;
  int anchor_y = 0;
  float rotation = 0;

  return_value_if_fail(widget != NULL && c != NULL, RET_BAD_PARAMS);
  
  if (widget_get_prop(widget, PROP_NEEDLE_LEN, &v) == RET_OK) {
    needle_len = value_int(&v);
  }

  if (widget_get_prop(widget, PROP_ANCHOR_X, &v) == RET_OK) {
    anchor_x = value_int(&v);
  }

  if (widget_get_prop(widget, PROP_ANCHOR_Y, &v) == RET_OK) {
    anchor_y = value_int(&v);
  }

  if (widget_get_prop(widget, WIDGET_PROP_ROTATION, &v) == RET_OK) {
    rotation = value_float(&v);
  }

  if (vg != NULL) {
    vgcanvas_save(vg);
    vgcanvas_translate(vg, anchor_x+needle_len/2, anchor_y+needle_len/2);
    vgcanvas_set_fill_color(vg, color_init(0xff, 0, 0, 0xff));
    vgcanvas_rounded_rect(vg, 0, 0, 20, 20, 20);
    vgcanvas_fill(vg);

    float len1 = needle_len*2/3 - 20;
    float len2 = needle_len*1/3 - 20;
    if(needle_len == BIG_RADIUS) {
      len1 = needle_len*2/3 - 50;
      len2 = needle_len*1/3 - 50;
    }
 
    float x1 = len1 * cos(rotation - 3.14156 / 2) + 10;
    float y1 = len1 * sin(rotation - 3.14156 / 2) + 10;
    float x2 = len2 * cos(rotation + 3.14156 / 2) + 10;
    float y2 = len2 * sin(rotation + 3.14156 / 2) + 10;

    vgcanvas_set_stroke_color(vg, color_init(0xff, 0, 0, 0xff));
    vgcanvas_set_line_width(vg, 3);
    vgcanvas_begin_path(vg);
    vgcanvas_move_to(vg, x1, y1);
    vgcanvas_line_to(vg, x2, y2);
    vgcanvas_stroke(vg);
    vgcanvas_restore(vg);
  }

  return RET_OK;
}

/**
 * 初始化图片和动画
 */
static void init_image(widget_t* win, int x, int y, int w, int h, char* img_name, float from, float to, int duration, int radius) {
#if 0
  widget_t* img = image_create(win, x, y, w, h);
  image_set_image(img, img_name);
  image_set_draw_type(img, IMAGE_DRAW_ICON);
#else
  widget_t* img = view_create(win, x, y, w, h);
  value_t   val;
  value_set_uint32(&val, radius);
  widget_set_prop(img, PROP_NEEDLE_LEN, &val);

  value_set_float(&val, 1.1);
  widget_set_prop(img, WIDGET_PROP_ROTATION, &val);

  value_set_uint32(&val, x);
  widget_set_prop(img, PROP_ANCHOR_X, &val);

  value_set_uint32(&val, y);
  widget_set_prop(img, PROP_ANCHOR_Y, &val);
  widget_on(img, EVT_PAINT, on_paint_needle, NULL); 
#endif

  char rotation_str[100];
  memset(rotation_str, 0, sizeof(rotation_str));
  tk_snprintf(rotation_str, sizeof(rotation_str), "rotation(from=%f ,to=%f, yoyo_times=0, duration=%d, easing=linear)", from, to, duration);
  widget_create_animator(img, rotation_str);
}

/**
 * 创建图片,rotation中的from和to使用的是弧度：1弧度=180/3.14=57.324度
 */
static ret_t create_images(widget_t* win){
  char small_image[] = "pointer_small";
  char big_image[] = "pointer_big";

  /* 这里的宽和高是指仪表盘宽度和高度，x, y指是各个仪表盘在背景图片上的左上标位置 */
  int width = 171;
  int height = 171;

  /* 左边：从上到下 */
  init_image(win, 114, 2, width, height, small_image, -2.2, 2.2, 2000, SMALL_RADIUS);
  init_image(win, 9, 140, width, height, small_image, -1.7, 1.7, 4000, SMALL_RADIUS);
  init_image(win, 44, 307, width, height, small_image, -1.5, 1.5, 3000, SMALL_RADIUS);

  /* 中间 */
  init_image(win, 272, -3, 261, 261, big_image, -2.5, 2.5, 2000, BIG_RADIUS);

  /* 右边：从上到下 */ 
  init_image(win, 524, 2, width, height, small_image, -2.2, 2.2, 2000, SMALL_RADIUS);
  init_image(win, 627, 140, width, height, small_image, -1.7, 1.7, 4000, SMALL_RADIUS);
  init_image(win, 595, 307, width, height, small_image, -1.5, 1.5, 3000, SMALL_RADIUS);

  return RET_OK;
}

/**
 * 初始化label
 */
static void init_label(widget_t* win, int x, int y, int w, int h, const wchar_t* text, const char* widget_name) {
  widget_t* label = label_create(win, x, y, w, h);
  widget_set_text(label, text);
  widget_set_name(label, widget_name);
}

/**
 * 创建label
 */
static ret_t create_labels(widget_t* win){
  int width = 30;
  int height = 30;
  
  /* 左边：从上到下 */
  init_label(win, 330, 315, width, height, L"3005", "left_top_label");
  init_label(win, 330, 365, width, height, L"12", "left_center_label");
  init_label(win, 330, 415, width, height, L"13", "left_bottom_label");

  /* 右边：从上到下 */
  init_label(win, 522, 315, width, height, L"14", "right_top_label");
  init_label(win, 522, 365, width, height, L"15", "right_center_label");
  init_label(win, 522, 415, width, height, L"16", "right_bottom_label");

  return RET_OK;
}

/**
 * Label文本随机显示int
 */
static void label_set_random_int(widget_t* label, int32_t min_num, int32_t max_num) {
  if (label) {
    char text[32];
    int32_t val = fmod(rand(), max_num - min_num) + min_num;
    widget_set_text_utf8(label, tk_itoa(text, sizeof(text), val));
  }
}

/**
 * 更新Label上的显示数值
 */
static ret_t on_update_label(const timer_info_t* timer) {
  widget_t* win = WIDGET(timer->ctx);

  /* 左边 */
  widget_t* left_top_label = widget_lookup(win, "left_top_label", TRUE);
  if (left_top_label) {
    label_set_random_int(left_top_label, 3000, 5000);
  }

  widget_t* left_center_label = widget_lookup(win, "left_center_label", TRUE);
  if (left_center_label) {
    label_set_random_int(left_center_label, 10, 30);
  }

  widget_t* left_bottom_label = widget_lookup(win, "left_bottom_label", TRUE);
  if (left_bottom_label) {
    label_set_random_int(left_bottom_label, 1, 15);
  }

  /* 右边 */
  widget_t* right_top_label = widget_lookup(win, "right_top_label", TRUE);
  if (right_top_label) {
    label_set_random_int(right_top_label, 1, 15);
  }

  widget_t* right_center_label = widget_lookup(win, "right_center_label", TRUE);
  if (right_center_label) {
    label_set_random_int(right_center_label, 1, 15);
  }

  widget_t* right_bottom_label = widget_lookup(win, "right_bottom_label", TRUE);
  if (right_bottom_label) {
    label_set_random_int(right_bottom_label, 1, 15);
  }

  return RET_REPEAT;
}

/**
 * 打开主窗口
 */
ret_t open_main_window(void) {
  widget_t* main_win = window_create(NULL, 0, 0, 0, 0);
  if (main_win) {
    create_images(main_win);
    create_labels(main_win);
    timer_add(on_update_label, main_win, 1000);
#if 0
    widget_t* widget = window_manager();
    window_manager_set_show_fps(widget, TRUE);
#endif
    return RET_OK;
  }

  return RET_FAIL;
}

