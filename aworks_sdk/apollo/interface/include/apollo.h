/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Apollo标准定义头文件
 *
 * 在所有需要使用Apollo的任何服务的模块(*.<b>c</b>文件)中，该文件必须被直接
 * 或间接地包含。
 *
 * \internal
 * \par modification history:
 * - 1.00 12-07-16  zen, first implementation
 * \endinternal
 */

#ifndef __APOLLO_H
#define __APOLLO_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aw_common.h"  /* 标准定义头文件 */

int aw_main( void ); /* 声明用户入口，将其固定为 C 函数，允许用户将此函数定义在C++文件中  */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __APOLLO_H */

/* end of file */
