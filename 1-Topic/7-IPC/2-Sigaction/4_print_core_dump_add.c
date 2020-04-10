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
	struct sigaction act;


	memset(&act, 0, sizeof(act));

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;

	int *iptr = (int *)0x123456;
	sigaction(SIGSEGV, &act, NULL);
	*iptr = 10;

	pause();
	return 0;
}
