#include "items.h"
#include <iostream>


// -------- Constructor and Destructor ----
AItem::AItem(sf::Vector2f i_position, int i_type)
	: position(i_position)
	, type(i_type)
{
	/*
		Initialize Item
		- change texture, value depending on type (also speed for cannonball)
		- setup sprite (texture, scale, anchor, position)
		- setup collision
	*/

	// setup type of item
	switch (this->type)
	{
	case 1:
		// meat
		if (!this->itemTexture.loadFromFile("assets/meat.png")) { std::cout << "Error loading Meat Item Image" << std::endl; }
		this->value = 50;

		break;

	case 2:
		// cannon ball
		if (!this->itemTexture.loadFromFile("assets/cannonball.png")) { std::cout << "Error loading Cannonball Item Image" << std::endl; }
		this->value = 0;
		this->speed *= 3.0f;

		break;

	case 3: 
		// loot 
		int random = std::rand() % 4 + 1; // random between 1 - 5
		switch (random)
		{
		case 1:
			if (!itemTexture.loadFromFile("assets/loot_1.png")) { std::cout << "Error loading Loot Item Image" << std::endl; }
			this->value = 100;
			break;
		case 2:
			if (!itemTexture.loadFromFile("assets/loot_2.png")) { std::cout << "Error loading Loot Item Image" << std::endl; }
			this->value = 125;
			break;
		case 3:
			if (!itemTexture.loadFromFile("assets/loot_3.png")) { std::cout << "Error loading Loot Item Image" << std::endl; }
			this->value = 50;
			break;
		case 4:
			if (!itemTexture.loadFromFile("assets/loot_4.png")) { std::cout << "Error loading Loot Item Image" << std::endl; }
			this->value = 75;
			break;
		case 5:
			if (!itemTexture.loadFromFile("assets/loot_5.png")) { std::cout << "Error loading Loot Item Image" << std::endl; }
			this->value = 150;
			break;
		}
		
		break;
	}
	
	// setup sprite
	this->itemSprite.setTexture(this->itemTexture);
	this->itemSprite.setScale(this->itemScale, this->itemScale);
	this->itemSprite.setOrigin(sf::Vector2f(16.0f, 16.0f));
	this->itemSprite.setPosition(this->position);

	// setup collision
	this->itemCollision.setPosition(position);
	this->itemCollision.setRadius(16.0f * this->itemScale);
	this->itemCollision.setOrigin(16.0f * this->itemScale, 16.0f * this->itemScale);

	//std::cout << "Item spawned" << std::endl;
}

AItem::~AItem()
{
	// Destructor
	//std::cout << "Item Destructed" << std::endl;
}

// ------------- Accessors ----------------
sf::Vector2f AItem::getPosition() const
{
	return position;
}

int AItem::getType() const
{
	return type;
}

// ------------- Functions ----------------
	// Render and Update Function
void AItem::draw(sf::RenderWindow& i_window) const
{
	/*
		Render Item
	*/
	i_window.draw(this->itemSprite);
	//i_window.draw(this->itemCollision);
}

void AItem::update(float deltaTime)
{
	/*
		Update Item
		- update collision
		- move item
		- animation
	*/

	// update collision position
	this->itemCollision.setPosition(position);

	// move item
	this->velocity.y = this->speed * deltaTime;

	// Update Position
	this->position += this->velocity;

	// Set Position
	this->itemSprite.setPosition(this->position);

	// Rotating Animation (with random speed between 100 and 150)
	this->itemSprite.rotate((100 + (std::rand() % 50))* deltaTime);

}


int AItem::onCollision(APlayer &Player)
{
	/*
		What happens on collision
		returns item value
	*/
	switch (this->type)
	{
	case 1: // meat
		// Heal Player
		Player.heal(1);

		break;

	case 2:// cannonball
		// Damage Player
		Player.damage(1);

		break;

	case 3: // loot
		// just gets collected
		break;
	}
	

	return this->value;
}