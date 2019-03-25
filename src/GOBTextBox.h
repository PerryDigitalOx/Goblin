#ifndef CGOBTEXTBOX_H
#define CGOBTEXTBOX_H

#include "GOBWidgetParent.h"

/*
CGOBTextBox is a widget that displays more than one line, at a limited area. The class divides the text to lines whenever 
SetText() is called. Whenever the TextBox has more lines than it can display, and the mouse is on it, it scrolls down.
When the mouse leaves the TextBox, the TextBox scrolls to the first line.

  NOTE: THE CLASS IS NOT YET FINISHED.
  Will be implemented:
  --------------------
  * Auto surface creation.
  * Define/Use align values (Left/Middle/Right)
  * Maybe completely remove the need of surfaces (although, it's faster)
  * Flexiblity.
*/

class CGOBTextBox : public CGOBWidgetParent
{
public:
	// Set default values.
	CGOBTextBox();
	
	// handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBDown(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnMouseMove (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostMouse (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnGotMouse (GOBLIN_PARAM param);
	void SetText(char * newtext );
	void SetAlignment(BOOL Left) {m_Alignment=Left;}
	UINT32 DivideLines(char* Input, BOOL SurfaceCreation = TRUE);
	void SetColors(UINT32 NormalColor=0,UINT32 OnMouseColor=0,UINT32 OnClickColor=0,UINT32 DisabledColor=0);
	
private:
	BOOL m_IsDown,				// Flag for mouse down state
		m_IsHover,				// Flag for mouse over state
		m_Alignment;           // true -> align to the left. false-> align to the right.
	UINT32  m_HoverFrames;         //from 0 to 30 frames
	UINT32  m_NormalColor,      // Color for normal state
		m_OnMouseColor,     // Color for mouse over state
		m_OnClickColor,     // Color for mouse down state
		m_DisabledColor;    // Color for disabled state
	
	CDXSurface *m_NormalSurface,  //Surface for normal state
		*m_OnMouseSurface, //Surface for mouse over state
		*m_OnClickSurface, //Surface for mouse down state
		*m_DisabledSurface;//Surface for disabled state
	
	char m_Lines  [100][100], m_LinesNum, m_LineVSize;
	INT32 m_FirstY;
	AnimObj *m_Timer;
	
	
private:
	void ResetLines();
	void AddLine(char* Line);	
	void CreateSurfaces();
};
#endif