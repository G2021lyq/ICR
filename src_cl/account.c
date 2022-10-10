#include "head.h"

int client_login (int sockfd,char *username,int q)
{
//服务器的套结字；用于返回的用户名字；程序进程号（用于KILL）

        int flag;//1是成功，0是失败。
        struct user client;//将要发送给服务器的信息  
       	int a=0;//操作符
        char code[20];//验证的密码
        int is_login=0; //是否成功登陆->循环出口

        while(!is_login)
        {
                create(0);//生成初始页面
                system("tput cup 15 47");
                scanf("%d",&a);
                setbuf(stdin,NULL);//清除缓存区
                switch(a)
                {
                        case 1://客户想要登陆
                                create(1);//生成登陆页面
                                system("tput cup 9 48");  
                                scanf("%s",client.name);
                                setbuf(stdin,NULL);
                                
                                system("stty -echo");//隐藏密码
                		system("tput cup 11 46");  
                                scanf("%s",client.code);
                                setbuf(stdin,NULL);
                                system("stty echo");
                                
                                system("tput cup 14 13");  
                                printf("\t正在登录,请稍等...\033[0m\n");
                                
                                client.flag = 0;
                                //1
                                send(sockfd, &client, sizeof(struct user), 0);      //发送用户名和密码
                                //2
                                recv(sockfd, &flag, sizeof(int), 0);            //接收服务器的信息flag
                                
                                if(flag == 1)//验证成功
                                {
                                        strcpy(username, client.name);//将名字返回到主函数 
                                        is_login=1;
                                        sleep(2);
                                }
                                else    //验证失败
                                {
                                        system("tput cup 16 13");  printf("\t\033[34;1m您的用户名或密码有误,请重新登录!\033[0m\n");
                                        system("tput cup 17 13");  printf("\t\033[34;1m5s后将返回首界面.\033[0m\n");
                                        sleep(5);
                                }
                                break;
                        case 2:
                         	create(2);
                                system("tput cup 9 48");  
                                scanf("%s",client.name); 
                                setbuf(stdin,NULL);
                                        
                                system("stty -echo");
                                system("tput cup 11 46"); 
                                scanf("%s",client.code);
                                setbuf(stdin,NULL);
                                system("tput cup 13 52");
                                scanf("%s",code);
                                setbuf(stdin,NULL);
                                system("stty echo");
                                if(!strcmp(client.code,code))
                                {
                                        client.flag = 1;
                                        send(sockfd, &client, sizeof(struct user), 0);   //发送用户名和密码
                                        recv(sockfd, &flag, sizeof(int), 0);            //接收服务器的信息flag
                                        if(flag == 1)//注册成功;
                                        {
                                                system("tput cup 15 13"); printf("注册成功!\n");
                                        }
                                        else //用户重复注册;
                                        {
                                                system("tput cup 15 13"); printf("\033[34;1m该用户已被注册!\033[0m\n");
                                        }
                                 }
                                 else
                                 {
                                         system("tput cup 15 13"); printf("两次密码不一致!请重新输入!\n");
                                 }
                               	sleep(2);
                               	break;
                        case 3:
                                kill(q+2,SIGKILL);
                                kill(q+3,SIGKILL);
                                kill(q+4,SIGKILL);
                                exit(0);
                                break;
                        default:
                                break;
                }
        }
        return 0;
}
