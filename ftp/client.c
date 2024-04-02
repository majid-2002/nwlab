#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#define BUFSIZE 1024
#define PORT_ADDR 6000

int main()
{
    struct sockaddr_in server;
    int socket_d, file_d, char_count, file_length, i;
    char buffer_1[BUFSIZE], buffer_2[BUFSIZE], pid_str[10];

    socket_d = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_ADDR);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(socket_d, (struct sockaddr *)&server, sizeof(server));

    printf("\nEnter the filename:\n");
    char_count = read(0, buffer_1, sizeof(buffer_1));
    buffer_1[char_count - 1] = '\0';

    write(socket_d, buffer_1, char_count);
    file_d = open(buffer_1, O_RDONLY);
    file_length = read(file_d, buffer_2, sizeof(buffer_2));

    if (file_d < 0)
        printf("\nFile not found!");
    else
    {
        printf("File length: %d\n", file_length);
        printf("\nPrinting content of file:\n");
        for (i = 0; i < file_length; i++)
            printf("%c", buffer_2[i]);
        printf("\n");
        read(socket_d, pid_str, sizeof(pid_str));
        printf("\nReceived process ID from server: %s\n", pid_str);
    }
    close(socket_d);

    return 0;
}