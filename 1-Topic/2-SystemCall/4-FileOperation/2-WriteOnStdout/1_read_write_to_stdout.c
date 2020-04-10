/*
Code to write from file to standard output
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define MAX 100

int main( int argc, char *argv[])
{
	char buffer[MAX];

	if( argc < 1)
	{
		printf("Error\n./a.out file.txt\n");
		return -1;
	}

	int fd, bytes, w_bytes;
	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	do
	{
		bytes = read(fd, buffer, MAX);
		if(bytes == -1)
		{
			perror("read");
			return -1;
		}
		
		w_bytes = write(1, buffer, bytes);

		if(w_bytes == -1)
		{
			perror("write");
			return -1;
		}

	}while(bytes == MAX);


	return 0;
}
