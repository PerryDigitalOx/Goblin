#include "GOBManager.h"
#include "GOBPopMenu.h"
#include "GOBComboBox.h"
#include "GOBColor.h"			// for color management

CGOBComboBox::CGOBComboBox()
{
	m_OrigHeight = -1;
	IsOpen = FALSE;
	m_pSelectedChild = NULL;
	m_ThumbWidth = 20;
}


void CGOBComboBox::SetText( const char * newtext)
{
    if(newtext != NULL)
    {
        DELETEARRAY(m_pText);
        m_pText = new char[strlen(newtext) + 1];
        strcpy(m_pText, newtext);
    }
}


GOBLIN_RETVAL CGOBComboBox::OnLBUp(GOBLIN_PARAM param)
{
	IsOpen = !IsOpen;

	Move(m_Pos.x, m_Pos.y);

	if(param)
	{
		m_pSelectedChild = (CGOBWidget*)param;

		GM.SetEvent(m_pSelectedChild->GetID());
	}

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBComboBox::OnLostFocus(GOBLIN_PARAM param)
{
	IsOpen = FALSE;
	Move(m_Pos.x, m_Pos.y);

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBComboBox::OnDraw(GOBLIN_PARAM param)
{
	UINT32 col1 = GWC.ButtonHilight;
	UINT32 col2 = GWC.ButtonShadow;

	RECT rc;
	rc.left = m_Pos.x;
	rc.top = m_Pos.y;
	rc.right = rc.left + m_Size.cx;
	rc.bottom = rc.top + m_Size.cy;

	CDXSurface *surf = GM.GetSurfacePtr();

	//combo box
	surf->FillRect(rc.left+1, rc.top+1, rc.right-m_ThumbWidth, rc.top+m_OrigHeight, GWC.ButtonFace );
	surf->Lock();
	surf->HLine(rc.left, rc.right-m_ThumbWidth, rc.top, col2);
	surf->HLine(rc.left, rc.right-m_ThumbWidth, rc.top+m_OrigHeight, col1);
	surf->VLine(rc.top, rc.top+m_OrigHeight, rc.left, col2);
	surf->VLine(rc.top, rc.top+m_OrigHeight, rc.right-m_ThumbWidth, col1);
	surf->UnLock();

	// combo button
	surf->FillRect(rc.right-m_ThumbWidth+1, rc.top+1, rc.right, rc.bottom, GWC.ButtonFace );
	surf->Lock();
	surf->HLine(rc.right-m_ThumbWidth, rc.right, rc.top, col1);
	surf->HLine(rc.right-m_ThumbWidth, rc.right, rc.bottom, col2);
	surf->VLine(rc.top, rc.bottom, rc.right-m_ThumbWidth, col1);
	surf->VLine(rc.top, rc.bottom, rc.right, col2);
	surf->UnLock();

	if(IsOpen)
	{
		//combo popup
		surf->FillRect(rc.left+1, rc.top+1+m_OrigHeight, rc.right, rc.bottom, GWC.ButtonFace );
		surf->Lock();
		surf->HLine(rc.left, rc.right, rc.top+m_OrigHeight, col1);
		surf->HLine(rc.left, rc.right, rc.bottom, col2);
		surf->VLine(rc.top+m_OrigHeight, rc.bottom, rc.left, col1);
		surf->VLine(rc.top+m_OrigHeight, rc.bottom, rc.right, col2);
		surf->UnLock();
	}

	if(m_pSelectedChild)
	{
		GM.m_Font[m_pSelectedChild->GetFontIndexToUse()]->Draw(m_Pos.x+1, m_Pos.y+1, m_pSelectedChild->GetText(), GM.GetSurfacePtr());
	}

	CGOBWidget *pWidget = NULL;
	
	pWidget = m_ActiveList.GetLast();

	//if(m_ActiveList.GetTail(&pWidget))
	if(pWidget)
	{
		do
		{
			if(!IsOpen)
			{
				//CGOBWidgetText *pw = (CGOBWidgetText*)pWidget;
				//if(pw->m_pText != NULL)
				//{
					//GM.m_Font[pw->m_FontIndex]->DrawTransColor(m_Pos.x+1, m_Pos.y+1, pw->m_pText, GM.GetSurfacePtr(), GWC.ButtonTextNormal);
				//}

				if(PtInRect(&rc, pWidget->m_Pos))
					SendMsg(pWidget, GM_DRAW, 0);
			}
			else
			{
				SendMsg(pWidget, GM_DRAW, 0);
			}
		}while((pWidget = m_ActiveList.Prev(pWidget)));
	}

    return GOBLIN_SUCCESS;
}


//  Moves a frame and all its children.
//  To be called during a setup routine, not from process() routine.
void CGOBComboBox::Move( INT32 newx, INT32 newy )
{
	FixPos(newx, newy);
    CGOBWidget *pWidget = NULL;
    INT32 yoffset = m_Size.cy;
    INT32 width = 0;

    if(m_OrigHeight==-1)
        m_OrigHeight = m_Size.cy;

    if((pWidget = m_ActiveList.GetLast()))
    {
        do
        {
            pWidget->Move(m_Pos.x+1, m_Pos.y+yoffset+1);
            yoffset += pWidget->m_Size.cy+1;

            if(pWidget->m_Size.cx>width)
                width = pWidget->m_Size.cx;
		}while((pWidget = m_ActiveList.Prev(pWidget)));
    }

    if(IsOpen)
    {
        m_OrigHeight = m_Size.cy;
        m_Size.cy = yoffset + 1;
    }
    else
    {
        m_Size.cy = m_OrigHeight;
    }

	//call parent class to move all children
	CGOBWidgetParent::Move(newx, newy);
}


INT32 CGOBComboBox::GetSelectedChildID()
{
	if (!m_pSelectedChild) return -1;
	return m_pSelectedChild->GetID();
}


void CGOBComboBox::SelectChild(INT32 Child_ID)
{
	CGOBWidget *pWidget = NULL;
	
	pWidget = m_ActiveList.GetLast();

	if(pWidget)
	{
		do
		{
			if (pWidget->GetID()==Child_ID) 
			{
				m_pSelectedChild=pWidget;
				return;
			}
		}
		while((pWidget = m_ActiveList.Prev(pWidget)));
	}
	m_pSelectedChild=NULL;
}