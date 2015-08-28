//���Թܵ��������ܵ�

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
	char string[WRITELEN]="��ã��ܵ�";
	char readbuffer[10*K];
	int *write_fd=&fd[1];
	int *read_fd=&fd[0];

	result=pipe(fd);//���Խ����ܵ�
	if(-1==result)
	{
		printf("create pipe fail");
		return -1;
	}

	pid=fork();//�����ӽ���
	if(-1==pid)
    {
		printf("fork failed");
	}

    if(0==pid)//�ӽ��̴�����
    {
        int write_size=WRITELEN;
        result=0;
        close(*read_fd);//�رն���
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
    }else//�����̴�����
    {
        close(*write_fd);//�ر�д��
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
                

