 //测试execve函数
 
#include <stdio.h>
#include <unistd.h>


int main(void)
{
    int *args[]={"/bin/ls",NULL};
    printf("系统的进程号是:%d\n",getpid());
    if(execve("/bin/ls",args,NULL)<0)
    {
        printf("execve 执行出错了\n");
    }
    return 0;
    
}
                

