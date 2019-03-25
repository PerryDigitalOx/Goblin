#include "GOBManager.h"
#include "AnimObj.h"

AnimObj::AnimObj()
{
	m_dwTime = 0;
	m_TotalFrames = 0;
	m_CurrentFrame = 0;
	m_MSDelay = 0;
	m_DelayType = ANIMDELAY_MS;
	m_IsPlaying = TRUE;
	m_StepRate = 1;
	m_IsLoopy = TRUE;
}

void AnimObj::SetInfo(INT16 curFrame, INT16 totalFrames, UINT16 msDelay, UINT8 delayType)
{
	m_CurrentFrame = curFrame;
	m_TotalFrames = totalFrames;
	m_MSDelay = msDelay;
	m_DelayType = delayType;
}

void AnimObj::Stop()
{
	m_IsPlaying = FALSE;
}

void AnimObj::Start()
{
	m_IsPlaying = TRUE;
}

void AnimObj::SetForward(INT16 steprate)
{
	m_StepRate = steprate;
}

void AnimObj::SetReverse(INT16 steprate)
{
	m_StepRate = -steprate;
}

void AnimObj::ResetTime()
{
	m_dwTime = GM.GetTimeStamp();
}

HRESULT AnimObj::Execute()
{
	//call GetTimeStamp once here to save calls later
	UINT32 thisTime = GM.GetTimeStamp();

	//if time is 0, that means we are not initialized.
	//get timestamp of this frame as initializing value
	if(m_dwTime==0)
	{
		m_dwTime = thisTime;
		return 0;
	}

	if(m_IsPlaying)
	{
		if(m_DelayType == ANIMDELAY_MS)
		{
			if(thisTime - m_dwTime > m_MSDelay)
			{
				m_dwTime = thisTime;

				m_CurrentFrame += m_StepRate;

				if(m_CurrentFrame >= m_TotalFrames) 
				{
					m_CurrentFrame = 0;
					if(!m_IsLoopy)
						Stop();
				}
				else if(m_CurrentFrame<0)
				{
					m_CurrentFrame = m_TotalFrames-1;
					if(!m_IsLoopy)
						Stop();
				}
				return TRUE;
			}
		}
		else if(m_DelayType == ANIMDELAY_FPS)
		{
			//not implemented

			//this should make the animation occur at a fps rate.
			//take total frames and calculate how often the frames 
			//should switch based on current applications fps rate
		}
	}

	return 0;
}
