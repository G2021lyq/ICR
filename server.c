#include <sys/types.h>
//数据类型定义
#include <sys/socket.h>
//提供socket函数及数据结构
#include <netinet/in.h>
//定义数据结构sockaddr_in
#include <arpa/inet.h>
//提供IP地址转换函数
#include <sys/ioctl.h>
//提供对I/O控制的函数
#include <sys/poll.h>
//提供socket等待测试机制的函数
#include <unistd.h>
//提供通用的unix类系统定义的文件、目录、程序及进程操作的函数
#include <errno.h>
//提供错误号errno的定义，用于错误处理
#include <fcntl.h>
//提供对文件控制的函数

#include <sys/time.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LISTEN_QUEUE_NUM 5
#define ECHO_PORT 2022


int main (int argc, char *argv[])
{
	struct sockaddr_in servaddr, remote; //指明地址信息.服务器地址,客户端地址 
	uint32_t addrlen; //地址的长度 
	
	int request_sock; //监听套接字
	int new_sock; //连接套接字
	
	int i=0;
	
	//创建监听套接字
	if((request_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
	//AF_INET表示IPv4地址，例如 127.0.0.1。SOCK_STREAM流式套接字，IPPROTO_TCP表示TCP传输协议 
		perror("socket:");
		return -1;
	}
	
	//初始化服务器地址 
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;//表明服务器地址协议类型为：TCP/IP 类型；
	servaddr.sin_addr.s_addr = INADDR_ANY;//指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或所有地址、任意地址
	servaddr.sin_port = htons((uint16_t)ECHO_PORT);//选择端口号 
	
	//绑定IP和端口号
	if(bind(request_sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
	//监听套接字，服务器地址，长度 
		perror("bind");
		return -1;
	}
	
	//监听
	if(listen(request_sock, LISTEN_QUEUE_NUM) < 0)
	{
	//监听套接字，监听等待队列长度 
		perror("listen");
		return -1;
	}
	
	while(1)
        {
                addrlen = sizeof(remote);

                //有人登录，进行连接。
                if((new_sock = accept(request_sock, (struct sockaddr *)&remote, &addrlen)) < 0)
                {

                        perror("accept");
                        continue;
                }
                printf("第%d次从客户端接收请求.\n",++i);
         }
	return 0;
}
