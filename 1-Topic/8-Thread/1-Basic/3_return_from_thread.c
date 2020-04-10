#include <pthread.h>
#include <stdio.h>

struct sum_data
{
	int num1;
	int num2;
};

typedef struct sum_data sumData;

/*find the sum of 2 numbers and print the result */
void *sum_thread(void *data)
{
	sumData *pdata = data;
	
	long int sum = pdata->num2 + pdata->num1;
	return (void *)sum;

}
int main()
{
	pthread_t thread_id1, thread_id2;
	sumData data = {10, 20};
	long int result;
	pthread_create (&thread_id1, NULL, &sum_thread, &data);
	pthread_join(thread_id1, (void **)&result);
	printf("SUM = %ld\n", result);

	
	return 0;
}

