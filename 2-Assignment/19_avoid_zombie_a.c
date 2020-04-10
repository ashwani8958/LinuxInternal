#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int flag;

void handler(int arg)
{
	flag = arg;
	printf("Inside handler\n");
	sleep(15);
	wait(NULL);
	sleep(15);
}


int main()
{
	struct sigaction act, oldact;
	pid_t pid;
	
	memset(&act, 0, sizeof(act));

	act.sa_handler = handler;

	sigaction(SIGCHLD, &act, &oldact);

	pid = fork();

	if(pid)
	{
		//while(!flag) | wait(NULL);
		while(!flag);

	}

	else
	{
		sleep(9);
	}

	return 0;
}
