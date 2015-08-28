 //����tcp/ip ��� bind�� ����
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>//sockaddr_in �ṹ��

#include <string.h>//bzero����
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

//������
int main(void)
{
    int res,sockfd;//�׽����ļ�������
	struct sockaddr_in my_addr;//�׽��ֵ�ַ�ṹ

	sockfd=socket(AF_INET,SOCK_STREAM,0);//һ��ipv4������������
	
	perr(sockfd,-1);

	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	my_addr.sin_addr.s_addr= htons(INADDR_ANY);//INADDR_ANY��ʾ�Զ���ȡ������ַ

	bzero(&(my_addr.sin_zero),8);//��0

	res=bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
	perr(res,-1);

	res=listen(sockfd,10);//�������г���
	perr(res,-1);

	close(sockfd);
	printf("end..\n");

    return;
    
    
    
}
    

                

