
#include "driver/pxp/awbl_imx1050_pxp.h"
#include "base/g2d.h"
#include "stdint.h"
#include "aw_cache.h"
#include "aw_mem.h"
#include "aw_emwin_fb.h"

ret_t g2d_fill_rect(bitmap_t* fb, rect_t* dst, color_t c) {
  return RET_NOT_IMPL;
}

ret_t g2d_copy_image(bitmap_t* fb, bitmap_t* img, rect_t* src, xy_t dx, xy_t dy) {
  return RET_NOT_IMPL;
}



ret_t g2d_blend_image(bitmap_t* fb, bitmap_t* img, rect_t* dst, rect_t* src, uint8_t global_alpha)
{
    uint16_t as_format   = 0;
    uint16_t as_pixsize  = 0;
    uint16_t ps_format   = 0;
    uint16_t ps_pixsize  = 0;
    uint16_t out_format  = 0;
    uint16_t out_pixsize = 0;

    uint8_t  *p_src_data = NULL;
    uint32_t size = 0;

    pxp_output_buffer_config_t pxp_output_config;
    pxp_ps_buffer_config_t     ps_buffer_config;

    //return RET_NOT_IMPL;

    return_value_if_fail(fb != NULL && fb->data != NULL, RET_BAD_PARAMS);
    return_value_if_fail(img != NULL && img->data != NULL && src != NULL && dst != NULL,
                         RET_BAD_PARAMS);
    return_value_if_fail(fb->format == BITMAP_FMT_BGR565 || fb->format == BITMAP_FMT_BGRA8888,
                         RET_BAD_PARAMS);
    return_value_if_fail(img->format == BITMAP_FMT_BGR565 || img->format == BITMAP_FMT_BGRA8888,
                         RET_BAD_PARAMS);

    uint16_t as_x  = 0;
    uint16_t as_y  = 0;
    uint16_t as_w  = 0;
    uint32_t as_addr = 0;

    uint16_t ps_x  = 0;
    uint16_t ps_y  = 0;
    uint16_t ps_w  = 0;
    uint32_t ps_addr = 0;

    uint8_t *p_scale_buf = NULL;

    if (img->format == BITMAP_FMT_BGR565) {
        as_pixsize = 2;
        as_format = kPXP_AsPixelFormatRGB565;
    } else {
        as_pixsize = 4;
        as_format = kPXP_AsPixelFormatARGB8888;
    }

    if (fb->format == BITMAP_FMT_BGR565) {
        out_pixsize = 2;
        out_format = kPXP_OutputPixelFormatRGB565;
    } else {
        out_pixsize = 4;
        out_format = kPXP_OutputPixelFormatRGB888;
    }

	if ((uint32_t)img->data % 32) {
		assert(!"address must align to 32 bytes");
		return RET_NOT_IMPL;
    } else {
        p_src_data = (uint8_t *)img->data;
    }

    as_x = src->x;
    as_y = src->y;
    as_w = img->w;

    /* ����AS��ʼ��ַ */
    as_addr = ((uint32_t)p_src_data + as_pixsize * (as_w * as_y + as_x));

    /* ÿ��ʹ��֮ǰ��Ҫ��λPXPӲ�� */
    pxp_hard_reset();

    /* �ж��Ƿ���Ҫ���� */
    if ((src->w != dst->w) || (src->h != dst->h)) {

        if (img->format == BITMAP_FMT_BGR565) {
            ps_pixsize = 2;
            ps_format = kPXP_PsPixelFormatRGB565;

        } else {
            ps_pixsize = 4;
            ps_format = kPXP_PsPixelFormatRGB888;
        }

        ps_x = src->x;
        ps_y = src->y;
        ps_w = img->w;

        /* ����һƬdstĿ����ͬ����Ļ���  */
        p_scale_buf = (uint8_t *)aw_mem_align(dst->w * dst->h * out_pixsize, 32);
        return_value_if_fail(p_scale_buf != NULL, RET_FAIL);

        aw_cache_flush((void *)p_scale_buf, dst->w * dst->h * out_pixsize);
        aw_cache_flush((void *)p_src_data, img->w * img->h * ps_pixsize);

        /* ����PS��ʼ��ַ */
        ps_addr = ((uint32_t)p_src_data + ps_pixsize * (ps_w * ps_y + ps_x));

        /* PS configure. */
        ps_buffer_config.pixel_format  = ps_format;
        ps_buffer_config.swap_byte     = 0;
        ps_buffer_config.buffer_addr   = (uint32_t)ps_addr;
        ps_buffer_config.buffer_addr_u = 0;
        ps_buffer_config.buffer_addr_v = 0;
        ps_buffer_config.pitch_bytes   = ps_w * ps_pixsize;

        /* ���ñ�����ɫ */
        //pxp_set_process_surface_back_ground_color(0x0);

        /* ����PS buffer */
        pxp_set_process_surface_buffer_config(&ps_buffer_config);

        /* ����AS */
        pxp_set_alpha_surface_position(0xFFFF, 0xFFFF, 0, 0);

        /* Output config. */
        pxp_output_config.pixel_format = out_format;
        pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
        pxp_output_config.buffer0_addr = (uint32_t) p_scale_buf;
        pxp_output_config.buffer1_addr = 0;
        pxp_output_config.pitch_bytes = dst->w * out_pixsize;
        pxp_output_config.width  = dst->w;
        pxp_output_config.height = dst->h;

        pxp_set_output_buffer_config(&pxp_output_config);

        /* Disable CSC1, it is enabled by default. */
        pxp_enable_csc1(0);

        /* �������ŵ���������ͼ��ĳ�����  */
        pxp_set_process_surface_scaler(src->w, src->h, dst->w, dst->h);

        /* ����PSͼ�δ�СΪĿ�괰�ڵĴ�С */
        pxp_set_process_surface_position(0, 0, dst->w - 1, dst->h - 1);

        /* ��ʼ���Ŵ��� */
        pxp_start();

        /* Wait for process complete. */
        pxp_complete_status_sync();

        /* ���ˣ����Ŵ����ͼ���Ѿ������p_scale_buf�������� ����ʱ���¸�ֵAS��ʼ��ַ��
         * ���ڽ�������blend��
         */
        as_addr = (uint32_t)p_scale_buf;
        as_x = dst->x;
        as_y = dst->y;
        as_w = dst->w;

        as_format  = out_format;
        as_pixsize = out_pixsize;

        /* ��λһ��PXP��ʹ���Ź���ʧЧ�������Ų���Ӱ���������blend */
        pxp_hard_reset();

        aw_cache_invalidate((void *)p_scale_buf, dst->w * dst->h * out_pixsize);
        aw_cache_invalidate((void *)p_src_data, img->w * img->h * ps_pixsize);

    }

    aw_cache_flush((void *)fb->data, fb->w * fb->h * out_pixsize);
    aw_cache_flush((void *)p_src_data, img->w * img->h * as_pixsize);

    /* ����PS��ʼ��ַ (����framebuffer��ΪPS�� )*/
    ps_addr = (uint32_t)fb->data;

    /* PS configure. */
    ps_buffer_config.pixel_format  = out_format,
    ps_buffer_config.swap_byte     = 0,
    ps_buffer_config.buffer_addr   = (uint32_t)ps_addr,
    ps_buffer_config.buffer_addr_u = 0,
    ps_buffer_config.buffer_addr_v = 0,
    ps_buffer_config.pitch_bytes   = fb->w * out_pixsize,

    /* ����PS������ɫ */
   // pxp_set_process_surface_back_ground_color(0x00);

    /* ����PS buffer */
    pxp_set_process_surface_buffer_config(&ps_buffer_config);

    /* AS ���ò������� */
    pxp_as_buffer_config_t as_buffer_config = {
        .pixel_format = as_format,
        .buffer_addr  = (uint32_t)as_addr,
        .pitch_bytes  = as_w * as_pixsize,
    };

    /* AS���� */
    pxp_set_alpha_surface_buffer_config(&as_buffer_config);


    /* ����͸���ȵ�һЩ���� */
    pxp_as_blend_config_t as_blend_config = {
        .alpha = global_alpha,   /* ����͸���� */
        .invert_alpha = 0,
        .alpha_mode = kPXP_AlphaMultiply,
        .rop_mode = kPXP_RopMergeAs        /* �����ɫ */
    };
    pxp_set_alpha_surface_blend_config(&as_blend_config);

    /* Output config. */
    pxp_output_config.pixel_format = out_format;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = (uint32_t)fb->data;
    pxp_output_config.buffer1_addr = 0;
    pxp_output_config.pitch_bytes = fb->w * out_pixsize;
    pxp_output_config.width  = fb->w;
    pxp_output_config.height = fb->h;

    pxp_set_output_buffer_config(&pxp_output_config);

    /* Disable CSC1, it is enabled by default. */
    pxp_enable_csc1(0);

    /* ����AS��λ�� */
    pxp_set_alpha_surface_position(dst->x, dst->y , dst->x + dst->w - 1,dst->y + dst->h - 1);

    /* ����PS��λ�� */
    pxp_set_process_surface_position(0, 0, fb->w - 1, fb->h - 1);

    /* ��ʼblend */
    pxp_start();

    /* Wait for process complete. */
    pxp_complete_status_sync();

    aw_cache_invalidate((void *)fb->data, fb->w * fb->h * out_pixsize);
    aw_cache_invalidate((void *)p_src_data, img->w * img->h * as_pixsize);

    /* �ͷ��ڴ� */
    aw_mem_free(p_scale_buf);

    if (((uint32_t)img->data) != ((uint32_t)p_src_data)) {

        aw_mem_free(p_src_data);
    }

    return RET_OK;
}


ret_t g2d_rotate_image(bitmap_t* fb, bitmap_t* img, rect_t* src, lcd_orientation_t o)
{
	assert(src->x >= 0);
	assert(src->y >= 0);
	assert(src->w >= 0);
	assert(src->h >= 0);

    return_value_if_fail(o == LCD_ORIENTATION_90, RET_NOT_IMPL);
    return_value_if_fail(fb != NULL && img != NULL && src != NULL, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == img->format, RET_BAD_PARAMS);
    return_value_if_fail(fb->w == img->h && fb->h == img->w, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == BITMAP_FMT_RGBA8888 || fb->format == BITMAP_FMT_BGR565,
                         RET_NOT_IMPL);
    //return RET_NOT_IMPL;

    uint16_t ps_format   = 0;
    uint16_t ps_pixsize  = 0;
    uint16_t out_format  = 0;
    uint16_t out_pixsize = 0;
    uint32_t ps_addr = 0;
    uint32_t size = 0;

    wh_t ps_x  = 0;
    wh_t ps_y  = 0;
    wh_t ps_w  = 0;
    wh_t start = 0;
    int     i = 0;

    uint8_t *p_out_buf  = NULL;
    uint8_t *p_src_data = NULL;
    pxp_output_buffer_config_t pxp_output_config;
    pxp_ps_buffer_config_t     ps_buffer_config;


    if (img->format == BITMAP_FMT_BGR565) {
        ps_pixsize = 2;
        ps_format = kPXP_PsPixelFormatRGB565;
    } else {
        ps_pixsize = 4;
        ps_format = kPXP_PsPixelFormatRGB888;
    }

    if (fb->format == BITMAP_FMT_BGR565) {
        out_pixsize = 2;
        out_format = kPXP_OutputPixelFormatRGB565;

    } else {
        out_pixsize = 4;
        out_format = kPXP_OutputPixelFormatRGB888;
    }

    /* ���img��������ʼ��ַû��cache���� */
    if (((uint32_t)img->data % 32)) {

        /* ��С cache line ����  */
        size = (img->w * img->h * ps_pixsize+ AW_CACHE_LINE_SIZE - 1) /
                AW_CACHE_LINE_SIZE * AW_CACHE_LINE_SIZE;

        p_src_data = (uint8_t *)aw_mem_align(size, AW_CACHE_LINE_SIZE);
        return_value_if_fail(p_src_data != NULL, RET_FAIL);
        memcpy(p_src_data, img->data, img->w * img->h * ps_pixsize);

    } else {
        p_src_data = (uint8_t *)img->data;
    }

    ps_x = src->x + 1;  /* ע: ��������1���ܺ����ʵ�ֵĽ��һ�� */
    ps_y = src->y;
    ps_w = img->w;

    if ((fb->w != src->h) || (fb->h != src->w)) {  /* ���ֻ�ǽ�ȡ��Ļ��һ����ͼ�������ת */

        /* ����ͼ�εı߳�Ϊ8�������� */
        int re = src->h % 8;
        if (re != 0) {
            src->h += (8 - re);
        }
        re = src->w % 8;
        if (re != 0) {
            src->w  += (8 - re);
        }

        size = (src->w * src->h * out_pixsize + AW_CACHE_LINE_SIZE - 1) /
                AW_CACHE_LINE_SIZE * AW_CACHE_LINE_SIZE;

        /* ����һƬ��imgһ����С�Ļ��� */
        p_out_buf = (uint8_t *)aw_mem_align(size, AW_CACHE_LINE_SIZE);
        return_value_if_fail(p_out_buf != NULL, RET_FAIL);

    } else {   /* ���ֻ����ת������Ļ */
        p_out_buf = (uint8_t *)fb->data;
    }

    aw_cache_flush((void *)p_out_buf, src->w * src->h * out_pixsize);
    aw_cache_flush((void *)p_src_data, img->w * img->h * ps_pixsize);

    /* ����PS��ʼ��ַ */
    ps_addr = ((uint32_t)p_src_data) + (ps_y * ps_w + ps_x)* ps_pixsize ;

    /* ÿ��ʹ��֮ǰ��Ҫ��λPXPӲ�� */
    pxp_hard_reset();

    /* PS configure. */
    ps_buffer_config.pixel_format  = ps_format;
    ps_buffer_config.swap_byte     = 0;
    ps_buffer_config.buffer_addr   = (uint32_t)ps_addr;
    ps_buffer_config.buffer_addr_u = 0;
    ps_buffer_config.buffer_addr_v = 0;
    ps_buffer_config.pitch_bytes   = ps_w * ps_pixsize;

    /* ����PS buffer */
    pxp_set_process_surface_buffer_config(&ps_buffer_config);

    pxp_set_process_surface_position(0,
                                     0,
                                     src->h - 1,
                                     src->w - 1);
    /* ���ñ�����ɫ */
    pxp_set_process_surface_back_ground_color(0x0);

    /* ����AS */
    pxp_set_alpha_surface_position(0xFFFF, 0xFFFF, 0, 0);

    /* Output config. */
    pxp_output_config.pixel_format = out_format;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = (uint32_t) p_out_buf;
    pxp_output_config.buffer1_addr = 0;
    pxp_output_config.pitch_bytes = src->h * out_pixsize;
    pxp_output_config.width  = src->h;
    pxp_output_config.height = src->w;

    pxp_set_output_buffer_config(&pxp_output_config);

    /* Disable CSC1, it is enabled by default. */
    pxp_enable_csc1(0);

    /* ��ת270��(��ת��������ʵ�ֵ���ת90�ȵĽ����һ��) */
    pxp_set_rotate_config(kPXP_RotateProcessSurface, kPXP_Rotate270, kPXP_FlipDisable);

    /* ��ʼ��ת */
    pxp_start();

    /* Wait for process complete. */
    pxp_complete_status_sync();

    aw_cache_invalidate((void *)p_out_buf, src->w * src->h * out_pixsize);
    aw_cache_invalidate((void *)p_src_data, img->w * img->h * ps_pixsize);

    /* ���ˣ�����img��ͼ����ת�������p_out_buf */
    if ((uint32_t)p_out_buf == (uint32_t)fb->data) {
        goto clean_up;
    }

    /* ����������е����ݿ�����fb */
    start = fb->h - src->x - src->w;
    for (i = 0; i < src->w; i++) {
        memcpy((void *)(fb->data + ((start + i) * fb->w + src->y) * out_pixsize),
                p_out_buf + i * src->h  * out_pixsize,
                src->h * out_pixsize);
    }

clean_up:
    if (((uint32_t)img->data) != ((uint32_t)p_src_data)) {
        aw_mem_free(p_src_data);
    }

    return RET_OK;
}



/* end of file */
