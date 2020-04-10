#include "main.h"

int open_file_write(char argv[MAX])
{
	//File Descriptor interger
	int fd_w;

	//Normal Varible
	char choice;
	
	//Check whether the destination file present or not
	fd_w = open(argv, O_EXCL);
	
	//If not Present then create
	if (fd_w == -1)
	{	
		//Create the destination file and store in index number in fd_r
		fd_w = open(argv, O_CREAT | O_WRONLY, 0666);

		//Check for failure
		if (fd_w == -1)
		{
			perror("open destination");
			return -1;
		}

		return fd_w;
	}

	//If destination file is exist ask user to overwrite or not
	else
	{
		//Ask for over write or not		
		printf("File is already there\nDo you want to overwrite:");

		//Scan the choice
		scanf("\n%c", &choice);

		if('Y' == choice || 'y' == choice)
		{
			//O_TRUNC is used to clear the content of destination file
			fd_w = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0666);

			return fd_w;
		}
		
		//Exit if user don't want to over write
		else
		{
			return -1;
		}
	}
}
