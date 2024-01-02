#include "game.h"

// ------------- Initialization ----------- 

void AGame::initWindow()
{	
	/*
		Initialize Window
	*/

	this->videoMode = sf::VideoMode(640, 640);
	this->window = new sf::RenderWindow(this->videoMode, "GUM GUM Collector", sf::Style::Close | sf::Style::Titlebar);
}

void AGame::initGameObjects()
{
	/*
		Initialize Game Objects
	*/
	// Player
	player = new APlayer(sf::Vector2f(230, 450));

	// background
	if (!backgroundTexture.loadFromFile("assets/background.png")) { std::cout << "Error loading Background Image" << std::endl; }
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(sf::Vector2f(0, 0));

	for (int i = 0; i < 10; i++) { this->spawnItem(); }
	

}

// ------ Constructor and Destructor ------
AGame::AGame()
{
	// Initialization
	this->initWindow();
	this->initGameObjects();
}

AGame::~AGame()
{
	delete this->window;
	delete this->player;
}

// ------------- Accessors ----------------

// ------------- Modifiers ----------------

// ------------- Functions ----------------
// main functions
bool const AGame::running() const
{
	return this->window->isOpen();
}

void AGame::pollEvents()
{
	while (this->window->pollEvent(this->windowEvent))
	{
		// Close Button
		if (this->windowEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}

		// Escape to close
		if (this->windowEvent.type == sf::Event::KeyPressed)
		{
			if (this->windowEvent.key.code == sf::Keyboard::Escape) 
			{
				this->window->close();
			}
		}
	}
}

// update and render functions
void AGame::update(float deltaTime)
{
	/*
		Update
		- check for sfml events
		- update player, items
		- check for player <-> item collision
	*/

	//sfml 
	this->pollEvents();

	// ------------ game ----------------
	// player
	this->player->update(deltaTime);

	// items
	for (auto *j : this->items)
	{
		j->update(deltaTime);
	}

	// collision
	this->checkPlayerCollisions();
}

void AGame::render()
{
	/*
		Display what happened in update
	*/
	this->window->clear(sf::Color::Black);
	//background
	this->window->draw(backgroundSprite);
	//player
	this->player->draw(*window);
	// items
	for (auto *j : this->items)
	{
		j->draw(*window);
	}


	this->window->display();
}

// game functions
void AGame::checkPlayerCollisions()
{
	/*
		everything concered with player collision
		- collectiong
		- damaging
		- activating events
	*/
	int i = 0;
	for (auto *j : this->items)
	{
		// calculate distance between player center and item center 
		float dx = this->player->playerCollision.getPosition().x - j->itemCollision.getPosition().x;
		dx = sqrt(dx * dx);
		float dy = this->player->playerCollision.getPosition().y - j->itemCollision.getPosition().y;
		dy = sqrt(dy * dy);

		// check if distance is less than radius of player and item
		if ((dx + dy) < (this->player->playerCollision.getRadius() + j->itemCollision.getRadius()))
		{
			score += j->onCollision(*player); // collect or activate item
			this->items.erase(items.begin() + i); // delete item
		}
		i++;
	}
}

void AGame::spawnItem()
{
	//AItem item(sf::Vector2f(20.0f, 20.0f), 1);
	// probability = 80 % loot , 10 % meat , 10 % devilfruits
	int probability[10] = { 1, 4, 3, 3, 3, 3, 3, 3, 3, 3}; // 1 is meat 3 is loot 4 is devil fruit
	int devilfruits[3] = { 4, 5, 6 };
	int type; 
	
	// if it selects 4 than choose between random devilfruits
	// else choose between meat and loot
	int choice = std::rand() % 10;
	if (probability[choice] == 4) 
	{
		choice = std::rand() % 3;
		//type = devilfruits[choice];
		type = 3; // todo: implement devilfruits
	}
	else
	{
		type = probability[choice];
	}
	sf::Vector2f p;
	p.x = (std::rand() % 460) + 20; // random value between 20 and 480
	p.y = -50.0f;
	this->items.push_back(new AItem(p, type));
}
