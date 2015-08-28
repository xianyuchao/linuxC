/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
 
#define MAXLINE 80

#define SERV_PORT 8100
 
int main(void)
{
        struct sockaddr_in servaddr, cliaddr;
        socklen_t cliaddr_len;
        int listenfd, connfd;
        char buf[MAXLINE];
        char str[20];
        int i, n;
 
        listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
		if(listenfd==-1)
		{
			printf("listen err\n"); 
			return 0;
		}

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERV_PORT);
   
        if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
        {       
                printf("bind err\n");
                return 0;
        } 

        if(listen(listenfd, 20))
		{
			printf("bind err\n");
            return 0;
		}
 
        printf("Accepting connections ...\n");
        while (1) {
               cliaddr_len = sizeof(cliaddr);
               connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &cliaddr_len);
				if ( connfd < 0)
				{
					printf("Server Accept Failed!\n");
					 return 0;
				}
         
               n = recv(connfd, buf, MAXLINE,0);

			   inet_ntop(AF_INET, (void*)&cliaddr, str, sizeof(str));

               printf("received from %s at PORT %d\n",str,ntohs(cliaddr.sin_port));
   
               for (i = 0; i < n; i++)
                       buf[i] = toupper(buf[i]);
               send(connfd, buf, n,0);
			   send(connfd,"woshiyigebing\n", 20,0);

               //close(connfd);
        }
		close(listenfd);
}
