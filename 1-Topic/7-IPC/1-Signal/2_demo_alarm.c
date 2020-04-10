#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//Declare global variable, its value will be change upon calling
//alarm function
sig_atomic_t sig;

//Alarm Handler
void handler(int arg)
{
	//Set the value of "sig"
	sig = 1;
}

int main(int argc , char *argv[])
{
	unsigned sec, time;
	int option;
#if 1
	if(argc < 2 || argc >= 3)
	{
		printf("ERROR IN GIVING COMMAND LINE ARGUMENTS\n ./a.out 3\n");
		exit(-1);
	}

	//Convert string to interger
	time = atoi(argv[1]);

	//Changing the default action of SIGALRM function
	signal(SIGALRM, handler);

	//call
	alarm(time);

	//print alarm occured
	printf("Alarm occured\n");

	while(1)
	{
		if(sig == 1)
		{
			printf("Choose option\n1.Snooze\n2.Exit\nchoose option: ");
			scanf("%d", &option);
			if(option == 1)
			{
				alarm(5);
				printf("Alarm occured\n");
				sig = 0;
			}
			else
			{
				exit(1);
			}
		}
	}
#endif

#if 0
	printf("sec: %u\n",sec);

	sleep(4);

	sec = alarm(10);

	printf("sec: %u\n",sec);

	pause();
#endif
	return 0;
}
