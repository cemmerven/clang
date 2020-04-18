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

//-----------------------------------------------------------------------------

char pathSeperator() {

   const char winSeperator = '\\';
   const char unxSeperator = '/';
   char seperator          = 0;

   const char* const sourceFile  = __FILE__;

   seperator = strchr( sourceFile, unxSeperator ) ? unxSeperator : winSeperator;

   return seperator;

}//pathSeperator

//-----------------------------------------------------------------------------

char* pathCombine( const char *s1, const char *s2 ) {

	const int reserveSeperators = 3;
	//reserve +1 for the "null" terminator and zero fill.
    char *result = calloc( 1, strlen(s1) + strlen(s2) + reserveSeperators );
    if ( NULL == result ) {
       return NULL;
    }

    // TODO : s1 ve s2 nin başında ve sonunda olabilecek separatörlere göre kod düzzenle

    char separator[] = " ";
    separator[0] = pathSeperator();

    if ( s1 )
       strcpy( result, s1 );

    strcat( result, separator );

    if ( s2 )
       strcat( result, s2 );

    return result;

}//pathCombine

//-----------------------------------------------------------------------------

char* replace( char *target, const char from, const char to ) {

    if ( NULL == target ) {
       return target;
    }

	size_t length = strlen( target );
	for ( int i = 0; i < length; i++ ) {
		if ( target[ i ] == from ) {
			target[ i ] = to;
		}
	}

    return target;

}//replace

//-----------------------------------------------------------------------------

// TODO : test under linux and windows
void adjustPathSeperator( char* path ) {

   const char winSeperator = '\\';
   const char unxSeperator = '/';

   char seperator = pathSeperator();

   unxSeperator == seperator
	  ? replace( path, winSeperator, seperator )
      : replace( path, unxSeperator, seperator );

}//adjustPathSeperator

//-----------------------------------------------------------------------------

