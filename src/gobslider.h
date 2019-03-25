#ifndef CGOBSLIDER_H
#define CGOBSLIDER_H

#include "GOBWidget.h"

/*
Slider is a flexible widget handling both vertical or horizontal or both at the same time.
This widget automatically handles the thumb slider inside the rectangle slider box.
Setting the thumb size to be smaller in any dimension than the surrounding rectangle
allows the thumb to move in that direction.  A step rate in both dimensions can be any value.

*/

class CGOBSlider: public CGOBWidget
{
public:
	// Set default values
	CGOBSlider();

	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);

	// Moves slider and thumb along with it.
	void Move( INT32 newx, INT32 newy );
	// Sets the range of values of slider.
	void SetRange( INT32 nMin, INT32 nMax );
	
	// Set offset
	void SetOffset( INT32 x, INT32 y)			{ m_xOffset = x; m_yOffset = y; }

	// Get X and Y value
	INT32 GetXPos()								{ return(m_nXPos); }
	INT32 GetYPos()								{ return(m_nYPos); }

	// Set the thumb dimensions.
	void SetThumbSize( INT16 w, INT16 h)		{ m_ThumbWidth = w; m_ThumbHeight = h; }
	// Set the position of the thumb.
	void SetThumbPos( INT32 nx, INT32 ny);

protected:
	// Dimensions of the thumb.
	RECT m_rcThumb;

private:
	// Thumb width and height
	INT16		m_ThumbWidth, m_ThumbHeight;
	// Thumb x,y offset
	INT32		m_xOffset, m_yOffset;
	// Sliders min and maximum values.
	INT32		m_nMin, m_nMax;
	// Sliders x and y position.  This is thumb position value.
	INT32		m_nXPos, m_nYPos;
};

#endif
