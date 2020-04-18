/*
 ============================================================================
 Name        : Primes.c
 Author      : John Doe
 Version     :
 Copyright   :
 Description : Sample codes in C99. Requires -std=c99 gcc c-compiler switch
 ============================================================================
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

//-----------------------------------------------------------------------------

_Bool isPrimeA( unsigned long long int primeCandidate ) {

	if ( primeCandidate == 1 ) {
		return false;
	}

	for ( unsigned long long int number = 3; number < primeCandidate; number++ ) {

	    if ( primeCandidate % number == 0 )
	       return false;

	}

	return true;

}//isPrimeA

_Bool isPrimeB( unsigned long long int primeCandidate ) {

	if ( primeCandidate == 2 || primeCandidate == 3 )
	  return true;

	_Bool notPrime =
		(primeCandidate & 1) == 0 ||
		(primeCandidate % 3) == 0;

	if ( notPrime ) {
		return false;
	}

	unsigned long long int root = sqrt( primeCandidate );
	for ( unsigned long long int number = 5; number < root; number++ ) {

	    if ( primeCandidate % number == 0 )
	       return false;

	}

	return true;

}//isPrimeB

//-----------------------------------------------------------------------------

_Bool isPrimeC( unsigned long long int primeCandidate ) {

	// TODO : benchmark this function against other "isPrime...()" implentations
	if (
 	 (primeCandidate == 2  ||
	  primeCandidate == 3  ||
	  primeCandidate == 5  ||
	  primeCandidate == 7  ||
	  primeCandidate == 11 ||
	  primeCandidate == 13)
    ) return true;

	_Bool notPrime =
		((primeCandidate & 1) == 0)  ||
		((primeCandidate % 3) == 0)  ||
		((primeCandidate % 5) == 0)  ||
		((primeCandidate % 7) == 0)  ||
		((primeCandidate % 11) == 0) ||
		((primeCandidate % 13) == 0);

	if ( notPrime ) {
		return false;
	}

	unsigned long long int root = sqrt( primeCandidate );
	for ( unsigned long long int number = 17; number < root; number++ ) {

	    if ( primeCandidate % number == 0 )
	       return false;

	}

	return true;

}//isPrimeC

//-----------------------------------------------------------------------------

void fileOpenAndReadPrimes( void ) {

   char* workingDirectory = NULL;
   char fileName[] = "/primes-first-million-little-endian.bin";
   char seperator  = pathSeperator();
   fileName[ 0 ]   = seperator;

   workingDirectory = getcwd( workingDirectory, 0 );

   char *filePath = pathCombine( workingDirectory, fileName );
   adjustPathSeperator( filePath );

   // open as "r" readonly and "b" binary
   FILE* hFile = fopen( filePath, "rb" );
   if ( NULL == hFile ) {
     exit( EXIT_FAILURE );
   }

   int prime = 0;
   const int million = 1000 * 1000;
   int primeCount = 0;
   int readCount = -1;

   for ( primeCount = 0; primeCount < million; primeCount++ ) {

	   readCount = fread( &prime, sizeof(prime), 1, hFile );
	   if ( readCount <= 0 ) {
		  break;
	   }

   }//for


   fclose( hFile );

   free( filePath );
   free( workingDirectory );

}//fileOpenAndReadPrimes

//-----------------------------------------------------------------------------

int* readPrimes( char fileName[] ) {

	char* workingDirectory = NULL;
	int *primes = NULL;

	// get current working directory
	workingDirectory = getcwd( workingDirectory, 0 );
	if ( NULL == workingDirectory ) {
	   goto EXIT;
	}

	char *filePath = pathCombine( workingDirectory, fileName );
	if ( NULL == filePath ) {
	   goto EXIT;
	}

	adjustPathSeperator( filePath );

	// open as "r" readonly and "b" binary
	FILE* hFile = fopen( filePath, "rb" );
	if ( NULL == hFile ) {
	   goto EXIT;
	}

	const int million = 1000 * 1000;
	primes = (int*) malloc( million * sizeof(int) );
	if ( NULL == primes ) {
	   goto EXIT;
	}

	fread( primes, million * sizeof(int), 1, hFile );
	if ( ferror( hFile ) ) {
	   goto EXIT;
	}

EXIT :

     if ( filePath )
	    free( filePath );

     if ( workingDirectory )
	    free( workingDirectory );

     if ( hFile )
	    fclose( hFile );

	return primes;

}//readPrimes

//-----------------------------------------------------------------------------

void testPrimes( void ) {

	_Bool isp = false;
	isp = isPrimeA( 1 );
	isp = isPrimeA( 2 );
	isp = isPrimeA( 3 );

	char fileName[] = "primes-first-million-little-endian.bin";
	int *primes = (int*) readPrimes( fileName );

	const int million = 1000 * 1000;
    // test first one million precalculated primes with your function
    for ( int i = 0; i < million; i++ ) {

    	int aPrime = primes[ i ];
    	if ( ! isPrimeB( aPrime ) ) {

    		// IF YOUR CONTROL FLOW REACHS THAT POINT, YOUR PRIME TESTING FUNCTION HAS A BUG IN IT !
            exit( EXIT_FAILURE );
    	}

	}//for

    for ( int i = 0; i < million; i++ ) {

    	_Bool isActualPrime = false;
        for ( int j = 0; j < million; j++ ) {
        	if ( i == primes[j] ) {
        	   isActualPrime = true;
        	   break;
        	}
        }

        if ( isActualPrime ) {
        	continue;
        }

    	if ( isPrimeB( i ) ) {

    		// IF YOUR CONTROL FLOW REACHS THAT POINT, YOUR PRIME TESTING FUNCTION HAS A BUG IN IT !
            exit( EXIT_FAILURE );
    	}

	}//for

}//TestPrimes

//-----------------------------------------------------------------------------
