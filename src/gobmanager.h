#ifndef CGOBMANAGER_H
#define CGOBMANAGER_H

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <cdx.h>
#include <cdxsurface.h>
#include "AnimObj.h"
#include "GOBPopMenu.h"
#include "GOBToolTip.h"
#include "CDXFontBase.h"
#include "CDXFontGDI.h"

class CGOBMsgList;

/*
Manager is the most important part of Goblin.  The manager is used in many of the widgets
as a main global controlling widget.  Its equivalent to say that the manager is like a
desktop.  Manager is the main widgetparent which contains all other widgets.  All widgets
should be added to the manager using GM.AddChild() or GM.AddInActiveChild().

Manager can have a background image with different tiling modes.  Center, Tiled, or Scrolling Tiled.

Every game cycle GM.Execute() must be called to handle any processing and drawing of the
entire Goblin system.

The global GI (Goblin Input) structure must be filled in appropriatly to allow the manager
to handle any actions.

Manager also has an event mechanism.  All widgets have an ID value.  On specific actions this ID
triggers an event in the manager.  Checking for events every cycle using GM.GetEvent() will return
an event ID that was triggered.

For example; a button widget will send its event ID when the
user clicks on it using the mouse.

Manager is made with all the basic functionality but allows a simpler and easier
to look at class if derived upon.

Manager handles tooltips automatically.  To have tooltips in your application, create
a tooltip widget and set it as the active tooltip widget in the manager.
GM.AddToolTipWidget() allows adding a created tooltip widget to the manager.  Only
one tooltip can be active at a time.  Manager will display the tooltip widget with
the tooltip text of the widget the mouse cursor is over after the tooltip timeout delay.
*/
class CGOBManager : public CGOBWidgetParent
{
public:
	CGOBManager();
	virtual ~CGOBManager();

	//CGOBWidget *m_CurrentObject;
	CGOBWidget *m_pMouseObject;
	CGOBWidget *m_pLastMouseObject;
	CGOBWidget *m_pKeyboardObject;
	CGOBWidget *m_pFocusObject;
	CGOBWidget *m_pModalObject;

	// Set the tooltip widget associated with the manager.
	void SetToolTipWidget(CGOBToolTip *widget);
	// Activate a popup menu widget.  Special case handling for this item.
	void ActivatePopup(CGOBPopMenu *widget);
	// Activate a modal widget.  No other widget is processed for mouse messages
	// until modal widget is removed.
	void ActivateModal(CGOBWidget *widget);
	// Disables the modal widget.
	void DeActivateModal();

	// Initialize Goblin manager with screen, drawing surface, and clipping rectangle.
	void Init( CDXScreen *screen, CDXSurface *drawbuffer, RECT cliprc );

	// Send a message to all widgets, recursively.
	void BroadcastMsg(GOBLIN_MSG msg, GOBLIN_PARAM param);

	// Manager handler to be called every cycle.
	GOBLIN_RETVAL Execute(void);

	void SetWorkspaceColor( UINT32 color );
	RECT GetClip(void)								{ return m_ClipRect; }
	void SetClip(RECT rc)							{ m_ClipRect = rc; }
	BOOL IsInited(void)								{ return m_IsInited; }

	void Shutdown(void);
	void CaptureMouse(CGOBWidget *w);
	void ReleaseMouse(CGOBWidget *w);
	BOOL IsMouseCaptured(void)						{ return m_IsMouseCaptured; }

	INT16 GetEvent();
	void SetEvent(INT16 eventid);

	UINT32	GetTimeStamp()							{ return m_dwTimeStamp; }

	//char AddFont( const char *fontname, int size );
	char AddFont( CDXFontBase *font );

	CDXSurface	*GetSurfacePtr()					{ return m_pCDXDrawSurface; }
	CDXScreen	*GetScreenPtr()						{ return m_pCDXScreen; }
	CDXFontBase	*m_Font[10];

	void		SetRedrawRate(UINT32 msdelay)		{ m_dwRedrawDelay = msdelay; }
	UINT32		GetRedrawRate()						{ return m_dwRedrawDelay; }
	BOOL		IsRedrawn;

	BOOL		IsArrangeOn()		{ return m_IsArrangeOn; }
	void		SetArrange(BOOL t)	{ m_IsArrangeOn = t; }
	void		DisplayDebugInfo(CGOBWidget * pWidget);

private:
	UINT32		m_dwWorkspaceImageParms;				//our workspace image parameters, 'Center, Tiled, etc.'

	GOBLIN_RETVAL		OnDraw (GOBLIN_PARAM param);	//our OnDraw function to draw the workspace

	GOBLIN_RETVAL	ActivateToolTip();					//when tooltip needs to be active, this func is called
	UINT32		m_dwToolTipTimer;						//internal timer for tool tip.
	UINT32		m_dwToolTipDelay;						//tool tip activation delay
	CGOBToolTip *m_pToolTipWidget;						//tool tip widget.  this points to user created tool tip widget
	BOOL		m_IsToolTipActive;						//flag specifies if tool tip is currently active

	INT16		m_EventID;								//global event ID sent by any other object
	RECT		m_ClipRect;								//our clipping rect of the workspace
	BOOL		m_IsInited;								//flag specifies if manager has been initialied
	UINT32		m_WorkspaceColor;						//our workspace color in RGB

	UINT32		m_dwStartTime;							//in ms
	UINT32		m_dwTimeStamp;							//time in MS when this drawing frame started

	CGOBPopMenu *m_pPopupWidget;						//popup menu widget.  points to user create popup widget
	BOOL		m_IsPopupActive;						//flag specifies if popup menu is active at the moment.

	BOOL		m_IsMouseCaptured;						//flag specifies if mouse is captured by a specific widget
	CGOBWidget	*m_pCapturedWidget;						//points to widget that has mouse capture

	HDC			m_HDC;									//handle to DC of workspace.  steering away from needing this.

	void InitColorSystem(void);							//initializes the global color structures

	// The following is for the workspace display and processing.
	AnimObj		m_WorkspaceAnimObj;						//Workspace AnimObj to handle scrolling background
	UINT32		m_dwRedrawDelay;						//redraw delay in milliseconds
	UINT32		m_dwLastRedrawTime;						//last redraw time

	INT32		m_WorkspaceXOff;						//X pixel offset of workspace image
	INT32		m_WorkspaceYOff;						//Y pixel offset of workspace image
	CDXScreen  *m_pCDXScreen;							//CDXScreen pointer
	CDXSurface *m_pCDXDrawSurface;						//CDXSurface that the workspace draws too

	// The following is for debug infomation for the developers.
	// This allows the developer to get run-time information
	// easier and faster then using the debugger.
	BOOL		m_IsDebugManagerOn;								//flag stating that debug manager is enabled/disabled
	void		DisplayManagerInfo(void);						//manager infomation
	void		gprintf( INT32 x, INT32 y, const char *msg, ... );	//manager printf for manager infomation
	CGOBMsgList	*m_DebugList;
	BOOL		m_IsArrangeOn;
};

extern CGOBManager GM;			//our global Goblin Manager

#endif
