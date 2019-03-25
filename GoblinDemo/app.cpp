#include <windows.h>
#define CDXINCLUDEALL     // this define includes all headers, otherwise include one by one
#include <cdx.h>
#include <gobmanager.h>

#include "resource.h"

#include "App.h"
#include <time.h>

#define MOUSE_SINGLEFRAME_FLAGS   (LMB_DCLICK|RMB_DCLICK|LMB_DCLICK|LMB_UEDGE|MMB_UEDGE|RMB_UEDGE|LMB_DEDGE|MMB_DEDGE|RMB_DEDGE)

CApp theApp;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CApp::CApp()
{
	strcpy(szAppName, "GUI");
    strcpy(szAppClassName, "GUIClass");

	GuiFont = 0;
	m_hInst = NULL;

    m_sizeScreen.cx = DEFAULT_SCREEN_WIDTH;
    m_sizeScreen.cy = DEFAULT_SCREEN_HEIGHT;
	
	// Is the program running?
	m_bActive = true;  

    // default draw fps is off;
    m_bDrawFPS = false;

	// Is DirectInput Ok
	bInputOk = false;

	// Frame rate counters
	FpsFlag=0;
	LastTime = 0;
	CurTime = 0;
	FpsTime = 0;
	DeltaTime = 0;
	FramesRendered = 0;
	Fps = 0;

 	m_hWnd = NULL;
    m_pScreen = NULL;

    m_dwMouseStatus = NULL;

    m_cState = GUI;
    m_cSubState = MAINMENU;
	
	m_LastKey = 0;

	m_hCursor = LoadCursor(m_hInst, IDC_ARROW);

    m_bFullScreen = false;
}

CApp::~CApp()
{
}


bool CApp::ToggleDisplay()
{
    m_bFullScreen = !m_bFullScreen;
    if(m_bFullScreen)
    {
        AdjustWinStyle();
        m_pScreen->CreateFullScreen(m_hWnd, 640, 480, 16);
        // we need to destroy and recreate the supporting CDX objects
        // that can't survive intact when we switch back to fullscreen mode
        {
            // TODO: add your own CDX objects that would have to be
            // destroyed and recreated on a mode switch
        }
    }
    else
    {
        m_pScreen->GetDD()->RestoreDisplayMode();
        AdjustWinStyle();
        m_pScreen->CreateWindowed(m_hWnd, 640, 480);
        // we need to destroy and recreate the supporting CDX objects
        // that can't survive intact when we switch back to windowed mode
        {
            // TODO: add your own CDX objects that would have to be
            // destroyed and recreated on a mode switch
        }
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// WinProc
/////////////////////////////////////////////////////////////////////////////////////////////
long PASCAL CApp::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
	case WM_SIZE:
		// Our window size is fixed, so this could
		// only be a minimize or maximize.
		if ( wParam == SIZE_MINIMIZED ) 
		{
			// We've been minimized, no need to
			// redraw the screen.
			InvalidateRect( hWnd, NULL, TRUE );
			theApp.m_bActive = FALSE;
		}
		else
		{
			theApp.m_bActive = TRUE;
		}
		return 0;
		break;

	case WM_QUERYNEWPALETTE:
		break;

	case WM_SYSKEYUP:
        if(wParam == 'F')
        {
            theApp.m_bDrawFPS = !theApp.m_bDrawFPS;
        }
		if (wParam == VK_RETURN)
		{
            return(theApp.ToggleDisplay());
		}
		return 1;

	case WM_CHAR:
		if(wParam<128)
		{
			theApp.m_Keys[wParam] = 1;
			theApp.m_LastKey = wParam;
		}
		break;

	case WM_KEYDOWN:
/*		if(wParam<128)
		{
			theApp.m_Keys[wParam] = 1;
			theApp.m_LastKey = wParam;
		}*/
		break;

	case WM_KEYUP:
/*
		if(wParam<128)
		{
			theApp.m_Keys[wParam] = 0;
			theApp.m_LastKey = 0;
		}*/
		break;

    case WM_CLOSE:
	case WM_DESTROY:
        theApp.ShutdownGame();
		PostQuitMessage( 0 );
		return 0;

	case WM_DISPLAYCHANGE:
		OutputDebugString( "A setting has changed.\n" );
		break;

	case WM_ACTIVATEAPP:
		// If we wanted to pause the application when it
		// became inactive, we could do so here.
		theApp.m_bActive = (BOOL) wParam;
		if(theApp.m_bActive)
		{
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
		}
		break;

	case WM_LBUTTONDBLCLK:
        theApp.m_dwMouseStatus |= LMB_DCLICK;
		break;

	case WM_RBUTTONDBLCLK:
        theApp.m_dwMouseStatus |= RMB_DCLICK;
		break;


	case WM_RBUTTONUP:
        theApp.m_dwMouseStatus &= ~RMB_DOWN;   // turn off down
        theApp.m_dwMouseStatus |= RMB_UEDGE;   // turn off down
		break;

	case WM_RBUTTONDOWN:
        if(!(theApp.m_dwMouseStatus & RMB_DOWN))
        {
            theApp.m_dwMouseStatus |= RMB_DEDGE;
        }
        theApp.m_dwMouseStatus |= RMB_DOWN;
		break;

    case WM_LBUTTONDOWN:
        {
            //WORD xPos = LOWORD(lParam);  // horizontal position of cursor 
            //WORD yPos = HIWORD(lParam);  // vertical position of cursor 

            // if the mouse wasnt already down, we flag down edge
            // otherwise we just record mouse is down.
            if(!(theApp.m_dwMouseStatus & LMB_DOWN))
            {
                theApp.m_dwMouseStatus |= LMB_DEDGE;
            }
            theApp.m_dwMouseStatus |= LMB_DOWN;
        }
		break;

    case WM_LBUTTONUP:
        theApp.m_dwMouseStatus &= ~LMB_DOWN;    //turn off down
        theApp.m_dwMouseStatus |= LMB_UEDGE;    //turn off down
		break;

    case WM_MOUSEMOVE:
        if(wParam==MK_LBUTTON)
        {
            theApp.m_dwMouseStatus |= LMB_DOWN;
        }
        if(wParam==MK_MBUTTON)
        {
            theApp.m_dwMouseStatus |= MMB_DOWN;
        }
        if(wParam==MK_RBUTTON)
        {
            theApp.m_dwMouseStatus |= RMB_DOWN;
        }
        break;

    case WM_SETCURSOR:
		{
			POINT mpos;
			GetCursorPos(&mpos);
			ScreenToClient(hWnd, &mpos);
			if(PtInRect(&theApp.m_Rect, mpos))
				SetCursor(NULL);
			else
				SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
        return TRUE;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////
// AdjustWinStyle - adjusts the window style according to the mode
/////////////////////////////////////////////////////////////////////
void CApp::AdjustWinStyle()
{
	if (m_bFullScreen)
	{
		DWORD       dwStyle;

		// Change window attributes

		dwStyle = WS_POPUP | WS_VISIBLE;

		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

		SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE |
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}
	else
	{
		RECT        rect = {0, 0, 640, 480};
		DWORD       dwStyle;

		// Change window attributes

		dwStyle = GetWindowStyle(m_hWnd);
		dwStyle &= ~WS_POPUP;
		dwStyle |= WS_OVERLAPPED | WS_CAPTION;

		SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

		// Resize the window so that the client area is 640x480

		AdjustWindowRectEx(&rect, GetWindowStyle(m_hWnd), GetMenu(m_hWnd) != NULL,
			GetWindowExStyle(m_hWnd));

		// Just in case the window was moved off the visible area of the
		// screen.

		SetWindowPos(m_hWnd, NULL, 0, 0, rect.right-rect.left,
			rect.bottom-rect.top, SWP_NOMOVE | SWP_NOZORDER |
			SWP_NOACTIVATE);

		//SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
	}
}

/////////////////////////////////////////////////////////////////////
// ChangeToEXEDir - sets CWD to the DIR the EXE is in
/////////////////////////////////////////////////////////////////////
void CApp::ChangeToEXEDir()
{
	char buf[MAX_PATH];
	char *cptr;

	//now change the directory
	//to make sure were accessing the proper file
	GetModuleFileName(NULL, buf, MAX_PATH);

	//move pointer to end of string
	cptr = buf + lstrlen(buf);

	//find the end of the path
	do
	{
		cptr--;
	} while (*cptr != '\\');
	cptr++;
	*cptr='\0';

	//change directory
	SetCurrentDirectory(buf);
}


/////////////////////////////////////////////////////////////////////////////////////////////
// InitApp - Create the window and the CDX objects
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CApp::Init(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS WndClass;

    m_hInst = hInstance;


#if defined(ONE_INSTANCE_ONLY)
#pragma message("Single Instance Only!")
	if ((m_hWnd = FindWindow(szAppName, 0))==NULL)
	{
        WndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		WndClass.lpfnWndProc = WinProc;
		WndClass.cbClsExtra = 0;
		WndClass.cbWndExtra = 0;
		WndClass.hInstance = m_hInst;
		WndClass.hIcon = LoadIcon(m_hInst, "AppIcon");
		WndClass.hCursor = LoadCursor(0, IDC_ARROW);
        WndClass.hbrBackground = NULL;
		WndClass.lpszMenuName = 0;
		WndClass.lpszClassName = szAppClassName;
		if (!RegisterClass(&WndClass))
		{
		  return(FALSE);
		}
    }
	else
	{
      //we set first instance focus no matter what, not just when its minimized.
      //if (IsIconic(m_hWnd))
	  {
        ShowWindow(m_hWnd,SW_RESTORE);
		SetForegroundWindow(m_hWnd);
	  }
      return(FALSE);    //return false so this instance ends.
    }
#else
#pragma message("Multiple Instances Allowed!")
    WndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WinProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = m_hInst;
    WndClass.hIcon = LoadIcon(m_hInst, "AppIcon");
    WndClass.hCursor = LoadCursor(0, IDC_ARROW);
    WndClass.hbrBackground = NULL;
    WndClass.lpszMenuName = 0;
    WndClass.lpszClassName = szAppClassName;
    if (!RegisterClass(&WndClass))
    {
        return(FALSE);
    }
#endif

    m_hWnd = CreateWindowEx(
			0, //WS_EX_TOPMOST,
			szAppClassName,
			szAppName,
			WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	
			//WS_POPUP | WS_SYSMENU,  // so we get an icon in the tray

            GetSystemMetrics(SM_CXSCREEN)/2-theApp.m_sizeScreen.cx/2,
			GetSystemMetrics(SM_CYSCREEN)/2-theApp.m_sizeScreen.cy/2,
			m_sizeScreen.cx,
			m_sizeScreen.cy,
			NULL,
			NULL,
			m_hInst,
			NULL);

	if(!m_hWnd) return FALSE;

	RECT rc;
	DWORD dwStyle;

	dwStyle = GetWindowStyle(m_hWnd);
	dwStyle |= WS_POPUP | WS_SYSMENU | WS_MINIMIZEBOX | WS_CAPTION;
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	SetRect(&rc, 0, 0, m_sizeScreen.cx, m_sizeScreen.cy);
	m_Rect = rc;

	AdjustWindowRectEx(&rc,
		GetWindowStyle(m_hWnd),
		GetMenu(m_hWnd) != NULL,
		GetWindowExStyle(m_hWnd));

	SetWindowPos(m_hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);


	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

  	ChangeToEXEDir();

	return TRUE;
}




bool CApp::InitializeGame(void)
{
	// Create the CDXSreen object
	m_pScreen = new CDXScreen();
    if(m_pScreen==NULL) return false;
    
    AdjustWinStyle();

    if (!m_pScreen->CreateWindowed(m_hWnd, m_sizeScreen.cx, m_sizeScreen.cy)) return FALSE;
//    if (!m_pScreen->CreateFullScreen(m_hWnd, m_sizeScreen.cx, m_sizeScreen.cy, 16)) return FALSE;
	m_pScreen->SetTripleBuffering( TRUE );
	m_pScreen->GetBack()->Fill(0);
	m_pScreen->Flip();

	// Seed the random-number generator with current time
	srand((unsigned)time(NULL));

    LastTime = timeGetTime();

    GetClientRect(m_hWnd, &(m_Rect));

	GM.Init( m_pScreen, m_pScreen->GetBack(), m_Rect );

	theApp.GuiFont = GM.AddFont("Times New Roman", 16);

    return true;
}



//////////////////////////////////////////////////////////////
// Function name : CApp::ShutdownGame
// Description   : shutdown stuff
//////////////////////////////////////////////////////////////
void CApp::ShutdownGame(void)
{
    SAFEDELETE(m_pScreen);

	DestroyCursor(m_hCursor);
  
}



//////////////////////////////////////////////////////////////
// Function name : GetFixedMouse
// Description   : For windowed mode usually since its possible to move 
//      mouse outside of window rect.  We constrain our cursor to inside
//      the window, and reset the mouse flags if we get outside of window.
//////////////////////////////////////////////////////////////
void CApp::GetFixedMouse()
{
    bool IsOutside = false;

    GetCursorPos(&m_ptCursorPos);
    ScreenToClient(GetHWnd(), &m_ptCursorPos);

    if(m_ptCursorPos.x < 0)
        IsOutside = true;

    if(m_ptCursorPos.x >= m_sizeScreen.cx)
        IsOutside = true;

    if(m_ptCursorPos.y < 0)
        IsOutside = true;

    if(m_ptCursorPos.y >= m_sizeScreen.cy)
        IsOutside = true;

    if(IsOutside)
        m_dwMouseStatus &= ~(LMB_DOWN|MMB_DOWN|RMB_DOWN);
}




//////////////////////////////////////////////////////////////
// Function name : CApp::DoPre
// Description   : Happens every frame before anything else
//////////////////////////////////////////////////////////////
void CApp::DoPre(void)
{
    GetFixedMouse();
}


//////////////////////////////////////////////////////////////
// Function name : CApp::DoPost
// Description   : Happens every frame after everything else.
//////////////////////////////////////////////////////////////
void CApp::DoPost(void)
{
  	m_ptCursorOldPos = m_ptCursorPos;   //store mouse position for comparison between frames

	if(m_pScreen)
	{
		if(PtInRect(&m_Rect, m_ptCursorPos))
		{
			m_pScreen->GetBack()->GetDC();
			DrawIconEx(m_pScreen->GetBack()->m_DC,m_ptCursorPos.x, m_ptCursorPos.y, 
							m_hCursor, 0, 0, 0, NULL, DI_NORMAL);
			m_pScreen->GetBack()->ReleaseDC();
		}

		//flip backbuffer to screen
		//if(m_IsFlipEnabled)
		m_pScreen->Flip(0,0,m_bDrawFPS);
	}

    m_dwMouseStatus &= ~MOUSE_SINGLEFRAME_FLAGS; // turn off mouse flags that only go for 1 frame

}

