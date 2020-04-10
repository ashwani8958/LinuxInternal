#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_DNS_PORT 6000
#define SERVER_LENGTH 10
#define SERVER_BUFF 20

int main()
{
	int sock_fd, sock_fd1, data_sock_fd, buffer_len;
	struct sockaddr_in serv_addr;
	char serv_buffer[SERVER_BUFF];// serv_port[SERVER_BUFF];
	int var1, var2, serv_port, opt = 3;
	char ch1[sizeof(int)*8], ch2[sizeof(int)*8];

	printf("Enter 1st number: ");
	scanf("%d", &var1);
	printf("Enter 2st number: ");
	scanf("%d", &var2);

	while(opt != 0)
	{
		switch(opt)
		{
#if	1
			case 3:
			{
				sprintf(ch1, "%d", var1);
				sprintf(ch2, "%d", var2);
				strcat(ch1, "+");
				strcat(ch1,ch2);
				strcpy(ch2,ch1);

				printf("client is sending data...\n");
		//connect to DNS SERVER
				//create a TCP socket
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				//Bind it to a particular IP address & port
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(SERVER_DNS_PORT);

				//connect
				connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				


				//Try to get some actual data from client
				send(sock_fd, (void *)ch1, SERVER_BUFF, 0);
				recv(sock_fd, (void *)&serv_port, 32, 0);

		//connect to add server
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(serv_port);


				int r;
				r = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				if( r == -1)
				{
					perror("error: ");
					exit(0);
				}

				send(sock_fd, (void *)ch2, SERVER_BUFF, 0);
				recv(sock_fd, (void *)ch1, SERVER_BUFF, 0);

				printf("%d + %d = %s\n", var1, var2, ch1);
			}
#endif

#if	1
			case 2:
			{
				ch1[32] = '\0';
				ch2[32] = '\0';
				sprintf(ch1, "%d", var1);
				sprintf(ch2, "%d", var2);
				strcat(ch1, "*");
				strcat(ch1,ch2);
				strcpy(ch2,ch1);

				printf("client is sending data...\n");
		//connect to DNS SERVER
				//create a TCP socket
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				//Bind it to a particular IP address & port
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(SERVER_DNS_PORT);

				//connect
				connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				


				//Try to get some actual data from client
				send(sock_fd, (void *)ch1, SERVER_BUFF, 0);
				recv(sock_fd, (void *)&serv_port, 32, 0);

		//connect to add server
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(serv_port);


				int r;
				r = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				if( r == -1)
				{
					perror("error: ");
					exit(0);
				}

				send(sock_fd, (void *)ch2, SERVER_BUFF, 0);
				recv(sock_fd, (void *)ch1, SERVER_BUFF, 0);

				printf("%d * %d = %s\n", var1, var2, ch1);
			}
#endif

#if	1
			case 1:
			{
				sprintf(ch1, "%d", var1);
				sprintf(ch2, "%d", var2);
				strcat(ch1, "/");
				strcat(ch1,ch2);
				strcpy(ch2,ch1);

				printf("client is sending data...\n");
		//connect to DNS SERVER
				//create a TCP socket
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				//Bind it to a particular IP address & port
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(SERVER_DNS_PORT);

				//connect
				connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				


				//Try to get some actual data from client
				send(sock_fd, (void *)ch1, SERVER_BUFF, 0);
				recv(sock_fd, (void *)&serv_port, 32, 0);

		//connect to add server
				sock_fd = socket(AF_INET, SOCK_STREAM, 0);
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
				serv_addr.sin_port = htons(serv_port);


				int r;
				r = connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
				if( r == -1)
				{
					perror("error: ");
					exit(0);
				}

				send(sock_fd, (void *)ch2, SERVER_BUFF, 0);
				recv(sock_fd, (void *)ch1, SERVER_BUFF, 0);

				printf("%d / %d = %s\n", var1, var2, ch1);
			}
#endif
		}
		--opt;

	}
	//close the socket 
	close(sock_fd);
}
