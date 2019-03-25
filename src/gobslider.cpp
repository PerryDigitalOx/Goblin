
#include "GOBManager.h"
#include "GOBSlider.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"


CGOBSlider::CGOBSlider()
{
	SetOffset(0,0);
	SetRange(0, 100);
	SetThumbSize(16,16);
	SetThumbPos(0,0);
}

void CGOBSlider::Move( INT32 newx, INT32 newy)
{
	CGOBWidget::Move(newx, newy);

	SetThumbPos(newx, newy);
}


GOBLIN_RETVAL CGOBSlider::OnMouseMove(GOBLIN_PARAM param)
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


GOBLIN_RETVAL CGOBSlider::OnLBDown(GOBLIN_PARAM param)
{
	if(PtInRect(&m_rcThumb, GI.MousePos))
	{
		GM.CaptureMouse(this);
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBSlider::OnLBUp(GOBLIN_PARAM param)
{
	if(GM.IsMouseCaptured())
	{
		GM.ReleaseMouse(this);
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBSlider::OnDraw(GOBLIN_PARAM param)
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

    return GOBLIN_SUCCESS;
}


void CGOBSlider::SetRange( INT32 nMin, INT32 nMax)
{
	m_nMin = nMin;
	m_nMax = nMax;
}


void CGOBSlider::SetThumbPos( INT32 nx, INT32 ny)
{
	float stepx = (float)m_Size.cx / (float)(m_nMax-m_nMin);
	INT32 posx = (INT32)((nx + m_xOffset - m_Pos.x) / stepx);
	float stepy = (float)m_Size.cy / (float)(m_nMax-m_nMin);
	INT32 posy = (INT32)((ny + m_yOffset - m_Pos.y) / stepy);

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

	m_rcThumb.left = m_Pos.x + (INT32)(posx * stepx);
	m_rcThumb.top = m_Pos.y + (INT32)(posy * stepy);
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

	if(m_rcThumb.top < m_Pos.y)
	{
		m_rcThumb.top = m_Pos.y;
		m_rcThumb.bottom = m_rcThumb.top + m_ThumbHeight;
	}
	else if(m_rcThumb.bottom > m_Pos.y+m_Size.cy)
	{
		m_rcThumb.bottom = m_Pos.y+m_Size.cy;
		m_rcThumb.top = m_rcThumb.bottom - m_ThumbHeight;
	}
}
