#include "main.h"

int main( int argc, char *argv[])
{
	//File descriptor integer 
	int fd_r, fd_w;

	//Normal variable to store the status
	int status_copy;

	//Check whether sufficent number of argument is passed or not
	if( argc < 2 || argc > 4)
	{
		printf("Error: ./a.out -p source_file destination_file\n");

		return -1;
	}

	//Check whether copy has to be created with permission or not
	if (!strcmp(argv[1],"-p"))
	{
		//open the source file in READ ONLY mode
		fd_r = open_file_read(argv[2]);
		
		//Condition when system call fail
		if(fd_r == -1)
		{
			return -1;
		}
	
		//Open Destinaton file in WRITE ONLY mode with 0666 Permission
		fd_w = open_file_write(argv[3]);

		//Condition when system call fail
		if(fd_w == -1)
		{
			return -1;
		}
		
		//Copy the content of file with permissions
		status_copy = copy(fd_r, fd_w, argv);

		//Condition when system call fail
		if(status_copy == 1)
		{
			return -1;
		}

		printf("\nCopy of file is created with permissions\n");
		printf("Content of file %s is copied/overwrite to %s\n", argv[2], argv[3]);

	}
	
	//Create copy without permissions
	else
	{

		//open the source file in READ ONLY mode
		fd_r = open_file_read(argv[1]);

		//Condition when system call fail
		if(fd_r == -1)
		{
			return -1;
		}

		//Open Destinaton file in WRITE ONLY mode with 0666 Permission
		fd_w = open_file_write(argv[2]);

		//Condition when system call fail
		if(fd_w == -1)
		{
			return -1;
		}

		//Copy the content of file without permissions
		status_copy = copy(fd_r,fd_w,argv);

		//Condition when system call fail
		if(status_copy == -1)
		{
			return -1;
		}
		
		printf("\nCopy of file is created without permission\n");
		printf("Content of file %s is copied/overwrite to %s\n", argv[1], argv[2]);

	}


	return 0;
}
