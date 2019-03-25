#ifndef GOBMSGBOX_H
#define GOBMSGBOX_H

#include "GOBPanel.h"

/*
MsgBox is a modal window that simply displays a text message and allows
a couple buttons like Ok and Cancel.  Can be expanded to be a powerful
and fully functional message box.  Great for error messages.
*/

class CGOBMsgBox : public CGOBPanel  
{
public:
	// Set model flag by default
	CGOBMsgBox();

	// Draws panel background and buttons and text
	GOBLIN_RETVAL OnDraw(GOBLIN_PARAM param);

	// Set text to be display in middle of box
	void	SetText(char *newtext);
};

#endif
