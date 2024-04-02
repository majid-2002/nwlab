#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define max 1024

int sockfd;
struct sockaddr_in server, client;
char *buf, *str;

void send_data()
{
    char ch;
    buf = (void *)malloc(max);
    str = (void *)malloc(max);
    int len = 0;

    printf("CC:");
    sprintf(str, "CC:");
    len += strlen(str);
    strcat(buf, str);
    scanf("%s", str);
    len += strlen(str);
    strcat(buf, str);

    printf("From:");
    sprintf(str, "\nFrom:");
    len += strlen(str);
    strcat(buf, str);
    scanf("%s", str);
    len += strlen(str);
    strcat(buf, str);

    printf("\nSubject:");
    sprintf(str, "\nSubject:");
    len += strlen(str);
    strcat(buf, str);
    scanf("%s", str);
    len += strlen(str);
    strcat(buf, str);

    printf("Message:\n");
    sprintf(str, "\nMessage:\n");
    len += strlen(str);
    strcat(buf, str);
    // Read Message. ! is the end of the message
    while ((ch = getchar()) != '!')
    {
        buf[len] = ch;
        len++;
    }

    buf[len++] = '\0';
    sendto(sockfd, buf, len, 0, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
    printf("Mail sent!\n");
    close(sockfd);
}

int main()
{
    char ch;
    server.sin_family = AF_INET;
    server.sin_port = htons(6299);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bind(sockfd, (struct sockaddr *)&client, sizeof(client));

    printf("C:Compose \nR:Read mail \n");
    scanf("%c", &ch);

    switch (ch)
    {
    case 'C':
        send_data();
        break;
    case 'R':
        printf("Please check mailbox\n");
    }

    return 0;
}