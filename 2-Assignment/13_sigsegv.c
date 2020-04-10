#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig_num, siginfo_t *info, void *ptr)
{
	printf("address %p\n", info->si_addr);
	exit(0);
}

int main()
{
	//declare variable
	struct sigaction act;

	//resetting struct act variable to zero
	memset(&act, 0, sizeof(act));
	
	//assign function to sa_sigaction field of act
	act.sa_sigaction = handler;

	//necessary flag to set if sigaction function is to be used
	act.sa_flags = SA_SIGINFO;
	
	//giving pointer invaild address
	int *iptr = (int *)0x123456;
	
	//registering the sigaction function
	sigaction(SIGSEGV, &act, NULL);
	
	//segment fault because 0x123456 is not a vaild address
	*iptr = 10;

	pause();

	return 0;
}
