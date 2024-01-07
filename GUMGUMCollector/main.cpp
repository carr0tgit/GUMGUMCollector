#include "game.h"


int main()
{
	// Initialize srand
	srand(static_cast<unsigned>(time(NULL)));

	// Initialize 
	AGame Game;

	// Game loop
	Game.run();
	
	return 0;
}

