/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn
* e-mail:      support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 时间戳相关服务
 *
 * 需要包含了 aw_timestamp.h 就可以使用本服务。
 *
 * \par 简单示例:计算程序执行时间,us级别的时间测量
 * \code
 *  #include "aw_timestamp.h"
 *
 *  int main()
 *  {
 *      unsigned int stamps;
 *
 *      stamps = aw_timestamp_get();
 *      //  do something
 *      stamps = aw_timestamp_get() - stamps;
 *      aw_kprintf("stamps used=%d\n , time=%d us",
 *                  stamps,
 *                  aw_stamps_to_us(tick));
 *      return 0;
 *  }
 * \endcode
 *
 * //更多内容待添加。。。
 *
 * \internal
 * \par modification history:
 * - 1.01 14-08-18  tee,   modified and tested. 
 * - 1.00 13-02-27  zen,   first implementation
 * \endinternal
 */

#ifndef __AW_TIMESTAMP_H
#define __AW_TIMESTAMP_H

#include "aw_types.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup grp_aw_if_timestamp
 * \copydoc aw_timestamp.h
 * @{
 */
 
/** \brief 定义时间戳频率的类型 */
typedef aw_psp_timestamp_freq_t aw_timestamp_freq_t;

/**
 * \brief 获取时间戳 (32位)
 *
 * \return 系统当前时间戳值(时间戳定时器的计数值)
 */
uint32_t aw_timestamp_get(void);

/**
 * \brief  将时间戳转换为时间(us)
 * \param  stamps 时间戳个数
 * \return 根据时间戳个数，转换得到的时间us数
 */
uint32_t aw_timestamps_to_us(uint32_t stamps);
    
/**
 * \brief 获取时间戳定时器频率 (32位)
 *
 * \return 时间戳定时器频率, Hz
 */
aw_timestamp_freq_t aw_timestamp_freq_get(void);

/**
 * \brief 获取时间戳 (64位)
 *
 * \return 系统当前时间戳值(时间戳定时器的计数值)
 */
uint64_t aw_timestamp_get64(void);

/**
 * \brief 计算两个时间戳的差值 (32位)
 *
 *  不需要考虑反转的问题: 负数的表示机制能自动避免反转问题，如0xfffffff即表示无符号的最大值(32bit)，
 *  也表示有符号数的-1.
 * \return 系统当前时间戳值(时间戳定时器的计数值)
 */
static aw_inline uint32_t aw_timestamp_diff(uint32_t __t0, uint32_t __t1)
{
    return __t1 - __t0;
}
/**
 * \brief 计算两个时间戳的差值 (64位)
 *
 *  不需要考虑反转的问题: 负数的表示机制能自动避免反转问题
 * \return 系统当前时间戳值(时间戳定时器的计数值)
 */
static aw_inline uint64_t aw_timestamp_diff64(uint64_t __t0, uint64_t __t1)
{
    return __t1 - __t0;
}
  
/** @} grp_aw_if_system */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif    /* __AW_TIMESTAMP_H    */

/* end of file */
