#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "192.168.43.37"
#define SERVER_PORT 5000
#define SERVER_LENGTH 30
#define SERVER_BUFF 60

int main()
{
	int sock_fd, data_sock_fd, buffer_len;
	struct sockaddr_in serv_addr;
	char serv_buffer[SERVER_BUFF] = {'\0'};
	pid_t pid;

	printf("Server is waiting...\n");

	//create a TCP socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	//Bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serv_addr.sin_port = htons(SERVER_PORT);
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

			exit(0);
		}
	}
	//close the socket 
	close(data_sock_fd);
	close(sock_fd);
}
