#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
    struct sockaddr_in server;
    int s, i;
    socklen_t slen = sizeof(server);
    char buf[BUFLEN];
    char message[BUFLEN];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if (inet_aton(SERVER, &server.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while (1)
    {
        printf("Enter message : ");
        gets(message);
        if (sendto(s, message, strlen(message), 0, (struct sockaddr *)&server, slen) == -1)
        {
            die("sendto()");
        }
        memset(buf, '\0', BUFLEN);
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&server, &slen) == -1)
        {
            die("recvfrom()");
        }
        puts(buf);
    }

    close(s);
    return 0;
}