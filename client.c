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

#include "head.h"
#include "head2.h"

#define SERVER_NAME "127.0.0.1"
#define ECHO_PORT 2022

#define RET_OK  0
#define RET_ERR -1
#define LISTEN_QUEUE_NUM 5

int q;
//记录进程号

char username[32];      //用户名
int onlinefd;           //服务器端的TCP连接后的套接字
char onlinename[1024];  //在线用户列表

int main (int argc, char *argv[])
{
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
        
        if(client_login(sock, username,q) != 0)
        {
                close(sock);
                return -1;
        }
        create(3);
        //3,4
        recv(sock, &onlinefd, sizeof(int), 0);
        recv(sock, onlinename, sizeof(onlinename), 0);
        system("tput cup 12 13");  printf("\033[34;1m%s\033[0m\n", onlinename); //打印在线用户名单

	work(sock,pid,q);
	
        close(sock);
        return 0;
   
}
