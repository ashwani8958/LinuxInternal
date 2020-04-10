#include "main.h"

extern int file_count;
extern int num;

void print_count(get_options optional_argu, int *line, int *word, int *byte, int *line_1, int *word_1, int *byte_1, char file[20])
{

	if( (!optional_argu.flags_l && !optional_argu.flags_w && !optional_argu.flags_b) ||
		(optional_argu.flags_l && optional_argu.flags_w && optional_argu.flags_b))
	{
		printf("\t%d\t%d\t%d\t%s\t\n", *line - *line_1, *word - *word_1, *byte - *byte_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%d\t%d\t%s\n",*line, *word, *byte, "total");
		}
	}

	else if(optional_argu.flags_b && optional_argu.flags_l)
	{
		printf("\t%d\t%d\t%s\n", *line - *line_1, *byte - *byte_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%d\t%s\n",*line, *byte, "total");
		}
	}

	else if(optional_argu.flags_b && optional_argu.flags_w)
	{
		printf("\t%d\t%d\t%s\n", *word - *word_1, *byte - *byte_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%d\t%s\n", *word, *byte, "total");
		}
	}

	else if(optional_argu.flags_w && optional_argu.flags_l)
	{
		printf("\t%d\t%d\t%s\n", *line - *line_1, *word - *word_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%d\t%s\n",*line, *word, "total");
		}
	}

	else if (optional_argu.flags_l)
	{
		printf("\t%d\t%s\n", *line - *line_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%s\n",*line, "total");
		}
	}

	else if (optional_argu.flags_b)
	{
		printf("\t%d\t%s\n", *byte - *byte_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%s\n", *byte, "total");
		}
	}

	else if (optional_argu.flags_w)
	{
		printf("\t%d\t%s\n", *word - *word_1, file);
		if(file_count == num && file_count != 1)
		{
			printf("\t%d\t%s\n",*word, "total");
		}
	}
}
