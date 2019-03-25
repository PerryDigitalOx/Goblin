
#include "GOBManager.h"
#include "GOBButton.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

CGOBButton::CGOBButton()
{
	m_IsDown = FALSE;
	m_IsHover = FALSE;

	m_NormalFrame = 0;
	m_HoverFrame = 1;
	m_DownFrame = 2;
}


void CGOBButton::SetText( char * newtext )
{
    DELETEARRAY(m_pText);
    m_pText = new char[strlen(newtext) + 1];
    strcpy(m_pText, newtext);

	GM.m_Font[m_FontIndex]->GetTextSize(m_pText, m_szText);
}


GOBLIN_RETVAL CGOBButton::OnLostMouse(GOBLIN_PARAM param)
{
	m_IsDown = FALSE;
	m_IsHover = FALSE;

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButton::OnGotMouse(GOBLIN_PARAM param)
{
	//this fixes, if mouse button goes down, move off of item, then back on, its back to down.
	if(GI.MouseButLeft & 1)
	{
		//hover must have been set prior.
		if(m_IsHover)		//this fixes bug where button is down, roll over other buttons, they do down.
			m_IsDown = TRUE;
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButton::OnMouseMove(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	//if button is down
	if(m_IsDown)
	{
		// and mouse button isnt down
		if(!(GI.MouseButLeft & 1))
		{
			// we change button to up state
			m_IsDown=FALSE;
		}
		//turn off hover state
		m_IsHover = FALSE;
	}
	else
	{
		//if the mouse button isn't down, then we hover
		if(!(GI.MouseButLeft & 1))
			m_IsHover = TRUE;
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButton::OnLBDown(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	m_IsDown = TRUE;

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButton::OnLBUp(GOBLIN_PARAM param)
{
	if(IsFlagSet(WF_DISABLED))
		return GOBLIN_DISABLED;

	m_IsDown = FALSE;

	GM.SetEvent(GetID());

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBButton::OnDraw(GOBLIN_PARAM param)
{
	UINT32 rgb = NULL;
	RECT rc;
	rc.left = m_Pos.x;
	rc.top = m_Pos.y;
	rc.right = rc.left + m_Size.cx;
	rc.bottom = rc.top + m_Size.cy;

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
		pImage->Draw( GM.GetSurfacePtr(), 0, 0, GetBltType());	//call CDXSprite draw
	}
	else
	{
		CDXSurface *surf = GM.GetSurfacePtr();


		//if button is down, we draw hover and down state and set text color to text select
		if(m_IsDown)
		{
			rgb = GWC.ButtonTextSelect;

			if(!IsFlagSet(WF_TRANSPARENTBG))
			{
				surf->Rect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonHoverHilight);
				surf->Lock();
				surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonHoverShadow);
				surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonHoverShadow);
				surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonHoverHilight);
				surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonHoverHilight);
				surf->UnLock();
			}
		}
		else if(m_IsHover)
		{
			//if button is hover only, we draw hilight and set text hover color
			rgb = GWC.ButtonTextHover;
			if(!IsFlagSet(WF_TRANSPARENTBG))
			{
				surf->Rect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonHoverShadow);
				surf->Lock();
				surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonHoverHilight);
				surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonHoverHilight);
				surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonHoverShadow);
				surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonHoverShadow);
				surf->UnLock();
			}
		}
		else
		{
			//otherwise button is not active we draw normal and set text normal
			rgb = GWC.ButtonTextNormal;
			if(!IsFlagSet(WF_TRANSPARENTBG))
			{
				surf->Rect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonShadow);
				surf->Lock();
				surf->HLine(rc.left, rc.right, rc.top, GWC.ButtonHilight);
				surf->VLine(rc.top, rc.bottom, rc.left, GWC.ButtonHilight);
				surf->HLine(rc.left, rc.right, rc.bottom, GWC.ButtonShadow);
				surf->VLine(rc.top, rc.bottom, rc.right, GWC.ButtonShadow);
				surf->UnLock();
			}
		}

		//if the background is to be drawn...
		if(!IsFlagSet(WF_TRANSPARENTBG))
		{
			//if disabled button, we draw disabled button face
			if(IsFlagSet(WF_DISABLED))
				surf->FillRect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonFaceDisabled);
			else
				surf->FillRect(rc.left, rc.top, rc.right, rc.bottom, GWC.ButtonFace);
		}
	}

	//if button is disabled we set text color to disabled text color
	if(IsFlagSet(WF_DISABLED))
		rgb = GWC.ButtonTextDisabled;

	if(m_pText != NULL)
	{
		INT32 tx = m_Pos.x+(m_Size.cx>>1)-(m_szText.cx>>1);
		INT32 ty = m_Pos.y+(m_Size.cy>>1)-(m_szText.cy>>1);

		//GM.m_Font[m_FontIndex]->DrawTransColor(tx, ty, m_pText, GM.GetSurfacePtr(), rgb);
		GM.m_Font[m_FontIndex]->Draw(tx, ty, m_pText, GM.GetSurfacePtr());
	}

    return GOBLIN_SUCCESS;
}

