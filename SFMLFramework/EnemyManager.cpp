
#include "EnemyManager.h"

//Constructor

EnemyManager::EnemyManager( )
	:	m_enemyX			( Settings::EnemyManager::g_initialEnemyXPos ),
		m_enemyY			( Settings::EnemyManager::g_initialEnemyYPos ),
		m_fireCooldownTimer	( m_fireCooldownDuration ),
		m_enemyRespawnTimer	( m_enemyRespawnCooldownDuration ),
		m_moveSpeed			( Settings::EnemyBase::Movement::g_horizontalMoveSpeed ),
		m_movingLeft		( true ),
		m_enemiesInWave		( 0 )
{

	setPosition( sf::Vector2f( Settings::Game::Window::g_windowWidth * 0.5f, Settings::Game::Window::g_windowHeight * 0.5f ) );

	m_enemyVelocity = sf::Vector2f( -1, 0 );

	m_enemyProjectiles.setProjectileSpeed( 200.0f );

	//Creates a local image and assigns it the projectile texture from the settings namespace
	sf::Image enemyProjectile;
	enemyProjectile.loadFromFile( Settings::EnemyBase::Textures::g_enemyProjectileTexture );

	//Assigns the previously loaded image file to the projectiles
	m_enemyProjectiles.setProjectileTexture( enemyProjectile );

	//Loads the text file containing the basic layout of the enemies
	m_basicLayoutFile.open( "LevelLayouts/BasicLayout.txt" );

	//Saves all of the text in the file to a char array until it reaches the end of the file, then closes it
	if ( m_basicLayoutFile.is_open( ) )
	{
		while ( !m_basicLayoutFile.eof( ) )
		{
			m_basicLayoutFile >> m_basicLayout;
		}
	}

	//Sets up the enemy layout using the text loaded previously
	positionEnemies( m_basicLayout );
}

//Methods

bool EnemyManager::detectCollisions( sf::FloatRect collisionRect, ScoreManager& scoreManager, UIManager& uiManager )
{
	//Loops through all of the enemies in the array and checks wether they overlap with the projectile passed in or not
	for ( int i = 0; i < m_numEnemies; ++i )
	{
		EnemyBase& currentEnemy = m_basicEnemies[i];
		//If they overlap and are alive, they are killed and the score is increased by the value assigned in the settings
		if ( currentEnemy.getIsAlive( ) && currentEnemy.getGlobalBounds( ).intersects( collisionRect ) )
		{
			currentEnemy.setIsAlive( false );
			++m_enemiesKilled;
			m_moveSpeed += Settings::EnemyBase::Movement::g_speedIncrementValue;
			if ( m_enemiesKilled == m_enemiesInWave )
			{
				m_waveComplete = true;
			}
			scoreManager.setCurrentScore( scoreManager.getCurrentScore( ) + Settings::EnemyManager::g_scoreValue, uiManager);
			return true;
		}
	}
	return false;
}

void EnemyManager::checkEnemiesReachedBoundaries( )
{
	//Loops through all of the enemies to see if they have reached any boundaries
	for ( int i = 0; i < m_numEnemies; ++i )
	{
		EnemyBase& currentEnemy = m_basicEnemies[i];

		if ( currentEnemy.getIsAlive( ) )
		{
			//If the enemies have reached the player's position, the game ends
			if ( currentEnemy.getPosition( ).y >= Settings::Player::Vectors::g_playerSpawnPoint.y )
			{
				m_enemiesReachedPlayer = true;
			}
			//If the enemies have reached the edges of the play area, they moved down the screen
			else if ( m_movingLeft && currentEnemy.getPosition( ).x <= 100 )
			{
				m_movingLeft = false;
				setPosition( sf::Vector2f( getPosition( ).x, getPosition( ).y + Settings::EnemyBase::Movement::g_verticalMovementDistance ) );
				m_enemyVelocity.x *= -1;
			}
			else if ( !m_movingLeft && currentEnemy.getPosition( ).x >= Settings::Game::Window::g_windowWidth - 100 )
			{
				m_movingLeft = true;
				setPosition( sf::Vector2f( getPosition( ).x, getPosition( ).y + Settings::EnemyBase::Movement::g_verticalMovementDistance ) );
				m_enemyVelocity.x *= -1;
			}
		}
	}
}

void EnemyManager::enemiesFire( )
{
	//Generates a random array index to choose an enemy to "fire" from until it finds an active enemy to use as a firing point
	while ( m_enemiesCanFire == true )
	{
		int enemyIndex = rand( ) % ( m_numEnemies - 1 );
		EnemyBase& enemyToFire = m_basicEnemies[enemyIndex];
		if ( enemyToFire.getIsAlive( ) )
		{
			//Fires a projectile from the "gun" position of the enemy, and plays their firing sound
			m_enemyProjectiles.fireProjectile( sf::Vector2f( enemyToFire.getPosition( ).x, enemyToFire.getPosition( ).y + enemyToFire.getGlobalBounds( ).height * 0.5f ) );
			m_fireSound.PlayWithRandomPitch( );
			m_enemiesCanFire = false;
		}
	}
}

void EnemyManager::fireCooldown( float deltaTime )
{
	//Reduces the value of the cooldown timer by the value of deltatime
	m_fireCooldownTimer -= deltaTime;
	//When the timer reaches zero, an enemy fires a projectile and the cooldown is reset
	if ( m_fireCooldownTimer <= 0.0f )
	{
		m_enemiesCanFire = true;
		m_fireCooldownTimer = m_fireCooldownDuration;
		enemiesFire( );
	}
}

void EnemyManager::respawnCooldown( float deltaTime )
{
	m_enemyRespawnTimer -= deltaTime;
	if ( m_enemyRespawnTimer <= 0 )
	{
		resetEnemies( );
	}
}

void EnemyManager::moveEnemies( float deltaTime )
{
	//Moves the enemy manager across the screen, if the leftmost or rightmost enemies reach the edge then they moved down the screen 
	move( m_enemyVelocity * m_moveSpeed * deltaTime );
	//updates all of the enemies' positions using their offset from the origin
	for ( int i = 0; i < m_numEnemies; ++i )
	{
		EnemyBase& currentEnemy = m_basicEnemies[i];
		currentEnemy.setPosition( getPosition( ).x + currentEnemy.getXOffset( ), getPosition( ).y + currentEnemy.getYOffset( ) );
	}
}

void EnemyManager::placeEnemy( int currentEnemyIndex, std::string enemyTexture )
{
	EnemyBase& currentEnemy = m_basicEnemies[currentEnemyIndex];

	//Positions the enemy at the location dictated by the current values of enemyX and enemyY
	currentEnemy.setPosition( sf::Vector2f( m_enemyX, m_enemyY ) );
	//Calculates the X and Y offsets from the origin of the EnemyManager so they can be moved correctly
	currentEnemy.setXOffset( currentEnemy.getPosition( ).x - getPosition( ).x );
	currentEnemy.setYOffset( currentEnemy.getPosition( ).y - getPosition( ).y );
	//Sets the enemies texture dependant on what was passed through in the parameters
	currentEnemy.getObjectTexture( ).loadFromFile( enemyTexture );
	currentEnemy.updateTexture( );
	//Activates the enemy so that it will be rendered and updated
	currentEnemy.setIsAlive( true );
	//Increments the number of enemies in the wave by one, so that the game can determine when a wave has been defeated
	++m_enemiesInWave;
}

void EnemyManager::positionEnemies( char* levelLayout )
{

	int currentEnemyIndex = 0;

	//Loops through all of the characters in the 
	for ( int i = 0; i < m_numEnemies; ++i )
	{
		switch ( m_basicLayout[i] )
		{
		case 'x':
		{
			placeEnemy( currentEnemyIndex );
			++currentEnemyIndex;
		}
		break;
		case 'y':
		{
			placeEnemy( currentEnemyIndex, Settings::EnemyBase::Textures::g_enemyVariantTexture );
			++currentEnemyIndex;
		}
		break;
		case 'o':
		{
			//Leave this space empty and move on to the next
		}
		break;
		default:
		{
			placeEnemy( currentEnemyIndex );
			++currentEnemyIndex;
		}
		break;
		}
		m_enemyX += Settings::EnemyManager::g_enemySpacing;
		if ( m_enemyX >= Settings::EnemyManager::g_enemyXPosLimit )
		{
			m_enemyX = Settings::EnemyManager::g_initialEnemyXPos;
			m_enemyY += Settings::EnemyManager::g_enemySpacing;
		}
	}
}

void EnemyManager::render( sf::RenderWindow& renderWindow )
{
	//Loops through the array of enemies, checking that each is alive before rendering it
	for ( int i = 0; i < m_numEnemies; ++i )
	{
		EnemyBase& currentEnemy = m_basicEnemies[i];
		if ( currentEnemy.getIsAlive( ) )
		{
			renderWindow.draw( currentEnemy );
		}
	}
	//Loops through all of the projectiles in the array, checking that each is active before rendering it
	for ( int i = 0; i < m_enemyProjectiles.getNumProjectiles( ); ++i )
	{
		Projectile& currentProjectile = m_enemyProjectiles.getProjectile( i );
		if ( currentProjectile.getIsActive( ) )
		{
			renderWindow.draw( currentProjectile );
		}
	}
}

void EnemyManager::resetEnemies( )
{
	//Resets the position of the enemy manager to the center of the screen
	setPosition( sf::Vector2f( Settings::Game::Window::g_windowWidth * 0.5f, Settings::Game::Window::g_windowHeight * 0.5f ) );
	//Resets the X and Y positions of the first enemy in the array for correct positioning
	m_enemyX = Settings::EnemyManager::g_initialEnemyXPos;
	m_enemyY = Settings::EnemyManager::g_initialEnemyYPos;
	//Resets wave data so the game can continue to be played
	m_enemiesInWave = 0;
	m_enemiesKilled = 0;
	m_waveComplete = false;
	//Resets the move speed to the default
	m_moveSpeed = Settings::EnemyBase::Movement::g_horizontalMoveSpeed;
	//Repositions the enemies
	positionEnemies( m_basicLayout );
}

void EnemyManager::update( float deltaTime )
{
	moveEnemies( deltaTime );
	checkEnemiesReachedBoundaries( );
	//If the enemies can't currently fire, and the wave has not been completed, the firing countdown is run
	//Checking if the wave has not been completed prevents the game from hanging when the enemies attempt to fire but can't find an active enemy to fire from
	if ( !m_enemiesCanFire && !m_waveComplete )
	{
		fireCooldown( deltaTime );
	}
	//If the wave has been completed, the enemy respawn timer is run to prevent enemies respawning immediately
	//This gives the player a short break between waves to rest
	if ( m_waveComplete )
	{
		respawnCooldown( deltaTime );
	}
	//Runs the update function of the enemy projectile manager, updating all of its active projectiles and their particles
	m_enemyProjectiles.update( deltaTime );
}

//Setters and Getters

//Returns the enemy at the given address in the array
EnemyBase& EnemyManager::getEnemy( int enemyIndex )
{
	return m_basicEnemies[enemyIndex];
}

//Returns the number of enemies in the array
int EnemyManager::getNumEnemies( )
{
	return m_numEnemies;
}

void EnemyManager::setEnemiesReachedPlayer( bool reachedPlayer )
{
	m_enemiesReachedPlayer = reachedPlayer;
}

bool EnemyManager::getEnemiesReachedPlayer( )
{
	return m_enemiesReachedPlayer;
}

//Returns the enemy projectile manager
ProjectileManager& EnemyManager::getProjectileManager( )
{
	return m_enemyProjectiles;
}

//Destructor

EnemyManager::~EnemyManager( )
{
}