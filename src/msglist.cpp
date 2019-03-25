#include "GOBManager.h"

#include "MsgList.h"
#define COLOR_WHITE RGB(255,255,255)

//////////////////////////////////////////////////////////////
//   CGOBMsgList Class Constructor
// Function name : CGOBMsgList::CGOBMsgList
// Description   :
//////////////////////////////////////////////////////////////
CGOBMsgList::CGOBMsgList()
{
	m_pSurface = NULL;
	m_iCurrentSize = 0;
	m_iMaxSize = 0;
	m_iMaxLife = 0;
	m_Coordinate.x = 0;
	m_Coordinate.y= 0;
	m_szLine = NULL;
	m_iVerticalSpace = 0;
	m_LineColor = NULL;
}


//////////////////////////////////////////////////////////////
//   CGOBMsgList Class Destructor
// Function name : CGOBMsgList::~CGOBMsgList
// Description   :
//////////////////////////////////////////////////////////////
CGOBMsgList::~CGOBMsgList()
{
	for(int i=0; i<m_iMaxSize; i++)
	{
        DELETEARRAY( m_szLine[i] );
	}

	SAFEDELETE( m_szLine );
    DELETEARRAY(m_LineColor);

}


//////////////////////////////////////////////////////////////
// Function name : CGOBMsgList::Init
// Description   : Sets the list to be drawn on the CDXSurface 'surface'.
//					The list will be drawn onscreen at 'coord'.
//					The list will be set to be 'size' lines long, with 'verticalSpace' between each line.
//					Each line will be on the list for a maximum of 'lifeSpan' milliseconds.
//////////////////////////////////////////////////////////////
void CGOBMsgList::Init(CDXSurface *surface, int x, int y, int size, int verticalSpace, int lifeSpan)
{
	m_pSurface = surface;
	m_Coordinate.x = x;
	m_Coordinate.y = y;
	m_iMaxSize  = size;
	m_iMaxLife = lifeSpan;

	m_szLine  = new char* [size];
	m_LineColor = new COLORREF [size];
	m_iVerticalSpace  = verticalSpace;
	for(int i = 0; i<size; i++)
	{
		m_szLine[i] = new char [80];
	}
	m_iCurrentSize = 0;
}


//////////////////////////////////////////////////////////////
// Function name : CGOBMsgList::Add
// Description   : Adds a line to the list, with variables and formatting.
//////////////////////////////////////////////////////////////
void CGOBMsgList::Add(const char *text, ...)
{
	char str[256];
    va_list args;

    va_start(args, text);
    vsprintf(str, text, args);
    va_end(args);

	if(m_iCurrentSize == m_iMaxSize)
	{
		for(int i = 1; i<m_iCurrentSize; i++)
		{
			strcpy(m_szLine[i-1], m_szLine[i]);
			m_LineColor[i-1] = m_LineColor[i];
		}
		strcpy(m_szLine[i-1], str);
		m_LineColor[i-1] = COLOR_WHITE;
	}
	else
	{
		strcpy(m_szLine[m_iCurrentSize], str);
		m_LineColor[m_iCurrentSize] = COLOR_WHITE;
		m_iCurrentSize++;
	}
	m_dwStartTime = GM.GetTimeStamp();
}


//////////////////////////////////////////////////////////////
// Function name : CGOBMsgList::Add
// Description   : Adds a colored line to the list, with variables and formatting.
//////////////////////////////////////////////////////////////
void CGOBMsgList::Add(COLORREF color, const char *text, ...)
{
	char str[256];
    va_list args;

    va_start(args, text);
    vsprintf(str, text, args);
    va_end(args);

	if(m_iCurrentSize == m_iMaxSize)
	{
		for(int i = 1; i<m_iCurrentSize; i++)
		{
			strcpy(m_szLine[i-1], m_szLine[i]);
			m_LineColor[i-1] = m_LineColor[i];
		}
		strcpy(m_szLine[i-1], str);
		m_LineColor[i-1] = color;
	}
	else
	{
		strcpy(m_szLine[m_iCurrentSize], str);
		m_LineColor[m_iCurrentSize] = color;
		m_iCurrentSize++;
	}
	m_dwStartTime = GM.GetTimeStamp();
}


//////////////////////////////////////////////////////////////
// Function name : CGOBMsgList::Update
// Description   : Draws the list, and removes any lines that have been on the list too long
//////////////////////////////////////////////////////////////
void CGOBMsgList::Update()
{
	if(GM.GetTimeStamp() - m_dwStartTime > m_iMaxLife)
	{
		for(int i = 1; i<m_iCurrentSize; i++)
		{
			strcpy(m_szLine[i-1], m_szLine[i]);
			m_LineColor[i-1] = m_LineColor[i];
		}
		m_dwStartTime = GM.GetTimeStamp();
		if(m_iCurrentSize > 0)
		{
			m_iCurrentSize--;
		}
	}

	m_pSurface->GetDC();
	m_pSurface->SetFont();
	for(int i=0; i<m_iCurrentSize; i++)
	{
		m_pSurface->TextXY(m_Coordinate.x, ((m_iFontHeight * (i+1))+(m_iVerticalSpace * (i+1))), m_LineColor[i], m_szLine[i]);
	}
	m_pSurface->ReleaseDC();
}

/*
CGOBMsgList *msgList=NULL;
void ListLoop(void)
{
	theApp.m_pScreen->GetBack()->Fill(0);

	static int i=0;
	static CDXTimer tmr;
	tmr.LockTime();
	PT p;
	p.x = p.y =5;
	if(!msgList)
	{
			msgList = new CGOBMsgList;
			msgList->Init(theApp.m_pScreen->m_lpDDSBack, p, 5, 10, 3000);
			msgList->ChangeFont("Avalon Quest", 10, 20);
	}
	if(i < 4)
	{
		if(tmr.IsInTime(1000, 0) == 0)
		{
			msgList->AddC(RGB((111*i), (50*i), (50*i)), "%d", i++);
			tmr.Reset();
		}
	}
	msgList->Update();
}
*/
