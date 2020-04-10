#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//int file_count = 0;

#if 1
typedef struct 
{
	int flags_b;
	int flags_w; 
	int flags_l;
} get_options;

#endif

#if 0
struct get_options
{
	int flags_b;
	int flags_w; 
	int flags_l;
} ;
#endif

typedef enum 
{
	no_arg,
	arg
} arg_check;



int find_option(int argc, char *argv[], get_options *ptr);
void count(int *line, int *word, int *byte, int read_source);
void print_count(get_options optional_argu, int *line, int *word, int *byte, int *line_1, int *word_1, int *byte_1, char file[20]);

#endif

