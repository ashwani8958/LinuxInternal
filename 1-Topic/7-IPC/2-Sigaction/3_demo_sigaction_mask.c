/* man sigsetops */

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void handler(int signal_number, siginfo_t *info, void *ptr)
{
	//print the pid 0 because it is return by kernal
	printf("\nSIGINT received from %d\n", info->si_pid);
}

int main()
{
	struct sigaction act, oldact;
	sigset_t block_signal;
	
	memset(&act, 0, sizeof(act));

	sigemptyset(&block_signal);

	sigfillset(&block_signal);

	act.sa_mask = block_signal;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;


	sigaction(SIGINT, &act, &oldact);

	printf("pid = %d\n", getpid());

	pause();

	return 0;
}


//run ./a.out & then use command "kill -2 PID" with the pid of process
//then in handler it print the pid of bash from where kill command 
//is issued
