/* man sigsetops */

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
int flag;
void handler_1(int signal)
{
	flag = signal;
}

void handler_2(int signal)
{
	flag = signal;
}
int main()
{
	pid_t pid;

	signal(SIGUSR1, handler_1);
	signal(SIGUSR2, handler_2);
	
	pid = fork();

	if(pid)
	{
		sleep(5);
		printf("SIGUSR1 is send to child\n");
		kill(pid, SIGUSR1);
		printf("Parent is waiting for SIGUSR2\n");
		while(flag != SIGUSR2);
			
		printf("SIGUSR2 received is from child\n");
			
	}

	else
	{
		while(flag != SIGUSR1);
		printf("SIGUSR1 received from parent\n");
		sleep(5);
		printf("SIGUSR2 is send to parent\n");
		kill(getppid(), SIGUSR2);
	}

	return 0;
}


//run ./a.out & then use command "kill -2 PID" with the pid of process
//then in handler it print the pid of bash from where kill command 
//is issued
