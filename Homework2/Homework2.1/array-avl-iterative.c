// Do a while Loop and define a cursor, do everthing with this cursor, write parentIndex functions for decrease level;
// Otherones same as the recursive ones. Rotate it after that shift it !!!!

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

int maxValueInSubTree(array_tree_ptr tree, int index)
{
    while (tree->tree[index].key != 0)
    {
        index = left(index);
    }
    return parent(index);
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

void deleteNode(array_tree_ptr tree, int index)
{
    memset(&tree->tree[index], 0, sizeof(node_t));
    tree->nodeCount--;
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

void arrayBalancer(array_tree_ptr tree, int initialCursor)
{
    int cursor = initialCursor;
    int isRoot = 0;
    while ((cursor > 0 || isRoot == 1) && tree->tree[cursor].key > 0)
    {
        tree->tree[cursor].height = 1 + max(height(tree, left(cursor)), height(tree, right(cursor)));
        int heightDebug = tree->tree[cursor].height;
        int balance = getBalanceFactor(tree, cursor);

        if (balance == 2)
        {
            if (tree->tree[left(cursor)].key != 0 && tree->tree[right(cursor)].key != 0)
            {
                leftRotateOnce(tree, left(cursor));
                rightRotateOnce(tree, cursor);
                shiftUpLeft(tree, left(left(cursor)));
                tree->tree[cursor].height = max(height(tree, left(cursor)), height(tree, left(cursor))) + 1;
                return;
            }
            else
            {
                rightRotateOnce(tree, cursor);
                return;
            }
        }
        if (balance == -2)
        {
            if (tree->tree[left(cursor)].key != 0 && tree->tree[right(cursor)].key != 0)
            {
                rightRotateOnce(tree, right(cursor));
                leftRotateOnce(tree, cursor);
                shiftUpRight(tree, right(right(cursor)));
                tree->tree[cursor].height = max(height(tree, left(cursor)), height(tree, left(cursor))) + 1;
                return;
            }
            else
            {
                leftRotateOnce(tree, cursor);
                return;
            }
        }
        
        cursor = parent(cursor);
        if (cursor == 0 && isRoot == 1)
            isRoot = 0;
        else if (cursor == 0)
            isRoot = 1;
    }
}

void arrayAvlDeleteIterative(array_tree_ptr tree, int key)
{
    int cursor = 0;
    char isDeleted = 0;
    while (isDeleted == 0)
    {
        if (tree->tree[cursor].key == key)
        {
            if (tree->tree[left(cursor)].key == 0 && tree->tree[right(cursor)].key == 0)
            {
                deleteNode(tree, cursor);
                arrayBalancer(tree, cursor);
            }
            else if (tree->tree[left(cursor)].key == 0)
            {

                deleteNode(tree, cursor);
                shiftUpRight(tree, cursor);
                arrayBalancer(tree, cursor);
            }
            else if (tree->tree[right(cursor)].key == 0)
            {

                deleteNode(tree, cursor);
                shiftUpLeft(tree, cursor);
                arrayBalancer(tree, cursor);
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
                int maxIndex = maxValueInSubTree(tree, right(cursor));

                tree->tree[cursor] = tree->tree[maxIndex];

                deleteNode(tree, maxIndex);
            }
            isDeleted = 1;
        }
        else if (key < tree->tree[cursor].key)
        {
            cursor = left(cursor);
        }
        else
        {
            cursor = right(cursor);
        }
    }
}

void arrayAvlInsertIterative(array_tree_ptr tree, int key)
{
    int cursor = 0;
    char isAdded = 0;

    while (isAdded == 0)
    {
        int keyDebug = tree->tree[cursor].key;
        if (tree->tree[cursor].key == 0)
        {
            init_node(tree, key, cursor, NULL);
            arrayBalancer(tree, cursor);
            isAdded = 1;
        }
        else if (key < tree->tree[cursor].key)
        {
            cursor = left(cursor);
        }
        else
        {
            cursor = right(cursor);
        }
    }
}

int main()
{
    array_tree_ptr tr = treeArrayInit();

    printf("Inserting: %d\n", 10);
    arrayAvlInsertIterative(tr, 10);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 6);
    arrayAvlInsertIterative(tr, 6);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 5);
    arrayAvlInsertIterative(tr, 5);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 4);
    arrayAvlInsertIterative(tr, 4);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 3);
    arrayAvlInsertIterative(tr, 3);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 2);
    arrayAvlInsertIterative(tr, 2);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 1);
    arrayAvlInsertIterative(tr, 1);
    printArray(tr);
    printf("\n");
    printf("Inserting: %d\n", 11);
    arrayAvlInsertIterative(tr, 11);
    printArray(tr);
    printf("\n");

    printf("Deleting: %d\n", 3);
    arrayAvlDeleteIterative(tr, 3);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 11);
    arrayAvlDeleteIterative(tr, 11);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 10);
    arrayAvlDeleteIterative(tr, 10);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 6);
    arrayAvlDeleteIterative(tr, 6);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 2);
    arrayAvlDeleteIterative(tr, 2);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 4);
    arrayAvlDeleteIterative(tr, 4);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 5); 
    arrayAvlDeleteIterative(tr, 5);
    printArray(tr);
    printf("\n");
    printf("Deleting: %d\n", 1);
    arrayAvlDeleteIterative(tr, 1);
    printArray(tr);
    printf("\n");
    printArray(tr);

    return 0;
}