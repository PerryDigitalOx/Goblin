#ifndef CDXFONTGDI_H
#define CDXFONTGDI_H

#include "CDXFontBase.h"

class CDXFontGDI : public CDXFontBase  
{
public:
	CDXFontGDI();
	virtual ~CDXFontGDI();

	Create( CDXScreen *pScreen, const char *szFontName, INT16 nFontSize );

	HRESULT Draw(INT32 xPos, INT32 yPos, char *pText, CDXSurface *lpDDest, INT16 nTextLength = -1);
	BOOL	GetTextSize(char *szText, SIZE &sz);


	HFONT m_hFont;				// A HFONT object describing the currently selected font
	HDC m_hDC;
};

#endif
