#include "GOBManager.h"
#include "GOBWidgetParent.h"
#include "GOBInput.h"

CGOBWidgetParent::CGOBWidgetParent()
{
	m_pBGImage = NULL;
	m_Size.cx=0;
	m_Size.cy=0;
	m_Limited = FALSE; //Not limited.
}

CGOBWidgetParent::~CGOBWidgetParent()
{
	CleanUp();
}


void CGOBWidgetParent::CleanUp(void)
{
	SAFEDELETE(m_pBGImage);

	CGOBWidget *pHead = NULL;

	while(m_ActiveList.GetCount())
	{
		m_ActiveList.Clear(TRUE);
/*		m_ActiveList.GetHead(&pHead);
		m_ActiveList.DeleteHead();		//remove just pointer from list
		if(GM.m_pFocusObject==pHead)
			GM.m_pFocusObject = NULL;
		SAFEDELETE(pHead);				//delete actual data
*/
	}

	pHead = NULL;
	while(m_InActiveList.GetCount())
	{
		m_InActiveList.Clear(TRUE);
/*
		m_InActiveList.GetHead(&pHead);
		m_InActiveList.DeleteHead();	//remove just pointer from list
		if(GM.m_pFocusObject==pHead)
			GM.m_pFocusObject = NULL;
		SAFEDELETE(pHead);				//delete actual data
*/
	}
	GM.m_pFocusObject = NULL;
}


void CGOBWidgetParent::AddInActiveChild( CGOBWidget *pWidget )
{
	//if this widget doesn't already have a parent...
	if(!pWidget->GetParent())
	{
		pWidget->IsDisabled = FALSE;
		//add the widget as a child of this object
		m_InActiveList.Add( pWidget, FALSE);

		//set the widgets parent to this object
		pWidget->SetParent(this);
	}
}


void CGOBWidgetParent::AddChild( CGOBWidget *pWidget )
{
	//if this widget doesn't already have a parent...
	if(!pWidget->GetParent())
	{
		pWidget->IsDisabled = FALSE;
		//add the widget as a child of this object
		m_ActiveList.Add( pWidget, FALSE );

		//set the widgets parent to this object
		pWidget->SetParent(this);
	}
	if(pWidget->IsFlagSet(WF_MODAL))
	{
		GM.ActivateModal(pWidget);
	}
}


void CGOBWidgetParent::RemoveInActiveChild(CGOBWidget * widget)
{
	CGOBWidget *pWidget = NULL;

	if((pWidget = m_InActiveList.GetFirst()))
	{
		do
		{
			if(pWidget == widget)
			{
				//make sure this widget doesn't point to a parent anymore
				pWidget->SetParent(NULL);
				m_InActiveList.Remove(pWidget, FALSE);
				break;
			}
		}while((pWidget = m_InActiveList.Next(pWidget)));
	}
}


void CGOBWidgetParent::RemoveChild(CGOBWidget * widget)
{
	CGOBWidget *pWidget = NULL;

	if((pWidget = m_ActiveList.GetFirst()))
	{
		do
		{
			if(pWidget == widget)
			{
				if(GM.m_pMouseObject)
				{
					if(GM.m_pMouseObject->GetParent() == widget)
					{
						SendEventMsg(GM.m_pMouseObject, GM_LOSTMOUSE, 0);
						GM.m_pMouseObject = NULL;
					}
				}
				widget->SetParent(NULL);
				m_ActiveList.Remove(pWidget, FALSE);
				if(widget->IsFlagSet(WF_MODAL))
				{
					GM.DeActivateModal();
				}
				break;
			}
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}


}


CGOBWidget* CGOBWidgetParent::FindMouseObject(void)
{
    CGOBWidget *pMouseObject = (CGOBWidget*)this;
	CGOBWidget *pWidget = NULL;

	RECT rc;

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
				pMouseObject = pWidget->FindMouseObject();
    //if our object is same a widget, meaning no children were hit,
    //check if that major object has transparent background, if so, we never really
    //hit any widgets, so our current widget is still the active one and continue
    //searching in case something is on top of us tho.
				if((pMouseObject==pWidget) && (pWidget->IsFlagSet(WF_TRANSPARENTMOUSE)))
				{
					pMouseObject = (CGOBWidget*)this;
					continue;
				}
				break;
			}
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}

    return pMouseObject;
}


void CGOBWidgetParent::Move( INT32 newx, INT32 newy)
{
	FixPos(newx,newy); //Must be called from every WidgetParent's Move() function 
					   //before changing the position.

	CGOBWidget *pWidget = NULL;
	INT32 tmpx = 0;
	INT32 tmpy = 0;

	if((pWidget = m_ActiveList.GetFirst()))
	{
		do
		{
			tmpx = pWidget->m_Pos.x - m_Pos.x + newx;
			tmpy = pWidget->m_Pos.y - m_Pos.y + newy;
			pWidget->Move(tmpx, tmpy);
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}

	pWidget = NULL;
	if((pWidget = m_InActiveList.GetFirst()))
	{
		do
		{
			tmpx = pWidget->m_Pos.x - m_Pos.x + newx;
			tmpy = pWidget->m_Pos.y - m_Pos.y + newy;
			pWidget->Move(tmpx, tmpy);
		}while((pWidget = m_InActiveList.Next(pWidget)));
	}

	SetPos(newx, newy);
}

void CGOBWidgetParent::ActivateChild( CGOBWidget *child )
{
	RemoveInActiveChild(child);
	AddChild(child);
}

void CGOBWidgetParent::DeActivateChild( CGOBWidget *child )
{
	RemoveChild(child);
	AddInActiveChild(child);
}


BOOL CGOBWidgetParent::SetBackgroundImage( const char * filename, UINT32 params )
{
	//clear any previously loaded image
	SAFEDELETE(m_pBGImage);

	//if we never set the filename to NULL, load the file
	if(filename)
	{
		m_pBGImage = new CDXSurface;
		if(!m_pBGImage)
			return FALSE;

		m_pBGImage->Create(GM.GetScreenPtr(), filename);

		SetFlag(params);

		if(params==WF_IMAGESIZE)
		{
			SetSize( m_pBGImage->GetWidth(), m_pBGImage->GetHeight());
		}
	}
	return TRUE;
}


CGOBWidget *CGOBWidgetParent::FindObject(INT16 id)
{
	CGOBWidget *pWidget = NULL;
	if((pWidget = m_ActiveList.GetFirst()))
	{
		do
		{
			if(pWidget->GetID() == id)
			{
				return pWidget;
			}
		}while((pWidget = m_ActiveList.Next(pWidget)));
	}

	return NULL;
}


void CGOBWidgetParent::Center( RECT src )
{
    Move( ((src.right-src.left)>>1)-(m_Size.cx>>1),
          ((src.bottom-src.top)>>1)-(m_Size.cy>>1) );
}


void CGOBWidgetParent::SendMsgToChildren( GOBLIN_MSG msg )
{
	CGOBWidget *pWidget = NULL;
	if(msg==GM_DRAW)
	{
		if((pWidget = m_ActiveList.GetLast()))
		{
			do
			{
				SendMsg(pWidget, GM_DRAW, 0);
				GM.DisplayDebugInfo(pWidget);
			}while((pWidget = m_ActiveList.Prev(pWidget)));
		}
	}
	else
	{
		if((pWidget = m_ActiveList.GetFirst()))
		{
			do
			{
				SendMsg(pWidget, msg, 0);
			}while((pWidget = m_ActiveList.Next(pWidget)));
		}
	}
}

void CGOBWidgetParent::SetLimits(BOOL Limited, INT32 x1, INT32 y1, INT32 x2, INT32 y2)
{
	if (!(m_Limited=Limited)) 
		return;

	 //Default limitation is fullscreen.
 	if (x2==-1)
		x2 = GM.GetScreenPtr()->GetWidth()-m_Size.cx;
	if (y2==-1)
		y2 = GM.GetScreenPtr()->GetHeight()-m_Size.cy;

	m_Limits.top = y1;
	m_Limits.bottom = y2;
	m_Limits.left = x1;
	m_Limits.right = x2;
}

void CGOBWidgetParent::FixPos(INT32 &newx, INT32 &newy)
{
	if (!m_Limited) 
		return; //Unlimited

	//Limited: fix the position
	if (newx < m_Limits.left) 
		newx = m_Limits.left;

	if (newx > m_Limits.right) 
		newx = m_Limits.right;

	if (newy < m_Limits.top) 
		newy = m_Limits.top;

	if (newy > m_Limits.bottom) 
		newy = m_Limits.bottom; 
}

