#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h> //hostent


#define BUFFER_SIZE 102400
#define PORT 80


int hostname_to_ip(char *, char *);


int main()
{
    char url[100];
    char url_cp[100];
    char *hostname;
    char *path;
    char ip[100];

    printf("Please enter the URL:\n");
    scanf("%s", url);

    strcpy(url_cp, url);

    hostname = strtok(url, "/");
    path = strchr(url_cp, '/');
    if (path == NULL) path = "/";

    hostname_to_ip(hostname, ip);

    printf("the valid URL is %s\n", hostname);
    printf("the path is %s\n", path);
    printf("the IP address of the host is %s\n", ip);

    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);

    // char *message = "Hello from client";
    // char *message = "GET /contact.php HTTP/1.1\r\nHost: www.cs.nthu.edu.tw\r\nConnection: close\r\n\r\n";
    // char *path = "/contact.php";
    // char *hostname = "www.cs.nthu.edu.tw";

    unsigned char buffer[BUFFER_SIZE] = {'\0'};

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
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

    // send(sockfd, message, strlen(message), 0);

    send(sockfd, "GET ", strlen("GET "), 0);
    send(sockfd, path, strlen(path), 0);
    send(sockfd, " HTTP/1.1\r\nHost: ", strlen(" HTTP/1.1\r\nHost: "), 0);
    send(sockfd, hostname, strlen(hostname), 0);
    send(sockfd, "\r\nConnection: close\r\n\r\n", strlen("\r\nConnection: close\r\n\r\n"), 0);

    printf("Hello message sent\n");

    // Consider using recv() in a loop for large data to ensure complete message reception
    recv(sockfd, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);

    close(sockfd);

    return 0;
}


int hostname_to_ip(char *hostname, char *ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(hostname)) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++)
    {
        // Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]));
        return 0;
    }

    return 1;
}