 //����system����������ֱ������shell���������

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ret;
    printf("ϵͳ�Ľ��̺���:%d\n",getpid());
    //ret=system("ping www.hisense.com -c 2");

    ret=system("ls");
    printf("system�������н��%d\n",ret);
    return 0;
    
}
                

