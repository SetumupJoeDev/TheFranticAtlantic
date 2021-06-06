#include "ScoreManager.h"

//Constructor

ScoreManager::ScoreManager( )
	: m_currentScore( 0 )
{

	readHighScores( );

}

//Methods

void ScoreManager::swapValues( int *valueOne, int *valueTwo )
{
	//Creates a temporary int and assigns it the value of valueOne so that it is not lost
	int temp = *valueOne;

	//Swaps the two passed values around
	*valueOne = *valueTwo;
	*valueTwo = temp;
}

void ScoreManager::checkForNewHighScore( )
{
	//If the player's current score is higher than the third place score, then it is overwritten with the new score and the scores are sorted
	if ( m_currentScore > m_highScoreArray[2] )
	{
		m_highScoreArray[2] = m_currentScore;
		sortHighScores( );
	}
	//The value of currentScore is reset, so that the player's score does not persist
	m_currentScore = 0;
}

void ScoreManager::readHighScores( )
{
	m_highScoreFile.open( Settings::Game::g_highScoreFile );
	if ( m_highScoreFile.is_open( ) )
	{
		std::string scoreStrings[m_numHighScores];

		for ( int i = 0; i < m_numHighScores; ++i )
		{
			//Saves the string version of the file contents to a local array, before converting it to an int and saving it to the correct array index
			std::getline( m_highScoreFile, scoreStrings[i] );
			m_highScoreArray[i] = std::stoi( scoreStrings[i] );
		}
		m_highScoreFile.close( );
	}
	else
	{
		std::cout << "Failed to open file: " << Settings::Game::g_highScoreFile << "\n";
	}

	sortHighScores( );

}

void ScoreManager::sortHighScores( )
{
	//Creates a local boolean that will keep track of wether or not any values have been swapped
	bool anyValuesSwapped;
	//Loops through the values stored in the high score array, checking to see if each is smaller than the next
	for ( int i = 0; i < m_numHighScores - 1; ++i )
	{
		anyValuesSwapped = false;
		//Uses m_numHighScores - i - 1 to prevent j from going outside the bounds of the array
		for ( int j = 0; j < m_numHighScores - i - 1; ++j )
		{
			//If one array element is smaller than the next element, the two values are swapped around using the swapValues method and anyValuesSwapped is set to true
			if ( m_highScoreArray[j] < m_highScoreArray[j + 1] )
			{
				swapValues( &m_highScoreArray[j], &m_highScoreArray[j + 1] );
				anyValuesSwapped = true;
			}
		}
		//If no values have been swapped, then the items in the array are already sorted and the loop is broken
		if ( !anyValuesSwapped )
		{
			break;
		}
	}
	writeHighScore( );
}

void ScoreManager::writeHighScore( )
{
	m_highScoreFile.open( Settings::Game::g_highScoreFile );

	//Opens the high score file and loops through the high scores, writing each to the file before closing it
	if ( m_highScoreFile.is_open( ) )
	{
		for ( int i = 0; i < m_numHighScores; ++i )
		{
			m_highScoreFile << m_highScoreArray[i] << "\n";
		}
		m_highScoreFile.close( );
	}
	else
	{
		std::cout << "Failed to write to high score file!\n";
	}
}

//Getters and Setters

int ScoreManager::getTopScore( )
{
	return m_highScoreArray[0];
}

int ScoreManager::getSecondTopScore( )
{
	return m_highScoreArray[1];
}

int ScoreManager::getThirdTopScore( )
{
	return m_highScoreArray[2];
}

//Setters and Getters

//Sets the value of the player's current score to m_currentScore + the value passed in through the parameters
void ScoreManager::setCurrentScore( int newScore, UIManager& uiManager )
{
	m_currentScore = newScore;
	uiManager.updateScoreText( m_currentScore );
}

//Returns the current value of the player's score
int ScoreManager::getCurrentScore( )
{
	return m_currentScore;
}

//Destructor

ScoreManager::~ScoreManager( )
{

}
