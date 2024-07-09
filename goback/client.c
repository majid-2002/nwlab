#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define wsize 4
#define nframes 8

int main()
{
    srand(time(0));
    int count = 0, start = 0;

    while(count < nframes){
        printf("\nSending frames: ");
        for(int i = start; i < start + wsize && i < nframes; i++){
            printf("%d ", i + 1);
        }
        printf("\n");
        if(rand() % 2 == 0){
            printf("Error in Frame %d. Retransmitting window..\n", count + 1);
        }
        else
        {
            printf("frame %d acknowledged\n", count + 1);
            count++;
            start++;
        }
    }
}