#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{ 
	unsigned int i; 
	alarm(1);//1������Լ�����sigalrm 
	for(i=0;1;i++) 
	printf("I=%d\n",i); 

	return 1;
} 