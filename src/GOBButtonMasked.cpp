#include "GOBManager.h"
#include "GOBButtonMasked.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

CGOBButtonMasked::CGOBButtonMasked()
{
	m_IsDown = FALSE;
	m_IsHover = FALSE;

	m_NormalFrame = 0;
	m_HoverFrame = 1;
	m_DownFrame = 2;
	m_MaskFrame = 3;
}

GOBLIN_RETVAL CGOBButtonMasked::OnLostMouse(GOBLIN_PARAM param)
{
	if(m_IsDown||m_IsHover)
	{
		m_IsDown = FALSE;
		m_IsHover = FALSE;
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButtonMasked::OnGotMouse(GOBLIN_PARAM param)
{
	//this fixes, if mouse button goes down, move off of item, then back on, its back to down.
	if(GI.MouseButLeft & 1)
		m_IsDown = TRUE;

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButtonMasked::OnMouseMove(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	if(m_IsDown)
	{
		if(!(GI.MouseButLeft & 1))
		{
			m_IsDown=FALSE;
		}
		m_IsHover = FALSE;
	}
	else
	{
		m_IsHover = FALSE;
		if(CheckMaskForHit())
			m_IsHover = TRUE;
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButtonMasked::OnLBDown(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	m_IsDown = TRUE;

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButtonMasked::OnLBUp(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	m_IsDown = FALSE;

	GM.SetEvent(GetID());

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButtonMasked::OnDraw(GOBLIN_PARAM param)
{
	CDXSprite *pImage = GetImagePtr();
	if(pImage)
	{
		if(IsFlagSet(WF_DISABLED))
			return GOBLIN_DISABLED;

		pImage->SetFrame(m_NormalFrame);

		if(m_IsHover)
			pImage->SetFrame(m_HoverFrame);

		if(m_IsDown)
			pImage->SetFrame(m_DownFrame);

		pImage->SetPos(m_Pos.x, m_Pos.y);
//		pImage->m_Tile->SetDest(m_Pos.x,m_Pos.y,m_Pos.y+m_Size.cy,m_Pos.x+m_Size.cx);
//		pImage->GetTile()->SetDest(m_Pos.x,m_Pos.y,m_Pos.y+m_Size.cy,m_Pos.x+m_Size.cx);

		pImage->Draw( GM.GetSurfacePtr(), 0, 0, GetBltType());	//call CDXSprite draw
	}

    return GOBLIN_SUCCESS;
}


BOOL CGOBButtonMasked::CheckMaskForHit(void)
{
	CDXSprite *pImage = GetImagePtr();
	if(pImage)
	{
		pImage->SetFrame(m_MaskFrame);
		INT32 x,y;
		x = GI.MousePos.x - m_Pos.x;
		y = GI.MousePos.y - m_Pos.y;
		x += pImage->GetTile()->m_BlockWidth * m_MaskFrame;


		pImage->GetTile()->Lock();
		UINT32 pixel = pImage->GetTile()->GetPixel( x,y );
		pImage->GetTile()->UnLock();
		if(pixel==RGB(0,0,0))
		{
			return TRUE;
		}
	}

	return FALSE;
}
