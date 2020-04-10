//Pressing Ctrl-C causes the SIGINT
//Pressing Ctrl-\ generates a SIGQUIT

#include <stdio.h>
#include <signal.h>

void sig_handler(int arg)
{
	if(arg == SIGINT)
	{
		printf("SIGINT is recieved\n");
	}

	else if(arg == SIGQUIT)
	{
		printf("SIGQUIT is recevied\n");
	}
}

int main()
{
	//sighandler_t ptr;
	//Registering new handler function for sigint

	//ptr =
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	while(1);
}
