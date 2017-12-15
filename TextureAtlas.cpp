#include "TextureAtlas.h"
#include "StdWilUtil.h"
#include "SDL.h"
#include <fstream>
#include <sstream>
using namespace std;

TextureAtlas::TextureAtlas()
{
	
}

bool TextureAtlas::loadData( string datafile )
{

	ifstream in( datafile.c_str() );
	if( !in )
	{
		error( "Could not load texture atlas datafile %s!", datafile.c_str() );
		return false;
	}

	while( !in.eof() )
	{
		string line;
		getline( in, line );
		if( !line.size() )
			skip;
		istringstream is( line );
		string name, eq;
		is >> name;
		is >> eq;
		
		SDL_Rect rect;
		is >> rect.x;
		is >> rect.y;
		is >> rect.w;
		is >> rect.h;
		spriteRects[ name ] = rect;
		
		printf( "%s @ (%d %d %d %d)\n", name.c_str(), rect.x, rect.y, rect.w, rect.h );
	}
	
	return true;
}
