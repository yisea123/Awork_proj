/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief emWin 5.22 帧缓冲设备接口头文件
 *
 * \par 使用说明
 *  使用帧缓冲设备前, 请先调用aw_emwin_fb_open函数, 而后调用aw_emwin_fb_init函数
 *  对帧缓冲设备进行初始化, 此时, 帧缓冲设备对象创建完成.
 *
 * \par 使用示例
 * \code
 * #include "aw_emwin_fb.h"
 *
 *  // 使用顺序依赖如下
 *  uint32_t *p_vaddr = NULL;
 *  aw_emwin_fb_info_t *pfb = aw_emwin_fb_open("mxs_emwin_fb", 0);
 *
 *  p_vaddr = aw_cache_dma_malloc(pfb->x_res * pfb->y_res * 2 * 2);
 *
 *  aw_emwin_fb_init(pfb, p_vaddr, AW_FB_VERTICAL_SCREEN);
 *
 *  aw_emwin_fb_run(pfb);            // frame buffer运行
 *  aw_emwin_fb_backlight(pfb, 80);  // 设置背光亮度
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.02 14-10-17  ops, code optimization.
 * - 1.00 14-08-05  ops, add five interface
 * - 1.00 14-05-29  zen, first implementation
 * \endinternal
 */

#ifndef __AW_EMWIN_FB_H
#define __AW_EMWIN_FB_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */
#include <stdarg.h>
#include "apollo.h"
#include "aw_intensity.h"
#include "aw_cache.h"

#define AW_FB_BLANK_UNBLANK            0    /* Screen : unblanked, hsync: on,  vsync: on   */
#define AW_FB_BLANK_NORMAL             1    /* Screen : blanked,   hsync: on,  vsync: on   */
#define AW_FB_BLANK_VSYNC_SUSPEND      2    /* Screen : blanked,   hsync: on,  vsync: off  */
#define AW_FB_BLANK_HSYNC_SUSPEND      3    /* Screen : blanked,   hsync: off, vsync: on   */
#define AW_FB_BLANK_POWERDOWN          4    /* Screen : blanked,   hsync: off, vsync: off  */

#define AW_FB_HORIZONTAL_SCREEN        0
#define AW_FB_VERTICAL_SCREEN          1

struct aw_emwin_fb_info;

enum aw_emwin_iocmd {
    AW_EMWIN_CMD_FLIP = 1,      /** \brief 切换缓冲区 */
};

/** \brief 帧缓冲设备操作接口 */
typedef struct aw_emwin_fb_ops {

	aw_err_t (*lcd_x_backlight)(struct aw_emwin_fb_info *p_fb, int level);
	aw_err_t (*lcd_x_backlight_by_gpio)(struct aw_emwin_fb_info *p_fb, bool_t on);
	aw_err_t (*lcd_x_blank)(struct aw_emwin_fb_info *p_fb, int blank);
	aw_err_t (*lcd_x_init)(struct aw_emwin_fb_info *p_fb);
	aw_err_t (*lcd_x_run)(struct aw_emwin_fb_info *p_fb);
	aw_err_t (*lcd_x_stop)(struct aw_emwin_fb_info *p_fb);
	aw_err_t (*lcd_x_vram_set)(struct aw_emwin_fb_info *p_fb, uint32_t addr);
	void* (*lcd_x_vram_get)(struct aw_emwin_fb_info *p_fb);

    aw_err_t (*lcd_x_ioctl)( struct aw_emwin_fb_info *p_fb, enum aw_emwin_iocmd cmd, va_list va );
}aw_emwin_fb_ops_t;

/** \brief 帧缓冲设备信息 */
typedef struct aw_emwin_fb_info {

	size_t      x_res;
	size_t      y_res;
	size_t      bpp;
	uint32_t    v_addr;          /* Video RAM address */
	uint32_t    v_addr2;          /* Video RAM address2. Set if supported. */

	uint32_t    orientation;     /* 横屏显示 或 竖屏显示 */

	aw_emwin_fb_ops_t fb_ops;

	void	*p_cookie;

} aw_emwin_fb_info_t;

/**
 * \brief 打开帧缓冲设备
 *
 * \param	name  	设备名
 * \param	unit	设备单元号
 *
 * \return   	NULL-失败，否则为帧设备
 */
aw_emwin_fb_info_t *aw_emwin_fb_open(const char *name, int unit);

/**
 * \brief 初始化帧缓冲设备
 *
 * \param	info  	              帧缓冲设备信息
 * \param	vram_addr    Video RAM的首地址
 *                       当vram_addr == NULL时, 由系统分配
 *                       (系统默认分配的大小为LCD_XSIZE * LCD_YSIZE * LCD_BITSPERPIXEL/8 * NUM_SCREENS, NUM_SCREENS = 2)
 *
 * \param   orientation  显示模式
 *                       AW_FB_HORIZONTAL_SCREEN -  横屏
 *                       AW_FB_VERTICAL_SCREEN   -  竖屏
 *
 * \return  0         初始化成功
 *          -EINVAL   nbytes小于0
 */
aw_err_t aw_emwin_fb_init(aw_emwin_fb_info_t *info, uint32_t *p_vram_addr, int orientation);

/**
 * \brief 运行帧缓冲设备
 *
 * \param	info  	      帧缓冲设备信息
 *
 * \return  0         运行成功
 */
aw_err_t aw_emwin_fb_run(aw_emwin_fb_info_t *info);

/**
 * \brief 停止帧缓冲设备   (未测试)
 *
 * \param   info      帧缓冲设备信息
 *
 * \return  0         停止成功
 */
aw_err_t aw_emwin_fb_stop(aw_emwin_fb_info_t *info);

/**
 * \brief 设置帧缓冲设备消隐
 *
 * \param	info  	帧缓冲设备信息
 * \param	unit    消隐级别(系统支持的有效级别在<aw_emwin_fb.h>中定义)
 *
 * \return
 */
aw_err_t aw_emwin_fb_blank(aw_emwin_fb_info_t *info, int blank);


/**
 * \brief ioctl
 *
 * \param   info    帧缓冲设备信息
 * \param   cmd     enum aw_emwin_iocmd中定义
 *
 * \return
 */
aw_err_t aw_emwin_fb_ioctl(aw_emwin_fb_info_t *info, enum aw_emwin_iocmd cmd, ... );

/**
 * \brief 设置帧缓冲设备背光
 *
 * \param	info  	   帧缓冲设备信息
 * \param	level    背光级别(0 - 100)
 *                   (如果设置的背光级别不在合法的范围内, 将使用默认背光级别100.)
 *
 * \return  AW_OK    设置成功
 */
aw_err_t aw_emwin_fb_backlight(aw_emwin_fb_info_t *info, int level);

/**
 * \brief 设置帧缓冲设备背光 (GPIO)
 *
 * \param info    帧缓冲设备信息
 * \param on      打开或关闭
 *
 * \return AW_OK  设置成功
 */
aw_err_t aw_emwin_fb_backlight_by_gpio(aw_emwin_fb_info_t *info, bool_t on);

/**
 * \brief 设置待显示Video RAM的地址
 *
 * \param	info  	   帧缓冲设备信息
 * \param	addr     待显示Video RAM的地址
 *
 * \return  0        显示成功
 *          -EINVAL  addr小于0
 */
aw_err_t aw_emwin_fb_vram_addr_set(aw_emwin_fb_info_t *info, uint32_t addr);

/**
 * \brief 获取待显示Video RAM的地址
 *
 * \param	info  	   帧缓冲设备信息
 *
 * \return  void*    指向vram
 */
void* aw_emwin_fb_vram_addr_get(aw_emwin_fb_info_t *info);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_EMWIN_FB_H */

/* end of file */

