#ifndef CGOBRADIOBUTTON_H
#define CGOBRADIOBUTTON_H

#include "GOBWidget.h"

/*

RadioButton is similar to button but a bit more complex.

This widget has a group ID value.  All associated radio buttons
use the same group ID.  When a radio button is selected all other
radio buttons are scanned for the same group ID and are deselected.

This widget draws a default radio button image created with inline
array of values.  For speed this should be superclassed with a
class that uses a sprite image.

*IMPORTANT* Must compile with RTTI (Run Time Type Information) Enabled.

*/

class CGOBRadioButton: public CGOBWidget
{
public:
	// Sets default values
	CGOBRadioButton();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostMouse (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotMouse (GOBLIN_PARAM param);

	// Set text to be displayed beside button.  (SHOULD ADD JUSTIFICATION)
	void SetText( const char * newtext);
	
	// Set state of button.
	void SetState(INT16 state);
	INT16 GetState()				{ return m_State; }

	// Set group ID
	void SetGroupID(INT8 id)		{ m_GroupID = id; }
	// Get group ID
	INT8 GetGroupID(void)			{ return m_GroupID; }

private:
	INT8		m_GroupID;		// group identifier
	INT16		m_State;		// state of radio button. STATE_CHECKED or STATE_UNCHECKED.
	BOOL		m_IsHover;		// mouse over status
};

#endif