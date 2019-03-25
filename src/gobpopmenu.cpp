#include "GOBManager.h"
#include "GOBPopMenu.h"
#include "GOBColor.h"			// for color management


GOBLIN_RETVAL CGOBPopMenu::OnDraw(GOBLIN_PARAM param)
{
	RECT rc = { m_Pos.x, m_Pos.y, m_Pos.x+m_Size.cx, m_Pos.y+m_Size.cy };

	CDXSurface *surf = GM.GetSurfacePtr();

	surf->FillRect( m_Pos.x+1, m_Pos.y+1, m_Pos.x+m_Size.cx-1, m_Pos.y+m_Size.cy-1, GWC.ActiveWindowFace );

	surf->Lock();
	surf->HLine(m_Pos.x, m_Pos.x+m_Size.cx, m_Pos.y, GWC.ActiveWindowHilight);
	surf->VLine(m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x, GWC.ActiveWindowHilight);
	surf->HLine(m_Pos.x, m_Pos.x+m_Size.cx, m_Pos.y+m_Size.cy, GWC.ActiveWindowShadow);
	surf->VLine(m_Pos.y, m_Pos.y+m_Size.cy, m_Pos.x+m_Size.cx, GWC.ActiveWindowShadow);
	surf->UnLock();

	SendMsgToChildren(GM_DRAW);

    return GOBLIN_SUCCESS;
}


//  Moves a frame and all its children.
//  To be called during a setup routine, not from process() routine.
void CGOBPopMenu::Move( INT32 newx, INT32 newy )
{
	FixPos(newx,newy);
	CGOBWidget *pWidget = NULL;
	INT32 y = 0;
	INT32 width = 0;

	if((pWidget = m_ActiveList.GetLast()))
	{
		do
		{
			pWidget->Move(m_Pos.x+2, m_Pos.y+y+2);
			y+=pWidget->m_Size.cy+2;

			if(pWidget->m_Size.cx>width)
				width = pWidget->m_Size.cx;
		}while((pWidget = m_ActiveList.Prev(pWidget)));
	}

	m_Size.cy = y+4;
	m_Size.cx = width+4;

	//call parent class to move all children
	CGOBWidgetParent::Move(newx, newy);
}
