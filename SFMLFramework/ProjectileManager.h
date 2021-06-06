#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <iostream>
#include <vector>


#include "Projectile.h"

#include "GameSound.h"
#include "Settings.h"

class ProjectileManager
{

private:

	//Integers

	//The number of active projectiles
	int m_activeProjectiles;

	//The speed at which the projectiles move
	int m_projectileSpeed;

	//The number of projectiles in the array
	static const int m_numProjectiles = Settings::ProjectileManager::g_numProjectiles;

	//Projectiles

	//The array of projectiles
	Projectile m_projectileArray[m_numProjectiles];

	//Private methods


public:

	//Constructor
	ProjectileManager( );

	//Methods

	//Runs every frame
	void update( float deltaTime );

	//Runs the logic behind firing a projectile
	void fireProjectile( sf::Vector2f playerPosition );

	//Setters and Getters

	//Number of projectiles

	int getNumProjectiles( );

	//Number of active projectiles

	void setActiveProjectiles( int activeProjectiles );

	int getActiveProjectiles( );

	//Projectiles

	Projectile& getProjectile( int projectileIndex );

	void setProjectileTexture( sf::Image newTexture );

	void setProjectileSpeed( int projectileSpeed );

	//Destructor
	~ProjectileManager( );

};

#endif