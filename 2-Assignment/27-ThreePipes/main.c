#include "main.h"


int main(int argc, char *argv[])
{
	

	int status, pipe_count = 0, arg_index, count_arg = 0, index;

	char *command_1[MAX];
	char *command_2[MAX];
	char *command_3[MAX];

	//Loop to count the number of pipes
	for(arg_index = 1; argv[arg_index]; arg_index++)
	{
		if(!strcmp(argv[arg_index], "|"))
		{
			++pipe_count;
		}
	}
	
	//Store 1st Command in buffer
	index = 0;
	for( arg_index = 1; argv[arg_index] && strcmp(argv[arg_index], "|"); arg_index++)
	{
		command_1[index] = argv[arg_index];
		index++;
	}
	command_1[index] = NULL;


	//store 2nd command in buffer
	arg_index++;
	index = 0;
	for( ; argv[arg_index] && strcmp(argv[arg_index], "|"); arg_index++)
	{
		command_2[index] = argv[arg_index];
		index++;
	}
	command_2[index] =  NULL;

	//store 3rd command in buffer
	arg_index++;
	index = 0;
	for( ; argv[arg_index]; arg_index++)
	{
		command_3[index] = argv[arg_index];
		index++;
	}
	command_3[index] =  NULL ;


	//ERROR CHECKING
	if(pipe_count == 1 && !argv[3] )
	{
		printf("ERROR: Argument is expected after the first pipe\n");
		return -1;
	}

	if(pipe_count == 2 && !argv[5] )
	{
		printf("ERROR: Argument is expected after the second pipe\n");
		return -1;
	}
	if(pipe_count == 0)
	{
		one_command(command_1);
	}

	if(pipe_count == 1)
	{
		two_command(command_1, command_2);
	}

	if(pipe_count == 2)
	{
		three_command(command_1, command_2, command_3);
	}
	
	return 0;
}
