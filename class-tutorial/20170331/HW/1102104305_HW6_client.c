/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 5

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result, n;

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if (result == -1) {
        perror("oops: client!");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    int i, j, tmp = 0, s = SIZE;
    int arr[SIZE] = {4, 7, 1, 8, 3};
    int rec[SIZE] = {0, 0, 0, 0, 0};
    printf("%d\n", s);

    write(sockfd, &s, sizeof(int));
    printf("\noriginal from client - arr[]\n"); 
    for (i = 0; i < SIZE; i++)
    	printf("arr[%d] = %d\n", i, arr[i]);

    write(sockfd, arr, sizeof(arr));
   
   
    read(sockfd, rec, SIZE * sizeof(rec));    
    printf("\nresult from server - rec[]\n");

    for (i = 0; i < SIZE; i++)
        printf("rec[%d] = %d\n", i, rec[i]); 
    

    close(sockfd);
    exit(0);
}
