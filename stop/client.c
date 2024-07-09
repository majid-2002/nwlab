#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main()
{
    srand(time(0)); // Seed for Random Number
    int frames_len;
    printf("Enter number of frames to transmit: ");
    scanf("%d", &frames_len);

    for (int i = 1; i <= frames_len; i++)
    {
        // SEND
        printf("\n\nSEND Frame %d", i);

        if (rand() % 2)
        {
            printf("\nFrame %d Sent!", i);
        }
        else
        {
            printf("\nFailed to Send.");
            i--;
            continue;
        }

        // ACK
        if (rand() % 2)
        {
            printf("\nACK recieved!");
        }
        else
        {
            printf("\nFailed to recieve ACK.");
            i--;
            continue;
        }
    }

    return 0;
}