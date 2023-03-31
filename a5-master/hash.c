// Name: Carson Mifsud
// Date: 2020-11-5
// Description: This program contains a collection of functions that operate on hash tables.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <stdbool.h>

/* This function will allocate memory for a Performance structure,
 * set all struct variables to 0,
 * and return the address structure.
 */
struct Performance *newPerformance() {

	struct Performance *my_ptr;

	// This allocates memory for a Performance structure
	my_ptr = ( struct Performance * ) malloc ( sizeof ( struct Performance ) );

	if ( my_ptr == NULL ) {

		fprintf ( stderr, "%s", "Memory allocation failed\n" );
		exit ( 0 );

	}

	// This block of code sets each variable within the Performance struct to 0
	my_ptr -> reads = 0;
	my_ptr -> writes = 0;
	my_ptr -> mallocs = 0;
	my_ptr -> frees = 0;

	return my_ptr;

}

/* This function will allocatethe memory for a HashTable
 * and initialize the parameters.
 */
struct HashTable *createTable ( struct Performance *performance, unsigned int capacity, int (*hash)( void *, int ), int (*compar)(const void *, const void *) ) {

	// malloc a new struct HashTable structure
	struct HashTable* new_node = ( struct HashTable * ) malloc ( sizeof ( struct HashTable ) );

	// malloc capacity bytes of data
	new_node->data = malloc ( capacity * sizeof ( void * ) );

	// error check is new_node is NULL
	if ( new_node == NULL ) {

		fprintf ( stderr, "%s", "Memory allocation failed\n" );
		exit ( 0 );

	}

	new_node->nel = 0;

	new_node->capacity = capacity;
	new_node->hash = hash;
	new_node->compar = compar;

	for ( int index = 0; index < capacity; index++ ) {

		( new_node->data[index] ) = NULL;

		performance->reads = performance->reads + 1;

	}

	performance->mallocs = performance->mallocs + 1;

	return new_node;

}

/* This function will add an element to the HashTable
 * with linear probing when a collision occurs
 */
void addElement ( struct Performance *performance, struct HashTable *table, void *src ) {

	// Error check if the number of elements is equal to the capacity
	if ( table->nel == table->capacity ) {

		fprintf ( stderr, "%s", "Number of elements equals the capacity\n" );
		exit ( 0 );

	}

	else {

		int index;

		index = table->hash( src, table->capacity );

		// while there is data present in the given index
		while ( ( table->data[index] ) ) {

			index = index + 1;

			if ( index == table->capacity ) {

				index = 0;

			}

			performance->reads = performance->reads + 1;

		}

		// copy pointer value of src to the index in the array
		( table->data[index] ) = src;

		// Increment the number of elements
		table->nel = table->nel + 1;

		performance->writes = performance->writes + 1;

	}

}

/* This function will find an element
 * in the given HashTable
 */
int getIdx ( struct Performance *performance, struct HashTable *table, void *src ) {

	int index = table->hash( src, table->capacity );
	int original_index = index;
	int value = 0;

	while ( true ) {

		// if there is data in the given index
		if ( ( table->data[index] ) != NULL ) {

			value = table->compar( ( table->data[index] ), src );

			performance->reads = performance->reads + 1;

			if ( value == 0 ) {

				return index;

			}

		}

		index = index + 1;

		// if the index is equal to the capacity of the table
		if ( index == table->capacity ) {

			index = 0;

		}

		// check if the new index equals the original index
		if ( original_index == index ) {

			return -1;

		}

	}

	return -1;

}

/* This function will free the data within the
 * HashTable and free the HashTable itself
 */
void freeTable ( struct Performance *performance, struct HashTable *table ) {

	free ( table->data );
	free ( table );

	performance->frees = performance->frees + 1;

}

/* This function will find an element in the
 * HashTable and return its pointer
 */
void *getElement ( struct Performance *performance, struct HashTable *table, void *src ) {

	int getIdx_value = getIdx ( performance, table, src );

	if ( getIdx_value == -1 ) {

		return NULL;

	}

	// return pointer
	return  ( table->data[getIdx_value] );

}

/* This function will remove an element
 * from the HashTable
 */
void removeElement ( struct Performance *performance, struct HashTable *table, void *target ) {

	int index = getIdx ( performance, table, target );

	( table->data[index] ) = NULL;

	performance->writes = performance->writes + 1;

	table->nel = table->nel - 1;

}

/* This function will compute the hash accuracy of the
 * contents in the HashTable
 */
int hashAccuracy ( struct HashTable *table ) {

	int index = 0;
	int hash_value = 0;
	int difference = 0;

	// check if index is less than the tables capacity
	for ( index = 0; index < (table->capacity); index++ ) {

		// if there is data at the given index
		if ( (table->data[index]) ) {

			// call hashing function
			hash_value = table->hash( (table->data[index]), table->capacity );

			if ( hash_value < index ) {

				difference = difference + ( index - hash_value );

			}

			else if ( hash_value > index ) {

				difference = difference + ( index + ( (table->capacity) - hash_value ) );

			}

		}

	}

	return difference;

}

/* This function will move the pointers in the HashTable
 * to get a better hashAccuracy
 */
void rehash ( struct HashTable *table ) {

	int index = 0;
	int hash_val = 0;

	// while the capacity is not greater than or equal to index
	while ( !(table->capacity <= index) ) {

		// if there is data in the given index
		if ( table->data[index] ) {

			while ( !(table->capacity <= hash_val) ) {

				if ( table->data[hash_val] ) {

					hash_val = hash_val + 1;

					// check if values are equal
					if ( (hash_val == table->capacity ) ) {

						hash_val = 0;

					}

				} else {

					// data at index becomes NULL
					table->data[index] = NULL;
					// data at returned hash value becomes data at index
					table->data[hash_val] = table->data[index];

				}

			}

		}

		index = index + 1;;

	}

}
