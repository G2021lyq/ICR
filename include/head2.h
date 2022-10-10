#define BUFFER_SIZE 5024
struct msg //在线用户的信息结构体（时时更新）
{
	int fd; //拥有者的服务器端的连接套接字
	char from_name[32]; //信息的拥有者
	char to_name[32]; //信息的读者
	char info[1024]; //拥有者时间 
	char message[1024]; //信息内容
	struct msg *next;
};
void work(int sock,pid_t pid,int q);
void thread_routine (void *param);
void delete_user (struct msg *head, int fd);
