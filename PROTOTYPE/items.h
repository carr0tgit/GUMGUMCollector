#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"

class AItem
{
private:
	// 1 meat 2 cannon ball 3 loot 4... df
	int type; 
	int value;

	// position and movement
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed = 75.0f + std::rand() % 40;

	// visuals
	sf::Sprite itemSprite;
	sf::Texture itemTexture;
	float itemScale = 1.0f;

public:
	// -------- Collision Variable ------------
	sf::CircleShape itemCollision;

	// -------- Constructor and Destructor ----
	AItem(sf::Vector2f i_position, int i_type);
	~AItem();

	// ------------- Accessors ----------------

	// ------------- Modifiers ----------------

	// ------------- Functions ----------------
	// Render and Update Function
	void draw(sf::RenderWindow& i_window) const;
	void update(float deltaTime);
	
	
	// Collision
	int onCollision(APlayer& Player);
	
};


