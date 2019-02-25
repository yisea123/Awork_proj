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
 * \brief GPRS���̣���������ʾGPRS�豸����socketͨ�Ź���
 *
 * - ��������:
 *   1. aw_prj_params.h ��ʹ�ܣ�
 *      - ��Ӧƽ̨��USBH��
 *      - ����Ӧƽ̨���ں�
 *      - AW_COM_CONSOLE
 *      - ��Ӧ��GPRS�豸��(���磺AW_DEV_GPRS_ME909S)
 *   2. ��GPRSģ����뿪�����USB HOST0�ӿڣ�
 *   3. �ڵ����ϴ� TCP&UDP ���������������������������
 *
 * - ʵ������:
 *   1. ���ڴ�ӡ�� GPRS�豸��������ĵ�����Ϣ���Լ�����˷��͵�������Ϣ��
 *   2. TCP&UDP ��������յ�GPRS�豸���͵����ݣ�
 *      ���ڴ�ӡTCP&UDP��λ�����͵����ݡ�
 *
 * - ��ע:
 *   1.ƽ̨֧�ֵ�GPRS�豸Ŀǰ��sim800,me909,u9300,��Ӧ�豸��������鿴��Ӧ�ĳ�ʼ���ļ�awbl_hwconf_gprs_xxxxx.h��
 * \code
 *
 * \endcode
 *
 * \par Դ����
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

/* gprs�豸id��ţ��û�����ݾ���gprs�豸���� awbl_hwconf_gprs_xxxxx.h�����ļ��в���id�� */
#define TEST_GPRS_DEV                   1

/* ʹ��TCPЭ���������� */
#define TEST_GPRS_MODE                  "TCP"

/*���ʵķ�����IP���û�����ݾ�������޸�*/
#define TEST_SERVER_IP                  "121.33.243.38"

/*���ʵķ������˿ڣ��û�����ݾ�������޸�*/
#define TEST_SEEVER_PORT                51237

static void __config_gprs(void){
    aw_err_t ret;
    struct in_addr ip_addr;

    // ����ppp����
    ret = aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPP_OPEN, (void *)NULL);
    while (ret != AW_OK) {
        aw_mdelay(500);
    }

    // PPP���ŵ�IP��ַ��ȡ
    ret = aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPPIF_IP_GET, (void *)&ip_addr);
    if (ret == AW_OK) {
        AW_INFOF(("IP: %s\r\n\r\n", inet_ntoa(ip_addr)));
    }

    return ;
}
/**
 * \brief net ʾ���������
 * \return ��
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
     * /brief gprs�豸�ϵ粢��ʼ��
     * id 0 - u9300c �豸
     * id 1 - sim800 �豸
     * id 2 - me909 �豸
     * ����id������ awbl_hwconf_gprs_xxxxx.h�����ļ��в���
     * note �û�����ݾ���gprs�豸��ʹ�ö�Ӧ��ID
     */
    ret = aw_gprs_power_on(TEST_GPRS_DEV);
    if (ret != AW_OK){
        aw_kprintf("aw_gprs_power_on error:%d\r\n",ret);
        return ;
    }

    /*����gprs*/
    __config_gprs();

    /*����socketͨ��*/
    hd = socket(AF_INET, SOCK_STREAM, 0);
    if(hd < 0){
        AW_INFOF(("TCP server socket failed!" ENDL));
        goto __exit;
    }

    /*���ý��ճ�ʱʱ��*/
    ret = setsockopt(hd, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout, sizeof(rcv_timeout));
    if(ret != AW_OK){
        aw_kprintf("setsockopt fail\r\n");
        goto __exit;
    }

    /*��ʼ��server�ṹ��*/
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port   = htons(TEST_SEEVER_PORT);
    ret = inet_aton(TEST_SERVER_IP, &(server.sin_addr));
    if (ret == 0) {
        aw_kprintf("inet_aton error!\r\n");
        goto __exit;
    }

    AW_INFOF(("TCP client: connecting..." ENDL));

    /* ���ӷ�����  */
    if (connect(hd, (struct sockaddr *) &server, sizeof(server)) == 0) {
        AW_INFOF(("TCP client: connected." ENDL));
        for (;;) {
            memset(net_buf,'\0',1500);/*��ջ�����*/
            send(hd, "hello,i'm gprs tcp client.\r\n", 28, 0); /* ��������������� */
            recv(hd, net_buf, sizeof(net_buf), 0);/* ���շ��������͵����� */
            aw_kprintf("recv:%s\r\n",net_buf);/*��ӡ����*/
            aw_mdelay(500);
        }
    }

__exit:
    closesocket(hd); /* �ر�socket���� */
    aw_gprs_ioctl(TEST_GPRS_DEV, AW_GPRS_REQ_PPP_CLOSE, (void *)NULL);/* �ر�ppp���� */
    aw_gprs_power_off(TEST_GPRS_DEV);/* �ر�gprs�豸 */

    return ;
}

/** [src_gprs_socket] */

/* end of file */
