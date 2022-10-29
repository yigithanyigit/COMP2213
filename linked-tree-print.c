#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LINKED_TREE_NODE_s *LINKED_TREE_NODE;
typedef struct LINKED_TREE_NODE_s {
	LINKED_TREE_NODE left;
	LINKED_TREE_NODE right;
	int key;
	void *data;
} LINKED_TREE_NODE_t[1];

typedef struct {
	LINKED_TREE_NODE root;
} LINKED_TREE_t[1], *LINKED_TREE;

typedef struct LINKED_QUEUE_NODE_s *LINKED_QUEUE_NODE;
typedef struct LINKED_QUEUE_NODE_s{
	LINKED_QUEUE_NODE next;
	void *data;
} LINKED_QUEUE_NODE_t[1];

typedef struct LINKED_QUEUE_s{
  	LINKED_QUEUE_NODE head;
  	LINKED_QUEUE_NODE tail;
} LINKED_QUEUE_t[1], *LINKED_QUEUE;

typedef struct {
	char *name;
	char *surname;
	float gpa;
} STUDENT_t[1], *STUDENT;

STUDENT student_init(char *name, char *surname, float gpa){
	STUDENT s = (STUDENT)malloc(sizeof(STUDENT_t));
	s->name = name;
	s->surname = surname;
	s->gpa = gpa;
	return s;
}

LINKED_QUEUE_NODE linked_queue_node_init() {
	LINKED_QUEUE_NODE new = malloc(sizeof(LINKED_QUEUE_NODE_t));
	new->data = NULL;
	new->next = NULL;
	return new;
}

void *linked_queue_dequeue(LINKED_QUEUE queue) {
	LINKED_QUEUE_NODE res, node;
	node = (LINKED_QUEUE_NODE) queue->head;
	if (node != NULL) {
		queue->head = node->next;
		res = node->data;
	} else {
		printf("Queue is Empty");
	}
	return res;
}

void linked_queue_enqueue(LINKED_QUEUE queue, void *data) {
	LINKED_QUEUE_NODE node = linked_queue_node_init();
	node->data = data;
	if (queue->head == NULL) {
		queue->head = node;
		queue->tail = node;
	} else {
		LINKED_QUEUE_NODE temp = (LINKED_QUEUE_NODE) queue->tail;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
		queue->tail = node;
	}
}

void linked_queue_print(LINKED_QUEUE queue) {
	LINKED_QUEUE_NODE node = (LINKED_QUEUE_NODE) queue->head;
	while (node != NULL) {
		printf("%s %s %0.2f \t ", ((STUDENT)node->data)->name, ((STUDENT)node->data)->surname, ((STUDENT)node->data)->gpa);
		node = node->next;
	}
}

LINKED_TREE linked_tree_init(){
	LINKED_TREE t = (LINKED_TREE)malloc(sizeof(LINKED_TREE_t));
	t->root = NULL;
	return t;
}

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

LINKED_TREE_NODE linked_tree_node_init(int key, void *data) {
	// Fill here!

	LINKED_TREE_NODE node = malloc(sizeof(LINKED_TREE_NODE_t));
	node->data = NULL;
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	LINKED_QUEUE que = malloc(sizeof(LINKED_QUEUE_t));

	que->head = NULL;
	que->tail = NULL;

	linked_queue_enqueue(que, data);

	node->data = que;

	return node;

}

void dup_node_handle(LINKED_TREE_NODE curr, void *data){
	// Fill here!

	linked_queue_enqueue((LINKED_QUEUE)curr->data, data);
}

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

int main(void) {
	LINKED_TREE tree = linked_tree_init();

	STUDENT s1 = student_init("name_1", "surname_1", 3.55);
	STUDENT s2 = student_init("name_2", "surname_2", 3.67);
	STUDENT s3 = student_init("name_3", "surname_3", 3.04);
	STUDENT s4 = student_init("name_4", "surname_4", 3.75);
	STUDENT s5 = student_init("name_5", "surname_5", 2.98);

	linked_tree_insert(tree, 15, s1);
	linked_tree_insert(tree, 34, s2);
	linked_tree_insert(tree, 34, s3);
	linked_tree_insert(tree, 18, s4);
	linked_tree_insert(tree, 18, s5);

	linked_tree_print(tree->root, 0);


	return EXIT_SUCCESS;
}


