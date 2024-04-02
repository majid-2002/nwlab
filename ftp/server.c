#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#define BUFSIZE 1024
#define PORT_ADDR 6000
#define QSIZE 5

int main()
{
    struct sockaddr_in server, client;
    socklen_t client_size;
    int i, socket_d_1, socket_d_2, file_d, char_count;
    char buffer_1[BUFSIZE], buffer_2[BUFSIZE], pid_str[10];

    socket_d_1 = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_ADDR);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(socket_d_1, (struct sockaddr *)&server, sizeof(server));
    listen(socket_d_1, QSIZE);

    client_size = sizeof(client);
    socket_d_2 = accept(socket_d_1, (struct sockaddr *)&client, &client_size);

    printf("\nRequest accepted.....\n");
    close(socket_d_1);

    snprintf(pid_str, sizeof(pid_str), "%d", getpid());
    char_count = read(socket_d_2, buffer_1, BUFSIZE);
    buffer_1[char_count] = '\0';

    printf("\nFilename is %s", buffer_1);

    if ((file_d = open(buffer_1, O_RDONLY)) >= 0)
    {
        printf("\nFile opened.");
        char_count = read(file_d, buffer_2, BUFSIZE);
        while (char_count > 0)
        {
            printf("\nSending file...");
            write(socket_d_2, buffer_2, char_count);
            printf("\nPrinting content of file:\n");
            for (i = 0; i < char_count; i++)
                printf("%c", buffer_2[i]);
            printf("\n");
            if (i == char_count)
                break;
        }
    }
    else
    {
        printf("\nRequested file not found!\n");
        write(socket_d_2, "", 1); // Sending empty response to indicate file not found
    }

    close(file_d);
    write(socket_d_2, pid_str, strlen(pid_str)); // Sending process ID to the client
    close(socket_d_2);

    return 0;
}