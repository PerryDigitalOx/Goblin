#ifndef GOBBUTTONMASKED_H
#define GOBBUTTONMASKED_H

#include "GOBWidget.h"

class CGOBButtonMasked : public CGOBWidget  
{
public:
	// Sets default values of members
	CGOBButtonMasked();

	// Virtual functions Overridden
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostMouse (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotMouse (GOBLIN_PARAM param);

protected:
	BOOL m_IsDown;				// Flag for mouse down state
	BOOL m_IsHover;				// Flag for mouse over state
	UINT16 m_DownFrame;			// Sprite frame for down image
	UINT16 m_HoverFrame;		// Sprite frame for mouse over image
	UINT16 m_NormalFrame;		// Sprite frame for normal state image};
	UINT16 m_MaskFrame;

private:
	BOOL CheckMaskForHit(void);
};

#endif
