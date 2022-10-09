#include "head.h"

int anybody_register(struct user client) 
{
	int flag=1;//表明注册成功或者失败 
	FILE* fp;
	int i=0;
	struct user usr[USER_SIZE];
//查用户表 
	if((fp=fopen("user.dat", "r")) == NULL) //user.dat里面存放着所有的用户名和密码
	{
		perror("open");
		exit(-1);
	}
	
	for(i = 0; i < USER_SIZE; i++) 
	{
		fscanf(fp, "%s %s", usr[i].name, usr[i].code);
		if(!strcmp(client.name, usr[i].name)) //已经被注册了 
		{
			flag=-1; 
			break;
		}
	}
	fclose(fp); 
//注册 
	if(flag!=-1)
	{
		if((fp=fopen("user.dat","a+"))==NULL) 
		{
			perror("open"); 
			exit(-1);
		}
		fprintf(fp,"%s %s ",client.name,client.code);
		//未完待续; 
		printf("注册信息为:%s %s\n",client.name,client.code); 
		fclose(fp);
	}
	return flag; 
}
