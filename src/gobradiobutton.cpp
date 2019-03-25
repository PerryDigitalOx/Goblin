
#include "GOBManager.h"
#include "GOBRadioButton.h"
#include "GOBColor.h"			// for color management

static UINT8 radioimage[] =
{
	0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,

	0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
	0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,0,1,2,2,2,1,1,1,1,2,2,2,1,0,0,
	0,1,2,2,2,1,1,1,1,1,1,2,2,2,1,0,
	0,1,2,2,1,1,1,1,1,1,1,1,2,2,1,0,
	1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,
	1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,
	1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,
	1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,
	0,1,2,2,1,1,1,1,1,1,1,1,2,2,1,0,
	0,1,2,2,2,1,1,1,1,1,1,2,2,2,1,0,
	0,0,1,2,2,2,1,1,1,1,2,2,2,1,0,0,
	0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,
	0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0,
	0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,

};

CGOBRadioButton::CGOBRadioButton()
{
	m_GroupID = 1;
	m_IsHover = FALSE;
	m_State = STATE_UNCHECKED;
	m_Size.cx = 16;
	m_Size.cy = 16;
};

void CGOBRadioButton::SetText( const char * newtext)
{
    DELETEARRAY(m_pText);
    m_pText = new char[strlen(newtext) + 1];
    strcpy(m_pText, newtext);
};

GOBLIN_RETVAL CGOBRadioButton::OnGotMouse(GOBLIN_PARAM param)
{
	m_IsHover = TRUE;

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBRadioButton::OnLostMouse(GOBLIN_PARAM param)
{
	if(m_IsHover)
	{
		m_IsHover = FALSE;
	}
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBRadioButton::OnLBUp(GOBLIN_PARAM param)
{
	CGOBWidget *pWidget = NULL;

	if(!GetParent())
		return GOBLIN_NOPARENT;

	if((pWidget = GetParent()->m_ActiveList.GetFirst()))
	{
		do
		{
//			if( dynamic_cast<CGOBRadioButton *>(pWidget) )
			if( static_cast<CGOBRadioButton *>(pWidget) )
			{
				if(GetGroupID() == ((CGOBRadioButton*)pWidget)->GetGroupID())
					((CGOBRadioButton*)pWidget)->SetState(STATE_UNCHECKED);
			}
		}
		while ((pWidget = pWidget->GetNext()));
	}

	SetState(STATE_CHECKED);

	return GOBLIN_SUCCESS;
};


GOBLIN_RETVAL CGOBRadioButton::OnDraw(GOBLIN_PARAM param)
{
	UINT32 col1 = GWC.ButtonHilight;
	UINT32 col2 = GWC.ButtonShadow;
	UINT8 x,y;
	UINT16 offset = 0;

	if(m_State==STATE_CHECKED)
		offset = 16*16;

	CDXSurface *surf = GM.GetSurfacePtr();

	surf->Lock();
	for(y=0; y<16; y++)
	{
		for(x=0; x<16; x++)
		{
			if(radioimage[y*16+x+offset]==1)
				surf->PutPixel(m_Pos.x+x,m_Pos.y+y,col1);
			else if(radioimage[y*16+x+offset]==2)
				surf->PutPixel(m_Pos.x+x,m_Pos.y+y,col2);
		}
	}
	surf->UnLock();

	if(m_pText != NULL)
	{
//		GM.m_Font[m_FontIndex]->DrawTransColor(m_Pos.x+16, m_Pos.y+2, m_pText, GM.GetSurfacePtr(), GOBColor(GetTextColor()));
		GM.m_Font[m_FontIndex]->Draw(m_Pos.x+16, m_Pos.y+2, m_pText, GM.GetSurfacePtr());
	}

    return GOBLIN_SUCCESS;
}


void CGOBRadioButton::SetState( INT16 state)
{
	m_State = state;
}
