#include <stdio.h>

void printSegv(void)
{
	char *segvPtr = 0;
	printf("main: segvPtr= (%s)\n", segvPtr);
}
int main()
{
	printf("main: enter\n");
	//printSegv();
	printf("main: i=%d"
               "j=<%s>\n", 2);
	printf("main: exit\n");
	return 1;
}
	
