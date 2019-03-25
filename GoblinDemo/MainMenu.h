#if !defined(AFX_MAINMENU_H__D4A36CE2_8869_11D3_ABCB_0050043E949C__INCLUDED_)
#define AFX_MAINMENU_H__D4A36CE2_8869_11D3_ABCB_0050043E949C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <gobmanager.h>
#include <gobmenu.h>
#include <gobeditbox.h>
#include <gobcheckbox.h>
#include <gobcombobox.h>
#include <gobpanel.h>
#include <gobframe.h>
#include <gobradiobutton.h>
#include <gobbutton.h>
#include <gobstaticpic.h>
#include <gobstatictext.h>
#include <gobimage.h>

enum _menuIDS {
	ID_EXITAPP = 1,
	MM_OP1,
	MM_OP2,
	MM_OP3,
	MM_OP4,
	PM_OP1,
	PM_OP2,
	PM_OP3,
	PM_OP4,
	COMBO_1,
	COMBO_2,
	COMBO_3,
	COMBO_4,
	ID_TOTAL			//last item to store count of items
};

class CMainMenu : public CGOBMenu  
{
public:
	CMainMenu();
	virtual ~CMainMenu();

public:
	CGOBToolTip *tooltip;
	CGOBEditBox *editbox;
	CGOBCheckBox *checkbox;
	CGOBPanel *panel;
	CGOBFrame *frame;
	CGOBRadioButton *radio[5];
	CGOBButton *bmpbtn;
	CGOBButton *MainMenuItem[4];
	CGOBButton *PopItem[4];
	CGOBPopMenu *popmenu;
	CGOBStaticPic *simg;
	CGOBStaticText *stxt;
};

#endif // !defined(AFX_MAINMENU_H__D4A36CE2_8869_11D3_ABCB_0050043E949C__INCLUDED_)
