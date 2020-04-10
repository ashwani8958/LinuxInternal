#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fifo_chk, fd_w;
	char buff[20] = {'\0'};
	ssize_t wrt;


	fd_w = open("/tmp/my_fifo", O_RDONLY);
	
	wrt = read(fd_w, buff, 20);
	
	if(wrt == -1)
	{
		perror("Can't read from my_fifo: ");
		return -1;
	}

	printf("%s\n", buff);



	return 0;
}
