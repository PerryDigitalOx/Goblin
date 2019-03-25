#ifndef CGOBPOPMENU_H
#define CGOBPOPMENU_H

#include "GOBWidgetParent.h"

/*
PopMenu is a popup widget that contains children widgets.  PopMenu automatically
adjusts itself to be big enough to hold all the children.  This allows for
any shaped widgets mixed together without a problem.

Usually the children will be CGOBButton with the WF_TRANSPARENTBG flag set.

Popups are handled in a special way by the manager much like the tooltip widget.
GM.ActivatePopup() can be used to activate a popup widget which will be modal
until an type of action occurs.  The popup then removes itself.
*/

class CGOBPopMenu : public CGOBWidgetParent
{
public:

	// Draws background big enough for all widgets to fit, then draws all children.
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);

	// Moves itself and all children.
	void Move(INT32 newx, INT32 newy);
};

#endif