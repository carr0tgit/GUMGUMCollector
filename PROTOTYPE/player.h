#pragma once
#include "SFML/Graphics.hpp"

class APlayer
{
	// -------- movement and position ---------
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f playerInput;

	// // ------------- dash ------------------
	const int dashSpeed = 50;
	float dashTimer = 5.0f;
	bool canDash = true;

	// -------- player variables --------------
	int health = 3;
	const int speed = 75;

	// ------------- visuals ------------------
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	const float playerScale = 1.33f;



public: 
	// -------- Collision Variable ------------
	sf::CircleShape playerCollision;
	

	// -------- Constructor and Destructor ----
	APlayer(sf::Vector2f i_position);
	~APlayer();
	// ------------- Accessors ----------------
	int getHealth() const;
	float getDashCooldown() const;
	// ------------- Modifiers ----------------

	// ------------- Functions ----------------
	// Render and Update Function
	void draw(sf::RenderWindow& i_window) const;
	void update(float deltaTime);

	// Damage and Healing
	void damage(int damageAmount);
	void heal(int healAmount);

	// Movement
	void calculateMovement(float deltaTime);

	// Abilities
	void grabAbility();
	void dashAbility(float deltaTime);

	void die();
};

// TODO :
/* 
	- Implement Animition while walking like little footsteps
	- Implement Devilfruits
	- Start Menu
	- Restart Screen
	- grab ability
	- Display Dash Timer

*/