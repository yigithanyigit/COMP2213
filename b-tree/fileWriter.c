#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 5
#define LEVEL_TO_WRITE 3
#define INITIAL_LEVEL MAX + 1

int expn(int base, int n)
{
    if (base == 0 || n == -1)
        return 0;

    if (n == 0 || base == 1)
        return 1;

    base *= expn(base, n - 1);
    return base;
}

int sumOfExpn(int base, int n)
{
    int sum = 0;
    while (n--)
    {
        sum += expn(base, n);
    }
    return sum;
}

void printTree(int **mainArray, int *index)
{
    /*
    int c = 0;
    for (int i = 0; i < (MAX - 1) * sumOfExpn(MAX, LEVEL_TO_WRITE); i++)
    {
        if (i % (MAX - 1) == 0 && i > 0)
        {
            printf("  ");
        }
        if (i % (expn(MAX, c) * 4 + (expn(MAX, c - 1) * 4)) == 0 && i > 0)
        {
            printf("\n");
            c++;
        }

        printf("%d ", data[i]);
    }
    */
    int c = 0;
    for (int i = 0; i < *index; i++)
    {

        for (int j = 0; j < MAX - 1; j++)
        {

            printf("%d ", mainArray[i][j]);
        }
        printf("  ");
        if (i % MAX == 0)
        {
            printf("%d\n", i);
            c++;
        }
        // printf("\n");
    }
}

int **fileRead(int **mainArray, int *mainIndex, int *initialSize)
{
    /*
    FILE *f = fopen("data.bin", "rb");
    int *data = calloc((MAX - 1) * sumOfExpn(MAX, LEVEL_TO_WRITE), sizeof(int));
    fread(data, sizeof(*data), 1, f);
    */

    FILE *f = fopen("data.bin", "rb");

    fseek(f, 0, SEEK_END);
    int size = ftell(f) / (sizeof(int) * (MAX - 1));
    fseek(f, 0, SEEK_SET);
    printf("%d \n", size);
    for (int i = 0; i < size; i++)
    {
        int *subArray = malloc(sizeof(int) * (MAX - 1));
        fread(subArray, sizeof(subArray) * (MAX - 1), 1, f);
        mainArray[*mainIndex] = subArray;
        (*mainIndex)++;
        if (*mainIndex == (*initialSize) - 1)
        {
            (*initialSize) *= 3;
            int **NewMainArray = realloc(mainArray, (*initialSize) * sizeof(int *));
            mainArray = NewMainArray;
        }
    }
}

void fileWrite()
{

    FILE *f = fopen("data.bin", "wb");

    for (int i = 0; i < 1; i++)
    {
        for (int child = 0; child < sumOfExpn(MAX, LEVEL_TO_WRITE); child++)
        {
            int *data = calloc(MAX - 1, sizeof(int));
            fwrite(data, sizeof(int) * (MAX - 1), 1, f);
        }
    }
    fclose(f);
}
/*
int main()
{
    fileWrite();
    fileRead();

    return 0;
}
*/