

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//structure
struct fact
{
	int lower_limit;
	int upper_limit;
	int *array;
};

typedef struct fact Fact; 

long int global_sum;
int global_max;
pthread_mutex_t mut;

//thread1
void *fact_1 (void *arg)
{
	Fact *ptr = arg;

	long int sum = 0;

	int max = ptr->array[ptr->lower_limit];

	//run from lower limit to upper limit
	for(int i = ptr->lower_limit; i <= ptr->upper_limit; i++)
	{
		sum = sum + ptr->array[i];
	}
	
	//lock
	pthread_mutex_lock(&mut);
	global_sum = global_sum + sum;
	//unlock
	pthread_mutex_unlock(&mut);

	//find max 
	for(int i = ptr->lower_limit; i <= ptr->upper_limit; i++)
	{
		if(ptr->array[i] > max)
		{
			max = ptr->array[i];
		}
	}
	
	//lock
	pthread_mutex_lock(&mut);
	if(global_max == 0)
	{
		global_max = max;
	}
	else
	{
		if(max > global_max)
		{
			global_max = max;
		}
	}
	//unlock
	pthread_mutex_unlock(&mut);


	return NULL;

}

int main()
{
	pthread_t t_id1, t_id2, t_id3, t_id4, t_id5;
	int num;
	
	pthread_mutex_init(&mut, NULL);
	Fact Data[5];
	
	printf("Enter the number of elements\n");

	scanf("%d", &num);
	
	int *array = (int *)malloc(sizeof(int) * num);

	printf("Enter the elements\n");
	for(int i = 0;  i < num; i++)
	{
		scanf("%d", &array[i]);
	}
	int x = 0;

	x = num/5;
	int y = 0;
	//divide the number among three threads
	Data[4].upper_limit = num - 1;
	Data[4].lower_limit = num - x;
	Data[4].array = array;
	
	
	Data[3].upper_limit = num - x - 1;
	Data[3].lower_limit = num - x - x ;
	Data[3].array = array;
	
	Data[2].upper_limit = num - x -x- 1;
	Data[2].lower_limit = num - x-x-x ;
	Data[2].array = array;

	Data[1].upper_limit = num - x -x-x- 1;
	Data[1].lower_limit = num - x-x-x-x ;
	Data[1].array = array;

	Data[0].upper_limit = num - x -x-x-x- 1;
	Data[0].lower_limit = 0;
	Data[0].array = array;

	//create threads
	pthread_create(&t_id1, NULL, fact_1, (void *)&Data[0]);
	pthread_create(&t_id2, NULL, fact_1, (void *)&Data[1]);
	pthread_create(&t_id3, NULL, fact_1, (void *)&Data[2]);
	pthread_create(&t_id4, NULL, fact_1, (void *)&Data[3]);
	pthread_create(&t_id5, NULL, fact_1, (void *)&Data[4]);
	
	//wait for the thread to finish
	pthread_join(t_id1, NULL);
	pthread_join(t_id2, NULL);
	pthread_join(t_id3, NULL);
	pthread_join(t_id4, NULL);
	pthread_join(t_id5, NULL);
	
	//calculate the result from all three
	
	printf("Sum of all elements : %ld\n", global_sum);
	printf("Max of all elements : %d\n", global_max);
	return 0;
}
