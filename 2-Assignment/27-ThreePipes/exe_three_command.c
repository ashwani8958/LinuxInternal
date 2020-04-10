#include "main.h"


void three_command(char *buff_1[MAX], char *buff_2[MAX], char *buff_3[MAX])
{
	//To store the pid 
	pid_t pid1, pid2, pid3;

	//Array fd and fd_2 is used to return two file descriptors referring
	//to end of the pipe. fd[0] and fd_2[0] refers to read end of the pipe
	//fd[1] and fd_2[1] refers to write end of the pipe
	int fd[2], fd_2[2], status;

	//create a pipe, a unidirectional data channel that can be used for 
	//interprocess communication
	pipe(fd);
	pipe(fd_2);

	//Create new process
	pid1 = fork();

	if(pid1)
	{
		//wait for 1st child to finish
		wait(&status);

		//close the write end of 1st pipe to write end of file
		close(fd[1]);

		//Create new process
		pid2 = fork();
		if(pid2)
		{
			//wait for 2st child to finish
			wait(&status);

			//close the write end of 2st pipe to write end of file
			close(fd_2[1]);

			//Create new process
			pid3 = fork();

			if(pid3)
			{

				//wait for 3rd child to finish
				wait(&status);
			}

			//3rd child
			else
			{

				//close the stdin
				close(0);

				//duplicate the fd[0] to index number of stdin
				dup(fd_2[0]);

				//as stdin is close and it is duplicated to fd_2[0]
				//therefor "wc" will read from another end of pipe
				execvp(buff_3[0], buff_3);
			}


		}

		//2nd child
		else
		{

			//close the read end of pipe 2
			close(fd_2[0]);
			
			//close the stdin
			close(0);
			
			//read from the pipe 1
			dup(fd[0]);
			
			//close the stdout
			close(1);
			
			//write to pipe 2
			dup(fd_2[1]);

			//grep from the input of pipe 1 and write on the write end of pipe
			// 2
			execvp(buff_2[0], buff_2);
			//execvp(argv[1], argv + 1);
		}
	}

	//1st child
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
		execvp(buff_1[0], buff_1);
	}
}
