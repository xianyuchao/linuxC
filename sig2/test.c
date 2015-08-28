/*��ݴ��뾭Դ���ʽ�����ʽ����
     yang_hx@neusoft.com      */
#include <signal.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <unistd.h>	// sleep ����

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
    /* ���źż�������Ϊ�� */
    sigaddset(&intmask,SIGINT);
    /* �����ж� Ctrl+C �ź�*/
    while(1)
    {
        /*�����ź�,���ǲ�ϣ������ԭ���ļ������Բ���ΪNULL*/
        sigprocmask(SIG_BLOCK,&intmask,NULL);
        fprintf(stderr,"SIGINT signal blocked\n");
		sleep(5);// ���ʱ���ڣ�����ctrl+c Ҳ�޷��жϽ��̣���Ϊ�������ź�
        for(i=0;i<repeat_factor;i++)y=sin((double)i);
        fprintf(stderr,"Blocked calculation is finished\n");
        /* ȡ������ */
        sigprocmask(SIG_UNBLOCK,&intmask,NULL);
        fprintf(stderr,"SIGINT signal unblocked\n");
		sleep(5);// ���ʱ���ڣ������ж�
        for(i=0;i<repeat_factor;i++)y=sin((double)i);
        fprintf(stderr,"Unblocked calculation is finished\n");
    }
    exit(0);
}