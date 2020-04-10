#include "main.h"

int find_option(int argc, char *argv[], get_options *ptr)
{
	int opt;
	

	while ((opt = getopt(argc, argv, "wbl")) != -1) 
	{
		switch (opt) 
		{
			case 'b':
			ptr->flags_b = 1;
			break;

			case 'w':
			ptr->flags_w = 1;
			break;

			case 'l':
			ptr->flags_l = 1;
			break;

			default: /* '?' */
			printf("Pass only vaild option\n./my_wc -l -w -b\n");
			exit(EXIT_FAILURE);
        }
    }

	if (optind >= argc) 
    {
    	return no_arg;
    }

    else
	{
		return arg;
	}

}
