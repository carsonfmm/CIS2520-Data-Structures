// Provided by Professor Kremer via Course Link
#include "ttt.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// display the value of the board corresponding to the hash values supplied on the command line
int main(int argc, char **argv) {

	int my_hash;

	if ( argc < 2 ) {

		exit ( 1 );

	}

	init_boards();
	init_board(START_BOARD);
	join_graph(START_BOARD);

	my_hash = atoi ( argv[argc-1]);

	print_node(htable[my_hash]);

	return 0;

}

