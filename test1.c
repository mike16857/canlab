#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h> //hostent


int hostname_to_ip(char *, char *);

int main() {
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