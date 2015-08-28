#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <signal.h> 
#include <stdlib.h>
/* Linux ��Ĭ�θ��˵������ַ�� /var/spool/mail/�û��ĵ�¼�� */ 
#define MAIL "/var/spool/mail/root" 
/* ˯��10���� */ 

#define SLEEP_TIME 10 
main(void) 
{ 
	pid_t child; 
	if((child=fork())==-1) 
	{ 
		printf("Fork Error:%s\n",strerror(errno)); 
		exit(1); 
	} 
	else if(child>0) 
	while(1); 

	printf("Fork ok\n"); 

	if(kill(getppid(),SIGTERM)==-1) 
	{ 
		printf("Kill Parent Error:%s\n",strerror(errno)); 
		exit(1); 
	}  
	{ 
		int mailfd; 
		while(1) 
		{ 
			if((mailfd=open(MAIL,O_RDONLY))!=-1) 
			{ 
				printf("open ok");
				fprintf(stderr,"%s","\007"); 
				close(mailfd); 
				
			}  
			else
			{
				printf("open result -1");
			}
			sleep(SLEEP_TIME); 
		} 
	} 
} 
