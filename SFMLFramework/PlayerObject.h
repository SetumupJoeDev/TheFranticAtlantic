#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "GameObject.h"

#include "GameSound.h"
#include "ParticleSystem.h"
#include "ProjectileManager.h"
#include "Settings.h"

class PlayerObject : public GameObject
{
private:

	//Booleans


	static constexpr std::uint_fast8_t m_canFire			{ 0b0000'0001 }; //Determines whether or not the ship can fire
	static constexpr std::uint_fast8_t m_leftPressed		{ 0b0000'0010 }; //Determines whether or not the left key is being pressed
	static constexpr std::uint_fast8_t m_rightPressed		{ 0b0000'0100 }; //Determines whether or not the right key is being pressed
	static constexpr std::uint_fast8_t m_spacePressed		{ 0b0000'1000 }; //Determines whether or not the space key is being pressed
	static constexpr std::uint_fast8_t m_isInvulnerable		{ 0b0001'0000 }; //Determines whether or not the player can take damage
	static constexpr std::uint_fast8_t m_isDead				{ 0b0010'0000 }; //Determines whether or not the player is dead
	static constexpr std::uint_fast8_t m_gameOver			{ 0b0100'0000 }; //Determines whether or not the player has gotten a game over
	static constexpr std::uint_fast8_t mask7				{ 0b1000'0000 }; //Represents bit 7

	std::uint_fast8_t m_flags { 0b0000'0101 }; //A group of bits used as boolean flags

	//Floats

	//The fixed amount of time between the player firing and being able to fire again
	const float m_fireCooldownDuration = Settings::Player::Weapons::g_weaponCooldown;

	//The current amount of time left before the player can fire their weapon
	float m_fireCooldown;

	//The fixed amount of time that the player is invulnerable for after respawning
	const float m_invulnerabilityDuration = Settings::Player::CountdownTimers::g_invulnerabilityDuration;

	//The current amount of time left before the player is no longer invulnerable
	float m_invulnerabilityTimer;

	//The fixed amount of time after dying before the player respawns
	const float m_respawnCooldownDuration = Settings::Player::CountdownTimers::g_respawnCooldownDuration;

	//The current amount of time left before the player respawns
	float m_respawnCooldown;

	//The speed at which the player moves across the screen
	const float m_moveSpeed = Settings::Player::Movement::g_moveSpeed;

	//The speed at which the player rotates during smooth rotation
	const float m_rotationSpeed = Settings::Player::Movement::g_rotationSpeed;

	//Images

	//The image used to represent the player's ship
	sf::Image m_shipTexture;

	//The image used to represent the player's projectiles
	sf::Image m_projectileTexture;

	//Integers

	//The leftmost position that the ship can move to
	int m_leftBound;

	//The rightmost position that the ship can move to
	int m_rightBound;

	//The current number of lives that the player has left
	int m_currentLives;

	//Objects

	//Manages all of the ships projectiles
	ProjectileManager m_projectileManager;

	//Particle Systems

	//The particle emitter for the ship's engine
	ParticleSystem m_engineParticles;

	//Sounds

	//The sound the ship makes when it is destroyed
	GameSound m_destroyedSound;

	//The sound the ship makes when it fires its torpedos
	GameSound m_fireSound;

	//Private Methods

	//Reads keyboard input and acts accordingly
	void detectInput( );

	//Runs actions that the player can make, such as firing weapons
	void playerActions( float deltaTime );

	//Runs the timer for invulnerability, reducing the timer by the value of deltaTime
	void invulnerabilityTimer( float deltaTime );

	//Runs the weapon cooldown timer, reducing the timer by the value of deltaTime
	void weaponCooldownTimer( float deltaTime );

	//Runs the respawn cooldown timer, reducing the timer by the value of deltaTime
	void respawnCooldownTimer( float deltaTime );

	//Changes the settings of the engine particle system
	void setupEngineParticles( );

	//Sets up the particle systems on the ship's projectiles
	void setupProjectileParticles( );

	//Updates the positions of the projectile particle emitters to the bottom of the projectiles
	void updateProjectileParticleEmitterPositions( );

	//Fires the player's torpedo weapons
	void fireWeapon( );

public:
	//Constructor

	PlayerObject( );

	//Destructor

	~PlayerObject( );

	//Methods

	//Runs every frame
	virtual void update( float deltaTime ) override;

	//Detects collisions between the ship and whatever is passed in
	bool detectCollisions( sf::FloatRect collisionRect );

	//Renders all of the player ship's child objects
	void render( sf::RenderWindow& renderWindow );

	//Resets the player so the game can be replayed
	void resetPlayer( );

	//Setters and Getters

	//Current Lives

	int getCurrentLives( );

	//Projectile Manager

	ProjectileManager& getProjectileManager( );

	//Is Dead

	bool getIsDead( );

	//Is Invulnerable

	bool getIsInvulnerable( );
		
	//Game Over

	bool getGameOver( );

};

#endif