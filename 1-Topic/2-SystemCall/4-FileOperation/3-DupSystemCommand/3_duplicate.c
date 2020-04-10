#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char *argv[])
{
	int new_fd, fd, backup_stdout;

	fd = open(argv[1], O_CREAT | O_WRONLY, 0666);
	if(fd == -1)
	{
		printf("open:");
		return -1;
	}

	

	backup_stdout = dup(1);

	close(1);

	new_fd = dup(fd);

	printf("fd: %d\tfd_new: %d\n", fd, new_fd);

	printf("Std output is closed\n");

	//close(new_fd);
	
	fflush(stdout);

	close(fd);

#if 0	
	close(new_fd);

	dup(backup_stdout);
#endif

#if 1

	dup2(backup_stdout, 1);

#endif

	printf("Std output is open\n");
	return 0;
}
