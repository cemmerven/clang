/*
 ============================================================================
 Name        : FirstCode.c
 Author      : John Doe
 Version     :
 Copyright   :
 Description : Sample codes in C99. Requires -std=c99 gcc c-compiler switch
 ============================================================================
 */


#include <wchar.h>

#include <limits.h>
#include <float.h>
#include <math.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

//-----------------------------------------------------------------------------

void integers( void ) {

	char c    = 0;
	int count = 0;
	int value = 0;

	int           a = 1;
	unsigned int ub = 1;

	size_t size = 0;

	// NOT : char tipinin bit sayısı plartforma göre değişebilir.
	// Her platformda 8 bit (1 Byte) olmak zorunda değil.
	count = CHAR_BIT;

	value = CHAR_MIN;
	value = CHAR_MAX;

	size = sizeof( char );
    //size = sizeof int;  //syntax error
    size = sizeof value;  // ok

    size = sizeof( c );
    size = sizeof( 0 );
	size = sizeof( 0L );
    size = sizeof( 0LL );

	size = sizeof( int );
	size = sizeof( unsigned int );
	count = CHAR_BIT * sizeof( unsigned int );

	size = sizeof( a );
	size = sizeof( ub );

	ub = (unsigned) 0xFFFFFFFF;
	a  = (signed) ub;
    ub = 0xFFFFFFFF;

}//integers

//-----------------------------------------------------------------------------

void decimals_Float( void ) {

   float fA = .0F;
   float fB = .0F;

   unsigned int count = 0;
   int value = 0;
   size_t size = 0;

   // char (byte) tipinin katları olarak bellekte kapladığı alan
   size = sizeof( float );
   size = sizeof( fA );

   // bit sayısı
   size =  CHAR_BIT * sizeof( float );

   _Bool result = true;

   fA = FLT_MIN;
   fA = FLT_MAX;

   // precision  0.000000
   count = FLT_DIG;

   //  base 10 of the exponent part of a float.
   value = FLT_MIN_10_EXP;
   value = FLT_MAX_10_EXP;

   fA = .0F / .0F;

   fB = sqrtf( -1.00F );
   fB = 1.0F / .00F;
   fB = INFINITY;

   float posInf =  1.0F / 0.0F;
   float negInf = -1.0F / 0.0F;

   fA = NAN;
   result = fA == fA;

}//decimals_Float

//-----------------------------------------------------------------------------

void decimals_Double( void ) {

   // TODO : decimals_Float yararlanarak deneyleri double tipi için uygulayınız

   // char (byte) tipinin katları olarak bellekte kapladığı alan

   // bit sayısı


   // precision  0.???

   //  base 10 of the exponent part of a double.


}//decimals_Double

//-----------------------------------------------------------------------------

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
    float number             = .0F;
    unsigned int diff        = 0;

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

void floatQuirks( void ) {

	float x = 1.1;
	_Bool result = x != 1.1;

    result = (float)x != (double)1.1;
    result = x != 1.1F;

   float f = 0.1F;

   // runtime calculations of values
   f = 0.0F;
   f += 0.2F;
   f += 0.2F;

   f += 0.2F;
   f += 0.2F;
   f += 0.2F;

   f += 0.2F;
   f += 0.2F;

   f += 0.2F;
   f += 0.2F;
   f += 0.2F;

   // compile time calculations of values
   float ft = 0.2F * 10;
   float fs = 0.2F + 0.2F + 0.2F + 0.2F + 0.2F + 0.2F + 0.2F + 0.2F + 0.2F + 0.2F;

   float fk = 0.5F;
   fk = 2.5F;
   float fk1 = 0;

   // runtime calculations of values
   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;

   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;
   fk1 += 2.6F;

   float fk2 = 2.6F * 10;

   result = fk1 == fk2;

   int loop = 10;
   f = 0.0F;

   double value = .02;
   double diff = value - value;
   result = diff == NAN;


   while ( loop-- ) {
      f += 0.1F;
   }


   f = 0.0F;
   for ( int j = 0 ; j < 10; j++ ){
      f += 0.1F;
   }

   result = f == ( 10 * 0.1F );

   float secondFromStart = nextafterf( FLT_EPSILON, INFINITY );

   // round(256.49999) == 256;
   // roundf(256.49999) == 257;

   // for(ever) : http://www.youtube.com/watch?v=IJNR2EpS0jw
   for( double d = 0; d != 0.3; d += 0.1 );

}//floatQuirks

//-----------------------------------------------------------------------------

void pointers1( void ) {

   int a = 0;
   int b = 0;


   unsigned int addressX = 0;
   unsigned int addressY = 0;

   char ar[] = "vwxyz";
   int  *pi;
   int* piA = NULL;
   int* piB = NULL;

   pi = 0;
   pi = '\0';
   pi = NULL;

   pi  = &a;
   *pi = 3;

   addressX = &a;
   addressY = pi;

   a = 5;
   b = *pi;

   pi++;
   *pi = 7;

   pi  = ar;
   *pi = 1684234849;

   a   = 3;
   piA = &a;
   piB = &a;

   int c = 0;
   c = *piA;
   c = *piB;

   c = 4;
   *piB = c;
   c = a + *piA + *piB;

   char d[] = "efgh";
   *pi = *(int*)d;

}//pointers1

//-----------------------------------------------------------------------------

void pointers2( void ) {

   int a = 0;
   int b = 0;
   int c = 0;
   int d = 0;
   int e = 0;

   int* pi  = NULL;

   int arr[] = { 0, 0, 0, 0, 0 };

   pi = &arr[0];
   *pi = 15;

   pi = pi + 1;
   *pi = 20;

   pi += 1;
   *pi = 25;

   pi++;
   *pi = 30;

   *pi++ = 35;

   *pi = 40;

   arr[0] = arr[1] = arr[2] = arr[3] = arr[4] = 0;

   pi = &arr[0];
   *(pi + 0) = 2;
   *(pi + 1) = 4;
   *(pi + 2) = 6;
   *(pi + 3) = 8;
   *(pi + 4) = 10;

   arr[0] = arr[1] = arr[2] = arr[3] = arr[4] = 0;

   pi = &arr[0];
   pi[0] = 3;
   pi[1] = 5;
   pi[2] = 7;
   pi[3] = 9;
   pi[4] = 11;

   arr[0] = arr[1] = arr[2] = arr[3] = arr[4] = 0;

   *arr = 111;
   *(arr + 0) = 100;
   *(arr + 1) = 200;
   *(arr + 2) = 300;
   *(arr + 3) = 400;
   *(arr + 4) = 500;


   pi = &arr[4];
   pi[-4] = 10;
   pi[-3] = 20;
   pi[-2] = 30;
   pi[-1] = 40;
   pi[ 0] = 50;


   pi = &c;

   // !! danger
   *(pi - 1) = 22;
   *(pi - 2) = 11;

   *(pi + 1) = 44;
   *(pi + 2) = 55;

   *(pi + 3) = 66;
   *(pi + 4) = 77;

   a = b = c = d = e;

   pi = (int*)&pi;

   // !! danger
   pi[-1] = 8;
   pi[-2] = 7;
   pi[-3] = 6;
   pi[-4] = 5;
   pi[-5] = 4;

   arr[0] = arr[1] = arr[2] = arr[3] = arr[4] = 0;

   0[arr] = 7;
   1[arr] = 6;
   2[arr] = 5;
   3[arr] = 4;
   4[arr] = 2;

   // http://www.youtube.com/watch?v=IJNR2EpS0jw
   *(pi + 5) = 88;
   *(pi + 6) = 99;

}//pointers2

//-----------------------------------------------------------------------------

void pointers3( void ) {

	int    a =  3;
	int   *b = &a;
	int  **c = &b;
	int ***d = &c;

	   a = 2;
	  *b = 3;
     **c = 4;
	***d = 5;

}//pointers3

//-----------------------------------------------------------------------------

void pointers4( void ) {

   int arrI[ 5 ] = { 10, 20, 30, 40, 50 };

   int *piA = NULL;
   int *piB = NULL;

   long double arrLD[ 5 ] = { .10L, .20L, .30L, .40L, .50L };

   long double *pldA = NULL;
   long double *pldB = NULL;

   size_t        size = 0;
   ptrdiff_t distance = 0;

   piA = &arrI[ 0 ];
   piB = &arrI[ 1 ];

   size = sizeof( int );
   distance = piA - piB;


   pldA = &arrLD[ 0 ];
   pldB = &arrLD[ 1 ];

   size = sizeof( long double );
   distance = pldA - pldB;

}//pointers4

//-----------------------------------------------------------------------------

void pointersConstantPointers( void ) {

   int a = 0;
   int b = 0;

   // both same
   const int *pcA;
   int const *pcB;

   int *const cpi = &a;

   const int *const cpci = &a;

   pcA = &a;
   pcB = &b;

   // *pcA = 3; // error
   // *pcB = 5; // error

   // cpi = &b; // error

}//pointersConstantPointers

//-----------------------------------------------------------------------------

void literals( void ) {

   // size as multiples of char
   size_t size = 0;

   // GCC -std=c99 komut satırı parametresi ve #include<stdbool.h> gerekli
   _Bool result = false;

   /*
   Decimal: 97
   Hex    : 0x61
   Binary : 0b01100001
   Octal  : 0141
   */
   char c = 0;

   c = 97;   // decimal (base 10) literal
   c = 0x61; // hexadecimal (base 16) literal
   c = 0141; // octal (base 8) literal
   c = 'a';  // character literal

   // binary literal, gcc specific
   c = 0b01100001;

   // single char literals (ASCII)
   char c01 = 'a';
   char c02 = -67;
   char c03 = '\0';
   char c04 = 0;

   char c05 = ' ';
   char c06 = '\\';
   //char c07 = ''';

   // non printable chars (escape sequence)
   char c08 = '"';
   char c09 = '\a';
   char c10 = '\b';
   char c11 = '\f';
   char c12 = '\n';
   char c13 = '\r';
   char c14 = '\t';
   char c15 = '\v';

   char c16 = '\456'; // octal
   char c17 = '\xAF'; // hex

   unsigned short     c18 = '\u20AC';
   unsigned short int c19 = '\u20AC';
   unsigned int       c20 = '\U40FFAA11';

   signed int si1 = -3;
   int        si2 = -3;

   long int liA = 10L;
   long     liB = 10L;

   long long int  lliA = 10LL;
   long long      lliB = 10LL;

   unsigned long long int ulliA = 10ULL;
   unsigned long long     ulliB = 10ULL;

   char text01[] = "hello";
   //char text02[] = "I'm";
   //char text03[] = "C:\Windows\System32\drivers\";
   //char text04[] = "he said "hello"";
   //char text05[] = "he said "hello"";

   // UNICODE char literal
   wchar_t wc01 = L'ç';
   size = sizeof( wc01 );

   // UNICODE string literal
   wchar_t text06[] = L"ĞÜŞİÖÇ ğüşiöç Iı";
   size = sizeof( text06 );

   // IEEE 754 single precision floating point number (4 Byte)
   float f01 = 0;
   float f02 = .0;
   float f03 = .0F;
   float f04 = 3.14F;
   float f05 = FLT_EPSILON;

   float pi          = 3.14159;
   float aMole       = 6.02E23;
   float anotherMole = 6.022e23;

   float electronCharge = 1.60217657e-19;
   float protonMass     = 1.67262178e-27;

   // IEEE 754 double precision floating point number (8 Byte)
   double d01 = .0;
   double d02 = .456;
   double d03 = DBL_EPSILON;

   // intel specific extended 80bit (10 Byte)
   long double ldGR = 1.618L;
   long double ldPI = 3.14159265358979323846264338328L;
   long double ld01 = LDBL_EPSILON;

   /* HEXADECIMAL FLOATS
    0x   .  13 x 4 = 52 decimal digits  (Power of 2 decimal digits)
            13 hexadecimal digits       (P - decimal)
   (0x1) . (999999999999A)              P(-4)
   */
   // C99 specific IEEE 754 double precision floating point HEXADECIMAL (base 16) literal
   // 1.100110011001100110011001100110011001100110011001101 x 2^(-4).
   double d04 = 0x1.999999999999Ap-4;

   double d05 = 0xF.999999999999aP-4;
   double d06 = 0xF.FFFFFFFFFFFFFP-4;
   double d07 = 0x1p-1;
   double d08 = 0x2p-1;
   double d09 = 0x3p-1;


}//literals

//-----------------------------------------------------------------------------

void everyIdentifierHasAnAddress( void ) {

   int a = 2;
   int b = 3;
   int c = 0;

   int size = sizeof( int );
   size = sizeof( c );

   int arrA[] = { 10, 20, 30, 40, 50 };
   int arrB[] = { 10, 20, 30, 40, 50 };
   int arrC[] = { 10, 20, 30, 40, 50 };

   int *arrD  = { 10, 20, 30, 40, 50 };// !!

   size = sizeof( arrC );
   size = sizeof( arrD );

   int i = 2;
   c = arrA[ i ];
   c = arrA[ 2 ];
   c = i[ arrA ];
   c = 2[ arrA ];

   c = arrA[ 0 ];
   c = arrD[ 0 ];

   c = arrA[ 2 ];
   //c = arrD[ 2 ];//!!

   c = literals - everyIdentifierHasAnAddress;
   c = &b - &a;
   c = (void*)&b - (void*)&a;

}//everyIdentifierHasAnAddress

//-----------------------------------------------------------------------------

void operators_equality(void){

   // see disassembly
   int a = 2;
   int b = 3;
   int c = 2;

   _Bool result = 0;

   // equality
   result = a == a;

   result = a == b;

   result = a == c;

   result = c == b;


   // inequality
   result = a != a;

   result = a != b;

   result = a != c;

   result = c != b;

}//operators_equality

//-----------------------------------------------------------------------------

void operators_relational( void ) {

  // see disassembly
  int a = 2;
  int b = 3;
  int c = 0;

  _Bool result = 0;

  result = a > b;

  result = a >= b;

  result = a < b;

  result = a <= b;

}//operators_relational

//-----------------------------------------------------------------------------

void operators_logical( void ) {

  // see disassembly
  int a = 2;
  int b = 3;
  int c = 0;

  _Bool result = 0;

  // equality
  result = a == a;
  result = !( a != b );

  // inequality
  result = a != b;
  result = !( a == b );

  // logical and
  result = ( a > b ) && ( b > c );

  // logical inclusive or
  result = ( a > b ) || ( b > c );

  // logical exclusive or (equivalent)
  result = ( a > b ) != ( b > c );

  // bool normalized exclusive or (equivalent)
  result = !a != !c;
  result = (_Bool)a != (_Bool)c;

  result = a >= b;
  result = !( a < b );

  result = a < b;
  result = !( a >= b );

  result = a <= b;
  result = !( a > b );

}//operators_logical

//-----------------------------------------------------------------------------

void operators_assignment( void ) {

   // see disassembly
   int a = 2;
   int b = 3;
   int r = 0;

   r = r + 1;
   r += 1;

   r = r - 1;
   r -= 1;

   r = 1;
   r = r * a;
   r *= a;

   r = r / 2;
   r /= 2;

   r = 5;
   r = r % 2;

   r = 5;
   r %=  2;

   // TODO : di�er "compound assignment" operat�rleri

}//operators_assignment

//-----------------------------------------------------------------------------

void operators_conditionalExpression( void ) {

   // see disassembly
   int a = 2;
   int b = 3;

   int min = 0;
   int max = 0;

   min =  a < b ? a : b;
   max =  a > b ? a : b;

   if ( a < b ) {
      min = a;
   } else {
      min = b;
   };

   if ( a > b ) {
      max = a;
   } else {
      max = b;
   };

   int  x    = 0;
   char sign = '.';

   x = 0;
   sign = x < 0 ? '-' :
          x > 0 ? '+' :
          '.';

   x = -5;
   sign = x < 0 ? '-' :
          x > 0 ? '+' :
          '.';

   x = +5;
   sign = x < 0 ? '-' :
          x > 0 ? '+' :
          '.';

   enum { colder, cold, warm, hot, hotter } climate = colder;

   int c = 18;
   climate = ( c <= -10 ) ? colder :
             ( c > -10 ) && ( c <= 10 ) ? cold :
             ( c >  10 ) && ( c <= 25 ) ? warm :
             ( c >  25 ) && ( c <= 35 ) ? hot  :
             hotter;

}//operators_conditionalExpression

//-----------------------------------------------------------------------------

void operators_multiplicative( void ) {

   // see disassembly
   char ca = 2;
   char cb = 3;
   char cc = 0;

   int ia = 2;
   int ib = 3;
   int ic = 0;

   unsigned int ua = 2;
   unsigned int ub = 3;
   unsigned int uc = 0;

   float fa = .2F;
   float fb = .3F;
   float fc = .0F;

   cc = ca * cb;
   cc = cc / ca;
   cc = cb % ca;

   ic = ia * ib;
   ic = ic / ia;
   ic = ib % ia;

   uc = ua * ub;
   uc = uc / ua;
   uc = ub % ua;

   fc = fa * fb;
   fc = fc / fa;

}//operators_multiplicative

//-----------------------------------------------------------------------------

void operators_additive( void ) {

   // see disassembly
   char ca = 2;
   char cb = 3;
   char cc = 0;

   short sa = 2;
   short sb = 3;
   short sc = 0;

   int ia = 2;
   int ib = 3;
   int ic = 0;

   unsigned int ua = 2;
   unsigned int ub = 3;
   unsigned int uc = 0;

   float fa = .2F;
   float fb = .3F;
   float fc = .0F;

   cc = ca + cb;
   cc = cb - ca;
   cc = ca - cb;

   sc = sa + sb;
   sc = sb - sa;
   sc = sa - sb;

   ic = ia + ib;
   ic = ib - ia;
   ic = ia - ib;

   uc = ua + ub;
   uc = ub - ua;
   uc = ua - ub;

   fc = fa + fb;
   fc = fb - fa;
   fc = fa - fb;

}//operators_additive

//-----------------------------------------------------------------------------

void operators_binary( void ) {

   // see disassembly
   char ca = 2;
   char cb = 3;
   char cc = 0;

   short sa = 2;
   short sb = 3;
   short sc = 0;

   int ia = 2;
   int ib = 3;
   int ic = 0;

   unsigned int ua = 2;
   unsigned int ub = 3;
   unsigned int uc = 0;

   cc = ca & cb;
   cc = ca | cb;
   cc = ca ^ cb;
   cc = ~ca;

   cc = ca << 1;
   cc = ca << 2;

   sc = sa & sb;
   sc = sa | sb;
   sc = sa ^ sb;
   sc = ~sa;

   sc = sa << 1;
   sc = sa << 2;

   sc = -3;
   sc = sc << 1;
   sc = -3;
   sc = sc >> 1;

   ic = ia & ib;
   ic = ia | ib;
   ic = ia ^ ib;
   ic = ~ia;

   ic = -3;
   ic = ic << 1;
   ic = -3;
   ic = ic >> 1;

   uc = ua & ub;
   uc = ua | ub;
   uc = ua ^ ub;
   uc = ~ua;

   uc = 8;
   uc = uc << 1;
   uc = 8;
   uc = uc >> 1;

}//operators_binary

//-----------------------------------------------------------------------------

void controlFlow_if() {

   int a = 2;
   int b = 3;
   int c = 0;

   _Bool result = a < b;

   if ( result )
      c = 1;
   else
	  c = 0;

   if ( a < b )
      c = 1;
   else
	  c = 0;

   if ( !(a < b) )
      c = 0;


   enum { colder, cold, warm, hot, hotter } climate = colder;

   c = 18;

   // if ladder
   if ( c <= -10 ) {

	  climate = colder;

   } else if ( ( c > -10 ) && ( c <= 10 ) ) {

	   climate = cold;

   } else if ( ( c >  10 ) && ( c <= 25 ) ) {

	   climate = warm;

   } else if ( ( c >  25 ) && ( c <= 35 ) ) {

	   climate = hot;

   } else {

	   climate = hotter;

   }//if

   // if-ladder switch case alternative
   climate = ( c <= -10 ) ? colder :
             ( c > -10 ) && ( c <= 10 ) ? cold :
             ( c >  10 ) && ( c <= 25 ) ? warm :
             ( c >  25 ) && ( c <= 35 ) ? hot  :
             hotter;


}//controlFlow_if

//-----------------------------------------------------------------------------

void controlFlow_Switch() {

   int  value = 3;
   char rating = 'X';

   // fall-through switch
   switch( value ) {

	   case 0 :
	   case 1 :
	   case 2 :
		   rating = 'D';
		   break;

	   case 3 :
	   case 4 :
	   case 5 :
		   rating = 'C';
	   break;

	   case 6 :
	   case 7 :
	   case 8 :
		   rating = 'B';
		   break;

	   case 9 :
	   case 10 :
		   rating = 'A';
		   break;

	   default :
		   rating = 'X';

   }//switch

	enum { colder, cold, warm, hot, hotter } climate = cold;
	wchar_t* text = "bilinmiyor";

	// switch without default
	switch ( climate ) {
		case colder : text = L"çok soğuk"; break;
		case cold   : text = L"soğuk";     break;
		case warm   : text = L"ılık";      break;
		case hot    : text = L"sıcak";     break;
		case hotter : text = L"çok sıcak"; break;
	};

}//controlFlow_Switch

//-----------------------------------------------------------------------------

/*
 * switch sample : lookup table
 */
float sinus( int angle ) {

	// TODO : process sign 0..360 degrees
	angle = angle > 45 ? 90 - angle : angle;

	switch( angle ) {

    	default : return NAN;

	    case 0  : return .0000;
		case 1  : return .0175;
		case 2  : return .0349;
		case 3  : return .0523;
		case 4  : return .0698;
		case 5  : return .0872;
		case 6  : return .1045;
		case 7  : return .1219;
		case 8  : return .1392;
		case 9  : return .1564;
		case 10 : return .1736;
		case 11 : return .1908;
		case 12 : return .2079;
		case 13 : return .2250;
		case 14 : return .2419;
		case 15 : return .2588;
		case 16 : return .2756;
		case 17 : return .2924;
		case 18 : return .3090;
		case 19 : return .3256;
		case 20 : return .3420;
		case 21 : return .3584;
		case 22 : return .3746;
		case 23 : return .3907;
		case 24 : return .4067;
		case 25 : return .4226;
		case 26 : return .4384;
		case 27 : return .4540;
		case 28 : return .4695;
		case 29 : return .4848;
		case 30 : return .5000;
		case 31 : return .5150;
		case 32 : return .5299;
		case 33 : return .5446;
		case 34 : return .5592;
		case 35 : return .5736;
		case 36 : return .5878;
		case 37 : return .6018;
		case 38 : return .6157;
		case 39 : return .6293;
		case 40 : return .6428;
		case 41 : return .6561;
		case 42 : return .6691;
		case 43 : return .6820;
		case 44 : return .6947;
		case 45 : return .7071;

	};//switch

}//sinus

//-----------------------------------------------------------------------------

typedef int (*callsomething)( int, int );

int dosomething( int a, int b ) {

	int loop = 3;
	while ( loop-- );

	return 0;

}//dosomething

void dosomething_endmarker( void ) {


}//dosomething_endmarker

void messWithTheFunctions() {

	int size = (void*)dosomething_endmarker - (void*)dosomething;

	char *source = dosomething;
	char *target = calloc( size, sizeof(char) );

	while ( size-- )
		*target++ = *source++;

	callsomething call = target;

	call( 3, 5 );

}//messWithTheFunctions

//-----------------------------------------------------------------------------

void printArguments( int argc, char** argv ) {

	for ( int i = 0; i < argc; i++ ) {
		printf( "[%d] : %s\r\n", (i+1), argv[i] );
	}//for

}//printArguments

//-----------------------------------------------------------------------------

// iki "int" tipinde değer alan ve bir "int" tipinde değer döndüren
// her tür fonksiyonu gösterebilen "function pointer" tanımla.
typedef int (*operation)( int, int );

int nop( int a, int b ) {
	return 0;
}

int add( int a, int b ) {
	return a + b;
}

int sub( int a, int b ) {
	return a - b;
}

int mul( int a, int b ) {
	return a * b;
}

int idv( int a, int b ) {
	return a / b;
}

/*
 * parseArguments : kendisine "comand line"dan gelen en az 4 char* argümanının
 * geçirileceğini varsayar ve argüman karakterleini operatör ve sayısal değerlere
 * çevirerek döndürür.
 * ÖNEMLİ NOT : bu "function" kendisine geçirilen "operand" karakterlerinin rakam
 * olup olmadığını kontrol etmez.
 *
 * INPUT:
 * in_values[ 0 ] argüman 1 : programın "full path"i (kullanılmaz gözardı edilir).
 * in_values[ 1 ] argüman 2 : operatör karakteri (  +  -  *  / )
 * in_values[ 2 ] argüman 3 : tamsayı değer (operand A)
 * in_values[ 3 ] argüman 4 : tamsayı değer (operand B)
 *
 * OUTPUT:
 * out_operator : operatör karakterinin ASCII kodu.
 * out_operandA : tamsayı değer.
 * out_operandB : tamsayı değer.
 *
 * RETURN:
 * void
 */
void parseArguments( char** in_values, char* out_operator, int* out_operandA, int* out_operandB ) {

	*out_operator = in_values[ 1 ][ 0 ];

    int* values[] = { out_operandA, out_operandB };
    int index     = ( sizeof(values) / sizeof(int*) );

	while ( index ) {

		char *valueStart = NULL;
		char *valueEnd   = NULL;

		// string'in başına git
		valueStart = valueEnd = in_values[ index + 1 ];

		// string'in sonuna git
		while ( *++valueEnd );

		// son, baştan büyük olduğu sürece "geri" git ve basamakların değerini hesapla
		int place = 1;
		while ( valueStart < valueEnd-- ) {

			*values[ index - 1 ] += ( *valueEnd - '0' ) * place;
			place *= 10;

		}

		index--;

	}//while

}//parseArguments

/*
 *  Eclipse, komut satırı parametrelerini belirle:
 *  Run => Debug Configurations... => tab[Arguments] => textbox[Program arguments]: + 1234 789
 */
int functionPointerSample( int argc, char** argv ) {

	const int minArgs = 4;

	if ( argc < minArgs ) {
	   puts( "Argüman sayısı yetersiz. En az 3 argüman gerekli." );
	   return EXIT_FAILURE;
	}

	// operatör ve operandların değerlerini tutacak değişkenleri hazırla
	char operator = '\0';
	int  operandA = 0;
	int  operandB = 0;

	// komut satırından girlen "ham" metinleri "kullanılabilir" veriye çevir
	parseArguments( argv, &operator, &operandA, &operandB );

	// operatörlere karşılık gelen operasyonları sağlayan fonksiyonların
	// adreslerini tutan "lookup table"ı tanımla
	const int maxEntries = 255;
	operation operations[ maxEntries ];

	int entryCount = maxEntries;

	// "lookup table"ı "no-operation" ile doldurarak başlat
	while ( entryCount-- )
		operations[ entryCount ] = nop;

	// başlatılan tabloyu hazırla
	operations[ '+' ] = add;
	operations[ '-' ] = sub;
	operations[ '*' ] = mul;
	operations[ '/' ] = idv;

	// verilen operatörün operasyonunu tablodan bul çağır ve işlem sonucunu al
	int result = operations[ operator ]( operandA, operandB );

	// herhangi bir karakterle "no-operation"ı dene.
	result = operations[ '?' ]( operandA, operandB );

	return EXIT_SUCCESS;

}//functionPointerSample

//-----------------------------------------------------------------------------

void functionPointers( void ) {

   int (*fp)( int, int ) = NULL;
   void *pv = NULL;

   int result = 0;

   // both the same
   fp = add;
   fp = &add;

   // old style call
   result = (*fp)( 5,3 );

   // C99 style call
   result = fp( 5, 3 );

   pv = add;

   // function address assignment with and without casting
   fp = (int(*)(int,int)) pv;
   fp = pv;

   result = fp( 5, 3 );

   // cast to function poimter than call :  int(*)(int,int)
   result = ( (int(*)(int,int))pv )( 5, 3 );

   pv = sub;
   result = ( (int(*)(int,int))pv )( 5, 3 );

   pv = mul;
   result = ( (int(*)(int,int))pv )( 5, 3 );

}//functionPointers

//-----------------------------------------------------------------------------


typedef enum {
	monday = 1,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
} Days;

typedef enum {
	pazartesi = 1,
	sali,
	carsamba,
	persembe,
	cuma,
	cumartesi,
	pazar
} DaysTurkish;

 static char* _daysEnglish[] = {
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};

static char* _daysSemiNordic[] = {
	"Mani's dag",
	"Tyr's dag",
	"Odin's dag",
	"Thor's dag",
	"Freya's dag",
	"Saturn's dag"
	"Sunna's dag",
};

char* getLatinName( Days day ) {

	static char error[] = "codex die ignotum";
	char * result = NULL;

	switch ( day ) {

		case monday :
			result = "Lunae";
			break;

		case tuesday :
			result = "Martis";
			break;

		case wednesday :
			result = "Mercuri";
			break;

		case thursday :
			result = "Jovis";
			break;

		case friday :
			result = "Veneris";
			break;

		case saturday :
			result = "Saturni";
			break;

		case sunday :
			result = "Solis";
			break;

		default:
			result = error;
			break;

	}//switch

	return result;

}//getLatinName

// enumeration type definition with TAG
typedef enum TAllColor {
	red = 3,
	green,
	blue,
	cyan,
	magenta,
	yellow,
	black,
	white
} AllColor;

void enums( void ) {

	enum { red, green, blue } colorA,
                              colorB,
	                          colorC,
	                          colorD;

	// enum { red, green, blue } colorE; // error: redeclaration of enumerator

	enum PrintColor { cyan, magenta, yellow, black };

	enum PrintColor colorW;
	enum PrintColor colorX;
	enum PrintColor colorY = black;
	enum PrintColor colorZ = magenta;

    enum TAllColor allA;
    enum TAllColor allB = black;
	AllColor       allC;
	AllColor       allD = white;

	size_t size = 0;
	size = sizeof( colorA );

	colorA = 0;
	colorA = 1;
	colorA = 2;

	colorA = red;
	colorA = green;
	colorA = blue;

	colorA = colorA - 1;
	colorA = colorA - 1;
	colorA = colorA - 1;

	colorA = INT_MIN;
	colorA = INT_MAX;

    colorA = colorZ;

}//enums

char* getSemiNordicName( Days day ) {

	static char error[] = "ukjent dag kode";

	if ( day < 1 || day > 7 ) {
		return error;
	}

	return _daysSemiNordic[ day - 1 ];

}//getSemiNordicName

char* getEnglishName( Days day ) {

	return ( day >= 1 && day <= 7 ) ? _daysEnglish[ day - 1 ] : "unknown day code";

}//getEnglishName

void enumerationSample( void ) {

   char* dayName = NULL;

   dayName = getEnglishName( 0 );

   Days aDay = thursday;
   dayName = getSemiNordicName( aDay );

   Days anotherDay = 6;
   dayName = getLatinName( anotherDay );

   dayName = getEnglishName( pazartesi + 2 );

   Days nextDay = pazartesi + 1;

}//enumerationSample

//-----------------------------------------------------------------------------

// TODO : string compare sample

typedef enum {
   lesser  = -1,
   equal   =  0,
   greater = +1,
} CompareResult;

typedef enum {
   caseSensitive  = 0,
   caseInsensitive,
} Comparison;

CompareResult compare( char * textA, char * textB, Comparison comparison ) {

	return equal;

}//compare

//-----------------------------------------------------------------------------

void arrays( void ) {

   //int arrA[];  // error: array size missing
   int arrA[] = {};
   int arrB[ 0 ];
   int arrC[ 5 ];

   char lettersA[] = { 65, 66, 67, 68, 69 };
   char lettersB[] = { 'A','B','C','D','E' };

   char stringA[] = { 'A','B','C','D','E', 0 };
   char stringB[] = { 'A','B','C','D','E', '\0' };
   char stringC[] = { "ABCDE" };

   wchar_t unicodeA[] = { L'Ğ', L'Ü', L'Ş', L'İ', L'Ö', L'Ç', 0 };
   wchar_t unicodeB[] = L"ĞÜŞİÖÇ";

   int arrQ[ 2 ] = { 1, 2, 3 }; // initialize the first 2, discard the 3rd.
   int arrW[ 3 ] = { 1, 2, 3 }; // initialize all.
   int arrX[ 4 ] = { 1, 2, 3 }; // initialize the first 3, leave 4th uninitialized.
   int arrY[ 5 ] = { [2] = 30 };// initialize the 3rd. initialize the rest with zero.
   int arrZ[ 5 ] = {};          // initialize all with zero.

   size_t size = 0;
   int count   = 0;


   size = sizeof( arrA );
   size = sizeof( arrB );

   size  = sizeof( arrC );
   size  = sizeof arrC;
   count = sizeof( arrC ) / sizeof( int );

   size = sizeof( lettersA );
   size = sizeof( lettersB );

   size = sizeof( stringA );
   size = sizeof( stringB );
   size = sizeof( stringC );

   size = sizeof( wchar_t );
   size = sizeof( unicodeA );

   size  = sizeof( unicodeB );
   count = sizeof( unicodeB ) / sizeof( wchar_t );

   size = sizeof( arrW );
   size = sizeof( arrX );
   size = sizeof( arrY );

   size = sizeof stringB;
   size = sizeof( arrX );
   size = sizeof( arrY );

   size  = sizeof( arrC );
   size  = sizeof arrC;

   arrA[ 0 ] = 1;
   arrB[ 0 ] = 1;

   arrC[ 0 ] = 10;
   arrC[ 1 ] = 20;

}//arrays

//-----------------------------------------------------------------------------

void arrays_variableSize( int length ) {

	//int valuesA[ length ] = {}; // error : variable-sized object may not be initialized
	int valuesA[ length ];

	int* valuesB = malloc( length * sizeof(int) );

	int loop = length;
	while( loop-- )
	   valuesB[ loop ] = valuesA[ loop ] = 0;

}//arrays_variableSize

//-----------------------------------------------------------------------------

// defines special type for ( 3 x 4 ) of integers.
typedef int Special3D[ 3 ][ 4 ];

void arrays_multiDimensional() {

    char valuesA[ 5 ][ 2 ] = { {0,1}, {2,3}, {4,5}, {6,7}, {8,9} };

	int valuesB[   ][ 3 ] = { {1,3,5} , {2,4,6} };
	int valuesC[ 2 ][ 3 ] = { {1,3,5} , {2,4,6} };
	//int valuesC[ 2 ][  ] = { {1,3,5} , {2,4,6} };// error : array type has incomplete element type

	int valuesE[ 2 ][ 3 ][ 4 ] = {
		{
			{111, 112, 113, 114} ,  {121, 122, 123, 124} ,  {131, 132, 133, 134}
		},
		{
			{211, 212, 213, 214} ,  {221, 222, 223, 224} ,  {231, 232, 233, 234}
		}
	};

	int distanceAsBytes = (int)&valuesA[0][0] - (int)&valuesA[1][0];

	// see disassembly
	int value = 0;
	value = valuesA[0][0];
	value = valuesA[0][1];

	value = valuesA[1][0];
	value = valuesA[1][1];

	value = valuesA[2][0];
	value = valuesA[3][1];

	const int lengthI = 4;
	const int lengthJ = 3;
	const int lengthK = 2;

	size_t size = sizeof valuesE;

	for ( int k = 0; k < lengthK; k++ ) {

		for ( int j = 0; j < lengthJ; j++ ) {

			for ( int i = 0; i < lengthI; i++ ) {

				int hundreds = k + 1;
				int tens     = j + 1;
				int ones     = i;

				valuesE[ k ][ j ][ i ] = 100*hundreds + 10*tens + ones;
				printf( "%d%d%d ", hundreds, tens, ones );

			}//fori

		}//forj

	}//fork

	Special3D* p3D = NULL;
	size_t allocateBytes = sizeof(Special3D) * lengthK;

	void* buffer = malloc( allocateBytes );
	if ( buffer == NULL ) {
		// not enough memory, terminate the program with failure
	    exit( EXIT_FAILURE );
	}

	// Casting void* to int(*)[3][4]. Same effect as casting to Special3D*
	p3D = (int(*)[3][4]) buffer;

	for ( int k = 0; k < lengthK; k++ ) {

		for ( int j = 0; j < lengthJ; j++ ) {

			for ( int i = 0; i < lengthI; i++ ) {

				int hundreds = k + 1;
				int tens     = j + 1;
				int ones     = i;

				p3D[ k ][ j ][ i ] = 100*hundreds + 10*tens + ones;

			}//fori

		}//forj

	}//fork

    // free the previously allocated memory
	free( p3D );

}//arrays_multiDimensional

//-----------------------------------------------------------------------------

void arrays_multiDimensionalJagged() {

	// jagged array sample
	// refer https://en.wikipedia.org/wiki/Jagged_array
	int** values = NULL;

    // TODO : implement check for return value of all "malloc()"s for an allocation error
    int arrayCount = 3;
    values = (int**) malloc( arrayCount * sizeof(int*) );

    const int leastElementCount = 2;
	for ( int i = 0; i < arrayCount; i++ ) {

		int  length = i + leastElementCount;
		int* buffer = malloc( length * sizeof(int) );

		values[ i ] = buffer;

		// fill the buffer
		for ( int j = 0; j < length; j++ ) {

			values[ i ][ j ] = i*10 + j;

		}//forj

	}//fori


	int distanceAsBytes = (int)&values[0][0] - (int)&values[1][0];

	// see disassembly
	int value = 0;
	value = values[0][0];
	value = values[0][1];
	value = values[0][2];

	value = values[1][0];
	value = values[1][1];
	value = values[1][2];

	value = values[2][0];
	value = values[2][1];
	value = values[2][2];

	// TODO : we need lots of "free()"s here...

}//arrays_multiDimensionalJagged

//-----------------------------------------------------------------------------

void arrays_multiDimensionalJaggedvsFlat() {

	// jagged array sample
	// refer https://en.wikipedia.org/wiki/Jagged_array

	int** jagged = NULL;
    int   flat[3][3] = { {0,1,2}, {10,11,12}, {20,21,22} };

    // TODO : implement check for return value of all "malloc"s for an allocation error
    int arrayCount = 3;
    jagged = (int**) malloc( 2 * sizeof(int*) );

    const int leastElementCount = 2;
	for ( int i = 0; i < arrayCount; i++ ) {

		int  length = i + leastElementCount;
		int* buffer = malloc( length * sizeof(int) );

		jagged[ i ] = buffer;

		// fill the buffer
		for ( int j = 0; j < length; j++ ) {

			jagged[ i ][ j ] = i*10 + j;

		}//forj

	}//fori

	int distanceAsBytes = 0;
	distanceAsBytes = (int)&jagged[0][0] - (int)&jagged[1][0];
	distanceAsBytes = (int)&flat[0][0]   - (int)&flat[1][0];

	// see disassembly
	int value = 0;

	value = flat[0][0];
	value = jagged[0][0];

	value = jagged[0][0];
	value = jagged[0][1];
	value = jagged[0][2];

	value = jagged[1][0];
	value = jagged[1][1];
	value = jagged[1][2];

	value = flat[0][0];
	value = flat[0][1];
	value = flat[0][2];

	value = flat[1][0];
	value = flat[1][1];
	value = flat[1][2];

	// TODO : we need lots of "free()"s here...

}//arrays_multiDimensionalJagged

//-----------------------------------------------------------------------------

/*
         1 1 0 0 1 0 0 1
         ^             ^
 MSb =>  7 . . . . . . 0  <= LSb
bitIdex  7 6 5 4 3 2 1 0
*/

typedef unsigned char byte;
typedef unsigned int doubleword;
typedef enum { zero, one } BitValue;

doubleword setBit( doubleword value, byte bitIndex ) {

	doubleword mask = 0;

	mask = (unsigned) 1 << bitIndex;
    value |= mask;

	return value;

}//setBit

doubleword resetBit( doubleword value, byte bitIndex ) {

	doubleword mask = 0;

	mask = (unsigned) 1 << bitIndex;
	mask = ~mask;

	value &= mask;

	return value;

}//resetBit

BitValue readBit( doubleword value, byte bitIndex ) {

	doubleword mask = 0;

	mask = (unsigned) 1 << bitIndex;
	mask = ~mask;

	return (value & mask) ? one : zero;

}//readBit

void xorSwap( doubleword* pValueA, doubleword* pValueB ) {

	if ( *pValueA == *pValueA )
		return;

    *pValueA ^= *pValueB;
    *pValueB ^= *pValueA;
    *pValueA ^= *pValueB;

    //*pValueA ^= *pValueB ^= *pValueA ^= *pValueB;

}//xorSwap

void xorIsNonDestructiveOperation( void ) {

   int value = 0xF0000000;

   value = value ^ value;

   value ^= value;
   value ^= value;

   value = 0xFFFF0000;

   value ^= value;
   value ^= value;

   byte cipherKey = '#';
   char message[] = "look to my coming on the first light of the fifth day";

   // cipher
   for ( int i = 0 ; message[ i ] ; i++ ) {

	   message[ i ] ^= (char) cipherKey;

   }

   // decipher
   for ( int i = 0 ; message[ i ] ; i++ ) {

	   message[ i ] ^= (char) cipherKey;

   }

}//xorIsNonDestructiveOperation

#define CLEAR_LOW_NIBBLE (4)
#define CLEAR_HIGH_NIBBLE (0xF)

byte getHighNibble( byte value ) {

	return (byte)( value >> CLEAR_LOW_NIBBLE );

}//getHighNibble

byte getLowNibble( byte value ) {

	return value & CLEAR_HIGH_NIBBLE;

}//getLowNibble

void bitManipulation() {

	BitValue valueAsBit = 0;
	int      result     = 0;
	int      testValue  = 6; // 00000000000000000000000000000110

	valueAsBit = readBit( testValue, 2 );

	result = resetBit( testValue, 2 );
	result = setBit( result, 2 );

	const byte mostSignificantBit  = 31;
	const byte leastSignificantBit = 0;

	// negatif ?
	result = setBit( result, mostSignificantBit );
	result = setBit( result, leastSignificantBit );

	result = resetBit( result, leastSignificantBit );
	result = resetBit( result, mostSignificantBit );

	int a = 3;
	int b = 5;
	xorSwap( &a, &b );

	xorIsNonDestructiveOperation();

	result = getLowNibble( 221 );
	result = getHighNibble( 221 );

	result = getLowNibble( 13 );
	result = getHighNibble( 208 );

	float fA = 2.99F;
	float fB = 1.99F;
	//result = fA & fB; // error invalid operands

}//bitManipulation

//-----------------------------------------------------------------------------

/*
  31        30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10  .  09  08  07  06  05  04  03  02  01     00
  |         |                                                                                   .  |                                       |
  |         |                                                                                      |                                       |
  sign-bit  decimal-bits                                                                           fraction-bits
 */

// Homemade fixed-point number
typedef struct {
   unsigned int fraction : 10;
   unsigned int decimal  : 21;
   unsigned int sign     : 1;
} Minireal;

// refer : http://en.wikipedia.org/wiki/ANSI_escape_code
// Fancy char for color-terminals
typedef struct {
    unsigned short icon      : 8;
    unsigned short color     : 4;
    unsigned short underline : 1;
    unsigned short blink     : 1;
} FancyChar;

// Some hardware register
typedef struct {
     unsigned ready         : 1;
     unsigned error_occured : 1;
     unsigned disk_spinning : 1;
     unsigned write_protect : 1;
     unsigned head_loaded   : 1;
     unsigned error_code    : 8;
     unsigned track         : 9;
     unsigned sector        : 5;
     unsigned command       : 5;
} DiskRegister;

void bitFields( void ) {

	int size = 0;
	size = sizeof(FancyChar);
    size = sizeof(Minireal);
    size = sizeof(DiskRegister);

    // blinking underlined red "A"
    FancyChar character = { 'A',red, true, true };

    character.underline = false;
    character.blink     = false;

	// +2345.678
	Minireal real = { 0, 2345, 1 };

	// -1234.567
	real.sign     = 1;
	real.decimal  = 2345;
	real.fraction = 0;

}//bitFields

//-----------------------------------------------------------------------------

// fast executing small function ( gcc -std=c99 )
static inline void swap( int *x, int *y ) {

    if ( x == y )
    	return;

    *x ^= *y;
	*y ^= *x;
	*x ^= *y;

}//swap

//-----------------------------------------------------------------------------

void targetFound( void ) {
   // ilginç bi'şey yap burada
}//targetFound

void goodGotosAlwaysBranchesForward() {

	static const int meaningOfLife       = 42;
	static const unsigned int largePrime = 2147483647;

	int values[ 2 ][ 3 ][ 4 ] = {
		{
			{111, 112, 113, 114}, {121, 122, 123, 124}, {131, 132, 133, 134}
		},
		{
			{211, 212, 213, 214}, {221, 222, 223, 224}, {231, 232, 233, 234}
		}
	};

	const int sizeI = 4;
	const int sizeJ = 3;
	const int sizeK = 2;

	void *buffer = malloc( sizeof(values) );

	// acaip bi'şey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == meaningOfLife )
	    goto CLEANUP;

	// acaip bi'şey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == largePrime )
	    goto CLEANUP;

	// acaip bi'şey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == NULL )
	    goto CLEANUP;

	// bulunamadıysa aramaya devam
	int target = 222;
	for ( int k = 0; k < sizeK; k++ ) {

		for ( int j = 0; j < sizeJ; j++ ) {

			for ( int i = 0; i < sizeI; i++ ) {

				if ( target == values[ k ][ j ][ i ] )
				   goto MULTIBREAK;

			}//fori

		}//forj

	}//fork

	// bi'şey bulunamadı "targetFound"un üzerinden atla
    goto CLEANUP;

MULTIBREAK:

    targetFound();

CLEANUP:

	free( buffer );

}//goodGotosAlwaysBranchesForward

//-----------------------------------------------------------------------------

int recursionLimit = 16;
void functions_recursiveFunction( void ) {

	if ( recursionLimit-- ) {
		functions_recursiveFunction();
	}

}//functions_recursiveFunction

long long int functions_recursiveFactorial( long long int number ) {

	/*
	if ( number == 0 ) {
	   return 1;
	} else {
	   return number * functions_recursiveFactorial( number - 1 );
	}
    */

	return number == 0 ? 1 : number * functions_recursiveFactorial( number - 1 );

}//functions_recursionFactorial

//-----------------------------------------------------------------------------

long long int functions_sum( int argc, ... ) {

	long long int sum = 0;
	va_list valist;

	// initialize macro
	va_start( valist, argc );

	for ( int i = 0; i < argc; i++)
	{
	   sum += va_arg(valist, int);
	}

	// clean valist left overs
	va_end( valist );

	return sum;

}//functions_sum

//-----------------------------------------------------------------------------

typedef union {

	char  byte;
	short word;
	int   integer;
	long double decimal;
	char text[12];

} Mix;

typedef union {

	struct {
		char cD;
		char cC;
		char cB;
		char cA;
	};

	struct {
		short sL;
		short sH;
	};

	struct {
	    int iValue;
	};

	struct {
	    char car[4];
	};

} MixCSI;

typedef union {

	struct {
		int mantissa : 23; // LSb little endian
		int exponent : 8;
		int sign     : 1;  // MSb little endian
	} bv;

	float fv;

} FloatBits;

typedef union {

	Mix        mix;
	MixCSI     mixCSI;
	FloatBits  bits;

} VeryMix;

void unions( void ) {

   // left uninitialized
   FloatBits bits;
   size_t size = 0;

   size = sizeof( bits );

   bits.fv      = -3.14F;
   bits.bv.sign = 0;

   // initialize with zeros
   MixCSI mcsi = {};
   mcsi.iValue = 0xFAFBFCFD;

   size = sizeof( MixCSI );

   char c = mcsi.cA;

   c = mcsi.cB;
   c = mcsi.cC;
   c = mcsi.cD;

   int s =  mcsi.sL;
   s =  mcsi.sH;

   int i = mcsi.iValue;

   mcsi.cD = 0xFF;

   mcsi.sH = 0xF1F2;

   int loop = 4;
   while ( loop-- )
	  mcsi.car[ loop ] = 68 - loop;

   // initialize with zeros
   Mix mix = {};
   size = sizeof( Mix );

   mix.decimal = -3.14L;
   mix.decimal = LDBL_MAX;

   loop = 12;
   while ( loop-- )
	  mix.text[ loop ] = 80 - loop;


   // initialize with zeros
   VeryMix vmx = {};
   char* pc = (char*) &vmx;

   loop = sizeof( VeryMix );
   while ( loop-- )
	   *pc++ = 0;

   vmx.mixCSI.cD = 65;

}//unions

//-----------------------------------------------------------------------------

void typePromotion( void ) {

	int   i =  1;
	float f =  0.10F;
	float r =  0.00F;

	r = f + i;

	char  c  = 2;
	short s  = 3;
	unsigned int u = 6;

	i = i + c;

	i = i + s;

	i = i + u;

	long long l = 1L + c;

}//typePromotion

//-----------------------------------------------------------------------------

void typePromotionPromoteToInt( void ) {

	// see disassembly
	// all ranks lower than int (signed or unsigned), promote to int
	_Bool b =  false;
	char  c =  'a';
	short s =  -8;

	int r = 0;

	r = b + c + s;

}//typePromotionPromoteToInt

//-----------------------------------------------------------------------------

void typePromotionSameWidth( void ) {

	// see disassembly
	// same size different rank
	signed   int negativeOne =  -1;
	unsigned int positiveOne =  +1;

	_Bool result = false;

	result = positiveOne < negativeOne;

}//typePromotionSameWidth

//-----------------------------------------------------------------------------

void evaluationOrderA( void ) {

	// see disassembly
   int a = 1;
   int b = 2;
   int c = 3;
   int d = 4;

   d = a + b - c + 3;

}//evaluationOrderA

//-----------------------------------------------------------------------------

void evaluationOrderB( void ) {

   // see disassembly
   int a = 1;
   int b = 2;
   int c = 3;
   int d = 4;

   d = a + b * c + 3;

}//evaluationOrderB

//-----------------------------------------------------------------------------

void evaluationOrderC( void ) {

   // see disassembly
   int a = 1;
   int b = 2;
   int c = 3;
   int d = 4;

   d = a = b = c = 5;

}//evaluationOrderC

//-----------------------------------------------------------------------------

void division( void ) {

   // see disassembly
   int a = 5;
   int b = 2;

   unsigned int ua = 5;
   unsigned int ub = 2;

   int          ir = 0;
   unsigned int ur = 0;
   float        fr = 0.0F;

   ir = a / b;

   fr = a / b;

   fr = (float)( a / b );

   fr = (float)a / b;

   fr = a / (float)b;

   ur = ua / ub;

   ur = (float)ua / ub;

}//division

//-----------------------------------------------------------------------------

void modulus( void ) {

   // see disassembly
   int r = 0;

   r = +5 % 3;
   r = -5 % 3;
   r = +5 % -3;

   r = +3 % 5;
   r = +3 % -5;

   r = (int)7.99F % 5;

   int a = 5;
   int b = 3;

   r = +a % 3;
   r = -a % 3;

   r = +a % -3;
   r = -a % -3;

}//modulus

//-----------------------------------------------------------------------------

void initializationOfVariables( void ) {

   // see disassembly
   char           c = 'A';
   unsigned char uc = 'B';

   short          s  = 1;
   unsigned short us = 1;

   int          i  = 3;
   unsigned int ui = 4;

   long long          ll  = 5LL;
   unsigned long long ull = 6ULL;

   float       dA = 1.99F;
   double      dB = 2.99;
   long double dC = 3.99L;


   i = c + 1;
   i = s + 1;
   i = i + 1;

   i = uc + 1;
   i = us + 1;
   i = ui + 1;

   dA = dA + i;
   dB = dB + 1.99;
   dC = dA + dB;

}//initializationOfVariables

//-----------------------------------------------------------------------------

int f( void ) { return 3; }

void expressionEvaluationOrder( void ) {

	// see disassembly
	int a = 0;
	int b = 0;
	int c = 1;

	// ! : not a 1.99 double
	float fA = 0.0F;
	fA = 1,99;
	(fA = 1) , 99;

	a & b || c;

	a && b || c--;

	1 + 2 * 2 ;
	1 + (2 * 2);

	1 + 2 * 2 * 4;
	1 + ( (2 * 2) * 4 );

	( 1 + 2 ) * 2 * 4;
	( (1 + 2) * 2 ) * 4;

	1 + 4, c = 2 | 3 + 5;
	( 1 + 4 ), ( c = ( 2 | ( 3 + 5 ) ) );

	1 + 5 & 4 == 3;
	(1 + 5) & (4 == 3);

	// series of constant expressions
	3 , 4 , 5;

	!a++ + ~f();
	( !(a++) ) + ( ~(f()) );


}//expressionEvaluationOrder

int sequentialEvaluation( void ) {

	// , comma / sequence operator
    // binary operator.
	// Left associative
	// eval first operand than discard it

	int values[2][3] = {
		{0,10,22} , {0,11,22}
	} ;


	int a=1, b=2, c=3, i=0; // commas act as separators in this line, not as an operator

	i = (a, b);             // stores b into i

	i = a, b;               // stores a into i. Equivalent to (i = a), b;
	                        // ... a=1, b=2, c=3, i=1
	i = (a += 2, a + b);    // increases a by 2, then stores a+b = 3+2 into i

	i = a += 2, a + b;      // increases a by 2, then stores a to i, and discards unused

	i = a, b, c;            // stores a into i, discarding the unused b and c rvalues

	i = (a, b, c);          // stores c into i, discarding the unused a and b rvalues


	values[0,1];             // ! not the same thing as values[0][1] : discards 0, use 1 as index
    values[1,1];             // ! not the same thing as values[1][1] : discards left 1, use riht 1 as index

	while ( a > 0, a-- );

	for ( int j = 0, k = 10; j < k; j++, k-- );


	return a=4, b=5, c=6;   // returns 6, not 4,

	return 1, 2, 3;         // returns 3, not 1,

	return (1), 2, 3;        // returns 3, not 1,

}//sequentialEvaluation

//-----------------------------------------------------------------------------

// global (link scope) identifier, with storage
struct {
	float fX;
	float fY;
} PointF;

// declaration (can be many), no storage allocation :
// "there is an identifier definition called PointF in the global (link scope) scope
struct PointF;
struct PointF;
struct PointF;

// global (link scope) identifiers, with storage
struct {
	int X;
	int Y;
} g_pointA, g_pointB, g_pointC, *g_pointer;


// structure definition with TAG (PointD) to refer structure, no storage allocation
struct PointD {
	double dX;
	double dY;
};

// structure type definition without TAG, no storage allocation
typedef struct {
	int X;
	int Y;
} Point;

/*
struct PointX {
	long double ldX;
	long double ldY;
	PointX* pNext; // error : PointX' could not be resolved, unknown type name 'PointX'
};
*/

// structure definition with TAG (PointX)
struct PointX {
	long double ldX;
	long double ldY;
	struct PointX* pNext;
};

typedef struct TBar {
	int A;
	int B;
	struct Foo* pFoo;
} Bar;

typedef struct TFoo {
	int A;
	int B;
	//TBar* pBar; // error :  TBar is not a type definition therefore TBar is unknown type, use: "struct TBar* pBar"  or  "Bar* pBar"
} Foo;

// gcc specific alignment attribute. See also __alignof__ (type)
struct TAlign {
    uint8_t  ui8  __attribute__((aligned(16)));
    uint16_t ui16 __attribute__((aligned(16)));
};

struct PointX structs_asParameterAndReturnValue( struct PointX point ) {

	return *(point.pNext);

}//structs_asParameterAndReturnValue

// TODO : struct flexible array member C99

void structs( void ) {

	struct { char C; int I; double D; } mixA;
	mixA.C = 'a';
	mixA.I = 3;
	mixA.D = 1.618;

	// mixB's type is different than mixA's type although they are looking the same
	struct { char C; int I; double D; } mixB = { 'a', 3, 1.618 };


	// mixA = mixB; // error : incompatible types struct<anonymous>

	PointF.fX = .01F;
	PointF.fX = .02F;

	Point pointA = { 2, 3 };
	Point pointB = { .X = 2, .Y = 3 };
	Point pointC = { .Y = 4 }; // initializes .X with zero

	// pointA = { 4,5 }         // error
	pointA = (Point){ 4, 5 };  // ok : "compound literal" assignment

	// !!
	pointA = (Point){ .Y = 6 }; // !! overrides .X with zero

	//
	pointA = pointB;

	// PointF
    PointF.fY = .1F;
    PointF.fY = .2F;

    //global points
    g_pointA.X = 1;
    g_pointA.Y = 2;

    g_pointB.X = 10;
    g_pointB.Y = 20;

    g_pointC.X = 100;
    g_pointC.Y = 200;

    // assigment (copy)
    g_pointA = g_pointB;

    // struct member referencing
    g_pointer = &g_pointC;
    (*g_pointer).X = 22;
    (*g_pointer).Y = 33;

    // member dereferencing operator
    g_pointer->X = 44;
    g_pointer->Y = 55;

    struct PointD pointD1;
    struct PointD pointD2 = { .1, .2 };

    //pointD1 = { .1, .2 };              // error
    //pointD1 = (PointD){ .1, .2 };      // error
    pointD1 = (struct PointD){ .1, .2 }; // ok : "compound literal" assignment

	size_t position = 0;
	position = offsetof(  Point, Y );

}//structs

//-----------------------------------------------------------------------------

struct TMeasurements {

	unsigned int length;
	long double values[];

};

void structs_flexibleArrayMember( measurementCount ) {

   struct TMeasurements* pMsr;

   size_t bytesAllocated = sizeof(struct TMeasurements) + measurementCount * sizeof(long double);
   pMsr = (struct TMeasurements*) malloc( bytesAllocated );
   pMsr->length = measurementCount;

   const int upperLimit = 10;
   int loop = measurementCount;

   while ( loop-- )
	   pMsr->values[ loop ] = (long double)rand();

}//structs_flexibleArrayMember

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

int split( int const* inArray, const int elementCount, const int splitAfter, int** outLeft, int** outRight ) {

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

}//split

//-----------------------------------------------------------------------------

int main( int argc, char** argv ) {

	int* array             = NULL;
	int resultCode         = 0;
	const int elementCount = 10;

	resultCode = getRandomizedArray( 9, -9, elementCount, &array );
    if ( RDZ_OK != resultCode ) {
    	exit( EXIT_FAILURE );
    }

	int* left  = NULL;
	int* right = NULL;
	resultCode = split( array, elementCount, 3, &left, &right );
    if ( SPLT_OK != resultCode ) {
    	exit( EXIT_FAILURE );
    }

	structs_flexibleArrayMember( 4 );

	arrays_variableSize( 3 );

	unions();

	arrays_multiDimensionalJaggedvsFlat();
	arrays_multiDimensionalJagged();
	arrays_multiDimensional();

	long long int sum = 0;
	sum = functions_sum( 3 , 2, 4, 6 );
	sum = functions_sum( 4 , 1, 3, 5, 7 );


	long long int factorial = functions_recursiveFactorial( 5 );

	functions_recursiveFunction();

	sinus( 120 );

	arrays();

	structs();

	literals();

	floatSteps();

	getLatinName( tuesday );

	operators_conditionalExpression();
	operators_additive();
	operators_multiplicative();

	functionPointers();

    everyIdentifierHasAnAddress();

    arrays();
    arrays_multiDimensional();
	initializationOfVariables();
	sequentialEvaluation();
	bitManipulation();

    int a = 1;

    int x = 1;
    int y = 1;
	int z = 0;


    // conditional evaluation of y
    x && y++;

    //x == 0 ? x += 1: x += 2;
    (x == 0) ? (x += 1) : (x += 2);

	z = !a++;


	z = ( 0, 1, 2, 3 + 4 );

	z = 0;
	a = 0;

	z = !(a++);

	division();

   
	typePromotionPromoteToInt();

	// precedence of post increment
	   int i[] = {3, 5};
	   int *p = i;
	   int j = --*p++;

	typePromotion();
	modulus();
	//SameWidthTypePromotion();


	expressionEvaluationOrder();

	literals();

    bitFields();


	int b = 5;
	swap( &a, &b );

	return EXIT_SUCCESS;

}//main

//-----------------------------------------------------------------------------
