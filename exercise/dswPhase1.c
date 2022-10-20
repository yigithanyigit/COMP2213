#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s
{
    NODE left;
    NODE right;
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

NODE rightRotator(NODE tree)
{
    NODE node, childNode, t1, t2, t3;
    node = tree;
    /*
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
    */
    if (node->left != NULL)
    {
        // rightRotator(node->left);

        childNode = rightRotator(node->left);

        t1 = childNode->left;
        t2 = childNode->right;
        t3 = node->right;

        node->left = t2;
        node->right = t3;
        childNode->right = node;

        rightRotator(node);

        return childNode;
    }
    if (node->right != NULL)
    {
        node->right = rightRotator(node->right);
        
    }
    else
        return node;
}

int main()
{
    BST t1 = bst_init();
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
    rightRotator(t1->root);
    bst_print(t1->root, 0);

    return 0;
}