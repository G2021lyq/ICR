#include "head.h"

int anybody_login (struct user client) 
{
	struct user users[USER_SIZE]; 
	int i;
	struct msg *p;
	int flag = 0;//检验用户名和密码匹配，0表示失败，1表示成功，-1表示重复登录。
	FILE *fp; 
//查用户表 
	if((fp=fopen("user.dat", "r")) == NULL) //user.dat存放着所有的用户名和密码
	{
		perror("open"); 
		exit(-1);
	}
	for(i = 0; i < USER_SIZE; i++) 
	{
		fscanf(fp, "%s %s", users[i].name, users[i].code);
		if(!strcmp(client.name, users[i].name) && !strcmp(client.code, users[i].code))
		{
			//用户名密码匹配 
			flag=1; 
			break;
		}
	}
	fclose(fp); 
	return flag; 
}
