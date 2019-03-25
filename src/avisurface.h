#ifndef __AVISURFACE_H
#define __AVISURFACE_H

#include <vfw.h>
#include <mmsystem.h>

class CAviSurface 
{
protected:
	HRESULT DrawBuffer(void);
	bool m_bRunning;                     // Video is playing
	BOOL m_bLoop;                        // Looping of Video on? 
	DWORD m_dwFps;                       // Freames per Second
	int m_iTimerID;				         // TimerID of timeEvents
	int m_iTimeTick;                     // Time between two frames 
private:
	RECT m_rcSrc;
	CRITICAL_SECTION    m_csAccessBuffer;
	LPDIRECTDRAWSURFACE4 m_lpAviSurface;  // The surface we draw to
	PAVISTREAM m_pasMovie;               // the Handle to the AVI-Videostream
	AVISTREAMINFO m_asiMovie;            // The Video-Information
	LPBYTE m_lpInput,					 // Decompressor Input -Buffer
		   m_lpOutput;                   // Decompressor Output-Buffer
	HIC  m_hicDecompressor;			     // Handle to the AVI-Decompressor
	LONG m_lLength,						 // Input-Bufferlength
		 m_lLinePitch;                   // Bitmap-Linepitch
	LPBITMAPINFOHEADER m_lpScrFmt;       // Format of VideoInput
	LPBITMAPV4HEADER m_lpb4hTargetFmt;   // Format of Surface
	DWORD m_dwColorKeyFlag,              // Flag for Colorkeying in Blt
		  m_dwColorKeyFlagFast;          // Flag for Colorkeying in BltFast 

public:
	LONG m_lIndex,						 // actual Frame - Index
		m_lFrames;                       // Video-Frames in AVI-File
	CAviSurface(char *lpszFilename,LPDIRECTDRAW4 lpDDraw,BOOL bLoop=FALSE);
//  Konstruktor 
//  Input:    lpszFilename - AVI-Filename
//  lpDDraw:  DirectDraw-Interface
//  bLoop:    Endless playing
//  Throws exception if error occurs
	virtual ~CAviSurface();
//  close AVI-File

	int Width()			{ return m_lpb4hTargetFmt->bV4Width; }
	int Height()		{ return m_lpb4hTargetFmt->bV4Height; }

	bool IsRunning(){return m_bRunning;};
//  returns true, if the Video is running

	HRESULT SetColorKey(DWORD dwColorKey);
//  Set a Keycolor (no Keyspace)

	HRESULT BlitTo(int x,int y,LPDIRECTDRAWSURFACE4 lpddsTarget);
//  Draws Videosurface to (left,upper) = (x,y)

	HRESULT StretchBlitTo(RECT *rcTarget,LPDIRECTDRAWSURFACE4 lpddsTarget);
//  Draws Videosurface to Targetrectangle

	virtual bool Start(); 
// Starts Video-Playback (starts the timer to count the frames up)

	virtual void Stop(); 
// Stops the timer

protected:
	int m_iChecktick;
	int m_iRest;
	virtual void ReadFrame(DWORD iFrame);
// Draws Frame with index iFrame to Surface
	virtual void GetNextFrame();
// Counts index up, and reads next frame

private:
	bool Init(LPDIRECTDRAW4 lpDDraw);
// Initalising (called from inside the Constructor, only to split things a bit)
	void Close();
// Freeing all things (called from, the Destructor, or befor the Cunstruktor throws an exception)

	friend void CALLBACK GetFrameTimeProc(UINT uID,UINT uMsg,
			DWORD dwUser,DWORD dw1,DWORD dw2);
// friend to answer the timeEvents
};


class CAviSurfaceWithSound: public CAviSurface
{
private:
	PAVISTREAM m_pasSound;           // Handle to Soundstream in AVI-File
	AVISTREAMINFO m_asiSound;        // Formatinformation of Soundstream
	WAVEFORMATEX *m_lpSoundScrFmt;   // Fromat of Sampledata
	LPDIRECTSOUNDBUFFER m_lpdsbTon;  // The streaming Soundbuffer
    DWORD m_dwLoadPos;               // Loadpos in streaming Buffer
public:
//	CAviSurfaceWithSound(char *lpszFilename,LPDIRECTDRAW2 lpDDraw,LPDIRECTSOUND lpDS,LPDIRECTSOUNDBUFFER m_lpdsPrimary=NULL,BOOL bLoop=FALSE);
	CAviSurfaceWithSound(HWND hWnd, char *lpszFilename,LPDIRECTDRAW4 lpDDraw,BOOL bLoop=FALSE);
//  Opens all required stuff 
//  Throws an exception, if an error occurs while loading  - 
//	maybe a silent handlig of nonexisting sound would be better

	~CAviSurfaceWithSound();
//  Frees all the stuff

	virtual bool Start(); 
//  Starts the soundplay and the videoplayback

	virtual void Stop(); 
//  Stops the soundplay and the videoplayback

	HWND m_AviWnd;

protected:
	BOOL CreateSoundStuff();
	BOOL DestroySoundStuff();
	LPDIRECTSOUND m_lpDS;
	LPDIRECTSOUNDBUFFER m_lpdsPrimary;

	void GetFrameSound();
// Loads the next portion of sound into the Directsoundbuffer

	virtual void GetNextFrame();
// Overrides the Function of CAviSurface - Loads the Sound then calls CAviSurface::GetNextFrame()

private:
//	bool InitSound(LPDIRECTSOUND lpDS);
	bool InitSound(void);
// called ba the Constructor 
	void CloseSound();
// called by the Destructor, or when construction fails
};

//#pragma comment(lib,"vfw32.lib")

#endif
