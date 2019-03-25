#ifndef CGOBSTATICPIC_H
#define CGOBSTATICPIC_H

/*
StaticPic is a simple widget similar to CGOBStaticText but 
handles an image instead of text.

The image is in the base class, so this class simply handles
drawing it.  This class is almost not needed since animation
can be handled with AnimObj and the image is in the base class.

This class could be removed but allows for customization in the future.
*/

class CGOBStaticPic: public CGOBWidget
{
public:
	// Draws the image
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
};

#endif