#ifndef CGOBFRAME_H
#define CGOBFRAME_H

#include "GOBWidgetParent.h"
#include "GOBButton.h"

/*
Frame is a window with a title bar.  The title bar is draggable and contains 
a minimize and close button.  Minimize will shrink the window to be only
the height of the title bar itself.  Close will deactivate the widget.
System messages are sent to the parent when minimize and close are selected.
*/

class CGOBFrame : public CGOBWidgetParent
{
public:
	// Set default values and add system buttons.
	CGOBFrame();
	
	// handlers
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnRBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnSystemMsg (GOBLIN_PARAM param);
	
	// Set the title bars text.
	void SetText( const char * newtext);
	
	// Brings widget to the front of the drawing and processing list.
	void BringToFront(void);
	
    // moves frame and all it's children
	void Move( INT32 newx, INT32 newy );
	
private:
	// Flag tells us if window is dragging.
	BOOL m_IsDragging;
	// Flag tells us if widget is in minimized state.
	BOOL m_IsMinimized;
	// Flag specifies if we have an exit button.
	BOOL m_ExitButton;
	
	CGOBButton *m_MinimizeButton;		// Minimize button
	CGOBButton *m_CloseButton;			// Close button
};


#endif