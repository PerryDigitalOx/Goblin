#include "CDXFontBase.h"

CDXFontBase::CDXFontBase()
{
	m_dwBkMode = TRANSPARENT;
	m_dwBkColor = RGB(0,0,0);
	m_dwTextColor = RGB(255,255,255);
	m_pScreen = NULL;
	m_szText.cx = 0;
	m_szText.cy = 0;
}

CDXFontBase::~CDXFontBase()
{

}


HRESULT CDXFontBase::Draw(INT32 xPos, INT32 yPos, char * pText , CDXSurface * lpDDest, INT16 nTextLength )
{
	return -1;
}

CDXFontBase::GetTextSize(char *szText, SIZE &sz)
{

}
