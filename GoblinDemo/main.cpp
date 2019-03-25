#include "App.h"
#include "mainmenu.h"
#include "GOBInput.h"

static CMainMenu *pMainMenu = NULL;


void HandleGui(void)
{
	CDXSurface *bb = theApp.m_pScreen->GetBack();
    if(!bb)
        return;
	
	if(pMainMenu)
	{
		//must setup some stuff in GI 
		GI.MousePos = theApp.m_ptCursorPos;
		GI.OldMousePos = theApp.m_ptCursorOldPos;
		GI.OldMouseButLeft = GI.MouseButLeft;
		GI.OldMouseButRight = GI.MouseButRight;
		GI.KeyChar = theApp.m_LastKey;
		theApp.m_LastKey = 0;
		
		if(theApp.m_dwMouseStatus & RMB_DEDGE)
			GI.MouseButRight = 1;
		else
			if(!(GI.MouseButRight &&  theApp.m_dwMouseStatus & RMB_DOWN))
				GI.MouseButRight = 0;

		if(theApp.m_dwMouseStatus & LMB_DEDGE)
		{
			GI.MouseButLeft = 1;
		}
		else
		{
			if(!(GI.MouseButLeft  &&  theApp.m_dwMouseStatus & LMB_DOWN))
				GI.MouseButLeft = 0;
		}
		
		//////////////////////////////////////////////////////////////
		GM.Execute();
		//////////////////////////////////////////////////////////////
		
		
		switch(GM.GetEvent())
		{
		case MM_OP1:
			GM.ActivateChild(pMainMenu->panel);
			pMainMenu->panel->Move(10,10);
			break;
		case MM_OP2:
			GM.ActivateChild(pMainMenu->frame);
			break;

		case PM_OP1:
			{
				if( GM.IsFlagSet( WF_IMAGE_ANIMATED|WF_IMAGE_TILE ) )
					GM.RemoveFlag( WF_IMAGE_ANIMATED );
				else
					GM.SetFlag( WF_IMAGE_TILE | WF_IMAGE_ANIMATED );
			}
			break;

		case PM_OP2:
			GM.RemoveFlag( WF_IMAGE_TILE|WF_IMAGE_ANIMATED );
			GM.SetFlag( WF_IMAGE_CENTER );
			break;

		case PM_OP4:
		case MM_OP4:
		case ID_EXITAPP:
			{
				GM.Shutdown();
				theApp.m_cState = EXITAPP;
			}
			return;
		}
		
		if(theApp.m_dwMouseStatus & RMB_UEDGE)
		{
			GM.ActivatePopup(pMainMenu->popmenu);
		}
	}
	else
	{
		pMainMenu = new CMainMenu();
	}
	
	//////////////////////////////////////////////////////////////
}
