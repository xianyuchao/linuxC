 //�����̵߳���غ�������������

//ע��Ҫ�����ʱ��Ҫ����-lpthread
#include <stdio.h>
#include <pthread.h>

#include <errno.h>

static int run=-1;
static int retvalue;


void *start_routine(void *arg)
{
    int *running=arg;
    int cnt=0;//��¼�ӽ��������˼���
    printf("�ӽ�����������\n");
    while(*running)
    {
        printf("�ӽ���������%d��\n",cnt++);
        usleep(1);
    }
    printf("�ӽ������н���\n",cnt++);
	retvalue=10;
    pthread_exit((void*)&retvalue);//end thread
}
        


//������
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
        printf("������%d��\n",i);
        usleep(1);
    }
    run=0;//���ӽ��̽���
    pthread_join(pt,(void*)&ret_join);
    printf("���̷߳���ֵΪ%d\n",*ret_join);
    return 0;
}
        

    

                

