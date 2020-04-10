
#include <stdio.h>
#include <pthread.h>

int x;
pthread_mutex_t mut;

void *thread_function(void *arg)
{
	while(1)
	{	
		pthread_mutex_lock(&mut);
		x = 5;
		x += 10;
		printf("%d\n", x);
		pthread_mutex_unlock(&mut);
	}
	return NULL;
}

int main(void)
{
	pthread_t thread_1, thread_2;

	pthread_mutex_init(&mut, NULL);

	pthread_create(&thread_1, NULL, thread_function, NULL);
	pthread_create(&thread_2, NULL, thread_function, NULL);

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	return 0;
}
