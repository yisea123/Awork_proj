#include "aworks.h"
#include "net/aw_sockets.h"
#include "aw_vdebug.h"
#include "aw_defer.h"
#include "string.h"

aw_local struct aw_defer        __g_defer;
aw_local struct aw_defer_djob   __g_djob;

aw_local void __data_handle(void * p_arg){

    int client_sockfd = *(int *)p_arg;
    char ch_buf[64];

    while(1){
        memset(ch_buf,0,64);
        recv(client_sockfd,&ch_buf[0],64,0);
        aw_kprintf("from fd %d data:%s\r\n",client_sockfd,ch_buf);
        send(client_sockfd,&ch_buf[0],64,0);
    }

}

void demo_tcp_server_thread(void){

    int server_sockfd,client_sockfd;
    socklen_t server_len,client_len;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int ret;

    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1234);
    server_len = sizeof(server_address);

    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

    listen(server_sockfd,5);

    // 初始化一个延迟作业
    aw_defer_init(&__g_defer);

    // 启动延迟作业
    AW_DEFER_START(&__g_defer, 5, 0, 4096, "defer");

    while(1){
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        if(client_sockfd > 0){


            // 初始化一个工作节点
            aw_defer_job_init(&__g_djob, __data_handle, (void *)&client_sockfd);

            ret = aw_defer_commit(&__g_defer, &__g_djob);
            if (ret == AW_OK) {
                AW_INFOF(("client %s %d connected.\r\n",
                           inet_ntoa(client_address.sin_addr),
                           htons(client_address.sin_port)));
            }else{
                closesocket(client_sockfd);
            }

        }
    }

    return ;
}
