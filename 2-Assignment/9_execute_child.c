/*
execvp system call replace child process with another proces, here child will be 
replaced by the command give from command line argument
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//Declare variable
	pid_t pid;
	int status;
	
	//create child process
	pid = fork();
	
	
	if(pid)
	{
		//Declare variable
		pid_t child_p;
		
		//Suspends execution parent it child terminate
		//return the pid of first terminated child
		child_p = wait(&status);

		printf("Child has finished : PID = %d\n", child_p);
		
		//if child terminate normally
		if(WIFEXITED(status))
		{
			printf("Child existed with code %d\n", WEXITSTATUS(status));
		}

		else
		{
			printf("Child terminated abnormally\n");
		}

	}

	else
	{
	
		execvp(argv[1], argv + 1);
		//execlp("grep", "grep", "19", NULL);

		//if failed print reason for it
		perror("execve");
	}


}
