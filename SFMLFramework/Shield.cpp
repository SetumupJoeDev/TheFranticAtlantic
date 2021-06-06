
#include "Shield.h"

//Constructor

Shield::Shield( )
	:	m_currentHealth( m_maxHealth ),
		m_isActive( true ),
		m_movingLeft( true )
{

	m_objectTexture.loadFromFile( "Textures/ShieldSprite.png" );

	updateTexture( );

	setScale( sf::Vector2f( 2.0f, 2.0f ) );

	m_leftBoundary = 100;

	m_rightBoundary = 1100;

	m_currentVelocity = sf::Vector2f( -1, 0 );

}

//Methods

bool Shield::detectCollisions( sf::FloatRect collisionRect )
{
	//If the shield intersects with the projectile passed in, it loses health
	if ( getGlobalBounds( ).intersects( collisionRect ) )
	{
		//If the health reaches 0, the shield is set to inactive and can no longer be hidden behind
		if ( --m_currentHealth < 0 )
		{
			m_isActive = false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void Shield::update( float deltaTime )
{
	//Shield will move left to right to make the cover more dynamic
	move( m_currentVelocity * m_moveSpeed * deltaTime );
	if ( getPosition( ).x < m_leftBoundary && m_movingLeft || getPosition().x > m_rightBoundary && !m_movingLeft )
	{
		m_movingLeft = !m_movingLeft;
		m_currentVelocity.x *= -1;
	}
}

//Setters and Getters


bool Shield::getIsActive( )
{
	return m_isActive;
}

//Destructor

Shield::~Shield( )
{

}
