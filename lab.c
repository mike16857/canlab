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
    int hyperlink_count;

    /* Enter URL */
    printf("Please enter the URL:\n");
    scanf("%s", url);
    strcpy(url_cp, url);

    /* Get host IP address */
    hostname = strtok(url, "/");
    path = strchr(url_cp, '/');
    hostname_to_ip(hostname, ip);

    /* Create socket */
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        exit(EXIT_FAILURE);
    }

    printf("Socket created\n");

    /* Connect socket to server */ 
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip); // server IP
    server_addr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&server_addr, addrlen) == -1) {
        perror("connect()");
        fprintf(stderr, "Please start the server first\n");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    /* Send HTTP GET request message */
    char *message1 = "GET /{path} HTTP/1.1\r\n";
    char *message2 = "Host: {hostname}\r\n";
    char *message3 = "Connection: close\r\n\r\n";

    send(sockfd, message, strlen(message), 0);
    send(sockfd, message, strlen(message), 0);
    send(sockfd, message, strlen(message), 0);
    printf("Sending HTTP request\n");

    /* Reveive response */
    unsigned char buffer[BUFFER_SIZE] = {'\0'};
    recv(sockfd, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);
    close(sockfd);

    /* Print result */
    printf("============================")
    //print hyperlinks
    printf("============================")
    printf("We have found %d hyperlinks", hyperlink_count)
    
    return 0;
}


/* Function: Convert host URL to its IP address */ 
int hostname_to_ip(char *hostname, char *ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(hostname)) == NULL) {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++) {
        // Return the first one;
        strcpy(ip, inet_ntoa(*addr_list[i]));
        return 0;
    }

    return 1;
}