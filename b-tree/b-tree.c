
#include <stdio.h>
#include <stdlib.h>
#include "fileWriter.c"

void addNode(int **tree, int key, int index)
{
    int potChildIndex = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (tree[index][i] == 0)
        {
            tree[index][i] = key;
            return;
        }
        if (key > tree[index][i])
            potChildIndex = (5 * index) + (i + 1);
            
    }
    addNode(tree, key, potChildIndex);
}

int main()
{
    int initialSize = 33;
    int **mainArray = malloc(sizeof(int *) * initialSize);
    int mainIndex = 0;
    fileRead(mainArray, &mainIndex, &initialSize);
    addNode(mainArray, 5, 0);
    addNode(mainArray, 6, 0);
    addNode(mainArray, 7, 0);
    addNode(mainArray, 8, 0);
    addNode(mainArray, 9, 0);
    addNode(mainArray, 10, 0);
    addNode(mainArray, 11, 0);
    addNode(mainArray, 12, 0);
    addNode(mainArray, 13, 0);
    printTree(mainArray, &mainIndex);
    return 0;
}