#include "main.h"

void one_command(char *buff[MAX])
{
	execvp(buff[0], buff);
}
