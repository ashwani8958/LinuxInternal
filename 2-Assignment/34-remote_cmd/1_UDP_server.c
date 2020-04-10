#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
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
#define SERVER_PORT 5000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20000

int main(int argc, char *argv[])
{
	int sock_fd, data_sock_fd, buffer_len, status;
	struct sockaddr_in serv_addr, client_addr;
	char serv_buffer[SERVER_BUFF];
	char buffer[SERVER_BUFF] = {'\0'};
	char *command[20] = {NULL}, *str;
	int file_fd, i;
	pid_t pid;
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
	
	str = strtok(serv_buffer, " ");	
	command[0] =  str;
	i = 1;
	while(str = strtok(NULL, " "))
	{
		command[i] =  str;
		i++;
	}

	file_fd = open("command_output.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if(file_fd == -1)
	{
		perror("Error in opening file ");
		return -1;
	}

	pid = fork();
	if(pid)
	{
		wait(NULL);
		while(read(file_fd, buffer, 20000) != 0);

	}
	
	else
	{  
		close(1);
		dup(file_fd);

		execvp(command[0], command);
		perror("execvp ");
	}
	
	printf("%s\n", buffer);

	sendto(sock_fd, (void *)buffer, SERVER_BUFF, 0, (struct sockaddr *)&client_addr, addrlen);

	
	//exit(0);
	//print the data received from client

	//close the socket 
	close(data_sock_fd);
	close(sock_fd);
}
