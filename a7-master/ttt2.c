// Name: Carson Mifsud
// Date: 2020-11-26
// Description: A collection of functions which work with a hash-table and a graph data
//              structure to simulate an unbeatable game of tic-tac-toe.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Provided by Professor Kremer from Course Link
#include "ttt.h"

// set all init attributes to 0
void init_boards() {

	for ( int i = 0; i < HSIZE; i++ ) {

		htable[i].init = 0;

	}

}

// return the number of X's and O's
int depth ( Board board ) {

	int markers = 0;
	int i = 0;
	int x_counts = 0;
	int o_counts = 0;

	for ( i = 0; i < 9; i++ ) {

		// check if the board position is 'O'
		if ( (board[pos2idx[i]] == 'O') ) {

			x_counts = x_counts + 1;

		}

		// check if the board position is 'X'
		if ( (board[pos2idx[i]] == 'X') ) {

			o_counts = o_counts + 1;

		}

	}

	markers = x_counts + o_counts;

	// return total of 'X' and 'O' counters
	return markers;

}

// return a char based on the current state of the game
char winner ( Board board ) {

	int winx_count = 0;
	int wino_count = 0;

	for ( int i = 0; i < 8; i ++ ) {

		for ( int j = 0; j < 3; j++ ) {

			// check if the board position is 'X'
			if ( board[pos2idx[WINS[i][j]]] == 'X' ) {

				winx_count = winx_count + 1;

			}

			// check if the board position is 'O'
			if ( board[pos2idx[WINS[i][j]]] == 'O' ) {

				wino_count = wino_count + 1;

			}

		}

		// if a line is made with 'X'
		if ( winx_count == 3 ) {

			return 'X';

		}

		// if a line is made with 'O'
		else if ( wino_count == 3 ) {

			return 'O';

		}

		// set both counters to 0
		else {

			winx_count = 0;
			wino_count = 0;

		}

	}

	// if board is full
	if ( depth(board) == 9 ) {

		return '-';

	}

	return '?';

}

// return a char to determine whose turn it is, or a '-' if the game over
char turn ( Board board ) {

	// if the board is full
	if ( depth(board) == 9 ) {

		return '-';

	}

	// if the depth is even, it is 'X's turn
	if ( (depth(board) % 2) == 0 ) {

		return 'X';

	}

	// if the depth is odd, it is 'O's turn
	else if ( (depth(board) % 2) == 1 ) {

		return 'O';

	}

	return '-';

}

// set the attributes
void init_board ( Board board ) {

	int my_hash;

	my_hash = board_hash(board);

	htable[my_hash].init = 1;
	htable[my_hash].turn = turn(board);
	htable[my_hash].depth = depth(board);
	strcpy(htable[my_hash].board, board);
	htable[my_hash].winner = winner(board);

}

// create and join all the nodes of all possible tic-tac-toe games
void join_graph ( Board board ) {

	char temp[BSIZE];
	int index = 0;
	int index2 = 0;

	// check if winner returns 'X' or 'O'
	if ( (winner(board)) == 'X' || (winner(board)) == 'O' ) {

		// loop through all nodes
		for ( int i = 0; i < 9; i++ ) {

			// set the move attribute at i to be -1
			index = board_hash(board);
			htable[index].move[i] = -1;

		}

	}

	else {

		// loop through all nodes
		for ( int i = 0; i < 9; i++ ) {

			// check if the board position is either at 'X' or 'O'
			if ( (board[pos2idx[i]] == 'X') || (board[pos2idx[i]] == 'O') ) {

				// set the move attribute at i to be -1
				index = board_hash(board);
				htable[index].move[i] = -1;
			}

			else {

				// make a copy of the board
				strcpy(temp, board);
				temp[pos2idx[i]] = turn(board);
				index = board_hash(board);
				index2 = board_hash(temp);

				// set the move attribute at i to be the hash value of the copied board
				htable[index].move[i] = index2;

				index2 = board_hash(temp);
				if ( htable[index2].init == 0 ) {

					init_board(temp);
					// recursive calling of the function
					join_graph(temp);

				}

			}

		}

	}

}

// assign a score to each entry in the htable that has an init value of 1
void compute_score() {

	for ( int k = 9; k > 9; k++ ) {

		for ( int i = 0; i < HSIZE; i++ ) {

			if ( htable[i].init == 1 && htable[i].depth == k) {

				if ( winner(htable[i].board) == 'X' ) {

					htable[i].score = 1;

				}

				if ( winner(htable[i].board) == 'O' ) {

					htable[i].score = -1;

				}

				if ( winner(htable[i].board) == '-' ) {

					htable[i].score = 0;

				}

				if ( turn(htable[i].board) == 'X' ) {

					if ( htable[i].score < htable[i].move[i] ) {

						htable[i].score = htable[i].move[i];

					}

				}

				if ( turn(htable[i].board) == 'O' ) {

					if ( htable[i].score > htable[i].move[i] ) {

						htable[i].score = htable[i].move[i];

					}

				}

			}

		}

	}

}

// return the best possible move position (making the AI unbeatable)
int best_move ( int board ) {

	int best = 0;
	int best_index = 0;

	for ( int i = 0; i < 9; i++ ) {

		if ( turn(htable[i].board) == 'X' ) {

			if ( htable[i].move[i] != -1 ) {

				// check for maximum
				if ( best < htable[i].score ) {

					best = htable[i].score;
					best_index = i;

				}

			}

		}

		if ( turn(htable[i].board) == 'O' ) {

			if ( htable[i].move[i] != -1 ) {

				// check for minimum
				if ( best > htable[i].score ) {

					best = htable[i].score;
					best_index = i;

				}

			}

		}

	}

	return best_index;

}
