#include "head.h"
#include "head2.h"

struct msg *head;       //在线用户的链表头   
pthread_mutex_t mutex_1;        //互斥锁，用于在线用户链表/聊天记录文件
extern struct user client;

void thread_routine (void *param)
{
        int new_sock = *((int *)param);         //连接套接字
        FILE *logsfp;
        int byteread;
        char buf[BUFFER_SIZE];
        char onlinename[BUFFER_SIZE];           //在线用户列表
        int onlinefd;                           //发送给客户端的连接套接字      

        struct timeval timeout;                 //select等待时间
        fd_set readset, r_readset;
        int maxfd;
        int nfound;

        //截取名字
        int k;
        int i;                                  //循环变量
        char *getname[20];
        char *q;

        struct msg msgs;
        struct msg *s, *p;
        struct msg tmp;                         //退出信息

        getname[0] = (char *)malloc(40);
        getname[1] = (char *)malloc(40);
        getname[2] = (char *)malloc(40);
        getname[3] = (char *)malloc(40);
        getname[4] = (char *)malloc(40);
        getname[5] = (char *)malloc(40);
        getname[6] = (char *)malloc(40);
        getname[7] = (char *)malloc(40);        //除了all，若群聊：只能和<=7个人聊

        //发送当前的套接字
        onlinefd = new_sock;
        if(send(new_sock, &onlinefd, sizeof(int), 0) < 0)
        {
                perror("sssend2 : ");
                pthread_exit(NULL);
        }

        pthread_mutex_lock(&mutex_1);
        //申请节点，插入链表
        s = (struct msg *)malloc(sizeof(struct msg));
        strcpy(s->from_name, client.name);
        s->fd = new_sock;

        s->next = head->next;
        head->next = s;

        //向当前用户发送消息“在线用户列表”
        bzero(onlinename, sizeof(onlinename));
        strcpy(onlinename, "在线的人:");
        for(p = head->next; p != NULL; p = p->next)
        {
                strcat(onlinename, p->from_name);
                strcat(onlinename, " ");
        }
        send(new_sock, onlinename, sizeof(onlinename), 0);


        //向其他用户发送信息“当前用户上线了”
        sprintf(tmp.message, "%s \033[32;1m上线了，您可以和他/她聊天了\033[0m\n", client.name);
        for(p = head->next; p != NULL; p = p->next)
        {
                if(p->fd != new_sock)
                {
                        if(send(p->fd, &tmp, sizeof(struct msg), 0) < 0)
                                perror("send : ");
                }
        }
pthread_mutex_unlock(&mutex_1);


        FD_ZERO(&readset);
        FD_SET(new_sock, &readset);

        maxfd = new_sock + 1;

        while(1)
        {
                r_readset = readset;

                timeout.tv_sec = 0;
                timeout.tv_usec = 500000;

                //io复用
                if((nfound = select(maxfd, &r_readset, (fd_set *)0, (fd_set *)0, &timeout)) < 0)
                {
                        perror("select");
                        continue;
                }
                else if(nfound == 0)
                {
                        continue;
                }

                if(FD_ISSET(new_sock, &r_readset))
                {
                        //接收消息
                        byteread = recv(new_sock, &msgs, sizeof(msgs), 0);

                        if(byteread < 0)        //recv出错
                        {
                                perror("recv -- :");
                                break;
                        }
                        else if(byteread == 0)  //连接中止，发送下线信息
                        {
                                break;
                        }

                        //若没“：”，无法处理，直接下一次。                              
                        if(strrchr(msgs.message, ':') == NULL)
                        {
                                continue;
                        }

                        //截取聊天信息中的用户名和内容  
                        k = 0;
                        strcpy(getname[k], strtok(msgs.message, ":"));

                        k++;
                        while((q = strtok(NULL, ":")))
                        {
                                strcpy(getname[k], q);
                                k++;
                        }

                        strcpy(msgs.message, getname[k - 1]);

pthread_mutex_lock(&mutex_1);
                        //记录聊天情况
                        if((logsfp = fopen("log.txt", "a")) == NULL)
                        {
                                perror("open file : ");
                        }


                        for(i = 0; i < k-1; i++)
                        {
                                sprintf(buf, "\n%s to %s %s %s\n", msgs.from_name, getname[i], msgs.info, msgs.message);
                                fprintf(logsfp, "%s", buf);     //写入文件

                                //向一个人发送消息
                                for(p = head->next; p != NULL; p = p->next)
                                {
                                        if(strcmp(getname[i], p->from_name) == 0)
                                        {
                                                send(p->fd, &msgs, sizeof(msgs), 0);
                                        }
                                }
                        }

                        //向所有人发送消息
                        if(strcmp(getname[0], "all") == 0)
                        {
                                for(p = head->next; p != NULL; p = p->next)
                                {
                                        if(strcmp(msgs.from_name, p->from_name) != 0)
                                        {
                                                send(p->fd, &msgs, sizeof(msgs), 0);
                                        }
                                }
                        }

                        fclose(logsfp);
pthread_mutex_unlock(&mutex_1);
                }//end if


        }//end while


pthread_mutex_lock(&mutex_1);
        //清理用户（下线的）
        delete_user(head, new_sock);
        close(new_sock);

        //发送下线消息
        sprintf(tmp.message, "%s 下线了\n", msgs.from_name);
        for(p = head->next; p != NULL; p = p->next)
        {
                send(p->fd, &tmp, sizeof(tmp), 0);
        }
pthread_mutex_unlock(&mutex_1);

        pthread_exit(NULL);
}

