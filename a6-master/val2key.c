// Name: Carson Mifsud
// Date: 2020-11-17
// Description: search for a given value and print the corresponding key
//		if a match is found

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Provided by Professor Kremer from Course Link
#include "util.h"
// Provided by Professor Kremer from Course Link
#include "hashfn.h"

int main ( int argc, char **argv ) {

	char vhs1[100];
	int temp = 0;

	// error message, for incorrect number of command line arguments
        if ( argc <= 2 || argc > 3 ) {

		fprintf ( stderr, "Usage: %s filename.kv 'search term'\n", argv[0] );
		exit ( 0 );

	}

	// open the .kv file for reading
	FILE *fp = fopen ( argv[1], "rb" );
	FILE *fpvhs;

	int cap;
	char val2[STRLEN];

	strncpy ( vhs1, argv[1], ( strlen ( argv[1] ) - 3 ) );
	vhs1[( strlen ( argv[1] ) - 3 )] = '\0';

	// open the .khs file for reading
	fpvhs = fopen ( strcat ( vhs1, ".vhs" ), "rb" );

	cap = get_capacity ( fpvhs );

	// calculate the hash value
	temp = hashfn ( argv[2], cap );

	int original = temp;

	while ( true ) {

		int counter;

		if ( read_index ( fpvhs, temp, &counter) == 1 ) {

			// read the value of the .kv file
			read_val ( fp, counter, val2 );

			// if the value equals the users input, then print the match
			if ( strcmp ( val2, argv[2] ) == 0 ) {

				// find the key at index
				read_key ( fp, counter, val2 );
				printf ( "%s\n", val2 );
				return 0;

			}

			temp = temp + 1;

			// if the hash value reaches the capacity, set the hash to 0
			if ( temp == cap ) {

				temp = 0;

			}

			// if the hash value equals the original hash value, no match is found
			if ( temp == original ) {

				printf ( "NOT FOUND\n" );
				break;

			}

		}

	}

	// close all files
	fclose ( fp );
	fclose ( fpvhs );

	return 0;

}
