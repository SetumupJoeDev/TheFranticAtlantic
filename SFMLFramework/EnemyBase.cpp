
#include "EnemyBase.h"

#include <iostream>

//Constructor

EnemyBase::EnemyBase( )
	:	m_maxHealth		( Settings::EnemyBase::Health::g_baseHealth ),
		m_currentHealth ( m_maxHealth ),
		m_isAlive		( false ),
		m_xOffset		( 0 ),
		m_yOffset	( 0 )
{
	//Sets the texture of the enemy
	if ( !getObjectTexture( ).loadFromFile( Settings::EnemyBase::Textures::g_enemyTexture ) )
	{
		std::cout << "Enemy failed to load texture!";
	}
	updateTexture( );

}

//Setters and Getters

//X Offset

void EnemyBase::setXOffset( int newXOffset )
{
	m_xOffset = newXOffset;
}

int EnemyBase::getXOffset( )
{
	return m_xOffset;
}

//Y Offset

void EnemyBase::setYOffset( int newYOffset )
{
	m_yOffset = newYOffset;
}

int EnemyBase::getYOffset( )
{
	return m_yOffset;
}

//Is Alive

void EnemyBase::setIsAlive( bool isAlive )
{
	m_isAlive = isAlive;
}

bool EnemyBase::getIsAlive( )
{
	return m_isAlive;
}

EnemyBase::~EnemyBase( )
{
}
