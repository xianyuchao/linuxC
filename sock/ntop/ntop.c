#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main (void)
{
	char IPdotdec[20]; //��ŵ��ʮ����IP��ַ
	//struct in_addr s; // IPv4��ַ�ṹ��
	struct sockaddr_in s;	//ͨ�ýṹ��
	// ����IP��ַ
	printf("Please input IP address: ");
	scanf("%s", IPdotdec);
	// ת��
	inet_pton(AF_INET, IPdotdec, (void *)&s);
	//printf("inet_pton: 0x%x\n", s.s_addr); // ע��õ����ֽ���
	printf("inet_pton: 0x%x\n", s.sin_addr.s_addr);
	// ��ת��
	inet_ntop(AF_INET, (void *)&s, IPdotdec, 16);
	printf("inet_ntop: %s\n", IPdotdec);
}