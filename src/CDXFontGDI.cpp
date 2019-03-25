#include "CDXFontGDI.h"

CDXFontGDI::CDXFontGDI()
{
	m_hFont = NULL;
	m_hDC = NULL;
}

CDXFontGDI::~CDXFontGDI()
{
	if(m_hFont)
		DeleteObject(m_hFont);
}

CDXFontGDI::Create( CDXScreen *pScreen, const char *szFontName, INT16 nFontSize )
{
	m_pScreen = pScreen;
	
	m_hDC = pScreen->GetBack()->GetDC();
	pScreen->GetBack()->ReleaseDC();

	if(m_hFont)
		DeleteObject(m_hFont);

	m_hFont = CreateFont(nFontSize, 0,
		0, 0,
		400,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		NONANTIALIASED_QUALITY,
		VARIABLE_PITCH,
		szFontName);

}


BOOL CDXFontGDI::GetTextSize( char *szText, SIZE &sz )
{
	if(m_hFont&&m_pScreen)
	{
		m_hDC = m_pScreen->GetBack()->GetDC();
		BOOL retval;
		SelectObject(m_hDC, m_hFont);
		retval = GetTextExtentPoint32(m_hDC, szText, strlen(szText), &sz);
		m_szText = sz;
		m_pScreen->GetBack()->ReleaseDC();
		return retval;
	}
	return FALSE;
}


HRESULT CDXFontGDI::Draw(INT32 xPos, INT32 yPos, char *pText, CDXSurface *lpDDest, INT16 nTextLength)
{
	m_hDC = lpDDest->GetDC();
	if(m_hDC)
	{
		SelectObject(m_hDC, m_hFont);
		::SetBkMode(m_hDC, GetBkMode());
		::SetTextColor(m_hDC, GetTextColor());

		//DrawText(m_hDC, pText, strlen(pText), pRect, DT_WORDBREAK);
		TextOut(m_hDC, xPos, yPos, pText, strlen(pText));
	}
	lpDDest->ReleaseDC();

	return S_OK;
}
