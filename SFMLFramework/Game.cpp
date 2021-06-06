
#include "Game.h"

#include "Settings.h"

Game::Game( )
	: m_isFullScreen( false )
{

	m_playerShip = new PlayerObject( );

	m_enemyManager = new EnemyManager( );

	m_shield.setPosition( sf::Vector2f( Settings::Game::Window::g_windowWidth * 0.5f, Settings::Game::Window::g_windowHeight * 0.75f ) );

	//Creates a render window with dimensions taken from the settings namespace
	m_renderWindow.create( sf::VideoMode( Settings::Game::Window::g_windowWidth, Settings::Game::Window::g_windowHeight ), Settings::Game::Window::g_gameName );

	//Loads the window's icon from the file denoted in the path
	m_windowIcon.loadFromFile( Settings::Game::Window::g_windowIconFile );

	//Sets the window's icon to the image saved in m_windowIcon
	m_renderWindow.setIcon( m_windowIcon.getSize( ).x, m_windowIcon.getSize( ).y, m_windowIcon.getPixelsPtr( ) );

	//Sets the current game state to main menu, so it is displayed when the game loads
	m_currentGameState = gameStates::mainMenu;

	//Updates the UI elements to use the correct values from the player and score manager
	m_uiManager.updateLivesText( m_playerShip->getCurrentLives( ) );

	m_uiManager.updateScoreText( m_scoreManager.getCurrentScore( ) );

	//Sets the current track on the music player to be the main menu theme
	m_musicManager.changeTrack( m_currentGameState, true );

	//Reads the high scores from the high score text file
	m_scoreManager.readHighScores( );

	//Updates the menu's high score display text
	m_menuManager.updateScoreTexts( m_scoreManager );

	loadBackgroundImages( );

	//Calculates the initial deltaTime value after everything has initialised to ensure the first value gained in update is small enough to be of use
	calculateDeltaTime( );

}

void Game::renderGame( )
{
	//Renders the game's background image
	m_renderWindow.draw( m_atlantisBackground );

	if ( m_shield.getIsActive( ) )
	{
		m_renderWindow.draw( m_shield );
	}

	//Draws the player's ship on screen
	if ( !m_playerShip->getIsDead( ) )
	{
		m_renderWindow.draw( *m_playerShip );
	}

	//Renders all of the UI elements in the UI manager
	m_uiManager.render( m_renderWindow );

	//Renders all of the player ship's childed objects
	m_playerShip->render( m_renderWindow );

	//Draws the enemies on screen
	m_enemyManager->render( m_renderWindow );

}

void Game::renderDeathScreen( )
{
	m_renderWindow.clear( );
	m_renderWindow.draw( m_mainMenuBackground );
	m_menuManager.renderMenu( m_renderWindow );
}

void Game::toggleFullScreen( )
{
	//Toggles the boolean
	m_isFullScreen = !m_isFullScreen;
	//If the game is not already in fullscreen, it will have been toggled to true and so the window is "recreated" in full screen
	if ( m_isFullScreen )
	{
		m_renderWindow.create( sf::VideoMode( Settings::Game::Window::g_windowWidth, Settings::Game::Window::g_windowHeight ), Settings::Game::Window::g_gameName );
	}
	//Otherwise, the window is recreated in windowed mode
	else
	{
		m_renderWindow.create( sf::VideoMode( Settings::Game::Window::g_windowWidth, Settings::Game::Window::g_windowHeight ), Settings::Game::Window::g_gameName, sf::Style::Fullscreen );
	}
	//Resets the bool in the menu manager to avoid constant triggers
	m_menuManager.setToggleFullscreen( false );
}

void Game::update( )
{
	//If the game has ended, the death screen is loaded and the game reset
	if ( m_playerShip->getGameOver( ) || m_enemyManager->getEnemiesReachedPlayer( ) )
	{
		//Sets up the game over menu before resetting the game
		m_currentGameState = gameStates::deathScreen;
		m_musicManager.changeTrack( m_currentGameState, true );
		m_menuManager.loadGameOverLayout( m_scoreManager );
		resetGame( );
	}

	//Checks to see if any projectiles have hit anything
	checkForCollisions( );

	//Runs the ship's update function, passing in the deltaTime float to create smoother movement
	m_playerShip->update( m_deltaTime );

	//Runs the enemy manager's update function
	m_enemyManager->update( m_deltaTime );

	if ( m_shield.getIsActive( ) )
	{
		m_shield.update( m_deltaTime );
	}

}

void Game::checkForCollisions( )
{
	ProjectileManager& playerProjectiles = m_playerShip->getProjectileManager( );

	ProjectileManager& enemyProjectiles = m_enemyManager->getProjectileManager( );

	//Loops through all of the ship's active projectiles and checks whether or not their bounds overlap with any of the active enemies


	for ( int i = 0; i < playerProjectiles.getNumProjectiles( ); ++i )
	{
		Projectile& currentPlayerProjectile = playerProjectiles.getProjectile( i );

		if ( currentPlayerProjectile.getIsActive( ) )
		{
			if ( m_enemyManager->detectCollisions( currentPlayerProjectile.getGlobalBounds( ), m_scoreManager, m_uiManager ) )
			{
				//If the check returns as true, the projectile is set to inactive and the number of active projectiles is reduced by one
				currentPlayerProjectile.setIsActive( false );
				playerProjectiles.setActiveProjectiles( playerProjectiles.getActiveProjectiles( ) - 1 );
			}
		}
	}

	//Detects collisions between enemy projectiles and the player, but only if they aren't invulnerable
	if ( !m_playerShip->getIsInvulnerable( ) )
	{
		for ( int i = 0; i < enemyProjectiles.getNumProjectiles( ); ++i )
		{
			Projectile& currentProjectile = enemyProjectiles.getProjectile( i );

			if ( currentProjectile.getIsActive( ) && !m_playerShip->getIsDead( ) )
			{
				if ( m_playerShip->detectCollisions( currentProjectile.getGlobalBounds( ) ) )
				{
					//If the projectile hit the player, it is made inactive
					currentProjectile.setIsActive( false );
					m_uiManager.updateLivesText( m_playerShip->getCurrentLives( ) );
				}
			}
		}
	}

	//Detects collisions between both the enemy and player projectiles and the shields

	if ( m_shield.getIsActive( ) )
	{
		for ( int i = 0; i < enemyProjectiles.getNumProjectiles( ); ++i )
		{
			Projectile& currentProjectile = enemyProjectiles.getProjectile( i );

			if ( currentProjectile.getIsActive( ) )
			{
				if ( m_shield.detectCollisions( currentProjectile.getGlobalBounds( ) ) )
				{
					currentProjectile.setIsActive( false );
				}
			}
		}

		for ( int i = 0; i < playerProjectiles.getNumProjectiles( ); ++i )
		{
			Projectile& currentProjectile = playerProjectiles.getProjectile( i );

			if ( currentProjectile.getIsActive( ) )
			{
				if ( m_shield.detectCollisions( currentProjectile.getGlobalBounds( ) ) )
				{
					currentProjectile.setIsActive( false );
				}
			}
		}
	}

}

void Game::calculateDeltaTime( )
{
	//Restarts the clock each frame, which returns the amount of time passed since it was started, giving us deltaTime, and saves it to a float
	m_deltaTime = m_deltaClock.restart( ).asSeconds();
}

void Game::toggleMute( )
{
	//Toggles the music volume on and off 
	m_musicManager.toggleMuteMusic( );
	//Resets the boolean to false so that the volume is not constantly toggled on and off
	m_menuManager.setToggleMute( false );
}

void Game::loadBackgroundImages( )
{
	//Loads the image for the main menu background from a file
	if ( !m_mainMenuBackground.getObjectTexture( ).loadFromFile( Settings::Game::Menus::g_mainMenuImage ) )
	{
		std::cout << "Main menu background failed to load!";
	}

	//Updates the main menu background's texture to the newly loaded image
	m_mainMenuBackground.updateTexture( );

	//Loads the image for the game's background from a file
	if ( !m_atlantisBackground.getObjectTexture( ).loadFromFile( Settings::Game::Menus::g_gameBackgroundImage ) )
	{
		std::cout << "Atlantis background failed to load!";
	}

	//Updates the game background's texture to the newly loaded image
	m_atlantisBackground.updateTexture( );

	//Calculates the origins of both background images using their height and width
	m_mainMenuBackground.setOrigin( m_mainMenuBackground.getLocalBounds( ).width * 0.5f, m_mainMenuBackground.getLocalBounds( ).height * 0.5f );

	m_atlantisBackground.setOrigin( m_atlantisBackground.getLocalBounds( ).width * 0.5f, m_atlantisBackground.getLocalBounds( ).height * 0.5f );

	//Positions the main menu background image in the center of the screen
	m_mainMenuBackground.setPosition( Settings::Game::Menus::g_backgroundPosition );

	//Scales up the main menu background so it fills the screen
	m_mainMenuBackground.setScale( Settings::Game::Menus::g_mainMenuImageScale );

	//Positions the game's background in the center of the screen
	m_atlantisBackground.setPosition( Settings::Game::Menus::g_backgroundPosition );
}

void Game::resetGame( )
{
	//Resets the player to restore its lives count and position
	m_playerShip->resetPlayer( );
	//Sets this to false so that the game does not auto-trigger a game over
	m_enemyManager->setEnemiesReachedPlayer( false );
	//Checks to see if the player has achieved a new high score
	m_scoreManager.checkForNewHighScore( );
	//Updates the UI elements to reflect the now reset values
	m_uiManager.updateLivesText( m_playerShip->getCurrentLives( ) );
	m_uiManager.updateScoreText( m_scoreManager.getCurrentScore( ) );
	//Resets the enemy formation
	m_enemyManager->resetEnemies( );
	//Updates the high score texts for the main menu with potentially new high scores
	m_menuManager.updateScoreTexts( m_scoreManager );
}

void Game::runGame( )
{
	//Clears the screen to allow things to be drawn in their new positions, if they have moved
	m_renderWindow.clear( sf::Color::Blue );
	//Runs the update function of the game
	update( );
	//Renders all of the necessary objects in the game
	renderGame( );
}

void Game::runDeathScreen( )
{
	//Renders the death screen elements
	renderDeathScreen( );

	m_menuManager.update( m_deltaTime, m_renderWindow );

	//Checks to see if any of the menu buttons were clicked and acts accordingly
	if ( m_menuManager.getWasQuitClicked( ) )
	{
		m_renderWindow.close( );
	}
	if ( m_menuManager.getIsReturningToMain( ) )
	{
		m_menuManager.setIsReturningToMain( false );
		m_currentGameState = gameStates::mainMenu;
		m_musicManager.changeTrack( m_currentGameState, true );
	}
}

void Game::renderMainMenu( )
{
	//Renders the menu background and the menu elements
	m_renderWindow.draw( m_mainMenuBackground );
	m_menuManager.renderMenu( m_renderWindow );
}

void Game::runMainMenu( )
{
	m_menuManager.update( m_deltaTime, m_renderWindow );
	//Checks to see if any of the menu buttons were clicked and acts accordingly
	if ( m_menuManager.getWasPlayClicked( ) )
	{
		m_menuManager.setWasPlayClicked( false );
		m_currentGameState = gameStates::inGame;
		m_musicManager.changeTrack( m_currentGameState, true );
	}
	if ( m_menuManager.getToggleFullscreen( ) )
	{
		toggleFullScreen( );
	}
	if ( m_menuManager.getToggleMute( ) )
	{
		toggleMute( );
	}
	if ( m_menuManager.getWasQuitClicked( ) )
	{
		m_renderWindow.close( );
	}
	renderMainMenu( );
}

void Game::runMainLoop( )
{
	while ( m_renderWindow.isOpen( ) )
	{
		calculateDeltaTime( );
		sf::Event event;
		while ( m_renderWindow.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
				m_renderWindow.close( );
		}
		switch ( m_currentGameState )
		{
		case gameStates::mainMenu:
		{
			runMainMenu( );
		}
		break;

		case gameStates::inGame:
		{
			//Game code goes here
			runGame( );
		}
		break;
		case gameStates::deathScreen:
		{
			//Death screen code goes here
			runDeathScreen( );
		}
		break;
		}

		//Displays the window
		m_renderWindow.display( );
	}
}

Game::~Game( )
{

}