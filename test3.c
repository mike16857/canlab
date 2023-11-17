// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
//     char s[] = "www.cs.nthu.edu.tw/~jungchuk/home.html";
//     char t = '/';
//     char *test;
    
//     test = strchr(s, t);
//     printf("%s\n", test);
     
//     return 0;    
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
#include <unistd.h>
// #include <netdb.h> //hostent


// int hostname_to_ip(char *, char *);

int main() {
    char url[100];
    char url_cp[100];
    char *hostname;
    char *path;
    // char ip[100];

    printf("Please enter the URL:\n");
    scanf("%s", url);

    strcpy(url_cp, url);

    hostname = strtok(url, "/");
    path = strchr(url_cp, '/');

    if (path == NULL) {
        path = "/";
    }

    // hostname_to_ip(hostname, ip);

    printf("the valid URL is %s\n", hostname);
    printf("the path is %s\n", path);
    // printf("the IP address of the host is %s\n", ip);

    return 0;
}