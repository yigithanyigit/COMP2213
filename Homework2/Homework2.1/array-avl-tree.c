#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define treeInitialLevel 5

typedef struct node_s
{
    int key;
    void *data;
    int height;
} node_t[1], *node_ptr;

typedef struct
{
    node_ptr tree;
    int nodeCount;
} *array_tree_ptr;

/**
 * Helper Functions Start
 *
 *
 *
 */

array_tree_ptr treeArrayInit()
{
    int nodes = 2;
    nodes <<= treeInitialLevel;
    nodes--;
    // Initialized with a initial value of node to prevent realloc every time
    // node_t *tree = calloc(nodes, sizeof(node_t));
    array_tree_ptr tree = malloc(sizeof(array_tree_ptr));
    tree->tree = calloc(nodes, sizeof(node_t));
    tree->nodeCount = 0;
    return tree;
}

node_ptr init_node(array_tree_ptr tree, int key, int index, void *data)
{

    tree->tree[index].key = key;
    tree->tree[index].data = NULL;
    tree->tree[index].height = 1;
    tree->nodeCount++;

    return &tree->tree[index];
}

int left(int index)
{
    return 2 * index + 1;
}

int right(int index)
{
    return 2 * index + 2;
}

int parent(int index)
{
    return (index - 1) / 2;
}

void deleteNode(array_tree_ptr tree, int index)
{
    memset(&tree->tree[index], 0, sizeof(node_t));
    tree->nodeCount--;
}

int height(array_tree_ptr tree, int index)
{
    if (tree->tree[index].key == 0)
    {
        return 0;
    }
    return tree->tree[index].height;
}

int getBalanceFactor(array_tree_ptr tree, int index)
{
    if (tree->tree[index].key == 0)
    {
        return 0;
    }
    return height(tree, left(index)) - height(tree, right(index));
}

void printArray(array_tree_ptr tree)
{

    for (int i = 0, q = 0; q < tree->nodeCount; i++)
    {
        printf("%d ", tree->tree[i].key);
        if (tree->tree[i].key != 0)
            q++;
    }
    printf("\n");
}

void shiftDownLeft(array_tree_ptr tree, int index)
{
    if (tree->tree[index].key == 0)
        return;

    shiftDownLeft(tree, left(index));

    tree->tree[left(index)].key = tree->tree[index].key;
    memset(&tree->tree[index], 0, sizeof(node_t));
    tree->tree[left(index)].height = max(height(tree, left(left(index))), height(tree, right(left(index)))) + 1;
}

void shiftDownRight(array_tree_ptr tree, int index)
{
    if (tree->tree[index].key == 0)
        return;

    shiftDownRight(tree, right(index));

    tree->tree[right(index)].key = tree->tree[index].key;
    memset(&tree->tree[index], 0, sizeof(node_t));
    tree->tree[right(index)].height = max(height(tree, left(right(index))), height(tree, right(left(index)))) + 1;
}

node_ptr shiftUpLeft(array_tree_ptr tree, int index)
{
    int heightT = tree->tree[index].height;
    if (tree->tree[index].key != 0 && tree->tree[index].height == 1)
    {
        node_ptr handlingNode = malloc(sizeof(int));
        *handlingNode = tree->tree[index];
        memset(&tree->tree[index], 0, sizeof(node_t));
        return handlingNode;
    }
    int kDebug = tree->tree[index].key;
    node_ptr node = shiftUpLeft(tree, left(index));
    struct node_s tempNode = (tree->tree[index]);
    tree->tree[index] = *node;
    // tree->tree[index].height = max(height(tree, right(right(index))), height(tree, left(left(index)))) + 1;
    int heightTNew = tree->tree[index].height;
    kDebug = tree->tree[index].key;
    *node = tempNode;
    return node;
}

node_ptr shiftUpRight(array_tree_ptr tree, int index)
{

    if (tree->tree[index].key != 0 && tree->tree[index].height == 1)
    {
        node_ptr handlingNode = malloc(sizeof(int));
        *handlingNode = tree->tree[index];
        tree->tree[index].key = 0;
        tree->tree[index].height = 0;
        tree->tree[index].data = 0;
        return handlingNode;
    }
    int heightT = tree->tree[index].height;
    node_ptr node = shiftUpRight(tree, right(index));
    struct node_s tempNode = (tree->tree[index]);
    tree->tree[index] = *node;

    heightT = tree->tree[index].height;
    *node = tempNode;
    return node;
}

/**
 * Helper Functions End
 *
 */

node_ptr leftRotateOnce(array_tree_ptr tree, int index)
{

    int rightIndex = right(index);
    int leftIndex = left(index);
    int childNodeIndex = rightIndex;
    struct node_s childNode = tree->tree[childNodeIndex];
    struct node_s childNodeLeft = tree->tree[left(childNodeIndex)];
    struct node_s childNodeRight = tree->tree[right(childNodeIndex)];

    shiftDownLeft(tree, left(index));

    tree->tree[right(leftIndex)] = childNodeLeft;
    memset(&tree->tree[right(rightIndex)], 0, sizeof(node_t));
    memset(&tree->tree[left(rightIndex)], 0, sizeof(node_t));
    tree->tree[leftIndex] = tree->tree[index];
    tree->tree[rightIndex] = childNodeRight;
    tree->tree[index] = childNode;

    tree->tree[childNodeIndex].height = max(height(tree, left(childNodeIndex)), height(tree, right(childNodeIndex))) + 1;
    tree->tree[leftIndex].height = max(height(tree, left(leftIndex)), height(tree, right(leftIndex))) + 1;
    tree->tree[index].height = max(height(tree, leftIndex), height(tree, rightIndex)) + 1;

    return &tree->tree[index];
}

node_ptr rightRotateOnce(array_tree_ptr tree, int index)
{
    int rightIndex = right(index);
    int leftIndex = left(index);
    int childNodeIndex = leftIndex;
    struct node_s childNode = tree->tree[childNodeIndex];
    struct node_s childNodeLeft = tree->tree[left(childNodeIndex)];
    struct node_s childNodeRight = tree->tree[right(childNodeIndex)];

    shiftDownRight(tree, right(index));

    tree->tree[left(rightIndex)] = childNodeRight;
    memset(&tree->tree[right(leftIndex)], 0, sizeof(node_t));
    memset(&tree->tree[left(leftIndex)], 0, sizeof(node_t));
    tree->tree[rightIndex] = tree->tree[index];
    tree->tree[leftIndex] = childNodeLeft;
    tree->tree[index] = childNode;

    tree->tree[childNodeIndex].height = max(height(tree, left(childNodeIndex)), height(tree, right(childNodeIndex))) + 1;
    tree->tree[rightIndex].height = max(height(tree, left(rightIndex)), height(tree, right(rightIndex))) + 1;

    tree->tree[index].height = max(height(tree, leftIndex), height(tree, rightIndex)) + 1;

    return &tree->tree[index];
}

int maxValueInSubTree(array_tree_ptr tree, int index)
{
    while (tree->tree[index].key != 0)
    {
        index = left(index);
    }
    return parent(index);
}

int minValueInSubTree(array_tree_ptr tree, int index)
{
    while (tree->tree[index].key != 0)
    {
        index = right(index);
    }
    return parent(index);
}

void arrayAvlInsert(array_tree_ptr tree, int key, int index)
{
    int leftIndex = left(index);
    int rightIndex = right(index);
    int keyDebug = tree->tree[index].key;
    if (tree->tree[index].key == 0)
    {
        init_node(tree, key, index, NULL);
        return;
    }
    else if (key < tree->tree[index].key)
        arrayAvlInsert(tree, key, leftIndex);
    else if (key > tree->tree[index].key)
        arrayAvlInsert(tree, key, rightIndex);

    tree->tree[index].height = 1 + max(height(tree, leftIndex), height(tree, rightIndex));
    int heightDebug = tree->tree[index].height;

    int rightHeightDebug = height(tree, right(index));
    int leftHeightDebug = height(tree, left(index));
    int balance = getBalanceFactor(tree, index);

    if (balance == 2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            leftRotateOnce(tree, left(index));
            rightRotateOnce(tree, index);
            shiftUpLeft(tree, left(left(index)));
            tree->tree[index].height = max(height(tree, left(index)), height(tree, left(index))) + 1;
            return;
        }
        else
        {
            rightRotateOnce(tree, index);
            return;
        }
    }
    if (balance == -2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            rightRotateOnce(tree, right(index));
            leftRotateOnce(tree, index);
            shiftUpRight(tree, right(right(index)));
            tree->tree[index].height = max(height(tree, left(index)), height(tree, left(index))) + 1;
            return;
        }
        else
        {
            leftRotateOnce(tree, index);
            return;
        }
    }

    return;
}

void arrayAvlDelete(array_tree_ptr tree, int key, int index)
{

    int leftIndex = left(index);
    int rightIndex = right(index);
    int keyDebug = tree->tree[index].key;
    if (key < tree->tree[index].key)
        arrayAvlDelete(tree, key, leftIndex);
    else if (key > tree->tree[index].key)
    {
        arrayAvlDelete(tree, key, rightIndex);
    }
    else
    {
        if (tree->tree[left(index)].key == 0 && tree->tree[right(index)].key == 0)
        {
            deleteNode(tree, index);
            return;
        }
        else if (tree->tree[left(index)].key == 0)
        {

            deleteNode(tree, index);
            shiftUpRight(tree, index);
            return;
        }
        else if (tree->tree[right(index)].key == 0)
        {

            deleteNode(tree, index);
            shiftUpLeft(tree, index);
            return;
        }

        /* IF HAS 2 CHILDS */
        /**
         * IN BALANCED BST TREE CONCEPT THIS ONE IS VERY IMPORTANT CONDITION,
         *
         * FIRST OF ALL WE NEED TO FIND MOST LEFT OF RIGHT OR MOST RIGHT OF LEFT SUBTREE
         * AFTER THAT WE NEED TO CHANGE AND LINK TO EACH OTHER AND IN FINAL IF WE HAVE A
         * LEFT CHILD OF "MAX/MIN" NODE THEN WE NEED TO AGAIN LINK TO PARENT OF MAX
         *    50                            60
           /     \         delete(50)      /   \
          40      70       --------->    40    70
                 /  \                            \
                60   80                           80
         */

        else
        {
            int maxIndex = maxValueInSubTree(tree, right(index));

            tree->tree[index] = tree->tree[maxIndex];

            deleteNode(tree, maxIndex);
        }
    }

    tree->tree[index].height = 1 + max(height(tree, leftIndex), height(tree, rightIndex));
    int height = tree->tree[index].height;
    int balance = getBalanceFactor(tree, index);

    if (balance == 2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            leftRotateOnce(tree, left(index));
            rightRotateOnce(tree, index);
            shiftUpLeft(tree, left(left(index)));
            return;
        }
        else
        {
            rightRotateOnce(tree, index);
            return;
        }
    }
    if (balance == -2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            rightRotateOnce(tree, right(index));
            leftRotateOnce(tree, index);
            shiftUpRight(tree, right(right(index)));
            return;
        }
        else
        {
            leftRotateOnce(tree, index);
            return;
        }
    }
    return;
}

int arrayAvlSearch(array_tree_ptr tree, int key, int index)
{
    int leftIndex = left(index);
    int rightIndex = right(index);
    if (tree->tree[index].key == key)
    {
        return tree->tree[index].key;
    }
    else if (tree->tree[index].key == 0)
        return -1;
    else if (key < tree->tree[index].key)
        return arrayAvlSearch(tree, key, leftIndex);
    else if (key > tree->tree[index].key)
        return arrayAvlSearch(tree, key, rightIndex);
}

int main()
{
    array_tree_ptr tr = treeArrayInit();

    /**
     * COMPILED WITH Succesfully gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0
     *
     */

    printf("Inserting: %d\n", 10);
    arrayAvlInsert(tr, 10, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 6);
    arrayAvlInsert(tr, 6, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 5);
    arrayAvlInsert(tr, 5, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 4);
    arrayAvlInsert(tr, 4, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 3);
    arrayAvlInsert(tr, 3, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 2);
    arrayAvlInsert(tr, 2, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 1);
    arrayAvlInsert(tr, 1, 0);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 11);
    arrayAvlInsert(tr, 11, 0);
    printArray(tr);
    printf("\n");

    printf("Searching: %d Found -> key, Not Found -> -1 \n", 10);
    printf("%d", arrayAvlSearch(tr, 10, 0));
    printf("\n\n");
    printf("Searching: %d Found -> key, Not Found -> -1 \n", 6);
    printf("%d", arrayAvlSearch(tr, 6, 0));
    printf("\n\n");
    printf("Searching: %d Found -> key, Not Found -> -1 \n", 22);
    printf("%d", arrayAvlSearch(tr, 22, 0));
    printf("\n\n");

    printf("Deleting: %d\n", 3);
    arrayAvlDelete(tr, 3, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 11);
    arrayAvlDelete(tr, 11, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 10);
    arrayAvlDelete(tr, 10, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 6);
    arrayAvlDelete(tr, 6, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 2);
    arrayAvlDelete(tr, 2, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 4);
    arrayAvlDelete(tr, 4, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 5);
    arrayAvlDelete(tr, 5, 0);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 1);
    arrayAvlDelete(tr, 1, 0);
    printArray(tr);
    printf("\n");

    return 0;
}