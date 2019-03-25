/*
This class is to be used with another object.  Create an instance of this object,
usually inside the class that animation is to be associated with.
On every cycle of your application call the Execute() function.  The return value
will notify you that an animation cycle has completed.  An animation cycle will complete
based on the amount of time of each frame specified or by the frame rate with the number of
game cycles.

  Ex:  
    // initialize animation object with frame information
	pAnimObj.SetInfo(0,0,20);
	.
	.
	.
	// Inside game cycle call animations handler
	if( pAnimObj->Execute() )
	{
		// do something
	}

*/

#ifndef ANIMOBJ_H
#define ANIMOBJ_H

#define ANIMDELAY_MS	1
#define ANIMDELAY_FPS	2

class AnimObj  
{
public:
	// sets default values to private members
	AnimObj();

	// Event handler will return TRUE when animation cycle occurs
	HRESULT Execute();

	// Starts an animation
	void	Start();
	// Stops an animation
	void	Stop();
	// Reset the internal timer.
	void	ResetTime();

	// Check if animation is currently in play mode
	BOOL	IsPlaying()						{ return m_IsPlaying; }

	// Set animation frame conditions
	void	SetInfo(INT16 curFrame, INT16 totalFrames, UINT16 msDelay, UINT8 delayType = ANIMDELAY_MS);
	// Enable/Disable looping of animation
	void	SetLooping(BOOL loopon)			{ m_IsLoopy = loopon; }
	// Set the animation to playback in a forward order
	void	SetForward(INT16 steprate);
	// Set the animation to playback in a backward order
	void	SetReverse(INT16 steprate);

private:
	INT16	m_CurrentFrame;			// Current frame index
	INT16	m_TotalFrames;			// Total number of frames
	UINT16	m_MSDelay;				// Delay in Milliseconds
	UINT8	m_DelayType;			// Delay type
	INT16	m_StepRate;				// Step rate of animation
	UINT32	m_dwTime;				// Animations current time
	BOOL	m_IsPlaying;			// Flag for animation play state
	BOOL	m_IsLoopy;				// Flag for animation loop state
};

#endif
