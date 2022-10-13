
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LINKED_TREE_NODE_s *LINKED_TREE_NODE;
typedef struct LINKED_TREE_NODE_s
{
	LINKED_TREE_NODE left;
	LINKED_TREE_NODE right;
	int key;
	void *data;
} LINKED_TREE_NODE_t[1];

typedef struct
{
	LINKED_TREE_NODE root;
} LINKED_TREE_t[1], *LINKED_TREE;

typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef struct LINKED_QUEUE_NODE_s
{
	LINKED_QUEUE_NODE next;
	void *data;
} LINKED_QUEUE_NODE_t[1];

typedef struct LINKED_QUEUE_s
{
	LINKED_QUEUE_NODE head;
	LINKED_QUEUE_NODE tail;
} LINKED_QUEUE_t[1], *LINKED_QUEUE;

typedef struct
{
	char *name;
	char *surname;
	float gpa;
} STUDENT_t[1], *STUDENT;

STUDENT student_init(char *name, char *surname, float gpa)
{
	STUDENT s = (STUDENT)malloc(sizeof(STUDENT_t));
	s->name = name;
	s->surname = surname;
	s->gpa = gpa;
	return s;
}

LINKED_QUEUE_NODE linked_queue_node_init()
{
	LINKED_QUEUE_NODE new = malloc(sizeof(LINKED_QUEUE_NODE_t));
	new->data = NULL;
	new->next = NULL;
	return new;
}

void *linked_queue_dequeue(LINKED_QUEUE queue)
{
	LINKED_QUEUE_NODE res, node;
	node = (LINKED_QUEUE_NODE)queue->head;
	if (node != NULL)
	{
		queue->head = node->next;
		res = node->data;
	}
	else
	{
		printf("Queue is Empty");
	}
	return res;
}

void linked_queue_enqueue(LINKED_QUEUE queue, void *data)
{
	LINKED_QUEUE_NODE node = linked_queue_node_init();
	node->data = data;
	if (queue->head == NULL)
	{
		queue->head = node;
		queue->tail = node;
	}
	else
	{
		LINKED_QUEUE_NODE temp = (LINKED_QUEUE_NODE)queue->tail;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = node;
		queue->tail = node;
	}
}

void linked_queue_print(LINKED_QUEUE queue)
{
	LINKED_QUEUE_NODE node = (LINKED_QUEUE_NODE)queue->head;
	while (node != NULL)
	{
		printf("%s %s %0.2f \t ", ((STUDENT)node->data)->name, ((STUDENT)node->data)->surname, ((STUDENT)node->data)->gpa);
		node = node->next;
	}
}

LINKED_TREE linked_tree_init()
{
	LINKED_TREE t = (LINKED_TREE)malloc(sizeof(LINKED_TREE_t));
	t->root = NULL;
	return t;
}

int is_linked_queue_empty(LINKED_QUEUE que)
{
	if (que->head == NULL)
	{
		return 1;
	}

	return 0;
}

/*
void linked_tree_print(LINKED_TREE_NODE node, int a) {
	if (node != NULL) {
		linked_tree_print(node->right, a + 1);
		int i;
		for (i = 0; i < a; ++i) {
			printf("    ");
		}
		printf("%d ",node->key);
		linked_queue_print(node->data);
		printf("\n");
		linked_tree_print(node->left, a + 1);
	}
}
*/

void linked_tree_print(LINKED_TREE_NODE node, int a)
{
	if (node != NULL)
	{
		linked_tree_print(node->right, a + 1);
		int i;
		for (i = 0; i < a; ++i)
		{
			printf("    ");
		}
		printf("%d ", node->key);
		// linked_queue_print(node->data);
		printf("\n");
		linked_tree_print(node->left, a + 1);
	}
}

void linked_node_print(LINKED_TREE_NODE node, int level)
{
	if (node != NULL)
	{
		int i;
		for (i = 0; i < level; ++i)
		{
			printf("    ");
		}
		printf("%d ", node->key);
		printf("\n");
	}
}

LINKED_QUEUE linked_queue_init()
{
	LINKED_QUEUE que = malloc(sizeof(LINKED_QUEUE_t));

	que->head = NULL;
	que->tail = NULL;

	return que;
}

LINKED_TREE_NODE linked_tree_node_init(int key, void *data)
{
	// Fill here!

	LINKED_TREE_NODE node = malloc(sizeof(LINKED_TREE_NODE_t));
	node->data = data;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	/*
	LINKED_QUEUE que = malloc(sizeof(LINKED_QUEUE_t));

	que->head = NULL;
	que->tail = NULL;

	linked_queue_enqueue(que, data);

	node->data = que;
	*/
	return node;
}

void dup_node_handle(LINKED_TREE_NODE curr, void *data)
{
	linked_queue_enqueue((LINKED_QUEUE)curr->data, data);
}

/*
void linked_tree_insert(LINKED_TREE tree, int key, void *data) {
	// Fill here!
	if(tree != NULL){
		if(tree->root != NULL){
			LINKED_TREE_NODE curr = tree->root;
			while(curr != NULL){
				if(key < curr->key){
					if(curr->left != NULL){
						curr = curr->left;
					}
					else{
						curr->left = linked_tree_node_init(key, data);
						curr = NULL;
					}
				}
				else if(key > curr->key){
					if(curr->right != NULL){
						curr = curr->right;
					}
					else{
						curr->right = linked_tree_node_init(key, data);
						curr = NULL;
					}
				}
				else {
					// Add Duplıcate functıon
					dup_node_handle(curr, data);
					curr = NULL;
				}
			}

		}
		else{

			LINKED_TREE_NODE n = linked_tree_node_init(key, data);

			tree->root = n;
		}
	}
	else{
		printf("Invalid tree.\n");
	}


}
*/

LINKED_TREE_NODE bst_insert_rec(LINKED_TREE_NODE node, int key, void *data)
{
	if (node == NULL)
	{
		node = linked_tree_node_init(key, data);
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

void bst_insert(LINKED_TREE t, int key, void *data)
{
	if (t == NULL)
	{
		printf("ERROR. Uninitialized tree\n");
	}
	else
	{
		if (t->root == NULL)
		{
			t->root = linked_tree_node_init(key, data);
		}
		else
		{
			t->root = bst_insert_rec(t->root, key, data);
		}
	}
}

void linked_tree_bf_traversal(LINKED_TREE_NODE rootNode)
{
	/**
	 * @brief Breadth-First Traversal for BST
	 *
	 */

	LINKED_QUEUE q = linked_queue_init();
	linked_queue_enqueue(q, rootNode);
	while (is_linked_queue_empty(q) == 0)
	{
		LINKED_TREE_NODE node = linked_queue_dequeue(q);
		printf("%d ", node->key);
		if (node->left != NULL)
		{

			linked_queue_enqueue(q, node->left);
		}
		if (node->right != NULL)
		{

			linked_queue_enqueue(q, node->right);
		}

		free(node);
	}
}

void bst_print(LINKED_TREE_NODE node, int l)
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

LINKED_TREE_NODE deleteIterative(LINKED_TREE_NODE root, int key)
{

/**
 * @brief Code is inorder doesnt work, because of a reason??
 * 
 */

	LINKED_TREE_NODE curr = root;
	LINKED_TREE_NODE prev = NULL;

	while (curr != NULL && curr->key != key)
	{
		prev = curr;
		if (key < curr->key)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}

	if (curr == NULL)
	{
		printf("Key: %d Not found in tree", key);
		return root;
	}

	if (curr->left == NULL || curr->right == NULL)
	{

		LINKED_TREE_NODE newCurr;

		if (curr->left == NULL)
		{
			newCurr = curr->right;
		}
		else
		{
			newCurr = curr->right;
		}

		if (prev == NULL)
			return newCurr;

		if (curr == prev->left)
			prev->left = newCurr;
		else
			prev->right = newCurr;

		free(curr);
	}

	else

	{
		LINKED_TREE_NODE p = NULL;
		LINKED_TREE_NODE temp;

		temp = curr->right;
		while (temp->left != NULL)
		{
			p = temp;
			temp = temp->left;
		}
		
		if ( p != NULL)
			p->left = temp->right;
		else
			curr->right = temp->right;

		curr->data = temp->data;
		free(temp);

	}

	return root;
}

int main(void)
{
	LINKED_TREE tree = linked_tree_init();

	STUDENT s1 = student_init("name_1", "surname_1", 3.55);
	STUDENT s2 = student_init("name_2", "surname_2", 3.67);
	STUDENT s3 = student_init("name_3", "surname_3", 3.04);
	STUDENT s4 = student_init("name_4", "surname_4", 3.75);
	STUDENT s5 = student_init("name_5", "surname_5", 2.98);
	STUDENT s6 = student_init("name_6", "surname_6", 2.98);
	STUDENT s7 = student_init("name_7", "surname_7", 2.98);
	STUDENT s8 = student_init("name_8", "surname_8", 2.98);

	bst_insert(tree, 15, s1);
	bst_insert(tree, 11, s2);
	bst_insert(tree, 27, s3);
	bst_insert(tree, 18, s4);
	bst_insert(tree, 45, s5);
	bst_insert(tree, 65, s6);
	bst_insert(tree, 49, s7);
	bst_insert(tree, 31, s8);

	bst_print(tree->root, 0);

	//linked_tree_bf_traversal(tree->root);
	//tree->root = NULL;

	deleteIterative(tree->root, 45);

	bst_print(tree->root, 0);

	return EXIT_SUCCESS;
}
