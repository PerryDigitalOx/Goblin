#ifndef GOBSTATICTEXT_H
#define GOBSTATICTEXT_H

#include "GOBWidget.h"

/*
Static text widget is useful for adding a widget that only displays a text string.
No other actions are handled with this simple widget.
*/

class CGOBStaticText: public CGOBWidget
{
public:
	// Sets text to be displayed.
	void SetText( const char * newtext );

	// Draws the text associated with widget.
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
};

#endif