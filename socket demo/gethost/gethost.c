#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
//#include <netdb.h>

int main(int argc, char *argv[]) 
{ 
	struct hostent * phostent; // 指向hostent结构的指针
	struct in_addr in;           // IPV4地址结构
	char hostname[20];
	if ((phostent = gethostbyname("www.pyp.edu.cn")) == NULL)
	  printf("gethostbyname() 错误：%d", errno);
	else
	{
	  // 拷贝4字节的IP地址到IPV4地址结构
	  memcpy(&in, phostent->h_addr, 4);
	
	  printf("主机 %s 的IP地址是：", phostent->h_name);
	  printf(" %s\n", inet_ntoa(in));
	}
	gethostname(hostname,20);
	printf("The host name is %s\n",hostname);
	exit(0); 
} 