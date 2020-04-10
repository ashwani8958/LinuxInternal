/*
To generater SIGINT(crtl + c) signal without pressing crtl + c
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sig_handler(int arg)
{
		;
}

int main()
{
	
	//Declare variable
	pid_t pid;

	//registering signal handler
	signal(SIGINT, sig_handler);
	
	//duplicate process
	pid = fork();

	if(pid)
	{	
		printf("parent process is waiting for SIGINT\n");
		
		pause();

		printf("parent: SIGINT received\n");

	}
	else
	{	
		//after sleeping for 3sec SIGINT signal is raised and sent to parent
		//using kill system call
		sleep(3);

		printf("Child process is sending SIGINT to Parent\n");
		kill(getppid(), SIGINT);
		printf("Child process: Terminated\n");
	}

}
