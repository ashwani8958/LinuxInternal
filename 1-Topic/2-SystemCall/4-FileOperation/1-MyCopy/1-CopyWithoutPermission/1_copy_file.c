#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
//#include <error.h>

#define MAX 100

int main( int argc, char *argv[])
{
	char buffer[MAX], choice;

	if( argc < 1)
	{
		printf("Error\n./a.out file.txt\n");
		return -1;
	}

	int fd_r, fd_w, bytes, w_bytes;

	fd_r = open(argv[1], O_RDONLY);

	if(fd_r == -1)
	{
		perror("open");
		return -1;
	}

//check if the file is already there or not
//check file if it already exist and fails if didn't exist and the output will
// MINUS ONE -1 otherwise if file exist output will be not -1
	fd_w = open(argv[2], O_EXCL);


#if 1
	if (fd_w == -1)
	{
		fd_w = open(argv[2], O_CREAT | O_WRONLY, 0666);



		if (fd_w == -1)
		{
			perror("open_in_write_mode");
			return -1;
		}
	}

	else
	{
		printf("File is already there\n");
		return -1;
	}

#endif

	do
	{
		bytes = read(fd_r, buffer, MAX);
		if(bytes == -1)
		{
			perror("read");
			return -1;
		}

		w_bytes = write(fd_w, buffer, bytes);

		if(w_bytes == -1)
		{
			perror("write");
			return -1;
		}

	}while(bytes == MAX);


	return 0;
}
