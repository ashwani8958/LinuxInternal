/*
Assignment 
Only one process should write on file at a time and another process should wait untill first finished the task
*/

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	//declare variable
	struct flock lock;
	int fd;
	pid_t pid;
	
	//set every field to zero
	memset(&lock, 0, sizeof(lock));

	//open file 
	fd = open(argv[1], O_CREAT | O_WRONLY, 0666 );
	if(fd == -1)
	{
		perror("Error in opening file: ");
		return -1;
	}
	
	//split into two process
	pid = fork();

	//parent process 
	//At one time only one from parent and child write to file
	if(pid)
	{	
		//parent is trying to get lock so that only parent can write
		lock.l_type = F_WRLCK;
		printf("Parent is trying to lock\n");

		//parent got the lock so that only parent can write
		fcntl(fd, F_SETLKW, &lock);
		printf("Parent got the lock\n");

		//parent write in file
		write(fd, "PARENT CONTENT\n", 16);

		//wait for user to interrupt from keyboard
		getchar();

		//parent release the lock now child can write
		lock.l_type = F_UNLCK;
		printf("Parent Process trying to UNLOCK fd\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("Parent process : fd is unlocked\n");
	}
	
	else
	{
		//child is trying to get lock so that only child can write
		lock.l_type = F_WRLCK;

		//child lock file and now only child can write
		printf("Child is trying to lock\n");
		fcntl(fd, F_SETLKW, &lock);
		
		//Child got the lock and only child can write on file
		printf("Child got the lock\n");
		write(fd, "CHILD CONTENT\n", 15);

		//Wait for input from  keyboard
		getchar();

		//Child unlocking so other process can write 
		lock.l_type = F_UNLCK;
		printf("child Process trying to UNLOCK fd\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("child process : fd is unlocked\n");
	}

	return 0;
}
