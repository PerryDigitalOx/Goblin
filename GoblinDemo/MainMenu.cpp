#include "app.h"
#include "MainMenu.h"
#include <GOBScrollBar.h>
#include <GOBButtonMasked.h>
#include <GOBColor.h>			// for color management


CMainMenu::CMainMenu()
{
	int i=0;
	CGOBButton *wa = NULL;
	tooltip = new CGOBToolTip;
	CGOBPanel *notepad;

	GM.SetWorkspaceColor( GC.BLACK );
	//GM.SetWorkspaceImage( "data\\guibgsm.bmp", WS_IMAGE_CENTER );
	//GM.SetWorkspaceImage( "data\\guibgsm.bmp", WS_IMAGE_TILE );
	GM.SetBackgroundImage("data\\guibgsm.bmp", WF_IMAGE_TILE | WF_IMAGE_ANIMATED );

	GM.SetToolTipWidget( tooltip );
	
	//CGOBSlider *hslider;
	//CGOBSlider *bslider;


	CGOBButtonMasked *iconbtn;
	iconbtn = new CGOBButtonMasked;
	iconbtn->CreateSprites( "data\\iconbutton.bmp", 64, 64, 4);
	iconbtn->Move(450,50);
	iconbtn->SetBltType(CDXBLT_TRANS);
	iconbtn->GetImagePtr()->SetColorKey();
	iconbtn->SetToolTipText("Example of CGOBButtonMasked");


	CGOBComboBox *combo;
	CGOBButton *netitem[4];

	combo = new CGOBComboBox;

	combo->SetPos(0,0);
	combo->SetSize(120,20);

	for(i=0; i<4; i++)
	{
		netitem[i] = new CGOBButton;
		netitem[i]->SetPos(0,0+(i*20));
		netitem[i]->SetSize(100,18);
		netitem[i]->SetFontIndexToUse(theApp.GuiFont);
		netitem[i]->SetID(COMBO_1+i);
		netitem[i]->SetFlag(WF_TRANSPARENTBG|WF_PARENTNOTIFY);
		combo->AddChild( netitem[i] );
	}
	netitem[0]->SetText("Intranet");
	netitem[1]->SetText("Internet");
	netitem[2]->SetText("Favourites");
	netitem[3]->SetText("History");

	combo->Move(20,250);
	combo->SetToolTipText("Combo box example");

	wa = new CGOBButton;
	editbox = new CGOBEditBox;
	checkbox = new CGOBCheckBox;
	panel = new CGOBPanel;
	notepad = new CGOBPanel;
	frame = new CGOBFrame;
	popmenu = new CGOBPopMenu;
	stxt = new CGOBStaticText;
	stxt->SetText("This is a Panel Widget");
	stxt->SetTextColor(GOBColor(RGB(255,0,255)));
	simg = new CGOBStaticPic;


	CGOBScrollBar *scroll;
	scroll = new CGOBScrollBar;
	scroll->SetSize(16,250);
	scroll->SetThumbSize(16,32);
	scroll->SetRange(0, 10);

	CGOBButton *sbartop = NULL;
	CGOBButton *sbarbot = NULL;
	sbartop = new CGOBButton;
	sbarbot = new CGOBButton;
	sbartop->SetSize(16,16);
	sbarbot->SetSize(16,16);
	scroll->SetFirstButton(sbartop);
	scroll->SetSecondButton(sbarbot);

	scroll->SetThumbPos(0,20);
	scroll->Move(250,10);


/*	
	hslider = new CGOBSlider;
	bslider = new CGOBSlider;

	hslider->SetSize(256, 32);
	hslider->SetThumbSize(8, 32);
	hslider->SetRange(0, 10);
	hslider->Move(100,300);

	bslider->SetSize(128,128);
	bslider->SetThumbSize(16,16);
	bslider->SetRange(0, 5);
	bslider->Move(400,250);
*/

	bmpbtn = new CGOBButton;
	bmpbtn->SetPos(550,420);
	bmpbtn->SetSize(50,50);
	bmpbtn->CreateSprites("data\\exit.bmp", 68, 38, 3);
	bmpbtn->SetID(ID_EXITAPP);
	bmpbtn->SetToolTipText( "Exit the app" );

	popmenu->SetPos(0,0);
	//popmenu->SetSize(60,100);

	this->SetPos(0,0);
	this->SetSize(640,480);
	this->SetFlag(WF_TRANSPARENTBG);
	this->SetFlag(WF_TRANSPARENTMOUSE);

	for(i=0; i<4; i++)
	{
		MainMenuItem[i] = new CGOBButton;
		MainMenuItem[i]->SetPos(100,50+(i*40));
		MainMenuItem[i]->SetSize(350,30);
		MainMenuItem[i]->SetFontIndexToUse(theApp.GuiFont);
		this->AddChild( MainMenuItem[i] );
	}
	MainMenuItem[0]->SetID(MM_OP1);
	MainMenuItem[1]->SetID(MM_OP2);
	MainMenuItem[2]->SetID(MM_OP3);
	MainMenuItem[3]->SetID(MM_OP4);
	MainMenuItem[0]->SetText("Panel with Widgets");
	MainMenuItem[1]->SetText("Frame with Widgets");
	MainMenuItem[2]->SetText("Nothing");
	MainMenuItem[3]->SetText("Exit App");

	for(i=0; i<4; i++)
	{
		PopItem[i] = new CGOBButton;
		//PopItem[i]->SetPos(0,(i*20));
		//PopItem[i]->SetPos(0,0);
		PopItem[i]->SetSize(190,40);
		PopItem[i]->SetFlag(WF_TRANSPARENTBG);
		popmenu->AddChild( PopItem[i] );
	}
//	PopItem[1]->SetSize(190,40);
	PopItem[0]->SetID(PM_OP1);
	PopItem[1]->SetID(PM_OP2);
	PopItem[2]->SetID(PM_OP3);
	PopItem[3]->SetID(PM_OP4);
	PopItem[0]->SetText("Toggle AnimBG");
	PopItem[1]->SetText("Center BG");
	PopItem[2]->SetText("(Nothing)");
	PopItem[3]->SetText("Exit App");

	wa->SetPos(60,60);
	wa->SetSize(150,50);

	editbox->SetPos(10,20);
	editbox->SetSize(250,20);

	checkbox->SetPos(10,80);
	checkbox->SetSize(16,16);
	checkbox->SetText("Check Box");
	checkbox->SetFontIndexToUse(theApp.GuiFont);
	checkbox->SetToolTipText( "Check Box ToolTip here!...");

	simg->CreateSprites("data\\amulets.bmp", 64,64,10);
	simg->SetPos(300,10);
	simg->GetImagePtr()->SetColorKey();
	simg->SetBltType(CDXBLT_TRANS);

	notepad->SetSize(350,350);
	notepad->SetToolTipText( "Example of scrollbar used in a panel.");
	notepad->AddChild(scroll);

	panel->SetPos(0,0);
	panel->SetSize(350,250);
	panel->SetBackgroundImage( "data\\panelbg.bmp", WF_IMAGESIZE );
	panel->SetToolTipText( "Panel example" );


	for(i=0; i<5; i++)
	{
		radio[i] = new CGOBRadioButton;
		panel->AddChild(radio[i]);
		radio[i]->SetPos(100,50+(i*20));
		radio[i]->SetGroupID(1);
		radio[i]->SetText("Radio Button");
	}
	radio[3]->SetGroupID(2);
	radio[4]->SetGroupID(2);
	radio[4]->SetState(STATE_CHECKED);
	radio[0]->SetState(STATE_CHECKED);
	radio[3]->SetPos(20,150);
	radio[4]->SetPos(20,170);

	stxt->Move(5,5);
	panel->AddChild(stxt);
	panel->AddChild(editbox);
	panel->AddChild(checkbox);

	frame->SetPos(0,0);
	frame->SetSize(400,300);
	frame->SetText("Test Dialog 1");
	frame->SetBackgroundImage( "data\\framebg.bmp", WF_IMAGESIZE );

	frame->AddChild(wa);
	frame->AddChild(simg);
	frame->Move(50,100);


	GM.AddChild(bmpbtn);

	/*	
	GM.AddChild(hslider);
	GM.AddChild(bslider);
	*/
	GM.AddChild(notepad);
	GM.AddChild(combo);
	GM.AddInActiveChild(panel);
	GM.AddInActiveChild(frame);
	
	GM.AddChild(iconbtn);
	
	GM.AddChild(this);
}

CMainMenu::~CMainMenu()
{
}
