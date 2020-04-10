#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_entry_function(void *argv)
{
	int i, res;
	
	res = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);

	for(i = 0; i< 10; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}

	res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	return NULL;
}

int main()
{
	pthread_t thread_id;
	pthread_attr_t attr;
	int loopindex, res;



	//now create a thread with this attribute
	pthread_create(&thread_id, NULL, thread_entry_function,NULL);
	
	sleep(3);
	res = pthread_cancel(thread_id);
	//NO need to call pthread_join here, main thread can continue its job

						/* MAIN JOIN */
	

	pthread_join(thread_id,NULL);
}
