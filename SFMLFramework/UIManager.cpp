
#include "UIManager.h"

#include "Settings.h"

//Constructor

UIManager::UIManager( )
{

}

//Methods

void UIManager::updateLivesText( int newLives )
{
	//Updates the content of the text's string with the new value passed in by newLives
	m_livesText.setString( "Lives: " + std::to_string( newLives ) );
	//Updates the text's origin and position to ensure it is displayed correctly
	m_livesText.updateTextOrigin( );
	m_livesText.setPosition( Settings::UIManager::g_livesCounterPosition );
}

void UIManager::updateScoreText( int newScore )
{
	//Updates the content of the text's string with the new value passed in by newScore
	m_scoreText.setString( "Score: " + std::to_string( newScore ) );
	//Updates the text's origin and position to ensure it is displayed correctly
	m_scoreText.updateTextOrigin( );
	m_scoreText.setPosition( Settings::UIManager::g_scoreCounterPosition );
}

void UIManager::render( sf::RenderWindow& renderWindow )
{
	//Renders the text on screen
	renderWindow.draw( m_livesText );
	renderWindow.draw( m_scoreText );
}

//Setters and Getters

GameText& UIManager::getLivesText( )
{
	return m_livesText;
}

GameText& UIManager::getScoreText( )
{
	return m_scoreText;
}


//Destructor
UIManager::~UIManager( )
{

}