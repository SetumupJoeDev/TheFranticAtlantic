#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <iostream>
#include <fstream>

#include "EnemyBase.h"
#include "GameObject.h"
#include "GameSound.h"
#include "ScoreManager.h"
#include "Settings.h"

class EnemyManager : public GameObject
{

private:

	//Booleans

	//Determines whether or not the enemies can currently fire, used in the cooldown timer
	bool m_enemiesCanFire;

	//Determines whether or not the enemies have reached the player, triggering a game over
	bool m_enemiesReachedPlayer;

	//Determines whether the player is moving left or not
	bool m_movingLeft;

	//Determines wether or not the current wave of enemies has been defeated
	bool m_waveComplete;
	 
	//Integers

	//The number of enemies in the array of enemies
	static const int m_numEnemies = Settings::EnemyManager::g_numberOfEnemies;

	//The number of enemies in the current wave
	int m_enemiesInWave;

	//The number of enemies that have been killed in this wave
	int m_enemiesKilled;

	//Floats

	//The set duration of the enemy weapons cooldown timer
	const float m_fireCooldownDuration = Settings::EnemyManager::g_firingInterval;

	//The time left before the enemies can fire again
	float m_fireCooldownTimer;

	//The set duration of the enemy respawn cooldown timer
	const float m_enemyRespawnCooldownDuration = 2.5f;

	//The time left before the enemies respawn
	float m_enemyRespawnTimer;

	//The X position of the enemy currently being positioned
	float m_enemyX;

	//The Y position of the enemy currently being positioned
	float m_enemyY;

	//The speed at which the enemies move
	float m_moveSpeed;

	//Vectors

	//The current volecity of the enemies, determining if they are moving left or right
	sf::Vector2f m_enemyVelocity;

	//Enemy Arrays

	//The array of enemies in the game
	EnemyBase m_basicEnemies[m_numEnemies];

	//Projectile Manager

	//The manager for all of the enemy projectiles
	ProjectileManager m_enemyProjectiles;

	//The sound to be played when an enemy fires a projectile
	GameSound m_fireSound;

	//Text Files

	//The basic enemy layout text file
	std::ifstream m_basicLayoutFile;

	char m_basicLayout[m_numEnemies];

	//Private Methods

	//Checks to see if any enemies have reached the sides of the screen, or the player
	void checkEnemiesReachedBoundaries( );

	//Calculates an enemy from which a projectile should be fire, and does so
	void enemiesFire( );

	//Runs a timer to determine whether or not an enemy should fire yet
	void fireCooldown( float deltaTime );

	//Runs a timer to determine whether or not the enemies can respawn yet
	void respawnCooldown( float deltaTime );

	//Moves the enemies across the screen
	void moveEnemies( float deltaTime );

	//Places an enemy at the current position
	void placeEnemy( int currentEnemyIndex, std::string enemyTexture = Settings::EnemyBase::Textures::g_enemyTexture );

public:

	//Constructor
	EnemyManager( );

	//Methods

	//Positions the enemies on screen
	void positionEnemies( char* levelLayout );

	//Renders all of the enemies and projectiles
	void render( sf::RenderWindow& renderWindow );

	void resetEnemies( );

	//Runs every frame
	void update( float deltaTime );

	//Detects collisions between an enemy and the player's projectiles
	bool detectCollisions( sf::FloatRect collisionRect, ScoreManager& scoreManager, UIManager& uiManager );

	//Setters and Getters

	//Enemies

	//Returns the enemy at the given index, passed in through the parameters
	EnemyBase& getEnemy( int enemyIndex );

	//NumEnemies

	//Returns the number of enemies in the array
	int getNumEnemies( );

	//Enemies Reached Player

	void setEnemiesReachedPlayer( bool reachedPlayer );

	bool getEnemiesReachedPlayer( );

	//Projectile Manager

	//Returns the projectile manager object
	ProjectileManager& getProjectileManager( );

	//Destructor
	~EnemyManager( );

};

#endif // !ENEMYMANAGER_H
