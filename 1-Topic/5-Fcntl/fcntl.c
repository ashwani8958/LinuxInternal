#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	struct flock lock;
	int fd;
	pid_t pid;
	
	memset(&lock, 0, sizeof(lock));

	fd = open(argv[1], O_CREAT | O_WRONLY, 0666 );
	if(fd == -1)
	{
		perror("Error in opening file: ");
		return -1;
	}

	pid = fork();
	if(pid)
	{
		lock.l_type = F_WRLCK;
		printf("Parent is trying to lock\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("Parent got the lock\n");
		write(fd, "PARENT CONTENT\n", 16);
		getchar();
		lock.l_type = F_UNLCK;
		printf("Parent Process trying to UNLOCK fd\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("Parent process : fd is unlocked\n");
	}
	
	else
	{
		lock.l_type = F_WRLCK;
		printf("Child is trying to lock\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("Child got the lock\n");
		write(fd, "CHILD CONTENT\n", 15);
		getchar();
		lock.l_type = F_UNLCK;
		printf("child Process trying to UNLOCK fd\n");
		fcntl(fd, F_SETLKW, &lock);
		printf("child process : fd is unlocked\n");
	}
}
