/*��ݴ��뾭Դ���ʽ�����ʽ����
     yang_hx@neusoft.com      */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#define PROMPT "������ֹ������?"
char*prompt=PROMPT ;
void ctrl_c_op(int signo)
{
    write(STDERR_FILENO,prompt,strlen(prompt));
}
int main()
{
    struct sigaction act ;
    act.sa_handler=ctrl_c_op ;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0 ;
    if(sigaction(SIGINT,&act,NULL)<0)
    {
        fprintf(stderr,"Install Signal Action Error:%s\n\a",strerror(errno));
        exit(1);
    }
    while(1);
}