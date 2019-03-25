#ifndef CGOBCHECKBOX_H
#define CGOBCHECKBOX_H

#include "GOBWidget.h"

/*
CheckBox is similar to button.

This widget draws a default check box image created with inline
array of values.  For speed this should be superclassed with a
class that uses a sprite image.
*/

class CGOBCheckBox: public CGOBWidget
{
public:
	// Set default values.
	CGOBCheckBox();

	// Handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostMouse (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotMouse (GOBLIN_PARAM param);

	// Set state of button.
	void SetState(INT16 state);
	INT16 GetState()							{ return m_State; }

	// Sets the check box text beside box.
	void SetText( const char * newtext);

private:
	INT16	m_State;				// state of checkbox. STATE_CHECKED or STATE_UNCHECKED.

	BOOL	m_IsHover;				// Flag states mouse over status.
};

#endif