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
#define SERVER_PORT 7000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20

int main()
{
	int sock_fd, data_sock_fd, buffer_len, var1, var2;
	struct sockaddr_in serv_addr;
	char serv_buffer[SERVER_BUFF] = {'\0'}, *str;

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

	//if there are any, accept and create a new data socket
	data_sock_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);

	//Try to get some actual data from client
	recv(data_sock_fd, (void *)serv_buffer, SERVER_BUFF, 0);

	//print the data received from client
	printf("Here is the client data: %s\n", serv_buffer);

	str = strtok(serv_buffer, "+");
	var1 =  atoi(str);
	str = strtok(NULL, "+");
	var2 = atoi(str);

	var2 = var1 + var2;

	sprintf(serv_buffer, "%d", var2);

	send(data_sock_fd, (void *)serv_buffer, SERVER_BUFF, 0);
	
	//close the socket 
	close(data_sock_fd);
	close(sock_fd);
}
