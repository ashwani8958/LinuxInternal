#include <pthread.h>
#include <stdio.h>

void *thread_entry_function(void *argv)
{
	int i;

	for(i = 0; i< 10; i++)
	{
		printf("%d\n", i);
	}
	return NULL;
}

int main()
{
	pthread_t thread_id;
	pthread_attr_t attr;
	int loopindex;

	//initialize the attribute
	pthread_attr_init(&attr);

	//set the attribute for a detached thread
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	//now create a thread with this attribute
	pthread_create(&thread_id, &attr, thread_entry_function,NULL);
	pthread_attr_destroy(&attr);

	//NO need to call pthread_join here, main thread can continue its job

						/* MAIN JOIN */
	
	loopindex = 20000000;
	while(loopindex--);

}
