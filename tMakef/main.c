#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char str[]="123c#*^#fjei";
	int i;
	for(i=0;str[i]!=0;i++)
	{
		if(isalnum(str[i]))printf("%c is alnum\n",str[i]);
	}

	return 0;
}
