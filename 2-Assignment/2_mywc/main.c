#include "main.h"

//Global variable
int file_count;
int num;

int main(int argc, char *argv[])
{
	//Declare variable
	get_options optional_argu;
	int check_arg, i, file_indx;
	int byte = 0, word = 0, line = 0;
	int line_1, word_1, byte_1;
	int arg_count = 0;
	
	//initilsation of variable
	optional_argu.flags_b = 0;
	optional_argu.flags_w = 0;
	optional_argu.flags_l = 0;

	//Call function to check the optional arguments and check either to read from stdin or file
	check_arg = find_option(argc, argv, &optional_argu);
	
	//read from stdin
	if(!check_arg)
	{	
		//initilization of line_1, word_1 and byte_1 work only if multipal file is pass
		line_1 = line;
		word_1 = word; 
		byte_1 = byte;

		//count the no. of line, word, bytes
		count(&line, &word, &byte, 0 );

		//printf no. of line, word, bytes
		print_count(optional_argu, &line, &word, &byte, &line_1, &word_1, &byte_1, "\0");
	}
	
	//read from file
	else if(arg)
	{
		//loop to seprate optional argument and file name
		for(i = 1; i < argc; i++)
			{	
				//seprate optional agrument
				if( !strcmp(argv[i],"-l") || !strcmp(argv[i], "-w") || !strcmp(argv[i],"-b"))
				{
					//variable to count number of optional agrument
					arg_count++;
					continue;
				}
				
				//check for file and open it and count line, byte, words
				else
				{
					//in case of multipal file if find
					line_1 = line;
					word_1 = word; 
					byte_1 = byte;
					
					//for printing total number of line, byte, word
					num = argc - arg_count - 1;
					
					//open file
					file_indx = open(argv[i], O_RDONLY);

					//count number of line, byte and word
					count(&line, &word, &byte, file_indx);

					//print number of line, word and byte
					print_count(optional_argu, &line, &word, &byte, &line_1, &word_1, &byte_1, argv[i]);
					
				}
			}
	}
	
	return 0;
           
}

