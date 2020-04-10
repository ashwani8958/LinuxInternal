#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>

#define MAX 500

int main()
{	
	//Declare variables
	int str_len, i = 0;
	int shmid;
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
		if(isalpha(ptr[ i + 1]))
			ptr[i + 1] = ptr[i + 1] - 32;
		i++;
		str_len--;
	}
	
	//Store NULL at last position in string
	ptr[i] = '\0';

	//set the first position in the shared memory so that parent in process 1 can 
	//come out of while loop
	ptr[0] = '1';
}	
