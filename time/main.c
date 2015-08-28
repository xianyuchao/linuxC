#include <stdio.h>
#include <time.h>

#include <sys/timeb.h>

int main(void)
{
	time_t timep;

	struct timeb tp;

	time(&timep);
	printf("%s\n",asctime(gmtime(&timep)));


	ftime(&tp);
	printf("time:%d\n",tp.time);
	printf("millitm:%d\n",tp.millitm);
	printf("zone:%d\n",tp.timezone);
	printf("dstflag:%d\n",tp.dstflag);	

	return 0;
}
