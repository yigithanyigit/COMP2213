
#include <stdio.h>
#include <stdlib.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct node_s *node_ptr;

typedef struct node_s
{
    node_ptr right;
    node_ptr left;
    int key;
    void *data;
    int height;
} node_t[1];

typedef struct avl_s
{
    node_ptr root;
} avl_t[1], *avl_ptr;

void print_tree(node_ptr node, int l)
{
    int i;
    if (node != NULL)
    {
        print_tree(node->right, l + 1);
        for (i = 0; i < l; ++i)
        {
            printf("     ");
        }
        printf("%d\n", node->key);
        print_tree(node->left, l + 1);
    }
}

/*
 *
 *   Helper Functions
 *
 **/

int height(node_ptr n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->height;
}

int getBalanceFactor(node_ptr node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

node_ptr maxValueInSubTree(node_ptr node)
{
    node_ptr temp = node;
    while (node->right != NULL)
    {
        temp = node->right;
        node = node->right;
    }
    return temp;
}

node_ptr init_node(int key, void *data)
{
    node_ptr node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->data = data;
    node->height = 1;
    return node;
}

avl_ptr treeInit()
{
    avl_ptr avl = malloc(sizeof(avl_t));
    avl->root = NULL;

    return avl;
}

/*
 *
 *   Helper Functions End
 *
 **/

node_ptr leftRotateOnce(node_ptr node)
{
    node_ptr childNode = node->right;

    node->right = childNode->left;
    childNode->left = node;

    node->height = max(height(node->left), height(node->right)) + 1;
    childNode->height = max(height(childNode->left), height(childNode->right)) + 1;

    return childNode;
}

node_ptr rightRotateOnce(node_ptr node)
{
    node_ptr childNode = node->left;

    node->left = childNode->right;
    childNode->right = node;

    childNode->height = max(height(childNode->left), height(childNode->right)) + 1;
    node->height = max(height(node->left), height(node->right)) + 1;

    return childNode;
}

node_ptr avlInsert(node_ptr node, int key, void *data)
{
    if (node == NULL)
        return init_node(key, data);

    if (key < node->key)
        node->left = avlInsert(node->left, key, data);
    else if (key > node->key)
        node->right = avlInsert(node->right, key, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalanceFactor(node);

    if (balance == 2)
    {
        if (node->left != NULL && node->right != NULL)
        {
            node->left = leftRotateOnce(node->left);
            return rightRotateOnce(node);
        }
        else
        {
            return rightRotateOnce(node);
        }
    }
    if (balance == -2)
    {
        if (node->left != NULL && node->right != NULL)
        {
            node->right = rightRotateOnce(node->right);
            return leftRotateOnce(node);
        }
        else
        {
            return leftRotateOnce(node);
        }
    }

    return node;
}

node_ptr avlSearchKey(node_ptr node, int key)
{
    if (key < node->key)
        avlSearchKey(node->left, key);
    else if (key > node->key)
        avlSearchKey(node->right, key);
    else
        return node;
}

node_ptr avlDeleteKey(node_ptr node, int key)
{

    if (key < node->key)
        node->left = avlDeleteKey(node->left, key);
    else if (key > node->key)
        node->right = avlDeleteKey(node->right, key);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }
        if (node->left == NULL)
        {

            node_ptr temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {

            node_ptr temp = node->left;
            free(node);
            return temp;
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
            node_ptr max = maxValueInSubTree(node->left);

            node_ptr temp = init_node(max->key, max->data);

            avlDeleteKey(node, max->key);

            temp->right = node->right;
            temp->left = node->left;
            node = temp;
        }
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalanceFactor(node);

    if (balance == 2)
    {
        if (node->left != NULL && node->right != NULL)
        {
            node->left = leftRotateOnce(node->left);
            return rightRotateOnce(node);
        }
        else
        {
            return rightRotateOnce(node);
        }
    }
    if (balance == -2)
    {
        if (node->left != NULL && node->right != NULL)
        {
            node->right = rightRotateOnce(node->right);
            return leftRotateOnce(node);
        }
        else
        {
            return leftRotateOnce(node);
        }
    }
    return node;
}

int main()
{
    avl_ptr t2 = treeInit();
    /*
    t2->root = avlInsert(t2->root, 2, NULL);
    t2->root = avlInsert(t2->root, 1, NULL);
    t2->root = avlInsert(t2->root, 16, NULL);
    t2->root = avlInsert(t2->root, 5, NULL);
    t2->root = avlInsert(t2->root, 9, NULL);
    t2->root = avlInsert(t2->root, 17, NULL);
    t2->root = avlInsert(t2->root, 20, NULL);
    t2->root = avlInsert(t2->root, 19, NULL);
    t2->root = avlInsert(t2->root, 18, NULL);
    t2->root = avlInsert(t2->root, 22, NULL);
    t2->root = avlInsert(t2->root, 35, NULL);
    */
    t2->root = avlInsert(t2->root, 10, 0);
    t2->root = avlInsert(t2->root, 6, 0);
    t2->root = avlInsert(t2->root, 5, 0);
    t2->root = avlInsert(t2->root, 4, 0);
    t2->root = avlInsert(t2->root, 3, 0);
    t2->root = avlInsert(t2->root, 2, 0);

    print_tree(t2->root, 0);
    // printf("%d", avlSearchKey(t2->root, 35)->key);
    return 0;
}