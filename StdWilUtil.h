#ifndef STDWILUTIL_H
#define STDWILUTIL_H

#include <math.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <list>
#include <map>
using namespace std;

#include "Log.h"

typedef unsigned int UInt32;
typedef unsigned char Byte;

#define every(intVal,cycle) (intVal%cycle==0)
#define YesOrNo(x) (x?"Yes":"No")


#define skip continue

template<typename T>
bool contains( const list<T>& container, const T& elt )
{
	return find( container.begin(), container.end(), elt ) != container.end() ;
}

template<typename T>
bool contains( const vector<T>& container, const T& elt )
{
	return find( container.begin(), container.end(), elt ) != container.end() ;
}

template<typename T,typename S>
bool contains( const map<T,S>& container, const T& elt )
{
	return container.find( elt ) != container.end() ;
}

template <typename T> inline T& clamp( T& x, T minVal, T maxVal ) {
	if( x < minVal ) x = minVal ;
	else if( x > maxVal ) x = maxVal ;
	return x ;
}

template <typename T> inline T clampCopy( T x, T minVal, T maxVal ) {
	if( x < minVal ) return minVal ;
	else if( x > maxVal ) return maxVal ;
	else return x ;
}

template <typename T> inline T& clampBelow( T& x, T minVal ) {
	if( x < minVal ) x = minVal ;
	return x ;
}

template <typename T> inline T clampBelowCopy( T x, T minVal ) {
	if( x < minVal ) x = minVal ;
	return x ;
}


template <typename T> inline T& clampAbove( T& x, T maxVal ) {
	if( x > maxVal ) x = maxVal ;
	return x ;
}

template <typename T> inline T clampAboveCopy( T x, T maxVal ) {
	if( x > maxVal ) x = maxVal ;
	return x ;
}


inline float clamp_0( float x ) {
	if( x < 0.0f ) return 0.0f ;
	else return x ;
}


inline float clamp_01( float x ) {
	if( x < 0.0f ) return 0.0f ;
	else if( x > 1.0f ) return 1.0f ;
	else return x ;
}


inline float clamp_11( float x ) {
	if( x < -1.0f ) return -1.0f ;
	else if( x > 1.0f ) return 1.0f ;
	else return x ;
}


inline bool sameSign( float a, float b ){
	return (a > 0.f && b > 0.f) || (a < 0.f && b < 0.f) ;
}

inline bool signDiffers( float a, float b ){

	return (a > 0.f && b < 0.f) || (a < 0.f && b > 0.f) ; 
	
}

inline bool sameSign( float a, float b, float c ){
	return (a > 0.f && b > 0.f && c > 0.f) ||
		(a < 0.f && b < 0.f && c < 0.f) ;
}


inline bool signDiffers( float a, float b, float c ){
	return !sameSign( a, b, c ) ;
}


inline int whichDifferent( float a, float b, float c ){
	if( sameSign(b, c) )  return 0 ;
	else if( sameSign(a, c) )  return 1 ;
	else  
		return 2 ;
}


inline float ratio( float wins, float losses )
{
	if( !wins ) return 0.f ; 
	return wins / (wins+losses);
}

inline int cycleFlag( int &val, int minVal, int maxVal )
{
	if( ++val > maxVal )
		val = minVal;

	return val;
}

inline int decycleFlag( int &val, int minVal, int maxVal )
{
	if( --val < minVal )
		val = maxVal;

	return val;
}

string makeString( const char *fmt, ... );

string makeString( const char *fmt, va_list args ) ;

string makeTime( double s ) ;


#endif