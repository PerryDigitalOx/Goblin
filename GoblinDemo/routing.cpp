#include "App.h"
#include "routing.h"

//////////////////////////////////////////////////////////////
// Function name : GameRoute
// Description   : Handle ingame specific routing
//////////////////////////////////////////////////////////////
void GameRoute(void)
{
    switch(theApp.m_cSubState)
    {
    case STARTPLAY: // if we are just starting a new game
        //GameInit();
        break;

    case PLAYING:   // If the game is playing update all info...
		//GameLoop(); 
		break;

	case PAUSED: 
		break;

    }
}

//////////////////////////////////////////////////////////////
// Function name : Route
// Description   : Handle application level routing.
//////////////////////////////////////////////////////////////
void Route(void) 
{
    theApp.DoPre();             // fix mouse and other things
    
	switch(theApp.m_cState) 
	{
    case GAME:
        GameRoute();
        break;

    case GUI:
		switch(theApp.m_cSubState)
        {
        case MAINMENU:
			HandleMainMenu();
            break;
        case OPTIONS:
            //MenuOptions();
            break;
        }
		break;

	case EXITAPP:
		//GameKill();
		SendMessage(theApp.GetHWnd(), WM_CLOSE, 0, 0);
        return;
		break;
	}

    theApp.DoPost();            // Do mouse and flip and other things.
}
