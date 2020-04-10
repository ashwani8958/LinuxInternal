#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Running ps with system\n");
	system("ps -el");
	system("sleep 5");
	printf("after ps\n");

	return 0;
}
