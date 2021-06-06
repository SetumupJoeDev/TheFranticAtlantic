#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "GameObject.h"
#include "GameSound.h"
#include "ProjectileManager.h"
#include "Settings.h"

class EnemyBase : public GameObject
{

private:

	//Booleans
	bool m_isAlive;					//Determines whether or not this enemy is alive

	//Integers
	int m_currentHealth;			//The current amount of health this enemy has
		
	const int m_maxHealth = 1;		//The maximum amount of health this enemy will have
	
	int m_xOffset;					//The enemy's X offset from the origin of the enemy manager

	int m_yOffset;					//The enemy's Y offset from the origin of the enemy manager

public:

	//Constructor
	EnemyBase( );

	//Methods

	//Setters and Getters

	//X Offset

	void setXOffset( int newXOffset );

	int getXOffset( );

	//Y Offset

	void setYOffset( int newYOffset );

	int getYOffset( );

	//isAlive
	void setIsAlive( bool isAlive );

	bool getIsAlive( );

	//Destructor
	~EnemyBase( );
};

#endif