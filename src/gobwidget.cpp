#include "GOBManager.h"
#include "GOBWidget.h"
#include "GOBColor.h"			// for color management
#include "GOBInput.h"

CGOBWidget::CGOBWidget()
{
	Initialize();
}

CGOBWidget::Initialize()
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Size.cx = 1;
	m_Size.cy = 1;
	m_pParent = NULL;
	m_dwFlags = 0;
	IsDisabled = FALSE;
	HitEnterKey = FALSE;
	m_pToolTipText = NULL;
	m_ID = -1;
	m_szText.cx = 0;
	m_szText.cy = 0;

	callback = NULL;

	//Text specific
	m_FontIndex = 0;
	m_pText = NULL;
	SetTextColor( GWC.ButtonTextNormal );
	SetTextShadowColor( GWC.ButtonTextShadow );
	SetTextShadowOffset( 0, 0 );

	m_pImage = NULL;
	m_BltType = CDXBLT_BLK;
}


CGOBWidget::~CGOBWidget()
{
	SAFEDELETE(m_pToolTipText);
    DELETEARRAY(m_pText);
	SAFEDELETE(m_pImage);

	if(GM.m_pFocusObject==this)
		GM.m_pFocusObject = NULL;
}

GOBLIN_RETVAL CGOBWidget::SendMsg(CGOBWidget * widget, GOBLIN_MSG msg, GOBLIN_PARAM param)
{
    GOBLIN_RETVAL retval = GOBLIN_NOTINITIALIZED;

    if(widget)
        retval = widget->MessageHandler(msg, param);

    return retval;
}

GOBLIN_RETVAL CGOBWidget::SendEventMsg(CGOBWidget * widget, GOBLIN_MSG msg, GOBLIN_PARAM param)
{
    GOBLIN_RETVAL retval = (GOBLIN_RETVAL)GOBLIN_NOTINITIALIZED;

    if(widget) {
        retval = widget->MessageHandler(msg, param);
        if(widget->callback)
            widget->callback( widget, msg, param);
    }

    return retval;
}

GOBLIN_RETVAL CGOBWidget::MessageHandler(GOBLIN_MSG msg, GOBLIN_PARAM param)
{
	switch(msg)
	{
		HANDLE_GOBLIN_MSG (GM_DRAW, OnDraw);
		HANDLE_GOBLIN_MSG (GM_PROCESS, OnProcess);
		HANDLE_GOBLIN_MSG (GM_LBUP, OnLBUp);
		HANDLE_GOBLIN_MSG (GM_RBUP, OnRBUp);
		HANDLE_GOBLIN_MSG (GM_LBDOWN, OnLBDown);
		HANDLE_GOBLIN_MSG (GM_RBDOWN, OnRBDown);
		HANDLE_GOBLIN_MSG (GM_DCLICK, OnDblClick);
		HANDLE_GOBLIN_MSG (GM_KEY, OnKey);
		HANDLE_GOBLIN_MSG (GM_CHAR, OnChar);
		HANDLE_GOBLIN_MSG (GM_GOTFOCUS, OnGotFocus);
		HANDLE_GOBLIN_MSG (GM_LOSTFOCUS, OnLostFocus);
		HANDLE_GOBLIN_MSG (GM_LOSTMOUSE, OnLostMouse);
		HANDLE_GOBLIN_MSG (GM_GOTMOUSE, OnGotMouse);
		HANDLE_GOBLIN_MSG (GM_MOUSEMOVE, OnMouseMove);
		HANDLE_GOBLIN_MSG (GM_SYSTEM, OnSystemMsg);
		HANDLE_GOBLIN_MSG (GM_EXTERNALEVENT, OnExternalEvent);

     default:
        return GOBLIN_SUCCESS;
	}
}




CGOBWidget *CGOBWidget::FindMouseObject(void)
{
	RECT rc;
	rc.left = m_Pos.x;
	rc.top = m_Pos.y;
	rc.right = rc.left + m_Size.cx;
	rc.bottom = rc.top + m_Size.cy;

	if(PtInRect(&rc, GI.MousePos))
		return this;

	return NULL;
}


void CGOBWidget::Move( INT32 newx, INT32 newy)
{
	SetPos(newx, newy);
}


BOOL CGOBWidget::CreateSprites( const char * filename, INT32 width, INT32 height, INT16 num)
{
	m_pImage = new CDXSprite(GM.GetScreenPtr(), filename, width, height, num, CDXMEM_SYSTEMONLY);
	if(!m_pImage)
		return FALSE;

	m_Size.cx = width;
	m_Size.cy = height;

	return TRUE;
}


void CGOBWidget::SetToolTipText( char * string )
{
    DELETEARRAY(m_pToolTipText);

	if(string==NULL)
		return;

	m_pToolTipText = new char[strlen(string)+1];
	if(m_pToolTipText)
	{
		strcpy(m_pToolTipText, string);
	}
}

