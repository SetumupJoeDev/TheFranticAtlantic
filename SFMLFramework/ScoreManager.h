#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <fstream>

#include "GameText.h"
#include "UIManager.h"

class ScoreManager
{
private:

	//Integers

	//The current score that the player has amassed
	int m_currentScore;
	
	//The number of high scores maintained at any time
	static const int m_numHighScores = 3;

	//The array of high score integers
	int m_highScoreArray[m_numHighScores];

	//High Score

	//The file that contains the high scores
	std::fstream m_highScoreFile;

	//Private methods

	//Swaps two values around, used for sorting values
	void swapValues( int *valueOne, int *valueTwo );

public:

	//Constructor

	ScoreManager( );

	//Methods

	//Checks to see if the player's current score is higher than the lowest current high score
	void checkForNewHighScore( );

	//Reads the high scores from the text file
	void readHighScores( );

	//Sorts the high scores, ordering them from highest to lowest
	void sortHighScores( );

	//Writes the high scores to the text file
	void writeHighScore( );

	//Setters and Getters

	//Top High Score

	int getTopScore( );

	//Second Top Score

	int getSecondTopScore( );

	//Third Top Score

	int getThirdTopScore( );

	//Current Score

	void setCurrentScore( int newScore, UIManager& uiManager );

	int getCurrentScore( );

	//Destructor

	~ScoreManager( );
};

#endif // !SCOREMANAGER_H

