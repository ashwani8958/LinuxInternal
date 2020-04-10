#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MAX 50
//#include <>

int main()
{
	//Declare variable
	char buff[MAX];
	char buff_2[MAX] = {'\0'};
	int fd;
	pid_t pid, pid_2;
	
	//Create another process
	pid = fork();
	
	//parent process
	if(pid)
	{	
		//Child is sleeping
		sleep(1);

		//convert pid in character and store address in buff
		sprintf(buff, "/proc/%d/status", pid);

		//open file/child whose address is in buff in read only mode
		fd = open(buff, O_RDONLY);

		if(fd == -1)
		{
			perror("open");
			return -1;
		}

		//read first 43 character (status) of child
		read(fd,buff_2, 43);
		printf("%s\n", buff_2);
		
		//child is zombie/orphan
		sleep(2);
		sprintf(buff, "/proc/%d/status", pid);
		fd = open(buff, O_RDONLY);
		read(fd,buff_2, 35);
		printf("%s\n", buff_2);
		
		//creating one more child with same parent
		pid_2 = fork();
		
		//parent process
		if(pid_2)
		{	
			//killing parent
			exit(1);
		}
		else
		{
			//putting child in sleep mode so that it become orphan
			sleep(1);	
			sprintf(buff, "/proc/%d/status", pid);

			//fd will be -1 because child had already been adopted by init process and it have been cleared
			fd = open(buff, O_RDONLY);
			if(fd == -1)
			{
				printf("Child is cleared by init\n");
				exit(0);
			}
		}
	}

	else
	{
		sleep(2);
	}
	return 0;
}
