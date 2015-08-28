 //测试线程的相关函数，操作方法

//注意要编译的时候要加上-lpthread
#include <stdio.h>
#include <pthread.h>

#include <errno.h>

static int run=-1;
static int retvalue;


void *start_routine(void *arg)
{
    int *running=arg;
    int cnt=0;//记录子进程运行了几次
    printf("子进程正在运行\n");
    while(*running)
    {
        printf("子进程运行了%d次\n",cnt++);
        usleep(1);
    }
    printf("子进程运行结束\n",cnt++);
	retvalue=10;
    pthread_exit((void*)&retvalue);//end thread
}
        


//主函数
int main(void)
{
    pthread_t pt;
    int ret=-1;
    int times=3;
    int i=0;
    int *ret_join=NULL;

    ret=pthread_create(&pt,NULL,(void*)start_routine,&run);

    if(ret!=0)
    {
        printf("create pthread failed\n");
        return 1;
    }

    usleep(1);
    for(;i<times;i++)
    {
        printf("主进程%d次\n",i);
        usleep(1);
    }
    run=0;//让子进程结束
    pthread_join(pt,(void*)&ret_join);
    printf("子线程返回值为%d\n",*ret_join);
    return 0;
}
        

    

                

