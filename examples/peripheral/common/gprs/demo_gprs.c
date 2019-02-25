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
 * \brief GPRS例程，该例程演示GPRS设备发送短信和联网通信的功能
 *
 * - 操作步骤:
 *   1. aw_prj_params.h 中使能：
 *      - 对应平台的USBH宏
 *      - 及对应平台串口宏
 *      - AW_COM_CONSOLE
 *      - 对应的GPRS设备宏(例如：AW_DEV_GPRS_ME909S)
 *   2. 将GPRS模块插入开发板的USB HOST0接口；
 *   3. 在电脑上打开 TCP&UDP 调试软件，建立并启动服务器。
 *
 * - 实验现象:
 *   1. 手机客户端会收到短信：Hello,i'm aworks。
 *   1. 串口打印： GPRS设备连接网络的调试信息；以及服务端发送的数据信息。
 *   2. TCP&UDP 调试软件收到GPRS设备发送的数据，
 *      串口打印TCP&UDP上位机发送的数据。
 *
 * - 备注:
 *   1.平台支持的GPRS设备目前有sim800,me909,u9300,对应设备的配置请查看相应的初始化文件awbl_hwconf_gprs_xxxxx.h。
 * \code
 *
 * \endcode
 *
 * \par 源代码
 * \snippet demo_gprs.c src_gprs
 *
 * \internal
 * \par modification history:
 * - 1.00 18-07-12 lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gprs
 * \copydoc demo_gprs.c
 */

/** [src_gprs] */

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_gprs.h"
#include <string.h>
#include "aw_delay.h"

/* gprs设备id编号，用户请根据具体gprs设备，在 awbl_hwconf_gprs_xxxxx.h配置文件中查找id号 */
#define TEST_GPRS_DEV                   2

/* 使用TCP协议连接网络 */
#define TEST_GPRS_MODE                  "TCP"

/*访问的服务器IP，用户需根据具体情况修改*/
#define TEST_SERVER_IP                  "121.33.243.38"

/*访问的服务器端口，用户需根据具体情况修改*/
#define TEST_SEEVER_PORT                51237

/*socket服务句柄，从0开始*/
#define TEST_SCOKET_HD                  0

/* 测试使用手机号，用户需修改, */
#define TEST_PHONE_NUM                  "+8618529453675"

/*
 * \brief GPRS 网络通信例程入口
 * \return 无
 */
void demo_gprs_entry(void)
{
    aw_err_t ret = AW_ERROR;
    uint8_t p_buf[1000];

    /**
     * /brief gprs设备上电并初始化
     * id 0 - u9300c 设备
     * id 1 - sim800 设备
     * id 2 - me909 设备
     * 具体id定义在 awbl_hwconf_gprs_xxxxx.h配置文件中查找
     * note 用户请根据具体gprs设备，使用对应的ID
     */
    ret = aw_gprs_power_on(TEST_GPRS_DEV);
    if(ret != AW_OK){
        aw_kprintf("aw_gprs_power_on error:%d\r\n",ret);
        return ;
    }

    /*发送短信*/
    ret = aw_gprs_sms_send(TEST_GPRS_DEV,"Hello,i'm aworks!",17,TEST_PHONE_NUM);
    if(ret != AW_OK){
        aw_kprintf("aw_gprs_sms_send error:%d\r\n",ret);
        goto exit;
    }

    /* 建立GPRS连接 */
    ret = aw_gprs_start(TEST_GPRS_DEV,TEST_GPRS_MODE,TEST_SERVER_IP,TEST_SEEVER_PORT,3000);
    if(ret < AW_OK){
        aw_kprintf("aw_gprs_start error:%d\r\n",ret);
        goto exit;
    }

    while(1){
        /*清空缓冲区*/
        memset(p_buf,'\0',sizeof(p_buf));
        /*接收服务器端发送的数据，非阻塞*/
        ret = aw_gprs_recv(TEST_GPRS_DEV,TEST_SCOKET_HD,p_buf,sizeof(p_buf));
        if(ret > 0){
            aw_kprintf("recv:%s\r\n",p_buf);
        }

        /*向服务器端发送数据*/
        aw_gprs_send(TEST_GPRS_DEV,TEST_SCOKET_HD,"Hello i'm aworks!\r\n",19,100);
        aw_mdelay(1000);
    }

exit:
    /*关闭gprs连接*/
    aw_gprs_close(TEST_GPRS_DEV,TEST_SCOKET_HD);
    /*关闭gprs设备*/
    aw_gprs_power_off(TEST_GPRS_DEV);

    return ;
}

/** [src_gprs] */

/* end of file */
