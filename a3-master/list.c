// Name: Carson Mifsud
// Date: 2020-10-13
// Description: This program contains a collection of functions that operate on linked lists.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* This function will allocate memory for a Performance structure,
   set all struct variables to 0,
   and return the address structure                               */
struct Performance *newPerformance() {

        struct Performance *my_ptr;

        // This allocates memory for a Performance structure
        my_ptr = ( struct Performance* ) malloc ( sizeof ( struct Performance ) );

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

// This function will add an item at the head of the list
void push ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ) {

	struct Node* new_node =  malloc ( sizeof ( struct Node ) );

	new_node->data = malloc ( width * sizeof ( unsigned int ) );

        if ( new_node == NULL ) {

                fprintf ( stderr, "%s", "Memory allocation failed\n" );
                exit ( 0 );

        }

	// Copy bytes of memory from src to data pointed to by new_node
	memcpy ( new_node->data, src, width );

	new_node->next = *list_ptr;

	*list_ptr = new_node;

	// Increment the mallocs and writes varibales within the Performance struct by 1
	performance->mallocs = performance->mallocs + 1;
        performance->writes = performance->writes + 1;

}

// This function will copy data from the head of the list into the variable dest
void readHead ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {

	if ( *list_ptr == NULL ) {

                fprintf ( stderr, "%s", "The list is empty\n" );
                exit ( 0 );

        }

	// Copy width of memory from data pointed to by the pointer of list_ptr into dest
	memcpy ( dest, (*list_ptr)->data, width );

	// Increment the reads variable within the Performance struct by 1
        performance->reads = performance->reads + 1;

}

// This function will remove an item from the head of the list
void pop ( struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width ) {

	struct Node *new_temp = *list_ptr;

        if ( !(*list_ptr) ) {

                fprintf ( stderr, "%s", "The list is empty\n" );
                exit ( 0 );

        }

        // Copy width of memory from data pointed to by the pointer of list_ptr into dest
	memcpy ( dest, (*list_ptr)->data, width );

	*list_ptr = (new_temp)->next;

	// Free data pointed to by new_temp
	free ( (new_temp)->data );
	// Free new_temp
	free ( (new_temp) );

        // Increment the frees and reads varibales within the Performance struct by 1
        performance->frees = performance->frees + 1;
        performance->reads = performance->reads + 1;

}

// This function will return pointer to the pointer to the second item in a list
struct Node **next ( struct Performance *performance, struct Node **list_ptr ) {

        if ( *list_ptr == NULL ) {

                fprintf ( stderr, "%s", "The list is empty\n" );
                exit ( 0 );

        }

        // Increment the reads variable within the Performance struct by 1
	performance->reads = performance->reads + 1;
	// Return address of next pointer from the structure pointed to by the pointer that list_ptr points to
        return ( &(*list_ptr)->next );

}

// This function is used to determine if a list is empty
int isEmpty ( struct Performance *performance, struct Node **list_ptr ) {

        if ( *list_ptr == NULL ) {

		return 1;

        }

	else {

		return 0;
	}

	return 0;

}

// This function will pop items off the given list until the the isEmpty function returns 1
void freeList ( struct Performance *performance, struct Node **list_ptr ) {

	int j;

	while ( ( isEmpty ( performance, list_ptr ) ) == 0 ) {

		pop ( performance, list_ptr, &j, sizeof ( int ) ) ;

	}

}

// This function will use the next and readHead functions to find the Node i, to retrieve data from the given position in the list
void readItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width ) {

	unsigned int i;

	for ( i = 0; i != index; i++ ) {

		list_ptr = next ( performance, list_ptr );

	}

	readHead ( performance, list_ptr, dest, width );

}

// The function will add an element to the end of the list
void appendItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ) {

	while ( ( !( isEmpty ( performance, list_ptr ) ) ) == 1 ) {

		list_ptr = next ( performance, list_ptr );

	}

	push ( performance, list_ptr, src, width );

}

// This function will use the next and push functions to insert a node at the given index
void insertItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width ) {

	int i;

	for ( i = 0; i != index; i++ ) {

		list_ptr = next ( performance, list_ptr );

	}

	push ( performance, list_ptr, src, width );

}

// This function will use the insertItem function to insert data at position 0
void prependItem ( struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width ) {

	insertItem ( performance, list_ptr, 0, src, width );

}

// This function will use the next and pop functions to remove the node at the given index
void deleteItem ( struct Performance *performance, struct Node **list_ptr, unsigned int index ) {

        int i;

        for ( i = 0; i != index; i++ ) {

                list_ptr = next ( performance, list_ptr );

        }

        pop ( performance, list_ptr, &index, sizeof ( int ) ) ;

}

/* This function will iterate through all items in the list until an item identical to that of the given target is found
   If a match is found the function will return the given index at which the match is located in the list
   if a match is not found the function will simply return -1								*/
int findItem ( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ) {

        unsigned int i = 0;

        char new_temp[STRINGLENGTH];

        while ( (*list_ptr) != NULL ) {

	        readHead ( performance, list_ptr, &new_temp, width );

		if ( compar (&new_temp, target) == 0 ) {

			return i;

		}

                list_ptr = next ( performance, list_ptr );

		i = i + 1;

	}

	return ( -1 );

}
