#include "SDL.h"
#include "SDLO.h"
#include "Sprite.h"


SDL::SDL(const char* title, int windowWidth, int windowHeight):window(0), screenSurface(0), renderer(0),
size(windowWidth, windowHeight)
{
	Sprite::sdl = this;
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		error( "SDL init error: %s\n", SDL_GetError() );
		exit( 1 );
	}

	window = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowWidth, windowHeight, SDL_WINDOW_SHOWN );
	if( !window )
	{
		error("Window could not be created! error: %s\n", SDL_GetError());
		exit( 1 );
	}
	
	
	screenSurface = SDL_GetWindowSurface( window );
	if( !screenSurface )
    {
    	error( "Could not create screenSurface %s", SDL_GetError() );
    }
    
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( !renderer )
    {
		error( "Could not create renderer %s", SDL_GetError() );
	    renderer = SDL_GetRenderer( window );
        if( renderer )
        {
        	
        	SDL_DestroyRenderer( renderer );
    		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        }
    }
    
	
	SDL_SetRenderDrawBlendMode( renderer, SDL_BLENDMODE_BLEND );

}

SDL::~SDL()
{
	SDL_DestroyRenderer(renderer);
	SDL_FreeSurface(screenSurface);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void SDL::setColor( SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
}

// Draws a simple line
void SDL::line( int startX, int startY, int endX, int endY, SDL_Color color )
{
	SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
	SDL_RenderDrawLine( renderer, startX - origin.x, startY - origin.y, endX, endY );
}

void SDL::rect( int x, int y, int w, int h, SDL_Color color )
{
	SDL_Rect rect = { (int)(x - origin.x), (int)(y - origin.y), (int)w, (int)h };
	setColor( color );
	SDL_RenderDrawRect( renderer, &rect );
}

void SDL::rect( RectF rect, SDL_Color color )
{
	SDL_Rect r = { (int)(rect.x - origin.x), (int)(rect.y - origin.y), (int)rect.w, (int)rect.h };
	setColor( color );
	SDL_RenderDrawRect( renderer, &r );
}

void SDL::fillRect( int x, int y, int w, int h, SDL_Color color )
{
	SDL_Rect rect = { (int)(x - origin.x), (int)(y - origin.y), (int)w, (int)h };
	setColor( color );
	SDL_RenderFillRect( renderer, &rect );
}

void SDL::fillRect( RectF rect, SDL_Color color )
{
	SDL_Rect r = { (int)(rect.x - origin.x), (int)(rect.y - origin.y), (int)rect.w, (int)rect.h };
	setColor( color );
	SDL_RenderFillRect( renderer, &r );
}

void SDL::drawTexture( SDL_Texture* tex, SDL_Rect rect )
{
	rect.x -= origin.x;
	rect.y -= origin.y;
	SDL_RenderCopy( renderer, tex, NULL, &rect );
}

void SDL::drawTextureFlippedX( SDL_Texture* tex, SDL_Rect rect )
{
	rect.x -= origin.x;
	rect.y -= origin.y;
	SDL_RenderCopyEx( renderer, tex, NULL, &rect, 0.0, NULL, SDL_RendererFlip::SDL_FLIP_HORIZONTAL );
}

void SDL::drawAtlasSpriteAt( int x, int y, string atlasName, string spriteName )
{
	TextureAtlas *ta = texAtlases[ atlasName ];
	SDL_Rect src = ta->spriteRects[ spriteName ];
	SDL_Rect dst = { (int)(x - origin.x), (int)(y - origin.y), (int)src.w, (int)src.h };
	SDL_RenderCopy( renderer, ta->tex, &src, &dst );
}

void SDL::playMusic( string musicFile )
{
	/// end all other music
	Mix_HaltMusic();

	if( musics.find(musicFile) == musics.end() )
	{
		loadMusic( musicFile );
	}

	Mix_PlayMusic( musics[musicFile], -1 );
}

void SDL::playSound( string soundFile )
{
	if( sfx.find(soundFile) == sfx.end() )
	{
		warning( "Sound %s not yet loaded!", soundFile.c_str() );
		loadWavSound( soundFile );
	}

	Mix_PlayChannel( -1, sfx[soundFile], 0 ) ;
}

SDL_Surface* SDL::loadSurface( string filename )
{

	SDL_Surface *surf = IMG_Load( filename.c_str() );
    if( !surf ) error( "Couldn't load surface `%s`!", filename.c_str() );
    return surf;
}

SDL_Texture* SDL::loadTexture( string filename )
{
	map<string,SDL_Texture*>::iterator iter = texes.find( filename );
	if( iter != texes.end() )
	{
		warning( "%s already loaded", filename.c_str() );
		return iter->second;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface( renderer, loadSurface(filename) );
	if( !tex ) error( "loadTexture: SDL_CreateTextureFromSurface failed %s %s", filename.c_str(), SDL_GetError() );
	SDL_SetTextureBlendMode( tex, SDL_BLENDMODE_BLEND );
	texes[ filename ] = tex;
	return tex;
}

TextureAtlas* SDL::loadAtlas( string imagefile, string datafile )
{
	TextureAtlas * ta = new TextureAtlas();
	ta->tex = loadTexture( imagefile );
	ta->loadData( datafile );
	texAtlases[ imagefile ] = ta;
	return ta;
}

SDL_Texture* SDL::makeText( TTF_Font* font, string text, SDL_Color color )
{
	SDL_Surface *messagesurf = TTF_RenderText_Blended( font, text.c_str(), color );
	if( !messagesurf ) error( "TTF_RenderText_Solid failed %s", text.c_str() );
	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, messagesurf );
	if( !texture ) error( "TTF_RenderText_Solid texture failed %s", text.c_str() );
	SDL_FreeSurface( messagesurf );
	return texture;
}

Mix_Music* SDL::loadMusic( string filename )
{
	if( musics.find(filename) != musics.end() )
	{
		error( "Music %s already loaded", filename.c_str() );
		return 0;
	}

	Mix_Music *music = Mix_LoadMUS( filename.c_str() ) ;
	if( !music ) error( "Couldn't load music `%s`!", filename.c_str() );
	musics[filename] = music;
	return music;
}

Mix_Chunk* SDL::loadWavSound( string waveFilename )
{
	if( sfx.find(waveFilename) != sfx.end() )
	{
		error( "Sound `%s` already loaded", waveFilename.c_str() );
		return sfx[waveFilename];
	}
	
	Mix_Chunk *sound = Mix_LoadWAV( waveFilename.c_str() ) ;
	if( !sound ) error( "Couldn't load sound `%s`!", waveFilename.c_str() );
	sfx[waveFilename] = sound;
	return sound;
}
