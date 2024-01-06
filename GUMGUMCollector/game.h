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

	// ------------- settings -----------------
	float soundVolume = 50.0f;
	// ------------- game objects -------------
	int score = 0;
	APlayer* player;

	std::vector<AItem*> items;
	float previousItemX;
	float previousCannonX;
	float itemTimer;
	float cannonTimer;
	float cannonReload; // how long till next shot
	int cannonTotal; // counts cannon shots

	// mouse position
	sf::Vector2i mousePosition;

	// background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Text scoreText;
	sf::Font font;

	sf::Texture healthTexture;
	sf::Sprite healthSprite[3];

	sf::Texture dashbarTexture;
	sf::Sprite dashbarSprite;
	sf::Texture dashbarTexture2;
	sf::Sprite dashbarSprite2;

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;

	// sounds
	sf::SoundBuffer b_cannon;
	sf::Sound	s_cannon;
	sf::SoundBuffer b_cannonHit;
	sf::Sound	s_cannonHit;
	sf::SoundBuffer b_loot;
	sf::Sound	s_loot;
	sf::SoundBuffer b_meat;
	sf::Sound	s_meat;
	sf::SoundBuffer b_grab;
	sf::Sound	s_grab;
	sf::SoundBuffer b_opeopenomi;
	sf::Sound	s_opeopenomi;
	sf::SoundBuffer b_hitohitonomi;
	sf::Sound	s_hitohitonomi;
	sf::SoundBuffer b_merameranomi;
	sf::Sound	s_merameranomi;

	// ------------- Initialization ----------- 
	void initWindow();
	void initGameObjects();
	void initSounds();


public:
	// ------ Constructor and Destructor ------
	AGame();
	~AGame();

	// ------------- Accessors ----------------
	sf::Vector2i getMousePosition() const;
	// ------------- Modifiers ----------------

	// ------------- Functions ----------------
	// main functions
	bool const running() const;
	void pollEvents();

	// update and render functions
	void update(float deltaTime);
	void render();

	// game state 
	//void titleScreen();

	// game functions

	void checkPlayerCollisions();
	void checkItemOffscreen(AItem* item, int i);
	void spawnItem();
	void spawnCannonball();
	void spawnFlames();
	void mouseUpdate();

	// visuals stuff
	void displayHealth();
	void displayScore();
	void displayDashbar();
	void displayCursor();

	// sound
	void cannonSound();
	void cannonHitSound();
	void lootSound();
	void meatSound();
	void grabSound();
	void opeopenomiSound();
	void hitohitonomiSound();
	void merameranomiSound();
};