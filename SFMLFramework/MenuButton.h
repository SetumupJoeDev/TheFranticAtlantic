#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "GameObject.h"

#include "GameSound.h"
#include "GameText.h"

class MenuButton : public GameObject
{

private:

	//Variables

	//Booleans

	//Determines whether or not this button is currently active and should be rendered
	bool m_isActive;

	//Determines wether or not the mouse is being hovered over the button
	bool m_mousedOver;

	//Determines wether or not the button has been clicked
	bool m_wasClicked;

	//Images

	//The image used to represent the button
	sf::Image m_buttonImage;

	//Integers

	//The left side of the button's bounding box
	int m_leftBound;

	//The right side of the button's bounding box
	int m_rightBound;

	//The top of the button's bounding box
	int m_topBound;

	//The bottom of the button's bounding box
	int m_bottomBound;

	//Sounds

	//The sound the button makes when it is clicked
	GameSound m_buttonClick;

	//Text

	//The text displayed on the button
	GameText m_buttonText;

	//Private Methods

	//Checks to see if the mouse is hovered over the button or clicked
	void checkMouseInput( sf::RenderWindow& window );

public:

	//Constructor

	MenuButton( );

	//Methods

	//Calculates the bounding box of the button
	void calculateBounds( );

	//Renders the text on the button
	void renderButtonText( sf::RenderWindow& renderWindow );

	//Runs every frame
	void update( float deltaTime, sf::RenderWindow& renderWindow );

	//Updates the positon of the text on the button
	void updateTextPosition( );

	//Setters and Getters

	//Is Active
	void setIsActive( bool isActive );

	bool getIsActive( );

	//Moused Over
	bool getMousedOver( );

	//Was Clicked
	void setWasClicked( bool wasClicked );

	bool getWasClicked( );

	//Button Text

	GameText& getButtonText( );

	//Button Text String
	void setButtonTextString( const std::string buttonText );

	//Destructor

	~MenuButton( );

};


#endif // !MENUBUTTON_H
