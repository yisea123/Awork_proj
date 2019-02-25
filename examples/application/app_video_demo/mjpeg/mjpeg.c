#include "mjpeg.h" 
#include "jpeglib.h"
#include "aw_emwin_fb.h"
#include "aw_mem.h"
#include "aw_common.h"
#include "aw_vdebug.h"


/** \brief mjpeg�ڴ�ش�С (38K�ֽ�) */
#define __MJPEG_MAX_MALLOC_SIZE   (38 * 1024)

/** \brief �����ⲿȫ�ֱ�����mjpeg���������Ϣ */
mjpeg_info_t  mjpeg_info;

/** \brief �ⲿȫ�ֱ�����fb�豸 */
aw_emwin_fb_info_t * __gp_mjpeg_fb;

/** \brief ����ȫ�ֱ�����lcd�Դ��ַ */
static uint8_t *gp_lcd_addr;

/** \brief ����ȫ�ֱ������Դ��л�������־ */
static uint8_t g_fram_cnt;


/**
 * \brief mjpeg�����ڴ�
 */
void *mjpeg_malloc(uint32_t num)
{
    uint32_t curpos = mjpeg_info.jmempos;   /* �˴η������ʼ��ַ */
    mjpeg_info.jmempos += num;              /* ��һ�η������ʼ��ַ */

    if (mjpeg_info.jmempos > __MJPEG_MAX_MALLOC_SIZE) {
        aw_kprintf("mem error:%d,%d", curpos, num);
    }

    /* �������뵽���ڴ��׵�ַ */
    return (void *)&mjpeg_info.jmem_buf[curpos];
}


/**
 * \brief �����˳�
 */
static void my_error_exit(j_common_ptr cinfo)
{ 
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
} 


METHODDEF(void) my_emit_message(j_common_ptr cinfo, int msg_level)
{
    my_error_ptr myerr = (my_error_ptr) cinfo->err;

    if (msg_level < 0) {
        printf("emit msg:%d\r\n", msg_level);
        longjmp(myerr->setjmp_buffer, 1);
    }
}


/**
 * \brief ʼ����Դ,��ִ���κβ���
 */
static void init_source(j_decompress_ptr cinfo)
{
    //����Ҫ���κ�����.
    return;
} 


/**
 * \brief ������뻺����,һ���Զ�ȡ��֡����
 */
static boolean fill_input_buffer(j_decompress_ptr p_cinfo)
{  

    if (mjpeg_info.jbufsize == 0) {   /* ������ */

        printf("jd read off \r\n");

        /* ����������� */
        mjpeg_info.jpegbuf[0] = (uint8_t) 0xFF;
        mjpeg_info.jpegbuf[1] = (uint8_t) JPEG_EOI;
        p_cinfo->src->next_input_byte = mjpeg_info.jpegbuf;
        p_cinfo->src->bytes_in_buffer = 2;
    } else {

        p_cinfo->src->next_input_byte = mjpeg_info.jpegbuf;
        p_cinfo->src->bytes_in_buffer = mjpeg_info.jbufsize;
        mjpeg_info.jbufsize -= mjpeg_info.jbufsize;
    }
    return TRUE;
}


/**
 * \brief ���ļ�����,����num_bytes������
 */
static void skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{ 
    /* Just a dumb implementation for now.  Could use fseek() except
    * it doesn't work on pipes.  Not clear that being smart is worth
    * any trouble anyway --- large skips are infrequent.
    */
    if (num_bytes > 0)
    {
        while(num_bytes>(long) cinfo->src->bytes_in_buffer)
        {
            num_bytes-=(long)cinfo->src->bytes_in_buffer;
            (void)cinfo->src->fill_input_buffer(cinfo);
            /* note we assume that fill_input_buffer will never
            * return FALSE, so suspension need not be handled.
            */
        }
        cinfo->src->next_input_byte += (size_t) num_bytes;
        cinfo->src->bytes_in_buffer -= (size_t) num_bytes;
    }
} 


/**
 * \brief �ڽ��������,��jpeg_finish_decompress��������
 */
static void term_source(j_decompress_ptr cinfo)
{
    //�����κδ���
    return;
}


/**
 * \brief ��ʼ��jpeg��������Դ
 */
static void jpeg_filerw_src_init(j_decompress_ptr cinfo)
{ 
    if (cinfo->src == NULL)     /* first time for this JPEG object? */
    {
        cinfo->src = (struct jpeg_source_mgr *)
                     (*cinfo->mem->alloc_small)((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                              sizeof(struct jpeg_source_mgr)); 
    } 
    cinfo->src->init_source = init_source;
    cinfo->src->fill_input_buffer = fill_input_buffer;
    cinfo->src->skip_input_data = skip_input_data;
    cinfo->src->resync_to_restart = jpeg_resync_to_restart; /* use default method */
    cinfo->src->term_source = term_source;
    cinfo->src->bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
    cinfo->src->next_input_byte = NULL; /* until buffer loaded */
} 

/**
 * \brief  mjpeg�����ʼ��
 */

uint8_t  mj_pool_buf[__MJPEG_MAX_MALLOC_SIZE];

struct my_error_mgr error_mgr;

struct jpeg_decompress_struct jpeg_decompress;



int mjpegdec_init(mjpeg_info_t *p_mjpeg, uint16_t offx, uint16_t offy)
{
#if 0
    p_mjpeg->cinfo = (struct jpeg_decompress_struct *) aw_mem_alloc(
                      sizeof(struct jpeg_decompress_struct));
    p_mjpeg->jerr = (struct my_error_mgr *) aw_mem_alloc(sizeof(struct my_error_mgr));
    p_mjpeg->jmem_buf = (uint8_t *)aw_mem_alloc(__MJPEG_MAX_MALLOC_SIZE);   /* MJPEG�����ڴ������ */
#else

    p_mjpeg->cinfo = &jpeg_decompress;

    p_mjpeg->jerr = &error_mgr;

    p_mjpeg->jmem_buf = mj_pool_buf;   /* MJPEG�����ڴ������ */

#endif
    if((p_mjpeg->cinfo == 0)    || (p_mjpeg->jerr == 0) ||
       (p_mjpeg->jmem_buf == 0)) {

        mjpegdec_free(p_mjpeg);
        return -1;
    }

    /* ����ͼ����x, y�����ƫ���� */
    p_mjpeg->imgoffx = offx;
    p_mjpeg->imgoffy = offy;

    return 0;
}

/**
 * \brief  mjpeg����,�ͷ��ڴ�
 */
void mjpegdec_free(mjpeg_info_t *p_mjpeg)
{    
#if 0
    aw_mem_free(p_mjpeg->cinfo);
    aw_mem_free(p_mjpeg->jerr);
    aw_mem_free(p_mjpeg->jmem_buf);
#endif
}


/**
 * \brief ����һ��JPEGͼƬ
 */
int  mjpegdec_decode(mjpeg_info_t *p_mjpeg,
                     uint8_t      *p_buf,
                     uint8_t      *p_out,
                     uint32_t      bsize)
{
    JSAMPARRAY buffer[2];

    if ((bsize == 0) || (p_buf == NULL)) {
        return -1;
    }

    p_mjpeg->jpegbuf  = p_buf;
    p_mjpeg->jbufsize = bsize;
    p_mjpeg->jmempos  = 0;       /* MJEPG����,���´�0��ʼ�����ڴ� */
    p_mjpeg->cinfo->err=jpeg_std_error(&p_mjpeg->jerr->pub);
    p_mjpeg->jerr->pub.error_exit = my_error_exit;
    p_mjpeg->jerr->pub.emit_message = my_emit_message;

    if (setjmp(p_mjpeg->jerr->setjmp_buffer))  {  /* ������ */

        jpeg_abort_decompress(p_mjpeg->cinfo);
        jpeg_destroy_decompress(p_mjpeg->cinfo);
        return -1;
    }
    jpeg_create_decompress(p_mjpeg->cinfo);
    jpeg_filerw_src_init(p_mjpeg->cinfo);
    jpeg_read_header(p_mjpeg->cinfo, TRUE);
    p_mjpeg->cinfo->dct_method = JDCT_IFAST;
    p_mjpeg->cinfo->do_fancy_upsampling = 0;
    p_mjpeg->cinfo->max_v_samp_factor = 2;

    jpeg_start_decompress(p_mjpeg->cinfo);

    while (p_mjpeg->cinfo->output_scanline < p_mjpeg->cinfo->output_height) {

        buffer[0] = p_out
                  + ((p_mjpeg->cinfo->output_scanline + p_mjpeg->imgoffy)
                  * p_mjpeg->cinfo->output_width  + p_mjpeg->imgoffx) * 2;



        buffer[1] = p_out
                  + ((p_mjpeg->cinfo->output_scanline + 1 + p_mjpeg->imgoffy)
                  * p_mjpeg->cinfo->output_width  + p_mjpeg->imgoffx) * 2;

        /* �������е����� */
        jpeg_read_scanlines(p_mjpeg->cinfo, buffer, 2);
    }

    /* ������� */
    jpeg_finish_decompress(p_mjpeg->cinfo);

    /* �ͷ���Դ */
    jpeg_destroy_decompress(p_mjpeg->cinfo);
    return 0;
}



/* end of file */
