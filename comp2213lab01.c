/*
 ============================================================================
 Name        : hello.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM 12

typedef struct
{
	int regno;
	float weight;
	char name[100];
	char surname[100];
}student_t[1], *student_ptr;


void swap(void *a, void *b) {
	int temp = *(int *)a;
	*(int *)a = *(int *)b;
	*(int *)b = temp;
}

int cmp_regno(void *a, void *b) {
	return (((student_ptr)a)->regno > ((student_ptr)b)->regno);

}


int cmp_name(void *a, void *b) {
	return (strcmp(((student_ptr)a)->name, ((student_ptr)b)->name) <= 0) ? 0 : 1;
}

int cmp_surname(void *a, void *b) {
	return (strcmp(((student_ptr)a)->surname, ((student_ptr)b)->surname) <= 0) ? 0 : 1;
}

void xsort(void **array, int size, int (*compare)(void *a, void *b)) {
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if ((*compare)(array[j], array[j+1]))
                swap(&array[j], &array[j + 1]);
}



int main(void) {


	student_ptr stu = malloc(sizeof(student_t) * 12);


	stu[0].regno = 899212;
		stu[0].weight = 90.41;
		strcpy(stu[0].name, "natalia");
		strcpy(stu[0].surname, "turnbull");

		stu[1].regno = 265748;
		stu[1].weight = 78.23;
		strcpy(stu[1].name, "blair");
		strcpy(stu[1].surname, "davies");

		stu[2].regno = 259755;
		stu[2].weight = 99.45;
		strcpy(stu[2].name, "sonnie");
		strcpy(stu[2].surname, "carver");

		stu[3].regno = 324785;
		stu[3].weight = 70.75;
		strcpy(stu[3].name, "roosevelt");
		strcpy(stu[3].surname, "bernal");

		stu[4].regno = 879514;
		stu[4].weight = 65.87;
		strcpy(stu[4].name, "komal");
		strcpy(stu[4].surname, "eastwood");

		stu[5].regno = 566875;
		stu[5].weight = 67.99;
		strcpy(stu[5].name, "mathilde");
		strcpy(stu[5].surname, "mckee");

		stu[6].regno = 378956;
		stu[6].weight = 69.76;
		strcpy(stu[6].name, "dexter");
		strcpy(stu[6].surname, "lawson");

		stu[7].regno = 714789;
		stu[7].weight = 75.98;
		strcpy(stu[7].name, "clifford");
		strcpy(stu[7].surname, "silva");

		stu[8].regno = 846289;
		stu[8].weight = 75.40;
		strcpy(stu[8].name, "kyra");
		strcpy(stu[8].surname, "mcdaniel");

		stu[9].regno = 459729;
		stu[9].weight = 73.54;
		strcpy(stu[9].name, "harvie");
		strcpy(stu[9].surname, "bloom");

		stu[10].regno = 179210;
		stu[10].weight = 68.98;
		strcpy(stu[10].name, "coby");
		strcpy(stu[10].surname, "roman");

		stu[11].regno = 358711;
		stu[11].weight = 88.42;
		strcpy(stu[11].name, "balraj");
		strcpy(stu[11].surname, "gomez");


		void *p[NUM];
		int i;
		for(i = 0; i < NUM; i++){
			p[i] = (void *)&stu[i];
		}

	//	xsort((void **)p, NUM, cmp_regno);
		xsort((void **)p, NUM, cmp_name);
	//	xsort((void **)p, NUM, cmp_surname);

		int q;
		for(q = 0; q < NUM; q++)
		{
			 printf("%d %s %s\n", ((student_ptr)p[q])->regno, ((student_ptr)p[q])->name, ((student_ptr)p[q])->surname);
		}


	return EXIT_SUCCESS;
}
