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
} * array_tree_ptr;

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


/**
 * TO DO
 * 
 *  Su anda shift fonksiyonlari sadece tek taraf icin calisiyor. the shift up ve shift down yap tum
 * tum nodelari kendi assagiya veya yukariya cikarsin.
 * 
 * 
 * 
 */



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
    // Give non zero element, Create New array and fill this array after that insert newArray elements to the main array

    if(tree->tree[index].key == 0 )
    {
        return NULL;
    }
    node_ptr node = shiftUpLeft(tree, left(index));
    if(node == NULL)
    {
        return &tree->tree[index]
    }
    else
    {

    }

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


    tree->tree[index].height = max(height(tree, leftIndex), height(tree, rightIndex)) + 1;
    tree->tree[leftIndex].height = max(height(tree, left(leftIndex)), height(tree, right(leftIndex))) + 1;

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


    tree->tree[rightIndex].height = max(height(tree, left(rightIndex)), height(tree, right(rightIndex))) + 1;
    tree->tree[index].height = max(height(tree, leftIndex), height(tree, rightIndex)) + 1;

    printf("KEY : %d ", tree->tree[index].key);

    return &tree->tree[index];
}

node_ptr arrayAvlInsert(array_tree_ptr tree, int key, int index)
{
    int leftIndex = left(index);
    int rightIndex = right(index);
    int keyDebug = tree->tree[index].key;
    if (tree->tree[index].key == 0)
        return init_node(tree, key, index, NULL);
    if (key < tree->tree[index].key)
        tree->tree[leftIndex] = *arrayAvlInsert(tree, key, leftIndex);
    else if (key > tree->tree[index].key)
        tree->tree[rightIndex] = *arrayAvlInsert(tree, key, rightIndex);

    tree->tree[index].height = 1 + max(height(tree, leftIndex), height(tree, rightIndex));
    int height = tree->tree[index].height;
    int balance = getBalanceFactor(tree, index);

    if (balance == 2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            tree->tree[leftIndex] = *leftRotateOnce(tree, left(index));
            printArray(tree);
            
            return rightRotateOnce(tree, index);
        }
        else
        {
            return rightRotateOnce(tree, index);
        }
    }
    if (balance == -2)
    {
        if (tree->tree[leftIndex].key != 0 && tree->tree[rightIndex].key != 0)
        {
            tree->tree[rightIndex] = *rightRotateOnce(tree, right(index));
            return leftRotateOnce(tree, index);
        }
        else
        {
            return leftRotateOnce(tree, index);
        }
    }

    return &tree->tree[index];
}

int main()
{
    array_tree_ptr tr = treeArrayInit();

    tr->tree[0] = *arrayAvlInsert(tr, 10, 0);
    tr->tree[0] = *arrayAvlInsert(tr, 6, 0);
    tr->tree[0] = *arrayAvlInsert(tr, 5, 0);
    tr->tree[0] = *arrayAvlInsert(tr, 4, 0);
    tr->tree[0] = *arrayAvlInsert(tr, 3, 0);
    tr->tree[0] = *arrayAvlInsert(tr, 2, 0);
    // tr->tree[0] = *arrayAvlInsert(tr, 1, 0);

    /*
     tr->tree[0] = *arrayAvlInsert(tr, 1, 0);
     tr->tree[0] = *arrayAvlInsert(tr, 2, 0);
     tr->tree[0] = *arrayAvlInsert(tr, 3, 0);
     tr->tree[0] = *arrayAvlInsert(tr, 4, 0);
     tr->tree[0] = *arrayAvlInsert(tr, 5, 0);
     */

    printArray(tr);
    // printf("%d", getBalanceFactor(tr, 1));
    return 0;
}