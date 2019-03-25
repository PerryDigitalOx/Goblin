#ifndef CGOBWIDGETPARENT_H
#define CGOBWIDGETPARENT_H

#include <cdxtypes.h>
#include <CDXCList.h>
#include "GOBWidget.h"

class CDXSurface;
/*
WidgetParent is a parent class to children widgets.  Only a parent can have children.
This would be menus, panels, frames, etc.  Since parents usually contain groups of
items it can have a background image associated using CGOBImage.
*/

class CGOBWidgetParent : public CGOBWidget
{
public:
	//Set default values
	CGOBWidgetParent();
	//Remove all children and deletes all childrens data.
	//Both active and inactive lists are processed.
	~CGOBWidgetParent();

	// Add widget to active list.
	void		AddChild(CGOBWidget *widget);
	// Add widget to inactive list.
	void		AddInActiveChild(CGOBWidget *widget);

	// Remove widget from active list.
	void		RemoveChild(CGOBWidget *widget);
	// Remove widget from inactive list.
	void		RemoveInActiveChild(CGOBWidget *widget);

	// Move this widget and all children widgets along with it.
	void		Move( INT32 newx, INT32 newy);

	// Limits the movement of the widgetparent and it's children
	void SetLimits(BOOL Limited = FALSE, INT32 x1=0, INT32 y1=0, INT32 x2=-1, INT32 y2=-1);

	// Set the backgound image and parameters
	BOOL		SetBackgroundImage( const char * filename, UINT32 params = NULL );

	//centers this widget within passed rect size
	void		Center( RECT src );

	void		SendMsgToChildren( GOBLIN_MSG msg );

	// This will search children widgets and if a child is a
	// parent it will search its children and so on...
	// CGOBWidget::FindMouseObject is optimized and doesn't
	// check for children since CGOBWidget is a child only.
	CGOBWidget	*FindMouseObject(void);
	// Find an object using its ID.  Returns pointer to widget.
	CGOBWidget	*FindObject(INT16 id);

	// Move inactive child from inactive list to active list.
	void		ActivateChild( CGOBWidget *child );
	// Move active child from active list to inactive list.
	void		DeActivateChild( CGOBWidget *child );

	// Linked list of children widgets. This list is only a list of pointers.
	// objects do not get destroyed automatically when removed from list.
    CDXCList <class CGOBWidget> m_ActiveList;

	// Linked list of inactive children widgets.
	// this is used to add children but not to the scene, which
	// allows automatic cleanup by the destructor.
    CDXCList <class CGOBWidget> m_InActiveList;

protected:
	// Background image for this parent
	CDXSurface *m_pBGImage;

	void		CleanUp(void);

	RECT        m_Limits;    
	BOOL        m_Limited; //If false, then m_Limits is ignored.

	// A small addition for the Move() function at the beginning of the handler
	void        FixPos(INT32 &newx, INT32 &newy);
};

#endif
