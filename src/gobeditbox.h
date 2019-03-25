#ifndef CGOBEDITBOX_H
#define CGOBEDITBOX_H

#include "GOBWidget.h"

/*
EditBox has a rectangle background which is can be transparent.  Accepts key strokes
that are set in the global input structure processed by the manager.  Currently
handles basic keystrokes.  Enter and tab loses mouse focus.  WF_KEEPFOCUS will 
keep focus when enter is hit.  This would be use for a chat edit box.
*/

class CGOBEditBox: public CGOBWidget
{
public:
	// Set default values
	CGOBEditBox();

	// Handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnChar (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostFocus (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotFocus (GOBLIN_PARAM param);

	// Sets the text to display in editbox
	void SetText( const char * newtext);

private:	
	AnimObj		m_CursorAnimObj;		// Animation object for flashing cursor.

	INT16		m_CharCount;			// Number of characters in string.

	BOOL		m_IsDown;				// Flag specifies if widget is selected.
	BOOL		m_IsCursorOn;			// Flag specifies if flashing cursor is on.
};

#endif