#include "GOBManager.h"
#include "GOBAvi.h"


CGOBAvi::CGOBAvi()
{
	pAVI=NULL;
	m_Size.cx=0;
	m_Size.cy=0;
	m_Pos.x=0;
	m_Pos.y=0;
	m_Size2=m_Size;
	IsPlaying=false;
}

CGOBAvi::~CGOBAvi()
{
	if (pAVI)
	{
		pAVI->Stop();
		delete pAVI;
		pAVI=NULL;
	}
}

GOBLIN_RETVAL CGOBAvi::LoadFile(char * filename, INT16 Width, INT16 Height, BOOL Looped)
{
	if (IsPlaying)       //Recreate the AVI object if needed
	{
		pAVI->Stop();
		delete pAVI;
		pAVI=NULL;
	}
	IsPlaying=false;
	pAVI = new CAviSurface(filename,GM.GetScreenPtr()->GetDD(),Looped);
	m_Size.cx=Width;
	m_Size.cy=Height;
	m_Size2.cx=m_Size2.cy=0;
	if (!pAVI) return GOBLIN_SUCCESS;  //Need to add error checking here
	return GOBLIN_SUCCESS; //Everything's OK.
}

GOBLIN_RETVAL CGOBAvi::OnDraw(GOBLIN_PARAM param)
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (!(IsPlaying = pAVI->IsRunning())) {Stop();return GOBLIN_SUCCESS;}
	RECT RCT;
	RCT.top=m_Pos.y;
	RCT.left=m_Pos.x;
	RCT.bottom=m_Pos.y + m_Size.cy;
	RCT.right=m_Pos.x + m_Size.cx;
	if (FAILED(pAVI->StretchBlitTo(&RCT,GM.GetScreenPtr()->GetBack()->GetDDS()))) return GOBLIN_SUCCESS; //FAILED! error checking here..
	return GOBLIN_SUCCESS; //Everything's OK.
}

GOBLIN_RETVAL CGOBAvi::Start()
{
	if ((m_Size2.cx!=0) && (m_Size2.cy!=0)) m_Size=m_Size2;
	m_Size2.cx=m_Size2.cy=0;
	SetFlag(WF_TRANSPARENTMOUSE);
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (IsPlaying) return GOBLIN_SUCCESS; //Already started
	if (IsPlaying = pAVI->Start()) 
		return this->OnDraw(0);
	//  return GOBLIN_SUCCESS;
	else return GOBLIN_SUCCESS;     //Need to add another error code for this? failed to start
}

GOBLIN_RETVAL CGOBAvi::Stop()
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	pAVI->Stop();
	pAVI=NULL;
	RemoveFlag(WF_TRANSPARENTMOUSE);
	m_Size2=m_Size;
	m_Size.cx=m_Size.cy=0;
	if (IsPlaying) return GOBLIN_SUCCESS;  //Ha? can't stop?! need error checking here

	if(callback) callback(this,GM_USER,0);
    //CB_EVENT(this, GM_USER, 0);        //GM_USER+1 is the AVI "Stopped" event

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBAvi::SetColorKey(DWORD NewColorKey)
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (FAILED(pAVI->SetColorKey(NewColorKey))) return GOBLIN_SUCCESS; //NOT TRUE. IT FAILED, BUT THERE IS NO OTHER RETURN VALUE!
	return GOBLIN_SUCCESS;
}
