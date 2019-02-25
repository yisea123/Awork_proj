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
 * \brief GPRS例程，该例程演示GPRS设备建立socket通信功能
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
 * \snippet demo_gprs_socket.c src_gprs_socket
 *
 * \internal
 * \par modification history:
 * - 1.00 18-07-12 lqy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_gprs_socket
 * \copydoc demo_gprs_socket.c
 */

/** [src_gprs_socket] */

#include "aworks.h"
#include "aw_vdebug.h"
#include "aw_gprs.h"
#include <string.h>
#include "net/aw_net.h"
#include "net/aw_sockets.h"
#include <string.h>

/* gprs设备id编号，用户请根据具体gprs设备，在 awbl_hwconf_gprs_xxxxx.h配置文件中查找id号 */
#define TEST_GPRS_DEV                   1

/* 使用TCP协议连接网络 */
#define TEST_GPRS_MODE                  "TCP"

/*访问的服务器IP，用户需根据具体情况修改*/
#define TEST_SERVER_IP                  "121.33.243.38"

/*访问的服务器端口，用户需根据具体情况修改*/
#define TEST_SEEVER_PORT                51237

static void __config_gprs(void){
    aw_err_t ret;
    struct in_addr ip_addr;

    // 启动ppp连接
    ret = aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPP_OPEN, (void *)NULL);
    while (ret != AW_OK) {
        aw_mdelay(500);
    }

    // PPP拨号的IP地址获取
    ret = aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPPIF_IP_GET, (void *)&ip_addr);
    if (ret == AW_OK) {
        AW_INFOF(("IP: %s\r\n\r\n", inet_ntoa(ip_addr)));
    }

    return ;
}
/**
 * \brief net 示例程序入口
 * \return 无
 */
void demo_gprs_socket_entry (void)
{
    aw_err_t ret;
    struct sockaddr_in  server;
    struct sockaddr_in  client;
    int hd;
    static uint16_t src_port = 50000;
     int rcv_timeout = 100;
    char net_buf[1500];

    /**
     * /brief gprs设备上电并初始化
     * id 0 - u9300c 设备
     * id 1 - sim800 设备
     * id 2 - me909 设备
     * 具体id定义在 awbl_hwconf_gprs_xxxxx.h配置文件中查找
     * note 用户请根据具体gprs设备，使用对应的ID
     */
    ret = aw_gprs_power_on(TEST_GPRS_DEV);
    if (ret != AW_OK){
        aw_kprintf("aw_gprs_power_on error:%d\r\n",ret);
        return ;
    }

    /*配置gprs*/
    __config_gprs();

    /*建立socket通信*/
    hd = socket(AF_INET, SOCK_STREAM, 0);
    if(hd < 0){
        AW_INFOF(("TCP server socket failed!" ENDL));
        goto __exit;
    }

    /*设置接收超时时间*/
    ret = setsockopt(hd, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout, sizeof(rcv_timeout));
    if(ret != AW_OK){
        aw_kprintf("setsockopt fail\r\n");
        goto __exit;
    }

    /*初始化server结构体*/
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port   = htons(TEST_SEEVER_PORT);
    ret = inet_aton(TEST_SERVER_IP, &(server.sin_addr));
    if (ret == 0) {
        aw_kprintf("inet_aton error!\r\n");
        goto __exit;
    }

    AW_INFOF(("TCP client: connecting..." ENDL));

    /* 连接服务器  */
    if (connect(hd, (struct sockaddr *) &server, sizeof(server)) == 0) {
        AW_INFOF(("TCP client: connected." ENDL));
        for (;;) {
            memset(net_buf,'\0',1500);/*清空缓存区*/
            send(hd, "hello,i'm gprs tcp client.\r\n", 28, 0); /* 向服务器发送数据 */
            recv(hd, net_buf, sizeof(net_buf), 0);/* 接收服务器发送的数据 */
            aw_kprintf("recv:%s\r\n",net_buf);/*打印数据*/
            aw_mdelay(500);
        }
    }

__exit:
    closesocket(hd); /* 关闭socket连接 */
    aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPP_CLOSE, (void *)NULL);/* 关闭ppp连接 */
    aw_gprs_power_off(TEST_GPRS_DEV);/* 关闭gprs设备 */

    return ;
}

/** [src_gprs_socket] */

/* end of file */
