// Name: Carson Mifsud
// Date: 2020-10-27
// Description: This program contains a collection of functions that operate on ordered binary trees.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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

/* This function adds a node to the given pointer.
 */
void attachNode ( struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width ) {

	// malloc a new struct Node structure
	struct Node* new_node =  malloc ( sizeof ( struct Node ) );

	// malloc width bytes of data
	new_node->data = malloc ( width * sizeof ( unsigned int ) );

	 // Error check is new_node is NULL
	if ( new_node == NULL ) {

		fprintf ( stderr, "%s", "Memory allocation failed\n" );
		exit ( 0 );

	}

	// Copy width bytes of data from the parameter src to the address data
	memcpy ( new_node->data, src, width );

	// Copy the address of new_node into pointer pointed to by node_ptr
	(*node_ptr) = new_node;

	// Increment mallocs and writes by 1
	performance->mallocs = performance->mallocs + 1;
	performance->writes = performance->writes + 1;

	// Set higher and lower pointers in structure to NULL
	new_node->lt = NULL;
	new_node->gte = NULL;

}

/* This function uses the compar function to compare the given
 * node with the specified target.
 */
int comparNode ( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target ) {

	// Increment reads by 1
	performance->reads = performance->reads + 1;

	return ( compar ( target, ((*node_ptr)->data)) );

}

/* This function determines the next node in the tree to
 * be visited.
 */
struct Node **next ( struct Performance *performance, struct Node **node_ptr, int direction ) {

	// Error checking if the given tree is empty
	if ( *node_ptr == NULL ) {

		fprintf ( stderr, "%s", "The tree is empty\n" );
		exit ( 0 );

	}

	// Increment reads by 1
	performance->reads = performance->reads + 1;

	// Return lt or gte node pointer depending on the value of the parameter direction
	if ( direction < 0 ) {

		return ( &(*node_ptr)->lt );

	}
	else if ( direction >= 0 )  {

		return ( &(*node_ptr)->gte );

	}

	return 0;

}

/* This function will copy data from a node
 * in the tree into the location given by the
 * dest parameter.
 */
void readNode ( struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width ) {

	// Error checking if the given tree is empty
	if ( *node_ptr == NULL ) {

		fprintf ( stderr, "%s", "The tree is empty\n" );
		exit ( 0 );

	}

	// Increment reads by 1
	performance->reads = performance->reads + 1;

	// Copy width bytes of data from the data pointer into dest
	memcpy ( dest, ( (*node_ptr)->data ), width );

}

/* This function removes an item from a tree consisting
 * of only one node.
 */
void detachNode ( struct Performance *performance, struct Node **node_ptr ) {

	// Error checking if the given tree is empty
	if ( (*node_ptr) == NULL ) {

		fprintf ( stderr, "%s", "The tree is empty\n" );
		exit ( 0 );

	}

	// Update pointer pointed to by node_ptr to be NULL
	( (*node_ptr)->gte ) = NULL;
	( (*node_ptr)->lt ) = NULL;

	// Free data pointer in the node pointed to by the pointer pointed to by node_ptr
	free ( (*node_ptr)->data );
	// Free the pointer pointed to by node_ptr
	free ( (*node_ptr) );

	// Increment frees by 1
	performance->frees = performance->frees + 1;

}

/* This function checks if the pointer pointed to
 * by node_ptr is NULL.
 */
int isEmpty ( struct Performance *performance, struct Node **node_ptr ) {

	if ( (*node_ptr) == NULL ) {

		// Return 1 if the pointer pointed to by node_ptr is NULL
		return 1;

	}

	else {

		// Return 0 if the pointer pointed to by node_ptr is not NULL
		return 0;

	}

	return 0;

}

/* This function adds an item to the tree at the
 * specified spot.
 */
void addItem ( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width ) {

	// Declare a variable to handle the compar function
	int ( *compar_node)(const void *, const void *);
	compar_node = compar;

	int direction;

	// While the tree is not empty, continue through the list
	while ( isEmpty ( performance, node_ptr ) == 0 ) {

		direction = comparNode ( performance, node_ptr, compar_node, src );
		node_ptr = next ( performance, node_ptr, direction );

	}

	// If the tree is empty, attach a node to the end of the list
	if ( isEmpty ( performance, node_ptr ) == 1 ) {

		attachNode ( performance, node_ptr, src, width );

	}

}

/* This function will remove all items from the
 * tree by freeing all memory.
 */
void freeTree ( struct Performance *performance, struct Node **node_ptr ) {

	// If the list is not empty, free the tree
	if ( isEmpty ( performance, node_ptr ) == 0 ) {

		// Recursively call the freeTree function to free the entire tree
		freeTree ( performance, next ( performance, node_ptr, -1 ) );
		freeTree ( performance, next ( performance, node_ptr, 1 ) );
		detachNode ( performance, node_ptr );

	}

}

/* This function will search for an item in the tree and return
 * 1 or 0 depending if a match is found or not.
 */
int searchItem ( struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width ) {

	// Declare a variable to handle the compar function
	int ( *compar_node)(const void *, const void *);
	compar_node = compar;

	int direction;

	// While the compar function returns any value but 0
	while ( !(compar ( target, (*node_ptr)->data ) == 0) ) {

		// Continue to the next node
		direction = comparNode ( performance, node_ptr, compar_node, target );
		node_ptr = next ( performance, node_ptr, direction );

		// If the tree is empty, return 0 for no match found
		if ( isEmpty ( performance, node_ptr ) == 1 ) {

			return 0;

		}

	}

	// If the comparNode function returns any value but 1
	if ( !(comparNode ( performance, node_ptr, compar_node, target ) == 1) ) {

		// Call readNode function
		readNode ( performance, node_ptr, target, width );

		// Return 1 as a match has been found
		return 1;

	}
	else {

		// Else return 0 as no match was found
		return 0;

	}

	return 0;

}

