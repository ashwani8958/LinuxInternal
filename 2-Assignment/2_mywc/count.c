#include "main.h"

extern int file_count;

void count(int *line, int *word, int *byte, int read_source)
{
	file_count++;

	char a[1];
	int flag =1;
	
	/*
	 Get from bufer until
	*/
	while( (read(read_source, &a, 1)) != 0 )
	{
		//For line count
		if( a[0] == '\n')
		{
			flag =1;
			(*line)++;
		}
		/*
		For word count and flag set 
		for identify non printable between
		characters
		*/
		else if (( isprint(a[0]) != 0 ) && (flag != 0) && isblank(a[0]) == 0 ) 
		{	
			flag = 0;
			(*word)++;
		}

		//Inorder for printable
		else if (isgraph(a[0]) == 0)
			flag = 1;

		(*byte)++;
	}
}
