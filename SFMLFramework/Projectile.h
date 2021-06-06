#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

#include "ParticleSystem.h"

class Projectile : public GameObject
{
private:

	//Booleans

	//Determines whether or not the projectile is active and should be rendered
	bool m_isActive;

	//Images

	//The image used to represent the projectile
	sf::Image m_projectileTexture;

	//Particles

	//The projectile's particle emitter
	ParticleSystem m_projectileParticles;

public:
	//Constructor
	Projectile( );

	//Methods

	//Renders the projectile's particles
	void renderParticles( sf::RenderWindow& renderWindow );

	//Runs every frame
	void virtual update( float deltaTime ) override;

	//Setters and Getters

	//Is Active
	void setIsActive( bool isActive );

	bool getIsActive( );

	//Particle System

	ParticleSystem& getProjectileParticles( );

	//Projectile Texture

	void setProjectileTexture( sf::Image newTexture );

	//Destructor
	~Projectile( );

};

#endif