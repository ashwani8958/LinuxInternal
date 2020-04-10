

#include <stdio.h>
#include <pthread.h>

//structure
struct fact
{
	int lower_limit;
	int upper_limit;
};

typedef struct fact Fact; 

//thread1
void *fact_1 (void *arg)
{
	Fact *ptr = arg;

	long long  int res = 1;
	
	//run from lower limit to upper limit
	for(int i = ptr->lower_limit; i <= ptr->upper_limit; i++)
	{
		res = res * i;
	}
	return (void *)res;

}

int main()
{
	pthread_t t_id1, t_id2, t_id3;
	long long int result, result1, result2, result3;
	int num;

	Fact Data1, Data2, Data3;
	
	printf("Enter the number to find the factorial\n");

	scanf("%d", &num);

	int x = 0;

	x = num/3;
	
	//divide the number among three threads
	Data1.upper_limit = num;
	Data1.lower_limit = num - x;

	Data2.upper_limit = num - x - 1;
	Data2.lower_limit = num - x - x;

	Data3.upper_limit = num - x- x - 1;
	Data3.lower_limit = 1;
	
	//create threads
	pthread_create(&t_id1, NULL, fact_1, (void *)&Data1);
	pthread_create(&t_id2, NULL, fact_1, (void *)&Data2);
	pthread_create(&t_id3, NULL, fact_1, (void *)&Data3);
	
	//wait for the thread to finish
	pthread_join(t_id1, (void**)&result1);
	pthread_join(t_id2, (void**)&result2);
	pthread_join(t_id3, (void**)&result3);
	
	//calculate the result from all three
	result = result1 * result2 * result3;
	
	printf("result = %lld\n", result);
	return 0;
}
