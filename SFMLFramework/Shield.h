#ifndef SHIELD_H
#define SHIELD_H

#include "GameObject.h"
#include "Settings.h"

class Shield : public GameObject
{

private:

	//Booleans

	//Determines whether or not this shield is active and should be updated and rendered
	bool m_isActive;

	//Determines whether the shield is moving left or right
	bool m_movingLeft;

	//Floats

	//The speed at which the shielf moves across the screen
	const float m_moveSpeed = Settings::Shield::g_shieldMoveSpeed;

	//Integers

	//The maximum amount of health the shield can have, the amount it starts with
	const int m_maxHealth = Settings::Shield::g_maxHealth;

	//The current amount of health that this shield has
	int m_currentHealth;

	//The leftmost position that the shield will move to
	int m_leftBoundary;

	//The rightmost position that the shield will move to
	int m_rightBoundary;

	//Vectors

	//The current target of the shield's lerp function
	sf::Vector2f m_currentVelocity;


public:

	//Constructor
	Shield( );

	//Methods

	//Detects collisions between the shield and whatever was passed in
	bool detectCollisions( sf::FloatRect collisionRect );

	//Runs every frame
	void update( float deltaTime );

	//Setters and Getters

	//Is Active

	bool getIsActive( );

	//Destructor
	~Shield( );

};

#endif