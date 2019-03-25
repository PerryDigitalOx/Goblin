#ifndef CDXFONTBITMAP_H
#define CDXFONTBITMAP_H

#include "CDXFontBase.h"
#include <cdxsprite.h>

class CDXFontBitmap : public CDXFontBase  
{
public:
	CDXFontBitmap();
	virtual ~CDXFontBitmap();

	Create( CDXScreen *pScreen, const char *szFileName, UINT32 BlockWidth, UINT32 BlockHeight, UINT16 nBlocks );

	HRESULT Draw(INT32 xPos, INT32 yPos, char * pText , CDXSurface * lpDDest, INT16 nTextLength = -1 );
	BOOL	GetTextSize(char *szText, SIZE &sz);

	CDXSprite *m_pSurface;

	void CalculateKerning();
};

#endif
