

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//structure
struct fact
{
	int *array1;
	int *array2;
	int rows;
	int col_count;
};

typedef struct fact Fact; 

long int global_sum;
int global_max;
pthread_mutex_t mut;

//thread1
void *fact_1 (void *arg)
{
	Fact *ptr = arg;

//	for(int i = );

	
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
	pthread_t *t_id;
	int rows, col;
	
	pthread_mutex_init(&mut, NULL);
	Fact **Data;
	
	printf("Enter the number of rows and columns\n");

	scanf("%d %d", &rows, &col);

	if(rows != col)
	{
		return -1;
	}

	t_id = malloc(sizeof(pthread_t) * rows);
	
	Data = malloc(sizeof(Fact) * rows);

	
	int **array1 = malloc(sizeof(int *) * rows);
	int **array1 = malloc(sizeof(int *) * rows);
	int *ptr;

	printf("Enter the elements\n");
	for(int i = 0;  i < rows; i++)
	{
		array1[i] = malloc(sizeof(int) *col);
		ptr = array1[i];
		for(int j = 0; j < col; j++)
		{
			scanf("%d", &ptr[j]);
		}
	}
	for(int i = 0;  i < rows; i++)
	{
		array2[i] = malloc(sizeof(int) *col);
		ptr = array2[i];
		for(int j = 0; j < col; j++)
		{
			scanf("%d", &ptr[j]);
		}
	}
	
	for(int i = 0; i < rows; i++)
	{
		Data[i]->col_count = col;
		Data[i]->rows = i;
		Data[i]->array1 = array1;
		Data[i]->array2 = array2;

		pthread_create(&t_id[i], NULL, fact_1, (void *)Data[i]);
	}
	
	for(int i = 0; i < rows ; i++)
	{
		pthread_join(t_id[i], NULL);
	}
	
	//calculate the result from all three
	
	printf("Sum of all elements : %ld\n", global_sum);
	printf("Max of all elements : %d\n", global_max);
	return 0;
}
