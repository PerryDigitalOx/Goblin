#include "GOBManager.h"
#include "GOBMsgBox.h"

CGOBMsgBox::CGOBMsgBox() : CGOBPanel()
{
	SetFlag(WF_MODAL);
}


void CGOBMsgBox::SetText(char *newtext)
{
    DELETEARRAY(m_pText);
    m_pText = new char[strlen(newtext) + 1];
    strcpy(m_pText, newtext);

	GM.m_Font[m_FontIndex]->GetTextSize(m_pText, m_szText);
}


GOBLIN_RETVAL CGOBMsgBox::OnDraw(GOBLIN_PARAM param)
{
	GOBLIN_RETVAL retval;

	retval = CGOBPanel::OnDraw(param);

	if(m_pText != NULL)
	{
//		GM.m_Font[m_FontIndex]->DrawTrans(m_Pos.x+m_Size.cx/2-m_szText.cx/2, m_Pos.y+m_Size.cy/2-m_szText.cy/2, m_pText, GM.GetSurfacePtr(), GetTextColor());
		GM.m_Font[m_FontIndex]->Draw(m_Pos.x+m_Size.cx/2-m_szText.cx/2, m_Pos.y+m_Size.cy/2-m_szText.cy/2, m_pText, GM.GetSurfacePtr());
	}

	return retval;
}
