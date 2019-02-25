/*******************************************************************************
*                                 AWorks
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief Flexspi NOR Flashͨ�ýӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ�
 * \code
 * #include aw_flexspi_nor_flash.h
 * \endcode
 *
 * \par ��ʾ��
 * \code
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 18-01-31 mex, first implementation
 * \endinternal
 */

#ifndef __AWBL_FLEXSPI_NOR_FLASH_H
#define __AWBL_FLEXSPI_NOR_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "aworks.h"


/**
 * \brief Flexspi NOR Flash��ָ����ַ������
 *
 * \param[in] addr  ��ַ
 * \param[in] p_buf ���ݶ�����
 * \param[in] bytes ��Ҫ��ȡ�������ֽ���
 *
 * \retval   AW_OK      ��ȡ�ɹ�
 * \retval   AW_ERROR   ��ȡʧ��
 */
aw_err_t  awbl_flexspi_nor_flash_read (uint32_t   addr,
                                       uint8_t   *p_buf,
                                       uint32_t   bytes);

/**
 * \brief Flexspi NOR Flash��״̬�Ĵ���
 *
 * \param[in] p_buf  ���ݶ�����
 * \param[in] bytes  ��Ҫ��ȡ�������ֽ���
 *
 * \retval   AW_OK      ��ȡ�ɹ�
 * \retval   AW_ERROR   ��ȡʧ��
 */
aw_err_t  awbl_flexspi_nor_flash_read_status(uint8_t   *p_buf,
                                             uint32_t   bytes);

/**
 * \brief Flexspi NOR Flashдʹ��
 *
 * \param[in] addr  д���ݵĵ�ַ
 *
 * \retval   AW_OK     �����ɹ�
 * \retval   AW_ERROR  ����ʧ��
 */
aw_err_t  awbl_flexspi_nor_flash_write_enable(uint32_t  addr);


/**
 * \brief Flexspi NOR Flash����һ������
 *
 * \param[in] addr  �������ڵĵ�ַ
 *
 * \retval   AW_OK     �����ɹ�
 * \retval   AW_ERROR  ����ʧ��
 */
aw_err_t awbl_flexspi_nor_flash_erase (uint32_t  addr);


/**
 * \brief Flexspi NOR Flash���
 *
 * \param[in] addr   ����д�����ʼ��ַ
 * \param[in] p_buf  ��д�������
 * \param[in] bytes  ��д��������ֽ���
 *
 * \retval   AW_OK     �����ɹ�
 * \retval   AW_ERROR  ����ʧ��
 */
aw_err_t awbl_flexspi_nor_flash_program (uint32_t   addr,
                                         uint8_t   *p_buf,
                                         uint32_t   bytes);

#ifdef __cplusplus
}
#endif

#endif  /* __AWBL_FLEXSPI_NOR_FLASH_H */

/* end of file */
