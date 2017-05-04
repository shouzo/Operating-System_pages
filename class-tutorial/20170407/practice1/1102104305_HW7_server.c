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
        printf("\nServer waiting...\n");

/*  Accept a connection.  */

        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

        res = pthread_create(&a_thread, NULL, thread_function, (void *)(long)client_sockfd);
        
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
    }
}




/*  We can now read/write to client on client_sockfd.  */
void *thread_function(void *arg) {
    int i, j, tmp = 0, get_n;
    int client_sockfd = (long)arg;
    int *buf;
        
    read(client_sockfd, &get_n, sizeof(get_n));
    buf = (int *) malloc(get_n * sizeof(int));
    read(client_sockfd, buf, get_n * sizeof(int));
    printf("sort arr[%d] from client:\n", get_n);
     
    for (i = 0; i < get_n; i++) {
        for (j = 0; j < get_n; j++) {
            if (buf[i] < buf[j]) {
                tmp = buf[i];
                buf[i] = buf[j];
                buf[j] = tmp;
            }
        }
    }


    for (i = 0; i < get_n; i++)
        printf("arr[%d] = %d\n", i, buf[i]);

    // sleep(3);
    write(client_sockfd, buf, get_n * sizeof(buf));
    close(client_sockfd);
    pthread_detach(pthread_self());
    pthread_exit(0);
}

