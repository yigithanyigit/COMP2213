#include <stdio.h>
#include <stdlib.h>
/*
Write a C code that can perform the tasks given below. You will make a demo of your code in this week's lab session. You will be graded according to your demo.

- Enter an ID number.

- Find the movie with the given ID number. Use FSEEK function to find the movie in the file "sorted.bin".

- Print all the information of the movie to the screen.
*/

#define MAX 1000


typedef struct
{
    int film_id;
    char title[255];
    char description[1023];
    unsigned int release_year;
    int rental_duration;
    float rental_rate;
    unsigned char length;
    float replacement_cost;
    char rating[10];
    char last_update[30];
} RECORD_t, *RECORD;

FILE *getFile(char *fileLocation)
{
    FILE *f = fopen(fileLocation, "rb");
    return f;
}

void printRecord(RECORD array, int key)
{
    printf("Film ID: %d \n", array[key].film_id);
    printf("Title: %s \n", array[key].title);
    printf("Description: %s \n", array[key].description);
    printf("Last Update: %s \n", array[key].last_update);
    printf("Length: %d \n", array[key].length);
    // printf("Rating: %c \n", array[i].rating);
    printf("Release Year: %d \n", array[key].release_year);
    printf("Rental Duration: %d \n", array[key].rental_duration);
    printf("Rental Rate: %f \n", array[key].rental_rate);
    printf("Replacement Cost: %f \n", array[key].replacement_cost);
}

int findKey(RECORD records, int key)
{
    for (int i = 0; i < MAX; i++)
    {
        if(records[i].film_id == key)
            return i;
    }
    
    return -1;
}

int main()
{
    int key;
    scanf("%d", &key);
    RECORD records = malloc(sizeof(RECORD_t) * MAX);
    FILE *f = getFile("sorted.bin");
    fread(records, sizeof(RECORD_t) * MAX, 1, f);
    int index = findKey(records, key);
    if (index != -1)
        printRecord(records, index);
    else
        printf("Record is not in the list");
    return 0;
}