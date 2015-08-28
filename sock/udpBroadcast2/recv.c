#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
    int socketfd;
    socklen_t addr_len;
    char buf[64];
    struct sockaddr_in server_addr;
    if(argc < 3)
    {
        printf("uasge: %s ip port\n",argv[0]);
        exit(-1);
    }
    if((socketfd = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("socket");
        exit(-1);
    }
    printf("socketfd = %d\n",socketfd);
 
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));    
	addr_len=sizeof(server_addr);
 
    if(bind(socketfd,(struct sockaddr*)&server_addr,addr_len) < 0)
    {
        perror("bind");
        exit(-1);
    }
    char name[64];
    size_t len = sizeof(name);
    gethostname(name,len);
    while(1)
    {
        if(recvfrom(socketfd,buf,64,0,(struct sockaddr*)&server_addr,&addr_len) < 0)
        {
            perror("sendrto");
            exit(-1);
        }
        if(strncmp(buf,"quit",4) == 0)
            break;
 
        printf("host name>%s",name);
        printf("from: %s port:%d >%s",inet_ntoa(server_addr.sin_addr),ntohs(server_addr.sin_port),buf);
    }
 
    close(socketfd);
    return 0;
}