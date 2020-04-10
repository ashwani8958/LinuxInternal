#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	//printf("Before fork\n");
	//system("ps -el");
	fork();
	fork();
	fork();
	printf("After fork\n");
	
	return 0;
}
