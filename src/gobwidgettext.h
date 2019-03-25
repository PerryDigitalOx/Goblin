#ifndef CGOBWIDGETTEXT_H
#define CGOBWIDGETTEXT_H

#include <cdxtypes.h>

class CGOBWidgetText
{
public:
	CGOBWidgetText();
	virtual ~CGOBWidgetText();

	void		SetTextColor(DWORD rgb)						{ m_TextColor = rgb; }
	DWORD		GetTextColor()								{ return m_TextColor; }
	void		SetShadowColor(DWORD rgb)					{ m_ShadowColor = rgb; }
	DWORD		GetShadowColor()							{ return m_ShadowColor; }
	void		SetShadowOffset( INT16 x, INT16 y )			{ m_Shadow.x = x; m_Shadow.y = y; }
	void		SetFontIndexToUse( char index )				{ m_FontIndex = index; }

	char *		m_pText;				//miscellaneous text associated with this widget
	SIZE		m_szText;				//dimensions of text using current font
	DWORD		m_TextColor;			//color of text
	DWORD		m_ShadowColor;			//color of shadow
	POINT		m_Shadow;				//shadow offset for text

	// index of font into managers font table
	char		m_FontIndex;


	// Get the text associated with this widget
	virtual char *GetText(void)								{ return m_pText; };

	// Change the text associated with this widget
	// Allocation of text is internal to widget.
	// User can trash their own pointer after this call.
	virtual void SetText( BYTE *newtext) {};

};

#endif
