/* man sigsetops */

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
sig_atomic_t flag;
int count = 3;

void handler(int signal_number, siginfo_t *info, void *ptr)
{
#if 0
	//print the pid 0 because it is return by kernal
	if(signal_number == SIGINT)
	{
		flag = 1;
	}
	if(signal_number == SIGQUIT)
	{
		flag = 2;
	}
	if(signal_number == SIGALRM)
	{
		flag = 3;
	}
#endif
	flag = signal_number;
}

int main()
{
	struct sigaction act, oldact;
	pid_t pid;

	memset(&act, 0, sizeof(act));

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;


	sigaction(SIGINT, &act, &oldact);
	sigaction(SIGQUIT, &act, &oldact);
	sigaction(SIGALRM, &act, &oldact);

	pid = fork();

	if(pid)
	{
		while(count--)
		{
			while(!flag);

				if(flag == SIGINT )
				printf("SIGINT is received\n");
				if(flag == SIGQUIT )
				printf("SIGQUIT is received\n");
				if(flag == SIGALRM )
				printf("SIGALRM is received\n");
				flag = 0;

		}
	}

	else
	{
		sleep(1);
		kill(getppid(), SIGQUIT);
		sleep(1);
		kill(getppid(), SIGINT);
		sleep(1);
		kill(getppid(), SIGALRM);
	}

	return 0;
}


//run ./a.out & then use command "kill -2 PID" with the pid of process
//then in handler it print the pid of bash from where kill command
//is issued
