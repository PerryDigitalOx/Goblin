#include "GOBManager.h"
#include "GOBAvi.h"


CGOBAvi::CGOBAvi()
{
	pAVI=NULL;
	m_Size.cx=0;
	m_Size.cy=0;
	m_Pos.x=0;
	m_Pos.y=0;
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
	if (pAVI)       //Recreate the AVI object if needed
	{
		pAVI->Stop();
		delete pAVI;
		pAVI=NULL;
	}
	IsPlaying=false;
	pAVI = new CAviSurface(filename,GM.GetScreenPtr()->GetDD(),Looped);
	m_Size.cx=Width;
	m_Size.cy=Height;
	if (pAVI) return GOBLIN_SUCCESS; else return GOBLIN_SUCCESS; //Need to add error checking here
}

GOBLIN_RETVAL CGOBAvi::OnDraw(GOBLIN_PARAM param)
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (!IsPlaying) return GOBLIN_DISABLED;
	RECT RCT;
	RCT.top=m_Pos.y;
	RCT.left=m_Pos.x;
	RCT.bottom=m_Pos.y + m_Size.cy;
	RCT.right=m_Pos.x + m_Size.cx;
	if (!(IsPlaying = pAVI->IsRunning())) {Stop();return GOBLIN_SUCCESS;}
	if (FAILED(pAVI->StretchBlitTo(&RCT,GM.GetScreenPtr()->GetBack()->GetDDS()))) return GOBLIN_SUCCESS; //FAILED! error checking here..
	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBAvi::Start()
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (IsPlaying) return GOBLIN_SUCCESS; //Already started
	if (IsPlaying = pAVI->Start()) return GOBLIN_SUCCESS; else return GOBLIN_SUCCESS;     //Need to add another error code for this? failed to start
}

GOBLIN_RETVAL CGOBAvi::Stop()
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	pAVI->Stop();
	if (IsPlaying) return GOBLIN_SUCCESS;  //Ha? can't stop?! need error checking here

    //CB_EVENT(this, GM_USER, 0);        //GM_USER+1 is the AVI "Stopped" event

	return GOBLIN_SUCCESS;
}

GOBLIN_RETVAL CGOBAvi::SetColorKey(DWORD NewColorKey)
{
	if (!pAVI) return GOBLIN_NOTINITIALIZED;
	if (FAILED(pAVI->SetColorKey(NewColorKey))) return GOBLIN_SUCCESS; //NOT TRUE. IT FAILED, BUT THERE IS NO OTHER RETURN VALUE!
	return GOBLIN_SUCCESS;
}
