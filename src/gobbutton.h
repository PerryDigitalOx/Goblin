#ifndef CGOBBUTTON_H
#define CGOBBUTTON_H

#include "GOBWidget.h"

/*
The Button is probably one of the widely used widget in Goblin.
Buttons have three states, normal, hilighted, and selected.
The disabled state is global to all widgets but could easily be
added for specific use with buttons very easily.

If text is set in the button, the text will be drawn on top of 
the button image or background.  The default order of the sprite
frames of a button is Normal, Hilight, Down.  Since these variables
are protected, they can be changed after the button is created.
This would be used if your images were already created with a different
order.
*/

class CGOBButton: public CGOBWidget
{
public:
	// Sets default values of members
	CGOBButton();

	// Virtual functions Overridden
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostMouse (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotMouse (GOBLIN_PARAM param);

	// sets the text associated with this button.
	// if there is no text the button will not have a text display.
	void SetText( char * newtext);		

protected:
	BOOL m_IsDown;				// Flag for mouse down state
	BOOL m_IsHover;				// Flag for mouse over state
	INT16 m_DownFrame;			// Sprite frame for down image
	INT16 m_HoverFrame;			// Sprite frame for mouse over image
	INT16 m_NormalFrame;		// Sprite frame for normal state image
};

#endif