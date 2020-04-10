#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20

int main()
{
	int sock_fd, data_sock_fd, buffer_len;
	struct sockaddr_in serv_addr, client_addr;
	char serv_buffer[SERVER_BUFF];
	socklen_t addrlen = sizeof(client_addr);

	printf("Server is waiting...\n");

	//create a UDP socket
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	//Bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	
	//inet_ntoa(binary value) to string
	//kernal choice the auto IP adderess
	//serv_addr.sin_addr.s_addr = INADDR_ANY;

	//LOOPBACK IP
	//serv_addr.sin_addr.s_addr = INADDR_LOOPBACK;


	serv_addr.sin_port = htons(SERVER_PORT);
	bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));


	//Try to get some actual data from client
	recvfrom(sock_fd, (void *)serv_buffer, SERVER_BUFF, 0, (struct sockaddr *)&client_addr, &addrlen);

	//print the data received from client
	printf("Here is the client data: %s\n", serv_buffer);

	//close the socket 
	close(data_sock_fd);
	close(sock_fd);
}
