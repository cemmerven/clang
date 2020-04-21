
#include <limits.h>
#include <float.h>
#include <math.h>

/*  Return the ULP of q.

    This was inspired by Algorithm 3.5 in Siegfried M. Rump, Takeshi Ogita, and
    Shin'ichi Oishi, "Accurate Floating-Point Summation", _Technical Report
    05.12_, Faculty for Information and Communication Sciences, Hamburg
    University of Technology, November 13, 2005.
*/
float ULP( float q ) {

    // SmallestPositive is the smallest positive floating-point number.
    static const float SmallestPositive = FLT_EPSILON * FLT_MIN;

    /*  Scale is .75 ULP, so multiplying it by any significand in [1, 2) yields
        something in [.75 ULP, 1.5 ULP) (even with rounding).
    */
    static const float Scale = 0.75 * FLT_EPSILON;

    q = fabs(q);

    // link with linker command line option -lm (Link Math library) otherwise fmax goes undefined
    return fmax(SmallestPositive, q - (q - q * Scale));

}//ULP

//-----------------------------------------------------------------------------

/*  Return the next floating-point value after the finite value q.

    This was inspired by Algorithm 3.5 in Siegfried M. Rump, Takeshi Ogita, and
    Shin'ichi Oishi, "Accurate Floating-Point Summation", _Technical Report
    05.12_, Faculty for Information and Communication Sciences, Hamburg
    University of Technology, November 13, 2005.
*/

float nextAfter( float q ) {
    // SmallestPositive is the smallest positive floating-point number.
    static const float SmallestPositive = FLT_EPSILON * FLT_MIN;

    /*  Scale is .625 ULP, so multiplying it by any significand in [1, 2)
        yields something in [.625 ULP, 1.25 ULP].
    */
    static const float Scale = 0.625 * FLT_EPSILON;

    // link with linker command line option -lm (Link Math library) otherwise fmax goes undefined
    return q + fmax(SmallestPositive, fabs(q)*Scale);

}//nextAfter

//-----------------------------------------------------------------------------

unsigned long long floatSteps( void ) {

	unsigned long long steps = 0;
	long double next         = .0F;
    float number            = .0F;
    unsigned int diff       = 0;

	for ( next = -FLT_MIN, steps = 1; next < FLT_MAX; steps++ ) {

		number = nextafterf( number, FLT_MAX );
        if ( number == HUGE_VALF ) {
           break;
        }

        next = number;

	}//for

	// 2^32 - (representable negative + positive float count)
	diff = UINT_MAX - steps;

	// another way
	float f = - FLT_MAX;
	long long count = 1;

	do {

       f = nextafterf( f, FLT_MAX );
	   count++;

	} while ( f != FLT_MAX );

	return steps;

}//floatSteps

//-----------------------------------------------------------------------------