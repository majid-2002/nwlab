#include <stdio.h>

void main()
{
    int bsize, n, store = 0, out;
    printf("Enter the bucket size : ");
    scanf("%d", &bsize);
    printf("Enter the rate: ");
    scanf("%d", &out);
    printf("Enter number of process : ");
    scanf("%d", &n);

    while (n != 0)
    {
        int process_size;
        printf("Enter the process size ");
        scanf("%d", &process_size);

        if (process_size <= (bsize - store))
        {
            store += process_size;
            printf("Bucket size %d occupied out of %d \n", store, bsize);
        }
        else
        {
            printf("%d discarded out of %d \n", process_size - (bsize - store), process_size);
            store = bsize;
            printf("Bucket size %d occupied out of %d \n", store, bsize);
        }
        if (store <= out)
        {
            store = 0;
        }
        else
        {
            store -= out;
        }
        n--;
    }
}
