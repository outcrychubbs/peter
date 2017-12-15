#include "StdWilUtil.h"


string makeString( const char *fmt, ... )
{
  va_list args ;
  va_start( args, fmt ) ;
  char msgBuffer[ 4096 ] ; 
  vsprintf( msgBuffer, fmt, args ) ;
  return string( msgBuffer ) ; 
}


string makeString( const char *fmt, va_list args )
{
  char msgBuffer[ 4096 ] ; 
  vsprintf( msgBuffer, fmt, args ) ;
  return string( msgBuffer ) ; 
}

string makeTime( double s )
{
  unsigned long long floorSec = s ;
  
  unsigned long long hours = floorSec / (60 * 60) ;
  int minutes = (floorSec / 60) % 60 ;
  int seconds = floorSec % 60 ;

  double ms = s - floorSec ;
  int msInt = (int)(ms*1000.) ;
  
  if( !hours )
    return makeString( "%d:%02d.%03d", minutes, seconds, msInt ) ;
  else
    return makeString( "%lld:%02d:%02d.%03d", hours, minutes, seconds, msInt ) ;
}