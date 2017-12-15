#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include "SDLO.h"
#include "Sprite.h"
#include "Controller.h"
#include "TitleScreen.h"
#include "Level.h"
#include "Player.h"

class Game
{
public:
	enum GameState { Title, Running, Paused, Exiting };
	
private:
	// The SDL object, which allows it to play sounds
	SDL* sdl;
	
	
	TitleScreen* title;
	Sprite* pausedText;
	SDL_Color bkgColor;	// the current background color
	
	Level* level;
	Player* player;

	// The font used to draw the scores
	TTF_Font* font;

	/
	GameState gameState;
	
	// An object to represent the game controller
	Controller controller;

	Vector2f camPos;
	
public:
	Game( SDL& iSdl );
	~Game();
	GameState getState();

	void setState( GameState newState );
	void togglePause();
	void drawScores();
	void checkForCollisions();
	void runGame();
	void update();
	void clear();
	void draw();
};

#endif