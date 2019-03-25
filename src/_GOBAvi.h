#ifndef CGOBAvi_H
#define CGOBAvi_H

#include "avisurface.h"

class CGOBAvi: public CGOBWidget
{
private:
	CAviSurface* pAVI;
	SIZE m_Size2; //When finished playing, it shrinks itself to 0, and the original size is saved here.
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
