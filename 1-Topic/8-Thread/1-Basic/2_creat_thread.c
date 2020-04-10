#include <pthread.h>
#include <stdio.h>
struct print_data
{
	char ch;
	int count;
};
typedef struct print_data printData;
/*prints character, count times */
void *print_xs(void *data)
{
	printData *pdata = data;

	while ((pdata->count)--)
	{
		fputc (pdata->ch, stderr);
	}
	return NULL;
}
int main()
{
	pthread_t thread_id1, thread_id2;
	printData data1 = {'A', 5000};
	printData data2 = {'B', 2000};

	/* create new thread. the new thread will run the print X's function */
	pthread_create (&thread_id1, NULL, &print_xs, &data1);
	pthread_create (&thread_id2, NULL, &print_xs, &data2);
	
	//like wait(it will wait till thread finish)
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	
return 0;
}

