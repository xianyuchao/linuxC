 //����execve����
 
#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int *args[]={"/bin/ls",NULL};
    printf("ϵͳ�Ľ��̺���:%d\n",getpid());
    if(execve("/bin/ls",args,NULL)<0)
    {
        printf("execve ִ�г�����\n");
    }
    return 0;
    
}
                

