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
 * \brief 断言的简单实现
 *
 * 使用本服务需要包含头文件 aw_assert.h
 *
 * // 更多内容待添加。。。
 *
 * \internal
 * \par modification history
 * - 1.00 12-10-23  orz, first implementation
 * \endinternal
 */

#ifndef __AW_ASSERT_H
#define __AW_ASSERT_H

/*lint ++flb */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup grp_aw_if_assert
 * \copydoc aw_assert.h
 * @{
 */

#ifdef AW_DEBUG

/* help macro */
#define _AW_VTOS(n)     #n          /* Convert n to string */
#define _AW_SVAL(m)     _AW_VTOS(m) /* Get string value of macro m */

/**
 * \brief 断言一个表达式
 *
 * 当表达式为真时这个宏不做任何事情，为假时会调用aw_assert_msg()输出断言信息，
 * 断言信息格式为：
 * 文件名：行号：表达式
 * \hideinitializer
 */
#define aw_assert(e) \
    ((e) ? (void)0 : aw_assert_msg(__FILE__":"_AW_SVAL(__LINE__)":("#e")\n"))

extern void aw_assert_msg (const char *msg);

#else

/**
 * \brief 断言一个表达式
 *
 * 当表达式为真时这个宏不做任何事情，为假时会调用aw_assert_msg()输出断言信息，
 * 断言信息格式为：
 * 文件名：行号：表达式
 * \hideinitializer
 */
#define aw_assert(e)    ((void)0)
#endif

#ifdef __cplusplus
}
#endif

/** @}  aw_grp_if_assert */

#endif /* __AW_ASSERT_H */

/* end of file */
