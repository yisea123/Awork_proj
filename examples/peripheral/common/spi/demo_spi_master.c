/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/
/**
 * \file
 * \brief SPI������ʾ���̣�����SPI�Ļ�����д����
 *
 * - ��������:
 *   1. ������ SPI �� MOSI ���ź� MISO �����öŰ��ߺʹԻ��豸��MOSI��MISO������
 *   2. ����aw_prj_params.h��ʹ��
 *      - ��Ӧƽ̨��SPI�ꣻ
 *      - �����豸��
 *
 * - ʵ������:
 *   1. ����ͨ��MISO�������ݣ����������ݴ�MOSI���أ�
 *   2. �ȽϷ����Ͷ��ص����ݣ������ͬLED0һֱ����,������200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_spi_master.c src_spi_master
 *
 * \internal
 * \par History
 * - 1.00 18-06-28  lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_spi_master
 * \copydoc demo_spi_master.c
 */

/** [src_spi_master] */
#include "aworks.h"                     /* ��ͷ�ļ����뱻���Ȱ��� */
#include "aw_delay.h"                   /* ��ʱ���� */
#include "aw_led.h"                     /* LED���� */
#include "aw_spi.h"
#include "aw_vdebug.h"

/** \brief SPI1������  */
#define SPI_DEV_BUSID        0                      /**< \brief SPI1���� */
#define SPI_DEV_MODE         AW_SPI_MODE_0          /**< \brief SPIģʽ0 */
#define SPI_DEV_SPEED        2000000                /**< \brief SPI�ٶ�  */
#define SPI_DEV_BPW          8                      /**< \brief SPI����λ����ȡֵֻ����8��16��32 */
#define SPI_TEST_LEN         256
#define SPI_CS_PIN           28                     /**< \brief ���ݾ���ƽ̨�޸�*/

aw_local aw_err_t __spi_trans (struct aw_spi_device *p_dev,
                               const uint8_t        *p_txbuf,
                               uint8_t              *p_rxbuf,
                               size_t                cnt,
                               uint32_t              spi_speed)
{
    struct aw_spi_message   spi_msg;
    struct aw_spi_transfer  spi_trans;

    /* ��ʼ����Ϣ, ���ûص������������(��Ϣ������Ϻ����) */
    aw_spi_msg_init(&spi_msg, NULL, NULL);

    /* ���䣺���� p_txbuf �е� cnt ������  �����ӴԻ��豸��ȡ cnt ������*/
    aw_spi_mktrans(&spi_trans, p_txbuf, p_rxbuf, cnt, 0, 0, 0, spi_speed, 0);

    /* ��������������ӵ���Ϣ�� */
    aw_spi_trans_add_tail(&spi_msg, &spi_trans);

    /* ����������������Ϣ(ͬ���ķ�ʽ����Ϣ������ϲŻ᷵��) */
    return aw_spi_sync(p_dev, &spi_msg);
}

/*
 * \brief
 *        ������Ҫע�⣺��AW_DEV_SPI_FLASH1��ע�͵�
 */

/*
 * \brief ���� SPI Flash, Flash���ͺ��ǣ�W25Q64(MicroPort-FlashС��)
 */
void demo_spi_master_entry (void)
{
    aw_kprintf("demo_spi_master test...\n");

    aw_spi_device_t     spi_dev;
    int                 ret;
    int                 i;
    uint8_t             read_buf[SPI_TEST_LEN];
    uint8_t             write_buf[SPI_TEST_LEN];
    int cs_pin = SPI_CS_PIN;

    /* ����SPI֮ǰ��������CS���� */
    aw_gpio_pin_request("spi_demo_cs", &cs_pin, 1);

    /* ���� SPI FLASH �豸 */
    aw_spi_mkdev(&spi_dev,
                  SPI_DEV_BUSID,   // λ������SPI������
                  SPI_DEV_BPW,     // �ִ�С
                  SPI_DEV_MODE,    // SPI ģʽ
                  SPI_DEV_SPEED,   // ֧�ֵ�����ٶ�
                  SPI_CS_PIN,      // Ƭѡ����
                  NULL);           // ���Զ����Ƭѡ���ƺ���

    if(aw_spi_setup(&spi_dev) != AW_OK){
        aw_kprintf("aw_spi_setup fail!\r\n");
        return ;
    }

    while(1){
        /* �����շ������� */
        for (i = 0;i < SPI_TEST_LEN; i++) {
            write_buf[i] = rand();
        }

        /*���read_buf*/
        memset(read_buf,0,sizeof(read_buf));

        /*��������*/
        ret = __spi_trans(&spi_dev,
                          write_buf,
                          read_buf,
                          SPI_TEST_LEN,
                          SPI_DEV_SPEED);

        if(ret != AW_OK){
            aw_kprintf("__spi_trans fail!\r\n");
            goto _exit ;
        }

        aw_kprintf("read_buf dada:%s\r\n",read_buf);

        aw_mdelay(500);
    }

_exit:
    /* ������ɺ��ͷ�CS���� */
    aw_gpio_pin_release(&cs_pin, 1);

    return ;
}
/** [src_spi_master] */

/*end of file */
