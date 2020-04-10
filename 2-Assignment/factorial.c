#include<stdio.h>
#include<pthread.h>
#define MAX 100

unsigned long int fact = 1;
int part = 1;

pthread_mutex_t mut;

void* factorial(void *arg )
{
	int i, fact_part;

	pthread_mutex_lock(&mut);
	fact_part = part++;

	for(i = fact_part * (*(int *)arg / *(int *)arg); i < (fact_part + 1) * (*(int *)arg / *(int *)arg); i++) 
	{
		fact = fact * i;
	}	

	pthread_mutex_unlock(&mut);
}
int main()
{
	int count, num;
	pthread_t thread_id[MAX];
	printf("enter the number: ");
	scanf("%d", &num);
	for(count = 1; count <= num; count++)
	{
		pthread_create(&thread_id[count], NULL, factorial, (void*)&num);
	}

	for(count = 1; count <= num; count++)
	{
		pthread_join(thread_id[count], NULL);
	}

	printf("fact %lu\n", fact);
	return 0;
}
