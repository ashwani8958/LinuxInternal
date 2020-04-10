#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fifo_chk, fd_w;
	char buff[20] = {'\0'};
	ssize_t wrt;

	fifo_chk = mkfifo("/tmp/my_fifo", 0666);

	fd_w = open("/tmp/my_fifo", O_WRONLY);
	if (fd_w == -1)
	{
		perror("Write in fifo failed due to: ");
		return -1;
	}

	printf("enter the string: ");
	scanf("%s", buff);

	wrt = write(fd_w, buff, 20);

	if(wrt == -1)
	{
		perror("Can't write in my_fifo: ");
		return -1;
	}



	return 0;
}
