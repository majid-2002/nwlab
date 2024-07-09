#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX 1024
#define PORT 12345

int main()
{
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    char buff[MAX], data[MAX];
    char ch;

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("C: Compose\nR: Read\n");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'C':
        bzero(data, MAX);
        printf("CC: ");
        strcat(data, "CC:");
        scanf("%s", buff);
        strcat(data, buff);

        printf("From: ");
        strcat(data, "\nFrom:");
        scanf("%s", buff);
        strcat(data, buff);

        printf("Subject: ");
        strcat(data, "\nSubject:");
        scanf("%s", buff);
        strcat(data, buff);

        int n = 0;
        bzero(buff, MAX);
        printf("Message: ");
        while ((buff[n++] = getchar()) != '!')
            ;
        strcat(data, "\nMessage:");
        strcat(data, buff);

        sendto(sockfd, data, sizeof(data), 0, (struct sockaddr *)&server, len);
        printf("Mail sent!");
        break;
    case 'R':
        printf("Check mail.txt");
    }

    close(sockfd);
}