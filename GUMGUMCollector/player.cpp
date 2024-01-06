#include <iostream>
#include "player.h"


// -------- Constructor and Destructor ----
APlayer::APlayer(sf::Vector2f i_position)
	: position(i_position)
{
	/*
		Initialize Texture, Sprite and Collision
	*/ 
	if (!this->playerTexture.loadFromFile("assets/strawhat.png")) { std::cout << "Error loading Player Image" << std::endl; }

	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setScale(this->playerScale, this->playerScale);
	this->playerSprite.setPosition(this->position);

	// collision (setup with a center origin)
	this->playerCollision.setPosition(sf::Vector2f(this->position.x + 16.0f * this->playerScale, this->position.y + 16.0f * this->playerScale));
	this->playerCollision.setRadius(16.0f * this->playerScale);
	this->playerCollision.setOrigin(16.0f * this->playerScale, 16.0f * this->playerScale);
}

APlayer::~APlayer()
{
	// Destructor
	std::cout << "Player Destructed" << std::endl;
}
// ------------- Accessors ----------------
int APlayer::getHealth() const
{
	return this->health;
}

float APlayer::getDashCooldown() const
{
	/*
		Returns Percentage of Cooldown left
		0 ... 1
		0 being dash just used
		1 being dash is up
	*/
	//std::cout << dashTimer << std::endl;
	if (dashTimer == 5.0f) { return 1.0f; }
	return 1 - (dashTimer / 5.0f);
}

sf::Vector2f APlayer::getPosition() const
{
	return this->position;
}

// ------------- Functions ----------------
// Render and Update Function
void APlayer::draw(sf::RenderWindow& i_window) const
{
	/*
		Render Player
	*/
	if (this->isGrabbing)
	{
		i_window.draw(this->arm);
	}
	i_window.draw(this->playerSprite);
}

void APlayer::update(float deltaTime, sf::Vector2i i_mousePosition)
{
	/*
		Update Player
		- update collision
		- movement
		- abilities
		- limit player movement 
	*/
	// Collision
	this->playerCollision.setPosition(sf::Vector2f(position.x + 16.0f * playerScale, position.y + 16.0f * playerScale)); // update collision to current position

	// Movement
	this->calculateMovement(deltaTime);

	// Mouse
	this->mousePosition = i_mousePosition;
	
	// Abilities
	// Dash
	this->dashAbility(deltaTime);
	// Grab
	this->grabAbility(deltaTime);


	// Update Position
	this->position += this->velocity;

	// Limiting Player Movement to Stay Inside Playing Area
	this->position.x = std::clamp(this->position.x, 0.0f, 500.0f - this->playerSprite.getGlobalBounds().width);
	this->position.y = std::clamp(this->position.y, 300.0f, 640.0f - this->playerSprite.getGlobalBounds().height);

	// Set Sprite Position
	this->playerSprite.setPosition(this->position);


}

// Damage and Healing
void APlayer::damage(int damageAmount)
{
	/*
		Damage Player and Check if Player is Dead
	*/
	this->health -= damageAmount;
	if (this->health <= 0) { this->health = 0; APlayer::die(); }
}

void APlayer::heal(int healAmount)
{
	/*
		Heal Player
	*/
	if (this->health >= 3) { return; }
	this->health += healAmount;
}

// Movement
void APlayer::calculateMovement(float deltaTime)
{
	/*
		Movement
		- set input
		- fix diagonal movement
		- calculate velocity

	*/
	//  Movement Input
	playerInput = sf::Vector2f(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { playerInput.x = -1.0f; } // Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { playerInput.x = 1.0f; } // Right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { playerInput.y = -1.0f; } // Forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { playerInput.y = 1.0f; } // Back


	// Fix diagonal movement being faster
	if ((playerInput.x != 0) && (playerInput.y != 0)) // check if moving diagonal
	{
		playerInput.x *= 0.707f; // 0.707 is sin(45°)
		playerInput.y *= 0.707f;
	}

	// Calculate Movement Velocity
	velocity.x = playerInput.x * speed * deltaTime;
	velocity.y = playerInput.y * speed * deltaTime;
}

// Abilities
void APlayer::grabAbility(float deltaTime)
{


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isGrabbing)
	{
		this->grabPoint.x = this->mousePosition.x;
		this->grabPoint.y = this->mousePosition.y;
		this->isGrabbing = true;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->isGrabbing = false;
	}

	if (this->isGrabbing)
	{
		float dx = this->playerCollision.getPosition().x - this->grabPoint.x;
		float dy = this->playerCollision.getPosition().y - this->grabPoint.y;
		float distance = sqrt((dx * dx) + (dy * dy));

		if (playerCollision.getPosition().x > this->grabPoint.x)
		{
			distance *= -1.0f;
		}

		float angle = asin(dy / distance);
		angle *= 180 / 3.1415; // convert to degree 
		
		std::cout << "dy: " << dy << std::endl;
		std::cout << "Distance: " << distance << std::endl;
		std::cout << "Angle: " << angle << std::endl;
		

		this->arm.setSize(sf::Vector2f(distance, 10.0f));
		this->arm.setOrigin(sf::Vector2(0.0f, 5.0f));
		this->arm.setPosition(this->playerCollision.getPosition());
		this->arm.setRotation(-angle);
	}
}

void APlayer::dashAbility(float deltaTime)
{
	/*
		Dash  
		- dash timer
		- dash ability
	*/
	// Timer Logic
	if (!this->canDash)
	{
		this->dashTimer -= deltaTime;
		if (this->dashTimer <= 0)
		{
			this->canDash = true;
			this->dashTimer = 5.0f; // reset timer
		}
	}
	// dash if space pressed and allowed to 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->canDash)
	{ 
		this->velocity.x = this->playerInput.x * this->dashSpeed;
		this->velocity.y = this->playerInput.y * this->dashSpeed;
		this->canDash = false;
	}

}

void APlayer::die()
{
	std::cout << "Died" << std::endl;
	return;
}