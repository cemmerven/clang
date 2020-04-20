
#include<stddef.h>
#include<string.h>

typedef enum TDaysEnglish {
	monday = 1,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
} DaysEnglish;


typedef enum TDaysTurkish {
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

//-----------------------------------------------------------------------------

char* getLatinName( DaysEnglish day ) {

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

//-----------------------------------------------------------------------------

char* getSemiNordicName( DaysEnglish day ) {

	static char error[] = "ukjent dag kode";

	if ( day < 1 || day > 7 ) {
		return error;
	}

	return _daysSemiNordic[ day - 1 ];

}//getSemiNordicName

//-----------------------------------------------------------------------------

char* getEnglishName( DaysEnglish day ) {

	return ( day >= 1 && day <= 7 ) ? _daysEnglish[ day - 1 ] : "unknown day code";

}//getEnglishName

//-----------------------------------------------------------------------------

void enumerationSample( void ) {

   char* dayName = NULL;

   dayName = getEnglishName( 0 );

   DaysEnglish aDay = thursday;
   dayName = getSemiNordicName( aDay );

   DaysEnglish anotherDay = 6;
   dayName = getLatinName( anotherDay );

   dayName = getEnglishName( pazartesi + 2 );

   DaysEnglish nextDay = pazartesi + 1;

}//enumerationSample

//-----------------------------------------------------------------------------

// TODO : string compare sample

typedef enum {
   lesser  = -1,
   equal   =  0,
   greater = +1,
} CompareResult;

typedef enum {
   caseSensitive = 0,
   caseInsensitive,
} Comparison;

CompareResult stringCompare( char * textA, char * textB, Comparison comparison ) {

    int returnValue = 0;
	CompareResult result = 0;

	returnValue = comparison == caseInsensitive
	   ? strcasecmp( textA, textB )   
       : strcmp( textA, textB ); 

    result = returnValue < 0 ? lesser :
             returnValue > 0 ? greater :
             equal;

	return result;     	

}//stringCompare

//-----------------------------------------------------------------------------

