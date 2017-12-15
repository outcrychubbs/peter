#ifndef VECTORF_H
#define VECTORF_H

#include <stdio.h>
#include <float.h>
#include <math.h>
#include "StdWilUtil.h"
#include "math_ext.h"


#define NAN_MOD_SAFETY
#define DEBUG_STOP_ON_NAN


#define NAN_DIV(x,y) ( (!x && !y) ? HUGE : x/y )



union Vector2f
{
	struct { float x,y; } ;
	float elts[2] ;

	Vector2f():x(0.f),y(0.f){}
	Vector2f( float ix, float iy ):x(ix),y(iy){}
	Vector2f( float iv ):x(iv),y(iv){}


	inline Vector2f& operator=( float v ) {
		x=y=v;
		return *this ;
	}

	static inline Vector2f random() { return Vector2f( randFloat(), randFloat() ) ;  }

	static inline Vector2f random(float min, float max) {
		return Vector2f( randFloat(min,max), randFloat(min,max) ) ;
	}

	//CONST
	inline void print() const {
		printf( "(%.2f %.2f) ",x,y ) ;
	}
	inline void print( const char* msg ) const {
		printf( "%s (%.2f %.2f)",msg,x,y ) ;
	}
	inline void println() const {
		printf( "(%.2f %.2f)\n",x,y ) ;
	}
	inline void println( const char* msg ) const {
		printf( "%s (%.2f %.2f)\n",msg,x,y ) ;
	}

	inline float max() const { return ::max( x,y ) ; }
	inline float min() const { return ::min( x,y ) ; }
	inline int minIndex() const { 
		if( x <= y )  return 0 ;
		else return 1 ;
	}
	inline int maxIndex() const { 
		if( x >= y )  return 0 ;
		else  return 1 ;
	}
	inline int fabsMinIndex() const { 
		Vector2f c = fabsCopy() ;
		if( c.x <= c.y )  return 0 ;
		else return 1 ;
	}
	inline int fabsMaxIndex() const { 
		Vector2f c = fabsCopy() ;
		if( c.x >= c.y ) return 0 ;
		else  return 1 ;
	}

	inline float getAvg() const { return (x+y)/2.f ; }
	inline float sum() const { return x+y ; }

	inline Vector2f operator+( const Vector2f& o ) const {
		return Vector2f(x+o.x,y+o.y);
	}
	inline Vector2f operator-() const {
		return Vector2f(-x,-y);
	}
	inline Vector2f operator-( const Vector2f& o ) const {
		return Vector2f(x-o.x,y-o.y);
	}

	inline Vector2f operator*( const Vector2f& o ) const {
		return Vector2f(x*o.x,y*o.y);
	}
	inline Vector2f operator*( float s ) const {
		return Vector2f(x*s,y*s);
	}

	inline Vector2f operator/( const Vector2f& o ) const {
		return Vector2f(x/o.x,y/o.y).checkNaN() ;

	}
	inline Vector2f operator/( float s ) const {
		return Vector2f(x/s,y/s).checkNaN() ;
	}
	inline float cross( const Vector2f& o ) const {
		return x*o.y-y*o.x ;
	}
	inline float dot( const Vector2f& o ) const {
		return x*o.x+y*o.y ;
	}
	inline float len() const {
		return sqrtf( x*x+y*y ) ;
	}
	inline float len2() const {
		return x*x+y*y ;
	}
	inline Vector2f& setLen( float iLen ){
		if( float length = len() )
		{
			*this *= iLen / length;
		}
		return *this;
	}
	inline Vector2f& setAngle( float a ){
	
		x = len();
		
		
		float newX = x * cosf( a );
		float newY = x * sinf( a );
		x=newX, y=newY;
		return *this;
	}
	inline Vector2f normalizedCopy() const {
		return Vector2f( *this ).normalize() ;
	}
	inline float angleWith( const Vector2f& o ) const {
		return acosf( this->normalizedCopy().dot(o.normalizedCopy()) ) ;
	}
	
	inline float signedAngleWith( const Vector2f& o ) const {
		float aThis = atan2f( y, x );
		float aO = atan2f( o.y, o.x ) ;

		return aThis - aO ;
		
	}
	
	inline bool isNear( const Vector2f& o ) const{
		return fabsf(x-o.x)<EPS_MIN && fabsf(y-o.y)<EPS_MIN ;
	}
	inline bool isNear( const Vector2f& o, const Vector2f& maxDiff ) const{
		return fabsf(x-o.x)<maxDiff.x && fabsf(y-o.y)<maxDiff.y ;
	}
	inline bool isCanonical() const {
		return -1.f <= x && x <= 1.f && 
			-1.f <= y && y <= 1.f ;
	}
 
	inline bool isNaN() const {
		return _isnan(x) || _isnan(y) ;
	}
	inline bool isNonZero() const {
		return x || y;
	}

	inline Vector2f& checkNaN() {
		
		if( _isnan( x ) )
			x = HUGE ;
		if( _isnan( y ) )
			y = HUGE ;
		return *this ;
	}

	
	inline bool operator==( const Vector2f& o ) const{
		return x==o.x && y==o.y ;
	}
	inline bool operator!=( const Vector2f& o ) const{
		return x!=o.x || y!=o.y ;
	}



	// Returns true if "this" is closer to A
	// than B
	inline bool isCloserTo( const Vector2f& a, const Vector2f& thanB ){
		return ( *this-a ).len2() < ( *this-thanB ).len2() ;
	}


	inline float parallelPerpX( const Vector2f& fN, Vector2f &vParallel, Vector2f &vPerp ) const
	{
		
		float compParallel = fN.dot( *this ) ;
		vParallel = fN * compParallel ;
		vPerp = (*this) - vParallel ;
		return compParallel ;
	}

	
	inline void parallelPerpComponents( const Vector2f& fN, float &compParallel, float &compPerp ) const
	{
		
		compParallel = fN.dot( *this ) ;
		compPerp = fN.cross( *this ) ;
	}


	inline Vector2f getPerpendicular() const {
		return Vector2f( -y,x ) ;
	}

	inline Vector2f fabsCopy() const {
		return Vector2f( fabsf(x), fabsf(y) ) ;
	}




	//NON-CONST
	inline Vector2f& normalize(){
		float length = len() ;

	
		if( !length ) {
			error( "Vector2f::normalize() attempt to divide by 0" ) ;
			return *this ;
		}

		return (*this)/=length ;
	}
	inline float safeNormalize(){
		float length = len() ;
		if( length )  (*this)/=length ;
		return length ;
	}
	inline Vector2f& operator+=( const Vector2f& o ){
		x+=o.x,y+=o.y;
		return *this ;
	}
	inline Vector2f& operator-=( const Vector2f& o ){
		x-=o.x,y-=o.y;
		return *this ;
	}
	inline Vector2f& operator*=( const Vector2f& o ){
		x*=o.x,y*=o.y;
		return *this ;
	}
	inline Vector2f& operator*=( float s ){
		x*=s,y*=s;
		return *this ;
	}
	inline Vector2f& operator/=( const Vector2f& o ){
		x/=o.x,y/=o.y;
		return checkNaN() ;
	}
	inline Vector2f& operator/=( float s ){
		x/=s,y/=s;
		return checkNaN() ;
	}
#ifdef NAN_MOD_SAFETY

	inline Vector2f& operator%=( float s ){
		if( !s ) {
			error( "mod by 0" ) ;
			return *this ;
		}
		x=fmodf( x,s );  y=fmodf( y,s );
		return *this ;
	}
	inline Vector2f& operator%=( const Vector2f &o ){
		if( !o.x )  error( "mod by 0 (x)" ) ;
		else x=fmodf( x,o.x );
		if( !o.y )  error( "mod by 0 (y)" ) ;  
		else y=fmodf( y,o.y );
		return *this ;
	}
#else
	inline Vector2f& operator%=( float s ){
		x=fmodf( x,s );  y=fmodf( y,s );
		return *this ;
	}
	inline Vector2f& operator%=( const Vector2f &o ){
		x=fmodf( x,o.x );  y=fmodf( y,o.y );
		return *this ;
	}
#endif

	inline Vector2f& wrap( const Vector2f& worldSize ){
		*this += worldSize ;
		return *this %= worldSize ;
	}
	inline Vector2f& clampLen( float maxLen ){
		float length = len() ;
		if( length > maxLen ) 
			return normalize()*=maxLen ;

		return *this ;
	}
	inline Vector2f& clampComponent( float minVal, float maxVal )
	{
		::clamp( x,minVal,maxVal ) ;
		::clamp( y,minVal,maxVal ) ;
		return *this ;
	}
	inline Vector2f& clampComponentBelow( float below )
	{
		if( x < below ) x=below ;
		if( y < below ) y=below ;
		return *this ;
	}
	inline Vector2f& clampComponentAbove( float above )
	{
		if( x > above ) x=above ;
		if( y > above ) y=above ;
		return *this ;
	}
	inline Vector2f& clampBelow( const Vector2f& below )
	{
		if( x < below.x ) x=below.x ;
		if( y < below.y ) y=below.y ;
		return *this ;
	}
	inline Vector2f& clampAbove( const Vector2f& above )
	{
		if( x > above.x ) x=above.x ;
		if( y > above.y ) y=above.y ;
		return *this ;
	}

	inline Vector2f& fabs()
	{
		x=fabsf(x) ;  y=fabsf(y);
		return *this ;
	}
} ;

inline Vector2f operator-( const Vector2f& v, float s )
{
	return Vector2f(v.x-s,v.y-s);
}

inline Vector2f operator-( float s, const Vector2f& v )
{
	return Vector2f(s-v.x,s-v.y);
}

#endif