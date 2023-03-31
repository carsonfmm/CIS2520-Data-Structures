// Provided by Professor Kremer via Course Link
#include "ttt.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Count the number of entries in the htable that have init == 1
int main(int argc, char **argv) {

	int counter = 0;

	init_boards();
	init_board(START_BOARD);
	join_graph(START_BOARD);

	for ( int i = 0; i < HSIZE; i++ ) {

		if ( htable[i].init == 1 ) {

			counter = counter + 1;

		}

	}

	printf("%d\n", counter);

	return ( 0 );

}
