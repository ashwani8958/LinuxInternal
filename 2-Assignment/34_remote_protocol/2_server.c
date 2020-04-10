

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
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

	struct sockaddr_in serv_addr, client_addr;
	char serv_buffer[20] = {'\0'};
	
	socklen_t len = sizeof(client_addr);
	printf("Server is waiting\n");

	//create a tcp socket
	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//bind it to a particular IP address & port
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(SERVER_PORT);
	bind(sock_fd , (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	//try to get the actual data
	recvfrom(sock_fd, (void *)serv_buffer, SERVER_BUFF, 0, (struct sockaddr *)&client_addr, &len);

	//print the data received from the client
	printf("Here is the client data : %s\n", serv_buffer);
	
	

	int fds[2];
	
	//creating a pipe
	pipe(fds);

	pid_t pid = fork();
	
	//parent process
	if(pid)
	{
		wait(NULL);
		//close write ned of the pipe
		close(fds[1]);
		char buffer1[500] = {'\0'};
		
		//read from the pipe
		read(fds[0], buffer1, sizeof(buffer1));

		//printf("%s\n", buffer1);
		
		//send it to the client
		sendto(sock_fd, buffer1, sizeof(buffer1), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));


	}
	//child process
	else
	{
		//close the read end of the pipe
		close(fds[0]);
		char *arr[8];
		char buffer[10] = {'\0'};
		
		int i = 0;
		int j = 0;
		int k = 0;
		
		//separating the command
		while(serv_buffer[i])
		{
			//fill every element of the command in the arr
			while(serv_buffer[i] != ' ' && serv_buffer[i] != '\0')
			{
				buffer[j] = serv_buffer[i];
				j++;
				i++;
			}
			buffer[j] = '\0';
			j = 0;

			int len = strlen(buffer);
			
			//fill in the arr
			arr[k] = malloc(sizeof(char) * (len + 1));

			strcpy(arr[k] , buffer);

			i++;
			k++;

		}
		arr[k] = NULL;
		
		//write to the pipe the stdout
		dup2(fds[1], 1);

		//new process
		execvp(arr[0], arr);
		printf("not successful\n");

	}
	//close the sockets
	close(data_sock_fd);
	close(sock_fd);

}

