#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define MAX 100
#define PORT 12345

int main()
{
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char buff[MAX];

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);

    printf("Server listening...\n");

    while (1)
    {
        int connfd = accept(sockfd, (struct sockaddr *)&client, &len);

        if (connfd != -1)
        {
            printf("Client accepted\n");
        }

        if (fork() == 0)
        {
            close(sockfd);
            while (1)
            {
                read(connfd, buff, MAX);
                printf("From client: %s\nTo client: ", buff);
                fgets(buff, MAX, stdin);
                write(connfd, buff, MAX);
            }
            close(connfd);
            exit(0);
        }
        else
        {
            close(connfd);
        }
    }

    close(sockfd);
}