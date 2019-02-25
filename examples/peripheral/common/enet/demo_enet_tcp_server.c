/*******************************************************************************
 *                                  AWorks
 *                       ----------------------------
 *                       innovating embedded platform
 *
 * Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
 * All rights reserved.
 *
 * Contact information:
 * web site:    http://www.zlg.cn
 * e-mail:      support@zlg.cn
 *******************************************************************************/

/**
 * \file
 * \brief TCP �������ʾ����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�������ꣻ
 *   2. �����߽����Ӻ͵�������������
 *   3. �û���򿪵��Ե����繲�����Ĳ鿴���ĵ���ʹ�õ��Ǿ�̬IP��ַ���Ƕ�̬IP��ַ��
 *      ������ö�̬��ʽ���� �� IP_OPEN_DHCPS �궨�壬�������˲��裻
 *      ������þ�̬��ʽ����ͨ����������һ�ַ�ʽ����֤�����������ͬһ�����Σ�
 *      (1) �޸ĵ��Ե�ip��ַ�����ص�ַ����֤�Ϳ�����ͬһ���Σ�
 *      (2) �޸� LOCAL_IP_ADDR0 ��LOCAL_GATAWAY_ADDR0 �궨�屣֤������͵�����ͬһ������
 *   4. �򿪵��Զ�TCP&UDP���Թ��ߣ�����TCP���͵Ŀͻ��ˣ�Ŀ��IP��д����������0 ip��ַ��Ŀ��˿���4000��
 *   5. ������Զ˺Ϳ����彨������ʧ�ܣ����ڴ��ڴ�ӡ����ִ��shell���
 *      - "ip addr"�� �鿴����������0 ip��ַ�Ƿ����óɹ���
 *      - "ping ����ip��ַ"���鿴���ԺͿ������໥֮���������ӳɹ���
 *      �򿪵���cmd����ִ��"ping ������ip��ַ",�鿴���ԺͿ������໥֮���������ӳɹ���
 *      ������ϲ���ȫ��ִ�гɹ�����ɽ������ӣ�������鿴�޸�ʧ��ԭ��
 *
 * - ʵ������
 *   1. TCP&UDP���Թ������ӳɹ��󣬷������ݣ����ڴ�ӡ�����յ������ݣ�������λ��������յ�������ط�����Ϣ��
 *
 * \par Դ����
 * \snippet demo_enet_tcp_server.c src_enet_tcp_server
 *
 * \internal
 * \par Modification History
 * - 1.00 18-06-27  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_enet_tcp_server
 * \copydoc demo_enet_tcp_server.c
 */

/** [src_enet_tcp_server] */
#include "apollo.h"
#include "lwip/sockets.h"
#include "lwip/netif.h"
#include "aw_vdebug.h"
#include <string.h>
#include "net/aw_netif.h"
#include "aw_delay.h"
#include "net/dhcp_server.h"

/** /note
 * �û���򿪵��Ե����繲�����Ĳ鿴���ĵ���ʹ�õ��Ǿ�̬IP��ַ���Ƕ�̬IP��ַ��
 * ������ĵ���ʹ�õ��Ǿ�̬IP��ַ�뿪���˺꣬�����彫ʹ�þ�̬��ʽ��������0 IP��ַ
 * ������ĵ���ʹ�õ��Ƕ�̬IP��ַ�����δ˺꣬�����彫ʹ�ö�̬��ʽ�������0 IP��ַ
 */
//#define IP_OPEN_DHCPS

#define LOCAL_IP_ADDR0                 "192.168.11.200"  /* ������ ����0 IP ��ַ���û��豣֤������͵��Ե�IP��ַ��ͬһ����   */
#define LOCAL_NET_MASK0                "255.255.255.0"   /* ������ ����0 ��������   */
#define LOCAL_GATAWAY_ADDR0            "192.168.11.254"  /* ������ ����0 ���ص�ַ ���û��豣֤������͵��Ե����ص�ַ��ͬһ���� */

#define LOCAL_NIC0_NAME                "eth0"            /* ����������0 ����(������������0�������ļ��ж���) */
#define LOCAL_PORT                     4000              /* ���Ӷ˿�         */


aw_local struct dhcp_server *__eth0_dhcp_server (void)
{
    aw_local struct dhcp_server dhcp_server;
    return &dhcp_server;
}


static aw_err_t __config_eth0_ip(void){
    struct in_addr addr;
    aw_netif_t * p_netif;
    aw_err_t ret;


    /*������0�豸*/
    p_netif = aw_netif_dev_open (LOCAL_NIC0_NAME);
    if(p_netif == NULL){
        aw_kprintf("aw_netif_dev_open fail\r\n");
        return AW_ERROR;
    }

    /* ��������0 IP ��ַ  */
    inet_aton(LOCAL_IP_ADDR0, &addr);
    ret = aw_netif_ipv4_ip_set(p_netif,&addr);
    if(ret != AW_OK){
        aw_kprintf("aw_netif_ipv4_ip_set fail,error code:%d\r\n",ret);
        return ret;
    }

    /* ��������0 ��������  */
    inet_aton(LOCAL_NET_MASK0, &addr);
    ret = aw_netif_ipv4_netmask_set(p_netif,&addr);
    if(ret != AW_OK){
        aw_kprintf("aw_netif_ipv4_netmask_set fail,error code:%d\r\n",ret);
        return ret;
    }

    /* ��������0 ����  */
    inet_aton(LOCAL_GATAWAY_ADDR0, &addr);
    aw_netif_ipv4_gw_set(p_netif,&addr);
    if(ret != AW_OK){
        aw_kprintf("aw_netif_ipv4_gw_set fail,error code:%d\r\n",ret);
        return ret;
    }

    dhcps_bind_netif(__eth0_dhcp_server(), LOCAL_NIC0_NAME);

#ifdef  IP_OPEN_DHCPS
    /* ���� DHCPS ����ˣ������彫��̬Ϊ�ͻ��˷���IP��ַ*/
    dhcps_start(__eth0_dhcp_server());
#else
    /* �ر� DHCPS ����ˣ��ͻ��������þ�̬IP��ַ */
    dhcps_stop(__eth0_dhcp_server());
#endif

    return AW_OK;
}

/**
 * \brief tcp ����˵���ں���
 */
void demo_enet_tcp_server_entry (void){

    int socfd, confd;
    char msg[32] = { 0 };
    struct sockaddr_in remote_addr;     /* Զ��(PC)��ַ */
    struct sockaddr_in local_addr;      /* ������ַ */
    socklen_t socklen = 0;
    int recv_size = 0;      /* ���յ����ַ����� */

    /* ���ÿ����������0 IP��ַ*/
    if (__config_eth0_ip() != AW_OK){
        return ;
    }

    /* ����socket�׽��� */
    socfd = socket(AF_INET, SOCK_STREAM, 0);    /* TCPΪ��ʽ�׽��� */
    if (socfd == -1) {
        AW_INFOF(("fail to socket\r\n"));
        return;
    }

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(LOCAL_PORT);
    local_addr.sin_addr.s_addr = 0;

    /* ���׽��ֽӿںͶ˿ڰ� */
    if (-1 == bind(socfd, (struct sockaddr*)&local_addr, sizeof(local_addr))) {
        AW_INFOF(("fail to bind\r\n"));
    }

    /* �ȴ����� */
    if (-1 == listen(socfd, 1)) {
        AW_INFOF(("fail to listen\r\n"));
        goto err1;
    }

    /* ��Ӧconnect���� */
    confd = accept(socfd, (struct sockaddr*)&remote_addr, &socklen);
    if (confd  < 0) {
        AW_INFOF(("fail to accept\r\n"));
        goto err2;
    }

    while (1) {
        recv_size = recv(confd, msg, sizeof(msg), 0);
        /* ��������Զ�˵����� */
        if (recv_size > 0) {

            AW_INFOF(("msg:%s\r\n", msg));

            /* �����ݷ��ͻ�ȥ */
            send(confd, msg, strlen(msg), 0);

            /*��ջ�����*/
            memset(msg, '\0', sizeof(msg));
        }
    }

err2:
    closesocket(confd);
err1:
    closesocket(socfd);
}
/** [src_enet_tcp_server] */

/* end of file */
