#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20000

int main(int argc, char *argv[])
{
	int sock_fd, data_sock_fd, buffer_len;
	int i;
	struct sockaddr_in serv_addr;
	socklen_t addrlen = sizeof(serv_addr);
	char serv_buffer[SERVER_BUFF] = {'\0'};
	char buffer[SERVER_BUFF] = {'\0'};

	printf("client is sending data...\n");

	//create a UDP socket
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serv_addr.sin_port = htons(SERVER_PORT);

	strcpy(serv_buffer, argv[1]);
	for(i = 1; i < argc - 1; i++)
	{
		strcat(serv_buffer + strlen(argv[i]), " ");
		strcat(serv_buffer + strlen(argv[i]), argv[i + 1]);
	}

	sendto(sock_fd, (void *)serv_buffer, SERVER_BUFF, 0, (struct sockaddr *)&serv_addr, addrlen);


	//Try to get some actual data from client
	recvfrom(sock_fd, (void *)buffer, SERVER_BUFF, 0, (struct sockaddr *)&serv_addr, &addrlen);
	
	printf("out %s\n", buffer);

	//close the socket 
	close(sock_fd);
}
