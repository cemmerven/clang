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
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------

static char* replace( char*, const char, const char ); 

//-----------------------------------------------------------------------------

char pathSeperator( void ) {

   const char winSeperator = '\\';
   const char unxSeperator = '/';
   char seperator          = 0;

   const char* const sourceFile  = __FILE__;

   seperator = strchr( sourceFile, unxSeperator ) ? unxSeperator : winSeperator;

   return seperator;

}//pathSeperator

//-----------------------------------------------------------------------------

 char _emptyText[] = "";

char* pathCombine( const char *s1, const char *s2 ) {

   size_t s1Len = strlen( s1 );      
   size_t s2Len = strlen( s2 );  
   //reserve +1 for the "null" terminator and zero fill.
   
   if ( s1Len + s2Len == 0 ) {
      return _emptyText;
   }

   const int reserveSeperators = 2;
   char *result = malloc( s1Len + s2Len + reserveSeperators );
   if ( NULL == result ) {
      return NULL;
   }

   char *cursor = result;
   
   //char separator[] = " ";
   char mark = pathSeperator();
   //separator[0] = pathSeperator();

   if ( s1 != NULL && s1Len > 0 ) {

      memcpy( cursor, s1, s1Len );
      cursor += s1Len;
   
   }//if

 
   if ( s2 != NULL && s2Len > 0 ) {

      *cursor++ = mark; 

      cursor += s1[ s1Len - 1 ] == mark ? 1 : 0;
      size_t start = s2[ 0 ] == mark ? 1 : 0;
      size_t size =  s2Len - start;
      memcpy( cursor, &s2[ start ], size );
      
      cursor[ size ] = '\0';  
       
   }//if

   return result;

}//pathCombine

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

static char* replace( char *target, const char from, const char to ) {

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
