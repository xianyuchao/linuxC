/*这份代码经源码格式软件格式化过
     yang_hx@neusoft.com      */
#include <signal.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <unistd.h>	// sleep 函数

int main(int argc,char**argv)
{
    double y ;
    sigset_t intmask ;
    int i,repeat_factor ;
    if(argc!=2)
    {
        fprintf(stderr,"Usage:%s repeat_factor\n\a",argv[0]);
        exit(1);
    }
    if((repeat_factor=atoi(argv[1]))<1)repeat_factor=10 ;
    sigemptyset(&intmask);
    /* 将信号集合设置为空 */
    sigaddset(&intmask,SIGINT);
    /* 加入中断 Ctrl+C 信号*/
    while(1)
    {
        /*阻塞信号,我们不希望保存原来的集合所以参数为NULL*/
        sigprocmask(SIG_BLOCK,&intmask,NULL);
        fprintf(stderr,"SIGINT signal blocked\n");
		sleep(5);// 这段时间内，发送ctrl+c 也无法中断进程，因为阻塞了信号
        for(i=0;i<repeat_factor;i++)y=sin((double)i);
        fprintf(stderr,"Blocked calculation is finished\n");
        /* 取消阻塞 */
        sigprocmask(SIG_UNBLOCK,&intmask,NULL);
        fprintf(stderr,"SIGINT signal unblocked\n");
		sleep(5);// 这段时间内，可以中断
        for(i=0;i<repeat_factor;i++)y=sin((double)i);
        fprintf(stderr,"Unblocked calculation is finished\n");
    }
    exit(0);
}