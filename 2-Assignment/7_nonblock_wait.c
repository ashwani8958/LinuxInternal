/*
Parent will not wait for child to finish and it will keep on doing it process
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	//declare variable
	pid_t pid;	
	
	//Create one process
	pid = fork();

	if(pid)
	{	
		//when child is finished it will return child PID
		while(waitpid(pid, NULL, WNOHANG) != pid)
		{
			printf("Parent is running\n");
		}
		
		//when in while loop child PID is returned it will come out of it 
		//and print 
		printf("Child is terminated\n");
	}
	
	//child 
	else
	{
		sleep(0.001);
	}

	return 0;
}
