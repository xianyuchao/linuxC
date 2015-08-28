 //测试tcp/ip 相关 bind等 函数
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//sockaddr_in 结构体

#include <string.h>//bzero函数
#include <errno.h>

#define MYPORT 3491

void perr(int ret,int equcst)//equal to const
{
	if(ret==equcst)
	{
		printf("%s\n",strerror(errno));
		return;
	}
}

//主函数
int main(void)
{
    int res,sockfd;//套接字文件描述符
	struct sockaddr_in my_addr;//套接字地址结构

	sockfd=socket(AF_INET,SOCK_STREAM,0);//一般ipv4都是这样设置
	
	perr(sockfd,-1);

	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	my_addr.sin_addr.s_addr= htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址

	bzero(&(my_addr.sin_zero),8);//清0

	res=bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
	perr(res,-1);

	res=listen(sockfd,10);//侦听队列长度
	perr(res,-1);

	close(sockfd);
	printf("end..\n");

    return;
    
    
    
}
    

                

