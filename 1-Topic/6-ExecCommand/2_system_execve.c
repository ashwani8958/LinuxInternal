#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int status;

	pid = fork();

	if(pid)
	{
		pid_t child_p;

		child_p = wait(&status);

		printf("Child has finished : PID = %d\n", child_p);

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
		perror("execve");
	}


}
