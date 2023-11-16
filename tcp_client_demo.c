#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
#define PORT 8080
int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);

    char *message = "Hello from client";
    unsigned char buffer[BUFFER_SIZE] = {'\0'};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1)
    {
        perror("connect()");
        fprintf(stderr, "Please start the server first\n");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    send(sockfd, message, strlen(message), 0);
    printf("Hello message sent\n");

    // Consider using recv() in a loop for large data to ensure complete message reception
    recv(sockfd, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);

    close(sockfd);

    return 0;
}