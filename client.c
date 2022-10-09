#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#include <netdb.h>
#include <sys/select.h>
#include <signal.h>
#include <sys/wait.h>

#define SERVER_NAME "192.168.139.131"
#define ECHO_PORT 2022

int q;
//记录进程号

int main (int argc, char *argv[])
{
        int i=0;
        int sock;	//套接字
        struct sockaddr_in servaddr;
        struct hostent *server;

        server = gethostbyname(SERVER_NAME);

        //创建socket套接字
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("socket");
                return -1;
        }

        //设置IP 和 端口号
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = *(uint32_t *)server->h_addr;
        servaddr.sin_port = htons((uint16_t)ECHO_PORT);

        //连接服务器
        if(connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
                perror("connect");
                return -1;
        }
        
        pid_t pid=fork();
        
        if(pid<0)
        {
                fprintf(stderr,"错误!");
        }
        else if(pid==0)
        {
                exit(0);
        }
        else
        {
                q=pid+1;
                printf("%d\n",q);
        }
        
        close(sock);

        return 0;
}
