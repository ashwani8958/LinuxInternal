#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 500

int main()
{
	//variable to store pid of process
	pid_t pid;

	//array "fd" is used to return two file descriptors referring to the ends
	//of pipe
	//fd[0] is read end of pipe and fd[1] is write end of pipe
	int fd[2];
	
	//Store the length of string
	int str_len;

	//Other variable
	int shmid;
	char buff[MAX];
	char rev_buff[MAX] = {'\0'};
	char *ptr;
	
	//Return the identifier (shmid) of the shared memory segment associated
	//with the value of key(0XAB) size of shared memory is MAX
	shmid = shmget(0XAB, MAX, IPC_CREAT | 0666);
	
	//Attaches the shared memory segment
	ptr = (char *)shmat(shmid , NULL , 0);
	
	//set the 1st char of shared memory to '0'
	//ptr[0] =  '0';

	//Create a undirectional pipe
	pipe(fd);

	pid = fork();
	
	//Parent process
	if(pid)
	{
		//File descriptor
		int fd_w;

		//Buffer to store string from FIFO pipe
		char buff_fifo[MAX] = {'\0'};
		ssize_t wrt;

		//close read descripter
		close(fd[0]);

		//prompt user to enter string
		printf("Enter the string: ");
		scanf("%[^\n]s", buff);

		//write to pipe and pass string to child process
		write(fd[1], buff, MAX);
		
		//Open FIFO pipe in read only mode
		fd_w = open("/tmp/my_fifo", O_RDONLY);
		
		//Read from pipe and store in buffer to print later
		wrt = read(fd_w, buff_fifo, MAX);
	
		if(wrt == -1)
		{
			perror("Can't read from my_fifo: ");
			return -1;
		}
		
		//print the FIFO buffer content
		printf("Content of FIFO buffer written by process 2 -> %s\n", buff_fifo);
	
	}

	else
	{
		//Declare variable
		int count = 0;

		//close write descripter
		close(fd[1]);

		//Read from pipe and print on stdout
		read(fd[0],buff,MAX);
		printf("string received in child -> %s\n", buff);

		//Calculate string length
		str_len = strlen(buff);

		//Reverse the string
		while(str_len >= 0)
		{
			rev_buff[count] = buff[str_len -1];
			str_len--;
			count++;
		}
		
		//Child process write to shared memory and print it from shared memory
		strcpy(ptr,rev_buff);
		printf("String stored in shared memory by child -> %s\n", ptr);

	}

	return 0;

}
