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
 * \brief TCP�ͻ�����ʾ����
 *
 * - �������裺
 *   1. ��Ҫ��aw_prj_params.hͷ�ļ���ʹ��
 *      - AW_COM_CONSOLE
 *      - ��Ӧƽ̨�������ꣻ
 *   2. �����߽����Ӻ͵�������������
 *   3. �û���򿪵��Ե����繲�����Ĳ鿴���ĵ���ʹ�õ��Ǿ�̬IP��ַ���Ƕ�̬IP��ַ��
 *      ������ö�̬��ʽ���� ��IP_OPEN_DHCPC �궨�壬�������˲��裻
 *      ������þ�̬��ʽ����ͨ����������һ�ַ�ʽ����֤�����������ͬһ�����Σ�
 *      (1) �޸ĵ��Ե�ip��ַ�����ص�ַ����֤�Ϳ�����ͬһ���Σ�
 *      (2) �޸� LOCAL_IP_ADDR0 ��LOCAL_GATAWAY_ADDR0 �궨�屣֤������͵�����ͬһ������
 *   4. �򿪵��Զ�TCP&UDP���Թ��ߣ���������������ָ��IP��ַΪ���Ե�IP��ַ���˿�Ϊ5000��Ȼ��������������
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
 * \snippet demo_enet_tcp_client.c src_enet_tcp_client
 *
 * \internal
 * \par Modification History
 * - 1.00 18-06-27  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_enet_tcp_client
 * \copydoc demo_enet_tcp_client.c
 */

/** [src_tcp] */
#include "apollo.h"
#include "lwip/sockets.h"
#include "lwip/netif.h"
#include "aw_vdebug.h"
#include <string.h>
#include "net/aw_netif.h"
#include "aw_delay.h"

/** /note
 * �û���򿪵��Ե����繲�����Ĳ鿴���ĵ���ʹ�õ��Ǿ�̬IP��ַ���Ƕ�̬IP��ַ��
 * ������ĵ���ʹ�õ��Ǿ�̬IP��ַ�뿪���˺꣬�����彫ʹ�þ�̬��ʽ��������0 IP��ַ
 * ������ĵ���ʹ�õ��Ƕ�̬IP��ַ�����δ˺꣬�����彫ʹ�ö�̬��ʽ�������0 IP��ַ
 */
//#define IP_OPEN_DHCPC

#ifndef IP_OPEN_DHCPC
#define LOCAL_IP_ADDR0                 "192.168.12.200"  /* ������ ����0 IP ��ַ���û��豣֤������͵��Ե�IP��ַ��ͬһ����   */
#define LOCAL_NET_MASK0                "255.255.255.0"   /* ������ ����0 ��������   */
#define LOCAL_GATAWAY_ADDR0            "192.168.12.254"  /* ������ ����0 ���ص�ַ ���û��豣֤������͵��Ե����ص�ַ��ͬһ���� */
#endif

#define REMOTE_IP_ADDR                 "192.168.12.34"    /* Զ�˷�����(����)IP��ַ���û�����ղ������裬���ݾ�������޸�*/
#define REMOT_PORT                     5000               /* Զ�˷������˿�  */

#define LOCAL_NIC0_NAME                "eth0"            /* ����������0 ����(������������0�������ļ��ж���) */
#define LOCAL_PORT                     4000              /* ���Ӷ˿�         */

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

#ifndef IP_OPEN_DHCPC

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

    /* �ر� DHCPC �ͻ��ˣ�����0ʹ�þ�̬IP��ַ */
    ret =  aw_netif_dhcpc_stop(p_netif);
    if(ret != AW_OK){
        aw_kprintf("awbl_nic_dhcpc_stop fail,error code:%d\r\n",ret);
    }
#else
    /* ����DHCPC �ͻ��� ����ʹ�ö�̬��ʽ���ÿ���������0��IP��ַ*/
    ret = aw_netif_dhcpc_start(p_netif);
    if(ret != AW_OK){
        aw_kprintf("aw_netif_dhcpc_start fail,error code:%d\r\n",ret);
        return ret;
    }
#endif

    return AW_OK;
}

/**
 * \brief tcp �ͻ��˵���ں���
 */
void demo_enet_tcp_client_entry (void){

    int socfd;
    char msg[32] = { 0 };
    struct sockaddr_in remote_addr;     /* Զ��(PC)��ַ */
    int recv_size = 0;      /* ���յ����ַ����� */

    /* ���ÿ����������0 IP��ַ*/
    if (__config_eth0_ip() != AW_OK){
        return ;
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(REMOT_PORT);
    remote_addr.sin_addr.s_addr = inet_addr(REMOTE_IP_ADDR);

    while(1){
        socfd = socket(AF_INET, SOCK_STREAM, 0);    /* TCPΪ��ʽ�׽��� */
        if (socfd < 0) {
            AW_INFOF(("fail to socket\r\n"));
            return;
        }

        if (0 == connect(socfd,(struct sockaddr *)&remote_addr,sizeof(remote_addr))) {
            aw_kprintf("TCP client: connected.\r\n");

            while (1) {
                recv_size = recv(socfd, msg, sizeof(msg), 0);
                /* ��������Զ�˵����� */
                if (recv_size > 0) {

                    AW_INFOF(("msg:%s\r\n", msg));

                    /* �����ݷ��ͻ�ȥ */
                    send(socfd, msg, strlen(msg), 0);

                    /*��ջ�����*/
                    memset(msg, '\0', sizeof(msg));
                }

            }

        }

        closesocket(socfd);
        aw_mdelay(1000);
    }

}

/** [src_enet_tcp_client] */

/* end of file */
