#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "EnemyManager.h"
#include "GameStateEnum.h"
#include "GameText.h"
#include "MenuManager.h"
#include "MusicManager.h"
#include "PlayerObject.h"
#include "ProjectileManager.h"
#include "ScoreManager.h"
#include "Shield.h"
#include "UIManager.h"

class Game
{
private:

	//Booleans

	//A boolean that determines wether or not the game window is fullscreen
	bool m_isFullScreen;

	//Clock used to calculate deltaTime
	sf::Clock m_deltaClock;

	//Enums

	//The state that the game is currently in
	gameStates m_currentGameState;

	//Floats

	//The amount of time passed since the last frame 
	float m_deltaTime;

	//Images

	//The icon displayed in the game's window bar
	sf::Image m_windowIcon;

	//Integers

	//The number of projectiles on the player
	int m_numPlayerProjectiles;

	//Objects

	//The enemy manager game object
	EnemyManager * m_enemyManager;

	//Handles all of the music within the game
	MusicManager m_musicManager;

	//The controllable player character
	PlayerObject * m_playerShip;

	//The object that handles all score data in the game
	ScoreManager m_scoreManager;

	//The shield that the player can hide behind to acoid projectiles
	Shield m_shield;

	//Manages all of the UI elements in the gameplay
	UIManager m_uiManager;

	//The game's background
	GameObject m_atlantisBackground;

	GameObject m_mainMenuBackground;

	//Render window

	//The render window that the game will play in
	sf::RenderWindow m_renderWindow;

	//Buttons

	//Handles all of the menu systems within the game
	MenuManager m_menuManager;

	//Private Methods

	//Calculates a deltatime value that can then be passed into all the update functions
	void calculateDeltaTime( );

	//Toggles the music between muted and unmuted
	void toggleMute( );

	//Loads in the background images for the game and menu, assigning them to their respective GameObjects
	void loadBackgroundImages( );

	//Resets all of the necessary elements of the game such as the player, enemies, and score
	void resetGame( );

	//Executes the update and render functions of everything in the main menu
	void runMainMenu( );

	//Executes the update and render functions of everything in the game
	void runGame( );

	//Executes the update and render functions of everything in the death screen
	void runDeathScreen( );

	//Renders all elements of the main menu
	void renderMainMenu( );

	//Renders all elements of gameplay
	void renderGame( );

	//Renders all elements of the death screen
	void renderDeathScreen( );

	//Toggles the game between fullscreen and windowed mode
	void toggleFullScreen( );

	//Runs every frame
	void update( );

	//Checks to see if any of the collision conditions have been met
	void checkForCollisions( );

public:

	//Constructor

	Game( );

	//Destructor

	~Game( );

	//Methods

	//Runs the main loop of the game, which will change depending on the current game state
	void runMainLoop( );
};

#endif // !GAME_H
