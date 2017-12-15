#include "Log.h"

// LOGGING
const char* progname = "SideScroll" ;


const char* ErrorLevelName[] = {
	"", //0
	"Info", //1
	"Warning", //2
	"",//3
	"Error", //4
	"","","" //5,6,7
} ;

tm* getCurrentTime()
{
	static time_t raw ;

	// grab the current time
	time( &raw ) ;

	// Now create that timeinfo struct
	static tm* timeinfo ;
	timeinfo = localtime( &raw ) ;

	return timeinfo ;
}

char* getCurrentTimeString()
{
	// write time into timeBuff
	static char timeBuf[ 256 ] ;
	strftime( timeBuf, 255, "%c", getCurrentTime() ) ;
	return timeBuf ;
}


void logDecorate( int logLevel, short color, const char *fmt, va_list args )
{

	char msgBuffer[ 4096 ] ;  
	vsprintf( msgBuffer, fmt, args ) ;

	// write time into timeBuff
	char timeBuf[ 32 ] ;
	strftime( timeBuf, 255, "%X", getCurrentTime() ) ;

	// Put it all together
	char buf[ 4096 ] ;

	sprintf( buf, "[ %s ][ %s ][ %s ]:  %s", progname, ErrorLevelName[ logLevel ], timeBuf, msgBuffer ) ;


	puts( buf ) ;
}

string logDecorateGetString( int logLevel, const char *fmt, va_list args )
{
	
	char msgBuffer[ 4096 ] ;  
	vsprintf( msgBuffer, fmt, args ) ;

	// write time into timeBuff.
	char timeBuf[ 32 ] ;
	strftime( timeBuf, 255, "%X", getCurrentTime() ) ;

	// Put it all together
	char buf[ 4096 ] ;

	sprintf( buf, "[ %s ][ %s ][ %s ]:  %s", progname, ErrorLevelName[ logLevel ], timeBuf, msgBuffer ) ;

	
	return string( buf ) ;
}

void error( const char *fmt, ... )
{
	va_list lp ;
	va_start( lp, fmt ) ;

	logDecorate( ErrorLevel::Error, ConsoleRed, fmt, lp ) ;
}

void warning( const char *fmt, ... )
{
	va_list lp ;
	va_start( lp, fmt ) ;

	logDecorate( ErrorLevel::Warning, ConsoleYellow, fmt, lp ) ;
}

void info( short iColor, const char *fmt, ... )
{
	va_list lp ;
	va_start( lp, fmt ) ;

	logDecorate( ErrorLevel::Info, iColor, fmt, lp ) ;
}

void info( const char *fmt, ... )
{
	va_list lp ;
	va_start( lp, fmt ) ;

	logDecorate( ErrorLevel::Info, ConsoleGray, fmt, lp ) ;
}
