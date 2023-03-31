#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bandb.h"

// Name: Carson Mifsud
// Date: Tuesday, September 22, 2020

// The purpose of the dpff function is to retrieve individual bits from the floating point number at the given address given by src
// and divide this array of bits into the sign, exponent and significand bits
void dpff ( char *sign, char *exponent, char *significand, double *src ) {

	char final[2+12+52];
	unsigned char dest2[8];
	int start = 64 - 1;
	int end = 0 - 1;

	// Calling of getbytes and getbits functions in order to have final[] set to a 64 bit binary number
	getbytes ( dest2, sizeof ( double ), src, 1 );
	getbits ( final, sizeof ( double ), dest2, start, end );

	// Terminating the final array with a null character '\0'
	final[1+11+52] = '\0';

	// Initializing the sign bit and terminating it with a null character
	sign[0] = final[0];
	sign[1] = '\0';

	int i = 0;
	int j = 0;

	// This for loop is used to initialize the exponent bits (11)
	for ( i = 0; i <= 10; i++ ) {

		exponent[i] = final[j+1];
		j++;

	}

	// This for loop is used to initialize the significand bits (52)
	for ( i = 0; i <= 51; i++ ) {

		significand[i] = final[j+1];
		j++;

	}

	// Terminating exponent and significand arrays with the null character '\0'
	exponent[11] = '\0';
	significand[52] = '\0';

}

// The purpose of the spff function is to retrieve individual bits from the floating point number at the given address given by src
// and divide this array of bits into the sign, exponent and significand bits
void spff ( char *sign, char *exponent, char *significand, float *src ) {

	char final[2+9+23];
	unsigned char dest2[4];
	int start = 32 - 1;
	int end = 0 - 1;

	// Calling of getbytes and getbits function in order to have final[] set to a 32 bit binary number
	getbytes ( dest2, sizeof ( float ), src, 1 );
	getbits ( final, sizeof ( float ), dest2, start, end );

	// Terminating the final array with a null character '\0'
	final[1+8+23] = '\0';

	// Initializing the sign bit and terminating it with a null character
	sign[0] = final[0];
	sign[1] = '\0';

	int i = 0;
	int j = 0;

	// This for loop is used to initialize the exponent bits (8)
	for ( i = 0; i <= 7; i++ ) {

		exponent[i] = final[j+1];
		j++;

	}

	// This for loop is used to initialize the significand bits (23)
	for ( i = 0; i <= 22; i++ ) {

		significand[i] = final[j+1];
		j++;

	}

	// Terminating exponent and significand arrays with the null character '\0'
	exponent[8] = '\0';
	significand[23] = '\0';

}

// The purpose of the getbytes function is to cpoy bytes from one memory location to another
void getbytes ( unsigned char dest[], int bytes, void *src, int reverse ) {

	int i, j;
	unsigned char temp[bytes];

	// This if statement checks if the reverse variable is set to 0. If true, 'bytes' characters are copied from src to dest
	if ( reverse == 0 ) {

		memcpy ( dest, src, bytes );

	}
	// This if statement checks if the reverse variable is not set to 0. If true, 'bytes' characters are copied from src to dest in reverse order
	else if ( reverse != 0 ) {

		memcpy ( dest, src, bytes );

		for ( j = 0, i = bytes - 1; i >= 0; j++, i-- ) {

			temp[j] = dest[i];

		}

		for ( i = 0; i < bytes; i++ ) {

			dest[i] = temp[i];

		}

	}

}

// The purpose of the getbits functionis to represent data stored in memory pointed to by the src pointer as a binary number
void getbits ( char dest[], int bytes, void *src, int start, int end ) {

	int the_quotient = 0;
	int total = 8 * bytes;
	char final[total];

	unsigned char dest2[bytes];

	// Calling of the getbytes function to copy bytes from one memory location to another
	getbytes ( dest2, bytes, src, 0 );

	int the_end = 0;
	int byte = 8;


	for ( the_end = 0; the_end < bytes; the_end++ ) {

		for ( the_quotient = byte - 1; the_quotient >= 0; the_quotient-- ) {

			// The following conditional statements are used to convert bytes into bits and store them into the final array
			if ( ( dest2[the_end] & ( 1 << the_quotient ) ) ) {

				final[( the_end + 1 ) * byte - the_quotient - 1] = '1';

			}

			else {

				final[( the_end + 1 ) * byte - the_quotient - 1] = '0';

			}

		}

	}

	int loop = start - end;
	int quotient = start;
	int formula = 0;
	int i = 0;

	// This for loop is used to the bits into the dest array
	for ( i = 0; i < loop; i++ ) {

		formula = ( bytes * 8 ) - quotient - 1;
		dest[i] = final[formula];
		quotient--;

	}

	// This statement is terminating the dest array with the null character '\0'
	dest[i] = '\0';

}

// The purpose of the bits2ull function is to convert a given binary number into a decimal number
unsigned long long bits2ull ( char *bits ) {

	unsigned long long decimal_val = 0;
	int count = 0;
	unsigned long long temp = 1;
	int i;

	// This for loop is used to double the temp variable and increase the count variable by 1 until bits[i] reaches the null character '\0'
	for ( i = 1; bits[i] != '\0'; i++ ) {

		temp = temp * 2;
		count++;

	}

	// This function is used to increase the decimal_val variable by temp each iteration bits[i] is equal to '1'. Thus converting binary to decimal
	for ( i = 0; count >= 0; i++ ) {

		if ( bits[i] == '1' ) {

			decimal_val = decimal_val + temp ;

		}

		temp = temp / 2;
		count--;

	}

	return decimal_val;

}

// The purpose of the bits2ll function is to convert a 2s complement binary number to a decimal number
long long bits2ll ( char *bits ) {

	int i = 1;
	long long decimal_val = 0;
	long long temp = 1;
	int count;

	// This if statement is used as a special case for said 2s complement number due to the maximum size of a long long variable
	if ( strcmp  ( bits, "0111111111111111111111111111111111111111111111111111111111111111" ) == 0 ) {

		decimal_val = 9223372036854775807;

	}

	else {

		// This for loop is used to double the temp variable and increase the count variable by 1 until bits[i] reaches the null character '\0'
		for ( i = 1; bits[i] != '\0'; i++ ) {

			temp = temp * 2;
			count++;

		}

		if ( bits[0] != '0' ) {

			// These calculations are made due to the 2s complement binary number beginning with a '1'. Thus making the final conversion a negative number
			temp = temp * -1;
			decimal_val = decimal_val + temp;
			temp = ( temp * -1 ) / 2;

			// This for loop is used to increase the decimal_val variable by temp each iteration bits[i] is equal to '1'. Thus converting 2s complement binary to decimal
			for ( i = 1; bits[i] != '\0'; i++ ) {

				if ( bits[i] == '1' ) {

					decimal_val = decimal_val + temp;

				}

				temp = temp / 2;

			}
		}

		else {

			// This for loop is used to increase the decimal_val variable by temp each iteration bit[i] is equal to '1'. Thus converting 2s complement binary to decimal
			for ( i = 0; count >= 0; i++ ) {

				if ( bits[i] == '1' ) {

					decimal_val = decimal_val + temp;

				}

				temp = temp / 2;
				count--;

			}

		}

	}

	return decimal_val;

}
