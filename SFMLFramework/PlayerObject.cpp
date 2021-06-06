
#include "PlayerObject.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <time.h>

#include "EmissionDirectionEnum.h"

//Constructor

PlayerObject::PlayerObject( )
	:	m_fireCooldown			( m_fireCooldownDuration ),
		m_invulnerabilityTimer	( m_invulnerabilityDuration ),
		m_respawnCooldown		( m_respawnCooldownDuration ),
		m_leftBound				( Settings::Player::Boundaries::g_leftBound ),
		m_rightBound			( Settings::Player::Boundaries::g_rightBound ),
		m_currentLives			( Settings::Player::Lives::g_initialLivesCount )
{
	m_flags |= m_canFire;
	m_fireSound.setSound( Settings::Player::Sounds::g_playerWeaponFire );

	m_destroyedSound.setSound( Settings::Player::Sounds::g_playerKilled );

	//Loads the ship's texture from a file and update's the texture of the object
	m_objectTexture.loadFromFile( Settings::Player::Textures::g_playerShipTexture );
	updateTexture( );

	m_projectileTexture.loadFromFile( Settings::Player::Textures::g_playerTorpedoTexture );
	m_projectileManager.setProjectileTexture( m_projectileTexture );

	//Sets the speed of the player's projectiles so that they move up the screen toward the enemies
	m_projectileManager.setProjectileSpeed( Settings::Player::Weapons::g_torpedoSpeed );

	//Increases the scale of the sprite to make it large enough to see properly
	setScale( Settings::Player::Vectors::g_playerScale );

	//Sets the origin of the player's ship to the center of the sprite
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );

	//Positions the ship in the center of the bottom quarter of the screen
	setPosition( Settings::Player::Vectors::g_playerSpawnPoint );

	setupEngineParticles( );

	setupProjectileParticles( );

}

//Private Methods

bool PlayerObject::detectCollisions( sf::FloatRect collisionRect )
{
	if ( getGlobalBounds( ).intersects( collisionRect ) )
	{
		if ( --m_currentLives < 0 )
		{
			m_flags |= m_gameOver;
		}
		//Plays the ship destroyed sound
		m_destroyedSound.play( );

		//Sets the necessary boolean flags so that the player is dead, and not moving left or right
		m_flags |= m_isDead;
		m_flags &= ~m_leftPressed;
		m_flags &= ~m_rightPressed;

		//Move the player to their spawn point
		setPosition( Settings::Player::Vectors::g_playerSpawnPoint );

		//Toggles engine emission off
		m_engineParticles.toggleEmission( );

		return true;
	}
	return false;
}

void PlayerObject::render( sf::RenderWindow& renderWindow )
{
	m_engineParticles.render( renderWindow );
	//Loops through all of the projectiles in the array, checking that each is active before drawing them to ensure only active projectiles are drawn
	for ( int i = 0; i < m_projectileManager.getNumProjectiles( ); ++i )
	{
		Projectile& currentProjectile = m_projectileManager.getProjectile( i );
		if ( currentProjectile.getIsActive( ) )
		{
			renderWindow.draw( currentProjectile );
			currentProjectile.renderParticles( renderWindow );
		}
	}
}

void PlayerObject::resetPlayer( )
{
	//Positions the ship in the center of the bottom quarter of the screen
	setPosition( Settings::Player::Vectors::g_playerSpawnPoint );

	//Resets the current number of lives that the player has, so the game can be played again
	m_currentLives = Settings::Player::Lives::g_initialLivesCount;

	//Sets isDead and gameOver to false so that the player will not die instantly when playing again
	m_flags &= ~m_isDead;
	m_flags &= ~m_gameOver;

	//Disables all of the projectiles the player has fired so that they can't kill enemies after the game ends
	for ( int i = 0; i < Settings::ProjectileManager::g_numProjectiles; ++i )
	{
		m_projectileManager.getProjectile( i ).setIsActive( false );
	}
}

void PlayerObject::detectInput( )
{
	//Reads the input from the keyboard
	if ( !sf::Keyboard::isKeyPressed( sf::Keyboard::A ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::D ) && ( m_flags & m_rightPressed ) || ( m_flags & m_leftPressed ) )
	{
		m_flags &= ~m_leftPressed;
		m_flags &= ~m_rightPressed;
	}
	//Otherwise, if the player is holding down only the A key, their velocity will be changed to move them left
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !( m_flags & m_leftPressed ) )
	{
		m_flags |= m_leftPressed;
		m_flags &= ~m_rightPressed;
	}
	//Otherwise, if the player is holding down only the D key, their velocity will be changed to move them right
	else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) && !sf::Keyboard::isKeyPressed( sf::Keyboard::A) && !( m_flags & m_rightPressed ) )
	{
		setRotation( 0.0f );
		m_flags |= m_rightPressed;
		m_flags &= ~m_leftPressed;
	}
	if ( !sf::Keyboard::isKeyPressed( sf::Keyboard::A ) && m_flags & m_leftPressed )
	{
		m_flags &= ~m_leftPressed;
	}
	if ( !sf::Keyboard::isKeyPressed( sf::Keyboard::D ) && m_flags & m_rightPressed )
	{
		m_flags &= ~m_rightPressed;
	}
	//If the player presses space and the weapons cooldown has ended, a projectile is fired
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && ( m_flags & m_canFire ) )
	{
		m_flags |= m_spacePressed;
	}
	if ( !sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && ( m_flags & m_spacePressed ) )
	{
		m_flags &= ~m_spacePressed;
	}
}

void PlayerObject::playerActions( float deltaTime )
{
	//Acts depending on the states of the flags
	if ( !( m_flags & m_leftPressed ) && !( m_flags & m_rightPressed ) )
	{
		setVelocity( sf::Vector2f( 0.0f, 0.0f ) );
		smoothRotate( getRotation( ), 0.0f, m_rotationSpeed );
	}
	//If the left key is pressed but not the right, the player ship moves left and is rotated slightly left
	if ( m_flags & m_leftPressed && !( m_flags & m_rightPressed ) )
	{
		smoothRotate( getRotation( ), Settings::Player::Movement::g_leftRotation, m_rotationSpeed );
		setVelocity( sf::Vector2f( -1, 0 ) );
	}
	//If the right key is pressed but not the left, the player ship moves right and is rotated slightly right
	if ( m_flags & m_rightPressed && !( m_flags & m_leftPressed ) )
	{
		smoothRotate( getRotation( ), Settings::Player::Movement::g_rightRotation, m_rotationSpeed );
		setVelocity( sf::Vector2f( 1, 0 ) );
	}
	//If the space button is pressed and the player can fire their weapon, the weapon is fired
	if ( m_flags & m_canFire && m_flags & m_spacePressed )
	{
		fireWeapon( );
	}
	//If the player is still within the boundaries of the game, they are moved depending on their current velocity
	if ( getPosition( ).x <= m_rightBound && getPosition( ).x >= m_leftBound )
	{
		move( getVelocity( ) * m_moveSpeed * deltaTime );
		//If the player's position is outside of the boundaries, their position is set to that of the boundary they are passing
		if ( getPosition( ).x > m_rightBound )
		{
			setPosition( sf::Vector2f( m_rightBound, getPosition( ).y ) );
		}
		else if ( getPosition( ).x < m_leftBound )
		{
			setPosition( sf::Vector2f( m_leftBound, getPosition( ).y ) );
		}
	}
}

void PlayerObject::invulnerabilityTimer( float deltaTime )
{
	//Runs down a timer that dictates how long the player is invulnerable for
	m_invulnerabilityTimer -= deltaTime;
	//When the timer reaches zero, the player is no longer invulnerable and the timer is reset
	//Their colour is also reset to white, in case they were transparent when the timer ran out
	if ( m_invulnerabilityTimer <= 0 )
	{
		m_flags &= ~m_isInvulnerable;
		m_invulnerabilityTimer = m_invulnerabilityDuration;
		setColor( sf::Color::White );
	}
	//If the timer is still running, the player's colour flashes between opaque and transparent to visualise their invulnerability
	else if ( getColor( ) == sf::Color::White )
	{
		setColor( sf::Color::Transparent );
	}
	else
	{
		setColor( sf::Color::White );
	}
}

void PlayerObject::weaponCooldownTimer( float deltaTime )
{
	//Runs a cooldown timer to prevent multiple shots from being fired at once
	m_fireCooldown -= deltaTime;
	if ( m_fireCooldown <= 0 )
	{
		m_flags |= m_canFire;
		m_fireCooldown = m_fireCooldownDuration;
	}
}

void PlayerObject::respawnCooldownTimer( float deltaTime )
{
	//Runs a cooldown timer to "respawn" the player after a small time passes
	m_respawnCooldown -= deltaTime;
	if ( m_respawnCooldown <= 0 )
	{
		m_flags &= ~m_isDead;
		m_flags |= m_isInvulnerable;
		m_respawnCooldown = m_respawnCooldownDuration;
		m_engineParticles.toggleEmission( );
	}
}

void PlayerObject::setupEngineParticles( )
{
	//Positions the emitter at the rear of the player's submarine, so the bubbles come from the engine
	m_engineParticles.setPosition( getPosition( ).x, getPosition( ).y + ( getGlobalBounds( ).height * 0.5f ) );

	//Sets the textures of the particles to be bubbles
	m_engineParticles.setParticleTexture( Settings::Player::Textures::g_bubbleParticleTexture );

	//Sets the lifetime of the particles, so that they disappear after a set time
	m_engineParticles.setParticleLifetime( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleLifetime );

	m_engineParticles.setEmissionInterval( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleEmissionInterval );

	//Sets the limit of active particles to prevent too many from being on screen at once
	m_engineParticles.setParticleLimit( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleLimit );

	//Sets the number of particles in a single emission to the value passed in
	m_engineParticles.setParticlesInEmission( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleNumInEmission );

	m_engineParticles.setParticleSpeed( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleMoveSpeed );

	m_engineParticles.setEmissionDirection( emissionDirections::South );

	m_engineParticles.setEmissionRadius( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleEmissionRadius );

	m_engineParticles.setReduceVelocity( true );

	m_engineParticles.setParticleScale( Settings::Player::ParticleSystems::EngineParticleSystem::g_engineParticleScale );

	m_engineParticles.toggleEmission( );
}

void PlayerObject::setupProjectileParticles( )
{
	for ( int i = 0; i < m_projectileManager.getNumProjectiles( ); ++i )
	{
		//Saves the current projectile to a local variable so it doesn't have to be retrieved again
		Projectile& currentProjectile = m_projectileManager.getProjectile( i );

		//Saves the particle system of the current projectile so it doesn't have to be retrieved for each setting
		ParticleSystem& currentParticleSystem = currentProjectile.getProjectileParticles( );

		//Positions the emitter at the rear of the player's torpedos, so the particles are emitted from the "propulsion system" of the torpedo
		currentParticleSystem.setPosition( currentProjectile.getPosition( ).x, currentProjectile.getPosition( ).y + currentProjectile.getGlobalBounds( ).height * 0.5f );

		//Sets the particles of the torpedos to use the bubble texture
		currentParticleSystem.setParticleTexture( Settings::Player::Textures::g_bubbleParticleTexture );

		currentParticleSystem.setParticleLifetime( 0.35f );

		currentParticleSystem.setEmissionInterval( 0.075f );

		currentParticleSystem.setParticlesInEmission( 10 );

		currentParticleSystem.setParticleSpeed( 12.5f );

		//Sets the particles emitted to move down the screen
		currentParticleSystem.setEmissionDirection( emissionDirections::South );

		currentParticleSystem.setEmissionRadius( 3 );

		currentParticleSystem.setReduceVelocity( false );

		currentParticleSystem.setParticleScale( sf::Vector2f( 0.2f, 0.2f ) );

		currentParticleSystem.toggleEmission( );

	}
}

void PlayerObject::updateProjectileParticleEmitterPositions( )
{
	for ( int i = 0; i < m_projectileManager.getNumProjectiles( ); ++i )
	{
		Projectile& currentProjectile = m_projectileManager.getProjectile( i );
		currentProjectile.getProjectileParticles( ).setPosition( currentProjectile.getPosition( ) );
	}
}

void PlayerObject::fireWeapon( )
{
	m_flags &= ~m_canFire;

	m_projectileManager.fireProjectile( sf::Vector2f( getPosition( ).x, getGlobalBounds( ).top ) );

	m_fireSound.PlayWithRandomPitch( );
}

//Methods

void PlayerObject::update( float deltaTime )
{
	//Reads input from the player before updating their position so the velocity vector is accurate
	if ( !( m_flags & m_isDead ) )
	{
		detectInput( );

		playerActions( deltaTime );

		m_engineParticles.setPosition( getPosition( ).x, getPosition( ).y + ( getGlobalBounds( ).height * 0.5f ) );

		updateProjectileParticleEmitterPositions( );
	}
	else
	{
		respawnCooldownTimer( deltaTime );
	}

	m_engineParticles.update( deltaTime );

	m_projectileManager.update( deltaTime );

	if ( !(m_flags & m_canFire) )
	{
		weaponCooldownTimer( deltaTime );
	}
	if ( m_flags & m_isInvulnerable )
	{
		invulnerabilityTimer( deltaTime );
	}
}

//Setters and Getters

//Projectile Manager

int PlayerObject::getCurrentLives( )
{
	return m_currentLives;
}

ProjectileManager& PlayerObject::getProjectileManager( )
{
	return m_projectileManager;
}

bool PlayerObject::getIsDead( )
{
	return m_flags & m_isDead;
}

bool PlayerObject::getIsInvulnerable( )
{
	return m_flags & m_isInvulnerable;
}

bool PlayerObject::getGameOver( )
{
	return m_flags & m_gameOver;
}

PlayerObject::~PlayerObject( )
{

}
