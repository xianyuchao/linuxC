//main.c
#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(int argc ,char **argv)
{
	int a=10,b=12;
	float x=1333.24433,y=33.55234;

	if(argc!=0)printf("arg count is %d\n",argc);

	//头文件定义的函数
	printf("int a+b IS:%d\n",add_int(a,b));	
	printf("int a-b IS:%d\n",sub_int(a,b));
	printf("float x+y IS:%f\n",add_float(x,y));
	printf("float x-y IS:%f\n",sub_float(x,y));


	return 0;

}