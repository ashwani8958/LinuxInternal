#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Before exec pid is %d\n", getpid());
	
	//printf("Before exec\n");
	//execl("/bin/ls", "ls", "-l", "-a", NULL);
	execlp("ls","ls","-l", "-a" ,NULL);

	//execl("/bin/ps", "ps", "-e", "l", (void *) 0);

	printf("After exec\n");
}
