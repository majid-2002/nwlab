#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void main()
{
    int windowSize, frameCount;
    printf("Enter the window size: ");
    scanf("%d", &windowSize);
    printf("Enter frame count: ");
    scanf("%d", &frameCount);

    int i, base = 0, next = 0;
    bool ack[50] = {false};

    while (base < frameCount)
    {
        // Transmit frames within the window
        while (next < base + windowSize && next < frameCount)
        {
            printf("Transmitting frame %d\n", next + 1);
            next++;
        }

        // Check for acknowledgements
        for (i = base; i < next; i++)
        {
            if (!ack[i])
            {
                if (rand() % 4 != 0) // Simulating a 25% loss
                {
                    ack[i] = true;
                    printf("Acknowledgement received for frame %d\n", i + 1);
                }
                else
                {
                    printf("Acknowledgement lost for frame %d\n", i + 1);
                }
            }
        }

        // Retransmit frames that were not acknowledged
        for (i = base; i < next; i++)
        {
            if (!ack[i])
            {
                printf("Retransmitting frame %d\n", i + 1);
                if (rand() % 4 != 0) // Simulating a 25% loss
                {
                    ack[i] = true;
                    printf("Retransmission success for frame %d\n", i + 1);
                }
                else
                {
                    printf("Retransmission failed for frame %d\n", i + 1);
                }
            }
        }

        // Move the window base
        while (ack[base] && base < frameCount)
        {
            base++;
        }
    }
}
