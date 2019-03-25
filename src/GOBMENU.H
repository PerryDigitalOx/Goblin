#ifndef CGOBMENU_H
#define CGOBMENU_H

#include "GOBWidgetParent.h"

class CDXSurface;

/*
Menu is a widget that can have a background image and children.
This is probably the second widely used widget beside the button.
If no background image is specified the background is transparent.
To make mouse hits to go through menu set flag WF_TRANSPARENT.
*/

class CGOBMenu : public CGOBWidgetParent
{
public:
	// Handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnProcess (GOBLIN_PARAM param);

	// Bring widget to front drawing and processing list.
	void BringToFront(void);
};


#endif