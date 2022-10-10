#include "head.h"
#include "head2.h"

extern char username[];      //用户名
extern int onlinefd;           //服务器端的TCP连接后的套接字
extern char onlinename[];  //在线用户列表

void work(int sock,pid_t pid,int q)
{
	int i=0;
	struct tm *ptm;         //时间有关
	time_t ts;
	char tim[50];
	int len;
	char buf[BUFFER_SIZE];
	struct msg msgs;
	
	if((pid = fork()) < 0)
        {
               // exit(-1);
        }
        
        if(pid == 0)    //该子进程接收消息（一般是其他用户的服务器处理程序 发送过来的）
        {
                while(1)
                {
                        bzero(&msgs, sizeof(msgs));
                        //5
                        len = recv(sock, &msgs, sizeof(msgs), 0);

                        if(len > 0)
                        {
                                printf("%s", msgs.info);
                                printf("\033[34;1m%s\033[0m", msgs.message);
                                sleep(1);
                                printf("---------------------------------------------------------------------------------\n");
                        }
                        else if(len < 0)
                        {
                                perror("recv : ");
                                break;
                        }
                        else
                        {
                                system("tput cup 10 33");  printf("\033[31;1m对不起，服务器出问题了\n");
                                system("tput cup 11 33");  printf("我们正在抢修，很抱歉给您造成麻烦了\033[0m\n");

                                //结束父进程
                                kill(getppid(), SIGKILL);
                                break;
                        }
                }
                
        }
        else    //父进程发送消息（只向该用户的服务器处理程序 发送）     
        {

                while(1)
                {
                        bzero(buf, BUFFER_SIZE);
                        bzero(&msgs, sizeof(struct msg));

                        msgs.fd = onlinefd;
                        strcpy(msgs.from_name, username);

                        if(fgets(buf, BUFFER_SIZE, stdin) == NULL)
                        {
                                if(ferror(stdin))
                                {
                                        perror("stdin");
                                        break;
                                }
                        }
                        strcpy(msgs.message, buf);
                        //判断是否退出
                        if(!strncasecmp(buf, "quit", 4))
                        {
                                send(sock, &msgs, sizeof(msgs), 0);
                                system("tput cup 44 13");  printf("\033[31;1m再见呢拜!\033[0m\n");
                                sleep(2);
                                system("clear");
                                kill(0,SIGKILL);
                                break;
                        }
                        if(!strncasecmp(buf,"stop",4))
                        {

                                kill(q+2,SIGKILL);
                                kill(q+3,SIGKILL);
                                kill(q+4,SIGKILL);
                        }

                        ts = time(NULL);                        //格式化时间
                        ptm = localtime(&ts);

                        sprintf(tim, "(%d-%d-%d %02d:%02d:%02d):", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
                        sprintf(msgs.info, "\n%s %s", username, tim);
                        if(send(sock, &msgs, sizeof(msgs), 0) < 0)
                        {
                        	printf("send ! %s", strerror(errno));
                                break;
                        }

                }
	}
}

