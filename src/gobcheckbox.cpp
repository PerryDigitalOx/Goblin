
#include "GOBManager.h"
#include "GOBCheckBox.h"
#include "GOBColor.h"			// for color management

static UINT8 checkboximage[] =
{
	1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,

	1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 1,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,1, 1,1,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,1, 1,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,1,1, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,1,1,1, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,1,1,2, 2,2,2,1,
	1,2,1,1, 1,2,2,2, 1,1,2,2, 2,2,2,1,
	1,2,2,1, 1,1,2,1, 1,1,2,2, 2,2,2,1,
	1,2,2,2, 1,1,1,1, 1,2,2,2, 2,2,2,1,
	1,2,2,2, 2,1,1,1, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,1,2, 2,2,2,2, 2,2,2,1,
	1,2,2,2, 2,2,2,2, 2,2,2,2, 2,2,2,1,
	1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1,

};

CGOBCheckBox::CGOBCheckBox()
{
	m_IsHover = FALSE;
	m_State = STATE_UNCHECKED;
	m_Size.cx = 16;
	m_Size.cy = 16;
};


void CGOBCheckBox::SetText( const char * newtext)
{
    DELETEARRAY(m_pText);
    m_pText = new char[strlen(newtext) + 1];
    strcpy(m_pText, newtext);
};

GOBLIN_RETVAL CGOBCheckBox::OnGotMouse(GOBLIN_PARAM param)
{
	m_IsHover = TRUE;

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBCheckBox::OnLostMouse(GOBLIN_PARAM param)
{
	if(m_IsHover)
	{
		m_IsHover = FALSE;
	}
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBCheckBox::OnLBUp(GOBLIN_PARAM param)
{
	if(m_State==STATE_CHECKED)
		SetState(STATE_UNCHECKED);
	else
		SetState(STATE_CHECKED);

	return GOBLIN_SUCCESS;
};


GOBLIN_RETVAL CGOBCheckBox::OnDraw(GOBLIN_PARAM param)
{
	UINT32 col1 = GWC.ButtonHilight;
	UINT32 col2 = GWC.ButtonShadow;
	UINT8 x,y;
	INT16 offset = 0;

	if(m_State==STATE_CHECKED)
		offset = 16*16;

	CDXSurface *surf = GM.GetSurfacePtr();
	surf->Lock();
	for(y=0; y<16; y++)
	{
		for(x=0; x<16; x++)
		{
			if(checkboximage[y*16+x+offset]==1)
				surf->PutPixel(m_Pos.x+x,m_Pos.y+y,col1);
			else if(checkboximage[y*16+x+offset]==2)
				surf->PutPixel(m_Pos.x+x,m_Pos.y+y,col2);
		}
	}
	surf->UnLock();

	if(m_pText != NULL)
	{
		GM.m_Font[m_FontIndex]->Draw(m_Pos.x+16, m_Pos.y+2, m_pText, GM.GetSurfacePtr());
	}

    return GOBLIN_SUCCESS;
};


void CGOBCheckBox::SetState( INT16 state )
{
	m_State = state;
}
