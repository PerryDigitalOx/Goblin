#include "GOBManager.h"
#include "GOBScrollBar.h"
#include "GOBInput.h"
#include "GOBColor.h"

CGOBScrollBar::CGOBScrollBar()
{
	m_pFirstButton = NULL;
	m_pSecondButton = NULL;
	SetOffset(0,0);
	SetRange(0, 100);
	SetVertical();
	SetThumbSize(16,16*4);
	SetThumbPos(0,0);
	m_stepx = m_stepy = 0;
}

void CGOBScrollBar::Move( INT32 newx, INT32 newy)
{
	CGOBWidgetParent::Move(newx, newy);

/*
	RECT rc = m_rcThumb;
	rc.left = newx-m_rcThumb.left;
	rc.top = newy-m_rcThumb.top;
	rc.right = rc.left + m_rcThumb.right-m_rcThumb.left;
	rc.bottom = rc.top + m_rcThumb.bottom-m_rcThumb.top;
*/

	SetThumbPos(newx, newy);
}


GOBLIN_RETVAL CGOBScrollBar::OnMouseMove(GOBLIN_PARAM param)
{
	if(GI.MouseButLeft && GM.IsMouseCaptured())
	{
		SetOffset(GI.MousePos.x - m_Pos.x, GI.MousePos.y - m_Pos.y);
		SetThumbPos(m_Pos.x, m_Pos.y);
	}
	else
	{
		GM.ReleaseMouse(this);
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBScrollBar::OnLBDown(GOBLIN_PARAM param)
{
	CGOBButton *but = (CGOBButton *)param;
	if(but==m_pFirstButton)
	{
		SetThumbPos(m_nXPos, m_nYPos-m_stepy);
	}
	else if(but==m_pSecondButton)
	{
		SetThumbPos(m_nXPos, m_nYPos+m_stepy);
	}

	if(PtInRect(&m_rcThumb, GI.MousePos))
	{
		GM.CaptureMouse(this);
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBScrollBar::OnLBUp(GOBLIN_PARAM param)
{
	if(GM.IsMouseCaptured())
	{
		GM.ReleaseMouse(this);
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBScrollBar::OnDraw(GOBLIN_PARAM param)
{
	RECT rc;
	rc.left = m_Pos.x;
	rc.top = m_Pos.y;
	rc.right = rc.left + m_Size.cx;
	rc.bottom = rc.top + m_Size.cy;

	CDXSurface *surf = GM.GetSurfacePtr();

	surf->FillRect( rc.left+1, rc.top+1, rc.right-1, rc.bottom-1, GWC.ButtonFace );
	surf->FillRect( m_rcThumb.left+1, m_rcThumb.top+1, m_rcThumb.right-1, m_rcThumb.bottom-1, GWC.ButtonFace );

	surf->Lock();

	surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonHilight);
	surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonHilight);
	surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonShadow);
	surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonShadow);

	surf->HLine(m_rcThumb.left, m_rcThumb.right, m_rcThumb.top, GWC.ButtonHilight);
	surf->VLine(m_rcThumb.top, m_rcThumb.bottom, m_rcThumb.left, GWC.ButtonHilight);
	surf->HLine(m_rcThumb.left, m_rcThumb.right, m_rcThumb.bottom, GWC.ButtonShadow);
	surf->VLine(m_rcThumb.top, m_rcThumb.bottom, m_rcThumb.right, GWC.ButtonShadow);

	surf->UnLock();

	SendMsgToChildren( GM_DRAW );

    return GOBLIN_SUCCESS;
}


void CGOBScrollBar::SetRange( INT32 nMin, INT32 nMax)
{
	m_nMin = nMin;
	m_nMax = nMax;
}


void CGOBScrollBar::SetThumbPos( INT32 nx, INT32 ny)
{
	SIZE butsize;
	butsize.cx = 0;
	butsize.cy = 0;

	if(m_pFirstButton)
	{
		butsize.cy += m_pFirstButton->m_Size.cy;
	}

	m_stepx = (float)m_Size.cx / (float)(m_nMax-m_nMin);
	INT32 posx = (INT32)((nx + m_xOffset - m_Pos.x) / m_stepx);
	m_stepy = (float)(m_Size.cy-(butsize.cy*2)) / (float)(m_nMax-m_nMin);
	INT32 posy = (INT32)((ny + m_yOffset - m_Pos.y-(butsize.cy*2)) / m_stepy);

	if(posx<0)
		posx = 0;
	if(posy<0)
		posy = 0;
	if(posx>m_nMax)
		posx = m_nMax;
	if(posy>m_nMax)
		posy = m_nMax;

	m_nXPos = posx;
	m_nYPos = posy;

	m_rcThumb.left = m_Pos.x + (INT32)(posx * m_stepx);
	m_rcThumb.top = m_Pos.y+butsize.cy + (INT32)(posy * m_stepy);
	m_rcThumb.right = m_rcThumb.left + m_ThumbWidth;
	m_rcThumb.bottom = m_rcThumb.top + m_ThumbHeight;


	if(m_rcThumb.left < m_Pos.x)
	{
		m_rcThumb.left = m_Pos.x;
		m_rcThumb.right = m_rcThumb.left + m_ThumbWidth;
	}
	else if(m_rcThumb.right > m_Pos.x+m_Size.cx)
	{
		m_rcThumb.right = m_Pos.x+m_Size.cx;
		m_rcThumb.left = m_rcThumb.right - m_ThumbWidth;
	}

	if(m_rcThumb.top < m_Pos.y+butsize.cy)
	{
		m_rcThumb.top = m_Pos.y+butsize.cy;
		m_rcThumb.bottom = m_rcThumb.top + m_ThumbHeight;
	}
	else if(m_rcThumb.bottom > m_Pos.y+m_Size.cy-butsize.cy)
	{
		m_rcThumb.bottom = m_Pos.y+m_Size.cy-butsize.cy;
		m_rcThumb.top = m_rcThumb.bottom - m_ThumbHeight;
	}
}


void CGOBScrollBar::SetFirstButton( CGOBButton *pFirst )
{
	m_pFirstButton = pFirst;
	m_pFirstButton->SetFlag(WF_PARENTNOTIFY);
	AddChild(m_pFirstButton);
	m_pFirstButton->Move(m_Pos.x, m_Pos.y);
}

void CGOBScrollBar::SetSecondButton( CGOBButton *pSecond )
{
	m_pSecondButton = pSecond;
	m_pSecondButton->SetFlag(WF_PARENTNOTIFY);
	AddChild(m_pSecondButton);
	m_pSecondButton->Move(m_Pos.x, m_Pos.y+m_Size.cy-m_pFirstButton->m_Size.cy);
}
