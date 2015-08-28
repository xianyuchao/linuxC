#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

/*
struct timeval 
{
    long tv_sec ;
    long tv_usec ;
};

int gettimeofday(struct timeval *tv,struct timezone *tz)
{
	tv->tv_sec=time((time_t*)NULL);
	tv->tv_sec=0;

	return 0;
}
*/

void function(void)
{
    unsigned int i,j ;
    double y ;
    for(i=0;i<1000;i++)
    for(j=0;j<1000;j++)
    y=sin((double)i);
}
int main(int argc,char**argv)
{
    struct timeval tpstart,tpend ;
    float timeuse ;
    gettimeofday(&tpstart,NULL);
    function();
    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
    tpend.tv_usec-tpstart.tv_usec ;
    timeuse/=1000000 ;
    printf("Used Time:%f\n",timeuse);
    exit(0);
}