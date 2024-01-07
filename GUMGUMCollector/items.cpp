#include "items.h"
#include <iostream>


// -------- Constructor and Destructor ----
AItem::AItem(sf::Vector2f i_position, int i_type)
	: position(i_position)
	, type(i_type)
{
	/*
		Initialize Item
		- change texture, value depending on type (also speed for cannonball and flames)
		- setup sprite (texture, scale, anchor, position)
		- setup collision
	*/

	int random; // randomize loot
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
		this->value = -25;
		this->speed *= 3.0f;

		break;

	case 3: 
		// loot 
		random = std::rand() % 4 + 1; // random between 1 - 5
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

	case 4:
		// ope ope no mi devilfruit (law)
		if (!this->itemTexture.loadFromFile("assets/df_law.png")) { std::cout << "Error loading Ope Ope No Mi Devilfruit Item Image" << std::endl; }
		this->value = 250;

		break;

	case 5:
		// ito ito no mi devilfruit (doflamingo)
		if (!this->itemTexture.loadFromFile("assets/df_dofi.png")) { std::cout << "Error loading Ito Ito No Mi Devilfruit Item Image" << std::endl; }
		this->value = 250;

		break;
	case 6:
		// mera mera no mi (ace :))
		if (!this->itemTexture.loadFromFile("assets/df_ace.png")) { std::cout << "Error loading Mera Mera No Mi Devilfruit Item Image" << std::endl; }
		this->value = 250;

		break;
	case 7:
		// flames
		if (!this->itemTexture.loadFromFile("assets/flames.png")) { std::cout << "Error loading Flames Item Image" << std::endl; }
		this->value = -25;
		this->speed *= 3.0f;

	}
	
	// setup sprite
	this->itemSprite.setTexture(this->itemTexture);
	this->itemSprite.setScale(this->itemScale, this->itemScale);
	this->itemSprite.setOrigin(sf::Vector2f(16.0f, 16.0f));
	this->itemSprite.setPosition(this->position);

	// setup collision
	this->itemCollision.setPosition(this->position);
	this->itemCollision.setRadius(16.0f * this->itemScale);
	this->itemCollision.setOrigin(16.0f * this->itemScale, 16.0f * this->itemScale);

}

AItem::~AItem()
{
	// Destructor
	//std::cout << "Item Destructed" << std::endl;
}

// ------------- Accessors ----------------
sf::Vector2f AItem::getPosition() const
{
	return this->position;
}

int AItem::getType() const
{
	return this->type;
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
	this->itemCollision.setPosition(this->position);

	// move item
	this->velocity.y = this->speed * deltaTime;

	// Update Position
	this->position += this->velocity;

	// Set Position
	this->itemSprite.setPosition(this->position);

	// Rotating Animation (with random speed between 100 and 150)
	if (this->type == 7) { return; } // flames dont rotate
	this->itemSprite.rotate((100 + (std::rand() % 50))* deltaTime);

}


int AItem::onCollision(APlayer &Player)
{
	/*
		Collision Event
		returns item value
	*/
	sf::Vector2f p;
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

	case 4: // ope ope no mi devilfruit (law)
		p.x = std::rand() % 500;
		p.y = std::rand() % 340 + 300;
		Player.setPosition(p);
		break;

	case 5: // ope ope no mi devilfruit (law)
		Player.setCanMove(false); // root player
		break;

	case 6: // mera mera no mi devilfruit (ace :))
		// event happens in game class
		break;

	case 7: // flames
		Player.damage(1);
		break;
	}
	

	return this->value;
}