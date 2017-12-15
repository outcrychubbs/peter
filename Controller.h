#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <sdl.h>
#endif

// handles user input 
class Controller
{
public:
	int mouseX, mouseY;
	
	Controller();
	// Updates the controller
	void update();
};

#endif