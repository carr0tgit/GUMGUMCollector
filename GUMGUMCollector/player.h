#pragma once
#include "SFML/Graphics.hpp"

class APlayer
{
	// -------- movement and position ---------
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f playerInput;

	bool canMove = true;
	float rootTimer = 1.0f;

	sf::Vector2i mousePosition;

	// --------------- dash ------------------
	const int dashSpeed = 50;
	float dashTimer = 5.0f;
	bool canDash = true;

	// --------------- grab ------------------
	bool startGrabbing = false;
	bool isGrabbing = false;
	bool grabSound = false;

	sf::RectangleShape arm;
	sf::Vector2f grabPoint;
	float grabTimer = 1.0f;
	float grabDistance = 0.0f; // 0 ... 1 

	// -------- player variables --------------
	int health = 3;
	const int speed = 75;

	// ------------- visuals ------------------
	sf::Sprite playerSprite;
	sf::Texture playerTexture;
	const float playerScale = 1.33f;

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
	bool getGrabSound() const;
	// ------------- Modifiers ----------------
	void setGrabSound(bool i_b);
	void setPosition(sf::Vector2f i_position);
	void setCanMove(bool i_b);
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

	void die();
};

// TODO :
/* 
	- Start Menu
	- Restart Screen
	- add music
	- better cannonball scaling / distrubition over game

*/