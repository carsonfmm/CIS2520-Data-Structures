// Name: Carson Mifsud
// Date: 2020-11-17
// Description: search for a given key and print the corresponding value
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

	char khs1[100];
	int temp = 0;

	// error message for wrong number of command line arguments
        if ( argc <= 2 || argc > 3 ) {

		fprintf ( stderr, "Usage: %s filename.kv 'search term'\n", argv[0] );
		exit ( 0 );

	}

	// open .kv file for reading
	FILE *fp = fopen ( argv[1], "rb" );
	FILE *fpkhs;

	int cap;
	char key2[STRLEN];


	strncpy ( khs1, argv[1], ( strlen ( argv[1] ) - 3 ) );
	khs1[( strlen ( argv[1] ) - 3 )] = '\0';

	// open .khs file for reading
	fpkhs = fopen ( strcat ( khs1, ".khs" ), "rb" );

	// get capacity of .khs file
	cap = get_capacity ( fpkhs );

	temp = hashfn ( argv[2], cap );

	// set original to calculated hash value
	int original = temp;

	while ( true ) {

		int counter;

		if ( read_index ( fpkhs, temp, &counter) == 1 ) {

			// read the key of the .kv file
			read_key ( fp, counter, key2 );

			// compare the key in the .kv file to the users input
			if ( strcmp ( key2, argv[2] ) == 0 ) {

				// print the value at this index
				read_val ( fp, counter, key2 );
				printf ( "%s\n", key2 );
				return 0;

			}

			temp = temp + 1;

			// if the hash value reaches capacity, set the hash to 0
			if ( temp == cap ) {

				temp = 0;

			}

			// if the hash value reaches the original hash, the key is not found
			if ( temp == original ) {

				printf ( "NOT FOUND\n" );
				break;

			}

		}

	}

	// close all files
	fclose ( fp );
	fclose ( fpkhs );

	return 0;

}
