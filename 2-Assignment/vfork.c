#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid;

	pid = vfork();

	if(pid)
	{
		printf("Parent PID %d\n", getpid());
	}
	else
	{
		sleep(1);
		printf("Parent ID of Child %d\n", getppid());
	}
}
