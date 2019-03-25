#ifndef CGOBPANEL_H
#define CGOBPANEL_H

#include "GOBWidgetParent.h"

/*
Panel is a flat window that has no title bar and can be moved by click and dragging
on an empty part of the panel.  Panel can have children widgets.  
This is good widget for a toolbox style window.
*/

class CGOBPanel : public CGOBWidgetParent
{
public:
	// Set default values.
	CGOBPanel();

	// handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);

	// Bring panel to front of drawing and processing list.
	void BringToFront(void);

private:
	// flag specifies if panel is currently being dragged.
	BOOL m_IsDragging;
	
};


#endif