#include "GOBManager.h"
#include "SystemButtons.h"
#include "GOBColor.h"			// for color management

static unsigned char closeimage[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,2,0,0,0,0,0,0,0,0,0,0,2,0,2,
	1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,
	1,0,0,0,2,0,0,0,0,0,0,2,0,0,0,2,
	1,0,0,0,0,2,0,0,0,0,2,0,0,0,0,2,
	1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,
	1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,2,
	1,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,
	1,0,0,0,0,2,0,0,0,0,2,0,0,0,0,2,
	1,0,0,0,2,0,0,0,0,0,0,2,0,0,0,2,
	1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,
	1,0,2,0,0,0,0,0,0,0,0,0,0,2,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,2,0,0,0,0,0,0,0,0,0,0,2,0,1,
	2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,
	2,0,0,0,2,0,0,0,0,0,0,2,0,0,0,1,
	2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1,
	2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,
	2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,2,2,0,0,0,0,0,0,1,
	2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,1,
	2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1,
	2,0,0,0,2,0,0,0,0,0,0,2,0,0,0,1,
	2,0,0,2,0,0,0,0,0,0,0,0,2,0,0,1,
	2,0,2,0,0,0,0,0,0,0,0,0,0,2,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

static unsigned char minimizeimage[] =
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,
	1,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,0,2,2,2,2,2,2,2,2,2,2,2,2,0,1,
	2,0,2,2,2,2,2,2,2,2,2,2,2,2,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

//////////////////////////////////////////////////
// System Close
//
CGOBSysClose::CGOBSysClose() : CGOBButton()
{
	m_Pos.x=0;
	m_Pos.y=0;
	m_Size.cx=16;
	m_Size.cy=16;
}

CGOBSysClose::~CGOBSysClose()
{
}


GOBLIN_RETVAL CGOBSysClose::OnLBUp(GOBLIN_PARAM param)
{
	CGOBButton::OnLBUp(param);	//call super class so handle up,down,hover status

	SendMsg(m_pParent, GM_SYSTEM, SYS_CLOSE);

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBSysClose::OnDraw(GOBLIN_PARAM param)
{
	//now draw close specific stuff
	//...
	UINT8 x = 0;
	UINT8 y = 0;
	UINT16 offset = 0;

	if(m_IsDown)
		offset = 16*16;

	CDXSurface *surf = GM.GetSurfacePtr();

	surf->Lock();
	for(y=0; y<16; y++)
	{
		for(x=0; x<16; x++)
		{
			switch(closeimage[y*16+x+offset])
			{
			case 0:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonFace);
				break;
			case 1:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonHilight);
				break;
			case 2:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonShadow);
				break;
			}
		}
	}
	surf->UnLock();

	return GOBLIN_SUCCESS;
}



//////////////////////////////////////////////////
// System Minimize
//
CGOBSysMinimize::CGOBSysMinimize() : CGOBButton()
{
	m_Pos.x=0;
	m_Pos.y=0;
	m_Size.cx=16;
	m_Size.cy=16;
}

CGOBSysMinimize::~CGOBSysMinimize() {}


GOBLIN_RETVAL CGOBSysMinimize::OnLBUp(GOBLIN_PARAM param)
{
	CGOBButton::OnLBUp(param);	//call super class so handle up,down,hover status

	SendMsg(m_pParent, GM_SYSTEM, SYS_MINIMIZE);

	return GOBLIN_SUCCESS;
}


GOBLIN_RETVAL CGOBSysMinimize::OnDraw(GOBLIN_PARAM param)
{
	//now draw specific stuff
	//...
	UINT8 x = 0;
	UINT8 y = 0;
	UINT16 offset = 0;

	if(m_IsDown)
		offset = 16*16;

	CDXSurface *surf = GM.GetSurfacePtr();

	surf->Lock();
	for(y=0; y<16; y++)
	{
		for(x=0; x<16; x++)
		{
			switch(minimizeimage[y*16+x+offset])
			{
			case 0:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonFace);
				break;
			case 1:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonHilight);
				break;
			case 2:
				surf->PutPixel(m_Pos.x+x, m_Pos.y+y, GWC.ButtonShadow);
				break;
			}
		}
	}
	surf->UnLock();

	return GOBLIN_SUCCESS;
}
