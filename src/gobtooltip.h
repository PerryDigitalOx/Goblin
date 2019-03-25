#ifndef CGOBTOOLTIP_H
#define CGOBTOOLTIP_H

#include "GOBWidget.h"

/*
Tooltip is a widget that simply draws a rectangle box and associated text.
Advanced tooltip widgets can easily be made to word wrap the text and
make cool looking bubble tooltips if wanted.

The tooltip widget text only points to the active widgets text.  This way
this widget only handles drawing and doesn't have to copy the text from each
widget for displaying.
*/

class CGOBToolTip: public CGOBWidget
{
public:
	//Does nothing
	CGOBToolTip();
	//Sets tooltip text pointer to NULL
	~CGOBToolTip();

	// Draws the rectangle and text.
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);

	// Sets the text pointer to the active widgets text.
	void SetTextPtr( const char * text)		{ m_pToolTipText = (char *)text; }

private:
    INT16        m_iYOffset;         // unused (reserved for offsetting from mouse pos or something)
    INT16        m_iXOffset;         // unused
    UINT32       m_FillColor;        // RGB color of fill
    UINT32       m_BorderColor;      // RGB color of border
    INT8         m_iBorder;          // width in pixels of border
};

#endif