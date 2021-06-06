
#include "ProjectileManager.h"

#include "EnemyManager.h"
#include "Helpers.h"

//Constructor

ProjectileManager::ProjectileManager( )
	: m_activeProjectiles ( 0 ),
	m_projectileSpeed ( 0 )
{
	
}

//Methods

void ProjectileManager::update( float deltaTime )
{
	//Loops through the array of projectiles and runs their update functions, passing in deltaTime
	for ( int i = 0; i < m_numProjectiles; ++i )
	{
		if ( m_projectileArray[i].getIsActive( ) )
		{
			m_projectileArray[i].update( deltaTime );
		}
	}
}

void ProjectileManager::fireProjectile( sf::Vector2f gunPosition )
{
	//Loops through the array of projectiles and activates the first dormant one it finds
	for ( int i = 0; i < m_numProjectiles; ++i )
	{
		Projectile& projectile = m_projectileArray[i];
		if ( !projectile.getIsActive( ) )
		{
			//Activates the projectile and breaks out of the loop so it doesn't activate more than one
			projectile.setIsActive( true );
			projectile.setPosition( gunPosition );
			++m_activeProjectiles;
			break;
		}
	}
}

//Setters and Getters

void ProjectileManager::setProjectileTexture( sf::Image newTexture )
{
	//Loops through all of the projectiles in the array and sets their texture based on the argument passed in by the parent object
	for ( int i = 0; i < m_numProjectiles; ++i )
	{
		m_projectileArray[i].setProjectileTexture( newTexture );
	}
}

void ProjectileManager::setProjectileSpeed( int projectileSpeed )
{
	for ( int i = 0; i < m_numProjectiles; ++i )
	{
		m_projectileArray[i].setVelocity( sf::Vector2f(0, projectileSpeed) );
	}
}

int ProjectileManager::getNumProjectiles( )
{
	//Returns the number of projectiles in the array
	return m_numProjectiles;
}

void ProjectileManager::setActiveProjectiles( int activeProjectiles )
{
	m_activeProjectiles = activeProjectiles;
}

int ProjectileManager::getActiveProjectiles( )
{
	//Returns the number of active projectiles in the array, so Game.cpp knows how many times to iterate through it in update
	return m_activeProjectiles;
}

Projectile& ProjectileManager::getProjectile( int projectileIndex )
{
	//Checks that the in passed in is within the bounds of the array. If so, the projectile at that index is returned. Otherwise, the program will close.
	ASSERT( projectileIndex < m_numProjectiles );
	return m_projectileArray[projectileIndex];
}

//Destructor

ProjectileManager::~ProjectileManager( )
{

}
