#include "main.h"

void two_command(char *buff_1[MAX], char *buff_2[MAX])
{
	pid_t pid1, pid2;
	
	//fd[0] is read fd and fd[1] is write fd
	int fd[2];
	int status;

	pipe(fd);

	pid1 = fork();

	if(pid1)
	{
		pid2 = fork();
		if(pid2)
		{
			//closing both read and write fd of pipe
			close(fd[0]);
			close(fd[1]);

			//wait for child to finish
			wait(&status);
			wait(&status);
		}
		else
		{
			//close read descripter
			close(fd[0]);

			//close the stdout
			close(1);

			//duplicate the fd[1] to index number of stdout
			dup(fd[1]);

			//as fd[1] is duplicated with stdout so output of "ls"
			//command will be written to one end of pipe
			execvp(buff_1[0], buff_1 );
		}
	}

	else
	{
		//close write descripter
		close(fd[1]);

		//close the stdin
		close(0);

		//duplicate the fd[0] to index number of stdin
		dup(fd[0]);
		
		//as stdin is close and it is duplicated to fd[0]
		//therefor "wc" will read from another end of pipe
		execvp(buff_2[0], buff_2);

	}
	return;
}
