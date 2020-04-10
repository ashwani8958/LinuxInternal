#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	int x = 10;

#if 0

	//pid is a Parent process ID
	pid = getpid();


	if(pid == getpid())
	{
		printf("This is parent %d\n", pid);
	}

	else
	{
		printf("This is child %d\n", getpid());
	}
#endif

#if 1

	//pid is child process ID
	pid = fork();

	if(pid)
	{
		x = 20;
		printf("This is parent %d child %d\n", getpid(), pid);
	}

	//For Child it return 0 PID
	else
	{
		//sleep so that parent run first
		sleep(1);

		printf("This is child %d\n", getpid());
		printf("x = %d\n", x);
	}
#endif

	return 0;
}
