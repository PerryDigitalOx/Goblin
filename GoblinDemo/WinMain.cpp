#pragma warning (disable : 4244 4201 4514 )

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "App.h"			//for theApp definition

extern void HandleGui(void);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	MSG msg;
    lpCmdLine = NULL;
	hPrevInstance = NULL;

	if(!theApp.Init(hInstance, nCmdShow)) 
        return false;

    if(!theApp.InitializeGame())
        return false;

	while(theApp.m_cState != EXITAPP)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0 )) 
			{
				return msg.wParam;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg);
		}
		else if (theApp.m_bActive)
		{
			theApp.DoPre();             // fix mouse and other things
			HandleGui();
			theApp.DoPost();            // Do mouse and flip and other things.
		}
	}

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
