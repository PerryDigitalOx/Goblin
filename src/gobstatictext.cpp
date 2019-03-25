#include "GOBManager.h"
#include <cdxdebug.h>   //CDXASSERT()
#include "GOBStaticText.h"


void CGOBStaticText::SetText( const char * newtext)
{
    DELETEARRAY(m_pText);
    m_pText = new char[strlen(newtext) + 1];

    CDXASSERT(m_pText);

	if(!m_pText)		//validate string
		return;

    strcpy(m_pText, newtext);

	GM.m_Font[m_FontIndex]->GetTextSize(m_pText, m_szText);
}


GOBLIN_RETVAL CGOBStaticText::OnDraw(GOBLIN_PARAM param)
{
//	int tx = m_Pos.x+(m_Size.cx>>1)-(m_szText.cx>>1)+1;
//	int ty = m_Pos.y+(m_Size.cy>>1)-(m_szText.cy>>1)+1;

	if(m_pText != NULL)
	{
		GM.m_Font[m_FontIndex]->Draw(1+m_Pos.x, 1+m_Pos.y, m_pText, GM.GetSurfacePtr(),GetTextColor());
		//GM.m_Font[m_FontIndex]->DrawTransColor(m_Pos.x, m_Pos.y, m_pText, GM.GetSurfacePtr(), GOBColor(GetTextColor()));
//PSR		GM.m_Font[m_FontIndex]->DrawTrans( m_Pos.x, m_Pos.y, m_pText, GM.GetSurfacePtr() );
	}

    return GOBLIN_SUCCESS;
}
