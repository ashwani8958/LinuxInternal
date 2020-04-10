#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void handler(int arg)
{
	printf("\nSIGINT received\n");
}

int main()
{
	struct sigaction act, oldact;

	memset(&act, 0, sizeof(act));

	act.sa_handler = handler;

	sigaction(SIGINT, &act, &oldact);

	pause();

	return 0;
}
