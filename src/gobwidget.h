#ifndef CGOBWIDGET_H
#define CGOBWIDGET_H

#include <cdxsprite.h>
#include <cdxtypes.h>
#include "gobdefs.h"

class CGOBWidget;
class CGOBWidgetParent;


/*
Widget is the base class of all widgets.
Widgets have position, size, flags, IDs, text routines, tooltip text,
and image capability using CDXSprite.
*/

class CGOBWidget
{
public:
	//set default information
    CGOBWidget();
	//free up allocated memory
    ~CGOBWidget();

	POINT		m_Pos;					//widget position
	SIZE		m_Size;					//widget size
	UINT32		m_dwFlags;				//widget flags

	// Set flags.  This will use Logical OR to add the flag.
	void		SetFlag( UINT32 flag )						{ m_dwFlags |= flag; }
	// Remove flags.  This will use Logical AND of the EXCLUSIVE flag, which removes only that flag.
	void		RemoveFlag( UINT32 flag )					{ m_dwFlags &= ~flag; }
	// Checks if flag is set using Logical AND to check flag.
	BOOL		IsFlagSet( UINT32 flag )						{ return m_dwFlags&flag; }

	// Flag used to check if widget is disabled.  (SHOULD BE CHANGED TO USE FLAGS)
	BOOL IsDisabled;
	// Flag used to check if enter key was hit. (NOT USED)
	BOOL HitEnterKey;

	// Get this widgets event ID.
	INT16 GetID()											{ return m_ID; }
	// Set this widgets event ID.
	void SetID( INT16 id )									{ m_ID = id; }

	// See if mouse is on this widget.
	virtual CGOBWidget *FindMouseObject(void);

	// Bring this widget to the front of the drawing/processing list.
	virtual void BringToFront(void) {};

	// Moves widget to new position and all children widgets with parent
	virtual void Move( INT32 newx, INT32 newy );

	// Initialization position and size calls.
	// These do not change children widgets
	GOBLIN_RETVAL SetPos( INT32 x, INT32 y)			
			{ m_Pos.x = x; m_Pos.y = y; return GOBLIN_SUCCESS; }
	GOBLIN_RETVAL SetSize( INT32 w, INT32 h)		
			{ m_Size.cx = w; m_Size.cy = h; return GOBLIN_SUCCESS; }

	POINT GetPos()		{ return m_Pos; }

	// Get a WidgetParent pointer to the parent of this widget.
	CGOBWidgetParent	*GetParent()							{ return m_pParent; }
	// Sets this widgets parent.
	void				SetParent(CGOBWidgetParent *parent)		{ m_pParent = parent; }

	// Return the tooltip text associated with this widget
	char *		GetToolTipText(void)						{ return m_pToolTipText; }
	// Set the tooltip text for this widget
	void		SetToolTipText(char * string);

	/////////////////////////////////////////////////////
	// Text specific stuff
	//
	void		SetTextColor(UINT32 rgb)						{ m_TextColor = rgb; }
	UINT32		GetTextColor()								{ return m_TextColor; }
	void		SetTextShadowColor(UINT32 rgb)				{ m_TextShadowColor = rgb; }
	UINT32		GetTextShadowColor()						{ return m_TextShadowColor; }
	void		SetTextShadowOffset( INT16 x, INT16 y )		{ m_TextShadow.x = x; m_TextShadow.y = y; }
	void		SetFontIndexToUse( char index )				{ m_FontIndex = index; }
	char		GetFontIndexToUse()							{ return m_FontIndex; }

	// Get the text associated with this widget
	virtual char *GetText(void)								{ return m_pText; };

	// Change the text associated with this widget
	// Allocation of text is internal to widget.
	// User can trash their own pointer after this call.
	virtual void SetText( char *) {};

	// Get the CDX blitting type.
	WORD GetBltType()										{ return m_BltType; }
	// Set the CDX blitting type.
	void SetBltType(WORD a)									{ m_BltType = a; }

	// Get the CDXSprite pointer for this widget.  (SHOULD USE CGOBImage)
	CDXSprite *GetImagePtr()								{ return m_pImage; }

	BOOL CreateSprites( const char * filename, INT32 width, INT32 height, INT16 num);

	BOOL (*callback)( CGOBWidget *widget, GOBLIN_MSG msg, GOBLIN_PARAM param );

protected:
	// up to 32768 for ID.  Used to set events from actions
	INT16		m_ID;

	//the parent widget if there is one
	CGOBWidgetParent *m_pParent;

	// Initialize internals.  Called by constructor only
	Initialize();

	//Text specific
	char *		m_pText;				//miscellaneous text associated with this widget
	SIZE		m_szText;				//dimensions of text using current font
	UINT32		m_TextColor;			//color of text
	UINT32		m_TextShadowColor;		//color of shadow
	POINT		m_TextShadow;			//shadow offset for text
	char		m_FontIndex;			//index of font into managers font table
	char *		m_pToolTipText;			//points to tool tips text string

	// CDXSprite image pointer.
	CDXSprite*	m_pImage;
	// CDX Blitting method.
	WORD		m_BltType;

public:
	// Send a specific message to a specific widget.  Use Internally.
    GOBLIN_RETVAL SendMsg(CGOBWidget * widget, GOBLIN_MSG msg, GOBLIN_PARAM param);
    GOBLIN_RETVAL SendEventMsg(CGOBWidget * widget, GOBLIN_MSG msg, GOBLIN_PARAM param);

private:
	// Handles messages for this widget
	GOBLIN_RETVAL MessageHandler(GOBLIN_MSG msg, GOBLIN_PARAM param);

protected:
    virtual GOBLIN_RETVAL   OnDraw (GOBLIN_PARAM)             { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnLBDown (GOBLIN_PARAM)           { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnLBUp (GOBLIN_PARAM)             { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnRBDown (GOBLIN_PARAM)           { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnRBUp (GOBLIN_PARAM)             { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnDblClick (GOBLIN_PARAM)         { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnKey (GOBLIN_PARAM)              { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnChar (GOBLIN_PARAM)             { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnGotFocus (GOBLIN_PARAM)         { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnLostFocus (GOBLIN_PARAM)        { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnGotMouse (GOBLIN_PARAM)         { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnLostMouse (GOBLIN_PARAM)        { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnProcess (GOBLIN_PARAM)          { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnMouseMove (GOBLIN_PARAM)        { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnSystemMsg (GOBLIN_PARAM)        { return GOBLIN_NOTIMPLEMENTED; }
    virtual GOBLIN_RETVAL   OnExternalEvent (GOBLIN_PARAM)    { return GOBLIN_NOTIMPLEMENTED; }


public:
    CGOBWidget* GetNext(void)   { return m_Next; }
    CGOBWidget* GetPrev(void)   { return m_Prev; }
    void SetNext(CGOBWidget* T) { m_Next = T; }
    void SetPrev(CGOBWidget* T) { m_Prev = T; }

private:
    CGOBWidget* m_Next;
    CGOBWidget* m_Prev;

};


#endif
