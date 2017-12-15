#include <stdio.h>
#include <string>
using namespace std;

#include "SDLO.h"
#include "Game.h"
#include "Sprite.h"
#include <time.h>
#include "SDL.h"

// Peter mulcahy
// This is uploaded to my blog, it was aided through the use of the internet.
// This code is riddled with problems as a resul of poor programming, and looking for help at sdl wiki and lazyfoo, and on my uni website. This was also helped along with video tutorials from youtube, google and udemy.
// other sites include gamedev and other gme development sites on google
// This due to the non working program is now put into thoery until later date where i can fix the code and make it run smoothly.

//December 3rd due to unforscene circumastances i have broken my leg and will be in hosptal until i have this operation to sort out my broken leg, 
//i have  unable to fix errors in work, this has been done through the use of research on new complicated methods from others in the industy

// This game is a platformer game featuring a little "Mario trademark of nintendo" bird originally an american football, due to complexity i had changed this, due to the lack of related images i could use

int main(int argc, char* args[])
{
	
	srand(time(0));
	
	// Create our SDL window
	SDL sdl( "SideScroller", 800, 600 );
	

	Game game( sdl );


	while( game.getState() != Game::Exiting )
	{
		
		SDL_Event e;
		while( SDL_PollEvent( &e ) )
		{
			if( e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
			{
				// the game will exit on the next frame
				game.setState( Game::Exiting );
			}
			else if( e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_P )
			{
				game.togglePause();
			}
			else if( e.type == SDL_KEYDOWN && game.getState() == Game::Title )
			{
				game.setState( Game::Running );
			}
		}
		
		
		game.clear();

		// Update the game, move the sprites
		game.update();

		// Draw out the new state
		game.draw();
	}
	
	return 0;
}





