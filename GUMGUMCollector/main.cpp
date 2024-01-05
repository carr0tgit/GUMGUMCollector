#include "game.h"


int main()
{
	// Initialize deltaTime
	sf::Clock clock;
	float deltaTime = 0.0f;

	// Initialize srand
	srand(static_cast<unsigned>(time(NULL)));

	// Initialize 
	AGame Game;

	// Game loop
	while (Game.running())
	{
		// setup deltaTime 
		deltaTime = clock.restart().asSeconds();

		// run game loop
		Game.update(deltaTime);
		Game.render();
	}
	
	return 0;
}

