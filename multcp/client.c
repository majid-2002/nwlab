#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define MAX 100
#define PORT 12345

int main()
{
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char buff[MAX];

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sockfd, (struct sockaddr *)&server, len);
    
    while (1){
        bzero(buff, MAX);
        printf("To server: ");
        fgets(buff, MAX, stdin);
        write(sockfd, buff, MAX);
        read(sockfd, buff, MAX);
        printf("From server: %s\n", buff);
    }

    close(sockfd);
}