/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int in;     // integer
    int result;
    // char ch = 'A';
  

/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9453;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: Client");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    printf("Please key in an integer：");
    scanf("%d", &in);

    write(sockfd, &in, sizeof(int));
    read(sockfd, &in, sizeof(int));

    if (in == 1)
        printf("Result from Server：數字'是質數'\n");
    else
        printf("result from server：數字'不是質數'\n");

    close(sockfd);
    exit(0);
}
