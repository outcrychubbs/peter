#ifndef MATH_EXT_H
#define MATH_EXT_H

#define EPS_MIN 1e-6f
#define EPS 1e-3f

#define DEGTORADCONST 0.017453292519943295769236907684886
#define RADTODEGCONST 57.295779513082320876798154814105
#define RADIANS(degreeMeasure) (degreeMeasure*DEGTORADCONST)
#define DEGREES(radianMeasure) (radianMeasure*RADTODEGCONST)
#define FREE(str) if(str){free(str);str=0;}
#define DESTROY(OBJ) if(OBJ){delete (OBJ); (OBJ)=0;}
#define DESTROY_ARRAY(ARR) if(ARR){delete[] (ARR); (ARR)=0;}
#define OVERWRITE(OBJ,WITHME) {if(OBJ) delete(OBJ); (OBJ)=WITHME;}


#define FLOOR(x) ( ((x)>0) ? ((int)(x)) : (((int)(x))-1) )
#define CEIL(x) ( ((x)<0) ? ((int)(x)) : ((int)(x)+1) )


#define FLOORPOS(x) ((int)(x))
#define CEILPOS(x) ((int)(x)+1)


#define OTHERAXIS1(axis) ((axis+1)%3)
#define OTHERAXIS2(axis) ((axis+2)%3)

// Gives the biggest of x,y, or z
#define max3(x,y,z) std::max(std::max(x,y),z)
#define min3(x,y,z) std::min(std::min(x,y),z)

inline bool IsPow2( int x )
{
	// the x && in front to make sure 0 isn't considered a power of 2
	return x && ((x & (x-1))==0) ;
}

// The 'i' is for int
inline unsigned int log2i( unsigned int x )
{
	unsigned int log2Val = 0 ;
	

	while( x>>=1 ) log2Val++;  
	
	return log2Val ;
}

// Returns the value of the highest bit in the number..
inline unsigned int hibit( unsigned int x )
{
	unsigned int log2Val = log2i( x ) ; 
	return  (1 << log2Val) ;   
}

int binomial( int n, int k ) ;


inline int NEG( bool neg ){
	return -2*neg+1 ;
}

inline int signum( float val ){
	
	if( val > 0 )  return 1 ;
	else if( val < 0 )  return -1 ;
	else return 0 ;
}

inline int signum( int i ){
	if( i > 0 ) return 1 ;
	else if( i < 0 ) return -1 ;
	else return 0 ;
}

inline bool isNear( float a, float b )
{
	return fabsf( a - b ) <= EPS_MIN ;
}

inline bool isNear( short a, short b, short tolerance )
{
	return abs( a - b ) <= tolerance ;
}


inline bool isNear( float val, float reference, float eps ) 
{
	return fabsf( val-reference ) < eps ;
}

// could be reverse order
template <typename T>
inline bool isBetweenOrdered( T val, T lowerBound, T upperBound ) {
	return lowerBound <= val && val <= upperBound ;
}


template <typename T>
inline bool isBetween( T val, T boundA, T boundB )
{

	return (boundA <= val && val <= boundB) ||
		(boundB <= val && val <= boundA) ;
}

inline float lerp( float t, float A, float B ){
	return A + (B-A)*t ; 
}
inline float unlerp( float v, float A, float B ){
	return (v-A)/(B-A) ;
}

inline float randFloat() {
	return (float)rand()/RAND_MAX ; 
}


inline float randFloat( float low, float high ) {
	return low + (high-low)*randFloat() ;
}

inline float randFloat( float high ) {
	return high*randFloat() ;
}


inline int randInt( int high ) {
	if( !high ) return high ;
	return rand() % high ;
}


inline int randInt( int low, int high ) {

	if( low==high ) return low ;
	return low + rand() % (high-low) ;
}


inline vector<int> randomOrder( int maxVal )
{
	vector<int> results ;

	vector<int> indices( maxVal ) ;

	
	for( int i = 0 ; i < maxVal ; i++ )
		indices[i] = i ;

	


	for( int i = 0 ; i < maxVal ; i++ )
	{
		
		int numsRem = maxVal - i ;

	
		int index = randInt( 0, numsRem ) ;

		
		results.push_back( indices[index] ) ;

	
		::swap( indices[index], indices[numsRem-1] ) ;
	}

	return results ;
}

inline int randSign()
{
	return -1 + 2*randInt(0,2) ; 
}


#endif