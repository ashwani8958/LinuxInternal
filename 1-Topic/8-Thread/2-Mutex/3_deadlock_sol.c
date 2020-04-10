#include <stdio.h>
#include <unistd.h>
#define __USE_GNU
#include <pthread.h>

pthread_mutex_t mutex /*= PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP*/;

void fun(void)
{
	if(pthread_mutex_lock(&mutex) == 35 /*EDEADLCK*/)
	{
		printf("I (%lu) already locked the mutex\n", pthread_self());
	}
}

void *thrd_func(void *args)
{
	printf("%lu locking mutex\n", pthread_self());

	pthread_mutex_lock(&mutex);

	printf("%lu locked mutex\n", pthread_self());

	fun();

	sleep(2);

	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t tid1, tid2, tid3;

#if 0
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&mutex, &attr);
#endif

	pthread_create(&tid1, NULL, thrd_func, NULL);
	pthread_create(&tid3, NULL, thrd_func, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid3, NULL);

	return 0;
}
