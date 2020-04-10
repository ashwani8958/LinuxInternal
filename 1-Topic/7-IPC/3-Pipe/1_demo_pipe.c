#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int fd[2];
	//fd[0] is read fd and fd[1] is write fd
	char buff[13];
	int status;
	
	pipe(fd);

	pid = fork();

	if(pid)
	{
		//close read descripter
		close(fd[0]);
		write(fd[1], "hello world", 12);
		//wait(&status);
	}

	else
	{
		//close write descripter
		close(fd[1]);
		read(fd[0],buff,12);
		printf("%s\n", buff);
	}
	return 0;
}
