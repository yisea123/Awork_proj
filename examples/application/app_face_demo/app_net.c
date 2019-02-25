/*
 * app_net.c
 *
 *  Created on: 2018年9月24日
 *      Author: 30374
 */


#include "aworks.h"
#include "aw_mem.h"
#include "aw_gprs.h"
#include "aw_delay.h"
#include "aw_task.h"
#include "aw_sem.h"
#include "aw_vdebug.h"
#include "string.h"
#include "net/aw_net.h"
#include "net/aw_sockets.h"
#include "stdio.h"


#define __NET_TSK_STACK  10 * 1024
#define __NET_IP         "120.79.119.10"//"121.33.243.38"//
#define __NET_PORT       3333

struct __app_net {
    int      dev_id;
    int      handel;
    uint8_t  face[320 * 240 * 3 + 54];
    uint8_t  buf[1028];
    int      len;
    bool_t   busy;

    AW_TASK_DECL(net_task, __NET_TSK_STACK);
    AW_SEMB_DECL(sync);

    void *p_arg;
    void (*pfn_response) (void *p_arg, void *response, int len);
};




aw_err_t app_net_face_send (void *p_app, uint8_t *p_img, int len)
{
    struct __app_net *p = (struct __app_net *)p_app;

    if (p->busy) {
        return -AW_EBUSY;
    }

    p->busy = TRUE;

    memcpy(p->face, p_img, len);
    p->len = len;
    AW_SEMB_GIVE(p->sync);

    return AW_OK;
}


const char __head[] = {
    "POST /recognition HTTP/1.1\r\n"
    "Host: zlab.zlgcloud.com:3333\r\n"
    "User-Agent: curl/7.47.1\r\n"
    "Accept: */*\r\n"
    "Content-Length: %d\r\n"
    "Expect: 100-continue\r\n"
    "Content-Type: multipart/form-data; boundary=------------------------98e64aeb08be0ce7\r\n"
    "\r\n"
};

const char __file_info[] = {
        "--------------------------98e64aeb08be0ce7\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"img.bmp\"\r\n"
        "Content-Type: application/octet-stream\r\n"
        "\r\n"
};

const char __tail[] = {
        "\r\n--------------------------98e64aeb08be0ce7--\r\n"
};



/******************************************************************************/
aw_local void __net_tsk_handle (void *p_arg)
{
    struct __app_net   *p_app = (struct __app_net *)p_arg;
    ssize_t             ret;
    int                 len;
    char               *ptr;
    int                 timeout = 2000;
    struct sockaddr_in  server;

    do {
        ret = aw_gprs_ioctl(p_app->dev_id, AW_GPRS_REQ_PPP_OPEN, (void *)NULL);
        if (ret != AW_OK) {
            aw_mdelay(500);
        }
    } while (ret != AW_OK);

    AW_FOREVER {
        p_app->busy = FALSE;
        if (p_app->handel >= 0) {
            closesocket(p_app->handel); /* 关闭socket连接 */
        }
        AW_SEMB_TAKE(p_app->sync, AW_WAIT_FOREVER);

        do {
            p_app->handel = socket(AF_INET, SOCK_STREAM, 0);
            if (p_app->handel < 0) {
                aw_mdelay(500);
            }
        } while (p_app->handel < 0);

        /*设置接收超时时间*/
        ret = setsockopt(p_app->handel, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        if(ret != AW_OK){
            aw_kprintf("set socket timeout failed!\r\n");
            continue;
        }

        /*初始化server结构体*/
        memset(&server, 0, sizeof(struct sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_port   = htons(__NET_PORT);
        ret = inet_aton(__NET_IP, &(server.sin_addr));
        if (ret == 0) {
            aw_kprintf("inet_aton error!\r\n");
            continue;
        }

        do {
            /* 连接服务器  */
            ret = connect(p_app->handel, (struct sockaddr *) &server, sizeof(server));
            if (ret != 0) {
                aw_mdelay(500);
            }
        } while (ret != 0);

        len = sprintf((char *)p_app->buf, __head, p_app->len + sizeof(__file_info) + sizeof(__tail) - 2);
        ret = send(p_app->handel, p_app->buf, len, 0);
        if (ret <= 0) {
            aw_kprintf("send head failed!\r\n");
            continue;
        }

        ret = recv(p_app->handel, p_app->buf, 1024, 0);
        if(ret > 0){
            p_app->buf[ret] = '\0';
            aw_kprintf("%s\r\n", p_app->buf);
        } else {
        	aw_kprintf("http head not get response\r\n");
        	continue;
        }

        ret = send(p_app->handel, __file_info, sizeof(__file_info) - 1, 0);
        if (ret <= 0) {
            aw_kprintf("send file infomation failed!\r\n");
            continue;
        }

        ptr = (char *)p_app->face;
        while (p_app->len) {
            len = min(p_app->len, 1024);
            ret = send(p_app->handel, ptr, len, 0);
            if (ret <= 0) {
                aw_kprintf("send data failed!\r\n");
                break;
            }
            p_app->len -= len;
            ptr        += len;
        }
        if (p_app->len) {
            continue;
        }

        ret = send(p_app->handel, __tail, sizeof(__tail) - 1, 0);
        if (ret <= 0) {
            aw_kprintf("send tail failed!\r\n");
            continue;
        }

        ret = recv(p_app->handel, p_app->buf, 1024, 0);
        if (ret > 0) {
            p_app->buf[ret] = '\0';
            aw_kprintf("%s\r\n", p_app->buf);
        } else {
        	aw_kprintf("face response failed!\r\n");
        	continue;
        }

        if (p_app->pfn_response){
        	p_app->pfn_response(p_app->p_arg, (void *)p_app->buf, 1024);
        }
    }
}

void *app_net_create (void *p_arg,
		              void (*pfn_response) (void *p_arg, void *response, int len))
{
    struct __app_net *p_app;
    aw_err_t          ret;

    p_app = aw_mem_alloc(sizeof(*p_app));
    if (p_app == NULL) {
        return NULL;
    }

    p_app->dev_id = 0;
    p_app->handel = -1;
    p_app->busy   = FALSE;

    p_app->p_arg = p_arg;
    p_app->pfn_response = pfn_response;

    ret = aw_gprs_power_on(p_app->dev_id);
    if(ret != AW_OK){
        aw_kprintf("GPRS pwoer open failed:%d!\r\n", ret);
        goto __failed;
    }

    AW_SEMB_INIT(p_app->sync, 0, AW_SEM_Q_PRIORITY);

    AW_TASK_INIT(p_app->net_task,
                 "net",
                 10,
                 __NET_TSK_STACK ,
                 __net_tsk_handle,
                 (void *)p_app);

    AW_TASK_STARTUP(p_app->net_task);

    return p_app;

__failed:
    aw_gprs_power_off(p_app->dev_id);
    aw_mem_free(p_app);
    return NULL;
}



void app_net_destroy (void *p_app)
{
    struct __app_net *p = (struct __app_net *)p_app;

    if (p->handel >= 0) {
        aw_gprs_close(p->dev_id, p->handel);
    }
    aw_gprs_power_off(p->dev_id);

    AW_SEMB_TERMINATE(p->sync);
    AW_TASK_TERMINATE(p->net_task);

    aw_mem_free(p);
}

