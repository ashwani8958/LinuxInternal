#include "main.h"

int copy(int fd_r, int fd_w, char *argv[])
{
	//Declartion of variable
	int status, file_permission;
	char buffer[MAX];

	//Declartion of structure
	//To Store info of source file
	struct stat file;

	//utimbuf structure store the info about modification time and access time
	//of source that later can be copied to destination file
	struct timespec times[3];

	//Call funtion to copy the content of file without permission 
	status = copy_content(fd_r,fd_w);

	//condition when system call fail
	if(status == -1)
	{
		return -1;
	}
	
	//Copy only permission when -p option is give
	if(!strcmp(argv[1], "-p"))
	{

		file_permission = fstat(fd_r, &file);

		//condition when system call fail
		if(file_permission == -1)
		{
			perror ("File Permission");
			return -1;
		}
		
		//set the variable of timespec to access and modification time of 
		//source file
		times[0].tv_sec = file.st_atim.tv_sec;
		times[0].tv_nsec = file.st_atim.tv_nsec;
		times[1].tv_sec = file.st_mtim.tv_sec;
		times[1].tv_nsec = file.st_mtim.tv_nsec;
		times[2].tv_sec = file.st_ctim.tv_sec;
		times[2].tv_nsec = file.st_ctim.tv_nsec;

		
		//Copy timestamp of source file to destination file
		file_permission = futimens(fd_w, times);

		//condition when system call fail
		if(file_permission == -1)
		{
			perror("Error in copying timestamp access time: ");
			return -1;
		}

		//System call to change the permission
		file_permission = fchmod(fd_w, file.st_mode);

		//condition when system call fail
		if(file_permission == -1)
		{
			perror ("Error in changing mode: ");
			return -1;
		}
		
		return 0;
	}

	return 0;
}
