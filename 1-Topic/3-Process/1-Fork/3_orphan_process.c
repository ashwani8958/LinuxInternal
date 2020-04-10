#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main()
{
	pid_t pid;
	int x = 10;


#if 1
	
	//pid is child process ID
	pid = fork();

	if(pid)
	{
		//chlid will run first
		sleep(1);

		printf("This is parent %d child %d\n", getpid(), pid);
	}
	
	//For Child it return 0 PID
	else
	{
		
		//1st time it will print the PID of parent
		printf("This is child %d parent %d\n", getpid(), getppid());

		//parent will run first
		sleep(2);

		//2nd time it will not print the process ID of parent as parent has finished
		//before the termination of child so the child become orphan and it is adopted by
		//init process and this case is known as orphan process
		printf("This is child %d parent %d\n", getpid(), getppid());
	}
#endif

	return 0;
}
