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


	if(pid)
	{
		pid_t child_pid2;
		printf("child 1 is created with PID %d\n", pid);
		child_pid2 = fork();

		if(child_pid2)
		{
			pid_t child_pid3;

			//PID return from wait function
			pid_t w_pid_1, w_pid_2, w_pid_3;

			printf("child 2 is created with PID %d\n", child_pid2);

			child_pid3 = fork();

			if(child_pid3)
			{
				int stat_1, stat_2,stat_3;

				printf("child 3 is created with PID %d\n", child_pid3);
				
				w_pid_1 = wait(&stat_1);
				
				if (w_pid_1 == pid)
				{
					if(WIFEXITED(stat_1))
					{
						printf("Child 1 with PID %d is termimated with status code %d\n ", pid, WEXITSTATUS(stat_1));
					}

					else
					{
						printf("Child 1 is terminated abnormally\n");
					}
				}

				w_pid_2 = wait(&stat_2);
				
				if(w_pid_2 == child_pid2)
				{
					if(WIFEXITED(stat_2))
					{
						printf("Child 2 with PID %d is termimated with status code %d\n ",child_pid2, WEXITSTATUS(stat_2));
					}

					else
					{
						printf("Child 2 is terminated abnormally\n");
					}
				}


				w_pid_3 = wait(&stat_3);
				if(w_pid_3 == child_pid3)
				{

					if(WIFEXITED(stat_3))
					{
						printf("Child 3 with PID %d is termimated with status code %d\n ",child_pid3, WEXITSTATUS(stat_3));
					}

					else
					{
						printf("Child 3 is terminated abnormally\n");
					}
				}


			}

			else
			{
				//child 3
				sleep(3);
			}

			
		}
		else
		{
			//child 2
			sleep(2);
		}
		
	}
	else
	{
		//child 1
		sleep(1);
	}

	return 0;
}
