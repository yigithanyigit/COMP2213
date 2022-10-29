/*
 ============================================================================
 Name        : lab2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM 12

typedef struct STUDENT_s *STUDENT;
typedef struct STUDENT_s{
	int regno;
	float weight;
	char name[100];
	char surname[100];
} STUDENT_t[1];


typedef struct NODE_s *NODE;
typedef struct NODE_s{
	NODE left;
	NODE right;
	void *data;
} NODE_t[1];

typedef struct{
	NODE root;
} BST_t[1], *BST;





int main(void) {

	srand(time(NULL));

	STUDENT stu = (STUDENT)malloc(sizeof(STUDENT_t) * NUM);

		stu[0].regno = 1;
		stu[0].weight = 90.41;
		strcpy(stu[0].name, "natalia");
		strcpy(stu[0].surname, "turnbull");

		stu[1].regno = 2;
		stu[1].weight = 78.23;
		strcpy(stu[1].name, "blair");
		strcpy(stu[1].surname, "davies");

		stu[2].regno = 3;
		stu[2].weight = 99.45;
		strcpy(stu[2].name, "sonnie");
		strcpy(stu[2].surname, "carver");

		stu[3].regno = 4;
		stu[3].weight = 70.75;
		strcpy(stu[3].name, "roosevelt");
		strcpy(stu[3].surname, "bernal");

		stu[4].regno = 5;
		stu[4].weight = 65.87;
		strcpy(stu[4].name, "komal");
		strcpy(stu[4].surname, "eastwood");

		stu[5].regno = 6;
		stu[5].weight = 67.99;
		strcpy(stu[5].name, "mathilde");
		strcpy(stu[5].surname, "mckee");

		stu[6].regno = 7;
		stu[6].weight = 69.76;
		strcpy(stu[6].name, "dexter");
		strcpy(stu[6].surname, "lawson");

		stu[7].regno = 8;
		stu[7].weight = 75.98;
		strcpy(stu[7].name, "clifford");
		strcpy(stu[7].surname, "silva");

		stu[8].regno = 9;
		stu[8].weight = 75.40;
		strcpy(stu[8].name, "kyra");
		strcpy(stu[8].surname, "mcdaniel");

		stu[9].regno = 10;
		stu[9].weight = 73.54;
		strcpy(stu[9].name, "harvie");
		strcpy(stu[9].surname, "bloom");

		stu[10].regno = 11;
		stu[10].weight = 68.98;
		strcpy(stu[10].name, "coby");
		strcpy(stu[10].surname, "roman");

		stu[11].regno = 12;
		stu[11].weight = 88.42;
		strcpy(stu[11].name, "balraj");
		strcpy(stu[11].surname, "gomez");


	BST_t tree;

	NODE_t node1, node2, node3, node4, node5, node6, node7,
	node8, node9, node10, node11, node12;


	node1->left = NULL;    node1->right = NULL;   node1->data = &stu[0];
	node2->left = NULL;    node2->right = NULL;   node2->data = &stu[1];
	node3->left = NULL;    node3->right = NULL;   node3->data = &stu[2];
	node4->left = NULL;    node4->right = NULL;   node4->data = &stu[3];
	node5->left = NULL;    node5->right = NULL;   node5->data = &stu[4];
	node6->left = NULL;    node6->right = NULL;   node6->data = &stu[5];
	node7->left = NULL;    node7->right = NULL;   node7->data = &stu[6];
	node8->left = NULL;    node8->right = NULL;   node8->data = &stu[7];
	node9->left = NULL;    node9->right = NULL;   node9->data = &stu[8];
	node10->left = NULL;   node10->right = NULL;  node10->data = &stu[9];
	node11->left = NULL;   node11->right = NULL;  node11->data = &stu[10];
	node12->left = NULL;   node12->right = NULL;  node12->data = &stu[11];


	tree->root = node5;

	node5->left = node7;
	node5->right = node4;

	node7->left = node6;
	node7->right = node8;

	node6->left = node9;
	node6->right = node1;

	node8->left = NULL;
	node8->right = node12;

	node12->left = node3;
	node12->right = NULL;

	node4->left = NULL;
	node4->right = node11;

	node11->left = NULL;
	node11->right = node2;

	node2->left = node10;
	node2->right = NULL;



	int r;

	NODE currentNode;

	currentNode = tree->root;

	while(currentNode != NULL){

		r = rand() % 2;

		printf("%d ", ((STUDENT)currentNode->data)->regno);

		if(r == 0)
		{
			// Left

			currentNode = currentNode->left;




		} else
		{
			// Right

			currentNode = currentNode->right;


		}

	}





	return EXIT_SUCCESS;
}
