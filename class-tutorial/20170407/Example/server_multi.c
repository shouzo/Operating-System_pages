/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	pthread_t a_thread;
	void *thread_result;
	int res;

/*  Create an unnamed socket for the server.  */

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = 9734;
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

	listen(server_sockfd, 5);
	while(1) {

        	printf("Server waiting...\n");

/*  Accept a connection.  */

		client_len = sizeof(client_address);
	    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		
		res = pthread_create(&a_thread, NULL, thread_function, (void*)(long)client_sockfd);
		if (res != 0) {
			perror("Thread creation failed");
  		    exit(EXIT_FAILURE);
		}
    }
}


void *thread_function(void *arg) {
	char ch;
	int client_sockfd = (long)arg;

    read(client_sockfd, &ch, 1);
    printf("Client_fd = %d, rec = %c\n", client_sockfd, ch);
    ch++;
	sleep(5);
    write(client_sockfd, &ch, 1);
    close(client_sockfd);
	pthread_detach(pthread_self());
	pthread_exit(0);
}
