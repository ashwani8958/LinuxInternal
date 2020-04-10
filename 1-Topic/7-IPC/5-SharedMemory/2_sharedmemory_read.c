#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int shmid;
	char *ptr;

	shmid = shmget(0xAB, 1000, IPC_CREAT | 0666);
	
	ptr = shmat(shmid, NULL, 0);

	printf("%s\n ", ptr);

	shmdt(ptr);

	return 0;
}
