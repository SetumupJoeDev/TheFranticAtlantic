#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "MenuButton.h"

#include "ScoreManager.h"
#include "Settings.h"

class MenuManager
{

private:

	//Booleans

	//Determines whether or not toggle mute has been clicked
	bool m_toggleMute;

	//Determines whether or not the layout is currently being swapped
	bool m_swapLayout;

	//Determines whether or not the game is being toggled between fullscreen and windowed mode
	bool m_toggleFullscreen;

	//Determines whether or not the menu is transitioning in
	bool m_transitioningIn;

	//Determines whether play was clicked or not
	bool m_wasPlayClicked;

	//Determines whether quit was clicked or not
	bool m_wasQuitClicked;

	//Determines whether or not the menu is returning to main
	bool m_isReturningToMain;

	//Integers

	//The number of buttons in the array of buttons
	static const int m_numButtons = Settings::MenuManager::g_numberOfButtons;

	//The array index of the button currently being lerped
	int m_buttonLerpIndex;

	//Enums

	enum class menuState{ mainMenu, optionsMenu, gameOverMenu };

	//The state that the menu is currently in
	menuState m_currentMenuState;

	//The state that the menu should be changed to after the transition
	menuState m_targetMenuState;

	enum class buttonFunctions{ startGame, showOptions, quitGame, returnToMain };

	//The function of the button when it is clicked
	buttonFunctions m_clickedButtonFunction;

	//Floats

	//The speed that the buttons are lerped at during a transition
	const float m_buttonTransitionSpeed = Settings::MenuManager::g_buttonTransitionSpeed;

	//The speed that the titles are lerped at during a transition
	const float m_titleTransitionSpeed	= Settings::MenuManager::g_titleTransitionSpeed;
	
	//Menu Buttons

	//The array of menu buttons
	MenuButton m_menuButtons[m_numButtons];

	//Text

	//The text used to display the title of the current menu
	GameText m_titleText;

	//The text used to siplay the player's final score on a game over
	GameText m_finalScoreText;

	//The top high score text
	GameText m_topHighScore;

	//The second highest high score text
	GameText m_secondHighScore;

	//The third highest high score
	GameText m_thirdHighScore;

	//Vector2s

	//The position of the title when it is on screen
	const sf::Vector2f m_titleOffScreenPos			= Settings::MenuManager::Titles::Vectors::g_titleOffScreenPos;

	//The position that the title moves to when it lerps offscreen
	const sf::Vector2f m_titleOnScreenPos			= Settings::MenuManager::Titles::Vectors::g_titleOnScreenPos;

	//The position of the play button when it is on screen
	const sf::Vector2f m_playButtonOffScreenPos		= Settings::MenuManager::Buttons::Vectors::g_playButtonOffScreenPos;

	//The position the play button lerps to when it lerps offscreen
	const sf::Vector2f m_playButtonOnScreenPos		= Settings::MenuManager::Buttons::Vectors::g_playButtonOnScreenPos;
	 
	//The position of the options button when it is on screen
	const sf::Vector2f m_optionsButtonOffScreenPos	= Settings::MenuManager::Buttons::Vectors::g_optionsButtonOffScreenPos;

	//The position the options button moves to when it lerps offscreen
	const sf::Vector2f m_optionsButtonOnScreenPos	= Settings::MenuManager::Buttons::Vectors::g_optionsButtonOnScreenPos;
	

	//The position of the quit button when it is on screen
	const sf::Vector2f m_quitButtonOffScreenPos		= Settings::MenuManager::Buttons::Vectors::g_quitButtonOffScreenPos;

	//The position the quit button moves to when it lerps offscreen
	const sf::Vector2f m_quitButtonOnScreenPos		= Settings::MenuManager::Buttons::Vectors::g_quitButtonOnScreenPos;

	//Private Methods

	//Recalculates the boundaries of the buttons after they are moved so they can be clicked
	void calculateButtonBounds( );

	//Checks to see if any of the active buttons have been clicked and executes their commands
	void checkIfButtonsClicked( float deltaTime );

	//Loads the options menu layout
	void loadOptionsMenuLayout( );

	//Renders all active buttons
	void renderButtons( sf::RenderWindow& window );

	//Renders the main menu elements
	void renderMainMenu( sf::RenderWindow& window );

	//Renders the options menu elements
	void renderOptionsMenu( sf::RenderWindow& window );

	//Renders the game over menu elements
	void renderGameOverMenu( sf::RenderWindow& window );

	//Renders the game's high score
	void renderHighScores( sf::RenderWindow& window );

	//Swaps between the current menu layout and the target menu layout
	void swapMenuLayout( float deltaTime );

	//Transitions into the main menu
	void transitionIntoMain( float deltaTime );

	//Transitions into the options menu
	void transitionIntoOptions( float deltaTime );

	//Transitions out of the main menu
	void transitionOutOfMain( float deltaTime );

	//Transitions out of the options screen
	void transitionOutOfOptions( float deltaTime );

	//Transitions out of the game over screen
	void transitionOutOfGameOver( float deltaTime );

public:

	//Constructor
	MenuManager( );

	//Methods

	//Loads the main menu's layout
	void loadMainMenuLayout( );

	//Loads the menu layout for the game over screen, taking the score manager as a parameter so it can display the player's final score
	void loadGameOverLayout( ScoreManager& scoreManager );

	//Renders the menu, depending on the current menu state
	void renderMenu( sf::RenderWindow& window );

	//Runs every frame
	void update( float deltaTime, sf::RenderWindow& window );

	void updateScoreTexts( ScoreManager& scoreManager );

	//Setters and Getters

	//Change Resolution

	void setToggleMute( bool changeResolution );

	bool getToggleMute( );

	//Toggle Fullscreen

	void setToggleFullscreen( bool toggleFullscreen );

	bool getToggleFullscreen( );

	//Is Returning To Main

	void setIsReturningToMain( bool isReturning );

	bool getIsReturningToMain( );

	//Was Play Clicked

	void setWasPlayClicked( bool wasClicked );

	bool getWasPlayClicked( );

	//Was Quit Clicked

	bool getWasQuitClicked( );

	//Destructor
	~MenuManager( );

};

#endif