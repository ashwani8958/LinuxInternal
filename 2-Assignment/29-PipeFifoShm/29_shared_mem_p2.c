#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 500

int main()
{	

	//Declare variables
	int str_len, i = 0;
	int shmid;
	int fifo_chk, fd_w;
	ssize_t wrt;
	char *ptr;
	
	//As shared memory is already created this time it will link
	//with it by the help of KEY 
	shmid = shmget(0XAB, MAX, IPC_CREAT | 0666);
	
	//Attaches the shared memory segment
	ptr = shmat(shmid , NULL , 0);
	
	//Calculate string length
	str_len = strlen(ptr);
	
	//Convert string in upper case character
	while(str_len > 0)
	{
		if(isalpha(ptr[i]))
		{
			ptr[i] = ptr[i] - 32;
		}

		i++;
		str_len--;
	}
	
	//Store NULL at last position in string
	ptr[i] = '\0';

	//Create the FIFO pipe 
	fifo_chk = mkfifo("/tmp/my_fifo", 0666);
	
	//Open in write only mode
	fd_w = open("/tmp/my_fifo", O_WRONLY);

	if (fd_w == -1)
	{
		perror("Write in fifo failed due to: ");
		return -1;
	}


	//write the content of shared memory in FIFO pipe
	wrt = write(fd_w, ptr, MAX);
	
	if(wrt == -1)
	{
		perror("Can't write in my_fifo: ");
		return -1;
	}
	
	return 0;
}	
