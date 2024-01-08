#include "game.h"

// ------------- Initialization ----------- 

void AGame::initWindow()
{	
	/*
		Initialize Window and Menu
	*/
	// window
	this->videoMode = sf::VideoMode(640, 640);
	this->window = new sf::RenderWindow(this->videoMode, "GUM GUM Collector", sf::Style::Close | sf::Style::Titlebar);
	this->window->setMouseCursorVisible(false);

	// font
	if (!this->font.loadFromFile("assets/font/font.ttf")) { std::cout << "Error loading Font" << std::endl; }

	// menu
	if (!this->menuTexture.loadFromFile("assets/menu.png")) { std::cout << "Error loading Menu Image" << std::endl; }
	this->menuSprite.setTexture(this->menuTexture);
	this->menuSprite.setPosition(sf::Vector2f(0, 0));
	// menu volume text
	this->volumeText.setPosition(sf::Vector2f(255, 338));
	this->volumeText.setString(std::to_string(this->soundVolume));
	this->volumeText.setCharacterSize(40);
	this->volumeText.setFont(this->font);

}

void AGame::initGameObjects()
{
	/*
		Initialize Game Objects
	*/
	// player
	player = new APlayer(sf::Vector2f(230, 450));

	//score
	this->score = 0;

	// items
	this->previousItemX = 0.0f;
	this->itemTimer = 0.0f;
	this->items.erase(items.begin(),items.end());

	// cannon
	this->previousCannonX = 0.0f;
	this->cannonTimer = 0.0f;
	this->cannonReload = 3.0f;
	this->cannonTotal = 0;

}

void AGame::initSounds()
{
	/*
		Initialize Sounds
	*/
	//cannon shot
	if (!this->b_cannon.loadFromFile("assets/sounds/cannon_fire.wav")) { std::cout << "Error Loading Cannon Sound" << std::endl; }
	this->s_cannon.setBuffer(this->b_cannon);
	this->s_cannon.setVolume(soundVolume * 0.65f);
	//cannon hit
	if (!this->b_cannonHit.loadFromFile("assets/sounds/cannon_hit.wav")) { std::cout << "Error Loading Cannon Sound" << std::endl; }
	this->s_cannonHit.setBuffer(this->b_cannonHit);
	this->s_cannonHit.setVolume(soundVolume);
	//loot collected
	if (!this->b_loot.loadFromFile("assets/sounds/loot_collected.wav")) { std::cout << "Error Loading Loot Collected Sound" << std::endl; }
	this->s_loot.setBuffer(this->b_loot);
	this->s_loot.setVolume(soundVolume);
	//meat collected
	if (!this->b_meat.loadFromFile("assets/sounds/meat_collected.wav")) { std::cout << "Error Loading Meat Collected Sound" << std::endl; }
	this->s_meat.setBuffer(this->b_meat);
	this->s_meat.setVolume(soundVolume);
	//grab
	if (!this->b_grab.loadFromFile("assets/sounds/grab.wav")) { std::cout << "Error Loading Grab  Sound" << std::endl; }
	this->s_grab.setBuffer(this->b_grab);
	this->s_grab.setVolume(soundVolume * 0.8f);
	//ope ope no mi
	if (!this->b_opeopenomi.loadFromFile("assets/sounds/df_law.wav")) { std::cout << "Error Loading Ope Ope No Mi Sound" << std::endl; }
	this->s_opeopenomi.setBuffer(this->b_opeopenomi);
	this->s_opeopenomi.setVolume(soundVolume * 0.8f);
	//hito hito no mi
	if (!this->b_hitohitonomi.loadFromFile("assets/sounds/df_dofi.wav")) { std::cout << "Error Loading Hito Hito No Mi Sound" << std::endl; }
	this->s_hitohitonomi.setBuffer(this->b_hitohitonomi);
	this->s_hitohitonomi.setVolume(soundVolume * 0.8f);
	//mera mera no mi
	if (!this->b_merameranomi.loadFromFile("assets/sounds/df_ace.wav")) { std::cout << "Error Loading Mera Mera No Mi Sound" << std::endl; }
	this->s_merameranomi.setBuffer(this->b_merameranomi);
	this->s_merameranomi.setVolume(soundVolume * 0.8f);
	// dash
	if (!this->b_dash.loadFromFile("assets/sounds/dash.wav")) { std::cout << "Error Loading Dash Sound" << std::endl; }
	this->s_dash.setBuffer(this->b_dash);
	this->s_dash.setVolume(soundVolume * 0.8f);
}

void AGame::initVisuals()
{
	/*
		Initialize Visuals
		- background
		- "interface"
	*/

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
	
	// score
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

	// cursor
	if (!this->cursorTexture.loadFromFile("assets/cursor.png")) { std::cout << "Error loading Cursor Image" << std::endl; }
	this->cursorSprite.setTexture(this->cursorTexture);
	this->cursorSprite.setOrigin(sf::Vector2f(16.0f, 16.0f));

	// gameover
	this->gameoverText.setFont(this->font);
	this->gameoverText.setCharacterSize(50);
	this->gameoverText.setFillColor(sf::Color::White);
	this->gameoverText.setPosition(sf::Vector2f(75, 150));
	this->gameoverText.setString("Game Over!\nScore:\nPress Spacebar\nto Continue");

	this->gameoverRectangle.setPosition(sf::Vector2f(0, 0));
	this->gameoverRectangle.setFillColor(sf::Color(100, 100, 100, 100));
	this->gameoverRectangle.setSize(sf::Vector2f(640, 640));

}

// ------ Constructor and Destructor ------
AGame::AGame()
{
	// Initialization
	this->initWindow();
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
	/*
		Poll SFML Events
	*/
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

void AGame::run()
{
	/*
		Game Main Function
		- handles gameloop and menu/ingame scene
	*/
	// Initialize deltaTime
	sf::Clock clock;
	float deltaTime = 0.0f;


	while (this->running())
	{
		deltaTime = clock.restart().asSeconds();
		this->pollEvents();
		if(!this->ingame) 
		{
			this->mainMenu(deltaTime);
		}
		else
		{
			this->update(deltaTime);
			this->render();
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

	// mouse
	this->mouseUpdate();

	// check gameover
	if (this->gameover) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // return to menu
		{
			this->ingame = false;
		}
		return; 
	}

	// ------------ game ----------------
	// player
	this->player->update(deltaTime, this->mousePosition);
	if (this->player->getGrabSound()) { this->grabSound(); this->player->setGrabSound(false); }
	if (this->player->getDashSound()) { this->dashSound(); this->player->setDashSound(false); }
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
		this->spawnCannonball();
		if (cannonReload > 0.4f)
		{
			this->cannonReload -= (std::rand() % 10) * 0.02f;
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
	//dashbar
	this->displayDashbar();
	//cursor
	this->displayCursor();

	if (this->gameover)
	{
		this->displayGameOver();
	}

	//score
	this->displayScore();

	this->window->display();
}
// game states

void AGame::mainMenu(float deltaTime)
{
	/*
		Main Menu
		- Enter to start game
		- Up/Down to change volume
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		this->startGame();
	}

	if (this->soundTimer > 0.15f) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->soundVolume += 5;
			if (this->soundVolume > 100)
			{
				this->soundVolume = 100;
			}
			this->volumeText.setString(std::to_string(this->soundVolume));
			this->soundTimer = 0.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->soundVolume -= 5;
			if (this->soundVolume < 0)
			{
				this->soundVolume = 0;
			}
			this->volumeText.setString(std::to_string(this->soundVolume));
			this->soundTimer = 0.0f;
		}
	}
	else
	{
		this->soundTimer += deltaTime;
	}


	// Clear / Draw / Display 
	this->window->clear(sf::Color::Black);

	this->window->draw(this->menuSprite);
	this->window->draw(this->volumeText);

	this->window->display();
}


// game functions
void AGame::startGame()
{
	/*
		Start Game
		- Reset all game variables
		- set ingame to true
		- set gameover to false
	*/

	//player
	if (this->player != nullptr)
	{
		this->player->~APlayer();
	}
	
	this->initGameObjects();
	this->initVisuals();
	this->initSounds();

	this->ingame = true;
	this->gameover = false;
}


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
			if (this->player->getHealth() == 0) // end game if player health is 0
			{
				this->gameover = true;
			}
			// sound
			if (j->getType() == 3) { this->lootSound(); } //loot
			else if (j->getType() == 2) { this->cannonHitSound(); } // cannonball
			else if (j->getType() == 1) { this->meatSound(); } // meat
			else if (j->getType() == 4) { this->opeopenomiSound(); } // ope ope no mi (law)
			else if (j->getType() == 5) { this->hitohitonomiSound(); } // hito hito no mi (doflamingo)
			else if (j->getType() == 6) { this->merameranomiSound(); this->spawnFlames(); } // mera mera no mi (ace :))

			this->items.erase(items.begin() + i); // erase item out of vector
			j->~AItem(); // call deconstructor
		}

		//hand collision check
		dx = this->player->handCollision.getPosition().x - j->itemCollision.getPosition().x;
		dx = sqrt(dx * dx);
		dy = this->player->handCollision.getPosition().y - j->itemCollision.getPosition().y;
		dy = sqrt(dy * dy);

		if ((dx + dy) <= (this->player->handCollision.getRadius() + j->itemCollision.getRadius()) && this->player->getIsGrabbing())
		{
			score += j->onCollision(*player); // collect or activate item
			if (this->player->getHealth() == 0) // end game if player health is 0
			{
				this->gameover = true;
			}
			// sound
			if (j->getType() == 3) { this->lootSound(); } //loot
			else if (j->getType() == 2 || j->getType() == 7) { this->cannonHitSound(); } // cannonball or flames
			else if (j->getType() == 1) { this->meatSound(); } // meat
			else if (j->getType() == 4) { this->opeopenomiSound(); } // ope ope no mi (law)
			else if (j->getType() == 5) { this->hitohitonomiSound(); } // hito hito no mi (doflamingo)
			else if (j->getType() == 6) { this->merameranomiSound(); this->spawnFlames(); } // mera mera no mi (ace :))

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
	// probability = 88 % loot , 6 % meat , 6 % devilfruits
	int probability[15] = { 1, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; // 1 is meat 3 is loot 4 is devil fruit
	int devilfruits[3] = { 4, 5, 6 };
	int type; 
	
	// if it selects 4 than choose between random devilfruits
	// else choose between meat and loot
	int choice = std::rand() % 15;
	if (probability[choice] == 4) 
	{
		choice = std::rand() % 3;
		type = devilfruits[choice];
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
		- cant spawn on previous cannonball starting position
		- target player sometimes
	*/

	sf::Vector2f p;
	p.x = (std::rand() % 460) + 20; // random value between 20 and 480
	p.y = -100.0f; // off screen spawning

	// target player
	if(this->cannonTotal % 3 == 1) // start with second shot 
	{
		p.x = this->player->getPosition().x + this->player->playerCollision.getRadius(); // target center of player
	}
	
	//  cant spawn on previous cannonball starting position
	float distance = sqrt((p.x - this->previousCannonX) * (p.x - this->previousCannonX));
	while (distance < 32) // 32 is width
	{
		p.x = (std::rand() % 460) + 20;
		distance = sqrt((p.x - this->previousCannonX) * (p.x - this->previousCannonX));
	}

	this->items.push_back(new AItem(p, 2));
	this->cannonSound();
	this->previousCannonX = p.x;
	this->cannonTotal++;
}

void AGame::spawnFlames()
{
	/*
		Spawn Flames
		- target player
	*/
	sf::Vector2f p;
	p.x = this->player->getPosition().x + this->player->playerCollision.getRadius(); // center of player
	p.y = -100.0f; // off screen spawning
	this->items.push_back(new AItem(p, 7));
}

void AGame::mouseUpdate()
{
	/*
		Set Mouse Position Relative to Window
		Set Cursor Sprite Position
	*/
	this->mousePosition = sf::Mouse::getPosition(*this->window);
	sf::Vector2f p;
	p.x = this->mousePosition.x;
	p.y = this->mousePosition.y;
	this->cursorSprite.setPosition(p);
}

// visuals
void AGame::displayHealth()
{
	for (int i = 0; i < this->player->getHealth(); i++)
	{
		this->window->draw(healthSprite[i]);
	}
}

void AGame::displayScore()
{
	this->scoreText.setString(std::to_string(this->score));
	this->window->draw(scoreText);
}

void AGame::displayDashbar()
{
	/*
		Display Dash Cooldown as a Bar
	*/
	sf::Vector2i p(this->dashbarSprite.getPosition());

	// if dash is up 
	if (this->player->getDashCooldown() == 1.0f)
	{
		this->window->draw(this->dashbarSprite2);
		return;
	}

	int dashbarx = 100 * this->player->getDashCooldown(); // width
	this->dashbarSprite.setTextureRect(sf::IntRect(p,sf::Vector2i(dashbarx, 32)));
	this->window->draw(this->dashbarSprite);
}

void AGame::displayCursor()
{
	this->window->draw(this->cursorSprite);
}



void AGame::displayGameOver()
{
	this->window->draw(this->gameoverRectangle);
	this->window->draw(this->gameoverText);

	sf::Vector2f p;
	p.x = this->gameoverText.getPosition().x + 175;
	p.y = this->gameoverText.getPosition().y + 50;

	this->scoreText.setPosition(p);
	this->scoreText.setCharacterSize(50);
	
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

void AGame::grabSound()
{
	this->s_grab.play();
}

void AGame::opeopenomiSound()
{
	this->s_opeopenomi.play();
}

void AGame::hitohitonomiSound()
{
	this->s_hitohitonomi.play();
}

void AGame::merameranomiSound()
{
	this->s_merameranomi.play();
}

void AGame::dashSound()
{
	this->s_dash.play();
}