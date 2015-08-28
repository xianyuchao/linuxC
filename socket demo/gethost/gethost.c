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
	struct hostent * phostent; // ָ��hostent�ṹ��ָ��
	struct in_addr in;           // IPV4��ַ�ṹ
	char hostname[20];
	if ((phostent = gethostbyname("www.pyp.edu.cn")) == NULL)
	  printf("gethostbyname() ����%d", errno);
	else
	{
	  // ����4�ֽڵ�IP��ַ��IPV4��ַ�ṹ
	  memcpy(&in, phostent->h_addr, 4);
	
	  printf("���� %s ��IP��ַ�ǣ�", phostent->h_name);
	  printf(" %s\n", inet_ntoa(in));
	}
	gethostname(hostname,20);
	printf("The host name is %s\n",hostname);
	exit(0); 
} 