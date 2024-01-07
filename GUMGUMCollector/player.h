#pragma once
#include "SFML/Graphics.hpp"

class APlayer
{
	// -------- movement and position ---------
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f playerInput;
	// locking movement
	bool canMove = true;
	float rootTimer = 1.0f; 
	// mouse
	sf::Vector2i mousePosition;

	// --------------- dash ------------------
	const int dashSpeed = 50;
	float dashTimer = 5.0f;
	bool canDash = true;
	bool dashSound = false;

	// --------------- grab ------------------
	bool startGrabbing = false;
	bool isGrabbing = false;
	bool grabSound = false;

	sf::Vector2f grabPoint; // target location
	float grabTimer = 1.0f;
	float grabDistance = 0.0f; // value between 0 and 1 with 1 being max distance

	// -------- player variables --------------
	int health = 3;
	const int speed = 75;

	// ------------- visuals ------------------
	// player (body/hat)
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	const float playerScale = 1.33f;

	//arm
	sf::RectangleShape arm;

	// hand
	sf::Sprite handSprite;
	sf::Texture handTexture;

	// strings
	sf::Sprite stringsSprite;
	sf::Texture stringsTexture;



public: 
	// -------- Collision Variable ------------
	sf::CircleShape playerCollision;
	sf::CircleShape handCollision;
	

	// -------- Constructor and Destructor ----
	APlayer(sf::Vector2f i_position);
	~APlayer();
	// ------------- Accessors ----------------
	int getHealth() const;
	float getDashCooldown() const;
	sf::Vector2f getPosition() const;
	bool getIsGrabbing() const;
	// sounds
	bool getGrabSound() const;
	bool getDashSound() const;
	// ------------- Modifiers ----------------
	void setPosition(sf::Vector2f i_position);
	void setCanMove(bool i_b);
	// sounds
	void setGrabSound(bool i_b);
	void setDashSound(bool i_b);
	// ------------- Functions ----------------
	// Render and Update Function
	void draw(sf::RenderWindow& i_window) const;
	void update(float deltaTime, sf::Vector2i i_mousePosition);

	// Damage and Healing
	void damage(int damageAmount);
	void heal(int healAmount);

	// Movement
	void calculateMovement(float deltaTime);

	// Abilities
	void grabAbility(float deltaTime);
	void dashAbility(float deltaTime);
};

// TODO :
/* 
	- Start Menu
	- add music

*/