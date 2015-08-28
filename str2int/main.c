#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char str[]="123c#*^#fjei";
	char *s=" 3883.33";
	float num1;
	int num2;

	num1=atof(str);
	num2=atoi(s);
	printf("%.2f\n%d\n",num1,num2);
	
	printf("Page Size =%d\n",getpagesize());

	return 0;
}
