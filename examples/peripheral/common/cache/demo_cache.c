/*******************************************************************************
*                                  AWorks
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
 * \brief cache����
 *
 * - �������裺
 *   1. ����������aw_prj_params.hͷ�ļ���ʹ��
 *      - ��Ӧƽ̨�Ĵ��ں�
 *      - AW_COM_CONSOLE
 *   2. �������е�DURX��DUTXͨ��USBת���ں�PC���ӣ����ڵ����������ã�
 *      ������Ϊ115200��8λ���ݳ��ȣ�1��ֹͣλ��������
 *
 * - ʵ������
 *   1. ���ڴ�ӡ������Ϣ��
 *
 * - ��ע��
 *   2. ��������ڳ�ʼ��ʱ������鿴��demo��ʹ��GPIO�Ƿ�������Ÿ��á�
 *
 * \par Դ����
 * \snippet demo_cache.c src_cache
 */

/**
 * \addtogroup demo_if_cache
 * \copydoc demo_cache.c
 */

/** [src_cache] */

#include "aworks.h"
#include "aw_cache.h"
#include "aw_vdebug.h"
#include <string.h>

/**
 * \brief cache demo
 * \return ��
 */
void demo_cache_entry (void)
{
    char *p_mem = NULL;

    /* ����500�ֽڴ�С�� cache-safe �Ļ�����  */
    p_mem = (char *)aw_cache_dma_malloc(500);
    if(p_mem == NULL){
        aw_kprintf("p_mem is NULL");
        return ;
    }

    memset(p_mem, '\0', 500);
    memcpy(p_mem, "test cache",sizeof("test cache"));
    AW_INFOF(("p_mem data : %s \n", p_mem));

    /* �ͷ� cache-safe �Ļ����� */
    aw_cache_dma_free(p_mem);

    /* ����ָ�����볤�ȵ� cache-safe �Ļ����� */
    p_mem = aw_cache_dma_align(1000, 16);

    memset(p_mem, '\0', 1000);
    memcpy(p_mem, "test cache", sizeof("test cache"));
    AW_INFOF(("p_mem data : %s \n", p_mem));

    /* �ͷ� cache-safe �Ļ����� */
    aw_cache_dma_free(p_mem);

    int  i = 0;
    uint8_t   buf[128] = {0};

    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = (uint8_t)i;
    }

    /* ��д���� */
    aw_cache_flush(buf, sizeof(buf));

    /* ��bufͨ��DMA�����ȥ */
    // todo

    memset(buf, 0, sizeof(buf));
    aw_cache_flush(buf, sizeof(buf));
    /* ͨ��DMA��ȡ������ buf */
    // todo

    aw_cache_invalidate(buf, sizeof(buf));

    /* ����ʹ��buf */
    // todo

    return ;
}

/** [src_cache] */

/* end of file */
