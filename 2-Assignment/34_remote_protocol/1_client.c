

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20

int main()
{
	int sock_fd, data_sock_fd, buffer_len;

	struct sockaddr_in serv_addr;

	socklen_t len = sizeof(serv_addr);
	char serv_buffer[25] = {'\0'};
	printf("Client\n");

	//create a tcp socket
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(SERVER_PORT);
	printf("Enter the command\n");

	scanf("%[^\n]s", serv_buffer);
	
	
	//send the command to be executed
	sendto(sock_fd, (void*)serv_buffer, sizeof(serv_buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	
    	char ch[500] = {'\0'};
	
	//receive the output of the command from the server
	recvfrom(sock_fd, ch, 500, 0, (struct sockaddr *)&serv_addr, &len);

	printf("Result\n");
	printf("%s\n", ch);



	//close the sockets
	close(sock_fd);

}

