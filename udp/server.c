#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUFLEN 512
#define PORT 8888

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(void)
{
    struct sockaddr_in server, client;
    int s, i, recv_len;
    socklen_t slen = sizeof(server);
    char buf[BUFLEN];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        die("bind");
    }

    while (1)
    {
        printf("Waiting for data...");
        fflush(stdout);
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&client, &slen)) == -1)
        {
            die("recvfrom()");
        }
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("Data: %s\n", buf);
        if (sendto(s, buf, recv_len, 0, (struct sockaddr *)&client, slen) == -1)
        {
            die("sendto()");
        }
    }

    close(s);
    return 0;
}