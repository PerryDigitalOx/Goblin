#ifndef CGOBAvi_H
#define CGOBAvi_H

#include "avisurface.h"

/*
StaticPic is a simple widget similar to CGOBStaticText but
handles an image instead of text.

The image is in the base class, so this class simply handles
drawing it.  This class is almost not needed since animation
can be handled with AnimObj and the image is in the base class.

This class could be removed but allows for customization in the future.
*/

class CGOBAvi: public CGOBWidget
{
private:
	CAviSurface* pAVI;
	BOOL IsPlaying;

public:
	CGOBAvi();
	~CGOBAvi();
	GOBLIN_RETVAL LoadFile(char * filename, INT16 Width, INT16 Height, BOOL Looped);
	GOBLIN_RETVAL Start();
	GOBLIN_RETVAL Stop();
	GOBLIN_RETVAL SetColorKey(DWORD NewColorKey);
	// Draws the current frame
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
};

#endif
