#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "player.h"
#include "items.h"

class AGame
{
private:
	// ------------- sfml stuff ---------------
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	sf::Event windowEvent;


	// ------------- game objects -------------
	int score = 0;
	APlayer* player;

	std::vector<AItem*> items;

	// background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	// ------------- Initialization ----------- 
	void initWindow();
	void initGameObjects();


public:
	// ------ Constructor and Destructor ------
	AGame();
	~AGame();

	// ------------- Accessors ----------------

	// ------------- Modifiers ----------------

	// ------------- Functions ----------------
	// main functions
	bool const running() const;
	void pollEvents();

	// update and render functions
	void update(float deltaTime);
	void render();

	// game functions
	void checkPlayerCollisions();
	void spawnItem();
};