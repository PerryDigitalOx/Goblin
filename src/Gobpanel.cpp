#include "GOBManager.h"
#include "GOBPanel.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

CGOBPanel::CGOBPanel() : CGOBWidgetParent()
{
	m_IsDragging = FALSE;
}


GOBLIN_RETVAL CGOBPanel::OnDraw(GOBLIN_PARAM param)
{
	if(m_pBGImage)
	{
		m_pBGImage->DrawDDBlk(GM.GetSurfacePtr(), m_Pos.x, m_Pos.y);
	}
	else
	{
		CDXSurface *surf = GM.GetSurfacePtr();

        surf->FillRect( m_Pos.x+1, m_Pos.y+1, m_Pos.x+m_Size.cx-1,
                        m_Pos.y+m_Size.cy-1, GWC.ActiveWindowFace );

		surf->Lock();
		surf->HLine(m_Pos.x, m_Pos.x+m_Size.cx, m_Pos.y, GWC.ActiveWindowHilight);
		surf->VLine(m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x, GWC.ActiveWindowHilight);
		surf->HLine(m_Pos.x, m_Pos.x+m_Size.cx, m_Pos.y+m_Size.cy, GWC.ActiveWindowShadow);
		surf->VLine(m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x+m_Size.cx, GWC.ActiveWindowShadow);
		surf->UnLock();
	}

	SendMsgToChildren( GM_DRAW );

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBPanel::OnLBUp(GOBLIN_PARAM param)
{
	BOOL childhit = FALSE;
	RECT rc;

	CGOBWidget *pWidget = NULL;
	if((pWidget = m_ActiveList.GetFirst()))
	{
		do
		{
			rc.left = pWidget->m_Pos.x;
			rc.top = pWidget->m_Pos.y;
			rc.right = rc.left + pWidget->m_Size.cx;
			rc.bottom = rc.top + pWidget->m_Size.cy;

			if(PtInRect(&rc, GI.MousePos))
			{
				childhit = TRUE;
				break;
			}
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}

    BringToFront();

    return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBPanel::OnLBDown(GOBLIN_PARAM param)
{
	BOOL childhit = FALSE;
	RECT rc;

	CGOBWidget *pWidget = NULL;
	if((pWidget = m_ActiveList.GetFirst()))
	{
		do
		{
			rc.left = pWidget->m_Pos.x;
			rc.top = pWidget->m_Pos.y;
			rc.right = rc.left + pWidget->m_Size.cx;
			rc.bottom = rc.top + pWidget->m_Size.cy;

			if(PtInRect(&rc, GI.MousePos))
			{
				childhit = TRUE;
				break;
			}
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}

    BringToFront();

    if(!childhit)
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


void CGOBPanel::BringToFront(void)
{
	CGOBWidgetParent *parent = GetParent();
    parent->RemoveChild(this);
    parent->AddChild(this);
}


GOBLIN_RETVAL CGOBPanel::OnMouseMove(GOBLIN_PARAM param)
{
	if(GI.MouseButLeft && GM.IsMouseCaptured())
	{
		if(m_IsDragging)
		{
            Move( m_Pos.x+(GI.MousePos.x - GI.OldMousePos.x),
                  m_Pos.y+(GI.MousePos.y - GI.OldMousePos.y));
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

