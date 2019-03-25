#ifndef CDXFONTBASE_H
#define CDXFONTBASE_H

#include <cdx.h>
#include <cdxscreen.h>
#include <cdxsurface.h>
#include <cdxtypes.h>

class CDXFontBase  
{
public:
	CDXFontBase();
	virtual ~CDXFontBase();

	virtual HRESULT Draw(INT32 xPos, INT32 yPos, char * pText , CDXSurface * lpDDest, INT16 nTextLength = -1 );
	virtual GetTextSize(char *szText, SIZE &sz);

	UINT32 GetBkColor()					{ return m_dwBkColor; }
	UINT32 GetBkMode()					{ return m_dwBkMode; }
	UINT32 GetTextColor()				{ return m_dwTextColor; }
	void SetBkMode(UINT32 mode)			{ m_dwBkMode = mode; }
	void SetBkColor(UINT32 color)		{ m_dwBkColor = color; }
	void SetTextColor(UINT32 color)		{ m_dwTextColor = color; }

protected:
   	CDXScreen *	m_pScreen;		// our CDX Screen pointer
	SIZE		m_szText;		// dimensions of text string in pixels

private:
	UINT32		m_dwBkMode;		// background drawing mode
	UINT32		m_dwBkColor;	// background color
	UINT32		m_dwTextColor;	// color of text
};

#endif
