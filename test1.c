#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void get_hyperlinks(const char *url)
{
    struct hostent *server;
    struct sockaddr_in server_address;

    // Parse the URL to extract host and path
    char host[256];
    char path[256];
    sscanf(url, "http://%255[^/]/%255[^\n]", host, path);

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    // Get server's IP address
    server = gethostbyname(host);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    // Set up the server_address structure
    bzero((char *)&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(80);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        error("ERROR connecting");
    }

    // Send an HTTP GET request
    char request[512];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);
    if (write(sockfd, request, strlen(request)) < 0)
    {
        error("ERROR writing to socket");
    }

    // Read and print the response
    char buffer[BUFFER_SIZE];
    int n;
    while ((n = read(sockfd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    // Close the socket
    close(sockfd);
}

int main()
{
    char url[256];

    printf("Enter the URL of the web page: ");
    fgets(url, sizeof(url), stdin);
    url[strcspn(url, "\n")] = 0; // Remove the newline character

    get_hyperlinks(url);

    return 0;
}
