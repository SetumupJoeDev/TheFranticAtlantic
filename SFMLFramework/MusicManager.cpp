
#include "MusicManager.h"

#include <iostream>

//Constructor

MusicManager::MusicManager( )
	: m_isMuted ( false )
{

}

//Methods

void MusicManager::changeTrack( gameStates newGameState, bool playImmediately )
{
	//Sets the sound of the music player depending on the new game state
	switch ( newGameState )
	{
	case gameStates::mainMenu:
	{
		m_musicPlayer.setSound( m_mainMenuTheme );
	}
		break;
	case gameStates::inGame:
	{
		m_musicPlayer.setSound( m_gameTheme );
	}
		break;
	case gameStates::deathScreen:
	{
		m_musicPlayer.setSound( m_deathTheme );
	}
		break;
	default:
	{
		std::cout << "No track was found for the current game state.";
	}
		break;
	}
	if ( playImmediately )
	{
		m_musicPlayer.play( );
	}
}

void MusicManager::toggleMuteMusic( )
{
	//If the music isn't currently muted, its volume is set to 0
	if ( !m_isMuted )
	{
		m_musicPlayer.setVolume( 0 );
		m_isMuted = true;
	}
	//If it is muted, the volume is set to 100
	else
	{
		m_musicPlayer.setVolume( 100 );
		m_isMuted = false;
	}
}

MusicManager::~MusicManager( )
{

}
