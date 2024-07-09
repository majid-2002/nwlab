#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{

    srand(time(0));
    int frame_count;
    int w_size;

    printf("Enter number of frames : ");
    scanf("%d", &frame_count);
    printf("\n");
    printf("Enter window size ");
    scanf("%d", &w_size);
    printf("\n");
    int start = 0, count = 0;

    while (count < frame_count)
    {
        printf("Frames to Send : ");
        for (int i = start; i < start + w_size && i < frame_count; i++)
        {
            printf("%d ", i + 1);
        }

        printf("\n");

        if ((rand() % 2) == 0)
        {
            printf("Error in Frame %d. Retransmitting window..\n", count + 1);
        }
        else
        {
            printf("Frame %d, acknowledged \n", count + 1);
            count++;
            start++;
        }
    }
}