 //测试system函数，可以直接运行shell命令好神奇

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ret;
    printf("系统的进程号是:%d\n",getpid());
    //ret=system("ping www.hisense.com -c 2");

    ret=system("ls");
    printf("system函数运行结果%d\n",ret);
    return 0;
    
}
                

