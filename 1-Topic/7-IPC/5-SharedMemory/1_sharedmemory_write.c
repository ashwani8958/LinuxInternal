#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int shmid;
	char *ptr;
	struct shmid_ds stat;

	shmid = shmget(0xAB, 1000, IPC_CREAT | 0666);
	
	ptr = shmat(shmid, NULL, 0);

	printf("Enter string: ");
	scanf("%[^\n]s", ptr);

	shmdt(ptr);
	
	//to destory
	shmctl(shmid, IPC_STAT, &stat);

	printf("segment: %ld\n last attach time %ld\n last detach time: %ld\n last change time: %ld\n PID of creator %d\n PID of last shmat/shmdt %d\n no.of current attachs %ld\n", stat.shm_segsz, stat.shm_atime, stat.shm_dtime, stat.shm_ctime, stat.shm_cpid, stat.shm_lpid, stat.shm_nattch);
	

	return 0;
}
