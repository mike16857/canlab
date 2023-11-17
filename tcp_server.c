#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
#define PORT 8080
int main() {
 int sockfd, client_sockfd;
 struct sockaddr_in address;
 socklen_t addrlen = sizeof(address);
 char *message = "Hello from server";
 unsigned char buffer[BUFFER_SIZE] = {'\0'};
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = INADDR_ANY;
 address.sin_port = htons(PORT);
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
 perror("socket()");
 exit(EXIT_FAILURE);
 }
 int on = 1; // Forcefully attaching socket to the port 8080
 if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
 perror("setsockopt()");
 exit(EXIT_FAILURE);
 }
 if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
 perror("bind()");
 exit(EXIT_FAILURE);
 }
 if (listen(sockfd, 1) == -1) {
 perror("listen()");
 exit(EXIT_FAILURE);
 }
 printf("Waiting for a client...\n");
 if ((client_sockfd = accept(sockfd, (struct sockaddr *)&address, &addrlen)) == -1) {
 perror("accept()");
 exit(EXIT_FAILURE);
 }
 // Consider using recv() in a loop for large data to ensure complete message reception
 recv(client_sockfd, buffer, BUFFER_SIZE, 0);
 printf("%s\n", buffer);
 send(client_sockfd, message, strlen(message), 0);
 printf("Hello message sent\n");
 close(client_sockfd);
 close(sockfd);
 return 0;
} 