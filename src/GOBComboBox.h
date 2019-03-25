#ifndef GOBCOMBOBOX_H
#define GOBCOMBOBOX_H

#include "GOBWidgetParent.h"

/*
ComboBox can contain children buttons.  (NOT COMPLETE)
*/

class CGOBComboBox : public CGOBWidgetParent
{
public:
	// Set default values
	CGOBComboBox();

	// Handlers
	GOBLIN_RETVAL OnDraw (GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLBUp(GOBLIN_PARAM param);
	GOBLIN_RETVAL OnLostFocus(GOBLIN_PARAM param);

	// Move widget and all children.
	void Move(INT32 newx, INT32 newy);
	
	// Set text displayed in combo box top.
	void SetText( const char * newtext);

	INT32 GetSelectedChildID();
	void SelectChild(INT32 Child_ID);

private:
	CGOBWidget *	m_pSelectedChild;		// Pointer to selected widget.
	BOOL			IsOpen;					// Flag specifies if combo is open (dropped down).
	INT32			m_OrigHeight;			// original height of combo box before its open.
	INT32			m_ThumbWidth;			// width of combo button
};

#endif
