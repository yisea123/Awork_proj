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
 * \brief SPI主机演示例程，测试SPI的基本读写功能
 *
 * - 操作步骤:
 *   1. 将主机 SPI 的 MOSI 引脚和 MISO 引脚用杜邦线和丛机设备的MOSI、MISO相连；
 *   2. 需在aw_prj_params.h中使能
 *      - 相应平台的SPI宏；
 *      - 串口设备宏
 *
 * - 实验现象:
 *   1. 主机通过MISO发送数据，发出的数据从MOSI读回；
 *   2. 比较发出和读回的数据，如果相同LED0一直常亮,否则以200ms时间间隔闪烁；
 *
 * \par 源代码
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
#include "aworks.h"                     /* 此头文件必须被首先包含 */
#include "aw_delay.h"                   /* 延时服务 */
#include "aw_led.h"                     /* LED服务 */
#include "aw_spi.h"
#include "aw_vdebug.h"

/** \brief SPI1的配置  */
#define SPI_DEV_BUSID        0                      /**< \brief SPI1总线 */
#define SPI_DEV_MODE         AW_SPI_MODE_0          /**< \brief SPI模式0 */
#define SPI_DEV_SPEED        2000000                /**< \brief SPI速度  */
#define SPI_DEV_BPW          8                      /**< \brief SPI数据位数，取值只能是8、16、32 */
#define SPI_TEST_LEN         256
#define SPI_CS_PIN           28                     /**< \brief 根据具体平台修改*/

aw_local aw_err_t __spi_trans (struct aw_spi_device *p_dev,
                               const uint8_t        *p_txbuf,
                               uint8_t              *p_rxbuf,
                               size_t                cnt,
                               uint32_t              spi_speed)
{
    struct aw_spi_message   spi_msg;
    struct aw_spi_transfer  spi_trans;

    /* 初始化消息, 设置回调函数及其参数(消息处理完毕后调用) */
    aw_spi_msg_init(&spi_msg, NULL, NULL);

    /* 传输：发送 p_txbuf 中的 cnt 个数据  ，并从丛机设备读取 cnt 个数据*/
    aw_spi_mktrans(&spi_trans, p_txbuf, p_rxbuf, cnt, 0, 0, 0, spi_speed, 0);

    /* 将这两个传输添加到消息中 */
    aw_spi_trans_add_tail(&spi_msg, &spi_trans);

    /* 请求控制器处理此消息(同步的方式，消息处理完毕才会返回) */
    return aw_spi_sync(p_dev, &spi_msg);
}

/*
 * \brief
 *        另外需要注意：将AW_DEV_SPI_FLASH1宏注释掉
 */

/*
 * \brief 测试 SPI Flash, Flash的型号是：W25Q64(MicroPort-Flash小板)
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

    /* 配置SPI之前需先申请CS引脚 */
    aw_gpio_pin_request("spi_demo_cs", &cs_pin, 1);

    /* 生成 SPI FLASH 设备 */
    aw_spi_mkdev(&spi_dev,
                  SPI_DEV_BUSID,   // 位于哪条SPI总线上
                  SPI_DEV_BPW,     // 字大小
                  SPI_DEV_MODE,    // SPI 模式
                  SPI_DEV_SPEED,   // 支持的最大速度
                  SPI_CS_PIN,      // 片选引脚
                  NULL);           // 无自定义的片选控制函数

    if(aw_spi_setup(&spi_dev) != AW_OK){
        aw_kprintf("aw_spi_setup fail!\r\n");
        return ;
    }

    while(1){
        /* 设置收发送数据 */
        for (i = 0;i < SPI_TEST_LEN; i++) {
            write_buf[i] = rand();
        }

        /*清空read_buf*/
        memset(read_buf,0,sizeof(read_buf));

        /*传输数据*/
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
    /* 测试完成后释放CS引脚 */
    aw_gpio_pin_release(&cs_pin, 1);

    return ;
}
/** [src_spi_master] */

/*end of file */
