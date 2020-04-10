/*
Block parent without using wait()
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int flag;

void sig_handler(int arg)
{
		flag = arg;
}

int main()
{
	
	//Declare variable
	pid_t pid;
	
	//SIGCHLD signal info when child change it state
	signal(SIGCHLD, sig_handler);

	pid = fork();

	if(pid)
	{
		printf("parent process is waiting for child to finised\n");

		//will be in while loop till child is alive
		while(!flag);
		printf("Child is finished\n");

	}
	else
	{	
		//child terminate after 4 sec and control go to function handler
		//and set the flag
		sleep(4);
		printf("Child process: Terminated\n");
	}

}
