#include <sys/select.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <semaphore.h>
#include <signal.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_SIZE 300
struct user     //用户名和密码
{
        char name[32];
        char code[32];
        int flag;
        struct user* next;
};

int anybody_register(struct user client); //服务器端的注册服务
int anybody_login (struct user client);//服务器端的登陆服务
void create(int num); //创建ui窗口
int client_login (int sockfd,char *username,int q);//客户端的账户系统



