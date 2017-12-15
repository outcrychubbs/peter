#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "SDL.h"
#include <sdl.h>

#include <map>
#include <string>
using namespace std;

class SDL;

class TextureAtlas
{
public:
	// The rectangles of sprites 
	map<string, SDL_Rect> spriteRects;
	SDL_Texture* tex;
	
	TextureAtlas();
	bool loadData( string datafile );
};

#endif