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
 * \brief emWin 5.22 ֡�����豸�ӿ�ͷ�ļ�
 *
 * \par ʹ��˵��
 *  ʹ��֡�����豸ǰ, ���ȵ���aw_emwin_fb_open����, �������aw_emwin_fb_init����
 *  ��֡�����豸���г�ʼ��, ��ʱ, ֡�����豸���󴴽����.
 *
 * \par ʹ��ʾ��
 * \code
 * #include "aw_emwin_fb.h"
 *
 *  // ʹ��˳����������
 *  uint32_t *p_vaddr = NULL;
 *  aw_emwin_fb_info_t *pfb = aw_emwin_fb_open("mxs_emwin_fb", 0);
 *
 *  p_vaddr = aw_cache_dma_malloc(pfb->x_res * pfb->y_res * 2 * 2);
 *
 *  aw_emwin_fb_init(pfb, p_vaddr, AW_FB_VERTICAL_SCREEN);
 *
 *  aw_emwin_fb_run(pfb);            // frame buffer����
 *  aw_emwin_fb_backlight(pfb, 80);  // ���ñ�������
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
    AW_EMWIN_CMD_FLIP = 1,      /** \brief �л������� */
};

/** \brief ֡�����豸�����ӿ� */
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

/** \brief ֡�����豸��Ϣ */
typedef struct aw_emwin_fb_info {

	size_t      x_res;
	size_t      y_res;
	size_t      bpp;
	uint32_t    v_addr;          /* Video RAM address */
	uint32_t    v_addr2;          /* Video RAM address2. Set if supported. */

	uint32_t    orientation;     /* ������ʾ �� ������ʾ */

	aw_emwin_fb_ops_t fb_ops;

	void	*p_cookie;

} aw_emwin_fb_info_t;

/**
 * \brief ��֡�����豸
 *
 * \param	name  	�豸��
 * \param	unit	�豸��Ԫ��
 *
 * \return   	NULL-ʧ�ܣ�����Ϊ֡�豸
 */
aw_emwin_fb_info_t *aw_emwin_fb_open(const char *name, int unit);

/**
 * \brief ��ʼ��֡�����豸
 *
 * \param	info  	              ֡�����豸��Ϣ
 * \param	vram_addr    Video RAM���׵�ַ
 *                       ��vram_addr == NULLʱ, ��ϵͳ����
 *                       (ϵͳĬ�Ϸ���Ĵ�СΪLCD_XSIZE * LCD_YSIZE * LCD_BITSPERPIXEL/8 * NUM_SCREENS, NUM_SCREENS = 2)
 *
 * \param   orientation  ��ʾģʽ
 *                       AW_FB_HORIZONTAL_SCREEN -  ����
 *                       AW_FB_VERTICAL_SCREEN   -  ����
 *
 * \return  0         ��ʼ���ɹ�
 *          -EINVAL   nbytesС��0
 */
aw_err_t aw_emwin_fb_init(aw_emwin_fb_info_t *info, uint32_t *p_vram_addr, int orientation);

/**
 * \brief ����֡�����豸
 *
 * \param	info  	      ֡�����豸��Ϣ
 *
 * \return  0         ���гɹ�
 */
aw_err_t aw_emwin_fb_run(aw_emwin_fb_info_t *info);

/**
 * \brief ֹͣ֡�����豸   (δ����)
 *
 * \param   info      ֡�����豸��Ϣ
 *
 * \return  0         ֹͣ�ɹ�
 */
aw_err_t aw_emwin_fb_stop(aw_emwin_fb_info_t *info);

/**
 * \brief ����֡�����豸����
 *
 * \param	info  	֡�����豸��Ϣ
 * \param	unit    ��������(ϵͳ֧�ֵ���Ч������<aw_emwin_fb.h>�ж���)
 *
 * \return
 */
aw_err_t aw_emwin_fb_blank(aw_emwin_fb_info_t *info, int blank);


/**
 * \brief ioctl
 *
 * \param   info    ֡�����豸��Ϣ
 * \param   cmd     enum aw_emwin_iocmd�ж���
 *
 * \return
 */
aw_err_t aw_emwin_fb_ioctl(aw_emwin_fb_info_t *info, enum aw_emwin_iocmd cmd, ... );

/**
 * \brief ����֡�����豸����
 *
 * \param	info  	   ֡�����豸��Ϣ
 * \param	level    ���⼶��(0 - 100)
 *                   (������õı��⼶���ںϷ��ķ�Χ��, ��ʹ��Ĭ�ϱ��⼶��100.)
 *
 * \return  AW_OK    ���óɹ�
 */
aw_err_t aw_emwin_fb_backlight(aw_emwin_fb_info_t *info, int level);

/**
 * \brief ����֡�����豸���� (GPIO)
 *
 * \param info    ֡�����豸��Ϣ
 * \param on      �򿪻�ر�
 *
 * \return AW_OK  ���óɹ�
 */
aw_err_t aw_emwin_fb_backlight_by_gpio(aw_emwin_fb_info_t *info, bool_t on);

/**
 * \brief ���ô���ʾVideo RAM�ĵ�ַ
 *
 * \param	info  	   ֡�����豸��Ϣ
 * \param	addr     ����ʾVideo RAM�ĵ�ַ
 *
 * \return  0        ��ʾ�ɹ�
 *          -EINVAL  addrС��0
 */
aw_err_t aw_emwin_fb_vram_addr_set(aw_emwin_fb_info_t *info, uint32_t addr);

/**
 * \brief ��ȡ����ʾVideo RAM�ĵ�ַ
 *
 * \param	info  	   ֡�����豸��Ϣ
 *
 * \return  void*    ָ��vram
 */
void* aw_emwin_fb_vram_addr_get(aw_emwin_fb_info_t *info);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AW_EMWIN_FB_H */

/* end of file */

