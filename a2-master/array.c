#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

// Name: Carson Mifsud
// Date: 30/09/2020
// Description: This file contains a collection of C functions that operate like arrays.

/* This function will allocate memory for a Performance structure,
   set all struct variables to 0,
   and return the address structure                               */
struct Performance *newPerformance() {

	struct Performance *my_ptr;

	// This allocates memory for a Performance structure
	my_ptr = ( struct Performance * ) malloc ( CAPACITY * sizeof ( struct Performance ) );

	if ( my_ptr == NULL ) {

		fprintf ( stderr, "%s", "Memory allocation failed\n" );
		exit ( 0 );

	}

	my_ptr -> reads = 0;
	my_ptr -> writes = 0;
	my_ptr -> mallocs = 0;
	my_ptr -> frees = 0;

	return my_ptr;

}

/* This function will allocate memory for an Array structure,
   initialize the struct variables,
   and return the address structure                          */
struct Array *newArray ( struct Performance *performance, unsigned int width, unsigned int capacity ) {

	struct Array *my_ptr;

	// This allocates memory for an Array structure
        my_ptr = ( struct Array * ) malloc ( CAPACITY * sizeof ( struct Array ) );

	if ( my_ptr == NULL ) {

		fprintf ( stderr, "%s", "Memory allocation failed\n" );
                exit ( 0 );

	}

	my_ptr -> width = width;
	my_ptr -> capacity = capacity;
	my_ptr -> nel = 0;
	my_ptr -> data = malloc ( width * capacity );

	performance -> mallocs = performance -> mallocs + 1;

	return my_ptr;

}

// This function copies memory from one memory location to the given destination.
void readItem ( struct Performance *performance, struct Array *array, unsigned int index, void *dest ) {

	if ( index >= array -> nel ) {

		fprintf ( stderr, "%s", "The index is greater than or equal to nel\n" );
                exit ( 0 );

	}

	else {

		void  *my_ptr = array -> data;

		memcpy ( dest, ( ( char * ) my_ptr ) + ( index * array -> width ), array -> width );

		// This increments the variable reads by 1
		performance -> reads = performance -> reads + 1;

	}

}

// This function copies memory from the given source to a memory location.
void writeItem ( struct Performance *performance, struct Array *array, unsigned int index, void *src ) {

	if ( index > array -> nel || index >= array -> capacity ) {

		fprintf ( stderr, "%s", "The index either exceeds nel or exceeds or is equal to capacity\n" );
                exit ( 0 );

	}

	else {

		void *my_ptr = array -> data;

		memcpy ( ( ( char * ) my_ptr ) + ( index * array -> width ), src, array -> width );

		if ( index == array -> nel ) {

			array -> nel = array -> nel + 1;

		}

		// This increments the writes variable by 1
		performance -> writes = performance -> writes + 1;

	}

}

// This function decrements the number of elements by one.
void contract ( struct Performance *performance, struct Array *array ) {

	if ( array -> nel == 0 ) {

		fprintf ( stderr, "%s", "Data stored in nel is 0\n" );
                exit ( 0 );

	}

	else {

		array -> nel = array -> nel - 1;

	}

}

// This function will free the data within the array, and the array itself
void freeArray ( struct Performance *performance, struct Array *array ) {

	free ( array -> data );
	free ( array );

	performance -> frees = performance -> frees + 1;

}

// This function will add an element to the end of the array.
void appendItem ( struct Performance *performance, struct Array *array, void *src ) {

	writeItem ( performance, array, array -> nel, src );

}

// This function will insert an element into the array given by index.
void insertItem ( struct Performance *performance, struct Array *array, unsigned int index, void *src ) {

	int nel_temp = array -> nel;
	int i = nel_temp;
	int write_insert;

	if ( index >= array -> capacity ) {

		fprintf ( stderr, "%s", "The capacity has been exceeded\n" );
		exit ( 0 );

	}

	else {

		void *temp;

		// Search through all elements in array using nel (number of elements)
		while ( i >= index + 1 ) {

			readItem ( performance, array, i - 1, &temp );
			writeItem ( performance, array, i, &temp );
			i = i - 1;

			if ( i == index ) {

				write_insert = i;

			}

		}

		writeItem ( performance, array, write_insert, src );

	}

}

// This function will insert data at position 0.
void prependItem ( struct Performance *performance, struct Array *array, void *src ) {

	insertItem ( performance, array, 0, src );

}

// This function will delete an element out of the array given by index.
void deleteItem ( struct Performance *performance, struct Array *array, unsigned int index ) {

	int nel_temp = array -> nel;
	int i = index + 1;
	void *temp;

	// Search through all elements of the array using nel (number of elements)
        while ( i < nel_temp ) {

        	readItem ( performance, array, i, &temp );
                writeItem ( performance, array, i - 1, &temp );
                i = i + 1;

	}

	contract ( performance, array );

}

// This function will search through array to try and find a matching element given by target.
int findItem ( struct Performance *performance, struct Array *array, int ( *compar ) ( const void *, const void * ), void *target ) {

	int nel_temp = array -> nel;
	char temp[STRINGLENGTH];
	int i = 0;

	// Search through all elements of the array using nel (number of elements)
	while ( i < nel_temp ) {

		readItem ( performance, array, i, &temp );

		if ( compar ( target, &temp ) == 0 ) {

			return i;

		}

		i = i + 1;

	}

	return -1;

}

// This function will search through array using a binary search method to find a matching element given by target.
int searchItem ( struct Performance *performance, struct Array *array, int (* compar ) ( const void *, const void * ), void *target ) {

        int nel_temp = array -> nel;
	char temp[STRINGLENGTH];
	int i = 0;

	// Search through all elements of the array using nel (number of elements)
	for ( i = 0; i != nel_temp - 1; i++ ) {

        readItem ( performance, array, ( nel_temp / 2 ), &temp );

		if ( ( compar ( target, &temp ) ) < 0 ) {

			readItem ( performance, array, i - 1, &temp );
			i = 1;

		}

		else if ( ( compar ( target, &temp ) ) > 0 ) {

                        readItem ( performance, array, i, &temp );
			i = -1;

		}

		else if ( compar ( target, &temp ) == 0 ) {

			// Return the elements number where the match was found
			return i;

		}

	}

	return -1;

}
