#ifndef __MJPEG_H
#define __MJPEG_H 
#include "stdio.h" 
#include "stdint.h"
#include <cdjpeg.h> 
#include <setjmp.h>


/**
 * \brief mjpeg�������ṹ��
 */
struct my_error_mgr {
  struct jpeg_error_mgr pub;
  jmp_buf setjmp_buffer;
};

typedef struct my_error_mgr * my_error_ptr;


/* mjpeg��Ϣ  */
typedef struct mjpeg_info {

    struct jpeg_decompress_struct *cinfo;
    struct my_error_mgr *jerr;

    uint8_t   *jmem_buf;          /**< \brief mjpeg����ʹ�õ��ڴ�� */
    uint32_t   jmempos;           /**< \brief mjpeg�����ڴ�ط������� */
    uint16_t   imgoffx;           /**< \brief ͼ����X���ϵ�ƫ�� */
    uint16_t   imgoffy;           /**< \brief ͼ����Y���ϵ�ƫ�� */
    uint32_t   jbufsize;          /**< \brief jpeg buf��С */
    uint8_t   *jpegbuf;           /**< \brief jpeg���ݻ���ָ�� */

} mjpeg_info_t;


extern mjpeg_info_t  mjpeg_info;


/**
 * \brief  mjpeg �����ʼ��
 *
 * \param[in] p_mjpeg  mjpeg���������Ϣ
 * \param[in] offx     ��Ƶ����Ļ�ϵ�X��ƫ��
 * \param[in] offy     ��Ƶ����Ļ�ϵ�y��ƫ��
 *
 * \retval     0       �ɹ�
 *            -1       ʧ��
 */
int  mjpegdec_init(mjpeg_info_t *p_mjpeg, uint16_t offx, uint16_t offy);


/**
 * \brief  �ͷ�mjpeg������ص��ڴ�
 *
 * \param[in] p_mjpeg  mjpeg���������Ϣ
 *
 * \return    ��
 */
void mjpegdec_free(mjpeg_info_t *p_mjpeg);


/**
 * \brief  ����һ��JPEGͼƬ
 *
 * \param[in] p_mjpeg  mjpeg���������Ϣ
 * \param[in] p_buf    ��Ƶ���������뻺��
 * \param[in] p_buf    ��Ƶ�����������
 * \param[in] bsize    ��Ƶ���������뻺���С
 *
 * \retval     0       �ɹ�
 *            -1       ʧ��
 */

int  mjpegdec_decode(mjpeg_info_t *p_mjpeg,
                     uint8_t      *p_buf,
                     uint8_t      *p_out,
                     uint32_t      bsize);

#endif

/* end of file */

