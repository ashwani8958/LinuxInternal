#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_DNS_PORT 6000
#define SERVER_ADD_PORT 7000
#define SERVER_MUL_PORT 8000
#define SERVER_DIVIDE_PORT 9000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20

int main()
{
	int sock_fd, data_sock_fd, buffer_len, var1, var2, plus, mul, divide;
	struct sockaddr_in serv_addr;
	char serv_buffer[SERVER_BUFF], *str, ch; //serv_port[SERVER_BUFF];
	int serv_port;
	pid_t pid;
	plus = 0;
	mul = 0;
	divide = 0;

	printf("Server is waiting...\n");

	//create a TCP socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	//Bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serv_addr.sin_port = htons(SERVER_DNS_PORT);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	//wait and listen for incoming connection
	listen(sock_fd, SERVER_LENGTH);

	while(1)
	{

	//if there are any, accept and create a new data socket
	data_sock_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);
	
	pid = fork();

		if(pid == 0)
		{
			//Try to get some actual data from client
			recv(data_sock_fd, (void *)serv_buffer, SERVER_BUFF, 0);

			//print the data received from client
			printf("Here is the client data: %s\n", serv_buffer);

			str = serv_buffer;

			while(*str != '\0')
			{
				ch = *str++;

				if(ch == '+')
					plus = 1;
				else if(ch == '*')
					mul = 1;
				else if(ch == '/')
					divide = 1;
				else if( plus == 1 || mul == 1 || divide == 1)
					break;
			}

			if(plus == 1)
			{
				//sprintf(serv_port, "%d", SERVER_ADD_PORT);
				serv_port = SERVER_ADD_PORT;

				send(data_sock_fd, (void *)&serv_port, 32, 0);
			}


			if(mul == 1)
			{
				//sprintf(serv_port, "%d", SERVER_MUL_PORT);
				serv_port = SERVER_MUL_PORT;

				send(data_sock_fd, (void *)&serv_port, SERVER_BUFF, 0);
			}

			if(divide == 1)
			{
				//sprintf(serv_port, "%d", SERVER_DIVIDE_PORT);
				serv_port = SERVER_DIVIDE_PORT;

				send(data_sock_fd, (void *)&serv_port, SERVER_BUFF, 0);
			}
			exit(0);
		}
	}
	//close the socket 
	close(data_sock_fd);
	close(sock_fd);
}
