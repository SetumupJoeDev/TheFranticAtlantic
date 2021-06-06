#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "SFML/Graphics.hpp"

#include "GameText.h"

class UIManager
{

private:

	//Text

	//The text that shows the player their current score
	GameText m_scoreText;

	//The text that shows the player how many lives they currently have
	GameText m_livesText;

public:

	//Constructor
	UIManager( );

	//Methods

	//Updates the text content of the Score Text
	void updateScoreText( int newScore );

	//Updates the text content of the Lives Text
	void updateLivesText( int newLives );

	//Renders all renderable parts of the game UI
	void render( sf::RenderWindow& renderWindow );

	//Setters and Getters

	//Lives Text
	GameText& getLivesText( );

	//Score Text
	GameText& getScoreText( );

	//Destructor
	~UIManager( );

};

#endif