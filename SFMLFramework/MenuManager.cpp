
#include "MenuManager.h"

#include <cstdlib>
#include <iostream>

//Constructor

MenuManager::MenuManager( )
	: m_buttonLerpIndex ( 0 ),
	  m_toggleFullscreen( false )
{

	loadMainMenuLayout( );

	//Positions the title on screen
	m_titleText.setPosition( m_titleOnScreenPos );
	
	//Positions all of the necessary buttons on screen
	MenuButton& startButton = m_menuButtons[0];
	startButton.setPosition( m_playButtonOnScreenPos );
	startButton.updateTextPosition( );
	startButton.calculateBounds( );

	MenuButton& optionsButton = m_menuButtons[1];
	optionsButton.setPosition( m_optionsButtonOnScreenPos );
	optionsButton.updateTextPosition( );
	optionsButton.calculateBounds( );

	MenuButton& quitButton = m_menuButtons[2];
	quitButton.setPosition( m_quitButtonOnScreenPos );
	quitButton.updateTextPosition( );
	quitButton.calculateBounds( );

	m_currentMenuState = MenuManager::menuState::mainMenu;
}

//Methods

void MenuManager::calculateButtonBounds( )
{
	for ( int i = 0; i < m_numButtons; ++i )
	{
		if ( m_menuButtons[i].getIsActive( ) )
		{
			m_menuButtons[i].calculateBounds( );
		}
	}
}

void MenuManager::checkIfButtonsClicked( float deltaTime )
{
	for ( int i = 0; i < m_numButtons; ++i )
	{
		MenuButton& currentButton = m_menuButtons[i];
		if ( currentButton.getIsActive( ) && currentButton.getWasClicked( ) )
		{
			switch ( m_currentMenuState )
			{
			case MenuManager::menuState::mainMenu:
			{
				//Main Menu button checks
				switch ( i )
				{
				case( 0 ):
				{
					m_wasPlayClicked = true;
				}
				break;

				case( 1 ):
				{
					m_swapLayout = true;
					m_targetMenuState = menuState::optionsMenu;
				}
				break;

				case( 2 ):
				{
					m_wasQuitClicked = true;
				}
				break;
				default:
				{
					std::cout << "Button function not found. Something went wrong.\n";
				}
					break;
				}
			}
				break;
			case MenuManager::menuState::optionsMenu:
				//Options Menu button checks
				switch ( i )
				{
				case( 0 ):
				{
					m_toggleFullscreen = true;
					calculateButtonBounds( );
				}
				break;
				case( 1 ):
				{
					m_toggleMute = true;
				}
				break;
				case( 2 ):
				{
					m_swapLayout = true;
					m_targetMenuState = menuState::mainMenu;
				}
				break;
				default:
				{
					std::cout << "Button function not found. Something went wrong.\n";
				}
					break;
				}
				break;
			case MenuManager::menuState::gameOverMenu:
			{
				switch ( i )
				{
				case 0:
				{
					m_isReturningToMain = true;
					m_swapLayout = true;
					m_targetMenuState = menuState::mainMenu;
				}
				break;
				case 1:
				{
					m_wasQuitClicked = true;
				}
				break;
				}
			}
				break;
			default:
				break;
			}
		}
	}
}

void MenuManager::loadMainMenuLayout(  )
{
	//Sets up the title text by setting its string and position
	m_titleText.setString( Settings::MenuManager::Titles::g_mainMenuTitle );
	m_titleText.setCharacterSize( Settings::MenuManager::Titles::g_titleCharSize );
	m_titleText.updateTextOrigin( );

	//Sets up the "Start" button by setting the text and position
	MenuButton& startButton = m_menuButtons[0];
	startButton.setIsActive( true );
	startButton.setWasClicked( false );
	startButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_playButtonLabel );
	startButton.getButtonText( ).setCharacterSize( 30 );

	//Sets up the "Options" button by setting the text and position
	MenuButton& optionsButton = m_menuButtons[1];
	optionsButton.setIsActive( true );
	optionsButton.setWasClicked( false );
	optionsButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_optionsButtonLabel );
	optionsButton.getButtonText( ).setCharacterSize( 30 );

	//Sets up the quit button by setting the text and position
	MenuButton& quitButton = m_menuButtons[2];
	quitButton.setIsActive( true );
	quitButton.setWasClicked( false );
	quitButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_quitButtonLabel );
}

void MenuManager::loadOptionsMenuLayout( )
{
	//Sets up the title text for the options menu by setting its string and position
	m_titleText.setString( Settings::MenuManager::Titles::g_optionsMenuTitle );
	m_titleText.updateTextOrigin( );

	//Sets up the first options button
	MenuButton& toggleFullscreen = m_menuButtons[0];
	toggleFullscreen.setIsActive( true );
	toggleFullscreen.setWasClicked( false );
	toggleFullscreen.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_toggleFullScreenButtonLabel );
	toggleFullscreen.getButtonText( ).setCharacterSize( 15 );

	//Sets up the second options button
	MenuButton& toggleMute = m_menuButtons[1];
	toggleMute.setIsActive( true );
	toggleMute.setWasClicked( false );
	toggleMute.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_muteMusicButtonLabel );
	toggleMute.getButtonText( ).setCharacterSize( Settings::MenuManager::Buttons::Labels::g_optionsButtonCharSize );

	//Sets up the third options button
	MenuButton& backButton = m_menuButtons[2];
	backButton.setIsActive( true );
	backButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_backButtonLabel );
}

void MenuManager::loadGameOverLayout( ScoreManager& scoreManager )
{
	//Sets up the title text for the game over menu by setting its string and position
	m_titleText.setString( Settings::MenuManager::Titles::g_gameOverTitle );
	m_titleText.updateTextOrigin( );
	m_titleText.setPosition( Settings::MenuManager::Titles::Vectors::g_titleOnScreenPos );

	//Sets up the final score text using the player's final score
	m_finalScoreText.setString( "Your final score was: " + std::to_string( scoreManager.getCurrentScore( ) ) );
	m_finalScoreText.updateTextOrigin( );
	m_finalScoreText.setPosition( Settings::MenuManager::Titles::Vectors::g_finalScorePosition );

	//Sets up the return to main button
	MenuButton& mainMenuButton = m_menuButtons[0];
	mainMenuButton.setIsActive( true );
	mainMenuButton.setWasClicked( false );
	mainMenuButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_mainMenuButtonLabel );
	mainMenuButton.getButtonText( ).setCharacterSize( Settings::MenuManager::Buttons::Labels::g_mainMenuButtonCharSize );
	mainMenuButton.setPosition( Settings::MenuManager::Buttons::Vectors::g_optionsButtonOnScreenPos );
	mainMenuButton.updateTextPosition( );

	//Sets up the quit button
	MenuButton& quitButton = m_menuButtons[1];
	quitButton.setIsActive( true );
	quitButton.setWasClicked( false );
	quitButton.setButtonTextString( Settings::MenuManager::Buttons::Labels::g_quitButtonLabel );
	quitButton.getButtonText( ).setCharacterSize( Settings::MenuManager::Buttons::Labels::g_mainMenuButtonCharSize );
	quitButton.setPosition( Settings::MenuManager::Buttons::Vectors::g_quitButtonOnScreenPos );
	quitButton.updateTextPosition( );

	//Disables the third button so it is not rendered on screen
	m_menuButtons[2].setIsActive( false );

	calculateButtonBounds( );

	m_currentMenuState = menuState::gameOverMenu;

}

void MenuManager::update( float deltaTime, sf::RenderWindow& window )
{
	for ( int i = 0; i < m_numButtons; ++i )
	{
		MenuButton& currentButton = m_menuButtons[i];
		if ( currentButton.getIsActive( ) )
		{
			currentButton.update( deltaTime, window );
		}
	}
	checkIfButtonsClicked( deltaTime );
	if ( m_swapLayout )
	{
		swapMenuLayout( deltaTime );
	}
}

void MenuManager::updateScoreTexts( ScoreManager& scoreManager )
{
	//Sets up the top high score text
	m_topHighScore.setString( "#1: " + std::to_string( scoreManager.getTopScore( ) ) );
	m_topHighScore.updateTextOrigin( );
	m_topHighScore.setPosition( sf::Vector2f( 640.0f, 200.0f ) );

	//Sets up the second top score text
	m_secondHighScore.setString( "#2: " + std::to_string( scoreManager.getSecondTopScore( ) ) );
	m_secondHighScore.updateTextOrigin( );
	m_secondHighScore.setPosition( sf::Vector2f( 640.0f, 230.0f ) );

	//Sets up the third top score text
	m_thirdHighScore.setString( "#3: " + std::to_string( scoreManager.getThirdTopScore( ) ) );
	m_thirdHighScore.updateTextOrigin( );
	m_thirdHighScore.setPosition( sf::Vector2f( 640.0f, 260.0f ) );

}

void MenuManager::renderButtons( sf::RenderWindow& window )
{
	for ( int i = 0; i < m_numButtons; ++i )
	{
		MenuButton& currentButton = m_menuButtons[i];
		if ( currentButton.getIsActive( ) )
		{
			window.draw( currentButton );
			currentButton.renderButtonText( window );
		}
	}
}

void MenuManager::renderMainMenu( sf::RenderWindow& window )
{
	window.draw( m_titleText );
	renderHighScores( window );
	renderButtons( window );
}

void MenuManager::renderOptionsMenu( sf::RenderWindow& window )
{
	window.draw( m_titleText );
	renderButtons( window );
}

void MenuManager::renderGameOverMenu( sf::RenderWindow& window )
{
	window.draw( m_titleText );
	window.draw( m_finalScoreText );
	renderButtons( window );
}

void MenuManager::renderHighScores( sf::RenderWindow& window )
{
	window.draw( m_topHighScore );
	window.draw( m_secondHighScore );
	window.draw( m_thirdHighScore );
}

void MenuManager::renderMenu( sf::RenderWindow& window )
{
	switch ( m_currentMenuState )
	{
	case MenuManager::menuState::mainMenu:
	{
		//Render the main menu here
		renderMainMenu( window );
	}
		break;

	case MenuManager::menuState::optionsMenu:
	{
		//Render the options menu here
		renderOptionsMenu( window );
	}
		break;
	case MenuManager::menuState::gameOverMenu:
	{
		//Renders the game over screen
		renderGameOverMenu( window );
	}
		break;
	default:
	{
		//Default code here
	}
		break;
	}
}

void MenuManager::swapMenuLayout( float deltaTime )
{
	switch ( m_currentMenuState )
	{
	case MenuManager::menuState::mainMenu:
	{
		switch ( m_targetMenuState )
		{
		case MenuManager::menuState::mainMenu:
		{
			std::cout << "Invalid menu swap! Current menu state and target state were the same!";
		}
			break;
		case MenuManager::menuState::optionsMenu:
		{
			if ( !m_transitioningIn )
			{
				transitionOutOfMain( deltaTime );
			}
			else
			{
				transitionIntoOptions( deltaTime );
			}
		}
			break;

		default:
			//Default outcome
			break;
		}
	}
		break;
	case MenuManager::menuState::optionsMenu:
	{
		switch ( m_targetMenuState )
		{
		case menuState::mainMenu:
		{
			if ( !m_transitioningIn )
			{
				transitionOutOfOptions( deltaTime );
			}
			else
			{
				transitionIntoMain( deltaTime );
			}

		}
		break;
		}
	}
		break;
	case MenuManager::menuState::gameOverMenu:
	{
		switch ( m_targetMenuState )
		{
		case MenuManager::menuState::mainMenu:
			if ( !m_transitioningIn )
			{
				transitionOutOfGameOver( deltaTime );
			}
			else
			{
				transitionIntoMain( deltaTime );
			}
			break;
		case MenuManager::menuState::optionsMenu:
		{
			std::cout << "Invalid menu transition!";
		}
			break;
		case MenuManager::menuState::gameOverMenu:
		{
			std::cout << "Invalid menu transition!";
		}
			break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}

void MenuManager::transitionIntoMain( float deltaTime )
{
	MenuButton& playButton = m_menuButtons[0];
	MenuButton& optionsButton = m_menuButtons[1];
	MenuButton& quitButton = m_menuButtons[2];

	m_titleText.lerp( m_titleText.getPosition( ), m_titleOnScreenPos, m_titleTransitionSpeed * deltaTime );

	switch ( m_buttonLerpIndex )
	{
	case( 0 ):
	{
		playButton.Lerpv( playButton.getPosition( ), m_playButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		playButton.updateTextPosition( );
		if ( abs( playButton.getPosition( ).x - m_playButtonOnScreenPos.x ) < 1 )
		{
			playButton.setPosition( m_playButtonOnScreenPos );
			playButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 1 ):
	{
		optionsButton.Lerpv( optionsButton.getPosition( ), m_optionsButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		optionsButton.updateTextPosition( );
		if ( abs( optionsButton.getPosition( ).x - m_optionsButtonOnScreenPos.x ) < 1 )
		{
			optionsButton.setPosition( m_optionsButtonOnScreenPos );
			optionsButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 2 ):
	{
		quitButton.Lerpv( quitButton.getPosition( ), m_quitButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		quitButton.updateTextPosition( );
		if ( abs( quitButton.getPosition( ).x - m_quitButtonOnScreenPos.x ) < 1 )
		{
			quitButton.setPosition( m_quitButtonOnScreenPos );
			quitButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 3 ):
	{
		m_buttonLerpIndex = 0;
		m_transitioningIn = false;
		m_swapLayout = false;
		m_currentMenuState = menuState::mainMenu;
		calculateButtonBounds( );
	}
	break;

	default:
		//Default outcome
		break;
	}
}

void MenuManager::transitionOutOfMain( float deltaTime )
{
	MenuButton& playButton = m_menuButtons[0];
	MenuButton& optionsButton = m_menuButtons[1];
	MenuButton& quitButton = m_menuButtons[2];

	m_titleText.lerp( m_titleText.getPosition( ), m_titleOffScreenPos, m_titleTransitionSpeed * deltaTime );

	switch ( m_buttonLerpIndex )
	{
	case( 0 ):
	{
		playButton.Lerpv( playButton.getPosition( ), m_playButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		playButton.updateTextPosition( );
		if ( abs( playButton.getPosition( ).x - m_playButtonOffScreenPos.x ) < 1 )
		{
			playButton.setPosition( m_playButtonOffScreenPos );
			playButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 1 ):
	{
		optionsButton.Lerpv( optionsButton.getPosition( ), m_optionsButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		optionsButton.updateTextPosition( );
		if ( abs( optionsButton.getPosition( ).x - m_optionsButtonOffScreenPos.x ) < 1 )
		{
			optionsButton.setPosition( m_optionsButtonOffScreenPos );
			optionsButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 2 ):
	{
		quitButton.Lerpv( quitButton.getPosition( ), m_quitButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		quitButton.updateTextPosition( );
		if ( abs( quitButton.getPosition( ).x - m_quitButtonOffScreenPos.x ) < 1 )
		{
			quitButton.setPosition( m_quitButtonOffScreenPos );
			quitButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 3 ):
	{
		m_buttonLerpIndex = 0;
		m_transitioningIn = true;
		switch ( m_targetMenuState )
		{
		case MenuManager::menuState::mainMenu:
		{
			loadMainMenuLayout( );
		}
		break;

		case MenuManager::menuState::optionsMenu:
		{
			loadOptionsMenuLayout( );
		}
		break;

		default:
			break;
		}
	}
	break;

	default:
		//Default outcome
		break;
	}
}

void MenuManager::transitionOutOfOptions( float deltaTime )
{
	MenuButton& optionOneButton = m_menuButtons[0];
	MenuButton& optionTwoButton = m_menuButtons[1];
	MenuButton& backButton = m_menuButtons[2];

	m_titleText.lerp( m_titleText.getPosition( ), m_titleOffScreenPos, m_titleTransitionSpeed * deltaTime );

	switch ( m_buttonLerpIndex )
	{
	case( 0 ):
	{
		optionOneButton.Lerpv( optionOneButton.getPosition( ), m_playButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		optionOneButton.updateTextPosition( );
		if ( abs( optionOneButton.getPosition( ).x - m_playButtonOffScreenPos.x ) < 1 )
		{
			optionOneButton.setPosition( m_playButtonOffScreenPos );
			optionOneButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 1 ):
	{
		optionTwoButton.Lerpv( optionTwoButton.getPosition( ), m_optionsButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		optionTwoButton.updateTextPosition( );
		if ( abs( optionTwoButton.getPosition( ).x - m_optionsButtonOffScreenPos.x ) < 1 )
		{
			optionTwoButton.setPosition( m_optionsButtonOffScreenPos );
			optionTwoButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 2 ):
	{
		backButton.Lerpv( backButton.getPosition( ), m_quitButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		backButton.updateTextPosition( );
		if ( abs( backButton.getPosition( ).x - m_quitButtonOffScreenPos.x ) < 1 )
		{
			backButton.setPosition( m_quitButtonOffScreenPos );
			backButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 3 ):
	{
		m_buttonLerpIndex = 0;
		m_transitioningIn = true;
		switch ( m_targetMenuState )
		{
		case MenuManager::menuState::mainMenu:
		{
			loadMainMenuLayout( );
		}
		break;

		case MenuManager::menuState::optionsMenu:
		{
			loadOptionsMenuLayout( );
		}
		break;

		default:
			break;
		}
	}
	break;

	default:
		//Default outcome
		break;
	}
}

void MenuManager::transitionOutOfGameOver( float deltaTime )
{
	MenuButton& mainMenuButton = m_menuButtons[0];
	MenuButton& quitButton = m_menuButtons[1];

	m_titleText.lerp( m_titleText.getPosition( ), m_titleOffScreenPos, m_titleTransitionSpeed * deltaTime );

	m_finalScoreText.lerp( m_finalScoreText.getPosition( ), m_titleOffScreenPos, m_titleTransitionSpeed * deltaTime );

	switch ( m_buttonLerpIndex )
	{
	case( 0 ):
	{
		mainMenuButton.Lerpv( mainMenuButton.getPosition( ), m_optionsButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		mainMenuButton.updateTextPosition( );
		if ( abs( mainMenuButton.getPosition( ).x - m_optionsButtonOffScreenPos.x ) < 1 )
		{
			mainMenuButton.setPosition( m_optionsButtonOffScreenPos );
			mainMenuButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 1 ):
	{
		quitButton.Lerpv( quitButton.getPosition( ), m_quitButtonOffScreenPos, m_buttonTransitionSpeed * deltaTime );
		quitButton.updateTextPosition( );
		if ( abs( quitButton.getPosition( ).x - m_quitButtonOffScreenPos.x ) < 1 )
		{
			quitButton.setPosition( m_quitButtonOffScreenPos );
			quitButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 2 ):
	{
		m_buttonLerpIndex = 0;
		m_transitioningIn = true;
		loadMainMenuLayout( );
	}
	break;

	default:
		//Default outcome
		break;
	}
}

void MenuManager::transitionIntoOptions( float deltaTime )
{
	MenuButton& playButton = m_menuButtons[0];
	MenuButton& optionsButton = m_menuButtons[1];
	MenuButton& quitButton = m_menuButtons[2];

	m_titleText.lerp( m_titleText.getPosition( ), m_titleOnScreenPos, m_titleTransitionSpeed * deltaTime );

	switch ( m_buttonLerpIndex )
	{
	case( 0 ):
	{
		playButton.Lerpv( playButton.getPosition( ), m_playButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		playButton.updateTextPosition( );
		if ( abs( playButton.getPosition( ).x - m_playButtonOnScreenPos.x ) < 1 )
		{
			playButton.setPosition( m_playButtonOnScreenPos );
			playButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 1 ):
	{
		optionsButton.Lerpv( optionsButton.getPosition( ), m_optionsButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		optionsButton.updateTextPosition( );
		if ( abs( optionsButton.getPosition( ).x - m_optionsButtonOnScreenPos.x ) < 1 )
		{
			optionsButton.setPosition( m_optionsButtonOnScreenPos );
			optionsButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 2 ):
	{
		quitButton.Lerpv( quitButton.getPosition( ), m_quitButtonOnScreenPos, m_buttonTransitionSpeed * deltaTime );
		quitButton.updateTextPosition( );
		if ( abs( quitButton.getPosition( ).x - m_quitButtonOnScreenPos.x ) < 1 )
		{
			quitButton.setPosition( m_quitButtonOnScreenPos );
			quitButton.updateTextPosition( );
			++m_buttonLerpIndex;
		}
	}
	break;

	case( 3 ):
	{
		m_buttonLerpIndex = 0;
		m_transitioningIn = false;
		m_swapLayout = false;
		m_currentMenuState = menuState::optionsMenu;
		calculateButtonBounds( );
	}
	break;

	default:
		//Default outcome
		break;
	}
}

//Setters and Getters

//Returning to main

void MenuManager::setIsReturningToMain( bool isReturning )
{
	m_isReturningToMain = isReturning;
}

bool MenuManager::getIsReturningToMain( )
{
	return m_isReturningToMain;
}

//Toggle Mute

void MenuManager::setToggleMute( bool changeResolution )
{
	m_toggleMute = changeResolution;
}

bool MenuManager::getToggleMute( )
{
	return m_toggleMute;
}

//Toggle Fullscreen

void MenuManager::setToggleFullscreen( bool toggleFullscreen )
{
	m_toggleFullscreen = toggleFullscreen;
}

bool MenuManager::getToggleFullscreen( )
{
	return m_toggleFullscreen;
}

//Was Play Clicked

void MenuManager::setWasPlayClicked( bool wasClicked )
{
	m_wasPlayClicked = wasClicked;
}

bool MenuManager::getWasPlayClicked( )
{
	return m_wasPlayClicked;
}

//Was Quit Clicked

bool MenuManager::getWasQuitClicked( )
{
	return m_wasQuitClicked;
}

MenuManager::~MenuManager( )
{

}
