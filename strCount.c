#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int printHyperlink(char*, int);

int main(void)
{
    char *s = "<td><a href=\"home.html\">Home</a> | <a href=\"education.html\">Education</a> | <a href=\"publication.html\">";
    char *t = "<div class=\"buttontext\"><a target='_blank' href=\"http://www.cs.nthu.edu.tw/~jungchuk/home.html\">Advisor</a></div>";
    
    printHyperlink(s, 1);
    printf("%d\n",printHyperlink(s, 0));
    // char *head, *pt;
    // // char hyplk[1000];

    // head = s;
    // // head = t;
    // pt = strstr(s, "<a ");
    // // pt = strstr(t, "<a ");
    // head = pt;

    // pt = strstr(head, "href=\"");
    
    // pt += strlen("href=\"");

    // while (*pt != '\"') 
    //     printf("%c", *pt++);
    
    // printf("\n");

    // // head = pt;

    // printf("%s\n", head);
    // printf("%s\n", pt);
    // // printf("%s\n", hyplk);
    return 0;
}

// int printHyperlink(char *response)
// {
//     char *head;
//     char *pt;
//     int cnt;

//     cnt = 0;
//     head = response;
//     pt = strstr(response, "<a ");

//     while (pt != NULL) {
//         head = pt;

//         pt = strstr(head, "href=\"");
//         pt += strlen("href=\"");

//         while (*pt != '\"') {
//             printf("%c", *pt++);
//         }
//         printf("\n");
//         cnt++;

//         head = pt;
//         pt = strstr(head, "<a ");
//     }

//     return cnt;
// }

int printHyperlink(char *response, int shouldPrint)
{
    char *head;
    char *pt;
    int cnt;

    cnt = 0;
    head = response;
    pt = strstr(response, "<a ");

    while (pt != NULL) {
        head = pt;

        pt = strstr(head, "href=\"");
        pt += strlen("href=\"");

        while (*pt != '\"') {
            // if (shouldPrint == 1)
                printf("%c", *pt);
            pt++;
        }
        // if (shouldPrint == 1)
            printf("\n");
        cnt++;

        head = pt;
        pt = strstr(head, "<a ");
    }

    return cnt;
}

