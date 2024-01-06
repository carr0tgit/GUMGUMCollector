#pragma once
#include "SFML/Graphics.hpp"

class APlayer
{
	// -------- movement and position ---------
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f playerInput;

	sf::Vector2i mousePosition;

	// --------------- dash ------------------
	const int dashSpeed = 50;
	float dashTimer = 5.0f;
	bool canDash = true;

	// --------------- grab ------------------
	bool isGrabbing = false;
	sf::RectangleShape arm;
	sf::Vector2f grabPoint;
	float grabTimer = 2.0f;

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
	sf::Vector2f getPosition() const;
	// ------------- Modifiers ----------------

	// ------------- Functions ----------------
	// Render and Update Function
	void draw(sf::RenderWindow& i_window) const;
	void update(float deltaTime, sf::Vector2i i_mousePosition);

	// Damage and Healing
	void damage(int damageAmount);
	void heal(int healAmount);

	// Movement
	void calculateMovement(float deltaTime);

	// Mouse

	// Abilities
	void grabAbility(float deltaTime);
	void dashAbility(float deltaTime);

	void die();
};

// TODO :
/* 
	- Implement Particle Animation like Dust Emitter class(position, direction, color)
	- Implement Devilfruits
	- Start Menu
	- Restart Screen
	- grab ability
	- add music
	- better cannonball scaling / distrubition over game

*/