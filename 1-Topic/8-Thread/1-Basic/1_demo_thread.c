#include <pthread.h>
#include <stdio.h>
/*prints x's to stderr. the psatameter is unused. doesn't return. */
void *print_xs(void *arg)
{
	while (1)
	{
		fputc ('X', stderr);
	}
	return NULL;
}
int main()
{
	pthread_t thread_id;
	/* create new thread. the new thread will run the print X's function */
	pthread_create (&thread_id, NULL, print_xs, (void *)NULL);
	while(1)
	{
		fputc ('O', stderr);
	}
return 0;
}

