#include <cdx.h>
#include <cdxsurface.h>
#include "GOBManager.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

#include "CDXFontGDI.h"
#include "CDXFontBitmap.h"

#include "MsgList.h"

CGOBManager GM;				//global manager.


CGOBManager::CGOBManager()			//-666 is the desktop ID
{
	m_ID = -666;
	m_pFocusObject = NULL;
	m_pMouseObject = NULL;
	m_pModalObject = NULL;
	m_IsInited = FALSE;
	m_IsMouseCaptured = FALSE;
	m_pCapturedWidget = NULL;
	m_dwStartTime = 0;
	m_dwToolTipTimer = 0;
	m_dwToolTipDelay = 1000;
	m_pToolTipWidget = NULL;
	m_pPopupWidget = NULL;
	m_IsToolTipActive = FALSE;
	m_EventID = -1;
	m_dwTimeStamp = 0;
	m_WorkspaceColor = -1;
	m_WorkspaceXOff = 0;
	m_WorkspaceYOff = 0;
	m_dwRedrawDelay = 0;
	m_dwLastRedrawTime = 0;

    m_IsArrangeOn = FALSE;
	m_IsDebugManagerOn = FALSE;
	m_DebugList = NULL;

	IsRedrawn = FALSE;

	SetFlag(WF_IMAGE_CENTER);

	m_WorkspaceAnimObj.SetInfo(0,0,20);

    UINT8 i;
    for(i=0; i<10; i++)	{
		m_Font[i] = NULL;
	}
}

CGOBManager::~CGOBManager()
{
	m_IsInited = FALSE;
	Shutdown();
}




void CGOBManager::SetWorkspaceColor(UINT32 color)
{
    m_WorkspaceColor = color;
}

void CGOBManager::DisplayDebugInfo(CGOBWidget *pWidget)
{
#ifdef _DEBUG
	if(m_IsDebugManagerOn) {
		POINT pt = pWidget->GetPos();
		gprintf(pt.x, pt.y, "%d:%d,%d", pWidget->GetID(), pt.x, pt.y);
	}
#endif
}

void CGOBManager::BroadcastMsg(GOBLIN_MSG msg, GOBLIN_PARAM param)
{
	CGOBWidget *pWidget = NULL;

	if(msg == GM_DRAW) {
		if((pWidget = m_ActiveList.GetLast())) {
			do {
				SendMsg(pWidget, GM_DRAW, 0);
				GM.DisplayDebugInfo(pWidget);
			} while((pWidget = m_ActiveList.Prev(pWidget)));
		}
	} else {
		if((pWidget = m_ActiveList.GetFirst())) {
			do {
				SendMsg(pWidget, msg, 0);
			} while((pWidget = m_ActiveList.Next(pWidget)));
		}
	}
}


void CGOBManager::Init( CDXScreen *pScreen, CDXSurface *drawsurface, RECT cliprc )
{
	m_pCDXScreen = pScreen;
	m_pCDXDrawSurface = drawsurface;

	GI.MouseButLeft = 0;
	GI.MouseButMiddle = 0;
	GI.MouseButRight = 0;

    m_pMouseObject = NULL;
    m_pKeyboardObject = NULL;
    m_pLastMouseObject = NULL;
    m_pFocusObject = NULL;
    m_IsInited = TRUE;
	m_dwTimeStamp = 0;

	InitColorSystem();

	SetClip(cliprc);

	m_DebugList = new CGOBMsgList;
	if(m_DebugList)	{
		m_DebugList->Init(drawsurface, 10, 60, 30, 0, 10000);
		m_DebugList->ChangeFont("Arial", 0, 12);
	}

	CDXFontGDI *gdifont = NULL;
	gdifont = new CDXFontGDI;
	gdifont->Create( pScreen, "Arial", 12 );
	AddFont(gdifont);

//	CDXFontBitmap *font = NULL;
//	font = new CDXFontBitmap;
//	font->Create( pScreen, "data\\bigfont.bmp", 32, 32, 64 );
//	AddFont(font);
}




void CGOBManager::InitColorSystem(void)
{
    GC.BLACK = GOBColor(RGB(0, 0, 0));
    GC.WHITE = GOBColor(RGB(255,255,255));
    GC.GRAY7 = GOBColor(RGB(200, 200, 200));
    GC.GRAY247 = GOBColor(RGB(160, 160, 160));
    GC.GRAY248 = GOBColor(RGB(128, 128, 128));
    GC.DARKGRAY = GOBColor(RGB(51, 51, 51));
    GC.RED = GOBColor(RGB(255, 0, 0));
    GC.DARKRED = GOBColor(RGB(102, 0, 0));
    GC.BLUE = GOBColor(RGB(0, 0, 255));
    GC.DARKBLUE = GOBColor(RGB(0, 0, 128));
    GC.ORANGE = GOBColor(RGB(255, 51, 0));
    GC.GREEN = GOBColor(RGB(0, 255, 0));
    GC.DARKGREEN = GOBColor(RGB(0, 128, 0));
    GC.YELLOW = GOBColor(RGB(255, 255, 0));
    GC.DARKYELLOW = GOBColor(RGB(128, 128, 0));
    GC.PURPLE = GOBColor(RGB(102, 0, 102));
    GC.BROWN = GOBColor(RGB(115, 75, 35));
    GC.LIGHTBROWN = GOBColor(RGB(175, 107, 59));
    GC.TEAL = GOBColor(RGB(0, 255, 255));
    GC.PEACH = GOBColor(RGB(255, 255, 102));
    GC.PINK = GOBColor(RGB(255, 51, 204));

	GWC.ActiveTitleBarFace		= GC.BLUE;
	GWC.InActiveTitleBarFace	= GC.BROWN;
	GWC.ActiveWindowFace		= GC.GRAY247;
	GWC.InActiveWindowFace		= GC.GRAY247;
	GWC.ActiveWindowHilight		= GC.GRAY7;
	GWC.ActiveWindowShadow		= GC.DARKGRAY;
	GWC.InActiveWindowHilight	= GC.LIGHTBROWN;
	GWC.InActiveWindowShadow	= GC.BROWN;
	GWC.ButtonFace				= GC.GRAY7;
	GWC.ButtonHilight			= GC.WHITE;
	GWC.ButtonShadow			= GC.GRAY248;
	GWC.ButtonHoverHilight		= GC.GREEN;
	GWC.ButtonHoverShadow		= GC.DARKGREEN;
	GWC.ButtonTextHover			= GC.RED;
	GWC.ButtonTextNormal		= GC.BLACK;
	GWC.ButtonTextSelect		= GC.DARKRED;
	GWC.ButtonTextDisabled		= GC.GRAY248;
	GWC.ButtonTextShadow		= GC.GRAY248;
	GWC.ButtonHilightDisabled	= GC.GRAY247;
	GWC.ButtonFaceDisabled		= GC.GRAY7;
}




GOBLIN_RETVAL CGOBManager::Execute(void)
{
	//if this manager has not been initialized, bail out.
	if(!IsInited())
		return GOBLIN_NOTINITIALIZED;

	//clear event ID
	m_EventID = -1;

	///////////////////////////////////////////////////////
	// Calculate time delays for tooltips etc
    // TimeStamp is created here so that all widgets can
    // get the current time of this frame without having
    // to call timeGetTime() multiple times, thus
    // saving CPU cycles every frame.
	m_dwTimeStamp = timeGetTime();
	if(m_dwStartTime==0) {
		m_dwStartTime = m_dwTimeStamp;
	}
	if(m_dwToolTipTimer==0) {
		m_dwToolTipTimer = m_dwTimeStamp;
	}

    /*
     IDEA - Add a call to a user created object or function pointer.
     This will allow Non Goblin objects to be handled and/or drawn
     before the manager draws itself.  This would be used in the case
     that a 3d scene must be rendered before Goblin draws the gui which
     in most cases resides on top of the rendered scene.

     Although this could be solved by rendering the 3d scene first, then
     calling Goblin, so maybe a layer system should be implemented to allow
     some gui objects to be drawn, then a 3d scene/objects, followed by
     the remaining gui objects.  eg: Goblin backdrop with 3d rendered objects
     on top, and some gui title stuff overlayed.
     */

	///////////////////////////////////////////////////////
	// Manager draws itself before any objects
	//
	OnDraw(0);


	///////////////////////////////////////////////////////
	// new object selection check
	//
	if(m_pLastMouseObject != m_pMouseObject) {
		//if last mouse is different then reset timers
		m_dwToolTipTimer = m_dwTimeStamp;
		m_dwStartTime = m_dwTimeStamp;
	}


	//set last mouse object this frame to current mouse object.
    m_pLastMouseObject = m_pMouseObject;


	///////////////////////////////////////////////////////
	// Mouse capture handling
	//
	if(IsMouseCaptured() && m_pCapturedWidget) {
		m_pMouseObject = m_pCapturedWidget;

		//if mouse object is a valid object
		if (m_pMouseObject != NULL) {
            SendEventMsg(m_pMouseObject, GM_MOUSEMOVE, 0);
		}
	} else {
		if( m_pModalObject ) {
			//search only children of modal object.
			//modal objects should only be CGOBWidgetParents, but not restricted to it.
			m_pMouseObject = m_pModalObject->FindMouseObject();
		} else
			//search for which object mouse is on currently
			m_pMouseObject = FindMouseObject();

        if(m_pMouseObject != m_pLastMouseObject) {
			if(m_IsToolTipActive) {
				m_pToolTipWidget->SetToolTipText(NULL);
				RemoveChild(m_pToolTipWidget);
				m_IsToolTipActive = FALSE;
			}

			if (m_pLastMouseObject != NULL) {
                SendEventMsg(m_pLastMouseObject, GM_LOSTMOUSE, 0);
				if(m_IsDebugManagerOn) {
					if(m_DebugList)
						m_DebugList->Add("%u: %3d - GM_LOSTMOUSE", GetTimeStamp(), m_pLastMouseObject->GetID());
				}
			}

			if (m_pMouseObject != NULL) {
                SendEventMsg(m_pMouseObject, GM_GOTMOUSE, 0);
				if(m_IsDebugManagerOn) {
					if(m_DebugList)
						m_DebugList->Add("%u: %3d - GM_GOTMOUSE", GetTimeStamp(), m_pMouseObject->GetID());
				}
			}
		}
		if(m_pMouseObject != NULL) {
            SendEventMsg(m_pMouseObject, GM_MOUSEMOVE, 0);
        }
	}

	///////////////////////////////////////////////////////
	// Tool Tip Timer handling
	//
	if( (m_dwTimeStamp - m_dwToolTipTimer) > m_dwToolTipDelay && !m_IsToolTipActive) {
		if(m_pMouseObject) {
			ActivateToolTip();
		}
		m_dwToolTipTimer = m_dwTimeStamp;
	}


	///////////////////////////////////////////////////////
	// Left mouse button
	//
	if(GI.MouseButLeft) {
/*
		if(m_pMouseObject->GetParent() && m_pMouseObject->GetParent()->GetID() != -666)
		{
			m_pMouseObject->GetParent()->BringToFront();
		}
*/
		//if mouse last state was not down and this state
		//it is...we have a down click
		if(!GI.OldMouseButLeft)	{
			if(m_IsArrangeOn) {
				CaptureMouse(m_pMouseObject);
			} else {
				if(m_pMouseObject->IsFlagSet(WF_PARENTNOTIFY)) {
					if(m_pMouseObject->GetParent()) {
						SendEventMsg(m_pMouseObject->GetParent(), GM_LBDOWN, (GOBLIN_PARAM)m_pMouseObject);
					}
				} else {
					SendEventMsg(m_pMouseObject, GM_LBDOWN, 0);
				}

				if(m_DebugList)
					m_DebugList->Add("%u: %3d - GM_LBDOWN", GetTimeStamp(), m_pMouseObject->GetID());
			}
		} else {
			if(m_IsArrangeOn) {
				if(IsMouseCaptured()&&m_pCapturedWidget)
					m_pCapturedWidget->Move( m_pCapturedWidget->m_Pos.x+(GI.MousePos.x - GI.OldMousePos.x),
					  m_pCapturedWidget->m_Pos.y+(GI.MousePos.y - GI.OldMousePos.y));
			}
		}
	} else if(GI.OldMouseButLeft) {
		//if our last button was down, but this time it wasn't we have an up button msg.

		if(m_IsArrangeOn) {
			if(IsMouseCaptured())
				ReleaseMouse(m_pCapturedWidget);
		} else {
			if(m_pMouseObject!=NULL) {
				if(m_pMouseObject->IsFlagSet(WF_PARENTNOTIFY)) {
					if(m_pMouseObject->GetParent()) {
						SendEventMsg(m_pMouseObject->GetParent(), GM_LBUP, (GOBLIN_PARAM)m_pMouseObject);
					}
				} else {
					SendEventMsg(m_pMouseObject, GM_LBUP, 0);
				}
			}
			if(m_IsDebugManagerOn) {
				if(m_DebugList&&m_pMouseObject)
					m_DebugList->Add("%u: %3d - GM_LBUP", GetTimeStamp(), m_pMouseObject->GetID());
			}

			if(m_IsPopupActive) {
				if(m_pMouseObject!=m_pPopupWidget) {
					m_IsPopupActive = FALSE;
					RemoveChild(m_pPopupWidget);
					m_pPopupWidget = NULL;
				}
			}
		}
	}

	if(GI.MouseButLeft || GI.MouseButMiddle || GI.MouseButRight) {
		if(m_IsToolTipActive) {
			m_pToolTipWidget->SetToolTipText(NULL);
			RemoveChild(m_pToolTipWidget);
			m_IsToolTipActive = FALSE;
			m_dwToolTipTimer = 0;
		}

		if(m_pFocusObject != m_pMouseObject) {	// focus change
			if(m_pFocusObject != NULL) {
				if(m_pFocusObject != m_pMouseObject->GetParent()) {
                    SendEventMsg(m_pFocusObject, GM_LOSTFOCUS, 0);
					if(m_IsDebugManagerOn) {
						if(m_DebugList)
							m_DebugList->Add("%u: %3d - GM_LOSTFOCUS", GetTimeStamp(), m_pFocusObject->GetID());
					}
                }
			}

			if( m_pMouseObject != NULL ) {
				if (!m_pMouseObject->IsDisabled) {		//if current object is not disabled
					//set keyboard object to same as mouse object
					m_pKeyboardObject = m_pMouseObject;
				}

				m_pFocusObject = m_pMouseObject;
                SendEventMsg(m_pFocusObject, GM_GOTFOCUS, 0);
				if(m_DebugList)
					m_DebugList->Add("%u: %3d - GM_GOTFOCUS", GetTimeStamp(), m_pFocusObject->GetID());
			}
		}
	}

	///////////////////////////////////////////////////////
	// Keyboard
	//
	if( GI.KeyChar ) {
		if(m_pKeyboardObject != NULL) {
			if(GI.KeyChar == VK_RETURN)
				m_pKeyboardObject->HitEnterKey = TRUE;
            SendEventMsg(m_pKeyboardObject, GM_CHAR, GI.KeyChar);
			if(m_DebugList&&m_pFocusObject)
				m_DebugList->Add("%u: %3d - GM_CHAR - %c", GetTimeStamp(), m_pFocusObject->GetID(), GI.KeyChar);
		}
	}

	if (m_pKeyboardObject) {
        //turn off keyboard enters
		m_pKeyboardObject->HitEnterKey = FALSE;
	}

	///////////////////////////////////////////////////////
	// Process and Draw all objects
	//
	BroadcastMsg(GM_PROCESS, 0);

	if(IsInited()) {
		IsRedrawn = FALSE;

		if( m_dwTimeStamp - m_dwLastRedrawTime >= m_dwRedrawDelay) {
			BroadcastMsg(GM_DRAW, 0);
			m_dwLastRedrawTime = m_dwTimeStamp;
			IsRedrawn = TRUE;

			if(m_IsDebugManagerOn)
				DisplayManagerInfo();
		}
	}

	return GOBLIN_SUCCESS;
}




void CGOBManager::Shutdown(void)
{
	m_IsInited = FALSE;
	if(m_pToolTipWidget) {
		RemoveChild(m_pToolTipWidget);
	}

    UINT8 i;
    for(i=0; i<10; i++) {
		SAFEDELETE(m_Font[i]);
	}
	SAFEDELETE(m_pToolTipWidget);

	SAFEDELETE(m_DebugList);

	//special code to make the manager not crash when exit.
	CleanUp();
}




void CGOBManager::CaptureMouse(CGOBWidget *w)
{
	m_IsMouseCaptured = TRUE;
	m_pCapturedWidget = w;
}




void CGOBManager::ReleaseMouse(CGOBWidget *w)
{
	if(m_pCapturedWidget==w) {
		m_pCapturedWidget = NULL;
		m_IsMouseCaptured = FALSE;
	}
}




void CGOBManager::ActivateModal(CGOBWidget *widget)
{
	m_pModalObject = widget;
}




void CGOBManager::DeActivateModal()
{
	m_pModalObject = NULL;
}




void CGOBManager::ActivatePopup(CGOBPopMenu *widget)
{
	//remove the popup if there is one
	if(m_pPopupWidget) {
		RemoveChild(m_pPopupWidget);
		m_IsPopupActive = FALSE;
	}

	m_pPopupWidget = widget;
	//if we have valid popup, place and add.
	if(m_pPopupWidget) {
		m_IsPopupActive = TRUE;
		m_pPopupWidget->Move(GI.MousePos.x, GI.MousePos.y);
		AddChild(m_pPopupWidget);
	}
}




void CGOBManager::SetToolTipWidget(CGOBToolTip *widget)
{
	m_pToolTipWidget = widget;
}




GOBLIN_RETVAL CGOBManager::ActivateToolTip()
{
	if(!m_pToolTipWidget)
		return GOBLIN_NOTINITIALIZED;

	if(m_pMouseObject) {
		m_pToolTipWidget->SetToolTipText(m_pMouseObject->GetToolTipText());
		m_pToolTipWidget->m_Pos.x = m_pMouseObject->m_Pos.x+5;
		m_pToolTipWidget->m_Pos.y = m_pMouseObject->m_Pos.y-25;
		AddChild(m_pToolTipWidget);

		m_IsToolTipActive = TRUE;
	}

	return GOBLIN_SUCCESS;
}




INT16 CGOBManager::GetEvent()
{
	return m_EventID;
}




void CGOBManager::SetEvent(INT16 eventid)
{
	m_EventID = eventid;
}




GOBLIN_RETVAL CGOBManager::OnDraw(GOBLIN_PARAM param)
{
	CDXSurface *surf = GetSurfacePtr();

	if(m_WorkspaceColor!=-1)
		surf->Fill(m_WorkspaceColor);

	if(m_pBGImage) {
		INT32 sw = surf->GetWidth();
		INT32 sh = surf->GetHeight();
		INT32 iw = m_pBGImage->GetWidth();
		INT32 ih = m_pBGImage->GetHeight();

		INT32 x,y;

		if(IsFlagSet(WF_IMAGE_TILE)) {
			if(IsFlagSet(WF_IMAGE_ANIMATED)) {
				if(m_WorkspaceAnimObj.Execute()) {
					m_WorkspaceXOff++;
					m_WorkspaceYOff++;
				}

				if(m_WorkspaceXOff>iw)
					m_WorkspaceXOff = 0;
				if(m_WorkspaceYOff>ih)
					m_WorkspaceYOff = 0;

				for(x=-iw; x<sw; x+=iw) {
					for(y=-ih; y<sh; y+=ih) {
						m_pBGImage->DrawDDBlk(surf, x+m_WorkspaceXOff, y+m_WorkspaceYOff);
					}
				}
			} else {
				for(x=0; x<sw; x+=iw) {
					for(y=0; y<sh; y+=ih) {
						m_pBGImage->DrawDDBlk(surf, x, y);
					}
				}
			}
		} else if(IsFlagSet(WF_IMAGE_CENTER)) {
			x = (sw>>1)-(iw>>1);
			y = (sh>>1)-(ih>>1);

			m_pBGImage->DrawDDBlk(surf, x, y);
		}
	}

	return GOBLIN_SUCCESS;
}



char CGOBManager::AddFont( CDXFontBase *font )
{
	//loop through list of font pointers...if empty one. create font. return index.
	//if no font was created cuz of no empty slots, return -1 (fail)
	UINT8 i;
	for(i=0; i<10; i++)	{
		if(m_Font[i]==NULL) {
			m_Font[i] = font;
			return i;				//if ok, return index
		}
	}
	if(i==0)			//if system font failed, return -1, otherwise 0 for system font default
		return -1;

	//if fail, return 0 (GOBManager default font)
	return 0;
}



void CGOBManager::DisplayManagerInfo(void)
{
#ifdef _DEBUG
	if(m_DebugList)	{
		m_DebugList->Update();
	}
	gprintf( 5, 5, "%d,%d", GI.MousePos.x, GI.MousePos.y);
#endif
}

void CGOBManager::gprintf( INT32 x, INT32 y, const char *msg, ... )
{
#ifdef _DEBUG
    char str[256];
    va_list args; // create variable list

	// format the message
    va_start( args, msg);  // the name of the first variable is "Message"
    vsprintf( str, msg, args); // Store the formatted string with vars in S
    va_end( args); // end of argument list

	CDXSurface *bb = GetSurfacePtr();
	if(bb) {
		HDC hdc = bb->GetDC();
		bb->SetFont();
		bb->TextXY(x+1, y+1, RGB(0,0,0), str);
		bb->TextXY(x, y, RGB(255, 255, 255), str);
		bb->ReleaseDC();
	}
#endif
}
