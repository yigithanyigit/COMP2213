#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s{
	NODE left;
	NODE right;
	int key;
	void *data;
} NODE_t[1];

typedef struct{
	NODE root;
} BST_t[1], *BST;


void inorder(NODE node){
	if(node != NULL){
		inorder(node->left);
		printf("%d ", node->key);
		inorder(node->right);
	}
}

void bst_print(NODE node, int l){
	int i;
	if(node != NULL){
		bst_print(node->right, l+1);
		for (i = 0; i < l; ++i) {
			printf("     ");
		}
		printf("%d\n", node->key);
		bst_print(node->left, l+1);
	}
}

BST bst_init(){
	BST t = (BST)malloc(sizeof(BST_t));
	t->root = NULL;
	return t;
}

void bst_free(BST t){
	//Think about what happens to the nodes!?
	free(t);
}

NODE bst_init_node(int key, void *data){
	NODE node = (NODE)malloc(sizeof(NODE_t));
	node->left = NULL;
	node->right = NULL;
	node->key = key;
	node->data = data;
	return node;
}

void bst_free_node(NODE n){
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

NODE bst_insert_rec(NODE node, int key, void *data){
	if(node == NULL){
		node = bst_init_node(key, data);
	}
	else{
		if(key < node->key){
			node->left = bst_insert_rec(node->left, key, data);
		}
		else if(key > node->key){
			node->right = bst_insert_rec(node->right, key, data);
		}
		else{
			printf("Duplicate key: %d. Ignoring...\n\n\n", key);
		}
	}
	return node;
}

void bst_insert(BST t, int key, void *data){
	if(t == NULL){
		printf("ERROR. Uninitialized tree\n");
	}
	else{
		if(t->root == NULL){
			t->root = bst_init_node(key, data);
		}
		else{
			t->root = bst_insert_rec(t->root, key, data);
		}
	}
}


NODE maxValueNode(NODE node)
{
    NODE curr = node;

    while (curr && curr->right != NULL)
    {
        curr = curr->right;
    }

    return curr;
    
}

NODE minValueNode(NODE node)
{
    NODE curr = node;
  
    while (curr && curr->left != NULL)
        curr = curr->left;
  
    return curr;
}

NODE bst_delete_unbalanced_recursive(NODE node, int key, void *data){
	if(node == NULL){
		return node;
    }
	else{
        
        NODE curr = node;
        if(key < curr->key)
        {
            curr->left = bst_delete_unbalanced_recursive(curr->left, key, data);
        }
        else if(key > curr->key)
        {
			curr->right = bst_delete_unbalanced_recursive(curr->right, key, data);
        }

		else if(curr == NULL){
			printf("The key is not found.\n");
		}

		else{
			/* NO CHILD AND AT MOST 1 CHILD*/

            if (curr->left == NULL)
            {

                NODE temp = curr->right;
                free(curr);
                return temp;

            } else if (curr->right == NULL)

            {

                NODE temp = curr->left;
                free(curr);
                return temp;

            }
            else {
                /* TWO CHILD*/
                /* WE USING BECAUSE OF BST STRUCTURE LEFT OF RIGHT OR RIGHT OF LEFT*/

                NODE temp = minValueNode(curr->right);

                curr->key = temp->key;

                curr->right = bst_delete_unbalanced_recursive(curr->right, temp->key, NULL);
            }
		}
        return curr;
	}
    
}


void bst_delete_unbalanced_iterative(BST t, int key, void *data){
	if(t == NULL){
		printf("ERROR. Uninitialized tree\n");
	}
	else{

		NODE parent = (NODE)t;
		NODE curr = t->root;
		while((curr != NULL) && (key != curr->key)){
			if(key < curr->key){
				parent = curr;
				curr = curr->left;
			}
			else if(key > curr->key){
				parent = curr;
				curr = curr->right;
			}
		}

		if(curr == NULL){
			printf("The key is not found.\n");
		}
		else{
			/* NO CHILD */
			if( (curr->left == NULL) && (curr->right == NULL) ){
				if(curr == parent->left){
					parent->left = NULL;
				}
				else{
					parent->right = NULL;
				}
				//bst_free_node(curr);
				free(curr->data); /* !? */
				free(curr);

			}
			/* SINGLE CHILD ON THE RIGHT */
			else if( (curr->left == NULL) && (curr->right != NULL) ){
				if(curr == parent->left){
					parent->left = curr->right;
				}
				else{
					parent->right = curr->right;
				}
			}
			/* SINGLE CHILD ON THE LEFT */
			else if( (curr->left != NULL) && (curr->right == NULL) ){
				if(curr == parent->left){
					parent->left = curr->left;
				}
				else{
					parent->right = curr->left;
				}
			}
			/* TWO CHILDREN */
			else{
				NODE max = curr->left;
				while(max->right != NULL){
					max = max->right;
				}
				max->right = curr->right;

				if(curr == parent->left){
					parent->left = curr->left;
				}
				else{
					parent->right = curr->left;
				}
			}
		}
	}
}


int main() {
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
    bst_insert(t1, 90, NULL);

    //bst_delete_unbalanced_iterative(t1, 34, NULL);

    bst_print(t1->root, 0);
    printf("\n");

    //bst_print(t1->root, 0);
    printf("\n");


    //bst_print(t1->root, 0);
    printf("\n");
    
     
    bst_delete_unbalanced_recursive(t1->root, 89, NULL);

	bst_print(t1->root, 0);
    printf("\n");

	return 0;
}







