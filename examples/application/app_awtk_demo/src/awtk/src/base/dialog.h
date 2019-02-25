﻿/**
 * File:   dialog.h
 * Author: AWTK Develop Team
 * Brief:  dialog
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
 * 2018-01-13 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_DIALOG_H
#define TK_DIALOG_H

#include "base/window_base.h"

BEGIN_C_DECLS

/**
 * @class dialog_t
 * @parent widget_t
 * @annotation ["scriptable"]
 * 对话框控件。
 */
typedef struct _dialog_t {
  window_base_t window;

  /*private*/
  widget_t* title;
  widget_t* client;
  uint32_t quit_code;

} dialog_t;

/**
 * @method dialog_create
 * 创建dialog对象。
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} dialog对象。
 */
widget_t* dialog_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method dialog_create_simple
 * 创建dialog对象，同时创建title/client。
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} dialog对象。
 */
widget_t* dialog_create_simple(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method dialog_cast
 * 转换dialog对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget dialog对象。
 *
 * @return {widget_t*} dialog对象。
 */
widget_t* dialog_cast(widget_t* widget);

/**
 * @method dialog_get_title
 * 获取title控件。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget dialog对象。
 *
 * @return {widget_t*} title对象。
 */
widget_t* dialog_get_title(widget_t* widget);

/**
 * @method dialog_get_client
 * 获取client控件。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget dialog对象。
 *
 * @return {widget_t*} client对象。
 */
widget_t* dialog_get_client(widget_t* widget);

/**
 * @method dialog_open
 * @annotation ["constructor", "scriptable"]
 * 从资源文件中加载并创建Dialog对象。本函数在ui_loader/ui_builder_default里实现。
 * @param {char*} name dialog的名称。
 *
 * @return {widget_t*} 对象。
 */
widget_t* dialog_open(const char* name);

/**
 * @method dialog_set_title
 * 设置对话框的标题文本。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget dialog对象。
 * @param {char*}  title 标题。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t dialog_set_title(widget_t* widget, const char* title);

/**
 * @method dialog_modal
 * 模态显示对话框。
 * @annotation ["scriptable"]
 * dialog_modal返回后，dialog对象将在下一个idle函数中回收，也就是在dialog_modal调用完成后仍然可以访问dialog中控件，直到本次事件结束。
 * @param {widget_t*} widget dialog对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
uint32_t dialog_modal(widget_t* widget);

/**
 * @method dialog_quit
 * 退出模态显示。
 * @annotation ["scriptable"]
 * @param {widget_t*} widget dialog对象。
 * @param {uint32_t} code 退出码，作为dialog_modal的返回值。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t dialog_quit(widget_t* widget, uint32_t code);

#define DIALOG(widget) ((dialog_t*)(widget))

END_C_DECLS

#endif /*TK_DIALOG_H*/
