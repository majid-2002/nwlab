#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define max 1024

int fdl;
socklen_t l;
struct sockaddr_in server, client;
void transfer()
{
    char *data;
    data = ((void *)malloc(max));
    recvfrom(fdl, data, max, 0, (struct sockaddr *)&client, &l);

    FILE *fptr = fopen("mailbox.txt", "w");
    fprintf(fptr, "%s", data);
    fclose(fptr);

    printf("\nReceived 1 mail! Saved to mailbox.txt\n");
}

int main()
{
    int l = 0;
    server.sin_family = AF_INET;
    server.sin_port = htons(6299);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    fdl = socket(AF_INET, SOCK_DGRAM, 0);
    l = sizeof(client);
    bind(fdl, (struct sockaddr *)&server, l);
    transfer();

    return 0;
}