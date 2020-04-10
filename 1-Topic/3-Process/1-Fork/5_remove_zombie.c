#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int exit_code, n;
	char *message;



	//pid is child process ID
	printf("Fork program starting\n");
	pid = fork();

	switch(pid)
	{
		case -1:
			exit(1);

		case 0:
			message = "THIS IS THE CHILD";
			n = 5;
			exit_code = 37;
			break;

		default:
			message = "THIS IS THE PARENT";
			n = 3;
			exit_code = 0;
			break;
	}

	for( ; n > 0; n--)
	{
		printf("%s\n", message);
		sleep(1);
	}


/* This section of the program waits for the child process to finish*/

	if(pid)
	{
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);
		printf("child has finished : PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
		{
			printf("child existed with code %d\n", WEXITSTATUS(stat_val));
		}

		else
		{
			printf("Child terminated abnormally\n");
		}

	}

	else
	{
		//For normal termination
		//exit(exit_code);

		//for abnormal termination
		abort();
	}

	return 0;
}
