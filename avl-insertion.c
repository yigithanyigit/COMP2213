#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct NODE_s *NODE;
typedef struct NODE_s
{
    NODE right;
    NODE left;
    int key;
    void *data;
    int height;
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
    free(t);
}

NODE bst_init_node(int key, void *data)
{
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    node->height = 1;
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

int height(NODE n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->height;
}

int getBalanceFactor(NODE n)
{
    if (n == NULL)
    {
        return 0;
    }
    // if getBalanceFactor() > 0 then left heavy otherwise right is heavy
    return height(n->left) - height(n->right);
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

NODE rightRotateOnce(NODE y)
{
    NODE x = y->left;
    NODE T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;

    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

NODE leftRotateOnce(NODE x)
{
    NODE y = x->right;
    NODE T2 = y->left;

    y->left = x;
    x->right = T2;

    // order of heights is important !! 
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
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

/*AVL Tree  insertion*/

NODE AVLInsert(NODE node, int key, void *data)
{
    if (node == NULL)
        return bst_init_node(key, data);

    if (key < node->key)
        node->left = AVLInsert(node->left, key, data);
    else if (key > node->key)
        node->right = AVLInsert(node->right, key, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key)
    {
        return rightRotateOnce(node);
    }
    if (balance < -1 && key > node->right->key)
    {
        return leftRotateOnce(node);
    }
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotateOnce(node->left);
        return rightRotateOnce(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotateOnce(node->right);
        return leftRotateOnce(node);
    }

    return node;
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
    // bst_print(t1->root, 0);
    // rightRotator(t1->root);
    NODE gp = (NODE)t1;
    rightRotatorIterator(gp);
    // toBalanced(t1->root, 11);
    bst_print(t1->root, 0);
    printf("\n\n\n\n\n\n\n");

    BST t2 = bst_init();
    // NODE gp1 = (NODE)t2;
    t2->root = AVLInsert(t2->root, 2, NULL);
    t2->root = AVLInsert(t2->root, 1, NULL);
    t2->root = AVLInsert(t2->root, 16, NULL);
    t2->root = AVLInsert(t2->root, 5, NULL);
    t2->root = AVLInsert(t2->root, 9, NULL);
    t2->root = AVLInsert(t2->root, 17, NULL);
    t2->root = AVLInsert(t2->root, 20, NULL);
    t2->root = AVLInsert(t2->root, 19, NULL);
    t2->root = AVLInsert(t2->root, 18, NULL);
    t2->root = AVLInsert(t2->root, 22, NULL);
    t2->root = AVLInsert(t2->root, 35, NULL);

    bst_print(t2->root, 0);
    return 0;
}