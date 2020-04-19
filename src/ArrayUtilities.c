#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------

#define RDZ_OK                 (0)
#define RDZ_ARRAY_SIZE_ERROR   (1)
#define RDZ_RANDOM_RANGE_ERROR (2)
#define RDZ_ALLOCATION_ERROR   (3)

int getRandomizedArray( int min, int max, const int elementCount, int** outArray ) {

	if ( elementCount <= 0 || elementCount >= INT_MAX / 2 ) {
       return RDZ_ARRAY_SIZE_ERROR;
	}

	if ( min > max ) {
       min ^= max ^= min ^= max;
	}

	const int halfRange = RAND_MAX / 2;
	if ( min <= -halfRange ||  max >= halfRange ) {
	   return RDZ_RANDOM_RANGE_ERROR;
	}

	int* intBuffer = (int*) malloc( elementCount * sizeof(int) );
	if ( intBuffer == NULL ) {
	   return RDZ_ALLOCATION_ERROR;
	}

	for ( int i = 0; i < elementCount; i++ ) {

		int value = min + (rand() % (int)(max - min + 1) );
		intBuffer[ i ] = value;

	}//for

	*outArray = intBuffer;

	return RDZ_OK;

}//getRandomizedArray

//-----------------------------------------------------------------------------

#define SPLT_OK                         (0)
#define SPLT_SPLIT_INDEX_OUT_OF_BOUNDS  (1)
#define SPLT_INPUT_ARRAY_IS_NULL        (2)
#define SPLT_INVALID_ARRAY_LENGTH       (3)
#define SPLT_ALLOCATION_ERROR           (4)

int splitArray( int const* inArray, const int elementCount, const int splitAfter, int** outLeft, int** outRight ) {

	if ( inArray == NULL ) {
	   return SPLT_INPUT_ARRAY_IS_NULL;
	}

	if ( elementCount <= 0 ) {
	   return SPLT_INVALID_ARRAY_LENGTH;
	}

	if ( splitAfter <= 0 || splitAfter > elementCount - 1 ) {
	   return SPLT_SPLIT_INDEX_OUT_OF_BOUNDS;
	}

	int leftLegth  = splitAfter + 1;
	int rightLegth = elementCount - leftLegth;

	int* leftBuffer  = (int*) malloc( leftLegth );
	if ( NULL == leftBuffer ) {
       return SPLT_ALLOCATION_ERROR;
	}

	int* rightBuffer = (int*) malloc( rightLegth );
	if ( NULL == rightBuffer ) {
	   if ( NULL != leftBuffer ) {
		  free( leftBuffer );
	   }
       return SPLT_ALLOCATION_ERROR;
	}

	memcpy( leftBuffer,  &inArray[ 0 ], leftLegth * sizeof(int) );
	memcpy( rightBuffer, &inArray[ leftLegth ], rightLegth * sizeof(int) );

	*outLeft  = leftBuffer;
	*outRight = rightBuffer;

    return SPLT_OK;

}//splitArray

//-----------------------------------------------------------------------------

void getRandomizedArray_Tester( void ) {

    int* array             = NULL;
	int resultCode         = 0;
	const int elementCount = 10;

	int resultCode = getRandomizedArray( 9, -9, elementCount, &array );
    if ( RDZ_OK != resultCode ) {
    	exit( EXIT_FAILURE );
    }

}//getRandomizedArray_Tester

//-----------------------------------------------------------------------------

void splitArray_Tester( void ) {

    int* array = NULL;
	int* left  = NULL;
	int* right = NULL;
	const int elementCount = 10;

	int resultCode = getRandomizedArray( 9, -9, elementCount, &array );
    if ( RDZ_OK != resultCode ) {
    	exit( EXIT_FAILURE );
    }

	int resultCode = split( array, elementCount, 3, &left, &right );
    if ( SPLT_OK != resultCode ) {
    	exit( EXIT_FAILURE );
    }

}//splitArray_Tester

//-----------------------------------------------------------------------------