#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define NUMBER_OF_RECORDS_AT_MOVIES_1 600
#define NUMBER_OF_RECORDS_AT_MOVIES_2 600

typedef struct
{
	int film_id;
	char title[255];
	char description[1023];
	unsigned int release_year;
	char rental_duration;
	float rental_rate;
	unsigned char length;
	float replacement_cost;
	char rating[10];
	char last_update[30];
} RECORD_t, *RECORD;

/*
 *
 *  HELPER DEFININGS - START
 *
 * */

#define STARTER_TABLE_SIZE 100

typedef struct TABLE_t
{
	RECORD table;
	float loadFactor;
	int numberOfElements;
	int tableSize;
} TABLE_t[1], *table_ptr;

/*
 *
 * HELPER DEFININGS - END
 *
 * */

/*
 *
 *
 *  HELPER FUNCTIONS - START
 *
 */

void fprint_movie(FILE *file, RECORD_t rec)
{
	fprintf(file, "ID: %d\n", rec.film_id);
	fprintf(file, "TITLE: %s\n", rec.title);
	fprintf(file, "DESCRIPTION: %s\n", rec.description);
	fprintf(file, "RELEASE YEAR: %d\n", rec.release_year);
	fprintf(file, "RENTAL DURATION: %d\n", rec.rental_duration);
	fprintf(file, "RENTAL RATE: %f\n", rec.rental_rate);
	fprintf(file, "REPLACEMENT COST: %f\n", rec.replacement_cost);
	fprintf(file, "RATING: %s\n", rec.rating);
	fprintf(file, "LAST UPDATE: %s\n", rec.last_update);
	fprintf(file, "\n");
}

table_ptr table_init()
{

	/*
	 * Function: table_init 
	 * -------------------------
	 *
	 *  initializes table
	 *
	 *	returns: returns table that dynamically alocated
	 */

	table_ptr table = malloc(sizeof(TABLE_t));
	table->table = calloc(STARTER_TABLE_SIZE, sizeof(RECORD_t) * STARTER_TABLE_SIZE);
	table->loadFactor = 0;
	table->numberOfElements = 0;
	table->tableSize = STARTER_TABLE_SIZE;

	return table;
}

void table_resize(table_ptr table)
{

	/*
	 * Function: table_resize
	 * -------------------------
	 *
	 *  sets table size of multiplication of current table size and 2
	 *
	 *	returns: None
	 */

	table->table = realloc(table->table, sizeof(RECORD_t) * table->tableSize * 2);
	memset(table->table + table->tableSize, 0, sizeof(RECORD_t) * table->tableSize);
	table->loadFactor /= 2;
	table->tableSize *= 2;
}

void table_setsize(table_ptr table, int size)
{
	/*
	 * Function: table_setsize
	 * -------------------------
	 *
	 *  sets table size of multiplication of current table size and size parameter
	 *
	 *	returns: None
	 */

	table->table = realloc(table->table, sizeof(RECORD_t) * table->tableSize * size);
	memset(table->table + table->tableSize, 0, sizeof(RECORD_t) * (table->tableSize * (size - 1)));
	table->loadFactor = table->numberOfElements / size;
	table->tableSize = size;
}

void table_destroy(table_ptr table)
{

	/*
	 * Function: table_destroy
	 * -------------------------
	 *
	 *  frees table
	 *
	 *	returns: None
	 */

	free(table->table);
	free(table);
}

void table_update_loadfactor(table_ptr table)
{

	/*
	 * Function: table_update_loadfactor
	 * -------------------------
	 *
	 *  updates load factor
	 *
	 *	returns: None
	 */

	table->loadFactor = table->numberOfElements / table->tableSize;
}

int table_add(table_ptr table, void *data)
{
	/*
	 * Function: table_add
	 * -------------------------
	 *
	 * 	adds record to table
	 *
	 *	returns: 1 if succesful else 0
	 */

	if (((RECORD)data)->film_id < table->tableSize)
	{
		if (table->table[((RECORD)data)->film_id].film_id == 0)
		{

			table->table[((RECORD)data)->film_id] = *((RECORD)data);
			table->numberOfElements += 1;
			table_update_loadfactor(table);
			return 1;
		}
	}
	else
	{
		table_resize(table);
		table_add(table, data);
	}

	return 0;
}

table_ptr table_intersection(table_ptr table1, table_ptr table2)
{

	/*
	 * Function: table_intersection
	 * -------------------------
	 *
	 * 	calculates two table intersection
	 *
	 *	returns: table of intersection
	 */

	table_ptr newtable = table_init();
	table_ptr intersection = table_init();
	int i;

	i = table1->numberOfElements;

	while (i > 0)
	{

		if (table_add(newtable, table1->table + i) == 0)
		{

			table_add(intersection, table1->table + i);
		}

		i--;
	}

	i = table2->numberOfElements;

	while (i > 0)
	{

		if (table_add(newtable, table2->table + i) == 0)
		{
			table_add(intersection, table2->table + i);
		}

		i--;
	}

	table_destroy(newtable);

	return intersection;
}

void table_reset(table_ptr table)
{

	/*
	 * Function: table_reset
	 * -------------------------
	 *
	 * 	fills table with NULL
	 *
	 *	returns: None
	 */

	int i;
	memset(table->table, 0, sizeof(RECORD_t) * table->tableSize);
}

table_ptr table_diffrence(table_ptr table1, table_ptr table2)
{

	/*
	 * Function: table_diffrence
	 * -------------------------
	 *
	 * 	calculates diffrence between two table (i.e. table1 - table2)
	 *
	 *	returns: diffrence table that not contains table2 values
	 */

	table_ptr diffrence_table = table_init();
	int i = 0;
	int c = 0;
	
	while (i < table1->tableSize && i < table2->tableSize)
	{

		if ((table1->table[i].film_id != table2->table[i].film_id) && table1->table[i].film_id != 0 )
		{

			table_add(diffrence_table, &table1->table[i]);
		}

		i++;
	}

	
	if(i < table1->tableSize)
	{
		while (i < table1->tableSize)
		{
			table_add(diffrence_table, &table1->table[i]);

			i++;
		}
		
		
	}
	
	return diffrence_table;
}

void add_all_movies_to_hashtable(table_ptr table, RECORD rec, int n)
{
	/*
	 * Function: add_all_movies_to_hashtable
	 * -------------------------------------
	 *
	 * adds all records to pre-defined table
	 *
	 *	returns: None
	 */

	int i;

	for (i = 0; i < n; i++)
	{

		table_add(table, &rec[i]);
	}
}

/*
 *
 *
 *  HELPER FUNCTIONS - END
 *
 */

void print_movie(RECORD_t rec)
{
	printf("ID: %d\n", rec.film_id);
	printf("TITLE: %s\n", rec.title);
	printf("DESCRIPTION: %s\n", rec.description);
	printf("RELEASE YEAR: %d\n", rec.release_year);
	printf("RENTAL DURATION: %d\n", rec.rental_duration);
	printf("RENTAL RATE: %f\n", rec.rental_rate);
	printf("REPLACEMENT COST: %f\n", rec.replacement_cost);
	printf("RATING: %s\n", rec.rating);
	printf("LAST UPDATE: %s\n", rec.last_update);
	printf("\n");
}

void print_all_movies(RECORD rec, int n)
{
	for (int i = 0; i < n; i++)
	{
		print_movie(rec[i]);
	}
}

void write_intersection(FILE *file, RECORD movies1, RECORD movies2)
{
	// TODO: Fill this block.

	table_ptr table1 = table_init();
	table_ptr table2 = table_init();
	int i;

	add_all_movies_to_hashtable(table1, movies1, NUMBER_OF_RECORDS_AT_MOVIES_1);
	add_all_movies_to_hashtable(table2, movies2, NUMBER_OF_RECORDS_AT_MOVIES_2);

	table_ptr intersection = table_intersection(table1, table2);

	i = intersection->tableSize;

	while (i > 0)
	{
		if (intersection->table[i].film_id > 0)
		{
			printf("%d \n", intersection->table[i]);

			fprint_movie(file, intersection->table[i]);
		}

		i--;
	}

	table_destroy(table1);
	table_destroy(table2);
	table_destroy(intersection);
}

void write_union(FILE *file, RECORD movies1, RECORD movies2)
{
	// TODO: Fill this block.

	table_ptr table = table_init();
	int i;

	add_all_movies_to_hashtable(table, movies1, NUMBER_OF_RECORDS_AT_MOVIES_1);
	add_all_movies_to_hashtable(table, movies2, NUMBER_OF_RECORDS_AT_MOVIES_2);

	i = table->numberOfElements;

	while (i > 0)
	{
		if (table->table[i].film_id > 0)
		{
			printf("%d \n", table->table[i]);

			fprint_movie(file, table->table[i]);
		}

		i--;
	}

	table_destroy(table);
}

void write_difference(FILE *file, RECORD movies1, RECORD movies2)
{
	// TODO: Fill this block.

	table_ptr table1 = table_init();
	table_ptr table2 = table_init();

	add_all_movies_to_hashtable(table1, movies1, NUMBER_OF_RECORDS_AT_MOVIES_1);
	add_all_movies_to_hashtable(table2, movies2, NUMBER_OF_RECORDS_AT_MOVIES_2);

	table_ptr diffrence_table = table_diffrence(table2, table1);

	int i = diffrence_table->tableSize;

	while (i > 0)
	{
		if (diffrence_table->table[i].film_id > 0)
		{
			printf("%d \n", diffrence_table->table[i]);

			fprint_movie(file, diffrence_table->table[i]);
		}

		i--;
	}

	table_destroy(diffrence_table);
	table_destroy(table1);
	table_destroy(table2);
}

int main()
{
	RECORD movies1_records = (RECORD)malloc(sizeof(RECORD_t) * NUMBER_OF_RECORDS_AT_MOVIES_1);
	FILE *movies1_file = fopen("movies-1.txt", "rb");
	if (movies1_file == NULL)
	{
		printf("Cannot open the movies-1.txt file.\n");
		exit(1);
	}
	fread(movies1_records, sizeof(RECORD_t) * NUMBER_OF_RECORDS_AT_MOVIES_1, 1, movies1_file);
	fclose(movies1_file);

	RECORD movies2_records = (RECORD)malloc(sizeof(RECORD_t) * NUMBER_OF_RECORDS_AT_MOVIES_2);
	FILE *movies2_file = fopen("movies-2.txt", "rb");
	if (movies2_file == NULL)
	{
		printf("Cannot open the movies-2.txt file.\n");
		exit(2);
	}
	fread(movies2_records, sizeof(RECORD_t) * NUMBER_OF_RECORDS_AT_MOVIES_2, 1, movies2_file);
	fclose(movies2_file);

	// TEST FUNCTIONS
	FILE *movies_intersection = fopen("movies_intersection.txt", "wb");
	FILE *movies_union = fopen("movies_union.txt", "wb");
	FILE *movies_difference = fopen("movies_difference.txt", "wb");

	write_intersection(movies_intersection, movies1_records, movies2_records);
	write_union(movies_union, movies1_records, movies2_records);
	write_difference(movies_difference, movies1_records , movies2_records);

	fclose(movies_intersection);
	fclose(movies_union);
	fclose(movies_difference);

	free(movies1_records);
	free(movies2_records);

	return 0;
}