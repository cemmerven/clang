
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "PathUtilities.h"

//-----------------------------------------------------------------------------

void pathCombineTester( void ) {
   
  char *result = pathCombine( "", "" ); 
  assert( result[ 0 ] == 0 );

  result = pathCombine( "root", "" ); 
  assert( strcmp( result,"root") == 0 );

  result = pathCombine( "root\\", "" ); 
  assert( strcmp( result,"root\\") == 0 );

  result = pathCombine( "root", "subdir" ); 
  assert( strcmp( result,"root\\subdir") == 0 );

  result = pathCombine( "root\\", "subdir" ); 
  assert( strcmp( result,"root\\subdir") == 0 );

  result = pathCombine( "root", "\\subdir" ); 
  assert( strcmp( result,"root\\subdir") == 0 );

  result = pathCombine( "root\\", "\\subdir" ); 
  assert( strcmp( result,"root\\subdir") == 0 );

}//pathCombineTester

//-----------------------------------------------------------------------------
