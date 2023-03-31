// Name: Carson Mifsud
// Date: 2020-11-17
// Description: This program will create a hash table for the keys and values
//		in the given .kv file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Provided by Professor Kremer from Course Link
#include "util.h"
// Provided by Professor Kremer from Course Link
#include "hashfn.h"

int main ( int argc, char **argv ) {

	// error message for wrong number of command line arguments
	if ( argc <= 2 || argc > 3 ) {

		fprintf ( stderr, "Usage: %s filename.kv capacity\n", argv[0] );
		exit ( 0 );

	}

	// open the .kv file for reading
	FILE *fp = fopen ( argv[1], "rb" );
	FILE *fpkhs;
	FILE *fpvhs;
	char key_ret[STRLEN];
	char value_ret[STRLEN];
	int temp_hash1;
	int temp_hash2;
	char khs1[100];
	char vhs1[100];
	int capacity = atoi(argv[2]);

	strncpy ( khs1, argv[1], ( strlen ( argv[1] ) - 3 ) );
	khs1[( strlen ( argv[1] ) - 3 )] = '\0';

	strncpy ( vhs1, argv[1], ( strlen ( argv[1] ) - 3 ) );
	vhs1[( strlen ( argv[1] ) - 3 )] = '\0';

	// open the .khs file for reading and writting
	fpkhs = fopen ( strcat ( khs1, ".khs" ), "wb+" );
	// open the .vhs file for reading and writting
	fpvhs = fopen ( strcat ( vhs1, ".vhs" ), "wb+" );

	// initialize .khs file with write_empty
	write_empty ( fpkhs, capacity );
	// initialize .vhs file with write_empty
	write_empty ( fpvhs, capacity );

	// loop until read_keyval does not return 2
	for ( int i = 0; read_keyval ( fp, key_ret, value_ret ) == 2; i++ ) {

		// calculate hash of key and val
		temp_hash1 = hashfn ( key_ret, capacity );
		temp_hash2 = hashfn ( value_ret, capacity );

		while ( true ) {

			int counter;

			read_index( fpkhs, temp_hash1, &counter );

			// if counter equals -1 break out of while loop
			if ( counter == -1 ) {

				break;

			}

			// increment the key hash value
			temp_hash1 = temp_hash1 + 1;

			// if the key hash value reaches the capacity, set the key hash to 0
			if ( temp_hash1 == capacity ) {

				temp_hash1 = 0;

			}

		}

		// write index for the .khs file at the given index and hash
		write_index ( fpkhs, i, temp_hash1 );

                while ( true ) {

                        int counter2;

                        read_index( fpvhs, temp_hash2, &counter2 );

			// if counter2 equals -1, break out of the while loop
                        if ( counter2 == -1 ) {

                                break;

                        }

			// increment the val hash value
                        temp_hash2 = temp_hash2 + 1;

			// if the key hash value reaches capacity, set the val hash to 0
                        if ( temp_hash2 == capacity ) {

                                temp_hash2 = 0;

                        }

                }

		// write index for the .vhs file at the given index and hash
                write_index ( fpvhs, i, temp_hash2 );
	}

	// close all files
	fclose ( fp );
	fclose ( fpkhs );
	fclose ( fpvhs );

	return 0;

}
