#include "main.h"

int open_file_read(char argv[MAX])
{
	//File descriptor
	int fd_r;
	
	//Open source file in READ ONLY mode
	fd_r = open(argv, O_RDONLY);
	
	//condition when system call fail
	if( fd_r == -1)
	{
		//Print Error message
		perror("Open:");

		return -1;
	}

}
