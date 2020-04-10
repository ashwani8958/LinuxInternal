#include "main.h"

int copy_content(int fd_r, int fd_w)
{
	char buffer[MAX];
	int bytes, w_bytes;

	do
	{
		bytes = read(fd_r, buffer, MAX);

		if(bytes == -1)
		{
			perror("read");
			return -1;
		}
				
		w_bytes = write(fd_w, buffer, bytes);

		if(w_bytes == -1)
		{
			perror("write");
			return -1;
		}

	}while(bytes == MAX);
}
