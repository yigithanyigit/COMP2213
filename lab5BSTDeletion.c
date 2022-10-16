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

/*
void bst_insert(BST t, int key, void *data){
    if(t == NULL){
        printf("ERROR. Uninitialized tree\n");
    }
    else{
        if(t->root == NULL){
            t->root = bst_init_node(key, data);
        }
        else{
            NODE node = t->root;
            while(node != NULL){
                if(key < node->key){
                    if(node->left == NULL){
                        node->left = bst_init_node(key, data);
                        node = NULL;
                    }
                    else{
                        node = node->left;
                    }
                }
                else if(key > node->key){
                    if(node->right == NULL){
                        node->right = bst_init_node(key, data);
                        node = NULL;
                    }
                    else{
                        node = node->right;
                    }
                }
                else{
                    printf("Duplicate key: %d. Ignoring...\n\n\n", key);
                    node = NULL;
                }
            }
        }
    }
}
*/

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

void bst_delete_unbalanced_iterative(BST t, int key, void *data)
{
    if (t == NULL)
    {
        printf("ERROR. Uninitialized tree\n");
    }
    else
    {

        NODE parent = (NODE)t;
        NODE curr = t->root;
        while ((curr != NULL) && (key != curr->key))
        {
            if (key < curr->key)
            {
                parent = curr;
                curr = curr->left;
            }
            else if (key > curr->key)
            {
                parent = curr;
                curr = curr->right;
            }
        }

        if (curr == NULL)
        {
            printf("The key is not found.\n");
        }
        else
        {
            /* NO CHILD */
            if ((curr->left == NULL) && (curr->right == NULL))
            {
                if (curr == parent->left)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
                // bst_free_node(curr);
                free(curr->data); /* !? */
                free(curr);
            }
            /* SINGLE CHILD ON THE RIGHT */
            else if ((curr->left == NULL) && (curr->right != NULL))
            {
                if (curr == parent->left)
                {
                    parent->left = curr->right;
                }
                else
                {
                    parent->right = curr->right;
                }
            }
            /* SINGLE CHILD ON THE LEFT */
            else if ((curr->left != NULL) && (curr->right == NULL))
            {
                if (curr == parent->left)
                {
                    parent->left = curr->left;
                }
                else
                {
                    parent->right = curr->left;
                }
            }
            /* TWO CHILDREN */
            else
            {
                NODE max = curr->left;
                while (max->right != NULL)
                {
                    max = max->right;
                }
                max->right = curr->right;

                if (curr == parent->left)
                {
                    parent->left = curr->left;
                }
                else
                {
                    parent->right = curr->left;
                }
            }
        }
    }
}

NODE maxValueInSubTree(NODE node)
{
    NODE temp = node;
    while (node->right != NULL)
    {
        temp = node->right;
        node = node->right;
    }
    return temp;
}

NODE bst_delete_recursive(NODE node, int key)
{

    if (key > node->key)
    {
        /* RIGHT */

        node->right = bst_delete_recursive(node->right, key);
    }
    else if (key < node->key)
    {
        /* LEFT */

        node->left = bst_delete_recursive(node->left, key);
    }
    else
    {
        /* IF HAS NOT A CHILD */
        /* JUST DELETE        */

        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }

        /* IF HAS AT LEAST ONE CHILD */
        /*
         * IN A BST SUB-TREE ANY NODE IN RIGHT SIDE MUST BE BIGGER THAN
         * PARENT NODE ALSO ANY NODE IN LEFT SIDE MUST BE SMALLER THAN
         * PARENT NODE SO WE CAN SIMPLY DELETE AND LINKED TO WHICH SIDE
         * THAT WE CAN DELETED
         */

        if (node->left == NULL)
        {
            /* IF LEFT HAS NULL THEN WE HAVE RIGHT NODE */

            NODE temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            /* IF RIGHT HAS NULL THEN WE HAVE LEFT NODE */

            NODE temp = node->left;
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
         *
         */

        else
        {
            NODE max = maxValueInSubTree(node->left);

            max->right = node->right;
            node = max;
                        
        }
        return node;
    }
}

int main()
{
    BST t1 = bst_init();

    bst_insert(t1, 44, NULL);
    bst_insert(t1, 11, NULL);
    bst_insert(t1, 34, NULL);
    bst_insert(t1, 52, NULL);
    bst_insert(t1, 89, NULL);
    bst_insert(t1, 62, NULL);
    bst_insert(t1, 23, NULL);
    bst_insert(t1, 72, NULL);
    bst_insert(t1, 93, NULL);
    bst_insert(t1, 92, NULL);
    bst_insert(t1, 94, NULL);
    bst_insert(t1, 61, NULL);


    bst_print(t1->root, 0); 
    printf("\n\n\n\n\n");
    bst_delete_recursive(t1->root, 89);
    //bst_delete_unbalanced_iterative(t1, 89, NULL);
    bst_print(t1->root, 0);

    return 0;
}
