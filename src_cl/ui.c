#include "head.h"

void create(int num)
{
	if (num == 0)
	{
		system("clear");
		system("tput cup 6 13"); printf("\t\033[34;1m********************************************************\n");
        	system("tput cup 7 13"); printf("\t*                  欢 迎 使 用ICR                      *\n");
        	system("tput cup 8 13"); printf("\t*------------------------------------------------------*\n");
        	system("tput cup 9 13"); printf("\t*                  1、登  陆                           *\n");
        	system("tput cup 10 13"); printf("\t*------------------------------------------------------*\n");
        	system("tput cup 11 13"); printf("\t*                  2、注  册                           *\n");
        	system("tput cup 12 13"); printf("\t*------------------------------------------------------*\n");
        	system("tput cup 13 13"); printf("\t*                  3、退  出                           *\n");
        	system("tput cup 14 13"); printf("\t*------------------------------------------------------*\n");
        	system("tput cup 15 13"); printf("\t*                  请  选  择:                         *\n");
        	system("tput cup 16 13"); printf("\t********************************************************\n");
        	//system("tput cup 15 47");
        }
        if (num == 1)
        {
        	system("clear");
                system("tput cup 6 13"); printf("\t\033[34;1m********************************************************\n");
                system("tput cup 7 13"); printf("\t*                      请    登   录                   *\n");
                system("tput cup 8 13"); printf("\t*------------------------------------------------------*\n");
                system("tput cup 9 13"); printf("\t*                      用 户 名:                       *\n");
                system("tput cup 10 13"); printf("\t*------------------------------------------------------*\n");
                system("tput cup 11 13"); printf("\t*                      密 码:                          *\n");
                system("tput cup 12 13"); printf("\t********************************************************\n"); 
                //system("tput cup 9 48");  
                //system("tput cup 11 46");  
         }
         if (num == 2)
         {
         	system("clear");
         	system("tput cup 6 13"); printf("\t\033[34;1m********************************************************\n");
                system("tput cup 7 13"); printf("\t*                      请    注   册                   *\n");
                system("tput cup 8 13"); printf("\t*------------------------------------------------------*\n");
                system("tput cup 9 13"); printf("\t*                      用 户 名:                       *\n");
                system("tput cup 10 13"); printf("\t*------------------------------------------------------*\n");
                system("tput cup 11 13"); printf("\t*                      密 码:                          *\n");
                system("tput cup 12 13"); printf("\t*------------------------------------------------------*\n");
                system("tput cup 13 13"); printf("\t*                      确 认 密 码:                    *\n");
                system("tput cup 14 13"); printf("\t********************************************************\n");
                //system("tput cup 9 49");  
                //system("tput cup 11 46");  
                //system("tput cup 13 52");  
         }
         if (num == 3)
         {
         	extern char username[];
         	system("reset");
         	system("tput cup 3 13");  printf("\033[32;1m登录成功\033[0m\n");
        	system("tput cup 4 13");  printf("\t\t\033[34;1m“%s” \033[0m\033[32;1m你好!\033[0m\n",username);
        	system("tput cup 5 13");  printf("\033[32;1m--------------------使用说明--------------------\n");
        	system("tput cup 6 13");  printf("单人聊天模式->格式为 聊天对象名:\033[0m\033[34;1m聊天内容\033[0m\n");
        	system("tput cup 7 13");  printf("\033[32;1m群聊聊天模式->格式为 all:\033[0m\033[34;1m聊天内容\033[0m\n");
        	system("tput cup 8 13");  printf("\033[32;1m退出聊天－>  \033[0m\033[34;1mquit\033[0m\n");
        	system("tput cup 9 13");  printf("\033[32;1m------------------------------------------------\033[0m\n");
        	system("tput cup 10 13");  printf("开始你的聊天吧，祝您聊的愉快...\033[0m\n\n");
         }
         
}
