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
         
}
