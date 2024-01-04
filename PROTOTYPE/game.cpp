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
	// player
	player = new APlayer(sf::Vector2f(230, 450));

	// background
	if (!this->backgroundTexture.loadFromFile("assets/background.png")) { std::cout << "Error loading Background Image" << std::endl; }
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setPosition(sf::Vector2f(0, 0));

	// health
	if (!this->healthTexture.loadFromFile("assets/heart.png")) { std::cout << "Error loading Heart Image" << std::endl; }
	this->healthSprite[0].setTexture(this->healthTexture);
	this->healthSprite[0].setPosition(sf::Vector2f(517, 86));
	this->healthSprite[1].setTexture(this->healthTexture);
	this->healthSprite[1].setPosition(sf::Vector2f(556, 86));
	this->healthSprite[2].setTexture(this->healthTexture);
	this->healthSprite[2].setPosition(sf::Vector2f(595, 86));

	// font / score
	if (!this->font.loadFromFile("assets/font/font.ttf")) { std::cout << "Error loading Font" << std::endl; }
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(25);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(sf::Vector2f(517, 23));

	// dashbar
	if (!this->dashbarTexture.loadFromFile("assets/dashbar.png")) { std::cout << "Error loading Dashbar Image" << std::endl; }
	this->dashbarSprite.setTexture(this->dashbarTexture);
	this->dashbarSprite.setPosition(sf::Vector2f(521, 147));

	if (!this->dashbarTexture2.loadFromFile("assets/dashbar2.png")) { std::cout << "Error loading Dashbar2 Image" << std::endl; }
	this->dashbarSprite2.setTexture(this->dashbarTexture2);
	this->dashbarSprite2.setPosition(sf::Vector2f(521, 147));

	// items
	this->previousItemX = 0.0f;
	this->itemTimer = 0.0f;
	this->cannonTimer = 0.0f;
	this->cannonReload = 3.0f;

}

void AGame::initSounds()
{
	/*
		Initialize Sounds
	*/
	//cannon shot
	if (!this->b_cannon.loadFromFile("assets/sounds/cannon_fire.wav")) { std::cout << "Error Loading Cannon Sound" << std::endl; }
	this->s_cannon.setBuffer(this->b_cannon);
	this->s_cannon.setVolume(soundVolume);
	//cannon hit
	if (!this->b_cannonHit.loadFromFile("assets/sounds/cannon_hit.wav")) { std::cout << "Error Loading Cannon Sound" << std::endl; }
	this->s_cannonHit.setBuffer(this->b_cannonHit);
	this->s_cannonHit.setVolume(soundVolume);
	//loot collected
	if (!this->b_loot.loadFromFile("assets/sounds/loot_collected.wav")) { std::cout << "Error Loading Loot Collected Sound" << std::endl; }
	this->s_loot.setBuffer(this->b_loot);
	this->s_loot.setVolume(soundVolume);
	//meat collected
	if (!this->b_meat.loadFromFile("assets/sounds/meat_collected.wav")) { std::cout << "Error Loading Loot Collected Sound" << std::endl; }
	this->s_meat.setBuffer(this->b_meat);
	this->s_meat.setVolume(soundVolume);
}

// ------ Constructor and Destructor ------
AGame::AGame()
{
	// Initialization
	this->initWindow();
	this->initGameObjects();
	this->initSounds();
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
	int i = 0;
	for (auto *j : this->items)
	{
		j->update(deltaTime);
		checkItemOffscreen(j, i);
		i++;
	}
	// spawn items 
	if (this->itemTimer > 0.7f)
	{
		this->itemTimer = (std::rand() % 5) * -0.1f; // randomise a bit more
		this->spawnItem();
	}
	this->itemTimer += deltaTime;
	// spawn cannonballs
	if (this->cannonTimer > this->cannonReload)
	{
		this->cannonTimer = (std::rand() % 10) * -0.05f; // randomise a bit more
		this->spawnCannonball();
		if (cannonReload > 0.35f)
		{
			this->cannonReload -= (std::rand() % 10) * 0.02f;
		}
		if (cannonReload > 1.5f) 
		{
			this->spawnCannonball();
			this->spawnCannonball();
		}
		else if (cannonReload > 0.5)
		{
			this->spawnCannonball();
		}
	}
	this->cannonTimer += deltaTime;
	
	

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
	//health
	this->displayHealth();
	//score
	this->displayScore();
	//dashbar
	this->displayDashbar();

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
		if ((dx + dy) <= (this->player->playerCollision.getRadius() + j->itemCollision.getRadius()))
		{
			score += j->onCollision(*player); // collect or activate item
			// sound
			if (j->getType() == 3) { this->lootSound(); } //loot
			else if (j->getType() == 2) { this->cannonHitSound(); } // cannonball
			else if (j->getType() == 1) { this->meatSound(); }

			this->items.erase(items.begin() + i); // erase item out of vector
			j->~AItem(); // call deconstructor
		}
		i++;
	}
}

void AGame::checkItemOffscreen(AItem* item, int i)
{
	/*
		Check if item is below bottom of screen and delete if it is
		- i is position in items vector
	*/
	if (i > this->items.size() - 1) { return; } // if iterator is outside range return (can happen due to player colliding with items)

	if (item->getPosition().y > 656)
	{
		this->items.erase(this->items.begin() + i); // erase item out of vector
		item->~AItem(); // call deconstructor
	}
	
}

void AGame::spawnItem()
{
	/*
		Handles spawning Items
		- selects random item between loot (80%), meat (10%) and devilfruits (10%)
		- selects random spawning position
		- check if spawn position is to close to last one
	*/
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
	p.y = -100.0f; // off screen spawning

	// dont allow items to spawn on top of each other
	float distance = sqrt((p.x - this->previousItemX) * (p.x - this->previousItemX));
	while (distance < 32)
	{
		p.x = (std::rand() % 460) + 20;
		distance = sqrt((p.x - this->previousItemX) * (p.x - this->previousItemX));
	}

	this->items.push_back(new AItem(p, type));
	this->previousItemX = p.x; // set previous item spawn x coordinate
}

void AGame::spawnCannonball()
{
	/*
		Spawn Cannonball
		- random position
		- cant spawn on previous item starting position
	*/

	sf::Vector2f p;
	p.x = (std::rand() % 460) + 20; // random value between 20 and 480
	p.y = -100.0f; // off screen spawning

	float distance = sqrt((p.x - this->previousCannonX) * (p.x - this->previousCannonX));
	while (distance < 32)
	{
		p.x = (std::rand() % 460) + 20;
		distance = sqrt((p.x - this->previousCannonX) * (p.x - this->previousCannonX));
	}

	this->items.push_back(new AItem(p, 2));
	this->cannonSound();
	this->previousCannonX = p.x;
}

void AGame::displayHealth()
{
	for (int i = 0; i < this->player->getHealth(); i++)
	{
		this->window->draw(healthSprite[i]);
	}
}

void AGame::displayScore()
{
	this->scoreText.setString(sf::String(std::to_string(score)));
	//this->scoreText.setString(sf::String("Test"));
	this->window->draw(scoreText);
}

void AGame::displayDashbar()
{
	sf::Vector2i p(this->dashbarSprite.getPosition());

	//std::cout << this->player->getDashCooldown() << std::endl;
	if (this->player->getDashCooldown() == 1.0f)
	{
		this->window->draw(this->dashbarSprite2);
		return;
	}

	int dashbarx = 100 * this->player->getDashCooldown();
	this->dashbarSprite.setTextureRect(sf::IntRect(p,sf::Vector2i(dashbarx, 32)));
	this->window->draw(this->dashbarSprite);
}


// sound
void AGame::cannonSound()
{
	this->s_cannon.play();
}

void AGame::cannonHitSound()
{
	this->s_cannonHit.play();
}

void AGame::lootSound()
{
	this->s_loot.play();
}

void AGame::meatSound()
{
	this->s_meat.play();
}
