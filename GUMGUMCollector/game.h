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
	bool gameover = false;
	bool ingame = false;
	int score = 0;
	APlayer* player;

	std::vector<AItem*> items;
	float previousItemX; // x location of previous spawned item
	float previousCannonX; // x location of previous spawned cannonball
	float itemTimer;
	float cannonTimer;
	float cannonReload; // how long till next shot
	int cannonTotal; // counts cannon shots

	// mouse position
	sf::Vector2i mousePosition;
	// font
	sf::Font font;
	// main menu
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	// background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	// score
	sf::Text scoreText;
	// health
	sf::Texture healthTexture;
	sf::Sprite healthSprite[3];
	// dashbar
	sf::Texture dashbarTexture;
	sf::Sprite dashbarSprite;
	sf::Texture dashbarTexture2;
	sf::Sprite dashbarSprite2;
	// cursor
	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
	// gameover
	sf::Text gameoverText;
	sf::RectangleShape gameoverRectangle;

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
	sf::SoundBuffer b_dash;
	sf::Sound	s_dash;

	// ------------- Initialization ----------- 
	void initWindow();
	void initGameObjects();
	void initSounds();
	void initVisuals();


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
	void run();
	void update(float deltaTime);
	void render();

	// main menu
	void mainMenu();

	// game functions
	void startGame();
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
	void displayGameOver();

	// sound
	void cannonSound();
	void cannonHitSound();
	void lootSound();
	void meatSound();
	void grabSound();
	void opeopenomiSound();
	void hitohitonomiSound();
	void merameranomiSound();
	void dashSound();
};