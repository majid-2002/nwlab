#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
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
    int connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    
    if (connfd != -1)
    {
        printf("Client accepted\n");
    }

    while (1)
    {
        bzero(buff, MAX);
        read(connfd, buff, MAX);
        buff[strcspn(buff, "\r\n")] = 0;
        printf("From client: %s\n", buff);
        int file = open(buff, O_RDONLY);
        if (file >= 0)
        {
            read(file, buff, MAX);
            printf("File found. Data: %s\n", buff);
            write(connfd, buff, sizeof(buff));
        }
        else
        {
            sprintf(buff, "File not found");
            printf("File not found\n");
            write(connfd, buff, sizeof(buff));
        }
    }

    close(sockfd);
}