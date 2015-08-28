//测试管道，创建管道

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define K 1024
#define WRITELEN (128*K)

int main(void)
{
    int result;
	int fd[2],nbytes;
	pid_t pid;
	char string[WRITELEN]="你好，管道";
	char readbuffer[10*K];
	int *write_fd=&fd[1];
	int *read_fd=&fd[0];

	result=pipe(fd);//尝试建立管道
	if(-1==result)
	{
		printf("create pipe fail");
		return -1;
	}

	pid=fork();//创建子进程
	if(-1==pid)
    {
		printf("fork failed");
	}

    if(0==pid)//子进程代码区
    {
        int write_size=WRITELEN;
        result=0;
        close(*read_fd);//关闭读端
        while(write_size>0)
        {
            result=write(*write_fd,string,write_size);
            if(result>0)
            {
                write_size-=result;
                printf("%d bytes wrote success,%d left\n",result,write_size);
            }
            else
            {
                sleep(10);
            }
        }
        printf("all are wrote by son pid\n");
        return 0;
    }else//父进程代码区
    {
        close(*write_fd);//关闭写端
        while(1)
        {
            nbytes=read(*read_fd,readbuffer,sizeof(readbuffer));
            if(nbytes<=0)
            {
                printf("all data read,no anymore\n");
                break;
            }
            printf("%d bytes are read.content is %s\n",nbytes,readbuffer);
        }
        return 0;
    }
}
                

