#include "GOBManager.h"
#include "GOBFrame.h"
#include "SystemButtons.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

#define	TB_H	20		//title bar height

CGOBFrame::CGOBFrame()
{
	m_IsMinimized = FALSE;
	m_ExitButton = TRUE;
    SetTextColor( GWC.ButtonTextNormal );
	m_IsDragging = FALSE;

	m_CloseButton = NULL;
	m_MinimizeButton = NULL;

	m_CloseButton = new CGOBSysClose;
	m_CloseButton->SetPos(0,0);
	m_CloseButton->SetSize(16,16);
	m_MinimizeButton = new CGOBSysMinimize;
	m_MinimizeButton->SetPos(0,0);
	m_MinimizeButton->SetSize(16,16);

	// no need to delete these in destructor, manager will delete them
	AddChild(m_MinimizeButton);
	AddChild(m_CloseButton);
}


void CGOBFrame::SetText( const char * newtext)
{
    if(newtext != NULL)
    {
        DELETEARRAY(m_pText);
        m_pText = new char[strlen(newtext) + 1];
        strcpy(m_pText, newtext);
    }
}


GOBLIN_RETVAL CGOBFrame::OnSystemMsg(GOBLIN_PARAM param)
{
	//param is the system specific message id
	switch(param)
	{
	case SYS_CLOSE:
		GetParent()->RemoveChild(this);
		break;

	case SYS_MINIMIZE:
        m_IsMinimized = !m_IsMinimized;
        break;
	}
	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBFrame::OnDraw(GOBLIN_PARAM param)
{

	RECT rc;

	if(m_IsMinimized)
	{
		rc.left = m_Pos.x;
		rc.top = m_Pos.y;
		rc.right = rc.left + m_Size.cx;
		rc.bottom = rc.top + TB_H;
	}
	else
	{
		rc.left = m_Pos.x;
		rc.top = m_Pos.y;
		rc.right = rc.left + m_Size.cx;
		rc.bottom = rc.top + m_Size.cy;
	}

	CDXSurface *surf = GM.GetSurfacePtr();

	if(m_pBGImage)
	{
		INT32 sw = surf->GetWidth();
		INT32 sh = surf->GetHeight();
		INT32 iw = m_pBGImage->GetWidth();
		INT32 ih = m_pBGImage->GetHeight();

//		INT32 x,y;

		RECT srcRect;
        srcRect.left   = 0;
        srcRect.top    = 0;
        srcRect.right  = sw;
		if(m_IsMinimized)
			srcRect.bottom = rc.bottom-rc.top;
		else
			srcRect.bottom = sh;

		m_pBGImage->DrawDDBlk(surf, rc.left, rc.top, &srcRect);
	}
	else
	{
		surf->FillRect( rc.left+2, rc.top+2, rc.right-2, rc.top+TB_H, GWC.ActiveTitleBarFace );
		surf->FillRect( rc.left+2, rc.top+TB_H, rc.right-1, rc.bottom-1, GWC.ActiveWindowFace );

		surf->Lock();

		surf->HLine(rc.left, rc.right, rc.top, GWC.ActiveWindowHilight);
		surf->VLine(rc.top, rc.bottom, rc.left, GWC.ActiveWindowHilight);
		surf->HLine(rc.left, rc.right, rc.bottom, GWC.ActiveWindowShadow);
		surf->VLine(rc.top, rc.bottom, rc.right, GWC.ActiveWindowShadow);

		surf->HLine(rc.left+1, rc.right-1, rc.top+1, GWC.ActiveWindowHilight);
		surf->VLine(rc.top+1, rc.bottom-1, rc.left+1, GWC.ActiveWindowHilight);
		surf->HLine(rc.left+1, rc.right-1, rc.bottom-1, GWC.ActiveWindowShadow);
		surf->VLine(rc.top+1, rc.bottom-1, rc.right-1, GWC.ActiveWindowShadow);

		surf->UnLock();
	}

	if(m_pText)
	{
		if(IsDisabled)
		{
			GM.m_Font[m_FontIndex]->Draw( m_Pos.x+2, m_Pos.y+2, m_pText, GM.GetSurfacePtr());
		}
		else
		{
			GM.m_Font[m_FontIndex]->Draw( m_Pos.x+2, m_Pos.y+2, m_pText, GM.GetSurfacePtr());
		}
	}


	if(!m_IsMinimized)
	{
		SendMsgToChildren(GM_DRAW);
	}
	else
	{
		if(m_CloseButton)
			SendMsg(m_CloseButton, GM_DRAW, 0);
		if(m_MinimizeButton)
			SendMsg(m_MinimizeButton, GM_DRAW, 0);
	}

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBFrame::OnLBUp(GOBLIN_PARAM param)
{
    if (m_IsMinimized)
	{
       return GOBLIN_SUCCESS;
    }

//    BringToFront();

    if (GI.MousePos.y <= m_Pos.y + TB_H)
	{
		GM.CaptureMouse(this);
		m_IsDragging = TRUE;

        return GOBLIN_SUCCESS;
    }
    else
	{
		m_IsDragging = FALSE;
    }

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBFrame::OnLBDown(GOBLIN_PARAM param)
{
    BringToFront();

    if (GI.MousePos.y <= m_Pos.y + TB_H)
	{
		GM.CaptureMouse(this);
		m_IsDragging = TRUE;

        return GOBLIN_SUCCESS;
    }
    else
	{
		m_IsDragging = FALSE;
    }

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBFrame::OnRBUp(GOBLIN_PARAM param)
{
    if(m_IsMinimized)
	{
        return GOBLIN_SUCCESS;
    }

    return GOBLIN_SUCCESS;
}


void CGOBFrame::BringToFront(void)
{
	CGOBWidgetParent *parent = GetParent();
    GetParent()->RemoveChild(this);
    parent->AddChild(this);
}


//  Moves a frame and all its children.
//  To be called during a setup routine, not from process() routine.
void CGOBFrame::Move( INT32 newx, INT32 newy)
{
	FixPos(newx,newy);

	INT32 cx = m_Pos.x + m_Size.cx;
	if(m_CloseButton)
	{
		cx-=m_CloseButton->m_Size.cx+2;
		m_CloseButton->m_Pos.x = cx;
		m_CloseButton->m_Pos.y = m_Pos.y+2;
	}
	if(m_MinimizeButton)
	{
		cx-=m_MinimizeButton->m_Size.cx+2;
		m_MinimizeButton->m_Pos.x = cx;
		m_MinimizeButton->m_Pos.y = m_Pos.y+2;
	}

	CGOBWidgetParent::Move(newx, newy);
}


GOBLIN_RETVAL CGOBFrame::OnMouseMove(GOBLIN_PARAM param)
{
	if(GI.MouseButLeft && GM.IsMouseCaptured())
	{
		if(m_IsDragging)
		{
			Move( m_Pos.x+(GI.MousePos.x - GI.OldMousePos.x), m_Pos.y+(GI.MousePos.y - GI.OldMousePos.y));
		}
	}
	else
	{
		if(m_IsDragging)
			GM.ReleaseMouse(this);

		m_IsDragging = FALSE;
	}

	return GOBLIN_SUCCESS;
}

