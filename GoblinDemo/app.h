#if !defined(APP_H)
#define APP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cdx.h>
						   
#define DEFAULT_KEYCOLOR        RGB(255,0,255)

#define DEFAULT_SCREEN_WIDTH    640
#define DEFAULT_SCREEN_HEIGHT   480

// button states as bit settings
#define     LMB_DOWN    0x0001      // left mouse button is down
#define     LMB_DEDGE   0x0002      // left mouse button just went down
#define     LMB_UEDGE   0x0004      // left mouse button just came up ( unused )
#define     LMB_DCLICK	0x0008      // left mouse button double clicked
// middle mouse button
#define     MMB_DOWN    0x0010
#define     MMB_DEDGE   0x0020
#define     MMB_UEDGE   0x0040
#define     MMB_DCLICK  0x0080
// right mouse button
#define     RMB_DOWN    0x0100      
#define     RMB_DEDGE   0x0200
#define     RMB_UEDGE   0x0400
#define     RMB_DCLICK	0x0800

typedef struct PT {
	signed int x;
	signed int y;
}PT, *pPT;


enum states {
    GUI,
    GAME,
    CREDITS,
    MOVIE,
    INTRO,
    EXTRO,
    EXITAPP,
};
enum guisubstates {
    MAINMENU,
    CHARSELMENU,
    OPTIONS,
};
enum gamesubstates {
    STARTPLAY,
    PLAYING,
    PAUSED,
    QUITTING,
};


class CApp  
{
public:
	CApp();
	virtual ~CApp();

public:
	// Routing states
	char		m_cState;
    char		m_cSubState;

    // Is the program running?
	BOOL		m_bActive;  
	RECT		m_Rect;
    DWORD		m_dwMouseStatus;        // mouse button states and flags

    SIZE		m_sizeScreen;
    BOOL		m_bFullScreen;

public:
    CDXScreen * m_pScreen;			//our screen 

	char		GuiFont;
    POINT       m_ptCursorPos;
    POINT       m_ptCursorOldPos;

	char		m_Keys[128];				//our array to hold keyboard keys pressed states
	char		m_LastKey;

public:
    void		DoPre(void);				//stuff happens before routing every frame
    void		DoPost(void);				//stuff happens after routing every frame

	BOOL		Init(HINSTANCE hInst, int nCmdShow);
    bool		InitializeGame(void);
    HWND		GetHWnd()			{ return m_hWnd; }
    bool		ToggleDisplay();

	HINSTANCE	GetHInstance()		{ return m_hInst; }

private:
	char		szAppName[10];
    char		szAppClassName[16];
    HWND		m_hWnd;
	HINSTANCE   m_hInst;

	HICON		m_hCursor;			//our handle to cursor


	BOOL		bInputOk;       // Is DirectInput Ok
    BOOL		m_bDrawFPS;     // draw fps

    // Frame rate counters
	BOOL		FpsFlag;
	DWORD		LastTime;
	DWORD		CurTime;
	DWORD		FpsTime;
	DWORD		DeltaTime;
	DWORD		FramesRendered;
	DWORD		Fps;

    void		ChangeToEXEDir();
    void		AdjustWinStyle();
    void		ShutdownGame(void);
    void		GetFixedMouse();

    static long PASCAL WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


extern CApp     theApp;

#endif // !defined(APP_H)
