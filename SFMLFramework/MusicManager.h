#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <string.h>

#include "GameSound.h"

#include "GameStateEnum.h"
#include "Settings.h"

class MusicManager
{

private:

	//Booleans

	//Determines wether or not the music is currently muted
	bool m_isMuted;

	//Music Player

	//The sound used to play the music in the game
	GameSound m_musicPlayer;

	//Music Tracks

	//The theme for the game's main menu
	const std::string m_mainMenuTheme = Settings::MusicManager::g_mainMenuMusic;

	//The theme for gameplay
	const std::string m_gameTheme = Settings::MusicManager::g_inGameMusic;

	//The theme for the game over screen
	const std::string m_deathTheme = Settings::MusicManager::g_deathScreenMusic;

public:

	//Constructor
	MusicManager( );

	//Methods

	//Changes the track currently being played by the music manager
	void changeTrack( gameStates newGameState, bool playImmediately );

	//Toggles the music between being muted and unmuted
	void toggleMuteMusic( );

	//Destructor
	~MusicManager( );

};

#endif