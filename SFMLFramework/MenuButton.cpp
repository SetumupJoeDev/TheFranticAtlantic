
#include "MenuButton.h"

#include<iostream>

#include <SFML/Window/Mouse.hpp>

#include "Settings.h"

//Constructor

MenuButton::MenuButton( )
	: m_topBound  ( 0 ),
	m_bottomBound ( 0 ),
	m_leftBound	  ( 0 ),
	m_rightBound  ( 0 )
{
	if ( !m_objectTexture.loadFromFile( Settings::MenuManager::Buttons::g_buttonTexture ) )
	{
		std::cout << "Menu button texture not found! was the texture name spelt wrong?\n\n";
	}

	setTexture( m_objectTexture, true );

	//Sets the origin of the button to the center of the sprite
	setOrigin( getLocalBounds( ).width * 0.5f, getLocalBounds( ).height * 0.5f );

	m_buttonClick.setSound( Settings::MenuManager::Buttons::g_buttonClickSound );

	calculateBounds( );

}

//Methods

void MenuButton::calculateBounds( )
{
	//Saves the height halved for use in calculations
	float heightHalved = getGlobalBounds().height * 0.5f;

	//Saves the width halved for use in calculations
	float widthHalved = getGlobalBounds().width * 0.5f;

	//Saves the X position for use in calculations
	float objectPosX = getPosition( ).x;

	//Saves the Y position for use in calculations
	float objectPosY = getPosition( ).y;

	//Calculates the top boundary of the button for use in determining whether the button is being moused over
	m_topBound = objectPosY - heightHalved;

	//Calculates the bottom boundary
	m_bottomBound = objectPosY + heightHalved;

	//Calculates the left boundary
	m_leftBound = objectPosX - widthHalved;

	//Calculates the right boundary
	m_rightBound = objectPosX + widthHalved;
}

void MenuButton::checkMouseInput( sf::RenderWindow& window )
{
	//Saves the mouse's X position to for use in later checks
	int mousePosX = sf::Mouse().getPosition( window ).x;

	//Saves the mouse's Y position to for use in later checks
	int mousePosY = sf::Mouse( ).getPosition( window ).y;

	if ( mousePosX > m_leftBound && mousePosX < m_rightBound && mousePosY > m_topBound && mousePosY < m_bottomBound )
	{
		m_mousedOver = true;
	}
	else if( m_mousedOver || m_wasClicked )
	{
		m_mousedOver = false;
		m_wasClicked = false;
	}
	if ( m_mousedOver && !m_wasClicked )
	{
		if ( sf::Mouse( ).isButtonPressed( sf::Mouse( ).Left ) )
		{
			m_buttonClick.play( );
			m_wasClicked = true;
		}
	}
}

void MenuButton::renderButtonText( sf::RenderWindow& renderWindow )
{
	renderWindow.draw( m_buttonText );
}

void MenuButton::update( float deltaTime, sf::RenderWindow& renderWindow )
{
	checkMouseInput( renderWindow );
}

void MenuButton::updateTextPosition( )
{
	m_buttonText.updateTextOrigin( );
	m_buttonText.setPosition( getPosition( ) );
}

//Setters and Getters

//Is Active

void MenuButton::setIsActive( bool isActive )
{
	m_isActive = isActive;
}

bool MenuButton::getIsActive( )
{
	return m_isActive;
}

//Moused Over

bool MenuButton::getMousedOver( )
{
	return m_mousedOver;
}

//Was Clicked

void MenuButton::setWasClicked( bool wasClicked )
{
	m_wasClicked = wasClicked;
}

bool MenuButton::getWasClicked( )
{
	return m_wasClicked;
}

//Button Text String

GameText& MenuButton::getButtonText( )
{
	return m_buttonText;
}

void MenuButton::setButtonTextString( const std::string buttonText )
{
	m_buttonText.setString( buttonText );
	updateTextPosition( );
}

//Destructor

MenuButton::~MenuButton( )
{

}