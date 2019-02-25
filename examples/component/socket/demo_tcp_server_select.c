#include "aworks.h"
#include "net/aw_sockets.h"
#include <string.h>
#include "stdio.h"

void demo_tcp_server_select(void){

    int server_sockfd,client_sockfd;
    socklen_t server_len,client_len;

    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds,testfds;

    /*创建套接字IPV4,tcp流套接字*/
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1234);
    server_len = sizeof(server_address);

    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

    listen(server_sockfd,5);

    FD_ZERO(&readfds);
    FD_SET(server_sockfd,&readfds);

    /*等待客户端请求*/
    while(1){
        char ch_buf[64];
        int fd;
        int nread = 1;
        testfds = readfds;

        aw_kprintf("server waiting\r\n");
        result = select(FD_SETSIZE,&testfds,(fd_set*)0,(fd_set*)0,(struct timeval*)0);
        if(result < 1){
            perror("server");
            exit(1);
        }

        /*轮询*/
        for(fd = 0 ;fd < FD_SETSIZE;fd++){
            if(FD_ISSET(fd,&testfds)){
                if(fd == server_sockfd){
                    client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
                    FD_SET(client_sockfd,&readfds);
                    aw_kprintf("adding client on fd %d\r\n",client_sockfd);
                }else{
                    ioctlsocket(fd,FIONREAD,&nread);
                    if(nread == 0){
                        closesocket(fd);
                        FD_CLR(fd,&readfds);
                        aw_kprintf("removing client on fd %d\r\n",fd);
                    }else{
                        memset(ch_buf,0,64);
                        recv(fd,&ch_buf[0],64,0);
                        aw_kprintf("from fd %d data:%s\r\n",fd,ch_buf);
                        send(fd,&ch_buf[0],64,0);
                    }
                }
            }
        }
    }

}
