#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s
{
    NODE right;
    NODE left;
    int key;
    void *data;
} NODE_t[1];

typedef struct
{
    NODE root;
} BST_t[1], *BST;

void inorder(NODE node)
{
    if (node != NULL)
    {
        inorder(node->left);
        printf("%d ", node->key);
        inorder(node->right);
    }
}

void bst_print(NODE node, int l)
{
    int i;
    if (node != NULL)
    {
        bst_print(node->right, l + 1);
        for (i = 0; i < l; ++i)
        {
            printf("     ");
        }
        printf("%d\n", node->key);
        bst_print(node->left, l + 1);
    }
}

BST bst_init()
{
    BST t = (BST)malloc(sizeof(BST_t));
    t->root = NULL;
    return t;
}

void bst_free(BST t)
{
    // Think about what happens to the nodes!?
    free(t);
}

NODE bst_init_node(int key, void *data)
{
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    return node;
}

void bst_free_node(NODE n)
{
    free(n);
}

NODE bst_insert_rec(NODE node, int key, void *data)
{
    if (node == NULL)
    {
        node = bst_init_node(key, data);
    }
    else
    {
        if (key < node->key)
        {
            node->left = bst_insert_rec(node->left, key, data);
        }
        else if (key > node->key)
        {
            node->right = bst_insert_rec(node->right, key, data);
        }
        else
        {
            printf("Duplicate key: %d. Ignoring...\n\n\n", key);
        }
    }
    return node;
}

void bst_insert(BST t, int key, void *data)
{
    if (t == NULL)
    {
        printf("ERROR. Uninitialized tree\n");
    }
    else
    {
        if (t->root == NULL)
        {
            t->root = bst_init_node(key, data);
        }
        else
        {
            t->root = bst_insert_rec(t->root, key, data);
        }
    }
}
/*
NODE rightRotatorDOESNTWORK(NODE tree)
{
    NODE node, childNode, t1, t2, t3;
    node = tree;

    int a = sizeof(*tree);
    int b = sizeof(NODE_t);
    if (sizeof(*tree) == sizeof(NODE_t))
    {

        node = (NODE)tree;
    }
    else
    {
        node = tree->root;
    }
    */

// Recurse to the most rightest of the left
/*
if(node->left == NULL)
{
    return node;
}
else
{
    childNode = rightRotator(node->left);

    t1 = childNode->left;
    t2 = childNode->right;
    t3 = node->right;

    node->left = t2;
    node->right = t3;
    childNode->right = node;
}


if (node->left != NULL)
{
    // rightRotator(node->left);

    childNode = rightRotator(node->left);
    // childNode = node->left;

    t1 = childNode->left;
    t2 = childNode->right;
    t3 = node->right;

    node->left = t2;
    node->right = t3;
    childNode->right = node;

    // rightRotator(node);

    return childNode;
}
if (node->right != NULL)
{
    node->right = rightRotator(node->right);
}
else
    return node;
}
*/
void rightRotatorRecursive(NODE parent, NODE grandParent)
{
}

void rightRotatorIterator(NODE gp)
{
    NODE temp = gp->right;

    while (temp)
    {
        if (temp->left)
        {
            NODE oldTmp = temp;
            temp = temp->left;
            oldTmp->left = temp->right;
            temp->right = oldTmp;
            gp->right = temp;
        }
        else
        {
            gp = temp;
            temp = temp->right;
        }
    }
}

/*
    scanner ← root
for i ← 1 to count
    child ← scanner.right
    scanner.right ← child.right
    scanner ← scanner.right
    child.right ← scanner.left
    scanner.left ← child
*/
/*
 routine vine-to-tree(root, size)
 leaves ← size + 1 − 2⌊log2(size + 1))⌋
 compress(root, leaves)
 size ← size − leaves
 while size > 1
 compress(root, ⌊size / 2⌋)
 size ← ⌊size / 2⌋
*/

void leftRotateToXtimes(NODE root, int count)
{

    NODE temp = root;
    for (size_t i = 0; i < count; i++)
    {
        NODE child = temp->right;
        temp->right = child->right;
        temp = temp->right;
        child->right = temp->left;
        temp->left = child;
    }
}

void toBalanced(NODE root, int size)
{

    int counter, temp = size + 1, Two = 2;
    while (temp >>= 1)
        counter++;
    Two = (Two << counter - 1);
    int leaves = size + 1 - Two;
    leftRotateToXtimes(root, leaves);
    bst_print(root, 0);
    printf("\n");
    size = size - leaves;
    while (size > 1)
    {
        leftRotateToXtimes(root, size / 2);
        bst_print(root, 0);
        printf("\n");
        size /= 2;
    }
}

int main()
{
    BST t1 = bst_init();
    bst_insert(t1, 2, NULL);
    bst_insert(t1, 1, NULL);
    bst_insert(t1, 16, NULL);
    bst_insert(t1, 5, NULL);
    bst_insert(t1, 9, NULL);
    bst_insert(t1, 17, NULL);
    bst_insert(t1, 20, NULL);
    bst_insert(t1, 19, NULL);
    bst_insert(t1, 18, NULL);
    bst_insert(t1, 22, NULL);
    bst_insert(t1, 35, NULL);
    bst_print(t1->root, 0);
    // rightRotator(t1->root);
    NODE gp = (NODE)t1;
    rightRotatorIterator(gp);
    toBalanced(t1->root, 11);
    bst_print(t1->root, 0);

    return 0;
}