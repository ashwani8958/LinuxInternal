#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t pid;


#if 1
	
	//pid is child process ID
	pid = fork();

	if(pid)
	{
		sleep(100);
		printf("This is parent %d child %d\n", getpid(), pid);
	}
	
	//For Child it return 0 PID
	else
	{
		//as parent is in sleep for long time the child process will complete before terminating the parent 
		//and child become zombie.
		printf("This is child %d parent %d\n", getpid(), getppid());
	}
#endif

	return 0;
}
