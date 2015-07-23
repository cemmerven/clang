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

void integers( void ) {

	char c    = 0;
	int count = 0;
	int value = 0;

	int           a = 1;
	unsigned int ub = 1;

	size_t size = 0;

	// NOT : char tipinin bit say�s� plartforma g�re de�i�ebilir.
	// Her platformda 8 bit (1 Byte) olmak zorunda de�il.
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

}//integers

//-----------------------------------------------------------------------------

void decimals_Float( void ) {

   float fA = .0F;
   float fB = .0F;

   unsigned int count = 0;
   int value = 0;
   size_t size = 0;

   // char (byte) tipinin katlar� olarak bellekte kaplad��� alan
   size = sizeof( float );
   size = sizeof( fA );

   // bit say�s�
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

   // TODO : decimals_Float �rne�inden yararlanarak deneyleri double tipi i�in uygulay�n�z.

   // char (byte) tipinin katlar� olarak bellekte kaplad��� alan

   // bit say�s�


   // precision  0.???

   //  base 10 of the exponent part of a double.


}//decimals_Double

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

   char c[] = "vwxyz";
   int  *pi;

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

   pi  = c;
   *pi = 1684234849;

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

   int* pi = NULL;

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

}//pointers3

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

   // GCC -std=c99 komut sat�r� parametresi ve #include<stdbool.h> gerekli
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

   char c16 = '\456';
   char c17 = '\xAF';

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
   wchar_t wc01 = L'�';
   size = sizeof( wc01 );


   // UNICODE string literal
   wchar_t text06[] = L"������ ���i�� I�";
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

   // intel specific extendet 80bit (10 Byte)
   long double ldGR = 1.618L;
   long double ldPI = 3.14159265358979323846264338328L;
   long double ld01 = LDBL_EPSILON;

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
             ( c >  10 ) && ( c <= 25 ) ? warm:
             ( c >  25 ) && ( c <= 35 ) ? hot:
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

// iki "int" tipinde de�er alan ve bir "int" tipinde de�er d�nd�ren
// her t�r fonksiyonu g�sterebilen "function pointer" tan�mla.
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
 * parseArguments : kendisine "comand line"dan gelen en az 4 char* arg�man�n�n
 * ge�irilece�ini varsayar ve arg�man karakterleini operat�r ve say�sal de�erlere
 * �evirerek d�nd�r�r.
 * �NEML� NOT : bu "function" kendisine ge�irilen "operand" karakterlerinin rakam
 * olup olmad���n� kontrol etmez.
 *
 * INPUT:
 * in_values[ 0 ] arg�man 1 : program�n "full path"i (kullan�lmaz g�zard� edilir).
 * in_values[ 1 ] arg�man 2 : operat�r karakteri (  +  -  *  / )
 * in_values[ 2 ] arg�man 3 : tamsay� de�er (operand A)
 * in_values[ 3 ] arg�man 4 : tamsay� de�er (operand B)
 *
 * OUTPUT:
 * out_operator : operat�r karakterinin ASCII kodu.
 * out_operandA : tamsay� de�er.
 * out_operandB : tamsay� de�er.
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

		// string'in ba��na git
		valueStart = valueEnd = in_values[ index + 1 ];

		// string'in sonuna git
		while ( *++valueEnd );

		// son, ba�tan b�y�k oldu�u s�rece "geri" git ve basamaklar�n de�erini hesapla
		int place = 1;
		while ( valueStart < valueEnd-- ) {

			*values[ index - 1 ] += ( *valueEnd - '0' ) * place;
			place *= 10;

		}

		index--;

	}//while

}//parseArguments

/*
 *  Eclipse, komut sat�r� parametrelerini belirle:
 *  Run => Debug Configurations... => tab[Arguments] => textbox[Program arguments]: + 1234 789
 */
int functionPointerSample( int argc, char** argv ) {

	const int minArgs = 4;

	if ( argc < minArgs ) {
	   puts( "Arg�man say�s� yetersiz. En az 3 arg�man gerekli." );
	   return EXIT_FAILURE;
	}

	// operat�r ve operandlar�n de�erlerini tutacak de�i�kenleri haz�rla
	char operator = '\0';
	int  operandA = 0;
	int  operandB = 0;

	// komut sat�r�ndan girlen "ham" metinleri "kullan�labilir" veriye �evir
	parseArguments( argv, &operator, &operandA, &operandB );

	// operat�rlere kar��l�k gelen operasyonlar� sa�layan fonksiyonlar�n
	// adreslerini tutan "lookup table"� tan�mla
	const int maxEntries = 255;
	operation operations[ maxEntries ];

	int entryCount = maxEntries;

	// "lookup table"� "no-operation" ile doldurarak ba�lat
	while ( entryCount-- )
		operations[ entryCount ] = nop;

	// ba�lat�lan tabloyu haz�rla
	operations[ '+' ] = add;
	operations[ '-' ] = sub;
	operations[ '*' ] = mul;
	operations[ '/' ] = idv;

	// verilen operat�r�n operasyonunu tablodan bul �a��r ve i�lem sonucunu al
	int result = operations[ operator ]( operandA, operandB );

	// herhangi bir karakterle "no-operation"� dene.
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

   // fun address assignment with and without casting
   fp = (int(*)(int,int)) pv;
   fp = pv;

   result = fp( 5, 3 );

   // cast than call
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
   equal   = 0,
   greater = 1,
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

   wchar_t unicodeA[] = { L'�', L'�', L'�', L'�', L'�', L'�', 0 };
   wchar_t unicodeB[] = L"������";

   int arrW[ 2 ] = { 1, 2, 3 }; // copy the first 2, discard the 3rd.
   int arrX[ 3 ] = { 1, 2, 3 };
   int arrY[ 4 ] = { 1, 2, 3 }; // copy the first 3, leave 4th uninitialized.

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

void multiDimensionalArrays() {

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

	const int sizeI = 4;
	const int sizeJ = 3;
	const int sizeK = 2;

	size_t count = sizeof valuesE;


	for ( int k = 0; k < sizeK; k++ ) {

		for ( int j = 0; j < sizeJ; j++ ) {

			for ( int i = 0; i < sizeI; i++ ) {

				int hundreds = k + 1;
				int tens     = j + 1;
				int ones     = i;

				valuesE[ k ][ j ][ i ] = 100*hundreds + 10*tens + ones;
				printf( "%d%d%d ",  hundreds, tens, ones );

			}//fori

		}//forj

	}//fork

}//multiDimensionalArrays

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
   unsigned int sign     : 1;
   unsigned int decimal  : 21;
   unsigned int fraction : 10;
} Minireal;

typedef enum { black = 30, red, green, yellow, blue, magenta, cyan, white } Color;

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
	Minireal real = { 0, 2345, 678 };

	// -1234.567
	real.sign     = 1;
	real.decimal  = 1234;
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
   // ilgin� bi'�ey yap burada
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

	// acaip bi'�ey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == meaningOfLife )
	    goto CLEANUP;

	// acaip bi'�ey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == largePrime )
	    goto CLEANUP;

	// acaip bi'�ey bulunduysa daha fazla aramaya gerek yok
	if ( rand() == NULL )
	    goto CLEANUP;

	// bulunamad�ysa aramaya devam
	int target = 222;
	for ( int k = 0; k < sizeK; k++ ) {

		for ( int j = 0; j < sizeJ; j++ ) {

			for ( int i = 0; i < sizeI; i++ ) {

				if ( target == values[ k ][ j ][ i ] )
				   goto MULTIBREAK;

			}//fori

		}//forj

	}//fork

	// bi'�ey bulunamad� "targetFound"un �zerinden atla
    goto CLEANUP;

MULTIBREAK:

    targetFound();

CLEANUP:

	free( buffer );

}//goodGotosAlwaysBranchesForward

//-----------------------------------------------------------------------------

typedef union {

	struct {
		int mantissa : 23;
		int exponent : 8;
		int sign     : 1;
	} bv;

	float fv;

}FloatBits;

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


	int a=1, b=2, c=3, i=0; // commas act as separators in this line, not as an operator

	i = (a, b);             // stores b into i

	i = a, b;               // stores a into i. Equivalent to (i = a), b;
	                        // ... a=1, b=2, c=3, i=1
	i = (a += 2, a + b);    // increases a by 2, then stores a+b = 3+2 into i

	i = a += 2, a + b;      // increases a by 2, then stores a to i, and discards unused

	i = a, b, c;            // stores a into i, discarding the unused b and c rvalues

	i = (a, b, c);          // stores c into i, discarding the unused a and b rvalues


	while ( a > 0, a-- );

	for ( int j = 0, k = 10; j < k; j++, k-- );


	return a=4, b=5, c=6;   // returns 6, not 4,

	return 1, 2, 3;         // returns 3, not 1,

	return (1), 2, 3;        // returns 3, not 1,

}//sequentialEvaluation

//-----------------------------------------------------------------------------

typedef struct {
	int X;
	int Y;
} Point;

void structs( void ) {

	size_t position = 0;

	struct { char C; int I; double D; } mix;
	Point point = { 2, 3 };

	mix.C = 'a';
	mix.I = 3;
	mix.D = 1.618;

	position = offsetof(  Point, Y );

}//structs

//-----------------------------------------------------------------------------


int main( int argc, char** argv ) {


	operators_conditionalExpression();
	operators_additive();
	operators_multiplicative();

	functionPointers();

    everyIdentifierHasAnAddress();

    arrays();
    multiDimensionalArrays();
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
