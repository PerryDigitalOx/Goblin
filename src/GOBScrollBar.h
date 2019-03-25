#ifndef GOBSCROLLBAR_H
#define GOBSCROLLBAR_H

#include "GOBWidgetParent.h"
#include "GOBButton.h"

class CGOBScrollBar : public CGOBWidgetParent
{
public:
	CGOBScrollBar();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);

	// Moves slider and thumb along with it.
	void Move( INT32 newx, INT32 newy );
	// Sets the range of values of slider.
	void SetRange( INT32 nMin, INT32 nMax );
	
	// Check if slider is vertical or horizontal
	BOOL IsVertical()							{ return m_IsVertical; }
	BOOL IsHorizontal()							{ return !m_IsVertical; }

	// Set vertical flag for vertical or horizontal
	void SetVertical()							{ m_IsVertical = TRUE; }
	void SetHorizontal()						{ m_IsVertical = FALSE; }

	// Set offset
	void SetOffset( INT32 x, INT32 y)			{ m_xOffset = x; m_yOffset = y; }

	// Get X and Y value
	INT32 GetXPos()								{ return(m_nXPos); }
	INT32 GetYPos()								{ return(m_nYPos); }

	// Set the thumb dimensions.
	void SetThumbSize( INT16 w, INT16 h)		{ m_ThumbWidth = w; m_ThumbHeight = h; }
	// Set the position of the thumb.
	void SetThumbPos( INT32 nx, INT32 ny);

	void SetFirstButton(CGOBButton *pFirstButton);	
	void SetSecondButton(CGOBButton *pSecondButton);

protected:
	// Dimensions of the thumb.
	RECT m_rcThumb;

private:
	CGOBButton *m_pFirstButton;
	CGOBButton *m_pSecondButton;

	// Thumb width and height
	INT16		m_ThumbWidth, m_ThumbHeight;
	// Thumb x,y offset
	INT32		m_xOffset, m_yOffset;
	// Sliders min and maximum values.
	INT32		m_nMin, m_nMax;
	// Sliders x and y position.  This is thumb position value.
	INT32		m_nXPos, m_nYPos;
	// Flag specifies if slider is vertical or horizontal in nature.
	BOOL		m_IsVertical;
	float		m_stepx, m_stepy;
};

#endif
