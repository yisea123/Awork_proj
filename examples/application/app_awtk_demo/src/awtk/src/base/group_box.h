﻿/**
 * File:   group_box.h
 * Author: AWTK Develop Team
 * Brief:  group_box
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
 * 2018-02-11 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_GROUP_BOX_H
#define TK_GROUP_BOX_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @class group_box_t
 * @parent widget_t
 * @annotation ["scriptable"]
 * 分组控件。
 */
typedef struct _group_box_t {
  widget_t widget;
} group_box_t;

/**
 * @method group_box_create
 * 创建group_box对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* group_box_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method group_box_cast
 * 转换为group_box对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget group_box对象。
 *
 * @return {widget_t*} group_box对象。
 */
widget_t* group_box_cast(widget_t* widget);

END_C_DECLS

#endif /*TK_GROUP_BOX_H*/
