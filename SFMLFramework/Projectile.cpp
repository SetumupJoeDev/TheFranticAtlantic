#include "Projectile.h"

#include "Settings.h"

//Constructor

Projectile::Projectile( )
	: m_isActive (false)
{
	setVelocity( sf::Vector2f( 0, 0 ) );
	setScale( Settings::Projectile::g_projectileScale );
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );
}

//Methods

void Projectile::renderParticles( sf::RenderWindow& renderWindow )
{
	m_projectileParticles.render( renderWindow );
}

void Projectile::update( float deltaTime )
{
	//Moves up the screen each frame
	move( getVelocity( ) * deltaTime );
	//Once the projectile moves off screen, it is set as inactive so it can be fired again
	if ( getPosition( ).y < Settings::Projectile::g_projectileMinYPos || getPosition().y > Settings::Projectile::g_projectileMaxYPos )
	{
		m_isActive = false;
	}
	m_projectileParticles.update( deltaTime );
}

//Getters and Setters

void Projectile::setIsActive( bool isActive )
{
	m_isActive = isActive;
	//Deactivates all of the active particles on the projectile to reset them
	for ( int i = 0; i < Settings::ParticleSystem::g_numParticles; ++i )
	{
		m_projectileParticles.setParticleActive( i, false );
	}
}

bool Projectile::getIsActive( )
{
	return m_isActive;
}

ParticleSystem& Projectile::getProjectileParticles( )
{
	return m_projectileParticles;
}

void Projectile::setProjectileTexture( sf::Image newTexture )
{
	//Sets the projectile's texture to the new texture, and then updates to use it so it is displayed correctly on screen
	m_objectTexture.loadFromImage( newTexture );
	updateTexture( );
}

Projectile::~Projectile( )
{

}
